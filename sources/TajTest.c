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
   double t;
   double p;
   double rSpinel[4], rBiotite[4];
   int nSan = -1, nH2O = -1, nTaj = -1, nSpn = -1;
   FILE *output;
   
   calculationMode = MODE__MELTS;

   liquid = meltsLiquid;
   solids = meltsSolids;
   nlc = meltsNlc;
   nls = meltsNls;
   npc = meltsNpc;

   printf("Cal to InitComputeDataStruct()\n");
   InitComputeDataStruct();
   setModeToMixingLiq(TRUE);
   
   for (i=0; i<npc; i++) {
     if (!strcmp("biotiteTaj", solids[i].label) && (solids[i].type == PHASE)) nTaj = i;
     if (!strcmp("spinel",     solids[i].label) && (solids[i].type == PHASE)) nSpn = i;
     if (!strcmp("water",      solids[i].label) && (solids[i].type == PHASE)) nH2O = i;
     if (!strcmp("sanidine",   solids[i].label)) nSan = i;
   }
   printf("%d %d %d %d\n", nTaj, nSpn, nH2O, nSan);
      
   rBiotite[0] = 0.0;       /* tbi  */  
   rBiotite[1] = 0.0;       /* east */  rSpinel[1] = 0.0;       /* chr */
                                        rSpinel[2] = 0.0;       /* ulv */
                                        rSpinel[3] = 1.0;       /* mag */
   output = fopen("biotite.csv", "w");
   
   for (j=0; j<2; j++) {
     if      (j == 0) p = 2070.0;
     else if (j == 1) p = 1035.0;
   for (i=0; i<3; i++) { /* fO2 */
     int FO2_CON;
     if      (i == 0) FO2_CON = FO2_HM;
     else if (i == 1) FO2_CON = FO2_NNO;
     else if (i == 2) FO2_CON = FO2_QFM;
     
   for (t=773.15; t<1273.15; t=t+10.0) {
     double muSpinel[5], muBiotite[5], muSanidine, muWater, muO2, muMag, muHer, muSpn, muAnn, muPhl;
     double dmu0 = 1000.0, dmu1 = 1000.0, dmu0Last = 1000.0, dmu1Last = 1000.0;
     double rTaj=0.8, rSpn=0.8, rTajLast = 1000.0, rSpnLast = 1000.0;
     int iter = 0;
     
     gibbs(t, p, "o2", &(oxygen.ref), NULL, NULL, &(oxygen.cur));                                          muO2       = oxygen.cur.g + 8.3143*t*log(10.0)*getlog10fo2(t, p, FO2_CON);
     gibbs(t, p, (char *) solids[nH2O].label,   &(solids[nH2O].ref),   NULL, NULL, &(solids[nH2O].cur));   muWater    = (solids[nH2O].cur).g;
     gibbs(t, p, (char *) solids[nSan].label,   &(solids[nSan].ref),   NULL, NULL, &(solids[nSan].cur));   muSanidine = (solids[nSan].cur).g;
     gibbs(t, p, (char *) solids[nTaj+4].label, &(solids[nTaj+4].ref), NULL, NULL, &(solids[nTaj+4].cur)); muAnn      = (solids[nTaj+4].cur).g;
     gibbs(t, p, (char *) solids[nTaj+5].label, &(solids[nTaj+5].ref), NULL, NULL, &(solids[nTaj+5].cur)); muPhl      = (solids[nTaj+5].cur).g;
     gibbs(t, p, (char *) solids[nSpn+2].label, &(solids[nSpn+2].ref), NULL, NULL, &(solids[nSpn+2].cur)); muHer      = (solids[nSpn+2].cur).g;
     gibbs(t, p, (char *) solids[nSpn+3].label, &(solids[nSpn+3].ref), NULL, NULL, &(solids[nSpn+3].cur)); muMag      = (solids[nSpn+3].cur).g;
     gibbs(t, p, (char *) solids[nSpn+4].label, &(solids[nSpn+4].ref), NULL, NULL, &(solids[nSpn+4].cur)); muSpn      = (solids[nSpn+4].cur).g;
     /*
     printf("O2  = %g\n", muO2);
     printf("H2O = %g %s\n", muWater, solids[nH2O].label);
     printf("San = %g %s\n", muSanidine, solids[nSan].label);
     printf("Ann = %g %s\n", muAnn, solids[nTaj+4].label);
     printf("Phl = %g %s\n", muPhl, solids[nTaj+5].label);
     printf("Her = %g %s\n", muHer, solids[nSpn+2].label);
     printf("Mag = %g %s\n", muMag, solids[nSpn+3].label);
     printf("Spn = %g %s\n", muSpn, solids[nSpn+4].label);
     */
     do {
       rSpinel[0]  = 1.0-rSpn;  /* sp  */
       rBiotite[2] = rTaj;      /* ann  */  
       rBiotite[3] = 1.0-rTaj;  /* phl  */
       actTaj(SECOND, t, p, rBiotite, NULL, muBiotite, NULL);
       actSpn(SECOND, t, p, rSpinel,  NULL, muSpinel,  NULL);

       dmu0 = muSanidine + (muMag + muSpinel[2]) + muWater - muO2/2.0 - (muAnn + muBiotite[3]);
       dmu1 = (muPhl + muBiotite[4]) + 3.0 * (muHer + muSpinel[1]) - (muAnn + muBiotite[3]) - 3.0 * (muSpn + muSpinel[3]);
       
       if (iter == 0) {
         rTajLast = rTaj;
	 rSpnLast = rSpn;
         rTaj -= 0.05;
	 rSpn += 0.05;
	 dmu0Last = dmu0;
	 dmu1Last = dmu1;
       } else {
         double deriv = (dmu0-dmu0Last)/(rTaj-rTajLast);
	 rTajLast = rTaj;
	 dmu0Last = dmu0;
	 rTaj = rTajLast - dmu0Last/deriv;
	 if (rTaj < 0.0) rTaj = 0.01;
	 if (rTaj > 1.0) rTaj = 0.99;
	 
	 deriv = (dmu1-dmu1Last)/(rSpn-rSpnLast);
	 rSpnLast = rSpn;
	 dmu1Last = dmu1;
	 rSpn = rSpnLast - dmu1Last/deriv;
	 if (rSpn < 0.0) rSpn = 0.00001;
	 if (rSpn > 1.0) rSpn = 0.99999;
       }
       iter++;
     } while ((iter < 100) && ((fabs(dmu0) > 0.001) || (fabs(dmu1) > 0.001)) );
     
     printf("fO2 = %d p = %5.0f, t = %5.0f ", FO2_CON, p, t);
     printf("iter = %3.3d rTaj = %8.6f, rSpn = %8.6f, dmu0 = %13.6g, dmu1 = %13.6g\n", iter, rTaj, rSpn, dmu0, dmu1); 

     fprintf(output,"%d %20.16e %20.16e %20.16e %20.16e %20.16e %20.16e\n", FO2_CON, p, t, rTaj, rSpn, dmu0, dmu1);
   }
   }
   }
   
   fclose(output);
    
   return 0;
}

/* End file: TEST_LIQUID-CONFIG.C */
