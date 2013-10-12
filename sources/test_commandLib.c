#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#include "silmin.h"

#include "status.h"
MeltsStatus meltsStatus;

#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"

#define REC   134

int calculationMode = MODE_xMELTS;
int quad_tol_modifier = 1;

void (*additionalOutput) (char *filename) = NULL;
char *addOutputFileName = NULL;

int main (int argc, char *argv[]) {
  double bulkComposition[20];
  int i, j;
  
  if (argc != 13) {
    printf("Wrong number of arguments.\n");
    exit(1);
  }
  
  bulkComposition[ 0] = atof(argv[1]); /* SiO2  */
  bulkComposition[ 1] = atof(argv[2]); /* TiO2  */
  bulkComposition[ 2] = atof(argv[3]); /* Al2O3 */
  bulkComposition[ 3] = atof(argv[4]); /* Fe2O3 */
  bulkComposition[ 4] = 0.0;
  bulkComposition[ 5] = atof(argv[5]); /* FeO   */
  bulkComposition[ 6] = 0.0;
  bulkComposition[ 7] = atof(argv[6]); /* MgO   */
  bulkComposition[ 8] = 0.0;
  bulkComposition[ 9] = 0.0;
  bulkComposition[10] = atof(argv[7]); /* CaO   */
  bulkComposition[11] = atof(argv[8]); /* Na2O  */
  bulkComposition[12] = atof(argv[9]); /* K2O   */
  bulkComposition[13] = 0.0;
  bulkComposition[14] = atof(argv[10]);/* H2O   */
  bulkComposition[15] = atof(argv[11]);/* CO2   */
  bulkComposition[16] = 0.0;
  bulkComposition[17] = 0.0;
  bulkComposition[18] = 0.0;
  bulkComposition[19] = 0.0;
  
  liquid = meltsLiquid;
  solids = meltsSolids;
  nlc = meltsNlc;
  nls = meltsNls;
  npc = meltsNpc;
  
  InitComputeDataStruct();
  
  silminState = allocSilminStatePointer();
  for (i=0, j=0; i<npc; i++) if (solids[i].type == PHASE) { 
    if      (!strcmp(solids[i].label, "fayalite"))      (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "garnet"))        (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "melilite"))      (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "hornblende"))    (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "water"))         (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "cummingtonite")) (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "amphibole"))     (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "nepheline"))     (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "kalsilite"))     (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "ortho-oxide"))   (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "alloy-solid"))   (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "alloy-liquid"))  (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "lime"))          (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "periclase"))     (silminState->incSolids)[j] = FALSE;
    else if (!strcmp(solids[i].label, "leucite"))       (silminState->incSolids)[j] = FALSE;
    else                                                (silminState->incSolids)[j] = TRUE; 
    j++; 
  }
  (silminState->incSolids)[npc] = TRUE;
  silminState->nLiquidCoexist  = 1;  
  silminState->fo2Path  = FO2_NNO;
  silminState->fo2Delta = 0.0;

  silminState->fractionateFlu = FALSE;
  silminState->fractionateSol = FALSE; 
  silminState->fractionateLiq = FALSE;
  
  for (i=0, silminState->liquidMass=0.0; i<nc; i++) {
      (silminState->bulkComp)[i] = bulkComposition[i]/bulkSystem[i].mw;
      silminState->liquidMass += bulkComposition[i];
  }
  for (i=0; i<nlc; i++) 
      for ((silminState->liquidComp)[0][i]=0.0, silminState->oxygen=0.0, j=0; j<nc; j++) {
        (silminState->liquidComp)[0][i] += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i];
        silminState->oxygen += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
  }

  silminState->isenthalpic = FALSE;  
  silminState->isentropic  = FALSE; 
  silminState->isochoric   = FALSE; 
  silminState->T           = 1273.15; /* was 1073.15 */
  silminState->dspTstart   = 1273.15;
  silminState->dspTstop    =  973.15;
  silminState->dspTinc     =    1.0; 
  silminState->P           = atof(argv[12]);  
  silminState->dspPstart   = atof(argv[12]);  		  
  silminState->dspPstop    = atof(argv[12]);
  silminState->dspPinc     = 0.0;
  silminState->dspDPDH     = 0.0;
      
  while(!silmin());
 
  exit(0); 
}
