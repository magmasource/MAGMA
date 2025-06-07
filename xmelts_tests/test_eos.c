const char *test_eos_ver(void) { return "$Id: test_eos.c,v 1.11 2008/09/18 16:17:17 ghiorso Exp $"; }

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Test routine to evaluate the functions defined for the computation
**      of EOS properties in the liquid 
**      (file: TEST_EOS.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  February 22, 2007 Original Version
**--
*/

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include "interface.h"
Widget main_window, silmin_adb, topLevel;
MeltsEnviron meltsEnviron;

static void intenToExtenGradient(double pMix, double *dpMix, int nr,  double *dp, 
  int na, double mTotal, double **drdm)
{
  int i, j;
  
  for (j=0; j<na; j++) {
    for (i=0, dp[j] = 0.0; i<nr; i++) dp[j] += dpMix[i]*drdm[i][j];
    dp[j] = mTotal*dp[j] + pMix;
  }
}

typedef struct _eosRefParameters {
  double v, dvdt, cRef, dcdt, cp, d2vdp2, d3vdp3, d4vdp4, mw;
  double alpha, v0, v1, v2, v3, v4, a, b;
  double K, Kp, Kpp, Kppp;    
} EosRefParameters;

EosRefParameters *getEosRefParameters(double *r);

#include "silmin.h"
#include "recipes.h"

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

#include <unistd.h>
#include <grace_np.h>

SilminState *silminState;
int calculationMode = MODE_DEFAULT;

static const int iOxFe2O3      =  3; /* Index of Fe2O3 in bulksystem[] structure array    */
static const int iOxFeO        =  5; /* Index of FeO in bulksystem[] structure array      */
static const int iOxFeO1_3     = 19; /* Index of FeO1.3 in bulksystem[] structure array   */

double integralV_GKsp(int index, double t, double p);

static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}

int main()
{
  int i, j, doRandom=TRUE;
  int nr = nlc - 1;
  float ftemp;
  double t = 2300.0 + 273.15;
  double p = 235000.0;
  /*		     SiO2 TiO2 Al2O3 Fe2O3 Cr2O3 0.24  FeO  MnO 0.19   MgO   NiO 0.16  CoO	CaO Na2O  K2O P2O5  H2O   CO2	SO3 Cl2O-1 F2O-1 */
  double grams[] = { 44.75, 0.27, 2.42,  0.0, 0.0, 9.15, 0.0, 32.04, 0.0, 0.0, 8.36, 0.6, 0.09, 0.0, 0.0, 0.0, 0.0,  0.0, 0.0 };
  double *moles, *x, *mu, *xSpecies, g, v, *dvdx, *dvdm, sum, dvdt, dvdp, d2vdp2, mTliq, mTox, **drdm, *molesTemp, *xTemp, mTliqTemp;
  int nStishovite = -1, nGrossular = -1, nPyrope = -1, nAlmandine = -1, nMajorite = -1, nMgwustite = -1, nFewustite = -1;
  int nDiopside = -1, nEnstatite = -1, nHedenbergite = -1;
  EosRefParameters *eos;

  printf("---> Default calculation mode is xMELTS.  Change this? (y or n): ");
  if (tolower(getchar()) == 'y') {
    getchar();
    printf("     Set calculation mode is MELTS (public release v 3.0.x)? (y or n): ");
    if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE__MELTS; }
    else {
      getchar();
      printf("     Set calculation mode is pMELTS (public release v 4.0.x)? (y or n): ");
      if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE_pMELTS; }
    }
  } else getchar();
  
  if (calculationMode == MODE_xMELTS) {
    printf("---> Calculation mode is xMELTS (experimental v 5.0.x).\n");
  } else if (calculationMode == MODE__MELTS) {
    printf("---> Calculation mode is MELTS (public release v 3.0.x).\n");
    liquid = meltsLiquid;
    solids = meltsSolids;
    nlc = meltsNlc;
    nls = meltsNls;
    npc = meltsNpc;
  } else if (calculationMode == MODE_pMELTS) {
    printf("---> Calculation mode is pMELTS (public release v 4.0.x).\n");
    liquid = pMeltsLiquid;
    solids = pMeltsSolids;
    nlc = pMeltsNlc;
    nls = pMeltsNls;
    npc = pMeltsNpc;
  }
  
   printf("***************************************************\n");
   printf("Converting default v2,v3,v4 into K',K'',K'''       \n");
   printf("***************************************************\n\n");
   
   for (i=0; i<nc+1; i++) {
     double v0    = bulkSystem[i].gk_v;
     double dvdt  = bulkSystem[i].gk_dvdt;
     double c     = bulkSystem[i].gk_c;
     double cp    = bulkSystem[i].gk_cp;
     double v2    = bulkSystem[i].gk_d2vdp2;
     double v3    = bulkSystem[i].gk_d3vdp3;
     double v4    = bulkSystem[i].gk_d4vdp4;
     double mw    = bulkSystem[i].mw;
     double alpha = dvdt/v0; 
     double v1    = -v0*v0*(1000.0/(mw*c*c) + 1673.15*alpha*alpha/cp);
     
     double K    = -v0/v1;
     double Kp   = K*K*v2/v0 - 1.0;
     double Kpp  = (K*K*K*v3/v0 + (2.0*Kp+1.0)*(Kp+1.0))/K;
     double Kppp = (K*K*K*K*v4/v0 - (3.0*Kp+1.0)*(2.0*Kp+1.0)*(Kp+1.0) + Kpp*K*(4.0+6.0*Kp))/(K*K);
     
     printf("%13.6g,%13.6g,%13.6g,%13.6g,---,%13.6g,%13.6g,%13.6g\n", K, Kp, Kpp, Kppp, v2, v3, v4);
   }

   printf("***************************************************\n");
   printf("Calling function: InitComputeDataStruct().         \n");
   printf("***************************************************\n\n");
   InitComputeDataStruct();

   setModeToMixingLiq(FALSE);

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Input test compositions (y or n)? ");
   if (tolower(getchar()) == 'y') doRandom = FALSE;
   getchar();
     
   for (i=0; i<(nls*(nls-1)/2+nls); i++) { modelParameters[i].activeH = TRUE; modelParameters[i].activeS = TRUE; modelParameters[i].activeV = TRUE; }
      
   /**************************************************************************
    Evaluate t and p choices for calculations                        
    **************************************************************************/
   
   printf("Do calculations at %7.2f C (y or n)? ", t-273.15);
   if (tolower(getchar()) != 'y') {
     getchar();
     printf("Input a temperature in (C):"); scanf("%f", &ftemp); t = ((double) ftemp)
     +273.15;
     getchar();
   } else getchar();
   
   printf("Do calculations at %7.2f bars (y or n)? ", p);
   if (tolower(getchar()) != 'y') {
     getchar();
     printf("Input a pressure in (bars):"); scanf("%f", &ftemp); p = (double) ftemp;
     getchar();
   } else getchar();

   printf("*******************************************************\n");
   printf("* Calculations at %7.2f (C) and %8.2f (bars) *\n", t-273.15, p);
   printf("*******************************************************\n\n");

   /***************************************************************************
    Allocate space for required vectors and matrices                 
    ***************************************************************************/
         
   moles    = vector(0, nlc-1);
   x        = vector(0, nr-1);
   mu       = vector(0, nlc-1);
   xSpecies = vector(0, nls-1);
   dvdx     = vector(0, nr-1);
   dvdm     = vector(0, nlc-1);
   drdm     = matrix(0, nr-1, 0, nlc-1);

   /*************************************************************************** 
    Compute composition of the liquid phase (moles)
    ***************************************************************************/

   if (!doRandom) {
     for (i=0; i<nlc; i++) {
       printf("Input wt of %15.15s: ", bulkSystem[i].label);
       scanf("%f", &ftemp); grams[i] = (double) ftemp; getchar();
     }
   }

   printf("\n");
   for (i=0,sum=0.0; i<nc; i++) {
     printf("Wt %-8.8s = %8.4f\n", bulkSystem[i].label, grams[i]);
     grams[i] /= bulkSystem[i].mw;
     sum += grams[i];
   }
   printf("Total moles of oxides = %g\n", sum); mTox = sum;
   printf("\n");
   for (i=0,mTliq=0.0; i<nlc; i++) {
     for (j=0,moles[i]=0.0; j<nc; j++) moles[i] += grams[j]*(bulkSystem[j].oxToLiq)[i];
     mTliq += moles[i];
   }
   printf("Total moles of liquid components = %g\n", mTliq);

   /***************************************************************************
    Transform mole vector into independent compositional variables
    ***************************************************************************/

   /* Convert moles of endmembers to independent compositional variables and
      mole fractions of endmembers. Get derivatives of the independent
      compositional variables with respect to moles of endmembers             */

   conLiq(SECOND, THIRD | FIFTH, t, p, NULL, moles, x, NULL, drdm, NULL, NULL);

   /* Calculate species distribution and report results */
   conLiq(THIRD, FOURTH | EIGHTH, t, p, NULL, NULL, x, xSpecies, NULL, NULL, NULL);
   printf("Distribution of species from conLiq:\n");
   for (i=0; i<nls; i++) printf("x[%20.20s] = %g\n", liquid[i].label, xSpecies[i]);
   printf("\n");
   
   /* Calculate CN state distribution and report results */
   conLiq(THIRD, FOURTH | NINTH, t, p, NULL, NULL, x, xSpecies, NULL, NULL, NULL);
   printf("CN state distribution from conLiq:\n");
   for (i=0; i<nCN; i++) printf("fraction CN[%1.1d] = %g\n", 3+i, xSpecies[i]);
   printf("\n");

   /* Test EOS model for this T and P combination */
   gmixLiq(FIRST, t, p, x, &g, NULL, NULL);
   if (!testLiq(EIGHTH, 0, 0, 0, 0, NULL, NULL, NULL, NULL)) { printf("EOS failure in liquid properties functions. Error: %d\n", liqERRstate); return 0; }

   eos = getEosRefParameters(x);
   printf("EOS parameters at 1400 C and 0.0001 GPa:\n");
   printf("  v      (cc)       = %g\n", eos->v     *10.0);
   printf("  dvdt   (cc/K)     = %g\n", eos->dvdt  *10.0);
   printf("  cRef   (m/sec)    = %g\n", eos->cRef  );
   printf("  dcdt   (m/sec-K)  = %g\n", eos->dcdt  );
   printf("  cp     (J/K)      = %g\n", eos->cp    );
   printf("  d2vdp2 (cc/GPa^2) = %g\n", eos->d2vdp2*10.0*10000.0*10000.0);
   printf("  d3vdp3 (cc/GPa^3) = %g\n", eos->d3vdp3*10.0*10000.0*10000.0*10000.0);
   printf("  d4vdp4 (cc/GPa^4) = %g\n", eos->d4vdp4*10.0*10000.0*10000.0*10000.0*10000.0);
   printf("  mw     (gm)       = %g\n", eos->mw    );
   printf("  alpha  (1/K)      = %g\n", eos->alpha );
   printf("  v0     (cc)       = %g\n", eos->v0    *10.0);
   printf("  v1     (cc/GPa)   = %g\n", eos->v1    *10.0*10000.0);
   printf("  v2     (cc/GPa^2) = %g\n", eos->v2    *10.0*10000.0*10000.0);
   printf("  v3     (cc/GPa^3) = %g\n", eos->v3    *10.0*10000.0*10000.0*10000.0);
   printf("  v4     (cc/GPa^4) = %g\n", eos->v4    *10.0*10000.0*10000.0*10000.0*10000.0);
   printf("  a      (1/GPa)    = %g\n", eos->a     *10000.0);
   printf("  b      (1/GPa^2)  = %g\n", eos->b     *10000.0*10000.0);
   printf("  K      (GPa)      = %g\n", eos->K     /10000.0);
   printf("  Kp                = %g\n", eos->Kp    );
   printf("  Kpp    (1/GPa)    = %g\n", eos->Kpp   *10000.0);
   printf("  Kppp   (1/GPa^2)  = %g\n", eos->Kppp  *10000.0*10000.0);    

   /***************************************************************************
    Evaluate activity routines
    ***************************************************************************/
   actLiq(SECOND, t, p, x, NULL, mu, NULL, NULL);

   printf("\n");
   for (i=0; i<nlc; i++) {
     printf("(mu-mu0)[%s] = %g\n", liquid[i].label, mu[i]);
   }
   printf("\n");

  GraceRegisterErrorFunction (grace_error_function);
  if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }

  GracePrintf("WITH G0\n");
   GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",  0.1,   0.1, 0.9, 0.9);
   GracePrintf("WORLD %lf, %lf, %lf, %lf\n",  0.0, -20.0, 1.0, 0.0);

   GracePrintf("XAXIS TICK MAJOR 0.20\n");
   GracePrintf("XAXIS TICK MINOR 0.05\n");
   GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

   GracePrintf("XAXIS LABEL \"P (GPa)\"\n");
   GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
   GracePrintf("XAXIS LABEL COLOR 2\n");

   GracePrintf("YAXIS TICK MAJOR 2.00\n");
   GracePrintf("YAXIS TICK MINOR 1.00\n");
   GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

   GracePrintf("YAXIS LABEL \"V (cc)\"\n");
   GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
   GracePrintf("YAXIS LABEL COLOR 2\n");
   
   GracePrintf("LEGEND ON\n");
   GracePrintf("FRAME ON\n");
 
   for (i=0; i<8; i++) {
     GracePrintf("g0.s%1.1d LINESTYLE 1\n", i);
     GracePrintf("g0.s%1.1d COLOR %1.1d\n", i, i+1);
     GracePrintf("g0.s%1.1d SYMBOL 0\n",    i);
   }

   vmixLiq(FIRST | SECOND | FOURTH | FIFTH | EIGHTH, t, p, x, &v, dvdx, NULL, &dvdt, &dvdp, NULL, NULL, &d2vdp2, NULL, NULL, NULL);
   intenToExtenGradient(v, dvdx, nr,  dvdm, nlc, mTliq, drdm);

   printf("\n");
   printf("v    = %g\n", v*mTliq);
   printf("dvdt = %g\n", dvdt*mTliq);
   printf("dvdp = %g\n", dvdp*mTliq);
   printf("K    = %g\n", -v/(dvdp*10000.0));
   printf("K'   = %g\n", d2vdp2*10000.0*10000.0*pow(-v/(dvdp*10000.0), (double) 2.0)/v - 1.0);
   printf("\n");
   for (i=0; i<nlc; i++) printf("dvdm[%-10.10s] = %g\n", liquid[i].label, dvdm[i]);
   
   for (i=0; i<npc; i++) if (!strcmp("stishovite-sx", solids[i].label)) { nStishovite = i; break; }
   for (i=0; i<npc; i++) if (!strcmp("majorite ss", solids[i].label)) { 
     nGrossular = i + 1; 
     nPyrope    = i + 2; 
     nAlmandine = i + 3; 
     nMajorite  = i + 4; 
     break; 
   }
   for (i=0; i<npc; i++) if (!strcmp("wustite ss", solids[i].label)) { 
     nMgwustite = i + 1; 
     nFewustite = i + 2; 
     break; 
   }
   for (i=0; i<npc; i++) if (!strcmp("clinopyroxene", solids[i].label)) { 
     nDiopside     = i + 1; 
     nEnstatite    = i + 2; 
     nHedenbergite = i + 3; 
     break; 
   }
   if(nStishovite == -1) printf("ERROR: Cannot find stishovite-sx\n");
   if(nGrossular  == -1) printf("ERROR: Cannot find majorite ss\n");
   if(nMgwustite  == -1) printf("ERROR: Cannot find wustite ss\n");
   if(nDiopside   == -1) printf("ERROR: Cannot find clinopyroxene ss\n");

   gibbs(t, p, (char *) solids[nStishovite].label,   &(solids[nStishovite].ref),   NULL, NULL, &(solids[nStishovite].cur));
   gibbs(t, p, (char *) solids[nGrossular].label,    &(solids[nGrossular].ref),    NULL, NULL, &(solids[nGrossular].cur));
   gibbs(t, p, (char *) solids[nPyrope].label,       &(solids[nPyrope].ref),	   NULL, NULL, &(solids[nPyrope].cur));
   gibbs(t, p, (char *) solids[nAlmandine].label,    &(solids[nAlmandine].ref),    NULL, NULL, &(solids[nAlmandine].cur));
   gibbs(t, p, (char *) solids[nMgwustite].label,    &(solids[nMgwustite].ref),    NULL, NULL, &(solids[nMgwustite].cur));
   gibbs(t, p, (char *) solids[nFewustite].label,    &(solids[nFewustite].ref),    NULL, NULL, &(solids[nFewustite].cur));
   gibbs(t, p, (char *) solids[nDiopside].label,     &(solids[nDiopside].ref),     NULL, NULL, &(solids[nDiopside].cur));
   gibbs(t, p, (char *) solids[nEnstatite].label,    &(solids[nEnstatite].ref),    NULL, NULL, &(solids[nEnstatite].cur));
   gibbs(t, p, (char *) solids[nHedenbergite].label, &(solids[nHedenbergite].ref), NULL, NULL, &(solids[nHedenbergite].cur));
   printf("v-bar SiO2         %g %g\n",                               dvdm[0], (solids[nStishovite  ].cur).v);
   printf("v-bar Ca3Al2Si3O12 %g %g\n", 1.5*dvdm[10]+dvdm[ 2]    +1.5*dvdm[0], (solids[nGrossular   ].cur).v);
   printf("v-bar Mg3Al2Si3O12 %g %g\n", 1.5*dvdm[ 7]+dvdm[ 2]    +1.5*dvdm[0], (solids[nPyrope      ].cur).v);
   printf("v-bar Fe3Al2Si3O12 %g %g\n", 1.5*dvdm[ 5]+dvdm[ 2]    +1.5*dvdm[0], (solids[nAlmandine   ].cur).v);
   printf("v-bar MgO          %g %g\n", 0.5*dvdm[ 7]             -0.5*dvdm[0], (solids[nMgwustite   ].cur).v);
   printf("v-bar FeO          %g %g\n", 0.5*dvdm[ 5]             -0.5*dvdm[0], (solids[nFewustite   ].cur).v);
   printf("v-bar CaMgSi2O6    %g %g\n", 0.5*dvdm[ 7]+0.5*dvdm[10]+    dvdm[0], (solids[nDiopside    ].cur).v);
   printf("v-bar Mg2Si2O6     %g %g\n",     dvdm[ 7]             +    dvdm[0], (solids[nEnstatite   ].cur).v);
   printf("v-bar CaFeSi2O6    %g %g\n", 0.5*dvdm[ 5]+0.5*dvdm[10]+    dvdm[0], (solids[nHedenbergite].cur).v);

   molesTemp = vector(0, nlc-1);
   xTemp     = vector(0, nr-1);
   for (i=0; i<nlc; i++) molesTemp[i] = moles[i];
   molesTemp[10] += 3.0*sqrt(DBL_EPSILON)/2.0;
   molesTemp[ 2] +=     sqrt(DBL_EPSILON);
   molesTemp[ 0] += 3.0*sqrt(DBL_EPSILON)/2.0;
   mTliqTemp = mTliq + 4.0*sqrt(DBL_EPSILON);
   conLiq(SECOND, THIRD, t, p, NULL, molesTemp, xTemp, NULL, NULL, NULL, NULL);
   for (i=1; i<101; i++) {
     double g, gTemp, muEst;
     double y          = 0.3;
     double intVFe2O3  = integralV_GKsp(iOxFe2O3,  t, p*(i-1.0)/100.0);
     double intVFeO    = integralV_GKsp(iOxFeO,    t, p*(i-1.0)/100.0);
     double intVFeO1_3 = integralV_GKsp(iOxFeO1_3, t, p*(i-1.0)/100.0);
     double deltaG1    = -106200.0 - t*(-55.1) + 31.86*(t - 1673.15 - t*log(t/1673.15)) + intVFe2O3/2.0 - intVFeO;
     double deltaG2    = -R*t*log(0.4) + intVFeO1_3 - (1.0-2.0*y)*intVFeO - y*intVFe2O3;
     double logfo2 = -12.312;
     logfo2 = getlog10fo2(t, (p*(i-1.0)/100.0 < 67201.0) ? p*(i-1.0)/100.0 : 67201.0, FO2_COH); /* Assume that there are carbon heaters */
     if (p*(i-1.0)/100.0 > 67201.0) logfo2 += 608.966*(p*(i-1.0)/100.0/10000.0)/t - 608.966*(67201.0/10000.0)/t; /* Andy Campbell's pressure correction for IW */
     gibbs(t, p*(i-1.0)/100.0, (char *) solids[nStishovite].label,   &(solids[nStishovite].ref),   NULL, NULL, &(solids[nStishovite].cur));
     gibbs(t, p*(i-1.0)/100.0, (char *) solids[nGrossular].label,    &(solids[nGrossular].ref),    NULL, NULL, &(solids[nGrossular].cur));
     gibbs(t, p*(i-1.0)/100.0, (char *) solids[nPyrope].label,       &(solids[nPyrope].ref),	   NULL, NULL, &(solids[nPyrope].cur));
     gibbs(t, p*(i-1.0)/100.0, (char *) solids[nAlmandine].label,    &(solids[nAlmandine].ref),    NULL, NULL, &(solids[nAlmandine].cur));
     gibbs(t, p*(i-1.0)/100.0, (char *) solids[nMajorite].label,     &(solids[nMajorite].ref),     NULL, NULL, &(solids[nMajorite].cur));
     gibbs(t, p*(i-1.0)/100.0, (char *) solids[nMgwustite].label,    &(solids[nMgwustite].ref),    NULL, NULL, &(solids[nMgwustite].cur));
     gibbs(t, p*(i-1.0)/100.0, (char *) solids[nFewustite].label,    &(solids[nFewustite].ref),    NULL, NULL, &(solids[nFewustite].cur));
     gibbs(t, p*(i-1.0)/100.0, (char *) solids[nDiopside].label,     &(solids[nDiopside].ref),     NULL, NULL, &(solids[nDiopside].cur));
     gibbs(t, p*(i-1.0)/100.0, (char *) solids[nEnstatite].label,    &(solids[nEnstatite].ref),    NULL, NULL, &(solids[nEnstatite].cur));
     gibbs(t, p*(i-1.0)/100.0, (char *) solids[nHedenbergite].label, &(solids[nHedenbergite].ref), NULL, NULL, &(solids[nHedenbergite].cur));
     actLiq(SECOND, t, p*(i-1.0)/100.0, x, NULL, mu, NULL, NULL);
#ifdef NEVER_DEFINED
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n",  1, (p*(i-1.0)/100.0)/10000.0, (mu[0]-(solids[nStishovite].cur).g)/1000.0); /* liq-sol */
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n",  2, (p*(i-1.0)/100.0)/10000.0, (1.5*mu[10]+    mu[ 2]+1.5*mu[0]-(solids[nGrossular   ].cur).g)/1000.0); /* liq-sol */
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n",  3, (p*(i-1.0)/100.0)/10000.0, (1.5*mu[ 7]+    mu[ 2]+1.5*mu[0]-(solids[nPyrope      ].cur).g)/1000.0); /* liq-sol */
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n",  4, (p*(i-1.0)/100.0)/10000.0, (1.5*mu[ 5]+    mu[ 2]+1.5*mu[0]-(solids[nAlmandine   ].cur).g)/1000.0); /* liq-sol */
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n",  5, (p*(i-1.0)/100.0)/10000.0, (2.0*mu[ 7]           +2.0*mu[0]-(solids[nMajorite    ].cur).g)/1000.0); /* liq-sol */
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n",  6, (p*(i-1.0)/100.0)/10000.0, (0.5*mu[ 7]           -0.5*mu[0]-(solids[nMgwustite   ].cur).g)/1000.0); /* liq-sol */
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n",  7, (p*(i-1.0)/100.0)/10000.0, (0.5*mu[ 5]           -0.5*mu[0]-(solids[nFewustite   ].cur).g)/1000.0); /* liq-sol */
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n",  8, (p*(i-1.0)/100.0)/10000.0, (0.5*mu[ 7]+0.5*mu[10]+    mu[0]-(solids[nDiopside    ].cur).g)/1000.0); /* liq-sol */
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n",  9, (p*(i-1.0)/100.0)/10000.0, (    mu[ 7]           +    mu[0]-(solids[nEnstatite   ].cur).g)/1000.0); /* liq-sol */
     GracePrintf("g0.s%2.2d POINT %lf, %lf\n", 10, (p*(i-1.0)/100.0)/10000.0, (0.5*mu[ 5]+0.5*mu[10]+    mu[0]-(solids[nHedenbergite].cur).g)/1000.0); /* liq-sol */
#endif
     gmixLiq(FIRST, t, p*(i-1.0)/100.0,     x,     &g, NULL, NULL);
     gmixLiq(FIRST, t, p*(i-1.0)/100.0, xTemp, &gTemp, NULL, NULL);
     muEst = (mTliqTemp*gTemp - mTliq*g)/sqrt(DBL_EPSILON);
#ifdef NEVER_DEFINED
     GracePrintf("g0.s%2.2d POINT %lf, %lf\n", 11, (p*(i-1.0)/100.0)/10000.0, (muEst-(solids[nGrossular].cur).g)/1000.0); /* liq-sol */
#endif
     GracePrintf("g0.s%2.2d POINT %lf, %lf\n", 12, (p*(i-1.0)/100.0)/10000.0, deltaG1/1000.0);
     GracePrintf("g0.s%2.2d POINT %lf, %lf\n", 13, (p*(i-1.0)/100.0)/10000.0, deltaG2/1000.0);
     conLiq(FIRST | SEVENTH, FIRST, t, p*(i-1.0)/100.0, grams, NULL, NULL, NULL, NULL,NULL, &logfo2);
     printf("T = %7.0f (K)  P = %10.4f (GPa) log fO2 = %10.2f  Fe2O3/FeO = %13.6g/%13.6g\n", t, p*(i-1.0)/100.0/10000.0, logfo2, grams[3], grams[5]);
     GracePrintf("g0.s%2.2d POINT %lf, %lf\n", 14, (p*(i-1.0)/100.0)/10000.0, 10.0*log(grams[3]/grams[5])); 
     GracePrintf("REDRAW\n");
   }
 
   /************************************************************************** 
    Destroy space allocated for vectors and matrices		     
    **************************************************************************/

   free_vector(    moles, 0, nlc-1);
   free_vector(        x, 0, nr-1);
   free_vector(       mu, 0, nlc-1);
   free_vector( xSpecies, 0, nls-1);
   free_vector(     dvdx, 0, nr-1);
   free_vector(     dvdm, 0, nlc-1);
   free_matrix(     drdm, 0, nr-1, 0, nlc-1);
   free_vector(molesTemp, 0, nlc-1);
   free_vector(    xTemp, 0, nr-1);
    
   return 0;
}

/* End file: TEST_EOS.C */
