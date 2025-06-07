
/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Routine to evaluate liquid model parameters by regression of
**      selected entropies of fusion (file: ENTROPY_REG.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  January 24, 2000 Original Version
**              Canabalized from test_entropy
**--
*/

#include "silmin.h"
#include "recipes.h"

#ifdef BUILD_MGO_SIO2_VERSION
#include "liq_struct_data_MgO_SiO2.h"
#include "sol_struct_data_MgO_SiO2.h"
#include "param_struct_data_MgO_SiO2.h"
#else
#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"
#endif /* BUILD_MGO_SIO2_VERSION */ 

int calculationMode = MODE_DEFAULT;
void *main_window, *silmin_adb, *topLevel, *meltsEnviron;
SilminState *silminState;

#include <unistd.h>
#include <grace_np.h>

static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}


struct _fusion {
  const char   *name;
  const char   *formula;
  const double t;
  const double p;
  const double s;
  const double error;
} fusion[] = {
/*  {"akermanite",         "Ca2MgSi2O7",     1727.0,  1.0,  71.7,  1.9 },
    {"albite",             "NaAlSi3O8",      1373.0,  1.0,  45.7,  1.5 },
    {"albite",             "NaAlSi3O8",      1373.0,  1.0,  46.2,  2.2 },
    {"albite",             "NaAlSi3O8",      1393.0,  1.0,  46.3,  2.2 },
    {"anorthite",          "CaAl2Si2O8",     1830.0,  1.0,  74.1,  4.8 },
    {"anorthite",          "CaAl2Si2O8",     1830.0,  1.0,  72.7,  2.2 },
*/  {"clinoenstatite",     "Mg2Si2O6",       1834.0,  1.0,  79.8,  6.6 },
/*  {"co-olivine",	   "Co2SiO4",	     1688.0,  1.0,  58.0,  5.0 },
    {"cordierite",	   "Mg2Al4Si5O18",   1740.0,  1.0, 199.0,  6.0 },
    {"corundum",           "Al2O3",          2323.0,  1.0,  46.3,  2.3 },
    {"cristobalite",       "SiO2",           1999.0,  1.0,   4.46, 0.5 },
    {"diopside",           "CaMgSi2O6",      1670.0,  1.0,  82.5,  1.2 },
    {"fayalite",	   "Fe2SiO4",	     1490.0,  1.0,  59.9,  0.7 },
    {"fluorphlogopite",    "KMg3AlSi3O10F2", 1670.0,  1.0, 185.0,  1.0 },
*/  {"forsterite",         "Mg2SiO4",        2174.0,  1.0,  65.3,  6.0 } /*,
    {"gehlenite",          "Ca2Al2SiO7",     1863.0,  1.0,  92.4,  3.2 },
    {"hematite",	   "Fe2O3",          1895.0,  1.0,  60.4,  0.0 },
    {"ilmenite",	   "FeTiO3",         1640.0,  1.0,  13.2,  0.1 },
    {"jadeite",            "NaAlSi2O6",      1100.0,  1.0,  53.9,  2.7 },
    {"kalsilite",	   "KAlSiO4",        2023.0,  1.0,  24.5,  0.0 },
    {"kdisilicate",        "K2Si2O5",        1309.0,  1.0,  24.3,  3.6 },
    {"kdisilicate",        "K2Si2O5",        1318.0,  1.0,  24.3,  3.0 },
    {"kmsilicate",         "K2SiO3",         1249.0,  1.0,  15.7,  3.2 },
    {"larnite",	           "Ca2SiO4",        2403.0,  1.0,  75.74, 0.0 },
    {"magnetite",	   "Fe3O4",          1870.0,  1.0,  73.84, 0.0 },
    {"mgchromite",	   "MgCr2O4",        2673.15, 1.0,  73.22, 0.0 },
    {"nadisilicate",       "Na2Si2O5",       1147.0,  1.0,  38.7,  3.6 },
    {"nadisilicate",       "Na2Si2O5",       1147.0,  1.0,  32.9,  3.8 },
    {"namsilicate",        "Na2SiO3",        1361.0,  1.0,  38.34, 0.5 },
    {"namsilicate",        "Na2SiO3",        1362.0,  1.0,  38.2,  0.7 },
    {"nepheline",          "NaAlSiO4",       1750.0,  1.0,  28.0,  1.2 },
    {"nepheline",          "NaAlSiO4",       1720.0,  1.0,  26.9,  1.2 },
    {"ni-olivine",	   "Ni2SiO4",	     1923.0,  1.0,  58.0,  5.0 },
    {"pseudowollastonite", "CaSiO3",         1817.0,  1.0,  31.50, 1.6 },
    {"pyrope",             "Mg3Al2Si3O12",   1500.0,  1.0, 162.0,  5.0 },
    {"pyrope",             "Mg3Al2Si3O12",   1570.0,  1.0, 154.1,  7.6 },
    {"quartz",             "SiO2",           1700.0,  1.0,   5.53, 0.56},
    {"rutile",	           "TiO2",	     1870.0,  1.0,  35.8,  0.0 },
    {"sanidine",           "KAlSi3O8",       1473.0,  1.0,  39.2,  2.8 },
    {"sanidine",           "KAlSi3O8",       1500.0,  1.0,  36.0,  2.7 },
    {"sphene",  	   "CaTiSiO5",       1670.0,  1.0,  74.1,  0.2 },
    {"spinel",	           "MgAl2O4",        2408.0,  1.0,  44.0,  4.0 },
    {"tephroite",	   "Mn2SiO4",	     1620.0,  1.0,  55.2,  0.3 },
    {"whitlockite",	   "Ca3(PO4)2",      1943.0,  1.0,  35.7,  0.0 },
    {"wollastonite",       "CaSiO3",         1770.0,  1.0,  34.9,  2.3 },
    {"wustite", 	   "Fe0.947O",       1652.0,  1.0,  19.0,  0.1 } */
};
int nFus = (sizeof fusion / sizeof(struct _fusion));

static double  *sRef, *hRef;
static double **rLiq;
static double  *sLiq, *hFus;
static double  *sFus;

static int funcEvals;

static void initializeSystem(void) {
  int i, j, k;
  
  printf("Calling function: InitComputeDataStruct().\n");
  InitComputeDataStruct();
  
  printf("Allocating and computing reference arrays.\n");
  sRef = (double  *) malloc((size_t) nFus*sizeof(double  ));
  hRef = (double  *) malloc((size_t) nFus*sizeof(double  ));
  sLiq = (double  *) malloc((size_t) nFus*sizeof(double  ));
  rLiq = (double **) malloc((size_t) nFus*sizeof(double *));
  sFus = (double  *) malloc((size_t) nFus*sizeof(double  ));
  hFus = (double  *) malloc((size_t) nFus*sizeof(double  ));
  for (i=0; i<nFus; i++) rLiq[i] = (double *) malloc((size_t) nlc*sizeof(double));

  setModeToMixingLiq(FALSE);

  for (i=0; i<nFus; i++) {
    printf("... generating ref fusion properties for %s.\n", fusion[i].name);
    for (j=0; j<npc; j++) {
      if ((solids[j].ref).h != 0.0 && strcmp(fusion[i].name, solids[j].label) == 0 && strcmp(fusion[i].formula, solids[j].formula) == 0) {
      
        conLiq(SECOND, THIRD, fusion[i].t, fusion[i].p, NULL, solids[j].solToLiq, rLiq[i], NULL, NULL, NULL, NULL);
	
	if (testLiq(FIFTH, fusion[i].t, fusion[i].p, 0, 0, NULL, NULL, rLiq[i], NULL)) {
          for (k=0, sLiq[i]=0.0; k<nlc; k++) sLiq[i] += (solids[j].solToLiq)[k];
	  
	  sRef[i] = 0.0; 
	  hRef[i] = 0.0;

          gibbs(fusion[i].t, fusion[i].p, (char *) solids[j].label, &(solids[j].ref), NULL, NULL, &(solids[j].cur));
          sRef[i] -= (solids[j].cur).s;
          hRef[i] -= (solids[j].cur).h;

	} else { printf("--> Generates negative mole fractions.\n"); exit(0); }
        break;
      }
    }
  }
  
  
}

static void getSandDeriv(double x, double *a, double *y, double *dyda, int ma) {
  int i, index = (int) (fabs(x) - 1);
  double sConfig, hConfig;
  
  funcEvals++;
  
  for (i=0; i<(nls*(nls-1)/2 + nls); i++) {
    if (modelParameters[i].activeH) modelParameters[i].enthalpy = a[			    i + 1]*1000.0;
    if (modelParameters[i].activeS) modelParameters[i].entropy  = a[  (nls*(nls-1)/2 + nls)+i + 1];
    if (modelParameters[i].activeV) modelParameters[i].volume	= a[2*(nls*(nls-1)/2 + nls)+i + 1];
    if (modelParameters[i].activeF) {
      modelParameters[i].activeH = TRUE;
      modelParameters[i].enthalpy = (fusion[index].t)*a[(nls*(nls-1)/2 + nls)+i + 1];
    }
  }
 
  if (x > 0.0) {
    smixLiq (FIRST | FOURTH, fusion[index].t, fusion[index].p, rLiq[index], &sConfig, NULL, NULL, &dyda[1]);
    *y =  sRef[index] + sLiq[index]*sConfig;         
    sFus[index] = *y;
  } else if (x < 0.0) {
    hmixLiq (FIRST | SECOND, fusion[index].t, fusion[index].p, rLiq[index], &hConfig, &dyda[1]);
    *y = (hRef[index] + sLiq[index]*hConfig)/1000.0; 
    hFus[index] = *y;
    for (i=1; i<=ma; i++) dyda[i] *= sLiq[index]/1000.0;
  } else { 
    printf("Fatal error in getSandDeriv(). Exiting to system.\n");
    exit(0);
  }
    
  for (i=0; i<(nls*(nls-1)/2 + nls); i++) {
    if (modelParameters[i].activeF) {
      modelParameters[i].activeH = FALSE;
      dyda[(nls*(nls-1)/2 + nls)+i + 1] += (fusion[index].t)*dyda[i + 1];
    }
    if (modelParameters[i].activeH) dyda[			 i + 1] *= sLiq[index]*1000.0;
    if (modelParameters[i].activeS) dyda[  (nls*(nls-1)/2 + nls)+i + 1] *= sLiq[index];
    if (modelParameters[i].activeV) dyda[2*(nls*(nls-1)/2 + nls)+i + 1] *= sLiq[index];
  }
    
}

/* Modified from Numerical Recipes mrqmin routine (v 2.0) */

static void mrqminWithSVA(double x[], double y[], double sig[], int ndata, double a[], int ia[],
  int ma, double **covar, double **alpha, double *chisq,
  void (*funcs)(double, double [], double *, double [], int), double *alamda)
{
  int j, k, l, m, rank;
  double wMin, wMax;
  
  static int mfit, graphSet=0;
  static unsigned long *key;
  static double ochisq, *atry, *beta, *da, *wSVA, **vSVA;
  static char *eSVA;

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
    mrqcof(x, y, sig, ndata, a, ia, ma, alpha, beta, chisq, funcs);
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
  
  indexx(mfit, wSVA, key);
  GracePrintf("WITH G2\n"); graphSet++;
  for (j=1; j<=mfit; j++) GracePrintf("g2.s%d POINT %lf, %g\n", graphSet, (double) j, (wSVA[key[mfit+1-j]] > 0.0) ? wSVA[key[mfit+1-j]] : DBL_EPSILON);
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

    for (j=1, k=0; j<=ma; j++) if (ia[j]) {
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
      GracePrintf("STRING DEF \"%1.1s %18.18s\"\n", (j < (nls+nls*(nls-1)/2+1)) ? "H" : "S",
        (j < (nls+nls*(nls-1)/2+1)) ? modelParameters[j-1].label : modelParameters[j-nls-nls*(nls-1)/2-1].label);
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
  
  for (wMax=0.0, j=1; j<=mfit; j++) if (wSVA[j] > wMax) wMax = wSVA[j];
  wMin = wMax*1.0e-6;
  for (j=1, rank=mfit; j<=mfit; j++) {
    printf("--->w: %20.13e (wMin: %20.13e, wMax: %20.13e)\n", wSVA[j], wMin, wMax);
    if (wSVA[j] < wMin) { wSVA[j] = 0.0; rank--; }
  }
  printf("--->In mrqmin (with SVA) computed rank is %d\n", rank);
  
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
  for (j=0,l=1; l<=ma; l++) if (ia[l]) atry[l] = a[l] + da[++j];
  mrqcof(x, y, sig, ndata, atry, ia, ma, covar, da, chisq, funcs);
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

int main(int argc, char *argv[])
{
  const int loopMax = 25;
  int i, j, ndata, ma, *ia, loop, i1, i2;
  double *x, *y, *sig, *a, **covar, **alpha, chisq, alamda, oldChisq, oldAlamda;
  FILE *output;

  printf("Opening output file entropy_reg.out.\n");
  output = fopen ("entropy_reg.out", "w");
  
  initializeSystem();
  
  x   = vector(1, 2*nFus);  /* Index of fusion entropy/enthalpy value to fit rLiq[index][] */
  y   = vector(1, 2*nFus);  /* Fusion entropy/enthalpy to fit                              */
  sig = vector(1, 2*nFus);  /* Uncertainty on fusion entropy/enthalpy                      */
  
  ndata = 2*nFus;
  for (i=0; i<nFus; i++) {
    x[2*i + 1]   = (double)   i + 1;
    x[2*i + 2]   = (double) -(i + 1);
    y[2*i + 1]   = fusion[i].s;
    y[2*i + 2]   = fusion[i].t*fusion[i].s/1000.0;
    sig[2*i + 1] = (fusion[i].error != 0.0) ?             fusion[i].error :                    0.20*fusion[i].s;
    sig[2*i + 2] = (fusion[i].error != 0.0) ? fusion[i].t*fusion[i].error/1000.0 : fusion[i].t*0.20*fusion[i].s/1000.0;
  }
  
  /*******************************************************************************
    Parameter order:
                                1 ...           nls*(nls-1)/2 W(H) parameters
                nls*(nls-1)/2 + 1 ...   nls +   nls*(nls-1)/2 EndMem(H) parameters
        nls +   nls*(nls-1)/2 + 1 ...   nls + 2*nls*(nls-1)/2 W(H) parameters
        nls + 2*nls*(nls-1)/2 + 1 ... 2*nls + 2*nls*(nls-1)/2 EndMem(S) parameters
      2*nls + 2*nls*(nls-1)/2 + 1 ... 2*nls + 3*nls*(nls-1)/2 W(V) parameters
      2*nls + 3*nls*(nls-1)/2 + 1 ... 3*nls + 3*nls*(nls-1)/2 EndMem(V) parameters
      
    Species order:
      ( 1) SiO2      ( 2) TiO2	   ( 3) Al2O3      ( 4) Fe2O3      ( 5) Cr2O3   
      ( 6) FeO       ( 7) MnO      ( 8) MgO        ( 9) NiO        (10) CoO   
      (11) CaO       (12) Na2O     (13) K2O        (14) P2O5       (15) CO2	  
      (16) SO3	     (17) Cl2O-1   (18) F2O-1      (19) H2O	   (20) FeO1.3  
      (21) Si0.25OH  (22) Fe2SiO4  (23) FeSiO3     (24) Mn2SiO4    (25) MnSiO3
      (26) Mg2SiO4   (27) MgSiO3   (28) Ni2SiO4    (29) NiSiO3     (30) Co2SiO4
      (31) CoSiO3    (32) Ca2SiO4  (33) CaSiO3     (34) Na2SiO3    (35) NaAlO2
      (36) K2SiO3    (37) KAlO2    (38) Ca3(PO4)2    
      
    W[i=1=Si4O8][j=2..nls] = j-1
    W[i=2=TiO2 ][j=3..nls] = nls-1 + j-2
    W[i=3=Al2O3][j=4..nls] = nls-1 + nls-2 + j-3
    W[i=4=Fe2O3][j=5..nls] = nls-1 + nls-2 +nls-3 +j-4 
   *******************************************************************************/
  ma = 3*(nls*(nls-1)/2 + nls);
  a  =  vector(1, ma);
  ia = ivector(1, ma);
  for (i=1; i<=ma; i++) ia[i] = 0;
  for (i=0; i<(nls*(nls-1)/2 + nls); i++) {
    a[  		      i + 1] = modelParameters[i].enthalpy/1000.0;
    a[  (nls*(nls-1)/2 + nls)+i + 1] = modelParameters[i].entropy;
    a[2*(nls*(nls-1)/2 + nls)+i + 1] = modelParameters[i].volume;
  }
  
  ia[nls + 2*nls*(nls-1)/2 +  1] = 1;    modelParameters[nls*(nls-1)/2 - 1 +  1].activeS = TRUE;  /* S SiO2       */  
                                         modelParameters[nls*(nls-1)/2 - 1 +  1].activeF = TRUE;  /* H SiO2       */
  ia[nls + 2*nls*(nls-1)/2 +  8] = 1;    modelParameters[nls*(nls-1)/2 - 1 +  8].activeS = TRUE;  /* S MgO        */  
                                         modelParameters[nls*(nls-1)/2 - 1 +  8].activeF = TRUE;  /* H MgO        */
  ia[nls + 2*nls*(nls-1)/2 + 26] = 1;    modelParameters[nls*(nls-1)/2 - 1 + 26].activeS = TRUE;  /* S Mg2SiO4    */  
                                         modelParameters[nls*(nls-1)/2 - 1 + 26].activeF = TRUE;  /* H Mg2SiO4    */
  ia[nls + 2*nls*(nls-1)/2 + 27] = 1;    modelParameters[nls*(nls-1)/2 - 1 + 27].activeS = TRUE;  /* S MgSiO3     */  
                                         modelParameters[nls*(nls-1)/2 - 1 + 27].activeF = TRUE;  /* H MgSiO3     */

  i1 =  1; /* SiO2 */
  i2 = 27; /* MgSiO3 */					  
  ia[nls*(i1-1)-i1*(i1-1)/2+i2-i1] = 1;  modelParameters[nls*(i1-1)-i1*(i1-1)/2+i2-i1-1].activeH = TRUE;

  i1 = 26; /* Mg2SiO4 */
  i2 = 27; /* MgSiO3 */					  
  ia[nls*(i1-1)-i1*(i1-1)/2+i2-i1] = 1;  modelParameters[nls*(i1-1)-i1*(i1-1)/2+i2-i1-1].activeH = TRUE;

  i1 =  8; /* MgO */
  i2 = 26; /* Mg2SiO4 */					  
  ia[nls*(i1-1)-i1*(i1-1)/2+i2-i1] = 1;  modelParameters[nls*(i1-1)-i1*(i1-1)/2+i2-i1-1].activeH = TRUE;

  covar = matrix(1, ma, 1, ma);
  alpha = matrix(1, ma, 1, ma);
  
  alamda = -1.0;
  
  for (i=0, chisq=0.0; i<nFus; i++) {
    smixLiq (FIRST, fusion[i].t, fusion[i].p, rLiq[i], &sFus[i], NULL, NULL, NULL);
    sFus[i] = sRef[i] + sFus[i]*sLiq[i];
    chisq += (y[2*i+1] - sFus[i])*(y[2*i+1] - sFus[i])/(sig[2*i+1]*sig[2*i+1]);
    hmixLiq (FIRST, fusion[i].t, fusion[i].p, rLiq[i], &hFus[i], NULL);
    hFus[i] = (hRef[i] + hFus[i]*sLiq[i])/1000.0;
    chisq += (y[2*i+2] - hFus[i])*(y[2*i+2] - hFus[i])/(sig[2*i+2]*sig[2*i+2]);
  }
  printf("Initial: chisq = %20.13g\n", chisq);	
  for (i=1; i<=ma; i++) if (ia[i]) printf("Param[%20.20s] = %20.13g\n", (i < (nls+nls*(nls-1)/2+1)) ? modelParameters[i-1].label :
    modelParameters[i-nls-nls*(nls-1)/2-1].label, a[i]);
  for (i=0; i<nFus; i++) 
    printf("%10.10s %15.15s S Fus = %6.2f+/-%6.2f Pred = %6.2f (%6.2f) t = %6.3f H Fus = %7.3f+/-%7.3f Pred = %7.3f (%7.3f)\n",
    fusion[i].name, fusion[i].formula, fusion[i].s, fusion[i].error, sFus[i], fusion[i].s-sFus[i], (fusion[i].s-sFus[i])/sig[2*i+1], 
    fusion[i].s*fusion[i].t/1000.0, fusion[i].error*fusion[i].t/1000.0, hFus[i], fusion[i].s*fusion[i].t/1000.0-hFus[i]);

  GraceRegisterErrorFunction (grace_error_function);
  if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }
  
  GracePrintf("WITH G0\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.1, 0.40, 0.4);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, (double) loopMax, chisq);

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
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, -9.0, (double) loopMax, 1.0);

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

    GracePrintf("XAXIS LABEL \"V[->][*]\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS LABEL \"V[*][->]\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");

    GracePrintf("G3 ON\n");
    GracePrintf("G3 TYPE CHART\n");
    GracePrintf("G3 STACKED TRUE\n");

  GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, (double) 0, chisq);
  GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 1, (double) 0, -3.0);
  GracePrintf("REDRAW\n");
  
  loop   = 0;
  do {
    funcEvals = 0;
    loop++;
    oldChisq  = chisq;
    oldAlamda = alamda;
    mrqminWithSVA(x, y, sig, ndata, a, ia, ma, covar, alpha, &chisq, getSandDeriv, &alamda);
    printf("Iter: %d chisq = %20.13g, lamba = %20.13g, funcEvals = %d\n", loop, chisq, alamda, funcEvals);   
    for (i=1; i<=ma; i++) if (ia[i]) printf("Param[%20.20s] = %20.13g\n", (i < (nls+nls*(nls-1)/2+1)) ? modelParameters[i-1].label :
      modelParameters[i-nls-nls*(nls-1)/2-1].label, a[i]);
    for (i=0; i<nFus; i++) 
      printf("%10.10s %15.15s S Fus = %6.2f+/-%6.2f Pred = %6.2f (%6.2f) t = %6.3f H Fus = %7.3f+/-%7.3f Pred = %7.3f (%7.3f)\n",
      fusion[i].name, fusion[i].formula, fusion[i].s, fusion[i].error, sFus[i], fusion[i].s-sFus[i], (fusion[i].s-sFus[i])/sig[2*i+1], 
      fusion[i].s*fusion[i].t/1000.0, fusion[i].error*fusion[i].t/1000.0, hFus[i], fusion[i].s*fusion[i].t/1000.0-hFus[i]);
      
    GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, (double) loop, chisq);
    GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 1, (double) loop, log10(alamda));
    GracePrintf("WITH G0\n"); GracePrintf("AUTOSCALE\n"); 
    GracePrintf("WITH G1\n"); GracePrintf("AUTOSCALE\n"); 
    GracePrintf("REDRAW\n");
    
  } while ( (loop < loopMax) && ( (alamda > oldAlamda) || (fabs(chisq-oldChisq) > 0.01*fabs(chisq)) ) );
  
  alamda = 0.0; funcEvals = 0;

  mrqminWithSVA(x, y, sig, ndata, a, ia, ma, covar, alpha, &chisq, getSandDeriv, &alamda);
  printf("Final: chisq = %20.13g, lamba = %20.13g, funcEvals = %d\n", chisq, alamda, funcEvals);   
  for (i=1; i<=ma; i++) if (ia[i]) printf("Param[%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", (i < (nls+nls*(nls-1)/2+1)) ? modelParameters[i-1].label :
    modelParameters[i-nls-nls*(nls-1)/2-1].label, a[i], sqrt(covar[i][i]));
  for (i=0; i<nFus; i++) 
    printf("%10.10s %15.15s S Fus = %6.2f+/-%6.2f Pred = %6.2f (%6.2f) t = %6.3f H Fus = %7.3f+/-%7.3f Pred = %7.3f (%7.3f)\n",
    fusion[i].name, fusion[i].formula, fusion[i].s, fusion[i].error, sFus[i], fusion[i].s-sFus[i], (fusion[i].s-sFus[i])/sig[2*i+1], 
    fusion[i].s*fusion[i].t/1000.0, fusion[i].error*fusion[i].t/1000.0, hFus[i], fusion[i].s*fusion[i].t/1000.0-hFus[i]);
  printf("Correlation coefficient matrix:\n");
  for (i=1; i<=ma; i++) if (ia[i]) {
    for (j=1; j<=ma; j++) if (ia[j]) printf("%6.2f ", covar[i][j]/(sqrt(covar[i][i])*sqrt(covar[j][j])));
    printf("\n");
  }

  printf("Exit program (y or n)? ");
  getchar();
  getchar();
  exit(0);
}

/* End file: ENTROPY_REG.C */

