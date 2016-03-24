//
//  main.c
//  Coarsening
//
//  Created by Mark Ghiorso on 3/23/16.
//  Copyright © 2016 Mark Ghiorso. All rights reserved.
//

#include <stdio.h>

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

#define REC   134

int calculationMode = MODE__MELTS;
int quad_tol_modifier = 1;

void (*additionalOutput) (char *filename) = NULL;
char *addOutputFileName = NULL;

int main (int argc, char *argv[]) {
    double bulkComposition[20];
    int i, j, k;
    
    bulkComposition[ 0] = 69.98;  /* SiO2  */
    bulkComposition[ 1] =  0.48;  /* TiO2  */
    bulkComposition[ 2] = 14.44;  /* Al2O3 */
    bulkComposition[ 3] =  3.59;  /* Fe2O3 */
    bulkComposition[ 4] =  0.0;
    bulkComposition[ 5] =  0.0;
    bulkComposition[ 6] =  0.07;  /* MnO   */
    bulkComposition[ 7] =  0.99;  /* MgO   */
    bulkComposition[ 8] =  0.0;
    bulkComposition[ 9] =  0.0;
    bulkComposition[10] =  2.78;  /* CaO   */
    bulkComposition[11] =  2.88;  /* Na2O  */
    bulkComposition[12] =  4.62;  /* K2O   */
    bulkComposition[13] =  0.16;  /* P2O5  */
    bulkComposition[14] = 10.0;   /* H2O   */
    bulkComposition[15] =  0.0;
    bulkComposition[16] =  0.0;
    bulkComposition[17] =  0.0;
    bulkComposition[18] =  0.0;
    bulkComposition[19] =  0.0;
    
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
        else if (!strcmp(solids[i].label, "fluid"))         (silminState->incSolids)[j] = FALSE;
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
    silminState->T           = 760.0 + 273.15;
    silminState->dspTstart   = 760.0 + 273.15;
    silminState->dspTstop    = 741.0 + 273.15;
    silminState->dspTinc     =   0.1;
    silminState->P           = 2500.0;
    silminState->dspPstart   = 2500.0;
    silminState->dspPstop    = 2500.0;
    silminState->dspPinc     = 0.0;
    silminState->dspDPDH     = 0.0;
    while(!silmin());
    
    silminState->dspTstop    = 740.87 + 273.15;
    silminState->dspTinc     =   0.01;
    while(!silmin());
    
    for (int l=0; l<6; l++) {
        static double *m, *r, *muLiq, *muSol;
        double moles, gLiq, mLiq, mass, gibbsEnergy, oxSum;
        int ns;
        double deltaT = 0.0;
        
        if      (l == 1) deltaT = -  0.1;
        else if (l == 2) deltaT = -  0.5;
        else if (l == 3) deltaT = -  1.0;
        else if (l == 4) deltaT = -  5.0;
        else if (l == 5) deltaT = - 10.0;
        
        if (l > 0) {
            /* -> Calculate liquid end-member properties                                  */
            for (i=0; i<nlc; i++)
                gibbs(silminState->T+deltaT, silminState->P, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
            
            /* -> Calculate solid  end-member properties                                  */
            for (i=0, j=0; i<npc; i++) {
                if (solids[i].type == PHASE) {
                    if ((silminState->incSolids)[j]) {
                        if(solids[i].na == 1)
                            gibbs(silminState->T+deltaT, silminState->P, (char *) solids[i].label, &(solids[i].ref), NULL, NULL, &(solids[i].cur));
                        else {
                            for (k=0; k<solids[i].na; k++) {
                                gibbs(silminState->T+deltaT, silminState->P, (char *) solids[i+1+k].label, &(solids[i+1+k].ref), NULL, NULL, &(solids[i+1+k].cur));
                            }
                            i += solids[i].na;
                        }
                    }
                    j++;
                }
            }
        }
        
        if (r     == NULL) r     = (double *) malloc((unsigned) nlc*sizeof(double));
        if (m     == NULL) m     = (double *) malloc((unsigned) nlc*sizeof(double));
        if (muLiq == NULL) muLiq = (double *) malloc((unsigned) nlc*sizeof(double));
        if (muSol == NULL) muSol = (double *) malloc((unsigned) nlc*sizeof(double));
        
        gLiq = 0.0;
        mLiq = 0.0;
        conLiq(SECOND, THIRD, silminState->T+deltaT, silminState->P, NULL, silminState->liquidComp[0], r, NULL, NULL, NULL, NULL);
        
        gmixLiq (FIRST, silminState->T+deltaT, silminState->P, r, &gibbsEnergy,  NULL, NULL);
        actLiq(SECOND, silminState->T+deltaT, silminState->P, r, NULL, muLiq, NULL, NULL);
        
        for (i=0, moles=0.0; i<nlc; i++) moles +=  (silminState->liquidComp)[0][i];
        gibbsEnergy *= moles;
        for (i=0; i<nlc; i++) gibbsEnergy  += (silminState->liquidComp)[0][i]*(liquid[i].cur).g;
        
        for (i=0, oxSum=0.0; i<nc; i++) {
            double value = 0.0;
            for (j=0, value=0.0; j<nlc; j++) value += (liquid[j].liqToOx)[i]*(silminState->liquidComp)[0][j];
            value *= bulkSystem[i].mw;
            oxSum	 += value;
        }
        gLiq += gibbsEnergy; mLiq += oxSum;
        printf("\nT, %.2f, massLiq, %.2f\n", silminState->T+deltaT-273.15, mLiq);
        
        for (j=0; j<npc; j++)
            for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
                if (solids[j].na == 1) {
                    moles       = (silminState->solidComp)[j][ns];
                    mass        = (silminState->solidComp)[j][ns]*solids[j].mw;
                    
                    printf("%s =", solids[j].label);
                    double deltaG = -(solids[j].cur).g;
                    for (i=0; i<nlc; i++) if( (solids[j].solToLiq)[i] != 0.0) {
                        deltaG += (solids[j].solToLiq)[i]*((liquid[i].cur).g+muLiq[i]);
                        printf(" %+5.2f %-10.10s", (solids[j].solToLiq)[i], liquid[i].label);
                    }
                    printf(" massSol, %.4f deltaG, %.4f\n", mass, deltaG*moles/mass);
                    
                } else {
                    char *formula;
                    for (i=0, mass=0.0; i<solids[j].na; i++) {
                        m[i] = (silminState->solidComp)[j+1+i][ns];
                        mass += (silminState->solidComp)[j+1+i][ns]*solids[j+1+i].mw;
                    }
                    (*solids[j].convert)(SECOND, THIRD, silminState->T+deltaT, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                    (*solids[j].display)(FIRST, silminState->T+deltaT, silminState->P, r, &formula);
                    (*solids[j].gmix) (FIRST, silminState->T+deltaT, silminState->P, r, &gibbsEnergy,  NULL, NULL, NULL);
                    (*solids[j].activity) (SECOND, silminState->T+deltaT, silminState->P, r, NULL, muSol, NULL);
                    gibbsEnergy  *= (silminState->solidComp)[j][ns];
                    for (i=0; i<solids[j].na; i++) gibbsEnergy  += m[i]*(solids[j+1+i].cur).g;
                    
                    double totalDeltaG = 0.0;
                    for (k=0; k<solids[j].na; k++) {
                        printf("     %s =", solids[j+1+k].label);
                        double deltaG = -muSol[k]-(solids[j+1+k].cur).g;
                        for (i=0; i<nlc; i++) if( (solids[j+1+k].solToLiq)[i] != 0.0) {
                            deltaG += (solids[j+1+k].solToLiq)[i]*((liquid[i].cur).g+muLiq[i]);
                            printf(" %+5.2f %-10.10s", (solids[j+1+k].solToLiq)[i], liquid[i].label);
                        }
                        printf(" deltaG, %.4f\n", deltaG*m[k]);
                        totalDeltaG += deltaG*m[k];
                    }
                    
                    printf("%s, %s, deltaG, %.4f, massSol, %.4f\n", solids[j].label, formula, totalDeltaG/mass, mass);
                }
            }
        
    }
    
    exit(0);

}