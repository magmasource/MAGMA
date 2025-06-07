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

int main() {
   int i, j;
   int nr = nlc - 1;
   double t = 1200.0 + 273.15;
   double p = 1000.0;
   double logfO2 = -10.0;
   double *grams, *moles, *x, *mu, junk;
   FILE *input, *output;
   char buffer[1000];
   
   calculationMode = MODE__MELTS;

   liquid = meltsLiquid;
   solids = meltsSolids;
   nlc = meltsNlc;
   nls = meltsNls;
   npc = meltsNpc;

   printf("Cal to InitComputeDataStruct()\n");
   InitComputeDataStruct();

   setModeToMixingLiq(TRUE);
   
   grams  = vector(0, nlc-1);
   moles  = vector(0, nlc-1);
   x      = vector(0, nr-1);
   mu     = vector(0, nlc-1);
   
   input  = fopen("hornblende-liquids.csv", "r");
   output = fopen("hornblende-mus.csv",    "w");
   
   printf("Begin loop ...\n");
   while(fgets(buffer, 1000, input) != NULL) {
     printf("...new case\n");
     t = atof(strtok(buffer, ",")) + 273.15;
     p = atof(strtok(NULL, ",")) * 10000.0;
     logfO2 = atof(strtok(NULL, ","));
     /* 0,SiO2 1,TiO2 2,Al2O3 3,Fe2O3 4,Cr2O3 5,FeO 6,MnO 7,MgO 8,NiO 9,CoO 10,CaO 11,Na2O 12,K2O 13,P2O5 */
     for (i=0; i<14; i++) grams[i] = atof(strtok(NULL, ","));
     junk = atof(strtok(NULL, ","));      /* SrO */
     junk = atof(strtok(NULL, ","));      /* BaO */
     grams[14] = atof(strtok(NULL, ",")); /* H2O */

     if (t != 0.0) {
       for (i=0; i<nc; i++) grams[i] /= bulkSystem[i].mw;
       conLiq(FIRST | SEVENTH, FIRST, t, p, grams, NULL, NULL, NULL, NULL, NULL, &logfO2);
       for (i=0; i<nlc; i++) for (j=0,moles[i]=0.0; j<nc; j++) moles[i] += grams[j]*(bulkSystem[j].oxToLiq)[i];

       conLiq(SECOND, THIRD, t, p, NULL, moles, x, NULL, NULL, NULL, NULL);
       actLiq(SECOND, t, p, x, NULL, mu, NULL, NULL);
       
       for (i=0; i<19; i++) {
         if (moles[i] == 0.0) mu[i] = 0.0;
	 else {
           if (i == 7) printf("mu[0], mu[7] = %g, %g\n", mu[0], mu[7]);
	   gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
	   mu[i] += liquid[i].cur.g;
           if (i == 7) printf("mu[0], mu[7] = %g, %g\n", mu[0], mu[7]);
	 }
       }
       
       for (i=0; i<14; i++) fprintf(output, "%20.13e,", mu[i]);
       fprintf(output, "%20.13e,", 0.0);
       fprintf(output, "%20.13e,", 0.0);
       fprintf(output, "%20.13e\n", mu[18]); /* H2O */
     } else {
       for (i=0; i<16; i++) fprintf(output, "0.0,");
       fprintf(output, "0.0\n");
     }
   }
   
   fclose(input);
   fclose(output);
    
   return 0;
}

/* End file: TEST_LIQUID-CONFIG.C */
