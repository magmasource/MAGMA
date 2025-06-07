const char *test_fo2_ver(void) { return "$Id: test_fo2.c,v 1.1 2008/05/02 19:03:52 ghiorso Exp $"; }

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include "interface.h"
Widget main_window, silmin_adb, topLevel;
MeltsEnviron meltsEnviron;

#include "silmin.h"
#include "recipes.h"

#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"

SilminState *silminState;
int calculationMode = MODE_DEFAULT;

#include <unistd.h>
#include <grace_np.h>

static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}

int main()
{
   int i, j, nFe2SiO5 = -1, nFe2SiO4 = -1;
   int nr = nlc - 1;
   float ftemp;
   double t = 2000.0 + 273.15;
   double pMax = 250000.0, p=100000.0;
   double logfo2 = -12.312, logfo2IW;
   double *moles, *x, *mu, *xSpecies, mtotal, g;
   /*		      SiO2 TiO2 Al2O3 Fe2O3 Cr2O3   FeO  MnO   MgO   NiO   CoO   CaO Na2O  K2O P2O5  H2O   CO2   SO3 Cl2O-1 F2O-1 */
   double grams[] = { 60.46, 0.45, 16.29,  0.921154, 0.04, 2.42796, 0.05, 1.94, 0.01, 0.01, 4.42, 4.02, 1.8, 0.01, 6.69, 0.01, 0.01,  0.01, 0.01 };

   InitComputeDataStruct();
   setModeToMixingLiq(FALSE);

   for (i=0; i<nlc; i++) if (strcmp(liquid[i].label, "Fe2SiO5") == 0) { nFe2SiO5 = i; break; }
   for (i=0; i<nlc; i++) if (strcmp(liquid[i].label, "Fe2SiO4") == 0) { nFe2SiO4 = i; break; }
   if ((nFe2SiO5 == -1) || (nFe2SiO4 == -1)) printf("Cannot find Fe species, nFe2SiO5 = %d, nFe2SiO4 = %d\n", nFe2SiO5, nFe2SiO4);

   printf("Do calculations at %7.2f C (y or n)? ", t-273.15);
   if (tolower(getchar()) != 'y') {
     getchar();
     printf("Input a temperature in (C):"); scanf("%f", &ftemp); t = ((double) ftemp) + 273.15;
     getchar();
   } else getchar();
   
   printf("Do calculations up to %7.2f bars (y or n)? ", pMax);
   if (tolower(getchar()) != 'y') {
     getchar();
     printf("Input a pressure in (bars):"); scanf("%f", &ftemp); pMax = (double) ftemp;
     getchar();
   } else getchar();

   moles    = vector(0, nlc-1);
   x        = vector(0, nr-1);
   mu       = vector(0, nlc-1);
   xSpecies = vector(0, nls-1);

   for (i=0; i<nc; i++) grams[i] /= bulkSystem[i].mw;
   for (i=0; i<nlc; i++) for (j=0,moles[i]=0.0; j<nc; j++) moles[i] += grams[j]*(bulkSystem[j].oxToLiq)[i];

   conLiq(SECOND, THIRD, t, p, NULL, moles, x, NULL, NULL, NULL, NULL);

   /* Calculate total moles */
   for (i=0, mtotal=0.0; i<nlc; i++) mtotal += moles[i];

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

   GraceRegisterErrorFunction (grace_error_function);
   if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }

   GracePrintf("WITH G0\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",  0.1,   0.1,  0.9, 0.9);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 10.0, -20.0, 25.0, 0.0);
    GracePrintf("XAXIS LABEL \"P (GPa)\"\n");
    GracePrintf("YAXIS LABEL \"log10 fo2\"\n");    
    GracePrintf("LEGEND ON\n");
    GracePrintf("FRAME ON\n");

    GracePrintf("g0.s%1.1d LINESTYLE 1\n", 0);
    GracePrintf("g0.s%1.1d COLOR 1\n", 	   0);
    GracePrintf("g0.s%1.1d SYMBOL 0\n",	   0);
    GracePrintf("g0.s%1.1d LINESTYLE 1\n", 1);
    GracePrintf("g0.s%1.1d COLOR 2\n", 	   1);
    GracePrintf("g0.s%1.1d SYMBOL 0\n",	   1);

   for (p=0.0; p<=pMax; p+=10000.0) {
     /* Test EOS model for this T and P combination */
     gmixLiq(FIRST, t, p, x, &g, NULL, NULL);
     if (!testLiq(EIGHTH, 0, 0, 0, 0, NULL, NULL, NULL, NULL)) { printf("EOS failure in liquid properties functions. Error: %d\n", liqERRstate); return 0; }

     actLiq(SECOND, t, p, x, NULL, mu, NULL, NULL);
     gibbs(t, p, "o2", &(oxygen.ref), NULL, NULL, &(oxygen.cur));
     
     /* 2 Fe2SiO5 = 2 Fe2SiO4 + O2			     */
     /* 0 = RT ln fO2 + mu0_O2 + 2 mu_Fe2SiO4 - 2 mu_Fe2SiO5 */
     /* 2 mu_Fe2SiO5 - 2 mu_Fe2SiO4 - mu0_O2 = RT ln fO2     */
     logfo2   = (2.0*mu[nFe2SiO5] - 2.0*mu[nFe2SiO4] - oxygen.cur.g)/(8.3143*t*log(10.0));
     logfo2IW = getlog10fo2(t, 1.0, FO2_IW) + 608.966*(p/10000.0)/t; 
     printf("log10 fO2 = %g, IW = %g, deltaIW = %g\n", logfo2, logfo2IW, logfo2-logfo2IW); 
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 0, p/10000.0, logfo2);  
     GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, p/10000.0, logfo2IW);  
     GracePrintf("REDRAW\n");
   }
   
   free_vector(    moles, 0, nlc-1);
   free_vector(        x, 0, nr-1);
   free_vector(       mu, 0, nlc-1);
   free_vector( xSpecies, 0, nls-1);
    
   return 0;
}
