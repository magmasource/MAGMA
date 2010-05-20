const char *preclb_slave_ver(void) { return "$Id: preclb_slave.c,v 1.40 2009/05/14 04:24:00 ghiorso Exp $"; }

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Slave for residual calculation in PRECLB (file: PRECLB_SLAVE.C)
**
**--
*/

/* System Include Files */

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifndef __APPLE__
#include <malloc.h>
#else
#include <malloc/malloc.h>
#endif

/* MELTS Include Files */

#include "silmin.h"               
#include "recipes.h"

#ifdef USE_MPI

#ifdef BUILD_MGO_SIO2_VERSION
#include "liq_struct_data_MgO_SiO2.h"
#include "sol_struct_data_MgO_SiO2.h"
#include "param_struct_data_MgO_SiO2.h"

#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
#include "liq_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"
#include "sol_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"
#include "param_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"

#else
#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"
#endif

#endif /* USE_MPI */

/* returns 1+ a(p-pr) + b (p-pr)^2 */
double retLiqEosParam (double *r, double t, double p, double *v1, double *v2, double *v3, double *v4, double *a,  double *b);
     
/* MELTS Regression Phase Support */

#include "calibration.h"

static int nParam = 0;

#ifdef USE_MPI
#define DEBUG_MPI         1
#define VERBOSE_DEBUG_MPI 0
#endif

/* 
defining STOLPER_WATER causes all hydroxyl species properties
to depend on those of H2O in a predefined manner 
*/  

#define NOT_STOLPER_WATER

extern int sa_(int     *n, double     *x, int     *max, double     *rt, double     *eps,
  int     *ns, int     *nt, const int     *neps, int     *maxevl, double     *lb, double     *ub,
  double     *c,int     *iprint, int     *iseed1, int     *iseed2, double     *t,
  double     *vm, double     *xopt, double     *fopt, int     *nacc, int     *nfcnev,
  int     *nobds, int     *ier, double     *fstar, double     *xp, int     *nacp);

static double *xLiqSAref, *rLiqSAref, *dgdrLiqSAref, gmixLiqSAref, tSAref, pSAref,
              *xLiqTmp, *rLiqTmp, gmixLiqCur;

int fcn_(int     *n, double     *theta, double    *h) {
  int i, j;
  if (xLiqTmp == NULL) {
    xLiqTmp = (double *) malloc((size_t) nlc*sizeof(double));
    rLiqTmp = (double *) malloc((size_t) (nlc-1)*sizeof(double));
  } 
  for (i=0, j=0; i<nlc; i++) {
    if (xLiqSAref[i] > 0.0) { xLiqTmp[i] = theta[j]; j++; } else xLiqTmp[i] = 0.0;
  }
  conLiq(SECOND, THIRD, tSAref, pSAref, NULL, xLiqTmp, rLiqTmp, NULL, NULL, NULL, NULL);
  gmixLiq(FIRST, tSAref, pSAref, rLiqTmp, &gmixLiqCur, NULL, NULL);  
  for (i=0, *h=gmixLiqCur-gmixLiqSAref; i<(nlc-1); i++) *h += -dgdrLiqSAref[i]*(rLiqTmp[i]-rLiqSAref[i]);
  return (0);
}

#ifdef USE_MPI
static
#endif
void calculateResidualPack(ResidualDataInput *localResidualDataInput, ResidualOutput *localResidualOutput) {
  static double *mu, *muTmp, *muTmpTmp, **dmudw, **dmudwTmp, *dsdw, *dmudt, **d2mudtdw,  *dmudtTmp, **d2muTmpdtdw;
  static int nH2O = -1, nSiOH = -1, nAlOH = -1, nFe3OH = -1, nFe2OH = -1, nMgOH = -1, nCaOH = -1, nNaOH = -1, nKOH = -1,
             nEnthalpy = -1, nEntropy = -1, nDensity = -1, nAdditionalLiquid = -1, 
	     *equivH2OSi, *equivH2OAl, *equivH2OFe3, *equivH2OFe2, *equivH2OMg, *equivH2OCa, *equivH2ONa, *equivH2OK;
#ifndef BUILD_MGO_SIO2_VERSION
#ifndef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION	     
  static int nFe2O3 = -1, nFeO1_3 = -1;
#endif
#endif
  int i = 0;

#ifdef USE_MPI
  if (VERBOSE_DEBUG_MPI) printf("MPI:calculateResidualPack[preclb_slave.c at line %d]--> Entering routine...\n", __LINE__);
#endif

  if (mu == NULL) {
    int j, k;
    int **indIJ = imatrix(0, nls-1, 0, nls-1); 
    mu          = vector(0, nlc-1); 
    muTmp       = vector(0, nlc-1); 
    muTmpTmp    = vector(0, nlc-1); 
    dmudw       = matrix(0, nlc-1, 0, 3*(nls*(nls-1)/2 + nls)+3*(nc+1)-1);
    dmudwTmp    = matrix(0, nlc-1, 0, 3*(nls*(nls-1)/2 + nls)+3*(nc+1)-1);
    dsdw        = vector(0, 3*(nls*(nls-1)/2 + nls)-1);
    dmudt       = vector(0, nlc-1); 
    dmudtTmp    = vector(0, nlc-1); 
    d2mudtdw    = matrix(0, nlc-1, 0, 3*(nls*(nls-1)/2 + nls)+3*(nc+1)-1);
    d2muTmpdtdw = matrix(0, nlc-1, 0, 3*(nls*(nls-1)/2 + nls)+3*(nc+1)-1);
    equivH2OSi  = ivector(0, (nls*(nls-1)/2 + nls)-1);
    equivH2OAl  = ivector(0, (nls*(nls-1)/2 + nls)-1);
    equivH2OFe3 = ivector(0, (nls*(nls-1)/2 + nls)-1);
    equivH2OFe2 = ivector(0, (nls*(nls-1)/2 + nls)-1);
    equivH2OMg  = ivector(0, (nls*(nls-1)/2 + nls)-1);
    equivH2OCa  = ivector(0, (nls*(nls-1)/2 + nls)-1);
    equivH2ONa  = ivector(0, (nls*(nls-1)/2 + nls)-1);
    equivH2OK   = ivector(0, (nls*(nls-1)/2 + nls)-1);
    for (i=0; i<(nls*(nls-1)/2+nls); i++) equivH2OSi[i]  = -1;
    for (i=0; i<(nls*(nls-1)/2+nls); i++) equivH2OAl[i]  = -1;
    for (i=0; i<(nls*(nls-1)/2+nls); i++) equivH2OFe3[i] = -1;
    for (i=0; i<(nls*(nls-1)/2+nls); i++) equivH2OFe2[i] = -1;
    for (i=0; i<(nls*(nls-1)/2+nls); i++) equivH2OMg[i]  = -1;
    for (i=0; i<(nls*(nls-1)/2+nls); i++) equivH2OCa[i]  = -1;
    for (i=0; i<(nls*(nls-1)/2+nls); i++) equivH2ONa[i]  = -1;
    for (i=0; i<(nls*(nls-1)/2+nls); i++) equivH2OK[i]   = -1;
    for (i=0, k=0; i<(nls-1); i++) { indIJ[i][i] = -1; for (j=i+1; j<nls; j++) { indIJ[i][j] = k; indIJ[j][i] = k; k++; } } 

    for (i=0;   i<nlc; i++) if (strcmp(liquid[i].label, "H2O")      == 0) { nH2O   = i; break; }
    for (i=nlc; i<nls; i++) if (strcmp(liquid[i].label, "Si0.25OH") == 0) { nSiOH  = i; break; }
    for (i=nlc; i<nls; i++) if (strcmp(liquid[i].label, "Al0.33OH") == 0) { nAlOH  = i; break; }
    for (i=nlc; i<nls; i++) if (strcmp(liquid[i].label, "Fe0.33OH") == 0) { nFe3OH = i; break; }
    for (i=nlc; i<nls; i++) if (strcmp(liquid[i].label, "Fe0.5OH" ) == 0) { nFe2OH = i; break; }
    for (i=nlc; i<nls; i++) if (strcmp(liquid[i].label, "Mg0.5OH" ) == 0) { nMgOH  = i; break; }
    for (i=nlc; i<nls; i++) if (strcmp(liquid[i].label, "Ca0.5OH" ) == 0) { nCaOH  = i; break; }
    for (i=nlc; i<nls; i++) if (strcmp(liquid[i].label, "NaOH"    ) == 0) { nNaOH  = i; break; }
    for (i=nlc; i<nls; i++) if (strcmp(liquid[i].label, "KOH"     ) == 0) { nKOH   = i; break; }
    if ( (nH2O == -1) || (nSiOH == -1) || (nAlOH == -1) || (nFe3OH == -1) || (nFe2OH == -1) 
                      || (nMgOH == -1) || (nCaOH == -1) || (nNaOH  == -1) || (nKOH   == -1) ) { 
      printf("calculateResidualPack[preclb_slave.c at line %d]--> failure to find index for H2O or *OH.\n", __LINE__);
    } else {
      for (i=0, k=0; i<(nls-1); i++) for (j=i+1; j<nls; j++) {
        if ( (i == nSiOH) && (j != nH2O ) ) equivH2OSi[k] = indIJ[nH2O][j];
	if ( (i != nH2O ) && (j == nSiOH) ) equivH2OSi[k] = indIJ[i][nH2O];
	k++;  
      }
      equivH2OSi[nls*(nls-1)/2+nSiOH] =  nls*(nls-1)/2+nH2O;
      for (i=0, k=0; i<(nls-1); i++) for (j=i+1; j<nls; j++) {
        if ( (i == nAlOH) && (j != nH2O ) ) equivH2OAl[k] = indIJ[nH2O][j];
	if ( (i != nH2O ) && (j == nAlOH) ) equivH2OAl[k] = indIJ[i][nH2O];
	k++;  
      }
      equivH2OAl[nls*(nls-1)/2+nAlOH] =  nls*(nls-1)/2+nH2O;
      for (i=0, k=0; i<(nls-1); i++) for (j=i+1; j<nls; j++) {
        if ( (i == nFe3OH) && (j != nH2O )  ) equivH2OFe3[k] = indIJ[nH2O][j];
	if ( (i != nH2O  ) && (j == nFe3OH) ) equivH2OFe3[k] = indIJ[i][nH2O];
	k++;  
      }
      equivH2OFe3[nls*(nls-1)/2+nFe3OH] =  nls*(nls-1)/2+nH2O;
      for (i=0, k=0; i<(nls-1); i++) for (j=i+1; j<nls; j++) {
        if ( (i == nFe2OH) && (j != nH2O )  ) equivH2OFe2[k] = indIJ[nH2O][j];
	if ( (i != nH2O  ) && (j == nFe2OH) ) equivH2OFe2[k] = indIJ[i][nH2O];
	k++;  
      }
      equivH2OFe2[nls*(nls-1)/2+nFe2OH] =  nls*(nls-1)/2+nH2O;
      for (i=0, k=0; i<(nls-1); i++) for (j=i+1; j<nls; j++) {
        if ( (i == nMgOH) && (j != nH2O ) ) equivH2OMg[k] = indIJ[nH2O][j];
	if ( (i != nH2O ) && (j == nMgOH) ) equivH2OMg[k] = indIJ[i][nH2O];
	k++;  
      }
      equivH2OMg[nls*(nls-1)/2+nMgOH] =  nls*(nls-1)/2+nH2O;
      for (i=0, k=0; i<(nls-1); i++) for (j=i+1; j<nls; j++) {
        if ( (i == nCaOH) && (j != nH2O ) ) equivH2OCa[k] = indIJ[nH2O][j];
	if ( (i != nH2O ) && (j == nCaOH) ) equivH2OCa[k] = indIJ[i][nH2O];
	k++;  
      }
      equivH2OCa[nls*(nls-1)/2+nCaOH] =  nls*(nls-1)/2+nH2O;
      for (i=0, k=0; i<(nls-1); i++) for (j=i+1; j<nls; j++) {
        if ( (i == nNaOH) && (j != nH2O ) ) equivH2ONa[k] = indIJ[nH2O][j];
	if ( (i != nH2O ) && (j == nNaOH) ) equivH2ONa[k] = indIJ[i][nH2O];
	k++;  
      }
      equivH2ONa[nls*(nls-1)/2+nNaOH] =  nls*(nls-1)/2+nH2O;
      for (i=0, k=0; i<(nls-1); i++) for (j=i+1; j<nls; j++) {
        if ( (i == nKOH) && (j != nH2O) ) equivH2OK[k] = indIJ[nH2O][j];
	if ( (i != nH2O) && (j == nKOH) ) equivH2OK[k] = indIJ[i][nH2O];
	k++;  
      }
      equivH2OK[nls*(nls-1)/2+nKOH] =  nls*(nls-1)/2+nH2O;
    }
#ifndef BUILD_MGO_SIO2_VERSION
#ifndef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
    for (i=0; i<nc+1; i++) if (strcmp(bulkSystem[i].label, "Fe2O3" ) == 0) { nFe2O3  = i; break; }
    for (i=0; i<nc+1; i++) if (strcmp(bulkSystem[i].label, "FeO1_3") == 0) { nFeO1_3 = i; break; }
    if ( (nFe2O3 == -1) || (nFeO1_3 == -1) )
      printf("calculateResidualPack[preclb_slave.c at line %d]--> failure to find index for one or both of Fe2O3 and FeO1_3 in bulkSystem[].\n", __LINE__);
#endif 
#endif   
    for (i=0; i<npc; i++) if (strcmp(solids[i].label, "density") == 0) { nDensity  = i; break; }
    if (nDensity == -1) 
      printf("calculateResidualPack[preclb_slave.c at line %d]--> failure to find index for solid phase <density>.\n", __LINE__);
    for (i=0; i<npc; i++) if (strcmp(solids[i].label, "entropy") == 0) { nEntropy  = i; break; }
    if (nEntropy == -1) 
      printf("calculateResidualPack[preclb_slave.c at line %d]--> failure to find index for solid phase <entropy>.\n", __LINE__);
    for (i=0; i<npc; i++) if (strcmp(solids[i].label, "enthalpy") == 0) { nEnthalpy  = i; break; }
    if (nEnthalpy == -1) 
      printf("calculateResidualPack[preclb_slave.c at line %d]--> failure to find index for solid phase <enthalpy>.\n", __LINE__);
    for (i=0; i<npc; i++) if (strcmp(solids[i].label, "liquid") == 0) { nAdditionalLiquid  = i; break; }
    if (nAdditionalLiquid == -1) 
      printf("calculateResidualPack[preclb_slave.c at line %d]--> failure to find index for solid phase <liquid>.\n", __LINE__);
    
    free_imatrix(indIJ, 0, nls-1, 0, nls-1);
        
    if (nParam == 0) {
      for (k=0; k<(nls*(nls-1)/2 + nls + npc); k++) {
        if ( (modelParameters[k].activeH && !modelParameters[k].activeF) ) nParam++; 
        if ( modelParameters[k].activeS )                                  nParam++;
        if ( modelParameters[k].activeV )                                  nParam++;
      }
#ifdef BUILD_MGO_SIO2_VERSION
      for (k=0; k<nc; k++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
      for (k=0; k<nc; k++) {
#else
      for (k=0; k<(nc+1); k++) {
#endif
        if ( eosModelParameters[k].activeKp   ) nParam++; 
        if ( eosModelParameters[k].activeKpp  ) nParam++;
        if ( eosModelParameters[k].activeKppp ) nParam++;
      }
    }

  }

#ifdef USE_MPI
  if (VERBOSE_DEBUG_MPI) printf("MPI:calculateResidualPack[preclb_slave.c at line %d]--> ...finished initialization block...\n", __LINE__);
#endif

  /* typedef struct _residualDataInput {										       */
  /*   int    LEPRnum;    LEPRnum,                unique LEPR database experiment index number                                 */
  /*   double t;	  t,		          temperature of the experiment in Kelvin				       */
  /*   double p;	  p,		          pressure of the experiment in bars				               */
  /*   double fo2;	  fo2,		          log 10 fo2 of the experiment						       */
  /*   int    nLiq;	  nLiq,		          number of liquids in this experiment					       */
  /*   double **rLiq;	  rLiq[0->nLiq][0->nc-1], vector of independent composition variables for liquid(s) in this experiment */
  /*   int    nSol;	  nSol,		          number of solids in this experiment					       */
  /*   int    *pIndex;    pIndex[0->nSol],        phase index of solid							       */
  /*   int    *cIndex;    pIndex[0->nSol],        component index of solid  						       */
  /*   double **rSol;	  rSol[0->nSol][0->nr],	  vector of independent composition variables for solid(s) in this experiment  */
  /*   int    *isEqual;   isEqual[0->nSol],       TRUE if equality constraint; FALSE if bound				       */  
  /*   double *depenG;	  depen[0->nsol],         Dependent variable in regresion problem (Gibbs free energy)		       */
  /*   double *dependGdT; depen[0->nsol],         Dependent variable in regresion problem (nagative entropy)		       */
  /* } ResidualDataInput;												       */
  /*															       */
  /* typedef struct _residualOutput {											       */
  /*   int flag;	  flag, TRUE if valid output retuned; false otherwise						       */
  /*   double *residuals; vector of returned residuals. Undef if valid == FALSE 					       */
  /* } ResidualOutput;  												       */
  
  localResidualOutput->flag = TRUE;
  if ( (localResidualDataInput->nLiq > 1) || (localResidualDataInput->nSol > 0) ) {
    int j;
/*  int    LEPRnum = localResidualDataInput->LEPRnum; */
    double t       = localResidualDataInput->t;
    double p       = localResidualDataInput->p;
    double *rLiq   = (localResidualDataInput->rLiq)[0];
    double denom, v1, v2, v3, v4, a, b;

#ifdef USE_MPI
    if (VERBOSE_DEBUG_MPI) printf("MPI:calculateResidualPack[preclb_slave.c at line %d]--> ...about to call actLiq()...\n", __LINE__);
#endif

#ifdef STOLPER_WATER
    /* Compute properties of the liquid */
    if ( (nH2O != -1) && (nSiOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OSi[j] != -1) && modelParameters[equivH2OSi[j]].activeH ) {
        modelParameters[j].activeH  = TRUE;
	modelParameters[j].enthalpy = modelParameters[equivH2OSi[j]].enthalpy/2.0;
      }
      if ( (equivH2OSi[j] != -1) && modelParameters[equivH2OSi[j]].activeS ) {
        modelParameters[j].activeS  = TRUE;
        modelParameters[j].entropy  = modelParameters[equivH2OSi[j]].entropy/2.0;
      }
      if ( (equivH2OSi[j] != -1) && modelParameters[equivH2OSi[j]].activeV ) {
        modelParameters[j].activeV  = TRUE;
        modelParameters[j].volume   = modelParameters[equivH2OSi[j]].volume/2.0;
      }
    }
    if ( (nH2O != -1) && (nAlOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OAl[j] != -1) && modelParameters[equivH2OAl[j]].activeH ) {
        modelParameters[j].activeH  = TRUE;
	modelParameters[j].enthalpy = modelParameters[equivH2OAl[j]].enthalpy/2.0;
      }
      if ( (equivH2OAl[j] != -1) && modelParameters[equivH2OAl[j]].activeS ) {
        modelParameters[j].activeS  = TRUE;
        modelParameters[j].entropy  = modelParameters[equivH2OAl[j]].entropy/2.0;
      }
      if ( (equivH2OAl[j] != -1) && modelParameters[equivH2OAl[j]].activeV ) {
        modelParameters[j].activeV  = TRUE;
        modelParameters[j].volume   = modelParameters[equivH2OAl[j]].volume/2.0;
      }
    }
    if ( (nH2O != -1) && (nFe3OH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OFe3[j] != -1) && modelParameters[equivH2OFe3[j]].activeH ) {
        modelParameters[j].activeH  = TRUE;
	modelParameters[j].enthalpy = modelParameters[equivH2OFe3[j]].enthalpy/2.0;
      }
      if ( (equivH2OFe3[j] != -1) && modelParameters[equivH2OFe3[j]].activeS ) {
        modelParameters[j].activeS  = TRUE;
        modelParameters[j].entropy  = modelParameters[equivH2OFe3[j]].entropy/2.0;
      }
      if ( (equivH2OFe3[j] != -1) && modelParameters[equivH2OFe3[j]].activeV ) {
        modelParameters[j].activeV  = TRUE;
        modelParameters[j].volume   = modelParameters[equivH2OFe3[j]].volume/2.0;
      }
    }
    if ( (nH2O != -1) && (nFe2OH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OFe2[j] != -1) && modelParameters[equivH2OFe2[j]].activeH ) {
        modelParameters[j].activeH  = TRUE;
	modelParameters[j].enthalpy = modelParameters[equivH2OFe2[j]].enthalpy/2.0;
      }
      if ( (equivH2OFe2[j] != -1) && modelParameters[equivH2OFe2[j]].activeS ) {
        modelParameters[j].activeS  = TRUE;
        modelParameters[j].entropy  = modelParameters[equivH2OFe2[j]].entropy/2.0;
      }
      if ( (equivH2OFe2[j] != -1) && modelParameters[equivH2OFe2[j]].activeV ) {
        modelParameters[j].activeV  = TRUE;
        modelParameters[j].volume   = modelParameters[equivH2OFe2[j]].volume/2.0;
      }
    }
    if ( (nH2O != -1) && (nMgOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OMg[j] != -1) && modelParameters[equivH2OMg[j]].activeH ) {
        modelParameters[j].activeH  = TRUE;
	modelParameters[j].enthalpy = modelParameters[equivH2OMg[j]].enthalpy/2.0;
      }
      if ( (equivH2OMg[j] != -1) && modelParameters[equivH2OMg[j]].activeS ) {
        modelParameters[j].activeS  = TRUE;
        modelParameters[j].entropy  = modelParameters[equivH2OMg[j]].entropy/2.0;
      }
      if ( (equivH2OMg[j] != -1) && modelParameters[equivH2OMg[j]].activeV ) {
        modelParameters[j].activeV  = TRUE;
        modelParameters[j].volume   = modelParameters[equivH2OMg[j]].volume/2.0;
      }
    }
    if ( (nH2O != -1) && (nCaOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OCa[j] != -1) && modelParameters[equivH2OCa[j]].activeH ) {
        modelParameters[j].activeH  = TRUE;
	modelParameters[j].enthalpy = modelParameters[equivH2OCa[j]].enthalpy/2.0;
      }
      if ( (equivH2OCa[j] != -1) && modelParameters[equivH2OCa[j]].activeS ) {
        modelParameters[j].activeS  = TRUE;
        modelParameters[j].entropy  = modelParameters[equivH2OCa[j]].entropy/2.0;
      }
      if ( (equivH2OCa[j] != -1) && modelParameters[equivH2OCa[j]].activeV ) {
        modelParameters[j].activeV  = TRUE;
        modelParameters[j].volume   = modelParameters[equivH2OCa[j]].volume/2.0;
      }
    }
    if ( (nH2O != -1) && (nNaOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2ONa[j] != -1) && modelParameters[equivH2ONa[j]].activeH ) {
        modelParameters[j].activeH  = TRUE;
	modelParameters[j].enthalpy = modelParameters[equivH2ONa[j]].enthalpy/2.0;
      }
      if ( (equivH2ONa[j] != -1) && modelParameters[equivH2ONa[j]].activeS ) {
        modelParameters[j].activeS  = TRUE;
        modelParameters[j].entropy  = modelParameters[equivH2ONa[j]].entropy/2.0;
      }
      if ( (equivH2ONa[j] != -1) && modelParameters[equivH2ONa[j]].activeV ) {
        modelParameters[j].activeV  = TRUE;
        modelParameters[j].volume   = modelParameters[equivH2ONa[j]].volume/2.0;
      }
    }
    if ( (nH2O != -1) && (nKOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OK[j] != -1) && modelParameters[equivH2OK[j]].activeH ) {
        modelParameters[j].activeH  = TRUE;
	modelParameters[j].enthalpy = modelParameters[equivH2OK[j]].enthalpy/2.0;
      }
      if ( (equivH2OK[j] != -1) && modelParameters[equivH2OK[j]].activeS ) {
        modelParameters[j].activeS  = TRUE;
        modelParameters[j].entropy  = modelParameters[equivH2OK[j]].entropy/2.0;
      }
      if ( (equivH2OK[j] != -1) && modelParameters[equivH2OK[j]].activeV ) {
        modelParameters[j].activeV  = TRUE;
        modelParameters[j].volume   = modelParameters[equivH2OK[j]].volume/2.0;
      }
    }
#endif /* STOLPER_WATER */

#ifndef BUILD_MGO_SIO2_VERSION
#ifndef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
    if (eosModelParameters[nFe2O3 ].activeKp || eosModelParameters[nFe2O3 ].activeKpp || eosModelParameters[nFe2O3 ].activeKppp ||
        eosModelParameters[nFeO1_3].activeKp || eosModelParameters[nFeO1_3].activeKpp || eosModelParameters[nFeO1_3].activeKppp) {
	int j;
	static double *oxides, *molFrac;  
	if (oxides  == NULL) oxides  = (double *) malloc((size_t)  nc*sizeof(double));
	if (molFrac == NULL) molFrac = (double *) malloc((size_t) nlc*sizeof(double));
	
	/* Convert r -> X -> oxide moles and recalculate ferric/ferrous ratio */
	conLiq(THIRD, FOURTH, t, p, NULL, NULL, rLiq, molFrac, NULL, NULL, NULL);
	for (i=0; i<nc; i++) for (j=0, oxides[i]=0.0; j<nlc; j++) oxides[i] += molFrac[j]*(liquid[j].liqToOx)[i];
	conLiq(FIRST | SEVENTH, FIRST, t, p, oxides, NULL, NULL, NULL, NULL, NULL, &(localResidualDataInput->fo2));
	
	/*  Test for EOS violation; convert oxide moles -> r */
	if (!testLiq(EIGHTH, 0, 0, 0, 0, NULL, NULL, NULL, NULL)) localResidualOutput->flag = FALSE;
	else {
	  for (i=0; i<nlc; i++) for (j=0, molFrac[i]=0.0; j<nc; j++) molFrac[i] += oxides[j]*(bulkSystem[j].oxToLiq)[i];
	  conLiq(SECOND, THIRD, t, p, NULL, molFrac, rLiq, NULL, NULL, NULL, NULL);
	}
    } 
#endif
#endif
      
    if ((denom = retLiqEosParam (rLiq, t, p, &v1, &v2, &v3, &v4, &a, &b)) <= 0.0) {
      printf("Liq LEPR No = %d, t = %f (C), p = %f (GPa)\n", localResidualDataInput->LEPRnum, localResidualDataInput->t-273.15, localResidualDataInput->p/10000.0);
      printf("  denom = %g, v1 = %g, v2 = %g, v3 = %g, v4 = %g, a = %g, b=%g (all GPa)\n", denom, v1*10000.0, v2*10000.0*10000.0, v3*10000.0*10000.0*10000.0, 
        v4*10000.0*10000.0*10000.0*10000.0, a*10000.0, b*10000.0*10000.0);
      localResidualOutput->flag = FALSE;
    
    } else { 
      actLiq (SECOND | FOURTH, t, p, rLiq, NULL, mu, NULL, dmudw);
      /* Fill in eos derivatives using finite differences */
      if(testLiq (EIGHTH, t, p, 0, 0, NULL, NULL, NULL, NULL) && testLiq (SEVENTH, t, p, 0, 0, NULL, NULL, NULL, NULL)) {
        if (useTregression) {
#ifndef NEVER_DEFINED
	  actLiq (EIGHTH | NINTH, t, p, rLiq, NULL, dmudt, NULL, d2mudtdw);
#else
          actLiq (EIGHTH, t, p, rLiq, NULL, dmudt, NULL, NULL);
	  for (i=0; i<(nls*(nls-1)/2+nls); i++) {
	    if (modelParameters[i].activeH) {
	      double hOld = modelParameters[i].enthalpy;
	      modelParameters[i].enthalpy = hOld + ((hOld != 0.0) ? fabs(hOld)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON));
	      actLiq (EIGHTH, t, p, rLiq, NULL, dmudtTmp, NULL, NULL);
	      for (j=0; j<nlc; j++) d2mudtdw[j][i] = (dmudtTmp[j]-dmudt[j])/(modelParameters[i].enthalpy-hOld);
	      modelParameters[i].enthalpy = hOld;
	    }
	    if (modelParameters[i].activeS) {
	      double sOld = modelParameters[i].entropy;
	      modelParameters[i].entropy = sOld + ((sOld != 0.0) ? fabs(sOld)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON));
	      actLiq (EIGHTH, t, p, rLiq, NULL, dmudtTmp, NULL, NULL);
	      for (j=0; j<nlc; j++) d2mudtdw[j][i+nls*(nls-1)/2+nls] = (dmudtTmp[j]-dmudt[j])/(modelParameters[i].entropy-sOld);
	      modelParameters[i].entropy = sOld;
	    }
	    if (modelParameters[i].activeV) {
	      double vOld = modelParameters[i].volume;
	      modelParameters[i].volume = vOld + ((vOld != 0.0) ? fabs(vOld)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON));
	      actLiq (EIGHTH, t, p, rLiq, NULL, dmudtTmp, NULL, NULL);
	      for (j=0; j<nlc; j++) d2mudtdw[j][i+2*nls*(nls-1)/2+2*nls] = (dmudtTmp[j]-dmudt[j])/(modelParameters[i].volume-vOld);
	      modelParameters[i].volume = vOld;
	    }
	  }
#endif
	}
#ifdef BUILD_MGO_SIO2_VERSION
        for (i=0; i<nc; i++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
        for (i=0; i<nc; i++) {
#else
        for (i=0; i<(nc+1); i++) {
#endif
          if (eosModelParameters[i].activeKp || eosModelParameters[i].activeKpp || eosModelParameters[i].activeKppp) {
	    double v0	 = bulkSystem[i].gk_v;
     	    double alpha = (v0 != 0.0) ? bulkSystem[i].gk_dvdt/v0 : 0.0;
     	    double c	 = bulkSystem[i].gk_c;
     	    double cp	 = bulkSystem[i].gk_cp;
     	    double mw	 = bulkSystem[i].mw;
     	    double v1	 = ((mw != 0.0) && (c != 0.0) && (cp != 0.0)) ? -v0*v0*(1000.0/(mw*c*c) + 1673.15*alpha*alpha/(cp)) : 0.0;
     	    double K	 = (v1 != 0.0) ? -v0/v1 : 0.0;
    	    double KpR	 = eosModelParameters[i].Kp;
    	    double KppR  = eosModelParameters[i].Kpp;
    	    double KpppR = eosModelParameters[i].Kppp;
	  
            if (eosModelParameters[i].activeKp) {
              double v2   = eosModelParameters[i].v2;
              double v3   = eosModelParameters[i].v3;
              double v4   = eosModelParameters[i].v4;
              double Kp   = KpR + ((KpR != 0.0) ? fabs(KpR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON));
	      double Kpp  = KppR;
	      double Kppp = KpppR;
     	      eosModelParameters[i].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	      eosModelParameters[i].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	      eosModelParameters[i].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
              actLiq (SECOND, t, p, rLiq, NULL, muTmp, NULL, NULL);
	      if (useTregression) actLiq (EIGHTH, t, p, rLiq, NULL, dmudtTmp, NULL, NULL);
              eosModelParameters[i].v2 = v2;
              eosModelParameters[i].v3 = v3;
              eosModelParameters[i].v4 = v4;
              for (j=0; j<nlc; j++) dmudw[j][3*(nls*(nls-1)/2 + nls) + 3*i] = (muTmp[j]-mu[j])/(Kp-KpR);
	      if (useTregression) for (j=0; j<nlc; j++) d2mudtdw[j][3*(nls*(nls-1)/2 + nls) + 3*i] = (dmudtTmp[j]-dmudt[j])/(Kp-KpR);
            }
            if (eosModelParameters[i].activeKpp) {
              double v2   = eosModelParameters[i].v2;
              double v3   = eosModelParameters[i].v3;
              double v4   = eosModelParameters[i].v4;
              double Kp   = KpR;
	      double Kpp  = KppR + ((KppR != 0.0) ? fabs(KppR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)/10000.0);
	      double Kppp = KpppR;
     	      eosModelParameters[i].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	      eosModelParameters[i].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	      eosModelParameters[i].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
              actLiq (SECOND, t, p, rLiq, NULL, muTmp, NULL, NULL);
	      if (useTregression) actLiq (EIGHTH, t, p, rLiq, NULL, dmudtTmp, NULL, NULL);
              eosModelParameters[i].v2 = v2;
              eosModelParameters[i].v3 = v3;
              eosModelParameters[i].v4 = v4;
              for (j=0; j<nlc; j++) dmudw[j][3*(nls*(nls-1)/2 + nls) + 3*i + 1] = (muTmp[j]-mu[j])/(Kpp-KppR);
              if (useTregression) for (j=0; j<nlc; j++) d2mudtdw[j][3*(nls*(nls-1)/2 + nls) + 3*i + 1] = (dmudtTmp[j]-dmudt[j])/(Kpp-KppR);
            }
            if (eosModelParameters[i].activeKppp) {
              double v2   = eosModelParameters[i].v2;
              double v3   = eosModelParameters[i].v3;
              double v4   = eosModelParameters[i].v4;
              double Kp   = KpR;
	      double Kpp  = KppR;
	      double Kppp = KpppR + ((KpppR != 0.0) ? fabs(KpppR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)/10000.0/10000.0);
     	      eosModelParameters[i].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	      eosModelParameters[i].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	      eosModelParameters[i].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
              actLiq (SECOND, t, p, rLiq, NULL, muTmp, NULL, NULL);
	      if (useTregression) actLiq (EIGHTH, t, p, rLiq, NULL, dmudtTmp, NULL, NULL);
              eosModelParameters[i].v2 = v2;
              eosModelParameters[i].v3 = v3;
              eosModelParameters[i].v4 = v4;
              for (j=0; j<nlc; j++) dmudw[j][3*(nls*(nls-1)/2 + nls) + 3*i + 2] = (muTmp[j]-mu[j])/(Kppp-KpppR);
              if (useTregression) for (j=0; j<nlc; j++) d2mudtdw[j][3*(nls*(nls-1)/2 + nls) + 3*i + 2] = (dmudtTmp[j]-dmudt[j])/(Kppp-KpppR);
            }	   
          } /* end test if Kp, Kpp, Kppp are active parameters */
	} /* end loop on oxides */
      } else localResidualOutput->flag = FALSE;
    }

#ifdef STOLPER_WATER    
    if ( (nH2O != -1) && (nSiOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OSi[j] != -1) && modelParameters[equivH2OSi[j]].activeH ) modelParameters[j].activeH  = FALSE;
      if ( (equivH2OSi[j] != -1) && modelParameters[equivH2OSi[j]].activeS ) modelParameters[j].activeS  = FALSE;
      if ( (equivH2OSi[j] != -1) && modelParameters[equivH2OSi[j]].activeV ) modelParameters[j].activeV  = FALSE;
    }
    if ( (nH2O != -1) && (nAlOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OAl[j] != -1) && modelParameters[equivH2OAl[j]].activeH ) modelParameters[j].activeH  = FALSE;
      if ( (equivH2OAl[j] != -1) && modelParameters[equivH2OAl[j]].activeS ) modelParameters[j].activeS  = FALSE;
      if ( (equivH2OAl[j] != -1) && modelParameters[equivH2OAl[j]].activeV ) modelParameters[j].activeV  = FALSE;
    }
    if ( (nH2O != -1) && (nFe3OH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OFe3[j] != -1) && modelParameters[equivH2OFe3[j]].activeH ) modelParameters[j].activeH  = FALSE;
      if ( (equivH2OFe3[j] != -1) && modelParameters[equivH2OFe3[j]].activeS ) modelParameters[j].activeS  = FALSE;
      if ( (equivH2OFe3[j] != -1) && modelParameters[equivH2OFe3[j]].activeV ) modelParameters[j].activeV  = FALSE;
    }
    if ( (nH2O != -1) && (nFe2OH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OFe2[j] != -1) && modelParameters[equivH2OFe2[j]].activeH ) modelParameters[j].activeH  = FALSE;
      if ( (equivH2OFe2[j] != -1) && modelParameters[equivH2OFe2[j]].activeS ) modelParameters[j].activeS  = FALSE;
      if ( (equivH2OFe2[j] != -1) && modelParameters[equivH2OFe2[j]].activeV ) modelParameters[j].activeV  = FALSE;
    }
    if ( (nH2O != -1) && (nMgOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OMg[j] != -1) && modelParameters[equivH2OMg[j]].activeH ) modelParameters[j].activeH  = FALSE;
      if ( (equivH2OMg[j] != -1) && modelParameters[equivH2OMg[j]].activeS ) modelParameters[j].activeS  = FALSE;
      if ( (equivH2OMg[j] != -1) && modelParameters[equivH2OMg[j]].activeV ) modelParameters[j].activeV  = FALSE;
    }
    if ( (nH2O != -1) && (nCaOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OCa[j] != -1) && modelParameters[equivH2OCa[j]].activeH ) modelParameters[j].activeH  = FALSE;
      if ( (equivH2OCa[j] != -1) && modelParameters[equivH2OCa[j]].activeS ) modelParameters[j].activeS  = FALSE;
      if ( (equivH2OCa[j] != -1) && modelParameters[equivH2OCa[j]].activeV ) modelParameters[j].activeV  = FALSE;
    }
    if ( (nH2O != -1) && (nNaOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2ONa[j] != -1) && modelParameters[equivH2ONa[j]].activeH ) modelParameters[j].activeH  = FALSE;
      if ( (equivH2ONa[j] != -1) && modelParameters[equivH2ONa[j]].activeS ) modelParameters[j].activeS  = FALSE;
      if ( (equivH2ONa[j] != -1) && modelParameters[equivH2ONa[j]].activeV ) modelParameters[j].activeV  = FALSE;
    }
    if ( (nH2O != -1) && (nKOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
      if ( (equivH2OK[j] != -1) && modelParameters[equivH2OK[j]].activeH ) modelParameters[j].activeH  = FALSE;
      if ( (equivH2OK[j] != -1) && modelParameters[equivH2OK[j]].activeS ) modelParameters[j].activeS  = FALSE;
      if ( (equivH2OK[j] != -1) && modelParameters[equivH2OK[j]].activeV ) modelParameters[j].activeV  = FALSE;
    }
#endif /* STOLPER_WATER */

#ifdef USE_MPI
    if (VERBOSE_DEBUG_MPI) printf("MPI:calculateResidualPack[preclb_slave.c at line %d]--> ...return from actLiq()...\n", __LINE__);
#endif
    
    /* Fix computed derivatives for activeF flag */
    if (localResidualOutput->flag) { /* EOS and Ordering state convergence verified */
      for (j=0; j<(nls*(nls-1)/2 + nls); j++) if (modelParameters[j].activeF) {
        double tFus = (j < (nls*(nls-1)/2)) ? 1473.15 : liquid[j-(nls*(nls-1)/2)].tfus;
        for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls) + j] += tFus*dmudw[i][j];
      }
#ifdef STOLPER_WATER
      if ( (nH2O != -1) && (nSiOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
        if ( (equivH2OSi[j] != -1) && modelParameters[equivH2OSi[j]].activeH ) for (i=0; i<nlc; i++) dmudw[i][equivH2OSi[j]] += dmudw[i][j]/2.0;
        if ( (equivH2OSi[j] != -1) && modelParameters[equivH2OSi[j]].activeS ) for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls)+equivH2OSi[j]] += dmudw[i][(nls*(nls-1)/2 + nls)+j]/2.0;
      }
      if ( (nH2O != -1) && (nAlOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
        if ( (equivH2OAl[j] != -1) && modelParameters[equivH2OAl[j]].activeH ) for (i=0; i<nlc; i++) dmudw[i][equivH2OAl[j]] += dmudw[i][j]/2.0;
        if ( (equivH2OAl[j] != -1) && modelParameters[equivH2OAl[j]].activeS ) for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls)+equivH2OAl[j]] += dmudw[i][(nls*(nls-1)/2 + nls)+j]/2.0;
      }
      if ( (nH2O != -1) && (nFe3OH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
        if ( (equivH2OFe3[j] != -1) && modelParameters[equivH2OFe3[j]].activeH ) for (i=0; i<nlc; i++) dmudw[i][equivH2OFe3[j]] += dmudw[i][j]/2.0;
        if ( (equivH2OFe3[j] != -1) && modelParameters[equivH2OFe3[j]].activeS ) for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls)+equivH2OFe3[j]] += dmudw[i][(nls*(nls-1)/2 + nls)+j]/2.0;
      }
      if ( (nH2O != -1) && (nFe2OH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
        if ( (equivH2OFe2[j] != -1) && modelParameters[equivH2OFe2[j]].activeH ) for (i=0; i<nlc; i++) dmudw[i][equivH2OFe2[j]] += dmudw[i][j]/2.0;
        if ( (equivH2OFe2[j] != -1) && modelParameters[equivH2OFe2[j]].activeS ) for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls)+equivH2OFe2[j]] += dmudw[i][(nls*(nls-1)/2 + nls)+j]/2.0;
      }
      if ( (nH2O != -1) && (nMgOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
        if ( (equivH2OMg[j] != -1) && modelParameters[equivH2OMg[j]].activeH ) for (i=0; i<nlc; i++) dmudw[i][equivH2OMg[j]] += dmudw[i][j]/2.0;
        if ( (equivH2OMg[j] != -1) && modelParameters[equivH2OMg[j]].activeS ) for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls)+equivH2OMg[j]] += dmudw[i][(nls*(nls-1)/2 + nls)+j]/2.0;
      }
      if ( (nH2O != -1) && (nCaOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
        if ( (equivH2OCa[j] != -1) && modelParameters[equivH2OCa[j]].activeH ) for (i=0; i<nlc; i++) dmudw[i][equivH2OCa[j]] += dmudw[i][j]/2.0;
        if ( (equivH2OCa[j] != -1) && modelParameters[equivH2OCa[j]].activeS ) for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls)+equivH2OCa[j]] += dmudw[i][(nls*(nls-1)/2 + nls)+j]/2.0;
      }
      if ( (nH2O != -1) && (nNaOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
        if ( (equivH2ONa[j] != -1) && modelParameters[equivH2ONa[j]].activeH ) for (i=0; i<nlc; i++) dmudw[i][equivH2ONa[j]] += dmudw[i][j]/2.0;
        if ( (equivH2ONa[j] != -1) && modelParameters[equivH2ONa[j]].activeS ) for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls)+equivH2ONa[j]] += dmudw[i][(nls*(nls-1)/2 + nls)+j]/2.0;
      }
      if ( (nH2O != -1) && (nKOH != -1) ) for (j=0; j<(nls*(nls-1)/2+nls); j++) {
        if ( (equivH2OK[j] != -1) && modelParameters[equivH2OK[j]].activeH ) for (i=0; i<nlc; i++) dmudw[i][equivH2OK[j]] += dmudw[i][j]/2.0;
        if ( (equivH2OK[j] != -1) && modelParameters[equivH2OK[j]].activeS ) for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls)+equivH2OK[j]] += dmudw[i][(nls*(nls-1)/2 + nls)+j]/2.0;
      }
#endif /* STOLPER_WATER */
    }

#ifdef USE_MPI
    if (VERBOSE_DEBUG_MPI) printf("MPI:calculateResidualPack[preclb_slave.c at line %d]--> ...about to call testLiq()...\n", __LINE__);
#endif
  
    /* Test if liquid calculation succeeded - if so, make solid residuals */ 
    if(localResidualOutput->flag) { /* EOS and Ordering state convergence verified */
      int nSol = localResidualDataInput->nSol;
      
#ifdef USE_MPI
      if (VERBOSE_DEBUG_MPI) printf("MPI:calculateResidualPack[preclb_slave.c at line %d]--> ...valid return from testLiq()...\n", __LINE__);
#endif

      if (nSol > 0) for (j=0; j<nSol; j++) {
        int    sID     = (localResidualDataInput->cIndex)[j];  /* solid phase/component index number                            */
	int    isEqual = (localResidualDataInput->isEqual)[j]; /* TRUE if equality constraint, FALSE if phase absent constraint */
	double *r      = localResidualOutput->residuals;
	double *dr     = localResidualOutput->dr; 
	int k, l=0;

#ifdef USE_MPI
        if (VERBOSE_DEBUG_MPI) printf("MPI:calculateResidualPack[preclb_slave.c at line %d]--> ...in nSol loop (j = %d)...\n", __LINE__, j);
#endif
    
        r[j] = (localResidualDataInput->depenG)[j];
	for (k=0; k<nParam; k++) dr[j*nParam +k] = 0.0;
	if (sID == nDensity) {
	  static double *xLiq = NULL;
	  double vSoln, mass, rhoMAX=-1.0, rhoMIN=-1.0, rho, rhoREF=-1.0, drhodv, dfdrho=1.0;
	  const double PENALTY       =  2.0;
	  const double DENOM_PENALTY = 10.0;
	  if (xLiq == NULL) xLiq = (double *) malloc((size_t) nlc*sizeof(double));
	  
	  if      (r[j] > 2000.0) rhoMIN = r[j] - 2000.0; /* This is a minimum condition   */
	  else if (r[j] > 1000.0) rhoMAX = r[j] - 1000.0; /* This is a maximum condition   */
	  else                    rhoREF = r[j];          /* This is an equality condition */
	  
	  vmixLiq (FIRST | ELEVENTH, t, p, rLiq, &vSoln, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, dsdw);
	  conLiq (THIRD, FOURTH, t, p, NULL, NULL, rLiq, xLiq, NULL, NULL, NULL);
	  for (k=0, mass=0.0; k<nlc; k++) for (l=0; l<nc; l++) mass += xLiq[k]*(liquid[k].liqToOx[l])*bulkSystem[l].mw;
	  rho = (vSoln != 0.0) ? mass/(10.0*vSoln) : 0.0;
	  drhodv = ((vSoln != 0.0) ? -mass/(10.0*vSoln*vSoln) : 0.0);
	  
	  if        (rhoMAX > 0.0) { r[j]   = pow(exp(-(rhoMAX-rho)), PENALTY) - 1.0;
	                             dfdrho = PENALTY*pow(exp(-(rhoMAX-rho)), (double) (PENALTY-1.0))*exp(-(rhoMAX-rho));
				     /* printf("MAX: LEPRnum,t,p,rho,rhoMAX,r %10d %8.2f %8.4f %6.2f %6.2f %13.6g\n", LEPRnum, t-273.15, p/10000.0, rho, rhoMAX, r[j]); */
	  } else if (rhoMIN > 0.0) { r[j]   = pow(exp(-(rho-rhoMIN)), PENALTY) - 1.0;
	                             dfdrho = -PENALTY*pow(exp(-(rho-rhoMIN)), (double) (PENALTY-1.0))*exp(-(rho-rhoMIN));
				     /* printf("MIN: LEPRnum,t,p,rho,rhoMIN,r %10d %8.2f %8.4f %6.2f %6.2f %13.6g\n", LEPRnum, t-273.15, p/10000.0, rho, rhoMIN, r[j]); */
	  } else                   { r[j]   = pow(exp(-(rhoREF-rho)), PENALTY) + pow(exp(-(rho-rhoREF)), PENALTY) - 2.0;
	                             dfdrho =  PENALTY*pow(exp(-(rhoREF-rho)), (double) (PENALTY-1.0))*exp(-(rhoREF-rho))
				              -PENALTY*pow(exp(-(rho-rhoREF)), (double) (PENALTY-1.0))*exp(-(rho-rhoREF));
				     /* printf("   : LEPRnum,t,p,rho,rhoREF,r %10d %8.2f %8.4f %6.2f %6.2f %13.6g\n", LEPRnum, t-273.15, p/10000.0, rho, rhoREF, r[j]); */
	  }
	  r[j] += DENOM_PENALTY*exp(-DENOM_PENALTY*denom);

          for (k=0,l=0; k<(nls*(nls-1)/2 + nls); k++) {
            if (modelParameters[k].activeH && !modelParameters[k].activeF)
	        			    dr[j*nParam+(l++)] += dfdrho*drhodv*dsdw[			       k]*SCALE;
            if (modelParameters[k].activeS) dr[j*nParam+(l++)] += dfdrho*drhodv*dsdw[  (nls*(nls-1)/2 + nls) + k];
            if (modelParameters[k].activeV) dr[j*nParam+(l++)] += dfdrho*drhodv*dsdw[2*(nls*(nls-1)/2 + nls) + k];
          }

	  for (k=nls*(nls-1)/2 + nls; k<(nls*(nls-1)/2 + nls + npc); k++) {
	    if (modelParameters[k].activeH && !modelParameters[k].activeF) l++;
	    if (modelParameters[k].activeS)                                l++;
	    if (modelParameters[k].activeV)                                l++;
	  }

	  /* Fill in remaining derivatives using finite differences */
#ifdef BUILD_MGO_SIO2_VERSION
          for (k=0; k<nc; k++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
          for (k=0; k<nc; k++) {
#else
          for (k=0; k<(nc+1); k++) {
#endif
	    if (eosModelParameters[k].activeKp || eosModelParameters[k].activeKpp || eosModelParameters[k].activeKppp) {
	      double v0	   = bulkSystem[k].gk_v;
     	      double alpha = (v0 != 0.0) ? bulkSystem[k].gk_dvdt/v0 : 0.0;
     	      double c	 = bulkSystem[k].gk_c;
     	      double cp	 = bulkSystem[k].gk_cp;
     	      double mw	 = bulkSystem[k].mw;
     	      double v1	 = ((mw != 0.0) && (c != 0.0) && (cp != 0.0)) ? -v0*v0*(1000.0/(mw*c*c) + 1673.15*alpha*alpha/(cp)) : 0.0;
     	      double K	 = (v1 != 0.0) ? -v0/v1 : 0.0;
    	      double KpR   = eosModelParameters[k].Kp;
    	      double KppR  = eosModelParameters[k].Kpp;
    	      double KpppR = eosModelParameters[k].Kppp;
	  
              if (eosModelParameters[k].activeKp) {
	        double vTemp, deriv, denomTemp, v1Temp, v2Temp, v3Temp, v4Temp, aTemp, bTemp, denomDeriv;
	        double v2   = eosModelParameters[k].v2;
                double v3   = eosModelParameters[k].v3;
                double v4   = eosModelParameters[k].v4;
                double Kp   = KpR + ((KpR != 0.0) ? fabs(KpR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON));
	        double Kpp  = KppR;
	        double Kppp = KpppR;
     	        eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	        eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	        eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
		denomTemp = retLiqEosParam (rLiq, t, p, &v1Temp, &v2Temp, &v3Temp, &v4Temp, &aTemp, &bTemp);
	     	vmixLiq (FIRST, t, p, rLiq, &vTemp, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	     	eosModelParameters[k].v2 = v2;
		eosModelParameters[k].v3 = v3;
                eosModelParameters[k].v4 = v4;
	     	deriv = (((vTemp != 0.0) ? mass/(10.0*vTemp) : 0.0) - ((vSoln != 0.0) ? mass/(10.0*vSoln) : 0.0))/(Kp-KpR);
		denomDeriv = (denomTemp-denom)/(Kp-KpR);
	     	dr[j*nParam+(l++)] += dfdrho*deriv - DENOM_PENALTY*DENOM_PENALTY*exp(-DENOM_PENALTY*denom)*denomDeriv;
	      }
              if (eosModelParameters[k].activeKpp) {
	        double vTemp, deriv, denomTemp, v1Temp, v2Temp, v3Temp, v4Temp, aTemp, bTemp, denomDeriv;
	        double v2   = eosModelParameters[k].v2;
                double v3   = eosModelParameters[k].v3;
                double v4   = eosModelParameters[k].v4;
                double Kp   = KpR;
	        double Kpp  = KppR + ((KppR != 0.0) ? fabs(KppR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)/10000.0);
	        double Kppp = KpppR;
     	        eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	        eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	        eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
		denomTemp = retLiqEosParam (rLiq, t, p, &v1Temp, &v2Temp, &v3Temp, &v4Temp, &aTemp, &bTemp);
	     	vmixLiq (FIRST, t, p, rLiq, &vTemp, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	     	eosModelParameters[k].v2 = v2;
		eosModelParameters[k].v3 = v3;
                eosModelParameters[k].v4 = v4;
	     	deriv = (((vTemp != 0.0) ? mass/(10.0*vTemp) : 0.0) - ((vSoln != 0.0) ? mass/(10.0*vSoln) : 0.0))/(Kpp-KppR);
		denomDeriv = (denomTemp-denom)/(Kpp-KppR);
	     	dr[j*nParam+(l++)] += dfdrho*deriv - DENOM_PENALTY*DENOM_PENALTY*exp(-DENOM_PENALTY*denom)*denomDeriv;
	      }
              if (eosModelParameters[k].activeKppp) {
	        double vTemp, deriv, denomTemp, v1Temp, v2Temp, v3Temp, v4Temp, aTemp, bTemp, denomDeriv;
	        double v2   = eosModelParameters[k].v2;
                double v3   = eosModelParameters[k].v3;
                double v4   = eosModelParameters[k].v4;
                double Kp   = KpR;
	        double Kpp  = KppR;
	        double Kppp = KpppR + ((KpppR != 0.0) ? fabs(KpppR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)/10000.0/10000.0);
     	        eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	        eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	        eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
		denomTemp = retLiqEosParam (rLiq, t, p, &v1Temp, &v2Temp, &v3Temp, &v4Temp, &aTemp, &bTemp);
	     	vmixLiq (FIRST, t, p, rLiq, &vTemp, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	     	eosModelParameters[k].v2 = v2;
		eosModelParameters[k].v3 = v3;
                eosModelParameters[k].v4 = v4;
	     	deriv = (((vTemp != 0.0) ? mass/(10.0*vTemp) : 0.0) - ((vSoln != 0.0) ? mass/(10.0*vSoln) : 0.0))/(Kppp-KpppR);
		denomDeriv = (denomTemp-denom)/(Kppp-KpppR);
	     	dr[j*nParam+(l++)] += dfdrho*deriv - DENOM_PENALTY*DENOM_PENALTY*exp(-DENOM_PENALTY*denom)*denomDeriv;
	      }
	    } /* end test if Kp, Kpp, Kppp parameters are active */
	  } /* end loop on oxides */
	  
	} else if (sID == nEntropy) {
	  double sSoln;
	  smixLiq (FIRST | FOURTH, t, p, rLiq, &sSoln, NULL, NULL, dsdw);
	  r[j] -= sSoln;
	  
          for (k=0,l=0; k<(nls*(nls-1)/2 + nls); k++) {
            if (modelParameters[k].activeH && !modelParameters[k].activeF)
	    				    dr[j*nParam+(l++)] -= dsdw[ 			 k]*SCALE;
            if (modelParameters[k].activeS) dr[j*nParam+(l++)] -= dsdw[  (nls*(nls-1)/2 + nls) + k];
            if (modelParameters[k].activeV) dr[j*nParam+(l++)] -= dsdw[2*(nls*(nls-1)/2 + nls) + k];
          }
	  
	  for (k=nls*(nls-1)/2 + nls; k<(nls*(nls-1)/2 + nls + npc); k++) {
	    if (modelParameters[k].activeH && !modelParameters[k].activeF) l++;
	    if (modelParameters[k].activeS)                                l++;
	    if (modelParameters[k].activeV)                                l++;
	  }

	  /* Fill in remaining derivatives using finite differences */
#ifdef BUILD_MGO_SIO2_VERSION
          for (k=0; k<nc; k++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
          for (k=0; k<nc; k++) {
#else
          for (k=0; k<(nc+1); k++) {
#endif
	    if (eosModelParameters[k].activeKp || eosModelParameters[k].activeKpp || eosModelParameters[k].activeKppp) {
	      double v0	   = bulkSystem[k].gk_v;
     	      double alpha = (v0 != 0.0) ? bulkSystem[k].gk_dvdt/v0 : 0.0;
     	      double c	 = bulkSystem[k].gk_c;
     	      double cp	 = bulkSystem[k].gk_cp;
     	      double mw	 = bulkSystem[k].mw;
     	      double v1	 = ((mw != 0.0) && (c != 0.0) && (cp != 0.0)) ? -v0*v0*(1000.0/(mw*c*c) + 1673.15*alpha*alpha/(cp)) : 0.0;
     	      double K	 = (v1 != 0.0) ? -v0/v1 : 0.0;
    	      double KpR   = eosModelParameters[k].Kp;
    	      double KppR  = eosModelParameters[k].Kpp;
    	      double KpppR = eosModelParameters[k].Kppp;
	  
	      if (eosModelParameters[k].activeKp) {
	        double sTemp, deriv;
	        double v2   = eosModelParameters[k].v2;
                double v3   = eosModelParameters[k].v3;
                double v4   = eosModelParameters[k].v4;
                double Kp   = KpR + ((KpR != 0.0) ? fabs(KpR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON));
	        double Kpp  = KppR;
	        double Kppp = KpppR;
     	        eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	        eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	        eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
	     	smixLiq (FIRST, t, p, rLiq, &sTemp, NULL, NULL, NULL);
	     	eosModelParameters[k].v2 = v2;
		eosModelParameters[k].v3 = v3;
                eosModelParameters[k].v4 = v4;
	     	deriv = (sTemp-sSoln)/(Kp-KpR);
	     	dr[j*nParam+(l++)] -= deriv;
	      }
	      if (eosModelParameters[k].activeKpp) {
	        double sTemp, deriv;
	        double v2   = eosModelParameters[k].v2;
                double v3   = eosModelParameters[k].v3;
                double v4   = eosModelParameters[k].v4;
                double Kp   = KpR;
	        double Kpp  = KppR + ((KppR != 0.0) ? fabs(KppR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)/10000.0);
	        double Kppp = KpppR;
     	        eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	        eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	        eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
	     	smixLiq (FIRST, t, p, rLiq, &sTemp, NULL, NULL, NULL);
	     	eosModelParameters[k].v2 = v2;
		eosModelParameters[k].v3 = v3;
                eosModelParameters[k].v4 = v4;
	     	deriv = (sTemp-sSoln)/(Kpp-KppR);
	     	dr[j*nParam+(l++)] -= deriv;
	      }
	      if (eosModelParameters[k].activeKppp) {
	        double sTemp, deriv;
	        double v2   = eosModelParameters[k].v2;
                double v3   = eosModelParameters[k].v3;
                double v4   = eosModelParameters[k].v4;
                double Kp   = KpR;
	        double Kpp  = KppR;
	        double Kppp = KpppR + ((KpppR != 0.0) ? fabs(KpppR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)/10000.0/10000.0);
     	        eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	        eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	        eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
	     	smixLiq (FIRST, t, p, rLiq, &sTemp, NULL, NULL, NULL);
	     	eosModelParameters[k].v2 = v2;
		eosModelParameters[k].v3 = v3;
                eosModelParameters[k].v4 = v4;
	     	deriv = (sTemp-sSoln)/(Kppp-KpppR);
	     	dr[j*nParam+(l++)] -= deriv;
	      }
	    } /* end test on active Kp, Kpp, Kppp */
	  } /* end loop on oxides */
	  
	} else if (sID == nEnthalpy) {
	  double hSoln;
	  hmixLiq (FIRST | SECOND, t, p, rLiq, &hSoln, dsdw);
	  r[j] -= hSoln/SCALE;
	  
          for (k=0,l=0; k<(nls*(nls-1)/2 + nls); k++) {
              if (modelParameters[k].activeH && !modelParameters[k].activeF)
	                                      dr[j*nParam+(l++)] -= dsdw[			   k]*SCALE/SCALE;
              if (modelParameters[k].activeS) dr[j*nParam+(l++)] -= dsdw[  (nls*(nls-1)/2 + nls) + k]/SCALE;
              if (modelParameters[k].activeV) dr[j*nParam+(l++)] -= dsdw[2*(nls*(nls-1)/2 + nls) + k]/SCALE;
          }
	  
	  for (k=nls*(nls-1)/2 + nls; k<(nls*(nls-1)/2 + nls + npc); k++) {
	    if (modelParameters[k].activeH && !modelParameters[k].activeF) l++;
	    if (modelParameters[k].activeS)                                l++;
	    if (modelParameters[k].activeV)                                l++;
	  }

	  /* Fill in remaining derivatives using finite differences */
#ifdef BUILD_MGO_SIO2_VERSION
	  for (k=0; k<nc; k++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
	  for (k=0; k<nc; k++) {
#else
	  for (k=0; k<(nc+1); k++) {
#endif
	    if (eosModelParameters[k].activeKp || eosModelParameters[k].activeKpp || eosModelParameters[k].activeKppp) {
	      double v0	   = bulkSystem[k].gk_v;
     	      double alpha = (v0 != 0.0) ? bulkSystem[k].gk_dvdt/v0 : 0.0;
     	      double c	 = bulkSystem[k].gk_c;
     	      double cp	 = bulkSystem[k].gk_cp;
     	      double mw	 = bulkSystem[k].mw;
     	      double v1	 = ((mw != 0.0) && (c != 0.0) && (cp != 0.0)) ? -v0*v0*(1000.0/(mw*c*c) + 1673.15*alpha*alpha/(cp)) : 0.0;
     	      double K	 = (v1 != 0.0) ? -v0/v1 : 0.0;
    	      double KpR   = eosModelParameters[k].Kp;
    	      double KppR  = eosModelParameters[k].Kpp;
    	      double KpppR = eosModelParameters[k].Kppp;
	  
	      if (eosModelParameters[k].activeKp) {
	        double hTemp, deriv;
	        double v2   = eosModelParameters[k].v2;
                double v3   = eosModelParameters[k].v3;
                double v4   = eosModelParameters[k].v4;
                double Kp   = KpR + ((KpR != 0.0) ? fabs(KpR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON));
	        double Kpp  = KppR;
	        double Kppp = KpppR;
     	        eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	        eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	        eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
	     	hmixLiq (FIRST, t, p, rLiq, &hTemp, NULL);
	     	eosModelParameters[k].v2 = v2;
		eosModelParameters[k].v3 = v3;
                eosModelParameters[k].v4 = v4;
	     	deriv = (hTemp-hSoln)/(Kp-KpR);
	     	dr[j*nParam+(l++)] -= deriv;
	      }
	      if (eosModelParameters[k].activeKpp) {
	        double hTemp, deriv;
	        double v2   = eosModelParameters[k].v2;
                double v3   = eosModelParameters[k].v3;
                double v4   = eosModelParameters[k].v4;
                double Kp   = KpR;
	        double Kpp  = KppR + ((KppR != 0.0) ? fabs(KppR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)/10000.0);
	        double Kppp = KpppR;
     	        eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	        eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	        eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
	     	hmixLiq (FIRST, t, p, rLiq, &hTemp, NULL);
	     	eosModelParameters[k].v2 = v2;
		eosModelParameters[k].v3 = v3;
                eosModelParameters[k].v4 = v4;
	     	deriv = (hTemp-hSoln)/(Kpp-KppR);
	     	dr[j*nParam+(l++)] -= deriv;
	      }
	      if (eosModelParameters[k].activeKppp) {
	        double hTemp, deriv;
	        double v2   = eosModelParameters[k].v2;
                double v3   = eosModelParameters[k].v3;
                double v4   = eosModelParameters[k].v4;
                double Kp   = KpR;
	        double Kpp  = KppR;
	        double Kppp = KpppR + ((KpppR != 0.0) ? fabs(KpppR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)/10000.0/10000.0);
     	        eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	        eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	        eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
	     	hmixLiq (FIRST, t, p, rLiq, &hTemp, NULL);
	     	eosModelParameters[k].v2 = v2;
		eosModelParameters[k].v3 = v3;
                eosModelParameters[k].v4 = v4;
	     	deriv = (hTemp-hSoln)/(Kppp-KpppR);
	     	dr[j*nParam+(l++)] -= deriv;
	      }
	    } /* end test if Kp, Kpp, Kppp active */
	  } /* end loop on oxides */
	  
	} else if (sID == nAdditionalLiquid && !isEqual) {
	  static int     nSA, nfcnevSA, ierSA, naccSA, nobdsSA, *nacpSA,
	                 maxSA = 0, 
			 nsSA = 20, 
			 ntSA = 5, 
			 iseed1SA = 1, 
			 iseed2SA = 2, 
			 maxevlSA = 100000, 
			 iprintSA = 0;
          const int     nepsSA = 4;
	  static double     tSA, foptSA, *lbSA, *ubSA, *xSA, *xoptSA, *cSA, 
	                    *vmSA, fstarSA[4], *xpSA,
	                    epsSA = 1.0e-6, 
			    rtSA  = 0.1;
	  char *liqFormula;
	  if (xLiqSAref == NULL) {
	    xLiqSAref    = (double *)     malloc((size_t)     nlc*sizeof(double));
	    rLiqSAref    = (double *)     malloc((size_t) (nlc-1)*sizeof(double));
	    dgdrLiqSAref = (double *)     malloc((size_t) (nlc-1)*sizeof(double));
	    lbSA         = (double     *) malloc((size_t)     nlc*sizeof(double    ));
	    ubSA         = (double     *) malloc((size_t)     nlc*sizeof(double    ));
	    xSA          = (double     *) malloc((size_t)     nlc*sizeof(double    ));
	    xoptSA       = (double     *) malloc((size_t)     nlc*sizeof(double    ));
	    cSA          = (double     *) malloc((size_t)     nlc*sizeof(double    ));
	    vmSA         = (double     *) malloc((size_t)     nlc*sizeof(double    ));
	    xpSA         = (double     *) malloc((size_t)     nlc*sizeof(double    ));
	    nacpSA       = (int     *)    malloc((size_t)     nlc*sizeof(int    ));
	  }
	  for (k=0; k<(nlc-1); k++) rLiqSAref[k] = rLiq[k];
	  conLiq(THIRD, FOURTH, t, p, NULL, NULL, rLiqSAref, xLiqSAref, NULL, NULL, NULL);
	  for (k=0, nSA=0; k<nlc; k++) {
	    if (xLiqSAref[k] < sqrt(DBL_EPSILON)) {
	      xLiqSAref[k] = 0.0;
	    } else {
	      xSA[nSA] = xLiqSAref[k]; 
	      lbSA[nSA] = 0.001; 
	      ubSA[nSA] = 0.999; 
	      cSA[nSA]  = 2.0;
	      vmSA[nSA] = 1.0;
	      nSA++;
	    }
	  }
	  tSA = 5.0;
          setModeToMixingLiq(TRUE);
          gmixLiq(FIRST | SECOND, t, p, rLiq, &gmixLiqSAref, dgdrLiqSAref, NULL);
	  tSAref = t;
	  pSAref = p;
	  dispLiq(FIRST, t, p, rLiq, &liqFormula);
	  printf("Entering sa %s", liqFormula);
	  sa_(&nSA, xSA, &maxSA, &rtSA, &epsSA, &nsSA, &ntSA, &nepsSA, &maxevlSA, 
	    lbSA, ubSA, cSA, &iprintSA, &iseed1SA, &iseed2SA, &tSA, vmSA, xoptSA, &foptSA, 
	    &naccSA, &nfcnevSA, &nobdsSA, &ierSA, fstarSA, xpSA, nacpSA);
	  dispLiq(FIRST, t, p, rLiqTmp, &liqFormula);
	  printf(" fopt = %g and %s\n", foptSA, liqFormula);
          setModeToMixingLiq(FALSE);
	  
	  if (foptSA < -sqrt(DBL_EPSILON)) {
	    static double *dgdwTmp, **d2gdrdwTmp;
	    if (dgdwTmp == NULL) {
	      dgdwTmp    = (double  *) malloc((size_t) 3*(nls*(nls-1)/2 + nls)*sizeof(double));
	      d2gdrdwTmp = (double **) malloc((size_t)                 (nlc-1)*sizeof(double *));
	      for (i=0; i<(nlc-1); i++) d2gdrdwTmp[i] = (double  *) malloc((size_t) 3*(nls*(nls-1)/2 + nls)*sizeof(double));
            }
	    r[j] = foptSA/SCALE;
	    for (i=0; i<nParam; i++) dr[j*nParam+i] = 0.0;
	    actLiq (FIFTH | SEVENTH, t, p, rLiq, NULL, dgdwTmp, NULL, d2gdrdwTmp);
            for (k=0,l=0; k<(nls*(nls-1)/2 + nls); k++) {
              if (modelParameters[k].activeH && !modelParameters[k].activeF) {
	        for (i=0; i<(nlc-1); i++) 
		  if (xLiqSAref[i+1] > 0.0) dgdwTmp[k] += d2gdrdwTmp[i][k]*(rLiqTmp[i]-rLiq[i]);
                dr[j*nParam+(l++)] -= dgdwTmp[k]*SCALE/SCALE;
              }
              if (modelParameters[k].activeS) {
	        for (i=0; i<(nlc-1); i++) 
		  if (xLiqSAref[i+1] > 0.0) dgdwTmp[(nls*(nls-1)/2+nls)+k] += d2gdrdwTmp[i][(nls*(nls-1)/2+nls)+k]*(rLiqTmp[i]-rLiq[i]);
	        dr[j*nParam+(l++)] -= dgdwTmp[(nls*(nls-1)/2+nls)+k]/SCALE;
              }
              if (modelParameters[k].activeV) {
	        for (i=0; i<(nlc-1); i++) 
		  if (xLiqSAref[i+1] > 0.0) dgdwTmp[2*(nls*(nls-1)/2+nls)+k] += d2gdrdwTmp[i][2*(nls*(nls-1)/2+nls)+k]*(rLiqTmp[i]-rLiq[i]);
	        dr[j*nParam+(l++)] -= dgdwTmp[2*(nls*(nls-1)/2+nls)+k]/SCALE;
              }
            }
	    
	    actLiq (FIFTH, t, p, rLiqTmp, NULL, dgdwTmp, NULL, NULL);
            for (k=0,l=0; k<(nls*(nls-1)/2 + nls); k++) {
              if (modelParameters[k].activeH && !modelParameters[k].activeF) dr[j*nParam+(l++)] += dgdwTmp[                      k]*SCALE/SCALE;
              if (modelParameters[k].activeS)                                dr[j*nParam+(l++)] += dgdwTmp[  (nls*(nls-1)/2+nls)+k]/SCALE;
              if (modelParameters[k].activeV)                                dr[j*nParam+(l++)] += dgdwTmp[2*(nls*(nls-1)/2+nls)+k]/SCALE;
            }

	  } else {
	    r[j] = 0.0;
	    for (i=0; i<nParam; i++) dr[j*nParam+i] = 0.0;
	  }

	} else if (sID == nAdditionalLiquid && isEqual) {
	  double *rTmp = (localResidualDataInput->rSol)[j];
	  int    iComp = (localResidualDataInput->isEqual)[j] - TRUE;
	  actLiq (SECOND | FOURTH, t, p, rTmp, NULL, muTmp, NULL, dmudwTmp);
	  if(testLiq (SEVENTH, t, p, 0, 0, NULL, NULL, NULL, NULL)) {
            r[j] += (mu[iComp]-muTmp[iComp])/SCALE;
            for (k=0,l=0; k<(nls*(nls-1)/2 + nls); k++) {
              if (modelParameters[k].activeH && !modelParameters[k].activeF)
	        			      dr[j*nParam+(l++)] += ( dmudw[   iComp][			        k]
					                             -dmudwTmp[iComp][			        k])*SCALE/SCALE;
              if (modelParameters[k].activeS) dr[j*nParam+(l++)] += ( dmudw[   iComp][  (nls*(nls-1)/2 + nls) + k]
	                                                             -dmudwTmp[iComp][  (nls*(nls-1)/2 + nls) + k])/SCALE;
              if (modelParameters[k].activeV) dr[j*nParam+(l++)] += ( dmudw[   iComp][2*(nls*(nls-1)/2 + nls) + k]
	                                                             -dmudwTmp[iComp][2*(nls*(nls-1)/2 + nls) + k])/SCALE;
            }
	  
	    for (k=nls*(nls-1)/2 + nls; k<(nls*(nls-1)/2 + nls + npc); k++) {
	      if (modelParameters[k].activeH && !modelParameters[k].activeF) l++;
	      if (modelParameters[k].activeS)                                l++;
	      if (modelParameters[k].activeV)                                l++;
	    }

	    /* Fill in remaining derivatives using finite differences */ 
#ifdef BUILD_MGO_SIO2_VERSION
	    for (k=0; k<nc; k++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
	    for (k=0; k<nc; k++) {
#else
	    for (k=0; k<(nc+1); k++) {
#endif
	      if (eosModelParameters[k].activeKp || eosModelParameters[k].activeKpp || eosModelParameters[k].activeKppp) {
	     	double v0    = bulkSystem[k].gk_v;
     	     	double alpha = (v0 != 0.0) ? bulkSystem[k].gk_dvdt/v0 : 0.0;
     	     	double c   = bulkSystem[k].gk_c;
     	     	double cp  = bulkSystem[k].gk_cp;
     	     	double mw  = bulkSystem[k].mw;
     	     	double v1  = ((mw != 0.0) && (c != 0.0) && (cp != 0.0)) ? -v0*v0*(1000.0/(mw*c*c) + 1673.15*alpha*alpha/(cp)) : 0.0;
     	     	double K   = (v1 != 0.0) ? -v0/v1 : 0.0;
    	     	double KpR   = eosModelParameters[k].Kp;
    	     	double KppR  = eosModelParameters[k].Kpp;
    	     	double KpppR = eosModelParameters[k].Kppp;
	  
	    
	        if (eosModelParameters[k].activeKp) {
	          double deriv;
	          double v2   = eosModelParameters[k].v2;
                  double v3   = eosModelParameters[k].v3;
                  double v4   = eosModelParameters[k].v4;
                  double Kp   = KpR + ((KpR != 0.0) ? fabs(KpR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON));
	          double Kpp  = KppR;
	          double Kppp = KpppR;
     	          eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	          eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	          eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
	          actLiq (SECOND, t, p, rTmp, NULL, muTmpTmp, NULL, NULL);
	     	  eosModelParameters[k].v2 = v2;
		  eosModelParameters[k].v3 = v3;
                  eosModelParameters[k].v4 = v4;
	          deriv = (muTmpTmp[iComp]-muTmp[iComp])/(Kp-KpR);
	          dr[j*nParam+(l++)] += (dmudw[iComp][3*(nls*(nls-1)/2 + nls) + 3*k] - deriv)/SCALE;
	        }
	        if (eosModelParameters[k].activeKpp) {
	          double deriv;
	          double v2   = eosModelParameters[k].v2;
                  double v3   = eosModelParameters[k].v3;
                  double v4   = eosModelParameters[k].v4;
                  double Kp   = KpR;
	          double Kpp  = KppR + ((KppR != 0.0) ? fabs(KppR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)/10000.0);
	          double Kppp = KpppR;
     	          eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	          eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	          eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
	          actLiq (SECOND, t, p, rTmp, NULL, muTmpTmp, NULL, NULL);
	     	  eosModelParameters[k].v2 = v2;
		  eosModelParameters[k].v3 = v3;
                  eosModelParameters[k].v4 = v4;
	          deriv = (muTmpTmp[iComp]-muTmp[iComp])/(Kpp-KppR);
	          dr[j*nParam+(l++)] += (dmudw[iComp][3*(nls*(nls-1)/2 + nls) + 3*k + 1] - deriv)/SCALE;
	        }
	        if (eosModelParameters[k].activeKppp) {
	          double deriv;
	          double v2   = eosModelParameters[k].v2;
                  double v3   = eosModelParameters[k].v3;
                  double v4   = eosModelParameters[k].v4;
                  double Kp   = KpR;
	          double Kpp  = KppR;
	          double Kppp = KpppR + ((KpppR != 0.0) ? fabs(KpppR)*sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)/10000.0/10000.0);
     	          eosModelParameters[k].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	          eosModelParameters[k].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	          eosModelParameters[k].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
	          actLiq (SECOND, t, p, rTmp, NULL, muTmpTmp, NULL, NULL);
	     	  eosModelParameters[k].v2 = v2;
		  eosModelParameters[k].v3 = v3;
                  eosModelParameters[k].v4 = v4;
	          deriv = (muTmpTmp[iComp]-muTmp[iComp])/(Kppp-KpppR);
	          dr[j*nParam+(l++)] += (dmudw[iComp][3*(nls*(nls-1)/2 + nls) + 3*k + 2] - deriv)/SCALE;
	        }
	      } /* end test on active Kp, Kpp, Kppp */
	    } /* end loop on oxides */
	  } else localResidualOutput->flag = FALSE;
	  
        } else if (sID < npc) {
	  double delG=0.0, deldGdT=0.0;
	  static double *drTmp;
	  if (useTregression && (drTmp == NULL)) drTmp = (double *) malloc((size_t) nParam*sizeof(double));
	  if (useTregression) {
	    delG    = (localResidualDataInput->depenG)[j];
	    deldGdT = (localResidualDataInput->dependGdT)[j];
	    for (i=0; i<nParam; i++) drTmp[i] = 0.0;
	  }
          for (i=0; i<nlc; i++) if (solids[sID].solToLiq[i] != 0.0) {
	    if (useTregression) {
              delG    -= (solids[sID].solToLiq[i])*mu[i]/SCALE;
	      deldGdT -= (solids[sID].solToLiq[i])*dmudt[i]/SCALE;
	    } else r[j] -= (solids[sID].solToLiq[i])*mu[i]/SCALE;
	    
            for (k=0,l=0; k<(nls*(nls-1)/2 + nls); k++) {
              if (modelParameters[k].activeH && !modelParameters[k].activeF) {
	        if (useTregression) drTmp[          l] -= (solids[sID].solToLiq[i])*d2mudtdw[i][			  k]*SCALE/SCALE;
	                            dr[j*nParam+(l++)] -= (solids[sID].solToLiq[i])*dmudw   [i][			  k]*SCALE/SCALE;
	      }
              if (modelParameters[k].activeS) {
	        if (useTregression) drTmp[          l] -= (solids[sID].solToLiq[i])*d2mudtdw[i][  (nls*(nls-1)/2 + nls) + k]/SCALE;
	                            dr[j*nParam+(l++)] -= (solids[sID].solToLiq[i])*dmudw   [i][  (nls*(nls-1)/2 + nls) + k]/SCALE;
	      }
              if (modelParameters[k].activeV) {
	        if (useTregression) drTmp[          l] -= (solids[sID].solToLiq[i])*d2mudtdw[i][2*(nls*(nls-1)/2 + nls) + k]/SCALE;
	                            dr[j*nParam+(l++)] -= (solids[sID].solToLiq[i])*dmudw   [i][2*(nls*(nls-1)/2 + nls) + k]/SCALE;
	      }
            }
          }
	  
	  if (useTregression) {
	    if (modelParameters[nls*(nls-1)/2+nls+sID].activeH) delG    +=         modelParameters[nls*(nls-1)/2+nls+sID].enthalpy/SCALE;
	    if (modelParameters[nls*(nls-1)/2+nls+sID].activeS) delG    +=      -t*modelParameters[nls*(nls-1)/2+nls+sID].entropy/SCALE;
	    if (modelParameters[nls*(nls-1)/2+nls+sID].activeV) delG    += (p-1.0)*modelParameters[nls*(nls-1)/2+nls+sID].volume/SCALE;
	    if (modelParameters[nls*(nls-1)/2+nls+sID].activeS) deldGdT +=        -modelParameters[nls*(nls-1)/2+nls+sID].entropy/SCALE;
	  } else {
	    if (modelParameters[nls*(nls-1)/2+nls+sID].activeH) r[j] +=         modelParameters[nls*(nls-1)/2+nls+sID].enthalpy/SCALE;
	    if (modelParameters[nls*(nls-1)/2+nls+sID].activeS) r[j] +=      -t*modelParameters[nls*(nls-1)/2+nls+sID].entropy/SCALE;
	    if (modelParameters[nls*(nls-1)/2+nls+sID].activeV) r[j] += (p-1.0)*modelParameters[nls*(nls-1)/2+nls+sID].volume/SCALE;
	  }
	  for (k=nls*(nls-1)/2 + nls; k<(nls*(nls-1)/2 + nls + npc); k++) {
	    if (modelParameters[k].activeH && !modelParameters[k].activeF) dr[j*nParam+(l++)] += (sID == (k - nls*(nls-1)/2 - nls)) ?      1.0*SCALE/SCALE : 0.0;
	    if (modelParameters[k].activeS) {
	      if (useTregression)                                          drTmp[          l] += (sID == (k - nls*(nls-1)/2 - nls)) ?       -1.0/SCALE     : 0.0;
	                                                                   dr[j*nParam+(l++)] += (sID == (k - nls*(nls-1)/2 - nls)) ?       -t/SCALE       : 0.0;
	    }
	    if (modelParameters[k].activeV)                                dr[j*nParam+(l++)] += (sID == (k - nls*(nls-1)/2 - nls)) ?  (p-1.0)/SCALE       : 0.0;
	  }

          for (i=0; i<nlc; i++) if (solids[sID].solToLiq[i] != 0.0) {
	    int m = l;
#ifdef BUILD_MGO_SIO2_VERSION
            for (k=0; k<nc; k++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
            for (k=0; k<nc; k++) {
#else
            for (k=0; k<(nc+1); k++) {
#endif
              if (eosModelParameters[k].activeKp) {
	        if (useTregression) drTmp[          m] -= (solids[sID].solToLiq[i])*d2mudtdw[i][3*(nls*(nls-1)/2 + nls) + 3*k    ]/SCALE;
	                            dr[j*nParam+(m++)] -= (solids[sID].solToLiq[i])*dmudw   [i][3*(nls*(nls-1)/2 + nls) + 3*k    ]/SCALE;
	      }
              if (eosModelParameters[k].activeKpp) {
	        if (useTregression) drTmp[          m] -= (solids[sID].solToLiq[i])*d2mudtdw[i][3*(nls*(nls-1)/2 + nls) + 3*k + 1]/SCALE;
	                            dr[j*nParam+(m++)] -= (solids[sID].solToLiq[i])*dmudw   [i][3*(nls*(nls-1)/2 + nls) + 3*k + 1]/SCALE;
	      }
              if (eosModelParameters[k].activeKppp) {
	        if (useTregression) drTmp[          m] -= (solids[sID].solToLiq[i])*d2mudtdw[i][3*(nls*(nls-1)/2 + nls) + 3*k + 2]/SCALE;
	                            dr[j*nParam+(m++)] -= (solids[sID].solToLiq[i])*dmudw   [i][3*(nls*(nls-1)/2 + nls) + 3*k + 2]/SCALE;
              }
            }
	  }

	  if (useTregression) {
	    r[j] = (deldGdT != 0.0) ? -delG/deldGdT : 0.0;
	    for (i=0; i<nParam; i++) dr[j*nParam+i] = (deldGdT != 0.0) ? -dr[j*nParam+i]/deldGdT + delG*drTmp[i]/(deldGdT*deldGdT) : 0.0;
	  }
	  
	  if (!isEqual && ((!useTregression && (r[j] > 0.0)) || (useTregression && (delG > 0.0)))) {
	    r[j] = 0.0;
	    for (i=0; i<nParam; i++) dr[j*nParam+i] = 0.0;
	  } else if (!useTregression && !isEqual && (r[j] < 0.0)) {
	    r[j] /= solids[sID].nAtoms;
	    for (i=0; i<nParam; i++) dr[j*nParam+i] /= solids[sID].nAtoms;
	  } else if (!useTregression) { 
	    r[j] /= solids[sID].nAtoms;
	    for (i=0; i<nParam; i++) dr[j*nParam+i] /= solids[sID].nAtoms;
	  }
	  
        } else {
	  int eID = extraSolids[sID-npc].index;
	  int kk;
	  double delG=0.0, deldGdT=0.0;
	  static double *drTmp;
	  if (useTregression && (drTmp == NULL)) drTmp = (double *) malloc((size_t) nParam*sizeof(double));
	  if (useTregression) {
	    delG    = (localResidualDataInput->depenG)[j];
	    deldGdT = (localResidualDataInput->dependGdT)[j];
	    for (i=0; i<nParam; i++) drTmp[i] = 0.0;
	  }
          for (i=0; i<nlc; i++) if (extraSolids[sID-npc].solToLiq[i] != 0.0) {
	    if (useTregression) {
	      delG    -= (extraSolids[sID-npc].solToLiq[i])*mu[i]/SCALE;
	      deldGdT -= (extraSolids[sID-npc].solToLiq[i])*dmudt[i]/SCALE;
            } else r[j] -= (extraSolids[sID-npc].solToLiq[i])*mu[i]/SCALE;
	    
            for (k=0,l=0; k<(nls*(nls-1)/2 + nls); k++) {
              if (modelParameters[k].activeH  && !modelParameters[k].activeF) {
	        if (useTregression) drTmp[          l] -= (extraSolids[sID-npc].solToLiq[i])*d2mudtdw[i][			   k]*SCALE/SCALE;
	                            dr[j*nParam+(l++)] -= (extraSolids[sID-npc].solToLiq[i])*dmudw   [i][			   k]*SCALE/SCALE;
	      }
              if (modelParameters[k].activeS) {
	        if (useTregression) drTmp[          l] -= (extraSolids[sID-npc].solToLiq[i])*d2mudtdw[i][  (nls*(nls-1)/2 + nls) + k]/SCALE;
	                            dr[j*nParam+(l++)] -= (extraSolids[sID-npc].solToLiq[i])*dmudw   [i][  (nls*(nls-1)/2 + nls) + k]/SCALE;
	      }
              if (modelParameters[k].activeV) {
	        if (useTregression) drTmp[          l] -= (extraSolids[sID-npc].solToLiq[i])*d2mudtdw[i][2*(nls*(nls-1)/2 + nls) + k]/SCALE;
	                            dr[j*nParam+(l++)] -= (extraSolids[sID-npc].solToLiq[i])*dmudw   [i][2*(nls*(nls-1)/2 + nls) + k]/SCALE;
	      }
            }
	  }

          if (useTregression) {
            for (kk=0; kk<solids[eID].na; kk++) {
	      if (modelParameters[nls*(nls-1)/2+nls+eID+1+kk].activeH) delG    +=         (extraSolids[sID-npc].m)[kk]*modelParameters[nls*(nls-1)/2+nls+eID+1+kk].enthalpy/SCALE;
	      if (modelParameters[nls*(nls-1)/2+nls+eID+1+kk].activeS) delG    +=      -t*(extraSolids[sID-npc].m)[kk]*modelParameters[nls*(nls-1)/2+nls+eID+1+kk].entropy/SCALE;
	      if (modelParameters[nls*(nls-1)/2+nls+eID+1+kk].activeV) delG    += (p-1.0)*(extraSolids[sID-npc].m)[kk]*modelParameters[nls*(nls-1)/2+nls+eID+1+kk].volume/SCALE;
	      if (modelParameters[nls*(nls-1)/2+nls+eID+1+kk].activeS) deldGdT +=        -(extraSolids[sID-npc].m)[kk]*modelParameters[nls*(nls-1)/2+nls+eID+1+kk].entropy/SCALE;
	    }
	  } else {
            for (kk=0; kk<solids[eID].na; kk++) {
	      if (modelParameters[nls*(nls-1)/2+nls+eID+1+kk].activeH) r[j] +=         (extraSolids[sID-npc].m)[kk]*modelParameters[nls*(nls-1)/2+nls+eID+1+kk].enthalpy/SCALE;
	      if (modelParameters[nls*(nls-1)/2+nls+eID+1+kk].activeS) r[j] +=      -t*(extraSolids[sID-npc].m)[kk]*modelParameters[nls*(nls-1)/2+nls+eID+1+kk].entropy/SCALE;
	      if (modelParameters[nls*(nls-1)/2+nls+eID+1+kk].activeV) r[j] += (p-1.0)*(extraSolids[sID-npc].m)[kk]*modelParameters[nls*(nls-1)/2+nls+eID+1+kk].volume/SCALE;
	    }
	  }
	  for (k=nls*(nls-1)/2 + nls; k<(nls*(nls-1)/2 + nls + npc); k++) {
	    if (modelParameters[k].activeH && !modelParameters[k].activeF) {
	      for (kk=0; kk<solids[eID].na; kk++) dr[j*nParam+l] += (eID+1+kk == (k - nls*(nls-1)/2 - nls)) ?    (extraSolids[sID-npc].m)[kk]*SCALE/SCALE : 0.0;
	      l++;
	    }
	    if (modelParameters[k].activeS) {
	      if (useTregression) for (kk=0; kk<solids[eID].na; kk++) drTmp[      l] += (eID+1+kk == (k - nls*(nls-1)/2 - nls)) ?   -(extraSolids[sID-npc].m)[kk]/SCALE       : 0.0;
	                          for (kk=0; kk<solids[eID].na; kk++) dr[j*nParam+l] += (eID+1+kk == (k - nls*(nls-1)/2 - nls)) ? -t*(extraSolids[sID-npc].m)[kk]/SCALE       : 0.0;
	      l++;
	    }
	    if (modelParameters[k].activeV) {
	      for (kk=0; kk<solids[eID].na; kk++) dr[j*nParam+l] += (eID+1+kk == (k - nls*(nls-1)/2 - nls)) ? (p-1.0)*(extraSolids[sID-npc].m)[kk]/SCALE  : 0.0;
	      l++;
	    }
	  }

          for (i=0; i<nlc; i++) if (extraSolids[sID-npc].solToLiq[i] != 0.0) {
	    int m = l;
#ifdef BUILD_MGO_SIO2_VERSION
            for (k=0; k<nc; k++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
            for (k=0; k<nc; k++) {
#else
            for (k=0; k<(nc+1); k++) {
#endif
              if (eosModelParameters[k].activeKp) {
	        if (useTregression) drTmp[          m] -= (extraSolids[sID-npc].solToLiq[i])*d2mudtdw[i][3*(nls*(nls-1)/2 + nls) + 3*k    ]/SCALE;
	                            dr[j*nParam+(m++)] -= (extraSolids[sID-npc].solToLiq[i])*dmudw   [i][3*(nls*(nls-1)/2 + nls) + 3*k    ]/SCALE;
	      }
              if (eosModelParameters[k].activeKpp) {
	        if (useTregression) drTmp[          m] -= (extraSolids[sID-npc].solToLiq[i])*d2mudtdw[i][3*(nls*(nls-1)/2 + nls) + 3*k + 1]/SCALE;
	                            dr[j*nParam+(m++)] -= (extraSolids[sID-npc].solToLiq[i])*dmudw   [i][3*(nls*(nls-1)/2 + nls) + 3*k + 1]/SCALE;
	      }
              if (eosModelParameters[k].activeKppp) {
	        if (useTregression) dr[             m] -= (extraSolids[sID-npc].solToLiq[i])*d2mudtdw[i][3*(nls*(nls-1)/2 + nls) + 3*k + 2]/SCALE;
	                            dr[j*nParam+(m++)] -= (extraSolids[sID-npc].solToLiq[i])*dmudw   [i][3*(nls*(nls-1)/2 + nls) + 3*k + 2]/SCALE;
	      }
            }
          }
	  
	  if (useTregression) {
	    r[j] = (deldGdT != 0.0) ? -delG/deldGdT : 0.0;
	    for (i=0; i<nParam; i++) dr[j*nParam+i] = (deldGdT != 0.0) ? -dr[j*nParam+i]/deldGdT + delG*drTmp[i]/(deldGdT*deldGdT) : 0.0;
	  } else {
	    r[j] /= extraSolids[sID-npc].nAtoms;
	    for (i=0; i<nParam; i++) dr[j*nParam+i] /= extraSolids[sID-npc].nAtoms;
	  }
	  
        }
      }
    }

  }

#ifdef USE_MPI
  if (VERBOSE_DEBUG_MPI) printf("MPI:calculateResidualPack[preclb_slave.c at line %d]--> Exiting routine...\n", __LINE__);
#endif
  
}

#ifdef USE_MPI
#include <mpi.h>

#ifdef USE_LAM_XLED
#include <ledreq.h>
#endif /* USE_LAM_XLED */

#include "res_struct_data.h"

#include "status.h"
MeltsStatus meltsStatus;

int calculationMode = MODE_xMELTS;
int quad_tol_modifier = 1;
int useTregression;

void (*additionalOutput) (char *filename) = NULL;
char *addOutputFileName = NULL;

int main(int argc, char *argv[]) {
  int size, position, msgsize, membersize, maxSizeIn, maxSizeOut;
  MPI_Comm   comm;
  MPI_Status status;
  char *bufferIn, *bufferOut;
  ResidualDataInput localResidualDataInput;
  ResidualOutput    localResidualOutput;
  int i, info[6], nLiqCoexistMax, nSolCoexistMax, nrMAX;
  double molesElmSol[107];

  /* Initialize the MELTS Enviroment */
  InitComputeDataStruct();

  /* 5b -> parse and determine conversion vectors for extra solid species */
  for(i=0; i<nes; i++) {
    int j, k;
    extraSolids[i].index = -1;
    for (j=0; j<npc; j++) if ((solids[j].type == PHASE) && (solids[j].convert != NULL) && !strcmp(solids[j].label, extraSolids[i].phase)) { 
      extraSolids[i].index = j; break; 
    }
    if (extraSolids[i].index != -1) {
      for (j=0; j<107; j++) molesElmSol[j] = 0.0;
      (void) formulaToMwStoich((char *) extraSolids[i].formula, molesElmSol);
      for (j=0,extraSolids[i].nAtoms=0.0; j<107; j++) extraSolids[i].nAtoms += molesElmSol[j];
      extraSolids[i].oxygen = molesElmSol[8];			 /* moles of oxygen   */
 
      extraSolids[i].m = (double *) malloc((size_t) (solids[extraSolids[i].index].na)*sizeof(double));
      (*solids[extraSolids[i].index].convert) (FIRST, SECOND, 1000.0, 1.0, molesElmSol, extraSolids[i].m, NULL, NULL, NULL, NULL, NULL, NULL);
      extraSolids[i].solToLiq = (double *) calloc((size_t) nlc, sizeof(double));
      for (j=0, extraSolids[i].norm=0.0; j<solids[extraSolids[i].index].na; j++) {
  	extraSolids[i].norm += pow((extraSolids[i].m)[j], (double) 2.0);
  	for (k=0; k<nlc; k++) (extraSolids[i].solToLiq)[k] += (extraSolids[i].m)[j]*(solids[extraSolids[i].index+1+j].solToLiq)[k];
      }
 
      for (j=0; j<solids[extraSolids[i].index].na; j++) if (fabs((extraSolids[i].m)[j]) < sqrt(DBL_EPSILON)) (extraSolids[i].m)[j] = 0.0;
      for (j=0; j<nlc; j++) if(fabs((extraSolids[i].solToLiq)[j]) < sqrt(DBL_EPSILON)) (extraSolids[i].solToLiq)[j] = 0.0;
    }
  }

  /* Initialize the MPI Environment */
  if (VERBOSE_DEBUG_MPI) printf("MPI:main[preclb_slave.c at line %d]--> Calling MPI_Init()...\n", __LINE__);
  MPI_Init(&argc, &argv);
  if (VERBOSE_DEBUG_MPI) printf("MPI:main[preclb_slave.c at line %d]--> Calling MPI_Comm_size()...\n", __LINE__);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (VERBOSE_DEBUG_MPI) printf("MPI:main[preclb_slave.c at line %d]--> Calling MPI_Comm_get_parent()...\n", __LINE__);
  MPI_Comm_get_parent(&comm);
  if (comm == MPI_COMM_NULL) {
    printf("MPI:main[preclb_slave.c at line %d]--> No parent for MPI slave process! ABORTING.\n", __LINE__);
    MPI_Abort(MPI_COMM_WORLD, (1 << 16) + 1);
  }
  
  if (VERBOSE_DEBUG_MPI) printf("MPI:main[preclb_slave.c at line %d]--> Calling MPI_Recv()[pre-loop]...\n", __LINE__);
  MPI_Recv(info, 7, MPI_INT, 0, MPI_ANY_TAG, comm, &status);
  nLiqCoexistMax = info[2];
  nSolCoexistMax = info[3];
  nrMAX          = info[4];
  nParam         = info[5];
  useTregression = info[6];
  if (VERBOSE_DEBUG_MPI) printf("  				        ...nLiqCoexistMax = %d...\n", nLiqCoexistMax);
  if (VERBOSE_DEBUG_MPI) printf("  				        ...nSolCoexistMax = %d...\n", nSolCoexistMax);
  if (VERBOSE_DEBUG_MPI) printf("  				        ...nrMAX	  = %d...\n", nrMAX);
  if (VERBOSE_DEBUG_MPI) printf("  				        ...nParam	  = %d...\n", nParam);
  if (VERBOSE_DEBUG_MPI) printf("  				        ...useTregression = %d...\n", useTregression);

#ifdef USE_LAM_XLED
   (void) lam_ledinit(info[0], info[1]);
   (void) lam_ledclr();
   (void) lam_ledon(3);
#endif
 
  /* Allocate enough storage to hold incoming case and its buffer */
  localResidualDataInput.rLiq      = (double **) malloc((size_t) nLiqCoexistMax*sizeof(double *));
  for (i=0; i<nLiqCoexistMax; i++) (localResidualDataInput.rLiq)[i] = (double *) malloc((size_t) (nlc-1)*sizeof(double));
  localResidualDataInput.pIndex    = (int *)     malloc((size_t) nSolCoexistMax*sizeof(int));
  localResidualDataInput.cIndex    = (int *)     malloc((size_t) nSolCoexistMax*sizeof(int));
  localResidualDataInput.rSol      = (double **) malloc((size_t) nSolCoexistMax*sizeof(double *));
  for (i=0; i<nSolCoexistMax; i++) (localResidualDataInput.rSol)[i] = (double *) malloc((size_t) nrMAX*sizeof(double));
  localResidualDataInput.isEqual   = (int *)     malloc((size_t) nSolCoexistMax*sizeof(int));
  localResidualDataInput.depenG    = (double *)  malloc((size_t) nSolCoexistMax*sizeof(double));
  localResidualDataInput.dependGdT = (double *)  malloc((size_t) nSolCoexistMax*sizeof(double));

  MPI_Pack_size(2 + 3*nSolCoexistMax, MPI_INT, comm, &membersize); 
  maxSizeIn  = membersize;
  MPI_Pack_size(3 + 2*nSolCoexistMax + (nlc-1)*nLiqCoexistMax + nrMAX*nSolCoexistMax, MPI_DOUBLE, comm, &membersize); 
  maxSizeIn += membersize;
  
  MPI_Pack_size(4*(nls*(nls-1)/2+nls+npc)+3*nc, MPI_INT, comm, &membersize);    if (membersize > maxSizeIn) maxSizeIn = membersize;
  MPI_Pack_size(3*(nls*(nls-1)/2+nls+npc)+3*nc, MPI_DOUBLE, comm, &membersize); if (membersize > maxSizeIn) maxSizeIn = membersize;

  bufferIn = (char *) malloc((size_t) maxSizeIn);
  
  /* Allocate enough storage to hold outgoing case and its buffer */
  localResidualOutput.residuals = (double *) malloc((size_t) nSolCoexistMax*sizeof(double));
  localResidualOutput.dr        = (double *) malloc((size_t) nSolCoexistMax*nParam*sizeof(double));

  MPI_Pack_size(1,                              MPI_INT,    comm, &membersize); maxSizeOut  = membersize;
  MPI_Pack_size(nLiqCoexistMax-1+nSolCoexistMax,MPI_DOUBLE, comm, &membersize); maxSizeOut += membersize;
  MPI_Pack_size(nSolCoexistMax*nParam,          MPI_DOUBLE, comm, &membersize); maxSizeOut += membersize;
  bufferOut = (char *) malloc((size_t) maxSizeOut);

  setModeToMixingLiq(FALSE);
  /* End initialization; Loop on work requests. */
  for (;;) {
    int j;
    if (VERBOSE_DEBUG_MPI) printf("MPI:main[preclb_slave.c at line %d]--> Calling MPI_Recv()[in loop]...\n", __LINE__);
    MPI_Recv(bufferIn, maxSizeIn, MPI_PACKED, 0, MPI_ANY_TAG, comm, &status);
    if (VERBOSE_DEBUG_MPI) {
      printf("MPI:main[preclb_slave.c at line %d]--> Exit from MPI_Recv()[in loop]. Status tag = %d\n", __LINE__, status.MPI_TAG);
      printf("                                       Legal: DIETAG (%d), INTPARAMSTAG (%d), DOUBLEPARAMSTAG (%d), or WORKTAG (%d)\n",
        DIETAG, INTPARAMSTAG, DOUBLEPARAMSTAG, WORKTAG);
    }
    
    if (status.MPI_TAG == DIETAG      ) break;
    
    if (status.MPI_TAG == INTPARAMSTAG) {
      static int *intParamsFromMaster;
      if (intParamsFromMaster == NULL) intParamsFromMaster = (int *) malloc ((size_t) (4*(nls*(nls-1)/2+nls+npc)+3*(nc+1))*sizeof(int));
      position = 0;
      MPI_Get_count(&status, MPI_PACKED, &msgsize);
      MPI_Unpack(bufferIn, msgsize, &position, intParamsFromMaster, 4*(nls*(nls-1)/2+nls+npc)+3*(nc+1), MPI_INT, comm);
      for (i=0; i<(nls*(nls-1)/2+nls+npc); i++) {
        modelParameters[i].activeH = intParamsFromMaster[		           i];
	modelParameters[i].activeS = intParamsFromMaster[  (nls*(nls-1)/2+nls+npc)+i];
	modelParameters[i].activeV = intParamsFromMaster[2*(nls*(nls-1)/2+nls+npc)+i];
	modelParameters[i].activeF = intParamsFromMaster[3*(nls*(nls-1)/2+nls+npc)+i];
      }
#ifdef BUILD_MGO_SIO2_VERSION
      for (i=0; i<nc; i++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
      for (i=0; i<nc; i++) {
#else
      for (i=0; i<(nc+1); i++) {
#endif
        eosModelParameters[i].activeKp   = intParamsFromMaster[4*(nls*(nls-1)/2+nls+npc)         +i];
	eosModelParameters[i].activeKpp  = intParamsFromMaster[4*(nls*(nls-1)/2+nls+npc)+  (nc+1)+i];
	eosModelParameters[i].activeKppp = intParamsFromMaster[4*(nls*(nls-1)/2+nls+npc)+2*(nc+1)+i];
      }
      
    } else if (status.MPI_TAG == DOUBLEPARAMSTAG) {
      static double *doubleParamsFromMaster;
      if(doubleParamsFromMaster == NULL) doubleParamsFromMaster = (double *) malloc ((size_t) nParam*sizeof(double));
      position = 0;
      MPI_Get_count(&status, MPI_PACKED, &msgsize);
      MPI_Unpack(bufferIn, msgsize, &position, doubleParamsFromMaster, nParam, MPI_DOUBLE, comm);
      for (i=0, j=0; i<(nls*(nls-1)/2+nls+npc); i++) {
        if (modelParameters[i].activeH && !modelParameters[i].activeF) 
	                                modelParameters[i].enthalpy = doubleParamsFromMaster[j++];
	if (modelParameters[i].activeS) modelParameters[i].entropy  = doubleParamsFromMaster[j++];
	if (modelParameters[i].activeV) modelParameters[i].volume   = doubleParamsFromMaster[j++];
	if (modelParameters[i].activeF) modelParameters[i].enthalpy = 
	  (((i < (nls*(nls-1)/2)) || (i > ((nls*(nls-1)/2)+nls))) ? 1473.15 : liquid[i-(nls*(nls-1)/2)].tfus)
          *modelParameters[i].entropy;
      }
#ifdef BUILD_MGO_SIO2_VERSION
      for (i=0; i<nc; i++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
      for (i=0; i<nc; i++) {
#else
      for (i=0; i<(nc+1); i++) {
#endif
        if (eosModelParameters[i].activeKp)   eosModelParameters[i].Kp   = doubleParamsFromMaster[j++];
	if (eosModelParameters[i].activeKpp)  eosModelParameters[i].Kpp  = doubleParamsFromMaster[j++];
	if (eosModelParameters[i].activeKppp) eosModelParameters[i].Kppp = doubleParamsFromMaster[j++];
	if (eosModelParameters[i].activeKp || eosModelParameters[i].activeKpp || eosModelParameters[i].activeKppp) {
     	  double v0    = bulkSystem[i].gk_v;
     	  double alpha = (v0 != 0.0) ? bulkSystem[i].gk_dvdt/v0 : 0.0;
     	  double c     = bulkSystem[i].gk_c;
     	  double cp    = bulkSystem[i].gk_cp;
     	  double mw    = bulkSystem[i].mw;
     	  double v1    = ((mw != 0.0) && (c != 0.0) && (cp != 0.0)) ? -v0*v0*(1000.0/(mw*c*c) + 1673.15*alpha*alpha/(cp)) : 0.0;
     	  double K     = (v1 != 0.0) ? -v0/v1 : 0.0;
     	  double Kp    = eosModelParameters[i].Kp;
     	  double Kpp   = eosModelParameters[i].Kpp;
     	  double Kppp  = eosModelParameters[i].Kppp;
     	  eosModelParameters[i].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
     	  eosModelParameters[i].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
     	  eosModelParameters[i].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
	}
      }
      
    } else { /* WORKTAG */
      position = 0;
      MPI_Get_count(&status, MPI_PACKED, &msgsize);
      MPI_Unpack(bufferIn, msgsize, &position, &(localResidualDataInput.t),        1,		                MPI_DOUBLE, comm);
      MPI_Unpack(bufferIn, msgsize, &position, &(localResidualDataInput.p),        1,		                MPI_DOUBLE, comm);
      MPI_Unpack(bufferIn, msgsize, &position, &(localResidualDataInput.fo2),      1,		                MPI_DOUBLE, comm);
      MPI_Unpack(bufferIn, msgsize, &position, &(localResidualDataInput.nLiq),     1,		                MPI_INT,    comm);
      for (i=0; i<localResidualDataInput.nLiq; i++) 
      MPI_Unpack(bufferIn, msgsize, &position,  (localResidualDataInput.rLiq)[i],  nlc-1,		        MPI_DOUBLE, comm);
      MPI_Unpack(bufferIn, msgsize, &position, &(localResidualDataInput.nSol),     1,		                MPI_INT,    comm);  
      MPI_Unpack(bufferIn, msgsize, &position,   localResidualDataInput.pIndex,    localResidualDataInput.nSol, MPI_INT,    comm);
      MPI_Unpack(bufferIn, msgsize, &position,   localResidualDataInput.cIndex,    localResidualDataInput.nSol, MPI_INT,    comm);
      for (i=0; i<localResidualDataInput.nSol; i++) if (solids[j = (localResidualDataInput.pIndex)[i]].convert != NULL)
      MPI_Unpack(bufferIn, msgsize, &position,  (localResidualDataInput.rSol)[i],  solids[j].nr,	        MPI_DOUBLE, comm);
      MPI_Unpack(bufferIn, msgsize, &position,   localResidualDataInput.isEqual,   localResidualDataInput.nSol, MPI_INT,    comm);
      MPI_Unpack(bufferIn, msgsize, &position,   localResidualDataInput.depenG,    localResidualDataInput.nSol, MPI_DOUBLE, comm);
      MPI_Unpack(bufferIn, msgsize, &position,   localResidualDataInput.dependGdT, localResidualDataInput.nSol, MPI_DOUBLE, comm);
      
      if (VERBOSE_DEBUG_MPI) {
        printf("MPI:main[preclb_slave.c at line %d]--> Finished unpacking liquid input structure...\n", __LINE__);
	printf("     T (K) = %lf, P (bars) = %lf, log fO2 = %lf, nSolids = %d\n", localResidualDataInput.t, localResidualDataInput.p,
	  localResidualDataInput.fo2, localResidualDataInput.nSol);
	printf("     pIndex cIndex flag dependent\n");
	for (i=0; i<localResidualDataInput.nSol; i++) {
	  printf("       %3.3d    %3.3d    %1.1d %lf %lf\n", (localResidualDataInput.pIndex)[i], (localResidualDataInput.cIndex)[i],
	    (localResidualDataInput.isEqual)[i], (localResidualDataInput.depenG)[i],(localResidualDataInput.dependGdT)[i]);
	}
      }
      if (VERBOSE_DEBUG_MPI) printf("MPI:main[preclb_slave.c at line %d]--> About to enter calculateResidualPack().\n", __LINE__);

#ifdef USE_LAM_XLED
     (void) lam_ledon(4);
#endif

      /* Perform the calculation for this case */
      calculateResidualPack(&localResidualDataInput, &localResidualOutput);

#ifdef USE_LAM_XLED
     (void) lam_ledoff(4);
#endif

      if (VERBOSE_DEBUG_MPI) {
        printf("MPI:main[preclb_slave.c at line %d]--> Return from calculateResidualPack().\n", __LINE__);
      
        printf("   nSol = %d, p = %d, dr = ", localResidualDataInput.nSol, nParam);
        for (i=0; i<localResidualDataInput.nSol; i++) printf("%lf ", (localResidualOutput.dr)[i]);
        printf("\n");
      }

      position = 0;
      MPI_Pack(&(localResidualOutput.flag),     1,				     MPI_INT,	 bufferOut, maxSizeOut, &position, comm);
      MPI_Pack(  localResidualOutput.residuals, localResidualDataInput.nSol,	     MPI_DOUBLE, bufferOut, maxSizeOut, &position, comm);
      MPI_Pack(  localResidualOutput.dr,       (localResidualDataInput.nSol)*nParam, MPI_DOUBLE, bufferOut, maxSizeOut, &position, comm);
      MPI_Send(bufferOut, position, MPI_PACKED, 0, REPLYTAG, comm);

    } /* End WORKTAG CASE */
  } /* END INFINITE LOOP - exit with DIETAG */

#ifdef USE_LAM_XLED
   (void) lam_ledoff(3);
   (void) lam_ledon(5);
#endif

  MPI_Comm_free(&comm);
  MPI_Finalize();
  return (0);
}

#endif /* USE_MPI */

/* End of file PRECLB_SLAVE.C */
