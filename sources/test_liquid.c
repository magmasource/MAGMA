const char *test_liquid_ver(void) { return "$Id: test_liquid.c,v 1.11 2009/05/14 04:24:00 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: test_liquid.c,v $
MELTS Source Code: RCS Revision 1.7  2008/01/06 22:35:59  ghiorso
MELTS Source Code: RCS Updated param and liq data structures to modify EOS parameters for FeO1.3
MELTS Source Code: RCS and to compute f O2 and ferric/ferrous from KC '89 + EOS integral
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2007/10/06 16:47:56  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2007/10/04 17:39:21  ghiorso
MELTS Source Code: RCS Relaxed convergence criteria in liquid ordering routine.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2007/06/08 17:25:43  ghiorso
MELTS Source Code: RCS Added code to allow regression of Ghiorso EOS parameters
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2006/10/20 00:59:23  ghiorso
MELTS Source Code: RCS (1) Made initial modifications for thread safe code.
MELTS Source Code: RCS (2) Added support for XML I/O in batch mode
MELTS Source Code: RCS (3) Added support for Melts-batch listener for eventual integration into VIGMCS
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:19  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2005/01/24 03:38:05  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2005/01/21 18:18:22  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added data structures and code to implement coordination number transformations
MELTS Source Code: RCS in the liquid phase EOS model.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2004/09/24 18:26:35  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2003/09/27 15:35:22  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2002/04/15 04:45:59  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2002/02/07 01:53:59  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 1.1  1997/07/18  16:02:06  ghiorso
 * This routine is modified from test_liquid to evaluate
 * the new liquid-config routine.
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Test routine to evaluate the functions defined for the computation
**      of activity composition relations in the liquid 
**      (file: TEST_LIQUID.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  July 18, 1997 Original Version
**--
*/

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include "interface.h"
Widget main_window, silmin_adb, topLevel;
MeltsEnviron meltsEnviron;

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

SilminState *silminState;
int calculationMode = MODE_DEFAULT;

#ifndef RAND_MAX
#define RAND_MAX INT_MAX         /* SparcStations don't define this macro */
#endif

#define TEST(x) \
   flag = ( ABS(temp - (x)) <= sqrt(sqrt(TAU))*ABS(x) ) \
   ? "OK " : "BAD"

extern const char *liquid_ver(void);

int main()
{
   int i, j, k, doRandom=TRUE;
   int nr = nlc - 1;
   char *flag, **names, **formulas, *dispForm;
   float ftemp;
   double t = 1200.0 + 273.15;
   double p = 1000.0;
   double logfo2 = -12.312;
   double *moles, *x, *a, *mu, *dmudt, **dadx, g, *dgdx, **d2gdx2, h, s, *dsdx,
      **d2sdx2, cp, dcpdt, v, *dvdx, **d2vdx2, dvdt, dvdp, d2vdt2,
      d2vdtdp, d2vdp2, deltaT, deltaP, *deltaX, *deltaM, temp, *xtemp,
      *mtemp, mtotal, *vtemp, **drdm, ***d2rdm2, **dtemp, muO2, *dmuO2dm,
      dmuO2dt, dmuO2dp, **d2muO2dm2, *d2muO2dmt, *d2muO2dmp, d2muO2dt2,
      d2muO2dtp, d2muO2dp2, viscosity, *dcpdx, *d2vdxdt, *d2vdxdp, *dgdw, 
      **dmudw, **d2mudtdw, *dsdw, *xSpecies, *dhdw;

  printf("\n");
  printf("%s\n", test_liquid_ver());
  printf("%s\n", liquid_ver());
  printf("\n");

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
   printf("Calling function: InitComputeDataStruct().         \n");
   printf("***************************************************\n\n");
   InitComputeDataStruct();

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Test liquid mixing properties (y or n)? ");
   if (tolower(getchar()) == 'y') setModeToMixingLiq(TRUE); else setModeToMixingLiq(FALSE);
   getchar();

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Input test compositions (y or n)? ");
   if (tolower(getchar()) == 'y') doRandom = FALSE;
   getchar();

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Use default model parameters (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 

     printf("***************************************************\n");
     printf("Using existing model-paramters.                    \n");
     printf("***************************************************\n\n");
     for (i=0, k=0; i<nls; i++) {
       for (j=i+1; j<nls; j++, k++) {
        printf("%d %13.6g %13.6g %13.6g\n", k, modelParameters[k].enthalpy,
           modelParameters[k].entropy, modelParameters[k].volume);
       }
     }
     printf("Endmember standard state correction terms:\n");
     for (i=0; i<nls; i++, k++) {
       printf("%d %13.6g %13.6g %13.6g\n", k, modelParameters[k].enthalpy,
         modelParameters[k].entropy, modelParameters[k].volume);
     }
   } else {
     getchar();

     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Use default W parameters (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       printf("***************************************************\n");
       printf("Using existing W-paramters.                        \n");
       printf("***************************************************\n\n");
       for (i=0, k=0; i<nls; i++) {
         for (j=i+1; j<nls; j++, k++) {
           printf("%d %13.6g %13.6g %13.6g\n", k, modelParameters[k].enthalpy,
             modelParameters[k].entropy, modelParameters[k].volume);
         }
       }
     } else {
       getchar(); 
       printf("***************************************************\n");
       printf("Creating non-zero W-paramters.                     \n");
       printf("***************************************************\n\n");
       for (i=0, k=0; i<nls; i++) {
         for (j=i+1; j<nls; j++, k++) {
           modelParameters[k].enthalpy = 10000.0*((double) rand())/((double) RAND_MAX);
           modelParameters[k].entropy  =    10.0*((double) rand())/((double) RAND_MAX);
           modelParameters[k].volume   =     0.0; /* ((double) rand())/((double) RAND_MAX)/10.0; */
           printf("%d %13.6g %13.6g %13.6g\n", k, modelParameters[k].enthalpy, modelParameters[k].entropy, modelParameters[k].volume);
         }
       }
     }
     
     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Use default standard state correction terms (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       printf("***************************************************\n");
       printf("Using existing standard state correction terms.    \n");
       printf("***************************************************\n\n");
       for (i=0; i<nls; i++, k++) {
         printf("%d %13.6g %13.6g %13.6g\n", k, modelParameters[k].enthalpy,
           modelParameters[k].entropy, modelParameters[k].volume);
       }
     } else {
       getchar(); 
       printf("***************************************************\n");
       printf("Creating non-zero standard state correction terms. \n");
       printf("***************************************************\n\n");
       for (i=0; i<nls; i++, k++) {
         modelParameters[k].enthalpy = 10000.0*((double) rand())/((double) RAND_MAX);
         modelParameters[k].entropy  =    10.0*((double) rand())/((double) RAND_MAX);
         modelParameters[k].volume   =     0.0; /* ((double) rand())/((double) RAND_MAX)/100.0; */
         printf("%d %13.6g %13.6g %13.6g\n", k, modelParameters[k].enthalpy, modelParameters[k].entropy, modelParameters[k].volume);
       }
     }
   }
   
   for (i=0; i<(nls*(nls-1)/2+nls); i++) { modelParameters[i].activeH = TRUE; modelParameters[i].activeS = TRUE; modelParameters[i].activeV = TRUE; }
   
   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Zero endmember standard state properties (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar();
     for (i=0; i<nls; i++) {
       (liquid[i].ref).h                = 0.0; 
       (liquid[i].ref).s                = 0.0;
       (liquid[i].ref).v                = 0.0;
       (liquid[i].ref).cp_type          = CP_BERMAN;
       (liquid[i].ref).cp.Berman.k0     = 0.0;
       (liquid[i].ref).cp.Berman.k1     = 0.0;
       (liquid[i].ref).cp.Berman.k2     = 0.0;
       (liquid[i].ref).cp.Berman.k3     = 0.0;
       (liquid[i].ref).cp.Berman.Tt     = 0.0;
       (liquid[i].ref).cp.Berman.deltah = 0.0;
       (liquid[i].ref).cp.Berman.l1     = 0.0;
       (liquid[i].ref).cp.Berman.l2     = 0.0;
       (liquid[i].ref).eos_type         = EOS_BERMAN;
       (liquid[i].ref).eos.Berman.v1    = 0.0;
       (liquid[i].ref).eos.Berman.v2    = 0.0;
       (liquid[i].ref).eos.Berman.v3    = 0.0;
       (liquid[i].ref).eos.Berman.v4    = 0.0;

       (liquid[i].liq).v                =    0.0;
       (liquid[i].liq).eos.Kress.dvdt   =    0.0;
       (liquid[i].liq).eos.Kress.dvdp   =    0.0;
       (liquid[i].liq).eos.Kress.d2vdtp =    0.0;
       (liquid[i].liq).eos.Kress.d2vdp2 =    0.0;
       (liquid[i].liq).tfus             = 1000.0;
       (liquid[i].liq).sfus             =    0.0;
       (liquid[i].liq).cp               =    0.0;
       (liquid[i].liq).tglass           =    0.0;
       
       /*  Why was this here?
       if ((liquid[i].label)[0] == 'H' && (liquid[i].label)[1] == '2' && (liquid[i].label)[2] == 'O' )
         { (liquid[i].label)[0] = 'h'; (liquid[i].label)[2] = 'o'; }
       */
     }
   } else getchar();
   
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

   /**************************************************************************
    Compute constants for numerical differentiation                        
    **************************************************************************/
   
   deltaT = sqrt(TAU)*(1.0+ABS(t));
   deltaP = sqrt(TAU)*(1.0+ABS(p));

   /***************************************************************************
    Allocate space for required vectors and matrices                 
    ***************************************************************************/
         
   moles    = vector(0, nlc-1);
   mtemp    = vector(0, nlc-1);
   x        = vector(0, nr-1);
   xtemp    = vector(0, nr-1);
   vtemp    = vector(0, nlc-1);
   deltaM   = vector(0, nlc-1);
   deltaX   = vector(0, nr-1);
   a        = vector(0, nlc-1);
   mu       = vector(0, nlc-1);
   dmudt    = vector(0, nlc-1);
   dgdx     = vector(0, nr-1);
   dsdx     = vector(0, nr-1);
   dvdx     = vector(0, nr-1);
   xSpecies = vector(0, nls-1);

   dcpdx   = vector(0, nr-1);
   d2vdxdt = vector(0, nr-1);
   d2vdxdp = vector(0, nr-1);

   dmuO2dm   = vector(0, nlc-1);
   d2muO2dmt = vector(0, nlc-1);
   d2muO2dmp = vector(0, nlc-1);
   dgdw      = vector(0, 3*(nls*(nls-1)/2+nls)-1);
   dsdw      = vector(0, 3*(nls*(nls-1)/2+nls)-1);
   dhdw      = vector(0, 3*(nls*(nls-1)/2+nls)-1);

   drdm     = matrix(0, nr-1, 0, nlc-1);
   dtemp    = matrix(0, nr-1, 0, nlc-1);
   dadx     = matrix(0, nlc-1, 0, nr-1);
   d2gdx2   = matrix(0, nr-1, 0, nr-1);
   d2sdx2   = matrix(0, nr-1, 0, nr-1);
   d2vdx2   = matrix(0, nr-1, 0, nr-1);
   dmudw    = matrix(0, nlc-1, 0, 3*(nls*(nls-1)/2+nls)-1);
   d2mudtdw = matrix(0, nlc-1, 0, 3*(nls*(nls-1)/2+nls)-1);

   d2muO2dm2 = matrix(0, nlc-1, 0, nlc-1);

   d2rdm2 = (double ***) malloc((unsigned) nr*sizeof(double **));
   for (i=0; i<nr; i++) d2rdm2[i] = matrix(0, nlc-1, 0, nlc-1);

   names    = (char **) malloc((unsigned) nlc*sizeof(char *));
   formulas = (char **) malloc((unsigned) nlc*sizeof(char *));
   for (i=0; i<nlc; i++) {
     names[i]    = (char *) malloc((unsigned)
                     (strlen(bulkSystem[i].label)+1)*sizeof(char));
     formulas[i] = (char *) malloc((unsigned)
                     (strlen(liquid[i].label)+1)*sizeof(char));
   }
         
   for (i=0; i<nlc; i++) {
     names[i]    = strcpy(names[i],    bulkSystem[i].label);
     formulas[i] = strcpy(formulas[i], liquid[i].label);
   }
   if (!testLiq(FIRST | SECOND | THIRD | FOURTH | NINTH, t, p,
       nlc, nr, names, formulas, (double *) NULL, (double *) NULL)) exit(0);

   /*************************************************************************** 
    Compute composition of the liquid phase (moles)
    ***************************************************************************/

   if (doRandom) {
     /*                 SiO2 TiO2 Al2O3 Fe2O3 Cr2O3   FeO  MnO   MgO   NiO   CoO   CaO Na2O  K2O P2O5  H2O   CO2   SO3 Cl2O-1 F2O-1 */
/*    double grams[] = { 45.0, 2.0, 10.0,  0.2, 0.01, 10.0, 0.5, 20.0, 0.05, 0.05, 10.0, 2.0, 0.5, 0.5, 0.1, 0.05, 0.05,  0.05, 0.05 }; */
/*   double grams[] = { 60.46, 0.45, 16.29,  0.921154, 0.04, 2.42796, 0.05, 1.94, 0.01, 0.01, 4.42, 4.02, 1.8, 0.01, 6.69, 0.01, 0.01,  0.01, 0.01 }; */
     double grams[] = { 49.0, 0.5, 16.0,  1.0, 0.0, 10.0, 0.0, 10.0, 0.0, 0.0, 10.0, 3.0, 0.5, 0.0, 1.0, 0.0, 0.0,  0.0, 0.0 };
     for (i=0; i<nc; i++) grams[i] /= bulkSystem[i].mw;
     for (i=0; i<nlc; i++) for (j=0,moles[i]=0.0; j<nc; j++) moles[i] += grams[j]*(bulkSystem[j].oxToLiq)[i];
   } else {
     for (i=0; i<nlc; i++) {
       printf("Input moles of %15.15s (%15.15s): ", names[i], formulas[i]);
       scanf("%f", &ftemp); moles[i] = (double) ftemp; getchar();
     }
   }
   for (i=0; i<nlc; i++) deltaM[i] = sqrt(TAU)*(1.0+ABS(moles[i]));

   /***************************************************************************
    Transform mole vector into independent compositional variables
    ***************************************************************************/

   /* Convert moles of endmembers to independent compositional variables and
      mole fractions of endmembers. Get derivatives of the independent
      compositional variables with respect to moles of endmembers             */

   conLiq(SECOND, THIRD | FOURTH | FIFTH | SIXTH, t, p, 
     (double *) NULL, moles, x, mtemp, drdm, d2rdm2, (double *) NULL);
   for (i=0; i<nr; i++) deltaX[i] = sqrt(TAU)*(1.0+ABS(x[i]));

   /* Output moles and independent compositional variables */
   for (i=0; i<nlc; i++) {
     printf("    moles[%-15.15s] = %13.6g", liquid[i].label, moles[i]);
     if (i < nr) printf("    x[%3d] = %13.6g\n", i, x[i]);
     else        printf("\n");
   }
   printf("\n");

   /* Output formula of the solid phase */
   dispLiq(FIRST, t, p, x, &dispForm);
   printf("    formula %s\n", dispForm); free(dispForm);
   printf("\n");

   /* Calculate total moles */
   for (i=0, mtotal=0.0; i<nlc; i++) mtotal += moles[i];

   /* Check calculated mole fractions for internal consistency */
   for (i=0; i<nlc; i++) {
     temp = mtemp[i];
     TEST(moles[i]/mtotal);
     printf("%s     X[%s] = %g (%g, %s)\n", flag, liquid[i].label, 
       moles[i]/mtotal, temp, "from conLiq SECOND->FOURTH");
   }
   printf("\n");

   if (calculationMode == MODE_xMELTS) {
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
   }

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Do drdm now (y or n)? ");
   if (tolower(getchar()) == 'y') { 
     getchar(); 
   
     /* print and test drdm[] */
     for (i=0; i<nlc; i++) {
       for (j=0; j<nlc; j++) mtemp[j] = moles[j];
       mtemp[i] += deltaM[i];
       conLiq(SECOND, THIRD, t, p, (double *) NULL, mtemp, xtemp,
  	 (double *) NULL, (double **) NULL, (double ***) NULL, (double *) NULL);
       for (j=0; j<nr; j++) {
  	 temp = (xtemp[j]-x[j])/deltaM[i];
  	 TEST(drdm[j][i]);
  	 printf("%s drdm[%d][%d] = %g (%g, %s)\n", flag, j, i, drdm[j][i],
  	   temp, "from r");
       }
     }
     printf("\n");
   } else getchar();

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Do d2rdm2 now (y or n)? ");
   if (tolower(getchar()) == 'y') { 
     getchar(); 

    /* print and test d2rdm2[][][] */
     for (i=0; i<nlc; i++) {
       for (j=0; j<nlc; j++) {
  	 for (k=0; k<nlc; k++) mtemp[k] = moles[k];
  	 mtemp[j] += deltaM[j];
  	 conLiq(SECOND, FIFTH, t, p, (double *) NULL, mtemp, (double *) NULL,
  	   (double *) NULL, dtemp, (double ***) NULL, (double *) NULL);
  	 for (k=0; k<nr; k++) {
  	   temp = (dtemp[k][i]-drdm[k][i])/deltaM[j];
  	   TEST(d2rdm2[k][i][j]);
  	   printf("%s d2rdm2[%d][%d][%d] = %g (%g, %s)\n", flag, k, i, j,
  	     d2rdm2[k][i][j], temp, "from drdm[][]");
  	 }
       }
     }
     printf("\n");
   } else getchar();
   
   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Do r to X test now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 
     /* Convert independent compositional variables into mole fractions */
     conLiq(THIRD, FOURTH, t, p, (double *) NULL, (double *) NULL, x, mtemp,
       (double **) NULL, (double ***) NULL, (double *) NULL);

     /* Check calculated mole fractions for internal consistency */
     for (i=0; i<nlc; i++) {
       temp = mtemp[i];
       TEST(moles[i]/mtotal);
       printf("%s     X[%s] = %g (%g, %s)\n", flag, liquid[i].label,
  	 moles[i]/mtotal, temp, "from conLiq THIRD->FOURTH");
     }
     printf("\n");
   } else getchar();

   /***************************************************************************
    Evaluate Gibbs energy of mixing and its derivatives
    ***************************************************************************/
   gmixLiq(FIRST | SECOND | THIRD, t, p, x, &g, dgdx, d2gdx2);

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate G now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar();
     printf("    g = %g\n", g);
   } else getchar();

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate derivatives of dG now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 
     /* print and test dgdx[] */
     for (i=0; i<nr; i++) {
       for (j=0; j<nr; j++) xtemp[j] = x[j];
       xtemp[i] += deltaX[i];
       gmixLiq(FIRST, t, p, xtemp, &temp,  NULL, NULL);
       temp = (temp-g)/deltaX[i];
       TEST(dgdx[i]);
       printf("%s dgdx[%d] = %g (%g, %s)\n", flag, i, dgdx[i], temp, "from g");
     }
   } else getchar();
   
   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate derivatives of d2G now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 
     /* print and test d2gdx2[][] */
     for (i=0; i<nr; i++) {
       for (j=0; j<nr; j++) {
  	 for (k=0; k<nr; k++) xtemp[k] = x[k];
  	 xtemp[j] += deltaX[j];
  	 gmixLiq(SECOND, t, p, xtemp, (double *) 0, vtemp, (double **) 0);
  	 temp = (vtemp[i]-dgdx[i])/deltaX[j];
  	 TEST(d2gdx2[i][j]);
  	 printf("%s d2gdx2[%d][%d] = %g (%g, %s)\n", flag, i, j, d2gdx2[i][j],
  	   temp, "from dgdx[]");
       }
     }
   } else getchar();
   
   if (calculationMode == MODE_xMELTS) {
   
     printf("\n");
     /* The next is a non-public call to actLiq */
     actLiq(FIFTH, t, p, x, NULL, dgdw, NULL, NULL); 

     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Evaluate g-parameter H derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       for (i=0; i<(nls*(nls-1)/2+nls); i++) {
     	 double param = modelParameters[i].enthalpy;
     	 double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[i].enthalpy));
     	 double left, right;
     	 modelParameters[i].enthalpy = param + delta;
     	 gmixLiq(FIRST, t, p, x, &left, NULL, NULL);
     	 modelParameters[i].enthalpy = param - delta;
     	 gmixLiq(FIRST, t, p, x, &right,  NULL, NULL);
     	 modelParameters[i].enthalpy = param;
     	 temp = ((left-g)/delta + (g-right)/delta)/2.0;
     	 TEST(dgdw[i]);
     	 printf("%s dgdw[%s] = %g (%g, %s)\n", flag, modelParameters[i].label, dgdw[i], temp, "from g - central difference");
       }
     } else getchar();
     	
     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Evaluate g-parameter S derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       for (i=0; i<(nls*(nls-1)/2+nls); i++) {
     	 double param = modelParameters[i].entropy;
     	 double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[i].entropy));
     	 double left, right;
     	 modelParameters[i].entropy = param + delta;
     	 gmixLiq(FIRST, t, p, x, &left, NULL, NULL);
     	 modelParameters[i].entropy = param - delta;
     	 gmixLiq(FIRST, t, p, x, &right,  NULL, NULL);
     	 modelParameters[i].entropy = param;
     	 temp = ((left-g)/delta + (g-right)/delta)/2.0;
     	 TEST(dgdw[i+nls+nls*(nls-1)/2]);
     	 printf("%s dgdw[%s] = %g (%g, %s)\n", flag, modelParameters[i].label, dgdw[i+nls+nls*(nls-1)/2], temp, "from g - central difference");
       }
     } else getchar();
 
     printf("Evaluate g-parameter V derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar();
       for (i=0; i<(nls*(nls-1)/2+nls); i++) {
     	 double param = modelParameters[i].volume;
     	 double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[i].volume));
     	 double left, right;
     	 modelParameters[i].volume = param + delta;
     	 gmixLiq(FIRST, t, p, x, &left, NULL, NULL);
     	 modelParameters[i].volume = param - delta;
     	 gmixLiq(FIRST, t, p, x, &right,  NULL, NULL);
     	 modelParameters[i].volume = param;
     	 temp = ((left-g)/delta + (g-right)/delta)/2.0;
     	 TEST(dgdw[i+2*nls+2*nls*(nls-1)/2]);
     	 printf("%s dgdw[%s] = %g (%g, %s)\n", flag, modelParameters[i].label, dgdw[i+2*nls+2*nls*(nls-1)/2], temp, "from g - central difference");
       }
     }  else getchar();
 
   }
   printf("\n");

   /***************************************************************************
    Evaluate activity routines
    ***************************************************************************/
   actLiq(FIRST | SECOND | THIRD, t, p, x, a, mu, dadx, NULL);
   if (calculationMode == MODE_xMELTS) {
     actLiq(FOURTH,         t, p, x, NULL,  NULL, NULL, dmudw);
     actLiq(EIGHTH | NINTH, t, p, x, NULL, dmudt, NULL, d2mudtdw);
   }

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate avtivities and mus now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 
     for (i=0; i<nlc; i++) {
       double mtotalp;
       for (j=0; j<nlc; j++) mtemp[j] = moles[j];
       mtemp[i] += deltaM[i];
       for (j=0, mtotalp=0.0; j<nlc; j++) mtotalp += mtemp[j];
       conLiq(SECOND, THIRD, t, p, (double *) NULL, mtemp, xtemp,
  	 (double *) NULL, (double **) NULL, (double ***) NULL, (double *) NULL);
       gmixLiq(FIRST, t, p, xtemp, &temp, (double *) 0, (double **) 0);
       /* temp = mtotal*((temp-g)/deltaM[i]) + (g+temp)/2.0; */
       temp = (mtotalp*temp - mtotal*g)/deltaM[i];
       temp = exp(temp/(8.3143*t));
       TEST(a[i]);
       printf("%s a[%s] = %g (%g, %s)\n", flag, liquid[i].label, a[i],
  	 temp, "from g");
     }

     /* print and test chemical potentials */
     for (i=0; i<nlc; i++) {
       temp = 8.3143*t*log(a[i]);
       TEST(mu[i]);
       printf("%s (mu-mu0)[%s] = %g (%g, %s)\n", flag, liquid[i].label,
  	 mu[i], temp, "from a[]");
     }
   } else getchar();

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate avtivity derivatives now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 
     /* print and test dadx[][] */
     for (i=0; i<nlc; i++) {
       for (j=0; j<nr; j++) {
  	 for (k=0; k<nr; k++) xtemp[k] = x[k];
  	 xtemp[j] += deltaX[j];
  	 actLiq(FIRST, t, p, xtemp, vtemp, NULL, NULL, NULL);
  	 temp = (vtemp[i]-a[i])/deltaX[j];
  	 TEST(dadx[i][j]);
  	 printf("%s dadx[%s][%d] = %g (%g, %s)\n", flag, liquid[i].label, j,
  	   dadx[i][j], temp, "from a[]");
       }
     }
   } else getchar();

   if (calculationMode == MODE_xMELTS) {
     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Evaluate chemical potential-parameter H derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       for (i=0; i<nlc; i++) {
    	 for (j=0; j<(nls*(nls-1)/2+nls); j++) {
    	   double param = modelParameters[j].enthalpy;
    	   double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[j].enthalpy));
    	   double left, right;
    	   modelParameters[j].enthalpy = param + delta;
    	   actLiq(SECOND, t, p, x, NULL, vtemp, NULL, NULL);
    	   left = vtemp[i];
    	   modelParameters[j].enthalpy = param - delta;
    	   actLiq(SECOND, t, p, x, NULL, vtemp, NULL, NULL);
    	   right = vtemp[i];
    	   modelParameters[j].enthalpy = param;
    	   temp = ((left-mu[i])/delta + (mu[i]-right)/delta)/2.0;
    	   TEST(dmudw[i][j]);
    	   printf("%s dmudw[%s][%s] = %g (%g, %s)\n", flag, liquid[i].label, modelParameters[j].label,
    	     dmudw[i][j], temp, "from m[] - central difference");
    	 }
       }
     } else getchar();
     
     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Evaluate chemical potential-parameter S derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       for (i=0; i<nlc; i++) {
    	 for (j=0; j<(nls*(nls-1)/2+nls); j++) {
    	   double param = modelParameters[j].entropy;
    	   double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[j].entropy));
    	   double left, right;
    	   modelParameters[j].entropy = param + delta;
    	   actLiq(SECOND, t, p, x, NULL, vtemp, NULL, NULL);
    	   left = vtemp[i];
    	   modelParameters[j].entropy = param - delta;
    	   actLiq(SECOND, t, p, x, NULL, vtemp, NULL, NULL);
    	   right = vtemp[i];
    	   modelParameters[j].entropy = param;
    	   temp = ((left-mu[i])/delta + (mu[i]-right)/delta)/2.0;
    	   TEST(dmudw[i][j+nls*(nls-1)/2+nls]);
    	   printf("%s dmudw[%s][%s] = %g (%g, %s)\n", flag, liquid[i].label, modelParameters[j].label,
    	     dmudw[i][j+nls*(nls-1)/2+nls], temp, "from m[] - central difference");
    	 }
       }
     } else getchar();

     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Evaluate chemical potential-parameter V derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       /* print and test dmudw[][] */
       for (i=0; i<nlc; i++) {
    	 for (j=0; j<(nls*(nls-1)/2+nls); j++) {
    	   double param = modelParameters[j].volume;
    	   double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[j].volume));
    	   double left, right;
    	   modelParameters[j].volume = param + delta;
    	   actLiq(SECOND, t, p, x, NULL, vtemp, NULL, NULL);
    	   left = vtemp[i];
    	   modelParameters[j].volume = param - delta;
    	   actLiq(SECOND, t, p, x, NULL, vtemp, NULL, NULL);
    	   right = vtemp[i];
    	   modelParameters[j].volume = param;
    	   temp = ((left-mu[i])/delta + (mu[i]-right)/delta)/2.0;
    	   TEST(dmudw[i][j+2*nls*(nls-1)/2+2*nls]);
    	   printf("%s dmudw[%s][%s] = %g (%g, %s)\n", flag, liquid[i].label, modelParameters[j].label,
    	     dmudw[i][j+2*nls*(nls-1)/2+2*nls], temp, "from m[] - central difference");
    	 }
       }
     } else getchar();

     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Evaluate derivative of chemical potential with respect to T now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       /* print and test dmudt */
       actLiq(SECOND, t+deltaT, p, x, NULL, vtemp, NULL, NULL);
       for (i=0; i<nlc; i++) {
    	 temp = (vtemp[i]-mu[i])/deltaT;
    	 TEST(dmudt[i]);
    	 printf("%s dmudt[%s] = %g (%g, %s)\n", flag, liquid[i].label, dmudt[i], temp, "from mu");
       }
     } else getchar();

     /***************************************************************************
      Question to proceed +2*nls*(nls-1)/2+2*nls]
      ***************************************************************************/
     printf("Evaluate derivative of chemical potential with respect to T and W now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       /* print and test d2mudtdw[][] */
       for (i=0; i<nlc; i++) {
    	 for (j=0; j<(nls*(nls-1)/2+nls); j++) {
    	   double param = modelParameters[j].enthalpy;
    	   double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[j].enthalpy));
    	   double left, right;
    	   modelParameters[j].enthalpy = param + delta;
    	   actLiq(EIGHTH, t, p, x, NULL, vtemp, NULL, NULL);
    	   left = vtemp[i];
    	   modelParameters[j].enthalpy = param - delta;
    	   actLiq(EIGHTH, t, p, x, NULL, vtemp, NULL, NULL);
    	   right = vtemp[i];
    	   modelParameters[j].enthalpy = param;
    	   temp = ((left-dmudt[i])/delta + (dmudt[i]-right)/delta)/2.0;
    	   TEST(d2mudtdw[i][j]);
    	   printf("%s dmudw[%s][%s] = %g (%g, %s)\n", flag, liquid[i].label, modelParameters[j].label,
    	     d2mudtdw[i][j], temp, "from dmudt[] - central difference");
    	 }
       }
     } else getchar();
   }
   
   printf("\n");
   
   /***************************************************************************
    Evaluate entropy of mixing and its derivatives
    ***************************************************************************/
   smixLiq(FIRST | SECOND | THIRD, t, p, x, &s, dsdx, d2sdx2, NULL);
   if (calculationMode == MODE_xMELTS) smixLiq(FOURTH, t, p, x, NULL, NULL, NULL, dsdw);

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate S now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar();   
     /* print and test s */
     gmixLiq(FIRST, t+deltaT, p, x, &temp, (double *) NULL, (double **) NULL);
     temp = -(temp-g)/deltaT;
     TEST(s);
     printf("%s s = %g (%g, %s)\n", flag, s, temp, "from g");
   } else getchar();

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate first derivatives of S now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 
     /* print and test dsdx[] */
     for (i=0; i<nr; i++) {
       for (j=0; j<nr; j++) xtemp[j] = x[j];
       xtemp[i] += deltaX[i];
       smixLiq(FIRST, t, p, xtemp, &temp, NULL, NULL, NULL);
       temp = (temp-s)/deltaX[i];
       TEST(dsdx[i]);
       printf("%s dsdx[%d] = %g (%g, %s)\n",flag, i, dsdx[i], temp, "from s");
     }
   } else getchar();
 
   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate second derivatives of S now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 
     /* print and test d2ddx2[][] */
     for (i=0; i<nr; i++) {
       for (j=0; j<nr; j++) {
  	 for (k=0; k<nr; k++) xtemp[k] = x[k];
  	 xtemp[j] += deltaX[j];
  	 smixLiq(SECOND, t, p, xtemp, NULL, vtemp, NULL, NULL);
  	 temp = (vtemp[i]-dsdx[i])/deltaX[j];
  	 TEST(d2sdx2[i][j]);
  	 printf("%s d2sdx2[%d][%d] = %g (%g, %s)\n", flag, i, j, d2sdx2[i][j],
  	   temp, "from dsdx[]");
       }
     }
   } else getchar();
   
   if (calculationMode == MODE_xMELTS) {
     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Evaluate s-parameter H derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    	 double param = modelParameters[i].enthalpy;
    	 double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[i].enthalpy));
    	 double left, right;
    	 modelParameters[i].enthalpy = param + delta;
    	 smixLiq(FIRST, t, p, x, &left, NULL, NULL, NULL);
    	 modelParameters[i].enthalpy = param - delta;
    	 smixLiq(FIRST, t, p, x, &right,  NULL, NULL, NULL);
    	 modelParameters[i].enthalpy = param;
    	 temp = ((left-s)/delta + (s-right)/delta)/2.0;
    	 TEST(dsdw[i]);
    	 printf("%s dsdw[%s] = %g (%g, %s)\n", flag, modelParameters[i].label, dsdw[i], temp, "from s - central difference");
       }
     } else getchar();
    	
     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Evaluate s-parameter S derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    	 double param = modelParameters[i].entropy;
    	 double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[i].entropy));
    	 double left, right;
    	 modelParameters[i].entropy = param + delta;
    	 smixLiq(FIRST, t, p, x, &left, NULL, NULL, NULL);
    	 modelParameters[i].entropy = param - delta;
    	 smixLiq(FIRST, t, p, x, &right,  NULL, NULL, NULL);
    	 modelParameters[i].entropy = param;
    	 temp = ((left-s)/delta + (s-right)/delta)/2.0;
    	 TEST(dsdw[i+nls+nls*(nls-1)/2]);
    	 printf("%s dsdw[%s] = %g (%g, %s)\n", flag, modelParameters[i].label, dsdw[i+nls+nls*(nls-1)/2], temp, "from s - central difference");
       }
     } else getchar();
 
     printf("Evaluate s-parameter V derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar();
       for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    	 double param = modelParameters[i].volume;
    	 double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[i].volume));
    	 double left, right;
    	 modelParameters[i].volume = param + delta;
    	 smixLiq(FIRST, t, p, x, &left, NULL, NULL, NULL);
    	 modelParameters[i].volume = param - delta;
    	 smixLiq(FIRST, t, p, x, &right,  NULL, NULL, NULL);
    	 modelParameters[i].volume = param;
    	 temp = ((left-s)/delta + (s-right)/delta)/2.0;
    	 TEST(dsdw[i+2*nls+2*nls*(nls-1)/2]);
    	 printf("%s dsdw[%s] = %g (%g, %s)\n", flag, modelParameters[i].label, dsdw[i+2*nls+2*nls*(nls-1)/2], temp, "from s - central difference");
       }
     }  else getchar();
   }
   
   printf("\n");
   
   /**************************************************************************
    Evaluate heat capacity of mixing and its derivatives
    **************************************************************************/
   cpmixLiq(FIRST | SECOND | THIRD, t, p, x, &cp, &dcpdt, dcpdx);

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate Cp and derivatives now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar();
     /* print and test cp */
     smixLiq(FIRST, t+deltaT, p, x, &temp, NULL, NULL, NULL);
     temp = t*(temp-s)/deltaT;
     TEST(cp);
     printf("%s cp = %g (%g, %s)\n", flag, cp, temp, "from s");

     /* print and test dcpdt */
     cpmixLiq(FIRST, t+deltaT, p, x, &temp, (double *) NULL, (double *) NULL);
     temp = (temp-cp)/deltaT;
     TEST(dcpdt);
     printf("%s dcpdt = %g (%g, %s)\n", flag, dcpdt, temp, "from cp");

     /* print and test dcpdx[] */
     for (i=0; i<nr; i++) {
       for (j=0; j<nr; j++) xtemp[j] = x[j];
       xtemp[i] += deltaX[i];
       cpmixLiq(FIRST, t, p, xtemp, &temp, (double *) 0, (double *) 0);
       temp = (temp-cp)/deltaX[i];
       TEST(dcpdx[i]);
       printf("%s dcpdx[%d] = %g (%g, %s)\n",flag, i, dcpdx[i], temp, "from cp");
     }
   } else getchar();
   printf("\n");

   /**************************************************************************
    Evaluate volume of mixing and its derivatives
    **************************************************************************/

   vmixLiq(FIRST | SECOND | THIRD | FOURTH | FIFTH | SIXTH | SEVENTH |EIGHTH |
   	   NINTH | TENTH, t, p, x, &v, dvdx, d2vdx2, &dvdt, &dvdp, &d2vdt2, 
   	   &d2vdtdp, &d2vdp2, d2vdxdt, d2vdxdp, NULL);

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate V now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar();
     /* print and test v */
     gmixLiq(FIRST, t, p+deltaP, x, &temp, (double *) NULL, (double **) NULL);
     temp = (temp-g)/deltaP;
     flag = ( ABS(temp - v) <= sqrt(TAU)*ABS(g) ) ? "OK " : "BAD";
     printf("%s v = %g (%g, %s)\n", flag, v, temp, "from g");
   } else getchar();

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate dVdr now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 
     /* print and test dvdx[] */
     for (i=0; i<nr; i++) {
       for (j=0; j<nr; j++) xtemp[j] = x[j];
       xtemp[i] += deltaX[i];
       vmixLiq(FIRST, t, p, xtemp, &temp, (double *) 0, (double **) 0,
 	 (double *) NULL, (double *) NULL, (double *) NULL, (double *) NULL,
 	 (double *) NULL, (double *) NULL, (double *) NULL, NULL);
       temp = (temp-v)/deltaX[i];
       TEST(dvdx[i]);
       printf("%s dvdx[%d] = %g (%g, %s)\n", flag, i, dvdx[i], temp, "from v");
     }
   } else getchar();
 
   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate d2Vdr2 now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 
     /* print and test d2vdx2[][] */
     for (i=0; i<nr; i++) {
       for (j=0; j<nr; j++) {
 	 for (k=0; k<nr; k++) xtemp[k] = x[k];
 	 xtemp[j] += deltaX[j];
 	 vmixLiq(SECOND, t, p, xtemp, (double *) 0, vtemp, (double **) 0,
 	   (double *) NULL, (double *) NULL, (double *) NULL, (double *) NULL,
 	   (double *) NULL, (double *) NULL, (double *) NULL, NULL);
 	 temp = (vtemp[i]-dvdx[i])/deltaX[j];
 	 TEST(d2vdx2[i][j]);
 	 printf("%s d2vdx2[%d][%d] = %g (%g, %s)\n", flag, i, j, d2vdx2[i][j],
 	   temp, "from dvdx[]");
       }
     }
   } else getchar();

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate dVdt, dVdp, etc.  now (y or n)? ");
   if (tolower(getchar()) == 'y') {
     getchar(); 
     /* print and test dvdt */
     vmixLiq(FIRST, t+deltaT, p, x, &temp, (double *) NULL, (double **) NULL,
       (double *) NULL, (double *) NULL, (double *) NULL, (double *) NULL,
       (double *) NULL, (double *) NULL, (double *) NULL, NULL);
     temp = (temp-v)/deltaT;
     TEST(dvdt);
     printf("%s dvdt = %g (%g, %s)\n", flag, dvdt, temp, "from v");
 
     /* print and test dvdp */
     vmixLiq(FIRST, t, p+deltaP, x, &temp, (double *) NULL, (double **) NULL,
       (double *) NULL, (double *) NULL, (double *) NULL, (double *) NULL,
       (double *) NULL, (double *) NULL, (double *) NULL, NULL);
     temp = (temp-v)/deltaP;
     TEST(dvdp);
     printf("%s dvdp = %g (%g, %s)\n", flag, dvdp, temp, "from v");

     /* print and test d2vdt2 */
     vmixLiq(FOURTH, t+deltaT, p, x, (double *) NULL, (double *) NULL,
       (double **) NULL, &temp, (double *) NULL, (double *) NULL,
       (double *) NULL, (double *) NULL, (double *) NULL, (double *) NULL, NULL);
     temp = (temp-dvdt)/deltaT;
     TEST(d2vdt2);
     printf("%s d2vdt2 = %g (%g, %s)\n", flag, d2vdt2, temp, "from dvdt");

     /* print and test d2vdtdp */
     vmixLiq(FOURTH, t, p+deltaP, x, (double *) NULL, (double *) NULL,
       (double **) NULL, &temp, (double *) NULL, (double *) NULL,
       (double *) NULL, (double *) NULL, (double *) NULL, (double *) NULL, NULL);
     temp = (temp-dvdt)/deltaP;
     TEST(d2vdtdp);
     printf("%s d2vdtdp = %g (%g, %s)\n", flag, d2vdtdp, temp, "from dvdt");

     /* print and test d2vdtdp */
     vmixLiq(FIFTH, t+deltaT, p, x, (double *) NULL, (double *) NULL,
       (double **) NULL, (double *) NULL, &temp, (double *) NULL,
       (double *) NULL, (double *) NULL, (double *) NULL, (double *) NULL, NULL);
     temp = (temp-dvdp)/deltaT;
     TEST(d2vdtdp);
     printf("%s d2vdtdp = %g (%g, %s)\n", flag, d2vdtdp, temp, "from dvdp");

     /* print and test d2vdp2 */
     vmixLiq(FIFTH, t, p+deltaP, x, (double *) NULL, (double *) NULL,
       (double **) NULL, (double *) NULL, &temp, (double *) NULL,
       (double *) NULL, (double *) NULL, (double *) NULL, (double *) NULL, NULL);
     temp = (temp-dvdp)/deltaP;
     TEST(d2vdp2);
     printf("%s d2vdp2 = %g (%g, %s)\n", flag, d2vdp2, temp, "from dvdp");

     /* print and test d2vdxdt[] */
     for (i=0; i<nr; i++) {
       for (j=0; j<nr; j++) xtemp[j] = x[j];
       xtemp[i] += deltaX[i];
       vmixLiq(FOURTH, t, p, xtemp, (double *) 0, (double *) 0, (double **) 0,
 	 &temp  	, (double *) NULL, (double *) NULL, (double *) NULL,
 	 (double *) NULL, (double *) NULL, (double *) NULL, NULL);
       temp = (temp-dvdt)/deltaX[i];
       TEST(d2vdxdt[i]);
       printf("%s d2vdxdt[%d] = %g (%g, %s)\n", flag, i, d2vdxdt[i], temp,
 	 "from dvdt");
     }

     /* print and test d2vdxdp[] */
     for (i=0; i<nr; i++) {
       for (j=0; j<nr; j++) xtemp[j] = x[j];
       xtemp[i] += deltaX[i];
       vmixLiq(FIFTH, t, p, xtemp, (double *) 0, (double *) 0, (double **) 0,
 	 (double *) NULL, &temp 	 , (double *) NULL, (double *) NULL,
 	 (double *) NULL, (double *) NULL, (double *) NULL, NULL);
       temp = (temp-dvdp)/deltaX[i];
       TEST(d2vdxdp[i]);
       printf("%s d2vdxdp[%d] = %g (%g, %s)\n", flag, i, d2vdxdp[i], temp,
 	 "from dvdp");
     }
   } else getchar();
   
   printf("\n");

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate H now (y or n)? ");
   if (tolower(getchar()) == 'y') getchar(); else getchar();

   /***************************************************************************
    Evaluate enthalpy of mixing and its parameter derivatives
    ***************************************************************************/

    hmixLiq(FIRST, t, p, x, &h, NULL);
    if (calculationMode == MODE_xMELTS) hmixLiq(SECOND, t, p, x, NULL, dhdw);

    /* print and test h */
    temp = g + t*s;
    TEST(h);
    printf("%s h = %g (%g, %s)\n", flag, h, temp, "from g and s"); 

   if (calculationMode == MODE_xMELTS) { 
     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Evaluate h-parameter H derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    	 double param = modelParameters[i].enthalpy;
    	 double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[i].enthalpy));
    	 double left, right;
    	 modelParameters[i].enthalpy = param + delta;
    	 hmixLiq(FIRST, t, p, x, &left, NULL);
    	 modelParameters[i].enthalpy = param - delta;
    	 hmixLiq(FIRST, t, p, x, &right,  NULL);
    	 modelParameters[i].enthalpy = param;
    	 temp = ((left-h)/delta + (h-right)/delta)/2.0;
    	 TEST(dhdw[i]);
    	 printf("%s dhdw[%s] = %g (%g, %s)\n", flag, modelParameters[i].label, dhdw[i], temp, "from h - central difference");
       }
     } else getchar();
    	
     /***************************************************************************
      Question to proceed
      ***************************************************************************/
     printf("Evaluate h-parameter S derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar(); 
       for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    	 double param = modelParameters[i].entropy;
    	 double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[i].entropy));
    	 double left, right;
    	 modelParameters[i].entropy = param + delta;
    	 hmixLiq(FIRST, t, p, x, &left, NULL);
    	 modelParameters[i].entropy = param - delta;
    	 hmixLiq(FIRST, t, p, x, &right,  NULL);
    	 modelParameters[i].entropy = param;
    	 temp = ((left-h)/delta + (h-right)/delta)/2.0;
    	 TEST(dhdw[i+nls+nls*(nls-1)/2]);
    	 printf("%s dhdw[%s] = %g (%g, %s)\n", flag, modelParameters[i].label, dhdw[i+nls+nls*(nls-1)/2], temp, "from h - central difference");
       }
     } else getchar();
 
     printf("Evaluate h-parameter V derivatives now (y or n)? ");
     if (tolower(getchar()) == 'y') {
       getchar();
       for (i=0; i<(nls*(nls-1)/2+nls); i++) {
    	 double param = modelParameters[i].volume;
    	 double delta = sqrt(sqrt(TAU))*(1.0+ABS(modelParameters[i].volume));
    	 double left, right;
    	 modelParameters[i].volume = param + delta;
    	 hmixLiq(FIRST, t, p, x, &left, NULL);
    	 modelParameters[i].volume = param - delta;
    	 hmixLiq(FIRST, t, p, x, &right,  NULL);
    	 modelParameters[i].volume = param;
    	 temp = ((left-h)/delta + (h-right)/delta)/2.0;
    	 TEST(dhdw[i+2*nls+2*nls*(nls-1)/2]);
    	 printf("%s dhdw[%s] = %g (%g, %s)\n", flag, modelParameters[i].label, dhdw[i+2*nls+2*nls*(nls-1)/2], temp, "from h - central difference");
       }
     }  else getchar();
   }
   
    printf("\n");

   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Evaluate mu O2 and derivatives now (y or n)? ");
   if (tolower(getchar()) != 'y') getchar(); else getchar();

   /***************************************************************************
    Evaluate oxygen potential routines and ferric/ferrous conversions
    ***************************************************************************/

   printf("    Note: The following test only insures internal consistency\n");
   printf("    of calls to conLiq with\n");
   printf("        inpMask = FISRT | SEVENTH and outMask = FIRST\n");
   printf("    and calls to conLiq with\n");
   printf("        inpMask = FIRST and outMask = SEVENTH.\n");

   for (i=0; i<nlc; i++) for (j=0, mtemp[i]=0.0; j<nlc; j++) 
     mtemp[i] += (liquid[j].liqToOx)[i]*moles[j];

   printf("    Input  Fe2O3/FeO = %13.6g/%13.6g\n", mtemp[3], mtemp[5]);
   conLiq(FIRST | SEVENTH, FIRST, t, p, mtemp, (double *) NULL,
     (double *) NULL, (double *) NULL, (double **) NULL,(double ***) NULL, 
     &logfo2);
   printf("    Output Fe2O3/FeO = %13.6g/%13.6g\n", mtemp[3], mtemp[5]);
   conLiq(FIRST, SEVENTH, t, p, mtemp, (double *) NULL, (double *) NULL, 
     (double *) NULL, (double **) NULL, (double ***) NULL, &temp);
   TEST(logfo2);
   printf("%s log10 fO2 = %g (%g, %s)\n", flag, logfo2, temp, 
     "from conLiq FIRST->SEVENTH");
   printf("\n");

   for (i=0; i<nlc; i++) for (j=0, moles[i]=0.0; j<nlc; j++) 
     moles[i] += (bulkSystem[j].oxToLiq)[i]*mtemp[j];

   muO2Liq(FIRST | SECOND | THIRD | FOURTH | FIFTH | SIXTH | SEVENTH |EIGHTH |
           NINTH | TENTH, t, p, moles, &muO2, dmuO2dm, &dmuO2dt, &dmuO2dp, 
           d2muO2dm2, d2muO2dmt, d2muO2dmp, &d2muO2dt2, &d2muO2dtp, &d2muO2dp2);

   /* Print and test muO2 */
   temp = 8.3143*t*log(10.0)*logfo2;
   TEST(muO2);
   printf("%s muO2 = %g (%g, %s)\n", flag, muO2, temp, "from defn of log fO2");

   /* print and test dmuO2dm[] */
   for (i=0; i<nlc; i++) {
     for (j=0; j<nlc; j++) mtemp[j] = moles[j];
     mtemp[i] += deltaM[i];
     muO2Liq(FIRST, t, p, mtemp, &temp, NULL, NULL, NULL, NULL, NULL, NULL,
       NULL, NULL, NULL);
     temp = (temp-muO2)/deltaM[i];
     TEST(dmuO2dm[i]);
     printf("%s dmuO2dm[%d] = %g (%g, %s)\n", flag, i, dmuO2dm[i], temp, 
       "from muO2");
   } 

   /* print and test dmuO2dt */
   muO2Liq(FIRST, t+deltaT, p, moles, &temp, NULL, NULL, NULL, NULL, NULL, 
     NULL, NULL, NULL, NULL);
   temp = (temp-muO2)/deltaT;
   TEST(dmuO2dt);
   printf("%s dmuO2dt = %g (%g, %s)\n", flag, dmuO2dt, temp, "from muO2"); 

   /* print and test dmuO2dp */
   muO2Liq(FIRST, t, p+deltaP, moles, &temp, NULL, NULL, NULL, NULL, NULL, 
     NULL, NULL, NULL, NULL);
   temp = (temp-muO2)/deltaP;
   TEST(dmuO2dp);
   printf("%s dmuO2dp = %g (%g, %s)\n", flag, dmuO2dp, temp, "from muO2"); 

   /* print and test d2muO2dm2[][] */
   for (i=0; i<nlc; i++) {
     for (j=0; j<nlc; j++) {
       for (k=0; k<nlc; k++) mtemp[k] = moles[k];
       mtemp[j] += deltaM[j];
       muO2Liq(SECOND, t, p, mtemp, NULL, vtemp, NULL, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL);
       temp = (vtemp[i]-dmuO2dm[i])/deltaM[j];
       TEST(d2muO2dm2[i][j]);
       printf("%s d2muO2dm2[%d][%d] = %g (%g, %s)\n", flag, i, j, 
         d2muO2dm2[i][j], temp, "from dmuO2dm[]");
     }
   }

   /* print and test d2muO2dmt[] */
   for (i=0; i<nlc; i++) {
     for (j=0; j<nlc; j++) mtemp[j] = moles[j];
     mtemp[i] += deltaM[i];
     muO2Liq(THIRD, t, p, mtemp, NULL, NULL, &temp, NULL, NULL, NULL, NULL,
       NULL, NULL, NULL);
     temp = (temp-dmuO2dt)/deltaM[i];
     TEST(d2muO2dmt[i]);
     printf("%s d2muO2dmt[%d] = %g (%g, %s)\n", flag, i, d2muO2dmt[i], temp, 
       "from dmuO2dt");
   } 

   /* print and test d2muO2dmp[] */
   for (i=0; i<nlc; i++) {
     for (j=0; j<nlc; j++) mtemp[j] = moles[j];
     mtemp[i] += deltaM[i];
     muO2Liq(FOURTH, t, p, mtemp, NULL, NULL, NULL, &temp, NULL, NULL, NULL,
       NULL, NULL, NULL);
     temp = (temp-dmuO2dp)/deltaM[i];
     TEST(d2muO2dmp[i]);
     printf("%s d2muO2dmp[%d] = %g (%g, %s)\n", flag, i, d2muO2dmp[i], temp, 
       "from dmuO2dp");
   } 

   /* print and test d2muO2dt2 */
   muO2Liq(THIRD, t+deltaT, p, moles, NULL, NULL, &temp, NULL, NULL, NULL, 
     NULL, NULL, NULL, NULL);
   temp = (temp-dmuO2dt)/deltaT;
   TEST(d2muO2dt2);
   printf("%s d2muO2dt2 = %g (%g, %s)\n", flag, d2muO2dt2, temp, 
     "from dmuO2dt"); 

   /* print and test d2muO2dtp */
   muO2Liq(THIRD, t, p+deltaP, moles, NULL, NULL, &temp, NULL, NULL, NULL, 
     NULL, NULL, NULL, NULL);
   temp = (temp-dmuO2dt)/deltaP;
   TEST(d2muO2dtp);
   printf("%s d2muO2dtp = %g (%g, %s)\n", flag, d2muO2dtp, temp, 
     "from dmuO2dt"); 

   /* print and test d2muO2dp2 */
   muO2Liq(FOURTH, t, p+deltaP, moles, NULL, NULL, NULL, &temp, NULL, NULL, 
     NULL, NULL, NULL, NULL);
   temp = (temp-dmuO2dp)/deltaP;
   TEST(d2muO2dp2);
   printf("%s d2muO2dp2 = %g (%g, %s)\n", flag, d2muO2dp2, temp, 
     "from dmuO2dp"); 
   printf("\n");

   /***************************************************************************
    Execute the viscosity routine                                        
    ***************************************************************************/

   printf("    Note: The following test only insures that the liquid\n");
   printf("          viscosity routine may be excuted.\n");
   printf("          It DOES NOT test the result.\n");
   visLiq(FIRST, t, p, x, &viscosity);
   printf("    viscosity = %g (log 10 poise, from visLiq)\n", viscosity);
   printf("\n");

   /************************************************************************** 
    Destroy space allocated for vectors and matrices		     
    **************************************************************************/

   free_vector(    moles, 0, nlc-1);
   free_vector(    mtemp, 0, nlc-1);
   free_vector(        x, 0, nr-1);
   free_vector(    xtemp, 0, nr-1);
   free_vector(    vtemp, 0, nlc-1);
   free_vector(   deltaM, 0, nlc-1);
   free_vector(   deltaX, 0, nr-1);
   free_vector(        a, 0, nlc-1);
   free_vector(       mu, 0, nlc-1);
   free_vector(    dmudt, 0, nlc-1);
   free_vector(     dgdx, 0, nr-1);
   free_vector(     dsdx, 0, nr-1);
   free_vector(     dvdx, 0, nr-1);
   free_vector(  dmuO2dm, 0, nlc-1);
   free_vector(d2muO2dmt, 0, nlc-1);
   free_vector(d2muO2dmp, 0, nlc-1);
   free_vector(    dcpdx, 0, nr-1);
   free_vector(  d2vdxdt, 0, nr-1);
   free_vector(  d2vdxdp, 0, nr-1);
   free_vector(     dgdw, 0, 3*(nls*(nls-1)/2+nls)-1);
   free_vector(     dsdw, 0, 3*(nls*(nls-1)/2+nls)-1);
   free_vector(     dhdw, 0, 3*(nls*(nls-1)/2+nls)-1);
   free_vector( xSpecies, 0, nls-1);

   free_matrix(     drdm, 0, nr-1, 0, nlc-1);
   free_matrix(    dtemp, 0, nr-1, 0, nlc-1);
   free_matrix(     dadx, 0, nlc-1, 0, nr-1);
   free_matrix(   d2gdx2, 0, nr-1, 0, nr-1);
   free_matrix(   d2sdx2, 0, nr-1, 0, nr-1);
   free_matrix(   d2vdx2, 0, nr-1, 0, nr-1);
   free_matrix(d2muO2dm2, 0, nlc-1, 0, nlc-1);
   free_matrix(    dmudw, 0, nlc-1, 0, 3*(nls*(nls-1)/2+nls)-1);
   free_matrix( d2mudtdw, 0, nlc-1, 0, 3*(nls*(nls-1)/2+nls)-1);

   for (i=0; i<nr; i++) free_matrix(d2rdm2[i], 0, nlc-1, 0, nlc-1);
   free(d2rdm2);

   for (i=0; i<nlc; i++) {free(names[i]); free(formulas[i]);}
   free(names);
   free(formulas);
    
   return 0;
}

/* End file: TEST_LIQUID-CONFIG.C */
