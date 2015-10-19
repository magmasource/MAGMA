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

int calculationMode = MODE_DEFAULT;

void *main_window, *silmin_adb, *topLevel, *meltsEnviron;
SilminState *silminState;

int main() {
  int i, j;
  double t = 1173.15;
  double p = 5000.00;
  FILE *output = fopen("thermo.dat", "w");

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
  
  InitComputeDataStruct();
  if (calculationMode == MODE_xMELTS) {
    printf("%s\n", liquid[nls-6].label);
    printf("%s\n", liquid[nls-2].label);
    printf("%s\n", liquid[nls-1].label);
    printf("%s\n", solids[npc-9].label);
    printf("%s\n", solids[npc-10].label);
    printf("%s\n", solids[npc-11].label);
    printf("%s\n", solids[npc-12].label);
    printf("%s\n", solids[npc-13].label);
  } else if (calculationMode == MODE__MELTS) printf("%s\n", solids[npc-10].label);
  else printf("%s\n", solids[npc-7].label);

  t = 1773.15;
  for (i=0; i<301; i++) {
    p = 100.0 + 100.0*i;
      
    if (calculationMode == MODE_xMELTS) {
      double hCorr1 = modelParameters[nls*(nls-1)/2 + nls - 2].enthalpy;
      double sCorr1 = modelParameters[nls*(nls-1)/2 + nls - 2].entropy;
      double hCorr2 = modelParameters[nls*(nls-1)/2 + nls - 1].enthalpy;
      double sCorr2 = modelParameters[nls*(nls-1)/2 + nls - 1].entropy;
      double hCorr3 = modelParameters[nls*(nls-1)/2 + nls - 6].enthalpy;
      double sCorr3 = modelParameters[nls*(nls-1)/2 + nls - 6].entropy;
      gibbs(t, p, (char *) liquid[nls-6].label, &(liquid[nls-6].ref), &(liquid[nls-6].liq), &(liquid[nls-6].fus), &(liquid[nls-6].cur));
      gibbs(t, p, (char *) liquid[nls-2].label, &(liquid[nls-2].ref), &(liquid[nls-2].liq), &(liquid[nls-2].fus), &(liquid[nls-2].cur));
      gibbs(t, p, (char *) liquid[nls-1].label, &(liquid[nls-1].ref), &(liquid[nls-1].liq), &(liquid[nls-1].fus), &(liquid[nls-1].cur));
      gibbs(t, p, (char *) solids[npc- 9].label, &(solids[npc- 9].ref), NULL, NULL, &(solids[npc- 9].cur));
      gibbs(t, p, (char *) solids[npc-10].label, &(solids[npc-10].ref), NULL, NULL, &(solids[npc-10].cur));
      //fprintf(output, "%20.13e %20.13e %20.13e %20.13e %20.13e %20.13e %20.13e\n", t, p/10.0, (liquid[nls-2].cur).g + hCorr1 - t*sCorr1, 
      //  (liquid[nls-1].cur).g + hCorr2 - t*sCorr2, (solids[npc-10].cur).g, (liquid[nls-6].cur).g + hCorr3 - t*sCorr3, (solids[npc-9].cur).g);
      fprintf(output, "%20.13e %20.13e %20.13e %20.13e %20.13e %20.13e %20.13e\n", t, p/10.0, (liquid[nls-2].cur).v, 
        (liquid[nls-1].cur).v, (solids[npc-10].cur).v, (liquid[nls-6].cur).v, (solids[npc-9].cur).v);
      
    } else if (calculationMode == MODE__MELTS) {
      gibbs(t, p, (char *) liquid[nlc-1].label, &(liquid[nlc-1].ref), &(liquid[nlc-1].liq), &(liquid[nlc-1].fus), &(liquid[nlc-1].cur));
      gibbs(t, p, (char *) solids[npc-10].label, &(solids[npc-10].ref), NULL, NULL, &(solids[npc-10].cur));
      fprintf(output, "%20.13e %20.13e %20.13e %20.13e\n", t, p/10.0, (liquid[nlc-1].cur).g, (solids[npc-10].cur).g);
      
    } else {
      gibbs(t, p, (char *) liquid[nlc-1].label, &(liquid[nlc-1].ref), &(liquid[nlc-1].liq), &(liquid[nlc-1].fus), &(liquid[nlc-1].cur));
      gibbs(t, p, (char *) solids[npc-7].label, &(solids[npc-7].ref), NULL, NULL, &(solids[npc-7].cur));
      fprintf(output, "%20.13e %20.13e %20.13e %20.13e\n", t, p/10.0, (liquid[nlc-1].cur).g, (solids[npc-7].cur).g);
    }

  }
  
  fclose(output);
  
  if (calculationMode == MODE_xMELTS) {
    FILE *outputExtra = fopen("fluid.dat", "w");
    t = 1273.15;
    p = 2000.0;
    gibbs(t, p, (char *) solids[npc- 9].label, &(solids[npc- 9].ref), NULL, NULL, &(solids[npc-11].cur)); // CO2 duan fluid
    gibbs(t, p, (char *) solids[npc-10].label, &(solids[npc-10].ref), NULL, NULL, &(solids[npc-12].cur)); // H2O duan fluid
    for (i=1; i<100; i++) {
      double r = (double) i*0.01, mu[2];
      (*solids[npc-13].activity)(SECOND, t, p, &r, NULL, mu, NULL);
      fprintf(outputExtra, "%20.13e %20.13e %20.13e %20.13e %20.13e %20.13e %20.13e\n", t, p/10.0, r, mu[0], mu[1], 
        mu[0]+(solids[npc-12].cur).g, mu[1]+(solids[npc-11].cur).g);
    }
    fclose(outputExtra);
  }

  return 0;
}

/* End file: TEST_GIBBS.C */

