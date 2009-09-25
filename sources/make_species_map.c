const char *make_species_map_ver(void) { return "$Id:$"; }

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Test routine to evaluate the functions defined for the computation
**      of EOS properties in the liquid 
**      (file: MAKE_SPECIES_MAP.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  June 2, 2008 Original Version
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

#include <unistd.h>
#include <grace_np.h>

SilminState *silminState;
int calculationMode = MODE_DEFAULT;

static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}

int main()
{
  int i, j;
  int nr = nlc - 1;
  double t = 1200.0 + 273.15;
  double p = 1000.0;
  /*		     SiO2    TiO2  Al2O3  Fe2O3   Cr2O3   FeO     MnO   MgO   NiO  CoO	CaO    Na2O  K2O   P2O5  H2O   CO2  SO3  Cl2O-1 F2O-1 */
  double gramsM[] = { 48.68, 1.01, 17.64, 0.89,   0.0425, 7.59,   0.0,  9.10, 0.0, 0.0, 12.45, 2.65, 0.03, 0.08, 0.20, 0.0, 0.0, 0.0, 0.0 }; /* MORB     */
  double gramsR[] = { 75.50, 0.21, 13.00, 0.2796, 0.0,    0.8283, 0.0,  0.25, 0.0, 0.0,  0.95, 3.35, 5.55, 0.0,  6.00, 0.0, 0.0, 0.0, 0.0 }; /* rhyolite */
  double gramsP[] = { 45.47, 0.11,  4.00, 0.0002, 0.68,   7.2217, 0.0, 38.53, 0.0, 0.0,  3.59, 0.31, 0.0,  0.0,  0.0,  0.0, 0.0, 0.0, 0.0 }; /* mm3 */
  
  double *moles, *molesM, *molesR, *molesP, *x, *xSpecies;
  float ftemp;

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
      
   /**************************************************************************
    Evaluate t and p choices for calculations                        
    **************************************************************************/
   
   printf("Do calculations at %7.2f C (y or n)? ", t-273.15);
   if (tolower(getchar()) != 'y') {
     getchar();
     printf("Input a temperature in (C):"); scanf("%f", &ftemp); t = ((double) ftemp)+273.15;
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
   molesM   = vector(0, nlc-1);
   molesR   = vector(0, nlc-1);
   molesP   = vector(0, nlc-1);
   x        = vector(0, nr-1);
   xSpecies = vector(0, nls-1);

   /*************************************************************************** 
    Compute composition of the liquid phase (moles)
    ***************************************************************************/

   for (i=0; i<nc; i++) {
     gramsM[i] /= bulkSystem[i].mw;
     gramsR[i] /= bulkSystem[i].mw;
     gramsP[i] /= bulkSystem[i].mw;
   }
   
   for (i=0; i<nlc; i++) {
     for (j=0,molesM[i]=0.0; j<nc; j++) molesM[i] += gramsM[j]*(bulkSystem[j].oxToLiq)[i];
     for (j=0,molesR[i]=0.0; j<nc; j++) molesR[i] += gramsR[j]*(bulkSystem[j].oxToLiq)[i];
     for (j=0,molesP[i]=0.0; j<nc; j++) molesP[i] += gramsP[j]*(bulkSystem[j].oxToLiq)[i];
   }
   
  GraceRegisterErrorFunction (grace_error_function);
  if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }

  GracePrintf("G0 on\n");
  GracePrintf("G0 type Chart\n");
  GracePrintf("G0 stacked true\n");

  GracePrintf("WITH G0\n");
   GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",  0.1, 0.1, 0.9, 0.9);
   GracePrintf("WORLD %lf, %lf, %lf, %lf\n",  0.0, 0.0, 1.0, 1.0);

   GracePrintf("XAXIS TICK MAJOR 0.20\n");
   GracePrintf("XAXIS TICK MINOR 0.05\n");
   GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

   GracePrintf("XAXIS LABEL \"X\"\n");
   GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
   GracePrintf("XAXIS LABEL COLOR 2\n");

   GracePrintf("YAXIS TICK MAJOR 2.00\n");
   GracePrintf("YAXIS TICK MINOR 1.00\n");
   GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

   GracePrintf("YAXIS LABEL \"X\"\n");
   GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
   GracePrintf("YAXIS LABEL COLOR 2\n");
   
   GracePrintf("LEGEND ON\n");
   GracePrintf("legend 0.95, 1\n");
   GracePrintf("legend font 6\n");
   GracePrintf("legend char size 0.500000\n");

   GracePrintf("FRAME ON\n");
 
   for (i=0; i<nls; i++) {
     int color = i+1;
     char *temp = (char *) malloc((size_t) (strlen(liquid[i].label)+1)*sizeof(char));
     (void) strcpy(temp, liquid[i].label);
     if      (color > 30) color -= 30;
     else if (color > 15) color -= 15;
     GracePrintf("g0.s%1.1d LINESTYLE 1\n", i);
     GracePrintf("g0.s%1.1d TYPE BAR\n",    i);
     GracePrintf("g0.s%1.1d SYMBOL 0\n",    i);
     GracePrintf("g0.s%1.1d SYMBOL COLOR %d\n", i, color);
     GracePrintf("g0.s%1.1d SYMBOL PATTERN 1\n", i);
     GracePrintf("g0.s%1.1d SYMBOL FILL COLOR %d\n", i, color);
     GracePrintf("g0.s%1.1d SYMBOL FILL PATTERN 1\n", i);
     GracePrintf("g0.s%1.1d LEGEND \"%s\"\n", i, strtok(temp, " "));
     free(temp);
   }

   for (i=1; i<101; i++) {
     for (j=0; j<nlc; j++) moles[j] = molesM[j]*(101.0-i)/100.0 + molesM[j]*(i-1.0)/100.0;
     t = 1200.0 + (double) i*20.0 + 273.15;

     conLiq(SECOND, THIRD,          t, p, NULL, moles, x, NULL,     NULL, NULL, NULL);
     conLiq(THIRD, FOURTH | EIGHTH, t, p, NULL, NULL,  x, xSpecies, NULL, NULL, NULL);

     for (j=0; j<nls; j++)
       GracePrintf("g0.s%1.1d POINT %lf, %lf\n",  j, (101.0-i)/100.0, xSpecies[j]); /* liq-sol */

     GracePrintf("REDRAW\n");
   }
 
   /************************************************************************** 
    Destroy space allocated for vectors and matrices		     
    **************************************************************************/

   free_vector(   molesM, 0, nlc-1);
   free_vector(   molesR, 0, nlc-1);
   free_vector(   molesP, 0, nlc-1);
   free_vector(        x, 0, nr-1);
   free_vector( xSpecies, 0, nls-1);
    
   return 0;
}

/* End file: MAKE_SPECIES_MAP.C */
