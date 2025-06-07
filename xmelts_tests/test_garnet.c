#include "silmin.h"
#include "recipes.h"

#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"

int calculationMode = MODE_DEFAULT;

void *main_window, *silmin_adb, *topLevel, *meltsEnviron;
SilminState *silminState;

int main()
{
  double t, p;
  int i, nGarAlm, nMajAlm;

  printf("Calling function: InitComputeDataStruct().\n");
  InitComputeDataStruct();

  t = 1000.0;
  for (i=0; i<npc; i++) {
    if (!strcmp("garnet",      solids[i].label)) nGarAlm = i+2; /* first component Alm, Grs, Pyr      */
    if (!strcmp("majorite ss", solids[i].label)) nMajAlm = i+1; /* third component Grs, Pyr, Alm, Maj */
  }
  
  printf("T = %g K\n", t);
  for (p=0.0; p<31.0; p=p+1.0) {
    gibbs(t, (p == 0.0) ? 1.0 : p*10000.0, (char *) solids[nGarAlm].label, &(solids[nGarAlm].ref), NULL, NULL, &(solids[nGarAlm].cur));
    gibbs(t, (p == 0.0) ? 1.0 : p*10000.0, (char *) solids[nMajAlm].label, &(solids[nMajAlm].ref), NULL, NULL, &(solids[nMajAlm].cur));
    
    printf("P = %g, Gar: %g, Maj: %g, diff: %g " , p, (solids[nGarAlm].cur).v, (solids[nMajAlm].cur).v, (solids[nGarAlm].cur).v - (solids[nMajAlm].cur).v); 
    printf("Gar: %g, Maj: %g, diff: %g\n" , (solids[nGarAlm].cur).g, (solids[nMajAlm].cur).g, (solids[nGarAlm].cur).g - (solids[nMajAlm].cur).g); 

  }

  return 0;
}

/* End file: TEST_GIBBS.C */

