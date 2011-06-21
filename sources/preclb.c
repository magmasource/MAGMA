const char *preclb_ver(void) { return "$Id: preclb.c,v 1.61 2009/05/14 04:24:00 ghiorso Exp $"; }
#ifdef USE_MPI
const char *preclb_slave_ver(void) { return "$Id: preclb.c,v 1.61 2009/05/14 04:24:00 ghiorso Exp $"; }
#endif
/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Toolkit work proceedure to drive a PRECLB iteration (file: PRECLB.C)
**
**--
*/

/**********************************************************************************/
/* If xMELTS is running in MPI-calibration mode ...                               */
/* <><><><><> Sections indicated below require configuration for specific cluster */
/**********************************************************************************/

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

/* Motif Include Files */

#include <Xm/Xm.h> 
#include <Xm/ToggleBG.h>

/* MELTS Include Files */

#include "interface.h"
#include "silmin.h"               
#include "recipes.h"

/* MELTS Regression Phase Support */

#include "calibration.h"
#include "res_struct_data.h"

#define DEBUG         1
#define VERBOSE_DEBUG 0

/* 
defining STOLPER_WATER causes all hydroxyl species properties
to depend on those of H2O in a predefined manner 
*/  

#define NOT_STOLPER_WATER

#ifdef USE_MPI
static const int nLiqCoexistMax =   1;
#endif
static const int nSolCoexistMax = 100;

ResidualDataInput *residualDataInput = NULL;
ResidualOutput    *residualOutput    = NULL;

int nEqn    = 0;
int nLiquid = 0;

/* Grace Graphics Package Support */

#ifdef GRACE_PIPE
#include <unistd.h>
#include <grace_np.h>
static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}
#endif /* GRACE_PIPE */

int isOrthopyroxene(double t, double p, double *r);
int isPigeonite(double t, double p, double *r);

#define SQUARE(x) ((x)*(x))
#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))

/* ======================================================================================= */
/* PORT 3 external routines and user defined functions                                     */
/* ======================================================================================= */

extern int dn2gb_(   /* double version of n2gb routine from the PORT Library v.3           */
  int     *n,	     /* number of observations						   */
  int     *p,	     /* number of parameters						   */
  double  *x,	     /* input: initial guess at optimal parameters. output: best estiamte  */
  double  *b,	     /* bounds, FORTRAN B(2,P) = {low, high, low, high, ....}		   */
  int    (*calcr)(), /* int calcr(...) : function to calculate vector of residuals	   */
  int    (*calcj)(), /* int calcj(...) : function to calculate the Jacobian matrix	   */
  int     *iv,       /* control array							   */
  int     *liv,      /* of length 82 + 4*p						   */
  int     *lv,       /* control array							   */
  double  *v,	     /* of length 105 + p*(n + 2*p + 21) + 2*n				   */
  int     *uiparm,   /* integer array passed to calcr, calcj				   */
  double  *urparm,   /* double array passed to calcr, calcj				   */
  int    (*ufparm)() /* int ufparam(...) : user function passed to calcr, calcj 	   */
);
  
extern int divset_(  /* double version of ivset routine from the PORT Library v.3          */
  int        *kind,  /* type of optimization routine, regression with simple bounds = 1    */
  int        *iv,    /* control array  						           */
  int        *liv,   /* of length 82 + 4*p						   */
  int        *lv,    /* control array  						           */
  double     *v      /* of length 105 + p*(n + 2*p + 21) + 2*n 			           */
);

int stopx_(/* function called by PORT Library v.3 to test for interrupts                   */
  int     dummy) {
  if (fopen("STOP_MELTS", "r") != NULL) return TRUE;
  else return FALSE;                            /* return TRUE_ to halt dn2gb              */
}

/*******************************************************************************************/
/*=========================================================================================*/
/*******************************************************************************************/

/* MPI Include Files */

#ifdef USE_MPI

#define DEBUG_MPI         1
#define VERBOSE_DEBUG_MPI 0

#include <mpi.h>

#ifdef USE_XLED
#include <ledreq.h>
#endif /* USE_XLED */

static int             ntasks;		/* # compute tasks */
static MPI_Comm        *icomm_slaves;	/* inter comm. to each slave */
static MPI_Request     *req_slaves;	/* receive reqs from slaves */

typedef struct _work {
  ResidualDataInput *residualDataInput;
  int                index;
  struct _work      *wrk_next;
} Work;

static Work **work_slaves; /* slave's current work                  */
static int    nwork_out;   /* # work items out there                */
static Work  *work_bottom; /* bottom of work list                   */
static Work  *work_top;	   /* top of work list                      */
static Work  *work_ref;    /* reference pointer to top of work list */

static char *bufferOut, *bufferParams, **bufferIn;
static int  maxSizeIn, maxSizeOut, maxSizeParams, *intParamsToSendToSlave;
static double *doubleParamsToSendToSlave;

static int return_status = 0;	/* Return status for master */

/* insert work into list */
static void insert(Work *pwrk) {
  if (work_top    == 0) { work_top = pwrk;              }
  if (work_bottom != 0) { work_bottom->wrk_next = pwrk; }
  work_bottom = pwrk;
  pwrk->wrk_next = 0;
}

/* gets results */
static int harvest(void) {
  int err, idone;

  nwork_out--;
  err = MPI_Waitany(ntasks, req_slaves, &idone, MPI_STATUS_IGNORE);

  if (err != MPI_SUCCESS) {
    if (idone >= 0) {
      req_slaves[idone] = MPI_REQUEST_NULL;
      MPI_Comm_free(&icomm_slaves[idone]);
      insert(work_slaves[idone]);
      if (DEBUG_MPI) printf("MPI:harvest[preclb.c at line %d]--> Insert() called.\n", __LINE__);
    }
    return (-1);
  }

  return (idone);
}

/* distributes work */
static void seed(int islave) {
  int i, err, position, index = work_top->index;
  ResidualDataInput *pt = work_top->residualDataInput;

  position = 0;
  MPI_Pack(&(pt->t),        1,        MPI_DOUBLE, bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack(&(pt->p),        1,        MPI_DOUBLE, bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack(&(pt->fo2),      1,        MPI_DOUBLE, bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack(&(pt->nLiq),     1,        MPI_INT,    bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  for (i=0; i<pt->nLiq; i++) 
    MPI_Pack((pt->rLiq)[i], nlc-1,    MPI_DOUBLE, bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack(&(pt->nSol),     1,        MPI_INT,    bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack( (pt->pIndex),   pt->nSol, MPI_INT,    bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack( (pt->cIndex),   pt->nSol, MPI_INT,    bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  for (i=0; i<pt->nSol; i++) if (solids[(pt->pIndex)[i]].convert != NULL)
    MPI_Pack((pt->rSol)[i], solids[(pt->pIndex)[i]].nr, MPI_DOUBLE, bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack( (pt->isEqual), pt->nSol,  MPI_INT,    bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack( (pt->depenG),    pt->nSol,  MPI_DOUBLE, bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack( (pt->dependGdT), pt->nSol,  MPI_DOUBLE, bufferOut, maxSizeOut, &position, icomm_slaves[islave]);

  if (VERBOSE_DEBUG_MPI) printf("MPI:seed[preclb.c at line %d]--> Calling MPI_Send(slave = %d) with a %d byte message.\n", 
                   __LINE__, islave+1, position);

  err = MPI_Send(bufferOut, position, MPI_PACKED, 0, WORKTAG, icomm_slaves[islave]);
  if (err != MPI_SUCCESS) { MPI_Comm_free(&icomm_slaves[islave]); return; }

  ++nwork_out;
  work_slaves[islave] = work_top;
  work_top = work_top->wrk_next;
  
  err = MPI_Irecv(bufferIn[index], maxSizeIn, MPI_PACKED, 0, REPLYTAG, icomm_slaves[islave], &req_slaves[islave]);
  if (err != MPI_SUCCESS) {
    req_slaves[islave] = MPI_REQUEST_NULL;
    MPI_Comm_free(&icomm_slaves[islave]);
    insert(work_slaves[islave]);
    if (DEBUG_MPI) printf("MPI:seed[preclb.c at line %d]--> Insert() called.\n", __LINE__);
    --nwork_out;
  }
}
#endif /* USE_MPI  */

/*******************************************************************************************/
/*=========================================================================================*/
/*******************************************************************************************/

static int lastNf, currentNf;

static int isNAN (double x) { return x != x; }

int calcr(/* Residual routine required by dn2gb                                     	   */
  int        *pt_n,  /* nuumber of observations 				    	   */
  int        *pt_p,  /* number of parameters					    	   */
  double     *x,     /* current parameter guess 				    	   */
  int        *pt_nf, /* invocation count for calcr; set to 0 if x is infeasible     	   */
  double     *r,     /* FORTRAN: R(N), r[1:n]                 	                    	   */
  int        *ui,    /* passed via dn2gb					    	   */
  double     *ur,    /* passed via dn2gb					    	   */
  int       (*uf)()  /* passed via dn2gb					    	   */
) {
  int n = (int) *pt_n, p = (int) *pt_p, nf = (int) *pt_nf, i, index, failure;
  double sumOfSquares = 0.0;
  static int nH2O = -1, nSiOH = -1, nAlOH = -1, nFe3OH = -1, nFe2OH = -1, nMgOH = -1, nCaOH = -1, 
             nNaOH = -1, nKOH = -1, *equivH2OSi, *equivH2OAl, *equivH2OFe3, *equivH2OFe2, 
	     *equivH2OMg, *equivH2OCa, *equivH2ONa, *equivH2OK, firstCall = TRUE;
  static Boolean useTrustRegionMethod;
  static double timeIn, timeOut, timeCumm;
  
#ifdef USE_MPI
  timeIn = MPI_Wtime();
#else
  timeIn = ( (double) clock())/( (double) CLOCKS_PER_SEC);
#endif

  if (VERBOSE_DEBUG) printf("calcr[preclb.c at line %d]--> Start with nf = %5.5d at time %lf (secs).\n", __LINE__,  nf, timeCumm); 
  fflush(stdout);

  /* Deal with the special case of water */
  if (firstCall) {
    int j, k;
    int **indIJ = imatrix(0, nls-1, 0, nls-1); 
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
      printf("calcr[preclb.c at line %d]--> failure to find index for H2O or *OH.\n", __LINE__);
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
    
    free_imatrix(indIJ, 0, nls-1, 0, nls-1);
    useTrustRegionMethod = XmToggleButtonGadgetGetState(tg_trust_region_method);
  }

  /* Update the current modelParameters values and set temporary active flags - reset below */
  for (i=0, index=0; i<(nls*(nls-1)/2+nls+npc); i++) {
    if (modelParameters[i].activeH) modelParameters[i].enthalpy = x[index++]*SCALE;
    if (modelParameters[i].activeS) modelParameters[i].entropy  = x[index++];
    if (modelParameters[i].activeV) modelParameters[i].volume   = x[index++];
  }
  for (i=0; i<(nls*(nls-1)/2+nls+npc); i++) if (modelParameters[i].activeF) {
    modelParameters[i].enthalpy = 
     (((i < (nls*(nls-1)/2)) || (i > ((nls*(nls-1)/2)+nls))) ? 1473.15 : liquid[i-(nls*(nls-1)/2)].tfus)
     *modelParameters[i].entropy;
    modelParameters[i].activeH  = TRUE;
  }
#ifdef BUILD_MGO_SIO2_VERSION
  for (i=0; i<nc; i++) if (eosModelParameters[i].activeKp || eosModelParameters[i].activeKpp || eosModelParameters[i].activeKppp) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
  for (i=0; i<nc; i++) if (eosModelParameters[i].activeKp || eosModelParameters[i].activeKpp || eosModelParameters[i].activeKppp) {
#else
  for (i=0; i<(nc+1); i++) if (eosModelParameters[i].activeKp || eosModelParameters[i].activeKpp || eosModelParameters[i].activeKppp) {
#endif
    double v0	 = bulkSystem[i].gk_v;
    double alpha = (v0 != 0.0) ? bulkSystem[i].gk_dvdt/v0 : 0.0;
    double c	 = bulkSystem[i].gk_c;
    double cp	 = bulkSystem[i].gk_cp;
    double mw	 = bulkSystem[i].mw;
    double v1	 = ((mw != 0.0) && (c != 0.0) && (cp != 0.0)) ? -v0*v0*(1000.0/(mw*c*c) + 1673.15*alpha*alpha/(cp)) : 0.0;
    double K	 = (v1 != 0.0) ? -v0/v1 : 0.0;
    double Kp, Kpp, Kppp;
    if (eosModelParameters[i].activeKp)   eosModelParameters[i].Kp   = x[index++];
    if (eosModelParameters[i].activeKpp)  eosModelParameters[i].Kpp  = x[index++];
    if (eosModelParameters[i].activeKppp) eosModelParameters[i].Kppp = x[index++];
    Kp    = eosModelParameters[i].Kp;
    Kpp   = eosModelParameters[i].Kpp;
    Kppp  = eosModelParameters[i].Kppp;
    eosModelParameters[i].v2 = (K != 0.0) ? (Kp+1.0)*v0/K/K : 0.0;
    eosModelParameters[i].v3 = (K != 0.0) ? (Kpp*K - (2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K : 0.0;
    eosModelParameters[i].v4 = (K != 0.0) ? (Kppp*K*K - Kpp*K*(4.0+6.0*Kp) + (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0))*v0/K/K/K/K : 0.0;
  }

#ifdef STOLPER_WATER  
  /* Special constraint on water: thermo prop correction is Si(1/4)OH = H2O/2 */ 
  if ( (nH2O != -1) && (nSiOH != -1) ) for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    if ((equivH2OSi[i] != -1) && modelParameters[equivH2OSi[i]].activeH) modelParameters[i].enthalpy = modelParameters[equivH2OSi[i]].enthalpy/2.0;
    if ((equivH2OSi[i] != -1) && modelParameters[equivH2OSi[i]].activeS) modelParameters[i].entropy  = modelParameters[equivH2OSi[i]].entropy/2.0;
    if ((equivH2OSi[i] != -1) && modelParameters[equivH2OSi[i]].activeV) modelParameters[i].volume   = modelParameters[equivH2OSi[i]].volume/2.0;
  }
  /* Special constraint on water: thermo prop correction is Al(1/3)OH = H2O/2 */ 
  if ( (nH2O != -1) && (nAlOH != -1) ) for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    if ((equivH2OAl[i] != -1) && modelParameters[equivH2OAl[i]].activeH) modelParameters[i].enthalpy = modelParameters[equivH2OAl[i]].enthalpy/2.0;
    if ((equivH2OAl[i] != -1) && modelParameters[equivH2OAl[i]].activeS) modelParameters[i].entropy  = modelParameters[equivH2OAl[i]].entropy/2.0;
    if ((equivH2OAl[i] != -1) && modelParameters[equivH2OAl[i]].activeV) modelParameters[i].volume   = modelParameters[equivH2OAl[i]].volume/2.0;
  }
  /* Special constraint on water: thermo prop correction is Fe(1/3)OH = H2O/2 */ 
  if ( (nH2O != -1) && (nFe3OH != -1) ) for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    if ((equivH2OFe3[i] != -1) && modelParameters[equivH2OFe3[i]].activeH) modelParameters[i].enthalpy = modelParameters[equivH2OFe3[i]].enthalpy/2.0;
    if ((equivH2OFe3[i] != -1) && modelParameters[equivH2OFe3[i]].activeS) modelParameters[i].entropy  = modelParameters[equivH2OFe3[i]].entropy/2.0;
    if ((equivH2OFe3[i] != -1) && modelParameters[equivH2OFe3[i]].activeV) modelParameters[i].volume   = modelParameters[equivH2OFe3[i]].volume/2.0;
  }
  /* Special constraint on water: thermo prop correction is Fe(1/2)OH = H2O/2 */ 
  if ( (nH2O != -1) && (nFe2OH != -1) ) for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    if ((equivH2OFe2[i] != -1) && modelParameters[equivH2OFe2[i]].activeH) modelParameters[i].enthalpy = modelParameters[equivH2OFe2[i]].enthalpy/2.0;
    if ((equivH2OFe2[i] != -1) && modelParameters[equivH2OFe2[i]].activeS) modelParameters[i].entropy  = modelParameters[equivH2OFe2[i]].entropy/2.0;
    if ((equivH2OFe2[i] != -1) && modelParameters[equivH2OFe2[i]].activeV) modelParameters[i].volume   = modelParameters[equivH2OFe2[i]].volume/2.0;
  }
  /* Special constraint on water: thermo prop correction is Mg(1/2)OH = H2O/2 */ 
  if ( (nH2O != -1) && (nMgOH != -1) ) for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    if ((equivH2OMg[i] != -1) && modelParameters[equivH2OMg[i]].activeH) modelParameters[i].enthalpy = modelParameters[equivH2OMg[i]].enthalpy/2.0;
    if ((equivH2OMg[i] != -1) && modelParameters[equivH2OMg[i]].activeS) modelParameters[i].entropy  = modelParameters[equivH2OMg[i]].entropy/2.0;
    if ((equivH2OMg[i] != -1) && modelParameters[equivH2OMg[i]].activeV) modelParameters[i].volume   = modelParameters[equivH2OMg[i]].volume/2.0;
  }
  /* Special constraint on water: thermo prop correction is Ca(1/2)OH = H2O/2 */ 
  if ( (nH2O != -1) && (nCaOH != -1) ) for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    if ((equivH2OCa[i] != -1) && modelParameters[equivH2OCa[i]].activeH) modelParameters[i].enthalpy = modelParameters[equivH2OCa[i]].enthalpy/2.0;
    if ((equivH2OCa[i] != -1) && modelParameters[equivH2OCa[i]].activeS) modelParameters[i].entropy  = modelParameters[equivH2OCa[i]].entropy/2.0;
    if ((equivH2OCa[i] != -1) && modelParameters[equivH2OCa[i]].activeV) modelParameters[i].volume   = modelParameters[equivH2OCa[i]].volume/2.0;
  }
  /* Special constraint on water: thermo prop correction is NaOH = H2O/2 */ 
  if ( (nH2O != -1) && (nNaOH != -1) ) for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    if ((equivH2ONa[i] != -1) && modelParameters[equivH2ONa[i]].activeH) modelParameters[i].enthalpy = modelParameters[equivH2ONa[i]].enthalpy/2.0;
    if ((equivH2ONa[i] != -1) && modelParameters[equivH2ONa[i]].activeS) modelParameters[i].entropy  = modelParameters[equivH2ONa[i]].entropy/2.0;
    if ((equivH2ONa[i] != -1) && modelParameters[equivH2ONa[i]].activeV) modelParameters[i].volume   = modelParameters[equivH2ONa[i]].volume/2.0;
  }
  /* Special constraint on water: thermo prop correction is KOH = H2O/2 */ 
  if ( (nH2O != -1) && (nKOH != -1) ) for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    if ((equivH2OK[i] != -1) && modelParameters[equivH2OK[i]].activeH) modelParameters[i].enthalpy = modelParameters[equivH2OK[i]].enthalpy/2.0;
    if ((equivH2OK[i] != -1) && modelParameters[equivH2OK[i]].activeS) modelParameters[i].entropy  = modelParameters[equivH2OK[i]].entropy/2.0;
    if ((equivH2OK[i] != -1) && modelParameters[equivH2OK[i]].activeV) modelParameters[i].volume   = modelParameters[equivH2OK[i]].volume/2.0;
  }
#endif /* STOLPER_WATER */

#ifdef USE_MPI
  if (firstCall) {
    for (i=0; i<(nls*(nls-1)/2+nls+npc); i++) {
      intParamsToSendToSlave[			       i] = modelParameters[i].activeH;
      intParamsToSendToSlave[  (nls*(nls-1)/2+nls+npc)+i] = modelParameters[i].activeS;
      intParamsToSendToSlave[2*(nls*(nls-1)/2+nls+npc)+i] = modelParameters[i].activeV;
      intParamsToSendToSlave[3*(nls*(nls-1)/2+nls+npc)+i] = modelParameters[i].activeF;
    }
#ifdef BUILD_MGO_SIO2_VERSION
    for (i=0; i<nc; i++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
    for (i=0; i<nc; i++) {
#else
    for (i=0; i<(nc+1); i++) {
#endif
      intParamsToSendToSlave[4*(nls*(nls-1)/2+nls+npc)+         i] = eosModelParameters[i].activeKp;
      intParamsToSendToSlave[4*(nls*(nls-1)/2+nls+npc)+  (nc+1)+i] = eosModelParameters[i].activeKpp;
      intParamsToSendToSlave[4*(nls*(nls-1)/2+nls+npc)+2*(nc+1)+i] = eosModelParameters[i].activeKppp;
    }
  }   
   
  for (i=0, index=0; i<(nls*(nls-1)/2+nls+npc); i++) {
    if (modelParameters[i].activeH && !modelParameters[i].activeF) 
                                    doubleParamsToSendToSlave[index++] = modelParameters[i].enthalpy;
    if (modelParameters[i].activeS) doubleParamsToSendToSlave[index++] = modelParameters[i].entropy;
    if (modelParameters[i].activeV) doubleParamsToSendToSlave[index++] = modelParameters[i].volume;
  }
  
#ifdef BUILD_MGO_SIO2_VERSION
  for (i=0; i<nc; i++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
  for (i=0; i<nc; i++) {
#else
  for (i=0; i<(nc+1); i++) {
#endif
    if (eosModelParameters[i].activeKp)   doubleParamsToSendToSlave[index++] = eosModelParameters[i].Kp;
    if (eosModelParameters[i].activeKpp)  doubleParamsToSendToSlave[index++] = eosModelParameters[i].Kpp;
    if (eosModelParameters[i].activeKppp) doubleParamsToSendToSlave[index++] = eosModelParameters[i].Kppp;
  }

  for (i=0; i<ntasks; i++) {
    int position;
    
    if (firstCall) {
      position = 0;
      MPI_Pack(intParamsToSendToSlave, 4*(nls*(nls-1)/2+nls+npc)+3*(nc+1), MPI_INT, bufferParams, maxSizeParams, &position, icomm_slaves[i]);
      MPI_Send(bufferParams, position, MPI_PACKED, 0, INTPARAMSTAG, icomm_slaves[i]);
    }
    
    position = 0;
    MPI_Pack(doubleParamsToSendToSlave, p, MPI_DOUBLE, bufferParams, maxSizeParams, &position, icomm_slaves[i]);
    MPI_Send(bufferParams, position, MPI_PACKED, 0, DOUBLEPARAMSTAG, icomm_slaves[i]);
  }
#endif

  /* Save the Jocobian from the previous call for potential use by calcj; store current Jocobian for potential use by calcj */
  lastNf = currentNf; currentNf = nf; for (i=0; i<(n*p); i++) { ur[i] = ur[n*p + i]; ur[n*p + i] = 0.0; }
  failure = FALSE;
  firstCall = FALSE;
  
#ifdef USE_MPI

#ifdef USE_LAM_XLED
  (void) lam_ledon(1);
  (void) lam_ledoff(2);
#endif

  /* Distribute work to slaves until all the answers have been received or their are no more living slaves. */
  nwork_out = 0;
  if (work_top) work_ref = work_top; else work_top = work_ref;
  while (work_top) {
  
    /* Distribute a work order to all living slaves. */
    for (i=0; work_top && (i<ntasks); ++i) {
      if (icomm_slaves[i] == MPI_COMM_NULL) continue;
      seed(i);
    }

    if (nwork_out == 0) {
      if (DEBUG_MPI) printf("MPI:calcr[preclb.c at line %d]--> All the slaves are dead! ABORTING.\n", __LINE__);
      MPI_Abort(MPI_COMM_WORLD, 1);
    }

    /* Collect results and issue new work orders until there are no outstanding work orders. */
    do {
      int islave = harvest();
      if (islave < 0) ++return_status;  /* a node has died */
      if ((islave >= 0) && work_top) seed(islave);
    } while (nwork_out > 0);

    /* After letting living slaves idle due to lack of work, new
     * work orders may appear from slaves that die later.  So
     * start this whole process over with the remaining work
     * orders and living slaves. */
  }
  
#ifdef USE_LAM_XLED
  (void) lam_ledoff(1);
  (void) lam_ledon(2);
#endif

  /* Unpack the answers returned by the slaves */
  for (index=0; index<nLiquid; index++) {
    int nSol, position = 0;
    nSol = residualDataInput[index].nSol;
    MPI_Unpack(bufferIn[index], maxSizeIn, &position, &(residualOutput[index].flag),     1,      MPI_INT,    MPI_COMM_WORLD);
    MPI_Unpack(bufferIn[index], maxSizeIn, &position,   residualOutput[index].residuals, nSol,   MPI_DOUBLE, MPI_COMM_WORLD);
    MPI_Unpack(bufferIn[index], maxSizeIn, &position,   residualOutput[index].dr,        nSol*p, MPI_DOUBLE, MPI_COMM_WORLD);
    if (VERBOSE_DEBUG_MPI) {
      int j;
      printf("calcr[preclb.c at line %d]--> Result of unpacking message from slave(s) for liquid %d of %d\n", __LINE__, index, nLiquid);
      printf("     nsol = %d, p = %d, dr = ", nSol, p);
      for (j=0; j<p*nSol; j++) printf("%lf ", (residualOutput[index].dr)[j]);
      printf("\n");
    }
    if (!(residualOutput[index].flag) ) { failure = TRUE; break; }
  }
#else  /* USE_MPI */
  for (index=0; index<nLiquid; index++) {
    if (fmod((double) index, (double) (nLiquid/10)) == 0.0) { printf("*"); fflush(stdout); }
    calculateResidualPack(&(residualDataInput[index]), &(residualOutput[index]));
    if (!(residualOutput[index].flag) ) { failure = TRUE; break; }
  }
  printf("\n"); 
#endif /* USE_MPI */

  if (failure) {
    *pt_nf = 0; currentNf = lastNf; for (i=0; i<n*p; i++) ur[n*p + i] = ur[i];  
    printf("calcr[preclb.c at line %d]--> Failure for liquid %d of %d\n", __LINE__, index, nLiquid);
  } else {
    int j;
    for (index=0, j=0; index<nLiquid; index++) {
      int k;
      for (k=0; k<residualDataInput[index].nSol; k++, j++) {
        int l;
        r[j] = (residualOutput[index].residuals)[k];
	if (isNAN(r[j])) {
	  printf("calcr[preclb.c at line %d]--> NaN detected for r[%d] in liquid %d of %d\n", __LINE__, j, index, nLiquid);
	  (residualOutput[index].residuals)[k] = 0.0;
	  r[j] = 0.0;
	} else {
	  for (l=0; l<p; l++) ur[n*p + j + n*l] = (residualOutput[index].dr)[k*p+l]; /* ur(N,P), j[1:n(p=0), 1:n(p=1), ...., (1:n)(p)] */
          sumOfSquares   += r[j]*r[j];
	}
      }
    }
  
    if (j == n) {
      if (DEBUG) printf("calcr[preclb.c at line %d]--> Sum-of-Squares = %g (std = %g)\n", __LINE__, sumOfSquares,
                        (n != 0) ? sqrt(sumOfSquares/((double) n)) : 0.0);
      if (useTrustRegionMethod) {
#ifdef GRACE_PIPE
      GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, (double) nf, sumOfSquares);
      GracePrintf("WITH G0\n"); GracePrintf("AUTOSCALE\n");
      for (i=0; i<p; i++) GracePrintf("g1.s%1.1d POINT %lf, %lf\n", i, (double) nf, x[i]);
      GracePrintf("WITH G1\n"); GracePrintf("AUTOSCALE\n");
      GracePrintf("REDRAW\n");
#endif /* GRACE_PIPE */
      }
    } 
  }

  /* Reset modelParameter flags that were alterated temporarily on entry */
  for (i=0; i<(nls*(nls-1)/2+nls+npc); i++) if (modelParameters[i].activeF) modelParameters[i].activeH  = FALSE;

#ifdef USE_MPI
  timeOut = MPI_Wtime();
#else
  timeOut = ( (double) clock())/( (double) CLOCKS_PER_SEC);
#endif
  timeCumm += timeOut-timeIn;
  if (DEBUG) printf("calcr[preclb.c at line %d]--> Delta time elapsed: %lf, Cummulative time: %lf\n", __LINE__, timeOut-timeIn, timeCumm);
  
  return(0);
}

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

int calcj(/* Jacobian routine required by dn2gb                                    */
  int        *pt_n,  /* nuumber of observations                                    */
  int        *pt_p,  /* number of parameters                                       */
  double     *x,     /* current parameter guess                                    */
  int        *pt_nf, /* invocation count for calcr; set to 0 if x is infeasible    */
  double     *j,     /* FORTRAN: J(N,P), j[1:n(p=0), 1:n(p=1), ...., (1:n)(p)]     */
  int        *ui,    /* passed via dn2gb                                           */
  double     *ur,    /* passed via dn2gb                                           */
  int       (*uf)()  /* passed via dn2gb                                           */
 ) {
  int n = (int) *pt_n, p = (int) *pt_p, nf = (int) *pt_nf, offset, i;
  
  if (VERBOSE_DEBUG) printf("calcj[preclb.c at line %d]--> Start with nf = %5.5d\n", __LINE__,  nf);
   
  if      (nf == lastNf)    offset = 0;
  else if (nf == currentNf) offset = n*p;
  else {
    if (DEBUG) printf("calcj called with nf = %d, stored values are %d and %d.  Setting nf = 0 and exiting.\n", nf, lastNf, currentNf);
    *pt_nf = 0;
    return(0);
  }
  
  for (i=0; i<(n*p); i++) j[i] = ur[offset + i];  
  return(0);
}

int ufparm(void) { return(0);} /* User routine required by dn2gb                           */

/* ======================================================================================= */
/* Revised MRQRDT routines and user defined functions                                      */
/* ======================================================================================= */

static int funcEvals;

static void mrqcofWithBounds(double x[], double y[], double sig[], int ndata, double a[], int ia[],
  int ma, double **alpha, double beta[], double *chisq)
{
  static int iter = 0;
  int i, j, k, l, m, mfit=0, nf, offset=0;
  double *ymod, wt, sig2i, dy, *dyda, *aTemp;

  ymod = vector(1, ndata);
  for (j=1; j<=ma; j++) if (ia[j]) mfit++;
  dyda  = vector(1, 2*mfit*ndata);
  aTemp = vector(1, mfit);
  for (j=1,k=1; j<=ma; j++) if (ia[j]) aTemp[k++] = a[j];
  
  for (j=1; j<=mfit; j++) {
    for (k=1; k<=j; k++) alpha[j][k] = 0.0;
    beta[j] = 0.0;
  }
  
  *chisq = 0.0;
  funcEvals++;
  
  /* Replaced call to funcs with call to calcr */
  iter++; nf = iter;
  (void) calcr((int     *) &ndata, (int     *) &mfit, &aTemp[1], (int     *) &nf, &ymod[1], NULL, &dyda[1], ufparm);
  if      (nf == lastNf)    offset = 0;
  else if (nf == currentNf) offset = ndata*mfit;
  else printf("mrqcofWithBounds[preclb.c at line %d]--> calcr returned nf = %d, stored values are %d and %d.\n", __LINE__, nf, lastNf, currentNf);
  
  if(nf != 0) {
    for (i=1; i<=ndata; i++) {
      sig2i = 1.0/(sig[i]*sig[i]);
      dy = ymod[i];
      for (j=1, l=1; l<=ma; l++) {
        if (ia[l]) {
          wt = -dyda[offset+i+(j-1)*ndata]*sig2i;
          for (k=1,m=1;m<=l;m++) if (ia[m]) { alpha[j][k] -= wt*dyda[offset+i+(k-1)*ndata]; k++; }
          beta[j] += dy*wt;
	  j++;
        }
      }
      *chisq += dy*dy*sig2i;
    }
  } else *chisq = DBL_MAX;
  
  for (j=2; j<=mfit; j++) for (k=1; k<j; k++) alpha[k][j] = alpha[j][k];
  free_vector(ymod,  1, ndata);
  free_vector(dyda,  1, 2*mfit*ndata);
  free_vector(aTemp, 1, mfit);
}

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

#define DISPLAY(w, string) \
  valueCS = XmStringCreateLtoR(string, "ISO8859-1"); \
  i = 0; \
  XtSetArg(arg_set[i], XmNlabelString, valueCS); i++; \
  XtSetValues(w, arg_set, i); \
  XmStringFree(valueCS);

#define DISPLAYD(w, number) \
  (void) snprintf(valueD, 21, "%20.13g", number); \
  valueCS = XmStringCreateLtoR(valueD , "ISO8859-1"); \
  i = 0; \
  XtSetArg(arg_set[i], XmNlabelString, valueCS); i++; \
  XtSetValues(w, arg_set, i); \
  XmStringFree(valueCS);

#define DISPLAYI(w, number) \
  (void) snprintf(valueI, 7, "%6.6d", number); \
  valueCS = XmStringCreateLtoR(valueI, "ISO8859-1"); \
  i = 0; \
  XtSetArg(arg_set[i], XmNlabelString, valueCS); i++; \
  XtSetValues(w, arg_set, i); \
  XmStringFree(valueCS);
  
static void mrqminWithSVA(double x[], double y[], double sig[], int ndata, double a[], int ia[],
  int ma, double **covar, double **alpha, double *chisq, double *alamda)
{
  int i, j, k, l, m, rank;
  double wMin, wMax;
  
  static char valueI[7];  /*  6 characters */
  static char valueD[21]; /* 20 characters */
  static XmString  valueCS  = NULL;
  
  static int mfit, graphSet=0;
  static unsigned long *key;
  static double ochisq, *atry, *beta, *da, *wSVA, **vSVA;
  static char *eSVA;

  Arg arg_set[20];

  if (*alamda < 0.0) {
    atry = vector(1, ma);
    beta = vector(1, ma);
    da   = vector(1, ma);
    for (mfit=0,j=1; j<=ma; j++) if (ia[j]) mfit++;
    wSVA = vector(1, mfit);
    vSVA = matrix(1, mfit, 1, mfit);
    eSVA = (char *) malloc((size_t) (mfit+1)*sizeof(char));
    key  = (unsigned long *) malloc((size_t) (mfit+1)*sizeof(unsigned long));
    for (j=1; j<=mfit; j++) eSVA[j] = '1';
    *alamda = 0.001;
    mrqcofWithBounds(x, y, sig, ndata, a, ia, ma, alpha, beta, chisq);
    ochisq = (*chisq);
    for (j=1; j<=ma; j++) atry[j] = a[j];
  }
  for (j=0,l=1; l<=ma; l++) {
    if (ia[l]) {
      for (j++,k=0,m=1; m<=ma; m++) {
        if (ia[m]) {
          k++;
          covar[j][k]=alpha[j][k];
        }
      }
      covar[j][j] = alpha[j][j]*(1.0+(*alamda));
    }
  }
  /* Original call to gaussj(covar,mfit,oneda,1); removed (oneda[j][1] = beta[j]) */
  svdcmp(covar, mfit, mfit, wSVA, vSVA);
  
  if (mfit > 0) indexx(mfit, wSVA, key);
#ifdef GRACE_PIPE
  GracePrintf("WITH G2\n"); graphSet++;
  if (graphSet > 1) GracePrintf("KILL g2.s1\n");
  for (j=1; j<=mfit; j++) GracePrintf("g2.s%d POINT %lf, %g\n", 1, (double) j, (wSVA[key[mfit+1-j]] > 0.0) ? wSVA[key[mfit+1-j]] : DBL_EPSILON);
  GracePrintf("AUTOSCALE\n");
  
  GracePrintf("WITH G3\n");
  if (graphSet == 1) {
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, (double ) (mfit+1), 1.0);
    GracePrintf("XAXIS TICK MAJOR 1.0\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS TICK MAJOR 0.2\n");
    GracePrintf("YAXIS TICK MINOR 0.1\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS TICK MINOR OFF\n");

    for (j=0, k=0; j<(npc+nls+nls*(nls-1)/2); j++) {
      if (ia[3*j+1]) {
        k++;
        GracePrintf("WITH STRING\n");
        GracePrintf("STRING ON\n");
        GracePrintf("STRING LOCTYPE VIEW\n");
        GracePrintf("STRING LINEWIDTH 1\n");
        GracePrintf("STRING ROT 0\n");
        GracePrintf("STRING FONT 4\n");
        GracePrintf("STRING JUST 0\n");
        GracePrintf("STRING CHAR SIZE 0.5\n");
        GracePrintf("STRING 1.1, %lf\n", 1.0 - ((double) k)/(mfit+1.0));
        if      (k < 15) GracePrintf("STRING COLOR %d\n", k);
        else if (k < 30) GracePrintf("STRING COLOR %d\n", k-14);
        else             GracePrintf("STRING COLOR %d\n", k-29);
        GracePrintf("STRING DEF \"%1.1s %18.18s\"\n","H", modelParameters[j].label);
      }
      if (ia[3*j+1+1]) {
        k++;
        GracePrintf("WITH STRING\n");
        GracePrintf("STRING ON\n");
        GracePrintf("STRING LOCTYPE VIEW\n");
        GracePrintf("STRING LINEWIDTH 1\n");
        GracePrintf("STRING ROT 0\n");
        GracePrintf("STRING FONT 4\n");
        GracePrintf("STRING JUST 0\n");
        GracePrintf("STRING CHAR SIZE 0.5\n");
        GracePrintf("STRING 1.1, %lf\n", 1.0 - ((double) k)/(mfit+1.0));
        if      (k < 15) GracePrintf("STRING COLOR %d\n", k);
        else if (k < 30) GracePrintf("STRING COLOR %d\n", k-14);
        else             GracePrintf("STRING COLOR %d\n", k-29);
        GracePrintf("STRING DEF \"%1.1s %18.18s\"\n","S", modelParameters[j].label);
      }
      if (ia[3*j+2+1]) {
        k++;
        GracePrintf("WITH STRING\n");
        GracePrintf("STRING ON\n");
        GracePrintf("STRING LOCTYPE VIEW\n");
        GracePrintf("STRING LINEWIDTH 1\n");
        GracePrintf("STRING ROT 0\n");
        GracePrintf("STRING FONT 4\n");
        GracePrintf("STRING JUST 0\n");
        GracePrintf("STRING CHAR SIZE 0.5\n");
        GracePrintf("STRING 1.1, %lf\n", 1.0 - ((double) k)/(mfit+1.0));
        if      (k < 15) GracePrintf("STRING COLOR %d\n", k);
        else if (k < 30) GracePrintf("STRING COLOR %d\n", k-14);
        else             GracePrintf("STRING COLOR %d\n", k-29);
        GracePrintf("STRING DEF \"%1.1s %18.18s\"\n","V", modelParameters[j].label);
      }
    }
    
    for (j=0; j<nc; j++) {
      if (ia[3*(npc+nls+nls*(nls-1)/2)+3*j  +1]) {
        k++;
        GracePrintf("WITH STRING\n");
        GracePrintf("STRING ON\n");
        GracePrintf("STRING LOCTYPE VIEW\n");
        GracePrintf("STRING LINEWIDTH 1\n");
        GracePrintf("STRING ROT 0\n");
        GracePrintf("STRING FONT 4\n");
        GracePrintf("STRING JUST 0\n");
        GracePrintf("STRING CHAR SIZE 0.5\n");
        GracePrintf("STRING 1.1, %lf\n", 1.0 - ((double) k)/(mfit+1.0));
        if      (k < 15) GracePrintf("STRING COLOR %d\n", k);
        else if (k < 30) GracePrintf("STRING COLOR %d\n", k-14);
        else             GracePrintf("STRING COLOR %d\n", k-29);
        GracePrintf("STRING DEF \"%2.2s %18.18s\"\n","K'",   eosModelParameters[j].label);
      }
      if (ia[3*(npc+nls+nls*(nls-1)/2)+3*j+1+1]) {
        k++;
        GracePrintf("WITH STRING\n");
        GracePrintf("STRING ON\n");
        GracePrintf("STRING LOCTYPE VIEW\n");
        GracePrintf("STRING LINEWIDTH 1\n");
        GracePrintf("STRING ROT 0\n");
        GracePrintf("STRING FONT 4\n");
        GracePrintf("STRING JUST 0\n");
        GracePrintf("STRING CHAR SIZE 0.5\n");
        GracePrintf("STRING 1.1, %lf\n", 1.0 - ((double) k)/(mfit+1.0));
        if      (k < 15) GracePrintf("STRING COLOR %d\n", k);
        else if (k < 30) GracePrintf("STRING COLOR %d\n", k-14);
        else             GracePrintf("STRING COLOR %d\n", k-29);
        GracePrintf("STRING DEF \"%3.3s %18.18s\"\n","K''",  eosModelParameters[j].label);
      }
      if (ia[3*(npc+nls+nls*(nls-1)/2)+3*j+2+1]) {
        k++;
        GracePrintf("WITH STRING\n");
        GracePrintf("STRING ON\n");
        GracePrintf("STRING LOCTYPE VIEW\n");
        GracePrintf("STRING LINEWIDTH 1\n");
        GracePrintf("STRING ROT 0\n");
        GracePrintf("STRING FONT 4\n");
        GracePrintf("STRING JUST 0\n");
        GracePrintf("STRING CHAR SIZE 0.5\n");
        GracePrintf("STRING 1.1, %lf\n", 1.0 - ((double) k)/(mfit+1.0));
        if      (k < 15) GracePrintf("STRING COLOR %d\n", k);
        else if (k < 30) GracePrintf("STRING COLOR %d\n", k-14);
        else             GracePrintf("STRING COLOR %d\n", k-29);
        GracePrintf("STRING DEF \"%4.4s %18.18s\"\n","K'''", eosModelParameters[j].label);
      }      
    }
    
    GracePrintf("G3 ON\n");

  } else { for (k=1; k<=mfit; k++) GracePrintf("KILL g3.s%d\n", k); }
  for (k=1; k<=mfit; k++) {  
    GracePrintf("s%d TYPE BAR\n", k);
    for (j=1; j<=mfit; j++) GracePrintf("g3.s%d POINT %lf, %lf\n", k, (double) j, vSVA[k][key[mfit+1-j]]*vSVA[k][key[mfit+1-j]]);
    if (k < 15) {
      GracePrintf("s%d SYMBOL COLOR %d\n",      k, k);
      GracePrintf("s%d SYMBOL FILL COLOR %d\n", k, k);
      GracePrintf("s%d SYMBOL FILL PATTERN 1\n",   k);
    } else if (k < 30) {
      GracePrintf("s%d SYMBOL COLOR %d\n",      k, k-14);
      GracePrintf("s%d SYMBOL FILL COLOR %d\n", k, k-14);
      GracePrintf("s%d SYMBOL FILL PATTERN 10\n",     k);
    } else {
      GracePrintf("s%d SYMBOL COLOR %d\n",      k, k-29);
      GracePrintf("s%d SYMBOL FILL COLOR %d\n", k, k-29);
      GracePrintf("s%d SYMBOL FILL PATTERN 11\n",     k);
    }
    GracePrintf("s%d LINE TYPE 0\n", k);
  }
   
  GracePrintf("REDRAW\n");
#endif /* GRACE_PIPE */
  
  for (wMax=0.0, j=1; j<=mfit; j++) if (wSVA[j] > wMax) wMax = wSVA[j];
  wMin = wMax*0.00005; /* *0.001 sqrt(DBL_EPSILON); For SAK fit 0.00005 */
/*  do { */
    for (j=1, rank=mfit; j<=mfit; j++) {
      printf("--->w: %20.13e (wMin: %20.13e, wMax: %20.13e)\n", wSVA[j], wMin, wMax);
      if (wSVA[j] < wMin) { wSVA[j] = 0.0; rank--; }
    }
/*    wMin = wMin/2.0; */
/*  } while ((rank < 10) && (rank <= mfit)); */
  printf("--->In mrqmin (with SVA) computed rank is %d\n", rank);

  DISPLAYI(mrqrdtADB[2], mfit) 
  DISPLAYI(mrqrdtADB[3], rank) 
  DISPLAYD(mrqrdtADB[5], wMax) 
  if (mfit > 0) { DISPLAYD(mrqrdtADB[6], wSVA[key[1]]) }
  DISPLAYD(mrqrdtADB[7], wMin)
  
  svbksb(covar, wSVA, vSVA, mfit, mfit, beta, eSVA, da);
  
  if (*alamda == 0.0) {
    svdvar(vSVA, mfit, wSVA, covar);
    covsrt(covar, ma, ia, mfit);
    free_vector(da,   1, ma);
    free_vector(beta, 1, ma);
    free_vector(atry, 1, ma);
    free_vector(wSVA, 1, mfit);
    free_matrix(vSVA, 1, mfit, 1, mfit);
    free(eSVA);
    free(key);
    return;
  }
  
  if (XmToggleButtonGadgetGetState(mrqrdtADB[10])) return;
  
  for (j=0,l=1; l<=ma; l++) if (ia[l]) atry[l] = a[l] + da[++j];
  mrqcofWithBounds(x, y, sig, ndata, atry, ia, ma, covar, da, chisq);
  if (*chisq < ochisq) {
    *alamda *= 0.1;
    ochisq = (*chisq);
    for (j=0,l=1; l<=ma; l++) {
      if (ia[l]) {
        for (j++,k=0,m=1; m<=ma; m++) {
          if (ia[m]) {
            k++;
            alpha[j][k] = covar[j][k];
          }
        }
        beta[j] = da[j];
        a[l] = atry[l];
      }
    }
  } else {
    *alamda *= 10.0;
    *chisq = ochisq;
  }
}

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

int useTregression; /* extern in calibration.h and passed to preclb_slave.c */

typedef struct _dependent {
  double g;
  double dgdt;
} Dependent;

static Dependent delta;

static int getDependentOfSolid(double *x, double t, double p, Boolean *lowWtFlag, 
                               int solidID, int componentID, double *rSol, int useSaved) {
  int i;
  delta.g    = 0.0;
  delta.dgdt = 0.0;
 
  for (i=0; i<nlc; i++) {
    if( (solids[solidID].solToLiq)[i] != 0.0) {
      Boolean lowMolFlag;
      int j;
      for (j=0, lowMolFlag=False; j<nc; j++) lowMolFlag |= ((liquid[i].liqToOx)[j] != 0.0) && lowWtFlag[j];
      if (x[i] == 0.0 || lowMolFlag) return FALSE; 
    }
  }

  if (solidID < 0) return TRUE;
  
  if(componentID < 0) {
    gibbs(t, p, (char *) solids[solidID].label, &(solids[solidID].ref), NULL, NULL, &(solids[solidID].cur));
    delta.g += (solids[solidID].cur).g;
    if (useTregression) delta.dgdt += -(solids[solidID].cur).s;

  } else {
    static double *mu = NULL, *dmudt = NULL;
    if (!useSaved) {
      if (mu != NULL) free(mu);
      mu = (double *) malloc((size_t) solids[solidID].na*sizeof(double));
    }
    
    if (!useSaved) (*solids[solidID].activity) (SECOND | FOURTH, t, p, rSol, NULL, mu, NULL);
    if (mu[componentID] == 0.0) return FALSE;
    delta.g = mu[componentID];
    
    if (useTregression) {
      double small = sqrt(DBL_EPSILON);
      if (!useSaved) {
        if (dmudt != NULL) free(dmudt);
        dmudt = (double *) malloc((size_t) solids[solidID].na*sizeof(double));
        (*solids[solidID].activity) (SECOND | FOURTH, t*(1.0+small), p, rSol, NULL, dmudt, NULL);
      }
      if (dmudt[componentID] == 0.0) return FALSE;
      delta.dgdt = (dmudt[componentID] - mu[componentID])/small;
    }    
        
    gibbs(t, p, (char *) solids[solidID+1+componentID].label, &(solids[solidID+1+componentID].ref), 
          NULL, NULL, &(solids[solidID+1+componentID].cur));
    delta.g += (solids[solidID+1+componentID].cur).g;
    if (useTregression) delta.dgdt += -(solids[solidID+1+componentID].cur).s;
   
  }
    
  return TRUE;
}

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

static char *alternateDataBase = (char *) NULL;

int getAlternateDataBaseFile(char *fileName)
{
  if (alternateDataBase == NULL) alternateDataBase = (char *) malloc((unsigned) (strlen(fileName)+1)*sizeof(char));
  else                           alternateDataBase = (char *) REALLOC(alternateDataBase, (unsigned) (strlen(fileName)+1)*sizeof(char));

  (void) strcpy(alternateDataBase, fileName);

  return 0;
}

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

static void writeParameters(char *paramFileName)
{
  XmString valueCS = NULL;
  int i, j, k;
  time_t dateTime;

  FILE *paramFile;

  if ( (paramFile = fopen (paramFileName, "w")) == NULL) {
    valueCS = XmStringCreateLtoR("Cannot open file PARAM_STRUCT_DATA.NEW" , "ISO8859-1");
    MESSAGE(valueCS); XmStringFree(valueCS); return;
  }

  (void) time(&dateTime);

  fprintf(paramFile, "#ifndef _Param_Struct_Data_h\n");
  fprintf(paramFile, "#define _Param_Struct_Data_h\n");
  fprintf(paramFile, "\n");
  
  fprintf(paramFile, "/*\n");
  fprintf(paramFile, "**++\n");
  fprintf(paramFile, "**  FACILITY:  Silicate Melts Regression Crystallization Package\n");
  fprintf(paramFile, "**\n");
  fprintf(paramFile, "**  MODULE DESCRIPTION:\n");
  fprintf(paramFile, "**\n");
  fprintf(paramFile, "**      Include file for initializing values of liquid interaction\n");
  fprintf(paramFile, "**         parameters (file: PARAM_STRUCT_DATA.H)\n");
  fprintf(paramFile, "**\n");
  fprintf(paramFile, "**  This file produced on: %s", asctime(localtime(&dateTime)));
  fprintf(paramFile, "**--\n");
  fprintf(paramFile, "*/\n");
  fprintf(paramFile, "\n");
  fprintf(paramFile, "/*\n");
  fprintf(paramFile, " *=============================================================================\n");
  fprintf(paramFile, " * Initialize global values of interaction parameters\n");
  fprintf(paramFile, " */\n");
  fprintf(paramFile, "\n");
  fprintf(paramFile, "ModelParameters modelParameters[] = {\n");

  for (i=0, k=0; i<nls; i++) {
    if (i > 0) fprintf(paramFile,"\n"); 
    for (j=i+1; j<nls; j++, k++) {
      fprintf(paramFile,"  { \"W(%-10.10s,%-10.10s)\",", liquid[j].label, liquid[i].label);
      fprintf(paramFile,"%10.1f,%10.1f,%10.6f, %s, %s, %s, %s }", modelParameters[k].enthalpy, modelParameters[k].entropy, modelParameters[k].volume, 
	modelParameters[k].activeH ? " TRUE" : "FALSE", modelParameters[k].activeS ? " TRUE" : "FALSE", 
	modelParameters[k].activeV ? " TRUE" : "FALSE", modelParameters[k].activeF ? " TRUE" : "FALSE");
      fprintf(paramFile,", /* %3.3d %-17.17s */\n", k, (j < nlc) ? "Basis species" : "Dependent species");
      if (j == (nlc-1)) fprintf(paramFile,"\n");
    }
  }
  
  for (i=0; i<nls; i++, k++) {
    fprintf(paramFile,"  { \"%-24.24s\",", liquid[i].label);
    fprintf(paramFile,"%10.1f,%10.1f,%10.6f, %s, %s, %s, %s }", modelParameters[k].enthalpy, modelParameters[k].entropy, modelParameters[k].volume, 
      modelParameters[k].activeH ? " TRUE" : "FALSE", modelParameters[k].activeS ? " TRUE" : "FALSE", 
      modelParameters[k].activeV ? " TRUE" : "FALSE", modelParameters[k].activeF ? " TRUE" : "FALSE");
    fprintf(paramFile,", /* %3.3d %17.17s */\n", k, (i < nlc) ? "Basis species" : "Dependent species");
    if (i == (nlc-1)) fprintf(paramFile,"\n");
  }  
  
  fprintf(paramFile,"\n");  

  for (i=0; i<npc; i++, k++) {
    fprintf(paramFile,"  { \"%-24.24s\",", solids[i].label);
    fprintf(paramFile,"%10.1f,%10.1f,%10.6f, %s, %s, %s, %s }", modelParameters[k].enthalpy, modelParameters[k].entropy, modelParameters[k].volume, 
      modelParameters[k].activeH ? " TRUE" : "FALSE", modelParameters[k].activeS ? " TRUE" : "FALSE", 
      modelParameters[k].activeV ? " TRUE" : "FALSE", modelParameters[k].activeF ? " TRUE" : "FALSE");
    fprintf(paramFile,"%c /* %3.3d %17.17s */\n", (i < (npc-1)) ? ',' : ' ', k, (solids[i].type == PHASE) ? "Solid Phase" : "Solid Component");
  }    

  fprintf(paramFile, "};\n");
  fprintf(paramFile, "\n");
    
  fprintf(paramFile, "EosModelParameters eosModelParameters[] = {\n");
#ifdef BUILD_MGO_SIO2_VERSION
  for (i=0; i<nc; i++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
  for (i=0; i<nc; i++) {
#else
  for (i=0; i<(nc+1); i++) {
#endif
    fprintf(paramFile,"  { \"%-24.24s\",", bulkSystem[i].label);
    fprintf(paramFile,"%13.6e,%13.6e,%13.6e, %s, %s, %s, %13.6e,%13.6e,%13.6e }", eosModelParameters[i].Kp, eosModelParameters[i].Kpp, 
      eosModelParameters[i].Kppp, eosModelParameters[i].activeKp ? " TRUE" : "FALSE", eosModelParameters[i].activeKpp ? " TRUE" : "FALSE", 
      eosModelParameters[i].activeKppp ? " TRUE" : "FALSE", eosModelParameters[i].v2, eosModelParameters[i].v3, eosModelParameters[i].v4);
    fprintf(paramFile,"%c /* %3.3d %17.17s */\n", (i < (nc-1)) ? ',' : ' ', i, "EOS: K', K'', K''', v2, v3, v4");
  }    
  fprintf(paramFile, "};\n");
  fprintf(paramFile, "\n");
  
  fprintf(paramFile, "#endif /* _Param_Struct_Data_h */\n");

  fclose(paramFile);
}

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

#define REC   134     /* Maximal record length for data file reads */

#define ABORT(string1, string2) \
  cstring1 = XmStringCreateLtoR(string1, "ISO8859-1"); \
  cstring2 = XmStringCreateLtoR(string2, "ISO8859-1"); \
  cstring3 = XmStringConcat(cstring1, cstring2); \
  i = 0; \
  XtSetArg(arg_set[i], XmNmessageString, cstring3); i++; \
  XtSetValues(message, arg_set, i); \
  XtManageChild(message); \
  XmStringFree(cstring1); \
  XmStringFree(cstring2); \
  XmStringFree(cstring3);
  

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

#include <libxml/encoding.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>
#include <libxml/xmlwriter.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#ifndef __MSDOS__
#define DIR_DELIM "/"
#else
#define DIR_DELIM "\\"
#endif

Boolean preclb(XtPointer client_data)
{
  static char value[6];   /*  5 characters */
  static char valueI[7];  /*  6 characters */
  static char valueD[21]; /* 20 characters */
  static XmString  valueCS  = NULL, cstring1 = NULL, cstring2 = NULL, cstring3 = NULL;

  /* Variables and definitions dependent on database structure */
  static char    **oxNamesLC = NULL;
  static int     ma, *iaMrqrdt, loop, o2Index, nrMAX, nParam, H2Oindex = -1, CO2index = -1; 
  static Boolean oneBarOnly, lowPonly, highPonly, anhydrousOnly, hydrousOnly, calibrateOxygen, useTrustRegionMethod, 
                 implementBounds;
  static Boolean *lowWtFlag, *zeroWtFlag, *phasesPresent, validLiquid=FALSE;
  static double  molesElmSol[107], *molesLiqCmp, *moles, *indep, *activity, *xMrqrdt, *yMrqrdt, *sigMrqrdt, *aMrqrdt, 
    **covar, **alpha, chisq, alamda, oldChisq, oldAlamda, t, p, logfo2, *sigWeights, *wt;

  enum steps { INITIAL, READING, PREREGRESS, REGRESS, POSTREGRESS, SOLUTION, FINAL };
  static int curStep = 0;
  static ResidualDataInput *pRDI;
  static ResidualOutput    *pRO;
  
  static xmlSchemaPtr schema = NULL;
  static xmlSchemaParserCtxtPtr ctxt = NULL;
  static xmlSchemaValidCtxtPtr ctxt2 = NULL;
  static xmlDocPtr doc = NULL;
  static xmlNode *root_element = NULL;
  static xmlNode *level1;
  
  static FILE *liqFile;


  WorkProcData *workProcData = (WorkProcData *) client_data;

  int i, j, k, l, id;
  double hORsORdCON=0.0;
  Arg arg_set[20];

  switch(curStep) {

/*=============================================================================
 * If the work procedure is being called for the first time, the data file
 * must be opened and some initialization of global and static variables 
 * must take place.
 *===========================================================================*/

  case INITIAL:

  if (doc == NULL) { 
    /* 1-> attempt to open the data file */ 
    if (alternateDataBase == (char *) NULL) {
      ABORT("Please specify an XML database file first using the Commands/Open... menu item.\n", "Exiting PRECLB procedure.")
      workProcData->active = FALSE; return TRUE;
    } else {   
      ctxt = xmlSchemaNewParserCtxt("LEPRdatabase.xsd");
      xmlSchemaSetParserErrors(ctxt,(xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr); 
      schema = xmlSchemaParse(ctxt);

      if (schema != NULL) {
        xmlSchemaFreeParserCtxt(ctxt);
        ctxt2 = xmlSchemaNewValidCtxt(schema);
        xmlSchemaSetValidErrors(ctxt2,(xmlSchemaValidityErrorFunc) fprintf,(xmlSchemaValidityWarningFunc) fprintf, stderr);
        doc = xmlReadFile(alternateDataBase, NULL, 0);
        if (doc) {
          if (xmlSchemaValidateDoc(ctxt2, doc)) {
            ABORT("XML database file is invalid against schema LEPRdatabase.xsd.\n", "Exiting PRECLB procedure.")
            xmlFreeDoc(doc); doc = NULL; workProcData->active = FALSE; return TRUE;
          } else {
            root_element = xmlDocGetRootElement(doc);
            level1 = root_element->children;
            DISPLAY(actionADB[0], "XML database file has been validated against schema LEPRdatabase.xsd.")
          }
          
        } else {
          ABORT("XML database file cannot be opened.\n", "Exiting PRECLB procedure.")
          workProcData->active = FALSE; return TRUE;
        }
  
      } else {
        ABORT("No schema file found! (LEPRdatabase.xsd does not exist).\n", "Exiting PRECLB procedure.")
        workProcData->active = FALSE; return TRUE;
      }
    }

    /* 3 -> allocate space and initialize for static arrays */
    if (molesLiqCmp   == NULL) molesLiqCmp   = (double *)  malloc((size_t) nlc*sizeof(double)); 
    if (lowWtFlag     == NULL) lowWtFlag     = (Boolean *) malloc((size_t)  nc*sizeof(Boolean)); 
    if (zeroWtFlag    == NULL) zeroWtFlag    = (Boolean *) malloc((size_t)  nc*sizeof(Boolean)); 
    if (phasesPresent == NULL) phasesPresent = (Boolean *) malloc((size_t) npc*sizeof(Boolean));
    for (i=0; i<npc; i++) { phasesPresent[i] = TRUE; preclbCount[i].np = 0; preclbCount[i].na = 0; }

    /* 4a -> compute maximal number of endmembers in any known solid solution, 
             and allocate an appropriate vectors for comp and activities     */
    for (i=0, j=1; i<npc; i++) j = MAX(j, solids[i].na);
    if (moles    == NULL) moles    = (double *) malloc((size_t) j*sizeof(double));
    if (activity == NULL) activity = (double *) malloc((size_t) j*sizeof(double));

    /* 4b -> compute maximal number of independent compositional variables in
             any known solid solution, and allocate an appropriate vector    */
    for (i=0, j=1; i<npc; i++) j = MAX(j, solids[i].nr);
    if (indep == NULL) indep = (double *) malloc((size_t) j*sizeof(double));
    nrMAX = j;

    /* 4c -> Get Pressure exclusion options                                  */
    oneBarOnly  = XmToggleButtonGadgetGetState(tg_1_bar_only);
    if (oneBarOnly) printf("Experiments above 1 bar will be excluded.\n");
    lowPonly  = XmToggleButtonGadgetGetState(tg_low_p_only);
    if (lowPonly) printf("High P (> 4 GPa) experiments will be excluded.\n");
    highPonly = XmToggleButtonGadgetGetState(tg_high_p_only);
    if (highPonly) printf("Low P (< 4 GPa) experiments will be excluded.\n");

    /* 4d -> Get hydrous/anhydrous exclusion options                         */
    anhydrousOnly = XmToggleButtonGadgetGetState(tg_anhydrous_only);
    if (anhydrousOnly) printf("Hydrous experiments will be excluded.\n");
    hydrousOnly = XmToggleButtonGadgetGetState(tg_hydrous_only);
    if (hydrousOnly) printf("Anhydrous experiments will be excluded.\n");
    
    /* 4e -> Get oxygen constraint calibration option                       */
    for (j=0, o2Index = -1; j<npc; j++) if ((solids[j].type == PHASE) && !strcmp(solids[j].label, "o2")) { o2Index = j; break; }
    if((calibrateOxygen = XmToggleButtonGadgetGetState(tg_oxygen_calib))) {
      if (o2Index == -1) calibrateOxygen = FALSE;
      if (calibrateOxygen) printf("O2 chemical potential calibration statements will be included.\n");
    }
    
    /* 4f -> Get Regression method and constraint settings                  */
    useTrustRegionMethod = XmToggleButtonGadgetGetState(tg_trust_region_method);
    if (useTrustRegionMethod) printf("Regression method set to Trust Region algorithm.\n");
    implementBounds = XmToggleButtonGadgetGetState(tg_implement_bounds);
    if (implementBounds) printf("Bounds on W(H) parameters will be implemented.\n");
    useTregression = XmToggleButtonGadgetGetState(tg_t_regression);
    if (useTregression) printf("Optimization will be performed on T rather than energy.\n");

    /* 5a -> compute number of moles of elements in each solid              */
    sigWeights = (double *) calloc((size_t) (npc+nes), sizeof(double));
    for (i=0; i<npc; i++) for (j=0; j<107; j++) for (k=0; k<nc; k++) sigWeights[i] += (solids[i].solToOx)[k]*(bulkSystem[k].oxToElm)[j];

    /* 5b -> parse and determine conversion vectors for extra solid species */
    for(i=0; i<nes; i++) {
      extraSolids[i].index = -1;
      for (j=0; j<npc; j++) if ((solids[j].type == PHASE) && (solids[j].convert != NULL) && !strcmp(solids[j].label, extraSolids[i].phase)) { 
        extraSolids[i].index = j; break; 
      }
      if (extraSolids[i].index != -1) {
        for (j=0; j<107; j++) molesElmSol[j] = 0.0;
        (void) formulaToMwStoich((char *) extraSolids[i].formula, molesElmSol);
	for (j=0,extraSolids[i].nAtoms=0.0; j<107; j++) extraSolids[i].nAtoms += molesElmSol[j];
        extraSolids[i].oxygen = molesElmSol[8]; 		   /* moles of oxygen	*/
        for (j=0; j<107; j++) sigWeights[npc+i] += molesElmSol[j]; /* moles of elements */
 
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
     
    /* 6-> initialize remaining statics */
    nEqn = 0;
    nLiquid = 0;
    for (i=0, nParam=0; i<(nls*(nls-1)/2+nls+npc); i++) { 
      if(modelParameters[i].activeH) nParam++;
      if(modelParameters[i].activeS) nParam++;
      if(modelParameters[i].activeV) nParam++;
    } 
#ifdef BUILD_MGO_SIO2_VERSION
    for (i=0; i<nc; i++) { 
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
    for (i=0; i<nc; i++) { 
#else
    for (i=0; i<(nc+1); i++) { 
#endif
      if(eosModelParameters[i].activeKp)   nParam++;
      if(eosModelParameters[i].activeKpp)  nParam++;
      if(eosModelParameters[i].activeKppp) nParam++;
    } 
    if (oxNamesLC == NULL) oxNamesLC = (char **) malloc((size_t) nc*sizeof(char *));
    for (i=0; i<nc; i++) {
      int len = strlen(bulkSystem[i].label);
      oxNamesLC[i] = (char *) malloc((size_t) (len+1)*sizeof(char));
      for (j=0; j<len; j++) oxNamesLC[i][j] = tolower((bulkSystem[i].label)[j]);
      oxNamesLC[i][len] = '\0';
      if      (!strcmp(oxNamesLC[i], "h2o")) H2Oindex = i;
      else if (!strcmp(oxNamesLC[i], "co2")) CO2index = i;
    }
    if (wt == NULL) wt = (double *) malloc((size_t) nc*sizeof(double));
       
  }

  if ( (liqFile = fopen ("liqList.res", "w")) == NULL) {
    valueCS = XmStringCreateLtoR("Cannot open file liqList.res", "ISO8859-1");
    MESSAGE(valueCS); XmStringFree(valueCS); workProcData->active = FALSE; 
    return(TRUE);
  }
  fprintf(liqFile,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", 
    "liq N", "Name", "Author", "Device", "Container", "Method", "T (C)", "P (GPa)", "log fO2");

  curStep++;
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Continue reading and processing the data file:
 *===========================================================================*/

  case READING:
  
  if (level1 != NULL) {
    if (level1->type == XML_ELEMENT_NODE) {
      xmlChar *content1 = xmlNodeGetContent(level1);
      
      if (!strcmp((char *) level1->name, "experiment")) {
	xmlNode *level2 = level1->children;
	int flagPC   = FALSE; /* flags for device type */
	int flagMA   = FALSE;
	int flagCSPV = FALSE;
	int flagIHPV = FALSE;
	int flagC    = FALSE; /* flags for container type */
	int flagPtC  = FALSE;
	int flagFe   = FALSE;
	int flagFePt = FALSE;
	int flagRe   = FALSE;
	int LEPRnum  = 0;
	char name[21], author[21], device[11], container[11], method[11];
	
	t = -9999.0; p = -9999.0; logfo2 = -9999.0;
	for (i=0; i<21;i++) { name[i] = ' '; author[i] = ' '; }
	name[20] = '\0'; author[20] = '\0';
	for (i=0; i<11;i++) { device[i] = ' '; container[i] = ' '; method[i] = ' '; }
	device[10] = '\0'; container[10] = '\0'; method[10] = '\0';

	while (level2 != NULL) {
	  if (level2->type == XML_ELEMENT_NODE) {
	    xmlChar *content2 = xmlNodeGetContent(level2);
	    
	    if      (!strcmp((char *) level2->name, "number" )) LEPRnum = atoi((char *) content2);
	    
	    else if (!strcmp((char *) level2->name, "name"   )) { 
	      (void) strncpy(name, (char *) content2, 20); 
	      DISPLAY(actionADB[1], (char *) content2) 
	    }
	    
	    else if (!strcmp((char *) level2->name, "author"    )) (void) strncpy(author, (char *) content2, 20);
	    
	    else if (!strcmp((char *) level2->name, "device"    )) {
	      (void) strncpy(device,    (char *) content2, 10);
	      if      (!strcmp((char *) content2, "PC"  )) flagPC   = TRUE;
	      else if (!strcmp((char *) content2, "MA"  )) flagMA   = TRUE;
	      else if (!strcmp((char *) content2, "CSPV")) flagCSPV = TRUE;
	      else if (!strcmp((char *) content2, "IHPV")) flagIHPV = TRUE;
	    }
	      
	    else if (!strcmp((char *) level2->name, "container" )) {
	      (void) strncpy(container, (char *) content2, 10);
	      if      (!strcmp((char *) content2, "C"   )) flagC    = TRUE;
	      else if (!strcmp((char *) content2, "PtC" )) flagPtC  = TRUE;
	      else if (!strcmp((char *) content2, "Fe"  )) flagFe   = TRUE;
	      else if (!strcmp((char *) content2, "FePt")) flagFePt = TRUE;
	      else if (!strcmp((char *) content2, "Re"  )) flagRe   = TRUE;
	    }
	    
	    else if (!strcmp((char *) level2->name, "method"    )) (void) strncpy(method,(char *) content2, 10);
	    
	    else if (!strcmp((char *) level2->name, "t"      )) t = atof((char *) content2) + 273.15; /* K    */
	    else if (!strcmp((char *) level2->name, "p"      )) p = atof((char *) content2)*10000.0;  /* bars */
	    else if (!strcmp((char *) level2->name, "fo2val" )) logfo2 = atof((char *) content2);	    
	    
	    else if (!strcmp((char *) level2->name, "liquid" )) { /* at this point t and p are defined */
	      xmlNode *level3 = level2->children;
	      for (i=0; i<nc; i++) wt[i] = 0.0;
	      while (level3 != NULL) {
	        if (level3->type == XML_ELEMENT_NODE) {
	          xmlChar *content3 = xmlNodeGetContent(level3);
		  for (i=0; i<nc; i++) if (!strcmp((char *) level3->name, oxNamesLC[i])) {
		    wt[i] = atof((char *) content3);
		    break;
		  }
		  if (content3 != NULL) xmlFree(content3);
		}
		level3 = level3->next;
	      }

              /********************************************************************/	      
	      /* Process liquid data in order to determine if this entry is valid */
	      /********************************************************************/

#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
              if (wt[0] == 0.0) { /* No silica in the system, experiments in Na2O-Al2O3 */
	        double corrSiO2 = 3.0;                              /* wt % */
		double pseudo = (wt[1] != 0.0) ? wt[3]/wt[1] : 0.0; /* Na2O/Al2O3: There should NEVER be zero Al2O3 */
		double corrAl2O3 = (100.0 - corrSiO2)/(1.0+pseudo);
		double corrNa2O = pseudo*corrAl2O3;
		wt[0] = corrSiO2;
		wt[1] = corrAl2O3;
		wt[3] = corrNa2O;
	      }
#endif
	      
              /* Convert wt % oxides to mole fractions of liquid components          */
              for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;
      
#ifdef BUILD_MGO_SIO2_VERSION
              for (i=0; i<nc; i++)  lowWtFlag[i] = FALSE;
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
              for (i=0; i<nc; i++)  lowWtFlag[i] = FALSE;
#else
#ifndef RHYOLITE_ADJUSTMENTS
              if (p > 50000.0) logfo2 = -9999.0; /* kill previous estimate of log fo2 from LEPR for high P experiments */
	      if ((LEPRnum >= 150001) && (LEPRnum <= 150312)) logfo2 = -9999.0; /* recalculate the log fO2s for all "density" constraints */
#endif
	      
              if (logfo2 == -9999.0 && (flagPC || flagMA) && (flagC || flagPtC)) {
	        /*
		 * The maximum log fO2 is acheived at a pressure of 6.7021 GPa.
		 *   Above that p use Andy Cambell's correction for IW buffer
		 */
	        logfo2 = getlog10fo2(t, (p < 67201.0) ? p : 67201.0, FO2_COH);
		if (p > 67201.0) logfo2 += 608.966*(p/10000.0)/t - 608.966*(67201.0/10000.0)/t;
		printf("%s [%s] %s %s --> fO2 for t = %f and p = %f computed to be %f\n", author, name, device, container, t, p, logfo2);
		
	      } else if (logfo2 == -9999.0 && (flagFe || flagFePt)) {
	        logfo2 = getlog10fo2(t, 1.0, FO2_IW) - 2.0 + 608.966*(p/10000.0)/t; /* Andy Campbell's pressure correction */
		printf("%s [%s] %s %s --> fO2 for t = %f and p = %f computed to be %f\n", author, name, device, container, t, p, logfo2);
		
	      } else if (logfo2 == -9999.0 && flagRe) { 
	        /* logfo2  = (-451020.0 + 297.595*t - 14.6585*t*log(t))/(8.3143*t*log(10.0)); */ /* good 850-1250 K */
		/* logfo2  = getlog10fo2(t, 1.0, FO2_IW) + 1.5; */ /* Tim Grove's suggestion */
	        logfo2 = getlog10fo2(t, (p < 67201.0) ? p : 67201.0, FO2_COH); /* Assume that there are carbon heaters */
		if (p > 67201.0) logfo2 += 608.966*(p/10000.0)/t - 608.966*(67201.0/10000.0)/t; /* Andy Campbell's pressure correction for IW */
		printf("%s [%s] %s %s --> fO2 for t = %f and p = %f computed to be %f\n", author, name, device, container, t, p, logfo2);
		
	      } else if (logfo2 == -9999.0 && (flagPC || flagMA)) {
	        logfo2 = getlog10fo2(t, (p < 67201.0) ? p : 67201.0, FO2_COH); /* Pure guess */
		if (p > 67201.0) logfo2 += 608.966*(p/10000.0)/t - 608.966*(67201.0/10000.0)/t; /* Andy Campbell's pressure correction for IW */
		printf("%s [%s] %s %s --> fO2 for t = %f and p = %f computed to be %f\n", author, name, device, container, t, p, logfo2);
		
	      } else if (logfo2 == -9999.0 && (flagCSPV || flagIHPV)) {
	        logfo2 = getlog10fo2(t, 1.0, FO2_NNO) + 2.5 + 0.046*(p-1.0)/t;  /* Frost pressure correction */
		printf("%s [%s] %s %s --> fO2 for t = %f and p = %f computed to be %f\n", author, name, device, container, t, p, logfo2);
		
	      } else if (logfo2 == -9999.0 && wt[3] == 0.0 && wt[5] == 0.0) { /* No iron in liquid */
	        logfo2 = getlog10fo2(t, 1.0, FO2_QFM);
		printf("%s [%s] %s %s --> fO2 for t = %f and p = %f cannot be computed, but No Fe in liquid. Set to QFM.\n", author, name, device, container, t, p);

	      } else if (logfo2 == -9999.0) {
		printf("%s [%s] %s %s --> fO2 for t = %f and p = %f cannot be computed\n", author, name, device, container, t, p);
	      }
	      {
	        double fo2air = -0.68 + ((p > 0.0) ? log(p)/log(10.0) : 0.0);
	        if (logfo2 > fo2air) logfo2 = fo2air; /* Constrain the log fO2 to be at or below air at P */
	      }
#ifndef RHYOLITE_ADJUSTMENTS
              if ((logfo2 != -9999.0) && (LEPRnum < 90000)) { /* 90000 and above are ferrc-ferrous calibration experiments */
	        conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL, NULL, NULL, &logfo2); /* FeO(T) -> Fe2O3, FeO */
                for (i=0; i<nc; i++)  lowWtFlag[i] = (wt[i]*bulkSystem[i].mw < 0.5);
                lowWtFlag[3] = (wt[3]*bulkSystem[3].mw < 0.1); /* Fe2O3 */
                lowWtFlag[4] = (wt[4]*bulkSystem[4].mw < 0.1); /* Cr2O3 */
	      } else for (i=0; i<nc; i++)  lowWtFlag[i] = FALSE;
#else
              for (i=0; i<nc; i++)  lowWtFlag[i] = FALSE;
#endif
#endif
    
              for (i=0; i<nc; i++) zeroWtFlag[i] = (wt[i] <= 0.0); 
              for (i=0; i<nlc; i++) for (j=0, molesLiqCmp[i]=0.0; j<nc; j++) molesLiqCmp[i] += wt[j]*(bulkSystem[j].oxToLiq)[i];
	      
#ifndef BUILD_MGO_SIO2_VERSION
#ifndef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
#ifndef RHYOLITE_ADJUSTMENTS
              /* Here is where experiments are excluded by LEPRnum.  Exclusion is accomplished by setting logfo2 back to -9999.0 */
	      if ( (LEPRnum >=    37) && (LEPRnum <=    37) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=    41) && (LEPRnum <=    41) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=   595) && (LEPRnum <=   596) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=   599) && (LEPRnum <=   599) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=   609) && (LEPRnum <=   611) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=   620) && (LEPRnum <=   622) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=   630) && (LEPRnum <=   633) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=   640) && (LEPRnum <=   640) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=   643) && (LEPRnum <=   644) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=   647) && (LEPRnum <=   648) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=   841) && (LEPRnum <=   894) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=   896) && (LEPRnum <=   967) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  1360) && (LEPRnum <=  1385) ) logfo2 = -9999.0; /* Purtirka (2003)		  */
	      if ( (LEPRnum >=  1702) && (LEPRnum <=  1707) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  1709) && (LEPRnum <=  1709) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  1712) && (LEPRnum <=  1715) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  1721) && (LEPRnum <=  1724) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  1897) && (LEPRnum <=  1914) ) logfo2 = -9999.0; /* Pure SiO2-H2O   		  */
	      if ( (LEPRnum >=  1965) && (LEPRnum <=  1966) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  1970) && (LEPRnum <=  1973) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  1997) && (LEPRnum <=  2008) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2003) && (LEPRnum <=  2008) ) logfo2 = -9999.0; /* Green et al. (2004)  	  */
	      if ( (LEPRnum >=  2314) && (LEPRnum <=  2314) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2316) && (LEPRnum <=  2317) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2319) && (LEPRnum <=  2320) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2322) && (LEPRnum <=  2325) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2327) && (LEPRnum <=  2327) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2329) && (LEPRnum <=  2331) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2333) && (LEPRnum <=  2335) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2337) && (LEPRnum <=  2339) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2341) && (LEPRnum <=  2343) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2345) && (LEPRnum <=  2347) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2349) && (LEPRnum <=  2351) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2353) && (LEPRnum <=  2355) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2357) && (LEPRnum <=  2359) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2361) && (LEPRnum <=  2363) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2365) && (LEPRnum <=  2367) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2369) && (LEPRnum <=  2370) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2372) && (LEPRnum <=  2374) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2376) && (LEPRnum <=  2378) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2380) && (LEPRnum <=  2382) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2384) && (LEPRnum <=  2385) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2387) && (LEPRnum <=  2389) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2391) && (LEPRnum <=  2392) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2394) && (LEPRnum <=  2394) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2395) && (LEPRnum <=  2395) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=  2396) && (LEPRnum <=  2398) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2531) && (LEPRnum <=  2531) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2533) && (LEPRnum <=  2534) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2536) && (LEPRnum <=  2537) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2540) && (LEPRnum <=  2542) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2544) && (LEPRnum <=  2544) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2546) && (LEPRnum <=  2547) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2804) && (LEPRnum <=  2841) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2831) && (LEPRnum <=  2864) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2844) && (LEPRnum <=  2844) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2848) && (LEPRnum <=  2849) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2852) && (LEPRnum <=  2854) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2856) && (LEPRnum <=  2858) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2860) && (LEPRnum <=  2860) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2862) && (LEPRnum <=  2864) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2867) && (LEPRnum <=  2896) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2900) && (LEPRnum <=  2903) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2912) && (LEPRnum <=  2913) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2916) && (LEPRnum <=  2918) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2928) && (LEPRnum <=  2928) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2933) && (LEPRnum <=  2934) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  2993) && (LEPRnum <=  2998) ) logfo2 = -9999.0; /* CO2 bearing                    */
	      if ( (LEPRnum >=  2999) && (LEPRnum <=  3002) ) logfo2 = -9999.0; /* CO2 bearing  		  */
	      if ( (LEPRnum >=  3242) && (LEPRnum <=  3242) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	    /*if ( (LEPRnum >=  3386) && (LEPRnum <=  3400) ) logfo2 = -9999.0;*/ /* Draper et al. (2003) 	  */
	      if ( (LEPRnum >=  3759) && (LEPRnum <=  3761) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=  3763) && (LEPRnum <=  3766) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=  3769) && (LEPRnum <=  3769) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=  3775) && (LEPRnum <=  3781) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	    /*if ( (LEPRnum >=  3804) && (LEPRnum <=  3818) ) logfo2 = -9999.0;*/ /* Mibe 			  */
	      if ( (LEPRnum >=  5297) && (LEPRnum <=  5297) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=  5302) && (LEPRnum <=  5302) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=  5305) && (LEPRnum <=  5305) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=  5310) && (LEPRnum <=  5310) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=  5316) && (LEPRnum <=  5316) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=  5320) && (LEPRnum <=  5320) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >=  5324) && (LEPRnum <=  5324) ) logfo2 = -9999.0; /* H2O bearing, no water in liquid*/
	      if ( (LEPRnum >= 12071) && (LEPRnum <= 12074) ) logfo2 = -9999.0; /* CO2 bearing                    */
	      if ( (LEPRnum >= 30234) && (LEPRnum <= 30255) ) logfo2 = -9999.0; /* CO2 bearing                    */
	      
	      if (p == 0.0) logfo2 = -9999.0; /* Bad entry */
#endif
#endif
#endif

              /* Do tests on liquid composition and store valid liquid entry */
#ifdef BUILD_MGO_SIO2_VERSION
              if (testLiq(SIXTH, t, p, 0, 0, NULL, NULL, NULL, molesLiqCmp)) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
              if (testLiq(SIXTH, t, p, 0, 0, NULL, NULL, NULL, molesLiqCmp)) {
#else                                                                                                 /* must have SiO2 */
              if ((logfo2 != -9999.0) && testLiq(SIXTH, t, p, 0, 0, NULL, NULL, NULL, molesLiqCmp) && !zeroWtFlag[0]) {
#endif
        	static double *xSpecies; if (xSpecies == NULL) xSpecies = (double *) malloc((size_t) nls*sizeof(double));

        	nLiquid++;
        	residualDataInput = (ResidualDataInput *) REALLOC(residualDataInput, (size_t) nLiquid*sizeof(struct _residualDataInput));
        	pRDI	        = &(residualDataInput[nLiquid-1]);
        	pRDI->LEPRnum   = LEPRnum;
        	pRDI->t         = t;
        	pRDI->p         = p;
        	pRDI->fo2       = logfo2;
        	pRDI->nLiq      = 1; /* Check against nLiqCoexistMax */
        	pRDI->rLiq      = (double **) malloc(sizeof(double *));
               (pRDI->rLiq)[0]  = (double *) malloc((size_t) (nlc-1)*sizeof(double));
        	pRDI->nSol      = 0;
        	pRDI->pIndex    = NULL;  
        	pRDI->cIndex    = NULL;  
        	pRDI->rSol      = NULL;  
        	pRDI->pIndex    = NULL;  
        	pRDI->isEqual   = NULL;  
        	pRDI->depenG    = NULL;  
        	pRDI->dependGdT = NULL;  

        	residualOutput  = (ResidualOutput *) REALLOC(residualOutput, (size_t)  nLiquid*sizeof(struct _residualOutput));
        	pRO = &(residualOutput[nLiquid-1]);
        	pRO->flag      = 1;
        	pRO->residuals = NULL;
        	pRO->dr        = NULL;

        	validLiquid = TRUE;
        	conLiq(SECOND, THIRD,		t, p, NULL, molesLiqCmp, (pRDI->rLiq)[0], NULL,     NULL, NULL, NULL);
        	conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL,	 (pRDI->rLiq)[0], xSpecies, NULL, NULL, NULL);

        	if (!testLiq(SEVENTH,0, 0, 0, 0, NULL, NULL, NULL, NULL)) { 
        	  validLiquid = FALSE;
        	  printf("-->Liquid %d fails ordering test.\n", nLiquid);
        	  nLiquid--;
        	} else {
        	  double gTest;
        	  gmixLiq(FIRST, t, p, (pRDI->rLiq)[0], &gTest, NULL, NULL);
        	  if (!testLiq(EIGHTH, 0, 0, 0, 0, NULL, NULL, NULL, NULL)) {
        	    validLiquid = FALSE;
        	    printf("-->Liquid %d causes failure (%d) in EOS algorithm.\n", nLiquid, liqERRstate);
        	    nLiquid--;
        	  }
        	}
              } else {
        	validLiquid = FALSE;
        	printf("-->Liquid %d fails validation test.logfO2 = %g, test = %d\n", nLiquid, logfo2,
		  testLiq(SIXTH, t, p, 0, 0, NULL, NULL, NULL, molesLiqCmp));
              }
              
              /* Insert an equation for oxygen calibration if liquid is valid composition */
              if (  validLiquid
        	    && calibrateOxygen
        	    && ((lowPonly   && (p < 100000.0)) || !lowPonly) 
		    && ((highPonly  && (p > 100000.0)) || !highPonly) 
		    && ((oneBarOnly && (p < 2.0))      || !oneBarOnly)
#ifndef BUILD_MGO_SIO2_VERSION
#ifndef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION

                    && ((anhydrousOnly && (molesLiqCmp[18] == 0.0)) || !anhydrousOnly) 
	            && ((hydrousOnly   && (molesLiqCmp[18] > 0.0))  || !hydrousOnly)
#endif
#endif
                 ) {
 		if(getDependentOfSolid(molesLiqCmp, t, p, lowWtFlag, o2Index, -1, NULL, FALSE)) {
 		   ResidualDataInput *pRDI = &(residualDataInput[nLiquid-1]);
 		   nEqn++;
 		   pRDI->nSol++; if (pRDI->nSol > nSolCoexistMax) 
 				 printf("ERROR:preclb[preclb.c at line %d] nSolCoexistMax[=%d] exceeded.\n", __LINE__, nSolCoexistMax);
 		   pRDI->pIndex  = (int *)     REALLOC(pRDI->pIndex, (size_t) (pRDI->nSol)*sizeof(int));
 		   pRDI->cIndex  = (int *)     REALLOC(pRDI->cIndex, (size_t) (pRDI->nSol)*sizeof(int));
 		   pRDI->rSol	 = (double **) REALLOC(pRDI->rSol,   (size_t) (pRDI->nSol)*sizeof(double *));
 		   pRDI->isEqual = (int *)     REALLOC(pRDI->isEqual,(size_t) (pRDI->nSol)*sizeof(int));
 		   pRDI->depenG  = (double *)  REALLOC(pRDI->depenG, (size_t) (pRDI->nSol)*sizeof(double));
		   if (useTregression) pRDI->dependGdT = (double *)  REALLOC(pRDI->dependGdT, (size_t) (pRDI->nSol)*sizeof(double));
 		  (pRDI->pIndex) [pRDI->nSol-1] = o2Index;
 		  (pRDI->cIndex) [pRDI->nSol-1] = o2Index; 
 		  (pRDI->isEqual)[pRDI->nSol-1] = TRUE;
 		  (pRDI->depenG) [pRDI->nSol-1] = (delta.g + R*t*log(10.0)*logfo2)/SCALE;
		   if (useTregression) (pRDI->dependGdT) [pRDI->nSol-1] = (delta.dgdt + R*log(10.0)*logfo2)/SCALE;
 		  (pRO->residuals) = (double *) REALLOC(pRO->residuals, (size_t)	(pRDI->nSol)*sizeof(double));
 		  (pRO->dr)	   = (double *) REALLOC(pRO->dr,	(size_t) nParam*(pRDI->nSol)*sizeof(double));
 		}      
 	      }
	      
	      if (validLiquid)   fprintf(liqFile,"%d\t%s\t%s\t%s\t%s\t%s\t%g\t%g\t%g\n", 
	        nLiquid-1, name, author, device, container, method, t-273.15, p/10000.0, logfo2);


	      /* This is the end of all liquid processing */
	    } else if (!strcmp((char *) level2->name, "phase" )) {
	      char *phaseNameXML = (char *) xmlGetProp(level2, (unsigned char *) "type");
	      char *phaseName;
	      int deRef = FALSE;
	      int bypass = FALSE;
	      xmlNode *level3 = level2->children;
	      
	      if      (!strcmp(phaseNameXML, "sulfide"                )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "oxide"                  )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "cas"                    )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "nakalsi"                )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "hollandite"             )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "carbonate"              )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "carbonateliquid"        )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "sodalite"               )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "sillimanite"            )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "kyanite"                )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "staurolite"             )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "zoisite"                )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "cordierite"             )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "chevkinite"             )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "clay"                   )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "chevkinite"             )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "epidote"                )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "montdorite"             )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "phlogopite"             )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "tisicomp"               )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "amphibole"              )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "melilite"               )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "armacolite"             )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "ferrobustamite"         )) bypass = TRUE;
  	      else if (!strcmp(phaseNameXML, "caperovskite"           )) bypass = TRUE;
  	      else if (!strcmp(phaseNameXML, "stishovite"             )) bypass = TRUE;
  	      else if (!strcmp(phaseNameXML, "coesite"                )) bypass = TRUE;
  	      else if (!strcmp(phaseNameXML, "perovskite"             )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "ferropericlase"         )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "density"                )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "o2"                     )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "potassium feldspar"     )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "oxide-generic"          )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "liquid"                 )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "allanite"               )) bypass = TRUE;
#ifdef RHYOLITE_ADJUSTMENTS
	      else if (!strcmp(phaseNameXML, "potassium tetrasilicate")) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "potassium disilicate"   )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "sodium metasilicate"    )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "sodium disilicate"      )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "mullite"                )) bypass = TRUE;
#else
	      else if (!strcmp(phaseNameXML, "biotite"                )) bypass = TRUE;
#endif	      
	      if (!bypass) {
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
                Boolean killPhase;
#endif
	        if	(!strcmp(phaseNameXML, "cpx"))            phaseName = "clinopyroxene";
	        else if (!strcmp(phaseNameXML, "opx"))            phaseName = "orthopyroxene"; 
	        else if (!strcmp(phaseNameXML, "plagioclase"))    phaseName = "feldspar"; 
	        else if (!strcmp(phaseNameXML, "kspar"))          phaseName = "feldspar"; 
	        else if (!strcmp(phaseNameXML, "ilmenite"))       phaseName = "rhm-oxide"; 
#ifndef RHYOLITE_ADJUSTMENTS
	        else if (!strcmp(phaseNameXML, "fluid"))          phaseName = "water"; 
#endif
	        else if (!strcmp(phaseNameXML, "titanite"))       phaseName = "sphene"; 
	        else { 
	          phaseName = (char *) malloc((size_t) (strlen(phaseNameXML)+1)*sizeof(char)); 
	          phaseName = strcpy(phaseName, phaseNameXML);
	          deRef = TRUE;
	        }
	        xmlFree(phaseNameXML);
	        
	        /* process a phase with name phaseName */
                /* phaseName can be Solid, ENTROPY (S J/gfw), ENTHALPY (H kJ/gfw), LIQUID (composition), DENSITY (gm/cc) */
                for (id=0; id<npc; id++) if ((solids[id].type == PHASE) && solids[id].inclInClb && !strcmp(solids[id].label, phaseName)) break;   
                if (id == npc) {
                  ABORT("Illegal phase descriptor in data file: ", phaseName)
                  if (deRef) free(phaseName); workProcData->active = FALSE; return TRUE;
                } else if (deRef) free(phaseName);

#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
                killPhase = FALSE; /* (!strcmp(solids[id].label, "nepheline") || !strcmp(solids[id].label, "carnegieite") */
                if ( !strcmp(solids[id].label, "carnegieite") &&
		     /* SiO2 - Al2O3 - Na2O senso stricto */
		     (wt[0] != 0.0) && (wt[1] != 0.0) && (wt[2] == 0.0) && (wt[3] != 0.0) && (wt[4] == 0.0) && (wt[5] == 0.0) && 
		     /* molar Si/Na should not be < 1.0 */
		     (wt[0]/(wt[3]*2.0) < 1.0)
		   ) {
		  killPhase = TRUE;
		  printf("Removed %s from experiment %d. Si/Na = %5.3f", solids[id].label, LEPRnum, wt[0]/(wt[3]*2.0));
		  printf(" SiO2, Al2O3, Na2O: %6.2f %6.2f %6.2f\n", wt[0]*bulkSystem[0].mw, wt[1]*bulkSystem[1].mw, wt[3]*bulkSystem[3].mw);
		}
#endif
	        for (i=0; i<nc; i++) wt[i] = 0.0;
	        hORsORdCON = 0.0;
	        while (level3 != NULL) {
	          if (level3->type == XML_ELEMENT_NODE) {
	            xmlChar *content3 = xmlNodeGetContent(level3);
	            for (i=0; i<nc; i++) if (!strcmp((char *) level3->name, oxNamesLC[i])) {
	              wt[i] = atof((char *) content3);
	              break;
	            }
	            if      (!strcmp((char *) level3->name, "value"  )) hORsORdCON = atof((char *) content3);
	            else if (!strcmp((char *) level3->name, "maximum")) hORsORdCON = atof((char *) content3) + 1000.0;
	            else if (!strcmp((char *) level3->name, "minimum")) hORsORdCON = atof((char *) content3) + 2000.0;
	            if (content3 != NULL) xmlFree(content3);
	          }
	          level3 = level3->next;
	        }
		
		if ( (CO2index != -1) && (H2Oindex != -1) && !strcmp(phaseName, "water") && (wt[CO2index] > 0.0) ) lowWtFlag[H2Oindex] = TRUE;

                if ( validLiquid && ((lowPonly && (p < 100000.0)) || !lowPonly) && ((highPonly && (p > 100000.0)) || !highPonly) &&
		                    ((oneBarOnly && (p < 2.0))    || !oneBarOnly) 
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
                    && !killPhase
#endif				    
#ifndef BUILD_MGO_SIO2_VERSION
#ifndef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
	            && ((anhydrousOnly && (molesLiqCmp[18] == 0.0)) || !anhydrousOnly) 
	            && ((hydrousOnly && (molesLiqCmp[18] > 0.0)) || !hydrousOnly)
#endif
#endif
                ) {

                  phasesPresent[id] = TRUE;
  
                  preclbCount[id].np++;
                  (void) snprintf(value, 6, "%5.5d", preclbCount[id].np);
                  DISPLAY(preclbCount[id].present, value)

                  /* Determine if phase data may be included */
                  if (preclbCount[id].usePhase) {
                    ResidualDataInput *pRDI = &(residualDataInput[nLiquid-1]);

                    if (solids[id].convert != NULL) {
		      double sumMoles = 0.0;
                      /* Convert wt % oxides to moles of oxides */
                      for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;
                      /* Convert moles of oxides to moles of elements */
                      for (i=0; i<107; i++) {
                	molesElmSol[i] = 0.0;
                	for (j=0; j<nc; j++) if ((bulkSystem[j].oxToElm)[i] != 0) molesElmSol[i] += ((double) (bulkSystem[j].oxToElm)[i])*wt[j];
                      }
                      /* Convert moles of elements to moles of endmember components	*/
                      (*solids[id].convert) (FIRST, SECOND, t, p, molesElmSol, moles, NULL, NULL, NULL, NULL, NULL, NULL);
		      for (i=0; i<solids[id].na; i++) sumMoles += moles[i];
	              
	              if ((sumMoles > 0.0) && (*solids[id].test) (SIXTH, t, p, 0, 0, NULL, NULL, NULL, moles)) {
		        int useSaved;

                	/* Convert moles of endmember components to independent variables */
                	(*solids[id].convert) (SECOND, THIRD, t, p, NULL, moles, indep, NULL, NULL, NULL, NULL, NULL);
			
			/* Check if the pyroxene is correctly classified */
			if (!strcmp("clinopyroxene", phaseName) && isOrthopyroxene(t, p, indep)) {
			  printf("Cpx in exp %d is reclassified to opx.\n", LEPRnum);
			  phasesPresent[id] = FALSE;
                   	  preclbCount[id].np--;
                   	  (void) snprintf(value, 6, "%5.5d", preclbCount[id].np);
                   	  DISPLAY(preclbCount[id].present, value)
			  for (id=0; id<npc; id++) if ((solids[id].type == PHASE) && solids[id].inclInClb && !strcmp(solids[id].label, "orthopyroxene")) break;   
			  phasesPresent[id] = TRUE;
                   	  preclbCount[id].np++;
                   	  (void) snprintf(value, 6, "%5.5d", preclbCount[id].np);
                   	  DISPLAY(preclbCount[id].present, value)

			} else if (!strcmp("orthopyroxene", phaseName) && isPigeonite(t, p, indep)) {
			  int changeClass = TRUE;
			  double wo = 100.0*molesElmSol[20]/(molesElmSol[20]+molesElmSol[26]+molesElmSol[12]);
			  if ( (p >= 5000.0) && (molesElmSol[13]*101.961/2.0 > 2.0) && (wo >= 4.0) && (wo <= 7.0)) changeClass = FALSE;
			  if (changeClass) {
			    printf("Opx in exp %d is reclassified to cpx.\n", LEPRnum);
			    phasesPresent[id] = FALSE;
                   	    preclbCount[id].np--;
                   	    (void) snprintf(value, 6, "%5.5d", preclbCount[id].np);
                   	    DISPLAY(preclbCount[id].present, value)
			    for (id=0; id<npc; id++) if ((solids[id].type == PHASE) && solids[id].inclInClb && !strcmp(solids[id].label, "clinopyroxene")) break;   
			    phasesPresent[id] = TRUE;
                   	    preclbCount[id].np++;
                   	    (void) snprintf(value, 6, "%5.5d", preclbCount[id].np);
                   	    DISPLAY(preclbCount[id].present, value)
			  }
			}
			
                	/* Compute activities of endmember components/exclude dilute comp */
                	for (j=0, useSaved=FALSE; j<solids[id].na; j++) {
                	  if(preclbCount[id+1+j].usePhase && getDependentOfSolid(molesLiqCmp, t, p, lowWtFlag, id, j, indep, useSaved)) {
                	    nEqn++;
                	    pRDI->nSol++; if (pRDI->nSol > nSolCoexistMax) 
	        			  printf("ERROR:preclb[preclb.c at line %d] nSolCoexistMax[=%d] exceeded.\n", __LINE__, nSolCoexistMax);
	        	    pRDI->pIndex  = (int *)	REALLOC(pRDI->pIndex, (size_t) (pRDI->nSol)*sizeof(int));
	        	    pRDI->cIndex  = (int *)	REALLOC(pRDI->cIndex, (size_t) (pRDI->nSol)*sizeof(int));
	        	    pRDI->rSol    = (double **) REALLOC(pRDI->rSol,   (size_t) (pRDI->nSol)*sizeof(double *));
	        	   (pRDI->rSol)[pRDI->nSol-1] = (double *) malloc((size_t) (solids[id].nr)*sizeof(double));
	        	    pRDI->isEqual = (int *)	REALLOC(pRDI->isEqual,(size_t) (pRDI->nSol)*sizeof(int));
	        	    pRDI->depenG  = (double *)  REALLOC(pRDI->depenG,  (size_t) (pRDI->nSol)*sizeof(double));
                            if (useTregression) pRDI->dependGdT = (double *)  REALLOC(pRDI->dependGdT, (size_t) (pRDI->nSol)*sizeof(double));
	        	   (pRDI->pIndex) [pRDI->nSol-1] = id;
	        	   (pRDI->cIndex) [pRDI->nSol-1] = id+1+j; 
	        	   (pRDI->isEqual)[pRDI->nSol-1] = TRUE;
	        	   (pRDI->depenG) [pRDI->nSol-1] = delta.g/SCALE;
                            if (useTregression) (pRDI->dependGdT) [pRDI->nSol-1] = delta.dgdt/SCALE;
	        	    for (i=0; i<solids[id].nr; i++) (pRDI->rSol)[pRDI->nSol-1][i] = indep[i];
	        	   (pRO->residuals) = (double *) REALLOC(pRO->residuals, (size_t)	 (pRDI->nSol)*sizeof(double));
	        	   (pRO->dr)	    = (double *) REALLOC(pRO->dr,	 (size_t) nParam*(pRDI->nSol)*sizeof(double));
                   	   preclbCount[id+1+j].np++;
                   	   (void) snprintf(value, 6, "%5.5d", preclbCount[id+1+j].np);
                   	   DISPLAY(preclbCount[id+1+j].present, value)
                	  }
			  useSaved = TRUE;
                	}
	              
	        	/* dependent species used as regression constraints */
	        	for (k=0; k<nes; k++) if (extraSolids[k].index == id) {
	        	  double sumMoles, newMoles = 0.0;
	        	  Boolean notSuitable = False;
			  int useSaved;
	        	  for (j=0; j<solids[id].na; j++) newMoles += (extraSolids[k].m)[j]*moles[j];
	
	        	  newMoles = (extraSolids[k].norm > 0.0)   ? newMoles/extraSolids[k].norm	  : 0.0;
	        	  sumMoles = (extraSolids[k].oxygen > 0.0) ? molesElmSol[8]/extraSolids[k].oxygen : 0.0;
	
	        	  /* Exclusion criteria on mole fraction */
	        	  if ((sumMoles == 0.0) || (newMoles/sumMoles < extraSolids[k].threshold)) break;
	
	        	  for (j=0; j<solids[id].na; j++) if ( ((extraSolids[k].m)[j] != 0.0) &&
	        	    ((extraSolids[k].mLimits)[j] != 0.0) && (moles[j]/sumMoles < (extraSolids[k].mLimits)[j]) ) notSuitable = True;
			  if (!strcmp("majorite ss", phaseName) && p <= 50000.0) notSuitable = True; /* Special case: Fe-majorite */
                	  if (notSuitable) break;

                	  /* Compute activities of endmember components/do not exclude dilute comp */
                	  (*solids[id].activity) (FIRST, t, p, indep, activity, NULL, NULL);

                	  nEqn++;
                	  pRDI->nSol++; if (pRDI->nSol > nSolCoexistMax) 
	        			printf("ERROR:preclb[preclb.c at line %d] nSolCoexistMax[=%d] exceeded.\n", __LINE__, nSolCoexistMax);
	        	  pRDI->pIndex  = (int *)     REALLOC(pRDI->pIndex, (size_t) (pRDI->nSol)*sizeof(int));
	        	  pRDI->cIndex  = (int *)     REALLOC(pRDI->cIndex, (size_t) (pRDI->nSol)*sizeof(int));
	        	  pRDI->rSol	= (double **) REALLOC(pRDI->rSol,   (size_t) (pRDI->nSol)*sizeof(double *));
	        	 (pRDI->rSol)[pRDI->nSol-1] = (double *) malloc((size_t) (solids[id].nr)*sizeof(double));
	        	  pRDI->isEqual = (int *)     REALLOC(pRDI->isEqual,(size_t) (pRDI->nSol)*sizeof(int));
	        	  pRDI->depenG	= (double *)  REALLOC(pRDI->depenG,  (size_t) (pRDI->nSol)*sizeof(double));
		          if (useTregression) pRDI->dependGdT = (double *)  REALLOC(pRDI->dependGdT, (size_t) (pRDI->nSol)*sizeof(double));
	        	 (pRDI->pIndex) [pRDI->nSol-1] = id;
	        	 (pRDI->cIndex) [pRDI->nSol-1] = npc+k; 
	        	 (pRDI->isEqual)[pRDI->nSol-1] = TRUE;
	        	 (pRDI->depenG) [pRDI->nSol-1] = 0.0;
	        	  for (i=0; i<solids[id].nr; i++) (pRDI->rSol)[pRDI->nSol-1][i] = indep[i];
	        	 (pRO->residuals) = (double *) REALLOC(pRO->residuals, (size_t)        (pRDI->nSol)*sizeof(double));
	        	 (pRO->dr)	  = (double *) REALLOC(pRO->dr,        (size_t) nParam*(pRDI->nSol)*sizeof(double));
	
                	  for (j=0, useSaved=FALSE; j<solids[id].na; j++) {
                	    if(getDependentOfSolid(molesLiqCmp, t, p, lowWtFlag, id, j, indep, useSaved)) {
                	      (pRDI->depenG)[pRDI->nSol-1] += (extraSolids[k].m)[j]*delta.g/SCALE;
                               if (useTregression) (pRDI->dependGdT) [pRDI->nSol-1] = delta.dgdt/SCALE;
                	    } else {
	        	      nEqn--;
	        	      free((pRDI->rSol)[pRDI->nSol-1]);
	        	      pRDI->nSol--;
	        	      break;
	        	    }
			    useSaved = TRUE;
                	  }
	        	}
	        	
	              } else printf("-->Phase %s in liquid %d fails validation test.\n", solids[id].label, nLiquid);
	              
                    } else {
	            
	              if ( (strncmp(solids[id].label, "entropy", 7) == 0) || (strncmp(solids[id].label, "enthalpy", 8) == 0) 
		        || (strncmp(solids[id].label, "density", 7) == 0) ) {
	        	double molesLiqTot = 0.0;
	        	for (i=0; i<nlc; i++) molesLiqTot += molesLiqCmp[i];
		        if (molesLiqTot != 0.0) {
                	  nEqn++;
                	  pRDI->nSol++; if (pRDI->nSol > nSolCoexistMax) 
	        			printf("ERROR:preclb[preclb.c at line %d] nSolCoexistMax[=%d] exceeded.\n", __LINE__, nSolCoexistMax);
	        	  pRDI->pIndex  = (int *)   REALLOC(pRDI->pIndex, (size_t) (pRDI->nSol)*sizeof(int));
	        	  pRDI->cIndex  = (int *)   REALLOC(pRDI->cIndex, (size_t) (pRDI->nSol)*sizeof(int));
	        	  pRDI->rSol	= (double **) REALLOC(pRDI->rSol, (size_t) (pRDI->nSol)*sizeof(double *));
	        	  pRDI->isEqual = (int *)   REALLOC(pRDI->isEqual,(size_t) (pRDI->nSol)*sizeof(int));
	        	  pRDI->depenG	= (double *)  REALLOC(pRDI->depenG, (size_t) (pRDI->nSol)*sizeof(double));
                          if (useTregression) pRDI->dependGdT = (double *)  REALLOC(pRDI->dependGdT, (size_t) (pRDI->nSol)*sizeof(double));
	        	 (pRDI->pIndex) [pRDI->nSol-1] = id;
	        	 (pRDI->cIndex) [pRDI->nSol-1] = id; 
	        	 (pRDI->isEqual)[pRDI->nSol-1] = TRUE;
			 if      (strncmp(solids[id].label, "density", 7)  == 0) (pRDI->depenG)  [pRDI->nSol-1] = hORsORdCON;
	        	 else (pRDI->depenG)  [pRDI->nSol-1] = hORsORdCON/molesLiqTot; /* Scale the entropy/enthalpy for one mole of liquid */
	        	 (pRO->residuals) = (double *) REALLOC(pRO->residuals, (size_t)        (pRDI->nSol)*sizeof(double));
	        	 (pRO->dr)	  = (double *) REALLOC(pRO->dr,        (size_t) nParam*(pRDI->nSol)*sizeof(double));
	        	}

	              } else if (strncmp(solids[id].label, "liquid", 6) == 0) {
	        	static double *molesTmp; 
	        	if (molesTmp == NULL) molesTmp = (double *) malloc((size_t) nc*sizeof(double));

                	for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;
                	conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL, NULL, NULL, &logfo2); /* FeO(T) -> Fe2O3, FeO */
                	for (i=0; i<nlc; i++) for (j=0, molesTmp[i]=0.0; j<nc; j++) molesTmp[i] += wt[j]*(bulkSystem[j].oxToLiq)[i];

                	if (testLiq(SIXTH, t, p, 0, 0, NULL, NULL, NULL, molesTmp)) {
                	  static double *xSpecies, *rTmp; 
	        	  if (xSpecies == NULL) xSpecies = (double *) malloc((size_t) nls*sizeof(double));
	        	  if (rTmp     == NULL) rTmp	 = (double *) malloc((size_t) (nlc-1)*sizeof(double));
	
	        	  conLiq(SECOND, THIRD, 	  t, p, NULL, molesTmp, rTmp, NULL,	NULL, NULL, NULL);
	        	  conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL,	rTmp, xSpecies, NULL, NULL, NULL);
	
	        	  if (testLiq(SEVENTH,0, 0, 0, 0, NULL, NULL, NULL, NULL)) { 
	        	    double gTest;
	        	    gmixLiq(FIRST, t, p, rTmp, &gTest, NULL, NULL);
	        	    if (testLiq(EIGHTH, 0, 0, 0, 0, NULL, NULL, NULL, NULL)) {

                	      for (i=0; i<nlc; i++) if ( (molesLiqCmp[i] != 0.0) && (molesTmp[i] != 0.0) ){
                		nEqn++;
                		pRDI->nSol++; if (pRDI->nSol > nSolCoexistMax) 
	        			      printf("ERROR:preclb[preclb.c at line %d] nSolCoexistMax[=%d] exceeded.\n", __LINE__, nSolCoexistMax);
	        		pRDI->pIndex  = (int *)   REALLOC(pRDI->pIndex, (size_t) (pRDI->nSol)*sizeof(int));
	        		pRDI->cIndex  = (int *)   REALLOC(pRDI->cIndex, (size_t) (pRDI->nSol)*sizeof(int));
	        		pRDI->rSol    = (double **) REALLOC(pRDI->rSol, (size_t) (pRDI->nSol)*sizeof(double *));
	        	       (pRDI->rSol)[pRDI->nSol-1] = (double *) malloc((size_t) (nlc-1)*sizeof(double));
	        		pRDI->isEqual = (int *)   REALLOC(pRDI->isEqual,(size_t) (pRDI->nSol)*sizeof(int));
	        		pRDI->depenG   = (double *)  REALLOC(pRDI->depenG,  (size_t) (pRDI->nSol)*sizeof(double));
                                if (useTregression) pRDI->dependGdT = (double *)  REALLOC(pRDI->dependGdT, (size_t) (pRDI->nSol)*sizeof(double));
	        	       (pRDI->pIndex) [pRDI->nSol-1] = id;
	        	       (pRDI->cIndex) [pRDI->nSol-1] = id; 
	        	       (pRDI->isEqual)[pRDI->nSol-1] = TRUE + i; /* Still TRUE, but it also carries the component index */
	        	       (pRDI->depenG)  [pRDI->nSol-1] = 0.0;
                                if (useTregression) (pRDI->dependGdT) [pRDI->nSol-1] = 0.0;
	        		for (j=0; j<(nlc-1); j++) (pRDI->rSol)[pRDI->nSol-1][j] = rTmp[j];
	        	       (pRO->residuals) = (double *) REALLOC(pRO->residuals, (size_t)	     (pRDI->nSol)*sizeof(double));
	        	       (pRO->dr)	= (double *) REALLOC(pRO->dr,	     (size_t) nParam*(pRDI->nSol)*sizeof(double));
                	      }

                	    }
	        	  }
	        	}
			
                      } else if(getDependentOfSolid(molesLiqCmp, t, p, lowWtFlag, id, -1, NULL, FALSE)) { 
                	nEqn++;
                	pRDI->nSol++; if (pRDI->nSol > nSolCoexistMax) 
	        		      printf("ERROR:preclb[preclb.c at line %d] nSolCoexistMax[=%d] exceeded.\n", __LINE__, nSolCoexistMax);
	        	pRDI->pIndex  = (int *)     REALLOC(pRDI->pIndex, (size_t) (pRDI->nSol)*sizeof(int));
	        	pRDI->cIndex  = (int *)     REALLOC(pRDI->cIndex, (size_t) (pRDI->nSol)*sizeof(int));
	        	pRDI->rSol    = (double **) REALLOC(pRDI->rSol,   (size_t) (pRDI->nSol)*sizeof(double *));
	        	pRDI->isEqual = (int *)     REALLOC(pRDI->isEqual,(size_t) (pRDI->nSol)*sizeof(int));
	        	pRDI->depenG  = (double *)  REALLOC(pRDI->depenG, (size_t) (pRDI->nSol)*sizeof(double));
                        if (useTregression) pRDI->dependGdT = (double *)  REALLOC(pRDI->dependGdT, (size_t) (pRDI->nSol)*sizeof(double));
	               (pRDI->pIndex) [pRDI->nSol-1] = id;
	               (pRDI->cIndex) [pRDI->nSol-1] = id; 
	               (pRDI->isEqual)[pRDI->nSol-1] = TRUE;
	               (pRDI->depenG) [pRDI->nSol-1] = delta.g/SCALE + ((id == o2Index) ? R*t*log(10.0)*logfo2/SCALE : 0.0);
                        if (useTregression) (pRDI->dependGdT) [pRDI->nSol-1] = delta.dgdt/SCALE + ((id == o2Index) ? R*log(10.0)*logfo2/SCALE : 0.0);
	               (pRO->residuals) = (double *) REALLOC(pRO->residuals, (size_t)	     (pRDI->nSol)*sizeof(double));
	               (pRO->dr)	= (double *) REALLOC(pRO->dr,	     (size_t) nParam*(pRDI->nSol)*sizeof(double));
                      }
	              
                    }
  
                  }
      
                }
	      } else xmlFree(phaseNameXML); /* end if block on bypass phase */
	    }
	    
	    if (content2 != NULL) xmlFree(content2);
	  }  
	  level2 = level2->next;
	} /* This is the end of the while loop on level2 - no more entries for this experiment */

        /* Assign Phase absent constraints for previous liquid */
        for (j=0; j<npc; j++) {
          if (!phasesPresent[j] && preclbCount[j].absPhase) {

            if (validLiquid && ((lowPonly && (p < 100000.0)) || !lowPonly) && ((highPonly && (p > 100000.0)) || !highPonly) &&
	                       ((oneBarOnly && (p < 2.0))    || !oneBarOnly)
#ifndef BUILD_MGO_SIO2_VERSION
#ifndef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
	        && ((anhydrousOnly && (molesLiqCmp[18] == 0.0)) || !anhydrousOnly) && ((hydrousOnly && (molesLiqCmp[18] > 0.0)) || !hydrousOnly)
#endif
#endif
	      ) {

              if (solids[j].convert == NULL) {
        	if(getDependentOfSolid(molesLiqCmp, t, p, zeroWtFlag, j, -1, NULL, FALSE)) { 
        	  preclbCount[j].na++;
        	  (void) snprintf(value, 6, "%5.5d", preclbCount[j].na);
        	  DISPLAY(preclbCount[j].absent, value)
        	  nEqn++;
        	  pRDI->nSol++; if (pRDI->nSol > nSolCoexistMax) 
        			printf("ERROR:preclb[preclb.c at line %d] nSolCoexistMax[=%d] exceeded.\n", __LINE__, nSolCoexistMax);
        	  pRDI->pIndex  = (int *)     REALLOC(pRDI->pIndex, (size_t) (pRDI->nSol)*sizeof(int));
        	  pRDI->cIndex  = (int *)     REALLOC(pRDI->cIndex, (size_t) (pRDI->nSol)*sizeof(int));
        	  pRDI->rSol	= (double **) REALLOC(pRDI->rSol,   (size_t) (pRDI->nSol)*sizeof(double *));
        	  pRDI->isEqual = (int *)     REALLOC(pRDI->isEqual,(size_t) (pRDI->nSol)*sizeof(int));
        	  pRDI->depenG	= (double *)  REALLOC(pRDI->depenG, (size_t) (pRDI->nSol)*sizeof(double));
                  if (useTregression) pRDI->dependGdT = (double *)  REALLOC(pRDI->dependGdT, (size_t) (pRDI->nSol)*sizeof(double));
        	 (pRDI->pIndex) [pRDI->nSol-1] = j;
        	 (pRDI->cIndex) [pRDI->nSol-1] = j; 
        	 (pRDI->isEqual)[pRDI->nSol-1] = FALSE;
        	 (pRDI->depenG) [pRDI->nSol-1] = delta.g/SCALE;
                  if (useTregression) (pRDI->dependGdT) [pRDI->nSol-1] = delta.dgdt/SCALE;
        	 (pRO->residuals) = (double *) REALLOC(pRO->residuals, (size_t)        (pRDI->nSol)*sizeof(double));
        	 (pRO->dr)	  = (double *) REALLOC(pRO->dr,        (size_t) nParam*(pRDI->nSol)*sizeof(double));
        	}
              } else if (solids[j].convert != NULL) {
	        int useSaved;
        	for (k=0, l=0, useSaved=FALSE; k<solids[j].na; k++) {
        	  if(getDependentOfSolid(molesLiqCmp, t, p, zeroWtFlag, j, k, NULL, useSaved)) { 
        	    nEqn++;
        	    pRDI->nSol++; if (pRDI->nSol > nSolCoexistMax) 
        			  printf("ERROR:preclb[preclb.c at line %d] nSolCoexistMax[=%d] exceeded.\n", __LINE__, nSolCoexistMax);
        	    pRDI->pIndex  = (int *)	REALLOC(pRDI->pIndex, (size_t) (pRDI->nSol)*sizeof(int));
        	    pRDI->cIndex  = (int *)	REALLOC(pRDI->cIndex, (size_t) (pRDI->nSol)*sizeof(int));
        	    pRDI->rSol    = (double **) REALLOC(pRDI->rSol,   (size_t) (pRDI->nSol)*sizeof(double *));
        	   (pRDI->rSol)[pRDI->nSol-1] = (double *) malloc((size_t) (solids[j].nr)*sizeof(double));
        	    pRDI->isEqual = (int *)	REALLOC(pRDI->isEqual,(size_t) (pRDI->nSol)*sizeof(int));
        	    pRDI->depenG  = (double *)  REALLOC(pRDI->depenG, (size_t) (pRDI->nSol)*sizeof(double));
                    if (useTregression) pRDI->dependGdT = (double *)  REALLOC(pRDI->dependGdT, (size_t) (pRDI->nSol)*sizeof(double));
        	   (pRDI->pIndex) [pRDI->nSol-1] = j;
        	   (pRDI->cIndex) [pRDI->nSol-1] = j+1+k; 
        	   (pRDI->isEqual)[pRDI->nSol-1] = FALSE;
        	   (pRDI->depenG) [pRDI->nSol-1] = delta.g/SCALE;
                    if (useTregression) (pRDI->dependGdT) [pRDI->nSol-1] = delta.dgdt/SCALE;
        	    for (i=0; i<solids[j].nr; i++) (pRDI->rSol)[pRDI->nSol-1][i] = 0.0;
        	   (pRO->residuals) = (double *) REALLOC(pRO->residuals, (size_t)	 (pRDI->nSol)*sizeof(double));
        	   (pRO->dr)	    = (double *) REALLOC(pRO->dr,	 (size_t) nParam*(pRDI->nSol)*sizeof(double));
        	    l++;
        	  }
		  useSaved = TRUE;
        	}
        	if (l > 0) {
        	  preclbCount[j].na++;
        	  (void) snprintf(value, 6, "%5.5d", preclbCount[j].na);
        	  DISPLAY(preclbCount[j].absent, value)
        	}
              }
            
            }
            
          }
          phasesPresent[j] = FALSE;
        }

      } /* This is the end of the if block testing if a level1 node is an experiment */
      if (content1 != NULL) xmlFree(content1);
      
    } /* This is the end of the if block testing if level1 is a node */
    level1 = level1->next;
    workProcData->active = TRUE; 
    return FALSE;
    
  } /* This is the end of the if block testing if level1 is NULL */

  if (doc    != NULL) xmlFreeDoc(doc);
  if (ctxt2  != NULL) xmlSchemaFreeValidCtxt(ctxt2);
  if (schema != NULL) xmlSchemaFree(schema);
  xmlSchemaCleanupTypes();
  xmlCleanupParser();	  

  DISPLAY(actionADB[1], "")
  if (useTrustRegionMethod) { DISPLAY(actionADB[0], "Processing of data file completed. initializing Trust Region Method analysis.") }
  else                      { DISPLAY(actionADB[0], "Processing of data file completed. initializing Marquardt analysis.") }

  curStep++;
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Redimension arrays, and setup Regression Analysis
 *===========================================================================*/

  case PREREGRESS: 

  free(molesLiqCmp);   molesLiqCmp   = NULL;
  free(lowWtFlag);     lowWtFlag     = NULL;
  free(zeroWtFlag);    zeroWtFlag    = NULL;
  free(phasesPresent); phasesPresent = NULL;
  free(moles);         moles         = NULL;
  free(indep);         indep         = NULL;
  free(activity);      activity      = NULL;
  free(wt);            wt            = NULL;
  
  fclose(liqFile);

#ifdef USE_MPI
  /* Set up MPI calls here to create slave processes and initialize them */
  { /* MPI scope     */
    void **attrp;
    MPI_Info appInfo;
#ifdef USE_LAM_MPI
    char filename[128];
    FILE *fp;
#endif
    int flag, membersize, err, i;
    Work *p;

    /* Initialize MPI. */
    if (DEBUG_MPI) printf("MPI:preclb[preclb.c at line %d]--> Calling MPI_Init()...\n", __LINE__);
    MPI_Init(NULL, NULL);
    if (DEBUG_MPI) printf("MPI:preclb[preclb.c at line %d]--> Calling MPI_Comm_size\n", __LINE__);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

    /* Check that we are the only master */
    if (ntasks != 1) {
      printf("MPI:preclb[preclb.c at line %d]--> Too many master processes. ABORTING.\n", __LINE__);
      MPI_Abort(MPI_COMM_WORLD, (1 << 16) + 1);
    }

    /* Get universe size */
    if (DEBUG_MPI) printf("MPI:preclb[preclb.c at line %d]--> Calling MPI_Attr_get\n", __LINE__);
    MPI_Attr_get(MPI_COMM_WORLD, MPI_UNIVERSE_SIZE, &attrp, &flag);
    if (flag == 1) {
      ntasks  = (int) *attrp; /* LAM determines the number of cpus automatically */
#ifndef USE_LAM_MPI
      ntasks = 6; /* Two processors per xserve node. <><><><><> */
#endif
      ntasks -= (ntasks > 1) ? 1 : 0;  /* There should be one CPU that just runs the master */
    } else {
      printf("MPI:preclb[preclb.c at line %d]--> This MPI does not support Universe Size.  ABORTING\n", __LINE__);
      MPI_Abort(MPI_COMM_WORLD, (1 << 16) + 1);
    }

#ifdef USE_LAM_XLED
    (void) lam_ledinit(0, ntasks+1);
    (void) lam_ledclr();
    (void) lam_ledon(0);
#endif

    /* Allocate slave communicator arrays. */
    icomm_slaves = (MPI_Comm *) malloc((size_t) (ntasks * sizeof(MPI_Comm)));
    if (icomm_slaves == NULL) MPI_Abort(MPI_COMM_WORLD, (errno << 16) + 1);

    /* Spawn off the slaves */

#ifdef USE_LAM_MPI
    (void) snprintf(filename, 128, "./MELTS_preclb_appschema.%d", (int) getpid());
    MPI_Info_create(&appInfo);
    MPI_Info_set(appInfo, "file", filename);
    for (i=0; i<ntasks; ++i) {

      /* Create a temporary app schema file */
      fp = fopen(filename, "w");
      if (fp == NULL) {
        printf("MPI:preclb[preclb.c at line %d]--> Could not open file %s. ABORTING.\n", __LINE__, filename);
        MPI_Finalize();
        return 1;
      }
      fprintf(fp, "c%d ./Melts-slave\n", i+1);
      fclose(fp);

      /* Spawn  slave processes */
      if (DEBUG_MPI) printf("MPI:preclb[preclb.c at line %d]--> Calling MPI_Comm_spawn(slave = %d)...\n", __LINE__, i+1);
      MPI_Comm_spawn(0, MPI_ARGV_NULL, 0, appInfo, 0, MPI_COMM_SELF, &(icomm_slaves[i]), &err);
      if (err != MPI_SUCCESS) {
        printf("MPI:preclb[preclb.c at line %d]--> Spawn Error %d.  ABORTING.\n", __LINE__, err);
        MPI_Abort(MPI_COMM_WORLD, (err << 16) + 1);
      } 
    }
    MPI_Info_free(&appInfo);
    unlink(filename);
#else
    for (i=0; i<ntasks; ++i) {
      /* Spawn  slave processes */
      MPI_Info_create(&appInfo);
      if      (i == 0) MPI_Info_set(appInfo, "host", "216.231.56.113"); /* <><><><><> */
      else if (i == 1) MPI_Info_set(appInfo, "host", "192.168.0.2"); /* <><><><><> */
      else if (i == 2) MPI_Info_set(appInfo, "host", "192.168.0.2"); /* <><><><><> */
      else if (i == 3) MPI_Info_set(appInfo, "host", "192.168.0.3"); /* <><><><><> */
      else if (i == 4) MPI_Info_set(appInfo, "host", "192.168.0.3"); /* <><><><><> */
    
      if (DEBUG_MPI) printf("MPI:preclb[preclb.c at line %d]--> Calling MPI_Comm_spawn(slave = %d)...\n", __LINE__, i+1);
      MPI_Comm_spawn((i == 0) ? "Melts-slave" : "/Network/Servers/x01.OFMcluster/ccuHome/ccuMSG/xMelts/Melts-slave", 
                     MPI_ARGV_NULL, 1, appInfo, 0, 
                     MPI_COMM_SELF, &(icomm_slaves[i]), &err);
      if (err != MPI_SUCCESS) {
        printf("MPI:preclb[preclb.c at line %d]--> Spawn Error %d.  ABORTING.\n", __LINE__, err);
        MPI_Abort(MPI_COMM_WORLD, (err << 16) + 1);
      }
       
      MPI_Info_free(&appInfo);
    }
#endif
  
    /* Tell each slave who they are, how many processes there are, and initilaize a few constants */
    for (i=0; i<ntasks; i++) {
      int info[7];
      info[0] = i+1;
      info[1] = ntasks+1;
      info[2] = nLiqCoexistMax;
      info[3] = nSolCoexistMax;
      info[4] = nrMAX;
      info[5] = nParam;
      info[6] = useTregression;
      if (DEBUG_MPI) printf("MPI:preclb[preclb.c at line %d]--> Calling MPI_Send(slave = %d)...\n", __LINE__, i+1);
      MPI_Send(info, 7, MPI_INT, 0, WORKTAG, icomm_slaves[i]);
    }

    /* Allocate slave receive request array. */
    req_slaves = (MPI_Request *) malloc((size_t) (ntasks * sizeof(MPI_Request)));
    if (req_slaves == NULL) MPI_Abort(MPI_COMM_WORLD, (errno << 16) + 1);
    for (i=0; i<ntasks; ++i) req_slaves[i] = MPI_REQUEST_NULL;

    /* Allocate slave work ptr array. */
    work_slaves = (Work **) malloc((size_t) (ntasks * sizeof(struct _work *)));
    if (work_slaves == NULL) MPI_Abort(MPI_COMM_WORLD, (errno << 16) + 1);

    MPI_Pack_size(2 + 3*nSolCoexistMax, MPI_INT,    MPI_COMM_WORLD, &membersize); maxSizeOut  = membersize;
    MPI_Pack_size(3 + 2*nSolCoexistMax + (nlc-1)*nLiqCoexistMax + nrMAX*nSolCoexistMax, 
                  MPI_DOUBLE, MPI_COMM_WORLD, &membersize); maxSizeOut += membersize;
    bufferOut = (char *) malloc((size_t) maxSizeOut);
    
    MPI_Pack_size(4*(nls*(nls-1)/2+nls+npc)+3*nc, MPI_INT,    MPI_COMM_WORLD, &membersize); maxSizeParams = membersize;
    MPI_Pack_size(3*(nls*(nls-1)/2+nls+npc)+3*nc, MPI_DOUBLE, MPI_COMM_WORLD, &membersize); if (membersize > maxSizeParams) maxSizeParams = membersize;
    bufferParams = (char *) malloc((size_t) maxSizeParams);
    
    intParamsToSendToSlave    = (int *)    malloc((size_t) (4*(nls*(nls-1)/2+nls+npc)+3*(nc+1))*sizeof(int));
    doubleParamsToSendToSlave = (double *) malloc((size_t) (3*(nls*(nls-1)/2+nls+npc)+3*(nc+1))*sizeof(double));

    MPI_Pack_size(1,                              MPI_INT,    MPI_COMM_WORLD, &membersize); maxSizeIn  = membersize;
    MPI_Pack_size(nLiqCoexistMax-1+nSolCoexistMax,MPI_DOUBLE, MPI_COMM_WORLD, &membersize); maxSizeIn += membersize;
    MPI_Pack_size(nSolCoexistMax*nParam,          MPI_DOUBLE, MPI_COMM_WORLD, &membersize); maxSizeIn += membersize;

    /* set communicators error handlers */
    for (i=0; i<ntasks; ++i) MPI_Errhandler_set(icomm_slaves[i], MPI_ERRORS_RETURN);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    /* Create the work list. */
    bufferIn = (char **) malloc((size_t) nLiquid*sizeof(char *));
    for (i=0; i<nLiquid; i++) {
      p = (Work *) malloc((size_t) sizeof(struct _work));
      if (p == 0) MPI_Abort(MPI_COMM_WORLD, errno);

      p->residualDataInput = &(residualDataInput[i]);
      p->index             = i;
      p->wrk_next          = NULL;

      bufferIn[i] = (char *) malloc((size_t) maxSizeIn);

      insert(p);
    }
    
  } /* End MPI scope */
#endif /* USE_MPI */

#ifdef GRACE_PIPE
  GraceRegisterErrorFunction (grace_error_function);
  if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }
#endif
 
  if (useTrustRegionMethod) {

#ifdef GRACE_PIPE 
  
    GracePrintf("WITH G0\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.15, 0.10, 0.45, 0.90);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 1.0);

      GracePrintf("XAXIS TICK MAJOR 0.2\n");
      GracePrintf("XAXIS TICK MINOR 0.1\n");
      GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("XAXIS LABEL \"iterate\"\n");
      GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("XAXIS LABEL COLOR 2\n");

      GracePrintf("YAXIS TICK MAJOR 0.2\n");
      GracePrintf("YAXIS TICK MINOR 0.1\n");
      GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS LABEL \"Sum of Squares\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");
      
    GracePrintf("G0 ON\n");
 
    GracePrintf("WITH G1\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.60, 0.10, 0.90, 0.90);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 1.0);

      GracePrintf("XAXIS TICK MAJOR 0.2\n");
      GracePrintf("XAXIS TICK MINOR 0.1\n");
      GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("XAXIS LABEL \"iterate\"\n");
      GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("XAXIS LABEL COLOR 2\n");

      GracePrintf("YAXIS TICK MAJOR 0.2\n");
      GracePrintf("YAXIS TICK MINOR 0.1\n");
      GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS LABEL \"Parameters\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");
      
    GracePrintf("G1 ON\n");

    GracePrintf("REDRAW\n");
#endif /* GRACE_PIPE */
 
  } else { /* !useTrustRegionMethod */
    int j, k, nSol;
    xMrqrdt   = vector(1, nEqn);
    yMrqrdt   = vector(1, nEqn);
    sigMrqrdt = vector(1, nEqn);
 
    for (i=0, k=0, chisq=0.0; i<nLiquid; i++) if ((nSol = residualDataInput[i].nSol) > 0) for (j=0; j<nSol; j++) {
      xMrqrdt[  k + 1] = (double) k;
      if (useTregression) {
        yMrqrdt[  k + 1] = residualDataInput[i].t;
        sigMrqrdt[k + 1] = 1.0;
      } else {
        yMrqrdt[  k + 1] = (residualDataInput[i].depenG)[j];                   /* kJ/atom					            */
        sigMrqrdt[k + 1] = 1.0; /* sigWeights[(residualDataInput[i].cIndex)[j]]/14.0; kJ - 7 atoms in molecule --> 0.5 kJ uncertainty */
      }
      /* This is a kludge, assumed initial guess for parameters is zero */
      chisq += 0.0; /* yMrqrdt[k+1]*yMrqrdt[k+1]/(sigMrqrdt[k+1]*sigMrqrdt[k+1]); */
      k++;
    }
    printf("k (loop) = %d, nEqn = %d\n", k, nEqn);
 
#ifdef BUILD_MGO_SIO2_VERSION
    ma = 3*(nls*(nls-1)/2 + nls + npc) + 3*nc;
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
    ma = 3*(nls*(nls-1)/2 + nls + npc) + 3*nc;
#else
    ma = 3*(nls*(nls-1)/2 + nls + npc) + 3*(nc+1);
#endif
    aMrqrdt  =  vector(1, ma);
    iaMrqrdt = ivector(1, ma);

    for (i=0; i<(nls*(nls-1)/2 + nls + npc); i++) {
      aMrqrdt[  3*i     + 1] = modelParameters[i].enthalpy/SCALE; /*                                 i + 1 */
      aMrqrdt[  3*i + 1 + 1] = modelParameters[i].entropy;	  /*   (nls*(nls-1)/2 + nls + npc) + i + 1 */
      aMrqrdt[  3*i + 2 + 1] = modelParameters[i].volume;	  /* 2*(nls*(nls-1)/2 + nls + npc) + i + 1 */
      iaMrqrdt[ 3*i	+ 1] = modelParameters[i].activeH;	  /*				     i + 1 */
      iaMrqrdt[ 3*i + 1 + 1] = modelParameters[i].activeS;	  /*    npc + nls + nls*(nls-1)/2  + i + 1 */
      iaMrqrdt[ 3*i + 2 + 1] = modelParameters[i].activeV;	  /* 2*(npc + nls + nls*(nls-1)/2) + i + 1 */
    }
#ifdef BUILD_MGO_SIO2_VERSION
    for (i=0; i<nc; i++) {
      aMrqrdt[ 3*(nls*(nls-1)/2 + nls + npc)+3*i   + 1] = eosModelParameters[i].Kp;
      aMrqrdt[ 3*(nls*(nls-1)/2 + nls + npc)+3*i+1 + 1] = eosModelParameters[i].Kpp;
      aMrqrdt[ 3*(nls*(nls-1)/2 + nls + npc)+3*i+2 + 1] = eosModelParameters[i].Kppp;
      iaMrqrdt[3*(nls*(nls-1)/2 + nls + npc)+3*i   + 1] = eosModelParameters[i].activeKp;
      iaMrqrdt[3*(nls*(nls-1)/2 + nls + npc)+3*i+1 + 1] = eosModelParameters[i].activeKpp;
      iaMrqrdt[3*(nls*(nls-1)/2 + nls + npc)+3*i+2 + 1] = eosModelParameters[i].activeKppp;
    }
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
    for (i=0; i<nc; i++) {
      aMrqrdt[ 3*(nls*(nls-1)/2 + nls + npc)+3*i   + 1] = eosModelParameters[i].Kp;
      aMrqrdt[ 3*(nls*(nls-1)/2 + nls + npc)+3*i+1 + 1] = eosModelParameters[i].Kpp;
      aMrqrdt[ 3*(nls*(nls-1)/2 + nls + npc)+3*i+2 + 1] = eosModelParameters[i].Kppp;
      iaMrqrdt[3*(nls*(nls-1)/2 + nls + npc)+3*i   + 1] = eosModelParameters[i].activeKp;
      iaMrqrdt[3*(nls*(nls-1)/2 + nls + npc)+3*i+1 + 1] = eosModelParameters[i].activeKpp;
      iaMrqrdt[3*(nls*(nls-1)/2 + nls + npc)+3*i+2 + 1] = eosModelParameters[i].activeKppp;
    }
#else
    for (i=0; i<(nc+1); i++) {
      aMrqrdt[ 3*(nls*(nls-1)/2 + nls + npc)+3*i   + 1] = eosModelParameters[i].Kp;
      aMrqrdt[ 3*(nls*(nls-1)/2 + nls + npc)+3*i+1 + 1] = eosModelParameters[i].Kpp;
      aMrqrdt[ 3*(nls*(nls-1)/2 + nls + npc)+3*i+2 + 1] = eosModelParameters[i].Kppp;
      iaMrqrdt[3*(nls*(nls-1)/2 + nls + npc)+3*i   + 1] = eosModelParameters[i].activeKp;
      iaMrqrdt[3*(nls*(nls-1)/2 + nls + npc)+3*i+1 + 1] = eosModelParameters[i].activeKpp;
      iaMrqrdt[3*(nls*(nls-1)/2 + nls + npc)+3*i+2 + 1] = eosModelParameters[i].activeKppp;
    }
#endif
 
    covar = matrix(1, ma, 1, ma);
    alpha = matrix(1, ma, 1, ma);
 
    alamda = -1.0;
 
#ifdef GRACE_PIPE 
    GracePrintf("WITH G0\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.1, 0.4, 0.4);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, chisq);

      GracePrintf("XAXIS TICK MAJOR 5.0\n");
      GracePrintf("XAXIS TICK MINOR 1.0\n");
      GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("XAXIS LABEL \"iterate\"\n");
      GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("XAXIS LABEL COLOR 2\n");

      GracePrintf("YAXIS TICK MAJOR %lf\n", chisq/5.0);
      GracePrintf("YAXIS TICK MINOR %lf\n", chisq/10.0);
      GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS LABEL \"chi sqr\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");
      
    GracePrintf("G0 ON\n");
 
    GracePrintf("WITH G1\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.4, 0.40, 0.7);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, -9.0, 1.0, 1.0);

      GracePrintf("XAXIS TICK MAJOR 5.0\n");
      GracePrintf("XAXIS TICK MINOR 1.0\n");
      GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS TICK MAJOR 1.0\n");
      GracePrintf("YAXIS TICK MINOR 0.5\n");
      GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS LABEL \"log10 lambda\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");
      
    GracePrintf("G1 ON\n");

    GracePrintf("WITH G2\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1,  0.8, 0.40, 0.95);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0,  0.0, 10.0, 1.0);

      GracePrintf("XAXIS TICK MAJOR 2.0\n");
      GracePrintf("XAXIS TICK MINOR 1.0\n");
      GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("XAXIS LABEL \"rank\"\n");
      GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("XAXIS LABEL COLOR 2\n");

      GracePrintf("YAXIS TICK MAJOR 0.2\n");
      GracePrintf("YAXIS TICK MINOR 0.1\n");
      GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS LABEL \"sing value\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");
      
    GracePrintf("G2 ON\n");

    GracePrintf("WITH G3\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.50,  0.1, 0.85, 0.95);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0,  0.0, 1.0, 1.0);

      GracePrintf("XAXIS LABEL \"V[*][->]\"\n");
      GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("XAXIS LABEL COLOR 2\n");
      
      GracePrintf("YAXIS LABEL \"V[->][*]\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");

    GracePrintf("G3 ON\n");
    GracePrintf("G3 TYPE CHART\n");
    GracePrintf("G3 STACKED TRUE\n");

    GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, (double) 0, chisq);
    GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 1, (double) 0, -3.0);
    GracePrintf("REDRAW\n");
#endif /* GRACE_PIPE */
 
    loop   = 0;
    printf("Initial: chisq = %20.13g\n", chisq);
 
    DISPLAYI(mrqrdtADB[0], loop)
    DISPLAYI(mrqrdtADB[1], funcEvals)
    DISPLAYI(mrqrdtADB[4], nEqn)
    DISPLAYD(mrqrdtADB[8], chisq)
    DISPLAYD(mrqrdtADB[9], alamda)
 
    DISPLAY(actionADB[0], "Finished initializing Marquardt analysis. Execute to perfom an interation sequence")
  }
  
  curStep++;
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Perform a Trust Region Analysis or perform a Marquardt step
 *===========================================================================*/

  case REGRESS:
  
  if (useTrustRegionMethod) {
  
    int     n = (int    ) nEqn, p = (int    ) nParam;
    
    if ((n > 0) && (p > 0)) {
      int        kind    = 1;
      int        liv     = 82 + 4*p;
      int        lv      = 105 + p*(n + 2*p + 21) + 2*n;
      int        *iv     = (int     *)    malloc((size_t)     lv*sizeof(int    )); 
      double     *x      = (double     *) malloc((size_t)      p*sizeof(double    ));  
      double     *b      = (double     *) malloc((size_t)    2*p*sizeof(double    )); 
      double     *v      = (double     *) malloc((size_t)     lv*sizeof(double    )); 
      double     *urparm = (double     *) calloc((size_t) 2*p*n, sizeof(double    ));;
  
      for (i=0, j=0; i<(nls*(nls-1)/2 + nls + npc); i++) {
        if (modelParameters[i].activeH) {
	  x[j]      = modelParameters[i].enthalpy/SCALE;
	  b[2*j  ]  = (implementBounds && (i < nls*(nls-1)/2)) ?       0.0/SCALE : -DBL_MAX;
	  b[2*j+1]  = (implementBounds && (i < nls*(nls-1)/2)) ?  100000.0/SCALE :  DBL_MAX;
	  j++;
	}
	if (modelParameters[i].activeS) {
	  x[j]      = modelParameters[i].entropy;
	  b[2*j  ]  = -DBL_MAX;
	  b[2*j+1]  =  DBL_MAX;
	  j++;
	}
	if (modelParameters[i].activeV) {
	  x[j]      = modelParameters[i].volume;
	  b[2*j  ]  = -DBL_MAX;
	  b[2*j+1]  =  DBL_MAX;
	  j++;
	}
      }
      
#ifdef BUILD_MGO_SIO2_VERSION
      for (i=0; i<nc; i++) {
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
      for (i=0; i<nc; i++) {
#else
      for (i=0; i<(nc+1); i++) {
#endif
        if (eosModelParameters[i].activeKp) {
	  x[j]      = eosModelParameters[i].Kp;
	  b[2*j  ]  = -DBL_MAX;
	  b[2*j+1]  =  DBL_MAX;
	  j++;
	}
	if (eosModelParameters[i].activeKpp) {
	  x[j]      = eosModelParameters[i].Kpp;
	  b[2*j  ]  = -DBL_MAX;
	  b[2*j+1]  =  DBL_MAX;
	  j++;
	}
	if (eosModelParameters[i].activeKppp) {
	  x[j]      = eosModelParameters[i].Kppp;
	  b[2*j  ]  = -DBL_MAX;
	  b[2*j+1]  =  DBL_MAX;
	  j++;
	}
      }
      if (p != j) printf("Fatal logic error in setup for Trust Region Method.\n");

      (void) divset_(&kind, iv, &liv, &lv, v);
      
      /* urparm -> storage for saving jocobian matrix at two most recent parameter choices */
      setModeToMixingLiq(FALSE);
      (void) dn2gb_(&n, &p, x, b, calcr, calcj, iv, &liv, &lv, v, NULL, urparm, ufparm);
      setModeToMixingLiq(TRUE);
      
      free(iv); free(x); free(b); free(v); free(urparm);
    } else printf("Trust Region analysis bypassed. Number of equations (%d) or parameters (%d) zero.\n", (int) n, (int) p);
        
    curStep++;
  
  } else { /* !useTrustRegionMethod */
    if ((loop > 0) && XmToggleButtonGadgetGetState(mrqrdtADB[10])) {
      curStep++;
      DISPLAY(actionADB[0], "Marquardt analysis terminated by user.")
      workProcData->active = TRUE;
      return FALSE;
    }

    funcEvals = 0;
    loop++;
    oldChisq  = chisq;
    oldAlamda = alamda;
 
    for (i=1; i<=ma; i++) if ((iaMrqrdt[i] != 0) || (aMrqrdt[i] != 0.0)) printf("...iaMrqrdt[%2.2d] = %d, aMrqrdt[%2.2d] = %g\n", i, iaMrqrdt[i], i, aMrqrdt[i]);
 
    setModeToMixingLiq(FALSE);
    mrqminWithSVA(xMrqrdt, yMrqrdt, sigMrqrdt, nEqn, aMrqrdt, iaMrqrdt, ma, covar, alpha, &chisq, &alamda);
    setModeToMixingLiq(TRUE);

    printf("Iter: %d chisq = %20.13g, lamba = %20.13g, funcEvals = %d\n", loop, chisq, alamda, funcEvals);

    for (i=0; i<(nls+npc+nls*(nls-1)/2); i++) {
      if (iaMrqrdt[3*i  +1]) printf("H   [%20.20s] = %20.13g\n", modelParameters[i].label, aMrqrdt[3*i  +1]);
      if (iaMrqrdt[3*i+1+1]) printf("S   [%20.20s] = %20.13g\n", modelParameters[i].label, aMrqrdt[3*i+1+1]);
      if (iaMrqrdt[3*i+2+1]) printf("V   [%20.20s] = %20.13g\n", modelParameters[i].label, aMrqrdt[3*i+2+1]);
    }

#ifdef BUILD_MGO_SIO2_VERSION
    for (i=0; i<nc; i++) {
      if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i  +1]) printf("Kp  [%20.20s] = %20.13g\n", eosModelParameters[i].label, aMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i  +1]);
      if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+1+1]) printf("Kp  [%20.20s] = %20.13g\n", eosModelParameters[i].label, aMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+1+1]);
      if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+2+1]) printf("Kp  [%20.20s] = %20.13g\n", eosModelParameters[i].label, aMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+2+1]);
    }  
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
    for (i=0; i<nc; i++) {
      if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i  +1]) printf("Kp  [%20.20s] = %20.13g\n", eosModelParameters[i].label, aMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i  +1]);
      if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+1+1]) printf("Kp  [%20.20s] = %20.13g\n", eosModelParameters[i].label, aMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+1+1]);
      if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+2+1]) printf("Kp  [%20.20s] = %20.13g\n", eosModelParameters[i].label, aMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+2+1]);
    }  
#else
    for (i=0; i<(nc+1); i++) {
      if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i  +1]) printf("Kp  [%20.20s] = %20.13g\n", eosModelParameters[i].label, aMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i  +1]);
      if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+1+1]) printf("Kp  [%20.20s] = %20.13g\n", eosModelParameters[i].label, aMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+1+1]);
      if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+2+1]) printf("Kp  [%20.20s] = %20.13g\n", eosModelParameters[i].label, aMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+2+1]);
    }  
#endif

#ifdef GRACE_PIPE
    GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, (double) loop, chisq);
    GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 1, (double) loop, log10(alamda));
    GracePrintf("WITH G0\n"); GracePrintf("AUTOSCALE\n");
    GracePrintf("WITH G1\n"); GracePrintf("AUTOSCALE\n");
    GracePrintf("REDRAW\n");
#endif /* GRACE_PIPE */

    DISPLAYI(mrqrdtADB[0], loop)
    DISPLAYI(mrqrdtADB[1], funcEvals)
    DISPLAYD(mrqrdtADB[8], chisq)
    DISPLAYD(mrqrdtADB[9], alamda)
 
    DISPLAY(actionADB[0], "Completed intermediate step in Marquardt analysis.")
  }
  
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Perform post-regression error analysis
 *===========================================================================*/

  case POSTREGRESS:

  if (useTrustRegionMethod) {
  
  } else { /* !useTrustRegionMethod */
    alamda = 0.0; funcEvals = 0;

    if (loop > 0) {
      setModeToMixingLiq(FALSE);
      mrqminWithSVA(xMrqrdt, yMrqrdt, sigMrqrdt, nEqn, aMrqrdt, iaMrqrdt, ma, covar, alpha, &chisq, &alamda);
      setModeToMixingLiq(TRUE);

      printf("Final: chisq = %20.13g, lamba = %20.13g, funcEvals = %d\n", chisq, alamda, funcEvals);
      for (i=0; i<(nls+npc+nls*(nls-1)/2); i++) {
        if (iaMrqrdt[3*i  +1]) printf("H   [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", modelParameters[i].label, aMrqrdt[3*i  +1], sqrt(covar[3*i  +1][3*i  +1]));
        if (iaMrqrdt[3*i+1+1]) printf("S   [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", modelParameters[i].label, aMrqrdt[3*i+1+1], sqrt(covar[3*i+1+1][3*i+1+1]));
        if (iaMrqrdt[3*i+2+1]) printf("V   [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", modelParameters[i].label, aMrqrdt[3*i+2+1], sqrt(covar[3*i+2+1][3*i+2+1]));
      }
#ifdef BUILD_MGO_SIO2_VERSION
      for (i=0; i<nc; i++) {
        int j = 3*(nls+npc+nls*(nls-1)/2);
        if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i  +1]) printf("Kp  [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", eosModelParameters[i].label, aMrqrdt[j+3*i  +1], sqrt(covar[j+3*i  +1][j+3*i  +1]));
        if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+1+1]) printf("Kp  [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", eosModelParameters[i].label, aMrqrdt[j+3*i+1+1], sqrt(covar[j+3*i+1+1][j+3*i+1+1]));
        if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+2+1]) printf("Kp  [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", eosModelParameters[i].label, aMrqrdt[j+3*i+2+1], sqrt(covar[j+3*i+2+1][j+3*i+2+1]));
      }  
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
      for (i=0; i<nc; i++) {
        int j = 3*(nls+npc+nls*(nls-1)/2);
        if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i  +1]) printf("Kp  [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", eosModelParameters[i].label, aMrqrdt[j+3*i  +1], sqrt(covar[j+3*i  +1][j+3*i  +1]));
        if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+1+1]) printf("Kp  [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", eosModelParameters[i].label, aMrqrdt[j+3*i+1+1], sqrt(covar[j+3*i+1+1][j+3*i+1+1]));
        if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+2+1]) printf("Kp  [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", eosModelParameters[i].label, aMrqrdt[j+3*i+2+1], sqrt(covar[j+3*i+2+1][j+3*i+2+1]));
      }  
#else
      for (i=0; i<(nc+1); i++) {
        int j = 3*(nls+npc+nls*(nls-1)/2);
        if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i  +1]) printf("Kp  [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", eosModelParameters[i].label, aMrqrdt[j+3*i  +1], sqrt(covar[j+3*i  +1][j+3*i  +1]));
        if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+1+1]) printf("Kp  [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", eosModelParameters[i].label, aMrqrdt[j+3*i+1+1], sqrt(covar[j+3*i+1+1][j+3*i+1+1]));
        if (iaMrqrdt[3*(nls+npc+nls*(nls-1)/2)+3*i+2+1]) printf("Kp  [%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", eosModelParameters[i].label, aMrqrdt[j+3*i+2+1], sqrt(covar[j+3*i+2+1][j+3*i+2+1]));
      }  
#endif
      printf("Correlation coefficient matrix:\n");
      for (i=1; i<=ma; i++) if (iaMrqrdt[i]) {
  	for (j=1; j<=ma; j++) if (iaMrqrdt[j]) printf("%6.2f ", covar[i][j]/(sqrt(covar[i][i])*sqrt(covar[j][j])));
  	printf("\n");
      }
    }
    DISPLAY(actionADB[0], "Completed final step in Marquardt analysis.")
  }

  curStep++;
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Write out solution
 *===========================================================================*/

  case SOLUTION:

  writeParameters("param_struct_data.preclb");

  curStep++;
  DISPLAY(actionADB[0], "New parameter written. Ready to analyze residuals.")
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Return to interface, release temporary storage
 *===========================================================================*/
  
  case FINAL:

  curStep = 0;
  
#ifdef USE_MPI
  /* We have all the answers now, so kill the living workers. */
  for (i=0; i<ntasks; ++i) {
    int err;
    printf("MPI:preclb[preclb.c at line %d]--> Finalizing slave %d.\n", __LINE__, i);
    if (icomm_slaves[i] == MPI_COMM_NULL) continue;

    printf("MPI:preclb[preclb.c at line %d]--> Slave %d exits.\n", __LINE__, i);
    err = MPI_Send((void *) 0, 0, MPI_INT, 0, DIETAG, icomm_slaves[i]);
    if (err != MPI_SUCCESS) MPI_Comm_free(&icomm_slaves[i]);
  }

  /* If any one of the slaves died, abort on just myself
   * (MPI_COMM_SELF).  If we abort on MPI_COMM_WORLD, LAM will
   * try to kill all processes (one or more of which is now
   * already dead and possibly unresponsive, so LAM would hang.
   * Hence, just abort on MPI_COMM_SELF).  See the MPI_Abort(3)
   * man page for an explanation of the error code. */
  if (return_status != 0) {
    printf("MPI:preclb[preclb.c at line %d]--> Errors arose from slave elimination.\n", __LINE__);
    MPI_Abort(MPI_COMM_SELF, (return_status << 16) + 1);
  }

  /*  This is done to avoid a bug in Open mpi that happens when 
      the laptop is added to the cluster
  printf("MPI:preclb[preclb.c at line %d]--> Calling MPI_finalize().\n", __LINE__);
  MPI_Finalize();
  */

#endif

  workProcData->active = FALSE; 
  return TRUE;

  } /* end switch */

  return TRUE;
}

/* end of file PRECLB.C */
