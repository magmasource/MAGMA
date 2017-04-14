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

/* ================================================================================== */
/* ================================================================================== */
/* Private functions to support libMelts                                                      */
/* ================================================================================== */
/* ================================================================================== */

static int iAmInitialized = FALSE;

static void initializeLibrary(void) {
  liquid = meltsLiquid;
  solids = meltsSolids;
  nlc = meltsNlc;
  nls = meltsNls;
  npc = meltsNpc;

  InitComputeDataStruct();
  iAmInitialized = TRUE;
}

/* ================================================================================== */
/* ================================================================================== */
/* Public interface for libMelts                                                      */
/* ================================================================================== */
/* ================================================================================== */

/* ================================================================================== */
/* Returns oxide names and order for bulk composition vector                          */
/* Input:                                                                             */
/*   nCharInName  - number of characters dimensioned for each name                    */
/*                  i.e. in FORTRAN : CHARACTER*20, where nCharInName is then 20      */
/* Output:                                                                            */
/*   oxideNames   - array of oxide names, ordered as in MELTS                         */
/*                  memory must be allocated by calling FORTRAN program, i.e.          */
/*                  CHARACTER*20 oxideNames(25)                                       */
/*   numberOxides - number of oxides in the system                                    */
/* ================================================================================== */

void meltsgetoxidenames_(char oxideNames[], int *nCharInName, int *numberOxides) {
  int i, nCh = *nCharInName;
  if (!iAmInitialized) initializeLibrary();
  for (i=0; i<nc; i++) strncpy(oxideNames + i*sizeof(char)*nCh, bulkSystem[i].label, nCh);
  *numberOxides = nc;
}        

/* ================================================================================== */
/* Input and Output (as above except):           				      */
/*   oxidePtr     - array of blank strings, assumed all to be of the same length      */
/*   numberOxides - input lt or equal to amount of allocated storage, output as above */
/* ================================================================================== */

void getMeltsOxideNames(char *oxidePtr[], int *nCharInName, int *numberOxides) {
  int i, nCh = *nCharInName, nox = *numberOxides;
  char oxideNames[nCh*nox];
  meltsgetoxidenames_(oxideNames, nCharInName, numberOxides);
  for (i=0; i<*numberOxides; i++) strncpy(oxidePtr[i], &oxideNames[nCh*i], nCh);
}

/* ================================================================================== */
/* Returns phase names and order for output properties vector                         */
/* Input:                                                                             */
/*   nCharInName  - number of characters dimensioned for each name                    */
/*                  i.e. in FORTRAN : CHARACTER*20, where nCharInName is then 20      */
/* Output:                                                                            */
/*   phaseNames   - array of phase names, ordered as in MELTS                         */
/*                  memory must be allocated by calling FORTRAN program, i.e.         */
/*                  CHARACTER*20 phaseNames(25)                                       */
/*   numberPhases - number of unique phases in the system                             */
/*   phaseIndices - index numbers of phases                                           */
/* ================================================================================== */

void meltsgetphasenames_(char phaseNames[], int *nCharInName, int *numberPhases, int phaseIndices[]) {
  int i, np=0, nCh = *nCharInName;
  if (!iAmInitialized) initializeLibrary();
  
  strncpy(phaseNames + np*sizeof(char)*nCh, "system", nCh); phaseIndices[np] = 1; np++; 
  strncpy(phaseNames + np*sizeof(char)*nCh, "liquid", nCh); phaseIndices[np] = 2; np++;
  for (i=0; i<npc; i++) if (solids[i].type == PHASE) { 
  	strncpy(phaseNames + np*sizeof(char)*nCh, solids[i].label, nCh); 
  	phaseIndices[np] = 10*i + 10;
  	np++; 
  }
  *numberPhases = np;
}        

/* ================================================================================== */
/* Input and Output (as above except):           				      */
/*   phasePtr     - array of blank strings, assumed all to be of the same length      */
/*   numberPhases - input lt or equal to amount of allocated storage, output as above */
/* ================================================================================== */

void getMeltsPhaseNames(char *phasePtr[], int *nCharInName, int *numberPhases, int phaseIndices[]) {
  int i, nCh = *nCharInName, np = *numberPhases;
  char phaseNames[nCh*np];
  meltsgetphasenames_(phaseNames, nCharInName, numberPhases, phaseIndices);
  for (i=0; i<*numberPhases; i++) strncpy(phasePtr[i], &phaseNames[nCh*i], nCh);
}

/* ================================================================================== */
/* MELTS processing call       							      */
/* Input:           								      */
/*   nodeIndex       - Index number of node (must be unique). First time a given node */
/*                     is used the system is set to the input conditions and a single */
/*                     (mode = 1) calculation performed. Subsequent calls pickup from */
/*                     the last successful call and may be isothermal or isenthalpic  */
/*   mode            - for continuation call (i.e. node has already been initialised) */
/*                     = 0, isenthalpic, temperature is output                        */
/*                     = 1, temperature is input in place of enthalpy                 */
/*   pressure        - Pressure in bars of the node                                   */
/*   bulkComposition - Bulk composition in grams of oxides                            */ 
/*   nCharInName     - number of characters dimensioned for each name                 */
/*                     i.e. in FORTRAN : CHARACTER*20, where nCharInName is then 20   */
/* Input and Output                                                                   */
/*   enthalpy        - Input: Total enthalpy in J of the node, if mode = 0            */
/*                     Output: Computed system enthalpy if mode = 1                   */
/*   temperature     - Input: Temperature of the node (K), if mode = 1                */
/*                     Output: Computed temperature if mode = 0                       */
/* Output:                                                                            */
/*   phaseNames      - array of phase names for columns of phaseProperties            */
/*                   - first name is always "system"                                  */
/*                     memory must be allocated for this array by the calling         */
/*                     program, e.g. CHARACTER*20 phaseNames(20)                      */
/*                   - second name is "liquid" if present                             */
/*   numberPhases    - number of entries in phaseNames and columns in phaseProperties */
/*   iterations      - Number of quadratic iterations                                 */
/*   status          - 0 = success,                                                   */
/*                   - 1 - 100 non fatal error condition                              */
/*                   - > 100 fatal error condition                                    */
/*   phaseProperties - 2-d array, one column per phase, row length is fixed as        */
/*                     G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2,    */
/*                     oxide compositions in order of meltsGetOxideNames in grams,    */
/*                     volume fraction, density, viscosity (for liquid phase,         */
/*                     otherwise, zero)                                               */
/*                     The first column is always the properties of the system        */
/*   phaseIndices    - array of unique indices for phases loaded into phaseNames      */
/*                     or phaseProperties columns                                     */ 
/* ================================================================================== */


typedef struct _nodeList {
  int node;
  SilminState *silminState;
} NodeList;
static NodeList *nodeList;
static int numberNodes;

static int compareNodes(const void *aPt, const void *bPt) {
  NodeList *a = (NodeList *) aPt;
  NodeList *b = (NodeList *) bPt;
  return (a->node - b->node);
}

static SilminState *createSilminState(void) {
  int i, np;
  SilminState *silminStateTemp = allocSilminStatePointer();
  for (i=0, np=0; i<npc; i++) if (solids[i].type == PHASE) { (silminStateTemp->incSolids)[np] = TRUE; np++; }
  (silminStateTemp->incSolids)[npc] = TRUE;
  silminStateTemp->nLiquidCoexist  = 1;  
  silminStateTemp->fo2Path  = FO2_NONE;
  silminStateTemp->fo2Delta = 0.0;

  silminStateTemp->fractionateFlu = FALSE;  /* Could be set */
  silminStateTemp->fractionateSol = FALSE; 
  silminStateTemp->fractionateLiq = FALSE;

  return silminStateTemp;
}

static double viscosityFromGRD(double t, double *oxValues) {
  /* Model: Giordano D, Russell JK, Dingwell DB (2008) Viscosity of magmatic liquids: A model. EPSL 271, 123-134 */
  /* Oxide order: (input values in grams)
     [ 0] SiO2 [ 1] TiO2 [ 2] Al2O3 [ 3] Fe2O3 [ 4] Cr2O3 [ 5] FeO [ 6] MnO [ 7] MgO    [ 8] NiO   [ 9] CoO 
     [10] CaO  [11] Na2O [12] K2O   [13] P2O5  [14] H2O   [15] CO2 [16] SO3 [17] Cl2O-1 [18] F2O-1 [19] FeO1_3
  */
  double molePerCent[11], mTotal = 0.0, A = -4.55, B, C;
  int i;
  
  molePerCent[ 0] =     oxValues[ 0]/bulkSystem[ 0].mw; /* SiO2  */
  molePerCent[ 1] =     oxValues[ 1]/bulkSystem[ 1].mw; /* TiO2  */
  molePerCent[ 2] =     oxValues[ 2]/bulkSystem[ 2].mw; /* Al2O3 */
  molePerCent[ 3] = 2.0*oxValues[ 3]/bulkSystem[ 3].mw + oxValues[5]/bulkSystem[5].mw; /* FeO(T) */ 
  molePerCent[ 4] =     oxValues[ 6]/bulkSystem[ 6].mw; /* MnO   */
  molePerCent[ 5] =     oxValues[ 7]/bulkSystem[ 7].mw; /* MgO   */
  molePerCent[ 6] =     oxValues[10]/bulkSystem[10].mw; /* CaO   */
  molePerCent[ 7] =     oxValues[11]/bulkSystem[11].mw; /* Na2O  */
  molePerCent[ 8] =     oxValues[12]/bulkSystem[12].mw; /* K2O   */
  molePerCent[ 9] =     oxValues[13]/bulkSystem[13].mw; /* P2O5  */
  molePerCent[10] =     oxValues[14]/bulkSystem[14].mw; /* H2O   */
  for (i=0; i<11; i++) mTotal += molePerCent[i];
  for (i=0; i<11; i++) molePerCent[i] /= (mTotal != 0.0) ? mTotal/100.0 : 1.0;
  
  B  =  159.6*(molePerCent[0] + molePerCent[1]);
  B += -173.3*molePerCent[2];
  B +=   72.1*(molePerCent[3]+molePerCent[4]+molePerCent[9]);
  B +=   75.7*molePerCent[5];
  B +=  -39.0*molePerCent[6];
  B +=  -84.1*(molePerCent[7]+molePerCent[10]);
  B +=  141.5*(molePerCent[10] + log(1.0+molePerCent[10]));
  B +=   -2.43*(molePerCent[0] + molePerCent[1])*(molePerCent[3] + molePerCent[4] + molePerCent[5]);
  B +=   -0.91*(molePerCent[0] + molePerCent[1] + molePerCent[2] + molePerCent[9])*(molePerCent[7] + molePerCent[8] + molePerCent[10]);
  B +=   17.6*molePerCent[2]*(molePerCent[7] + molePerCent[8]);
  
  C  =   2.75*molePerCent[0];
  C +=  15.7*(molePerCent[1] + molePerCent[2]);
  C +=   8.3*(molePerCent[3] + molePerCent[4] + molePerCent[5]);
  C +=  10.2*molePerCent[6];
  C += -12.3*(molePerCent[7] + molePerCent[8]);
  C += -99.5*log(1.0+molePerCent[10]);
  C +=   0.30*(molePerCent[2] + molePerCent[3] + molePerCent[4] + molePerCent[5] + molePerCent[6] - molePerCent[9])
             *(molePerCent[7] + molePerCent[8] + molePerCent[10]);
	     
  return exp(log(10.0)*(A + B/(t - C)));
}

void meltsprocess_(int *nodeIndex, int *mode, double *pressure, double *bulkComposition, 
         double *enthalpy, double *temperature, 
  	     char phaseNames[], int *nCharInName, int *numberPhases, int *iterations, int *status, 
  	     double *phaseProperties, int phaseIndices[]) {
  int update = FALSE;
  int nCh = *nCharInName;
  if (!iAmInitialized) initializeLibrary();
  
  if (numberNodes != 0) {
    NodeList key, *res;
    key.node = *nodeIndex;
    res = bsearch(&key, nodeList, (size_t) numberNodes, sizeof(struct _nodeList), compareNodes);
    if (res == NULL) {
      numberNodes++;
      nodeList = (NodeList *) realloc(nodeList, (size_t) numberNodes*sizeof(struct _nodeList));
      (nodeList[numberNodes-1]).silminState = createSilminState();
      (nodeList[numberNodes-1]).node = *nodeIndex;
      silminState = (nodeList[numberNodes-1]).silminState;
      qsort(nodeList, (size_t) numberNodes, sizeof(struct _nodeList), compareNodes);
    } else { 
      int i;
      silminState = res->silminState;
      for(i=0; i<nc; i++) {
	if((silminState->bulkComp)[i] != 0.0) {
	  update = TRUE;
	  break;
	}
      }
    } 
  }  else {
    numberNodes = 1;
    nodeList = (NodeList *) realloc(nodeList, sizeof(struct _nodeList));
    (nodeList[0]).silminState = createSilminState();
    (nodeList[0]).node = *nodeIndex;
    silminState = (nodeList[0]).silminState;
  }
  
  if (update) {
    int i, j;
    static double *changeBC = NULL;
    if (changeBC == NULL) changeBC = (double *) malloc((size_t) nc*sizeof(double));
    for (i=0; i<nc; i++) {
      changeBC[i] = bulkComposition[i]/bulkSystem[i].mw - (silminState->bulkComp)[i];
      silminState->liquidMass += bulkComposition[i] - (silminState->bulkComp)[i]*bulkSystem[i].mw;
    }
    for (i=0; i<nc; i++) (silminState->bulkComp)[i] += changeBC[i];
    for (i=0; i<nlc; i++) 
      for (j=0; j<nc; j++) {
        (silminState->liquidComp)[0][i] += changeBC[j]*(bulkSystem[j].oxToLiq)[i];
        silminState->oxygen += changeBC[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
      }

    silminState->isenthalpic = FALSE;  
    silminState->isentropic  = FALSE; 
    silminState->isochoric   = FALSE; 
    silminState->T           = *temperature;
    silminState->dspTstart   = *temperature;
    silminState->dspTstop    = *temperature; 
    silminState->dspTinc     = 0.0; 
    silminState->P           = *pressure;  
    silminState->dspPstart   = *pressure;  		  
    silminState->dspPstop    = *pressure;

    if(*mode) { /* isothermal mode */
      silminState->refEnthalpy = 0.0;
    }
    else {
      silminState->isenthalpic = TRUE;  
      silminState->dspHstop    = *enthalpy; 
      silminState->dspHinc     = *enthalpy - silminState->refEnthalpy; 
      silminState->dspTstart   = 0.0;
      silminState->dspTstop    = 0.0; 
    }

    if ((silminState->fractionateSol || silminState->fractionateFlu) && silminState->fracSComp == NULL) {
      silminState->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
      silminState->nFracCoexist = (int *) calloc((unsigned) npc, sizeof(int));
    }
    if (silminState->fractionateLiq && silminState->fracLComp == NULL) {
      silminState->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
    }

  } else {
    int i, j;
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
    silminState->T           = *temperature;
    silminState->dspTstart   = *temperature;
    silminState->dspTstop    = *temperature; 
    silminState->dspTinc     = 0.0; 
    silminState->P           = *pressure;  
    silminState->dspPstart   = *pressure;  		  
    silminState->dspPstop    = *pressure;
    silminState->dspPinc     = 0.0;
    silminState->dspDPDH     = 0.0;

    if ((silminState->fractionateSol || silminState->fractionateFlu) && silminState->fracSComp == NULL) {
      silminState->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
      silminState->nFracCoexist = (int *) calloc((unsigned) npc, sizeof(int));
    }
    if (silminState->fractionateLiq && silminState->fracLComp == NULL) {
      silminState->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
    }

  }
      
  while(!silmin());
  
  strncpy(phaseNames, "system", nCh);
  *numberPhases = 1;
  phaseIndices[0] = 1;
  *iterations = -1;
  
  switch (meltsStatus.status) {
    case SILMIN_SUCCESS:
      *status = 0;
      break;
    case SILMIN_QUAD_MAX:
      *status = 1;
      break;
    case SILMIN_LIN_ZERO:
      *status = 100;
      break;
    case SILMIN_LIN_MAX:
      *status = 101;
      break;
    case SILMIN_ADD_LIQUID_1:
      *status = 102;
      break;
    case SILMIN_ADD_LIQUID_2:
      *status = 103;
      break;
    case SILMIN_ADD_LIQUID_3:
      *status = 104;
      break;
    case SILMIN_RANK:
      *status = 105;
      break;
    case SILMIN_TIME:
      *status = 106;
      break;
    case GENERIC_INTERNAL_ERROR:
      *status = 107;
      break;
    default:
      *status = 1000;
      break;
  }

  { /* output block */
    double gLiq = 0.0, hLiq = 0.0, sLiq = 0.0, vLiq = 0.0, cpLiq = 0.0, dcpdtLiq = 0.0, 
           dvdtLiq = 0.0, dvdpLiq = 0.0, d2vdt2Liq = 0.0, d2vdtdpLiq = 0.0, d2vdp2Liq = 0.0;
    double totalG=0.0, totalH=0.0, totalS=0.0, totalV=0.0, totalCp=0.0, totaldCpdT=0.0, 
           totaldVdT=0.0, totaldVdP=0.0, totald2VdT2=0.0, totald2VdTdP=0.0, totald2VdP2=0.0, temp;
    static double *m, *r, *oxVal;
    int i, j;
    int columnLength = 11 + nc + 3; /* G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2, + nc oxides + volume fraction, density, viscosity */
    
    if (m == NULL)	   m = (double *) malloc((size_t)      nc*sizeof(double));
    if (r == NULL)	   r = (double *) malloc((size_t) (nlc-1)*sizeof(double));
    if (oxVal == NULL) oxVal = (double *) malloc((size_t)      nc*sizeof(double));
    
    /* liquid is the second "phase" reported */
    if (silminState->liquidMass != 0.0) {
      int nl;
      double totalGrams=0.0;
      strncpy(phaseNames + sizeof(char)*nCh, "liquid", nCh);
      *numberPhases = 2;
      phaseIndices[1] = 2;
      
      for (i=0; i<nc; i++) oxVal[i]=0.0;
    
      for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
	    double moles;
	    double G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2;
	
        conLiq(SECOND, THIRD, silminState->T, silminState->P, NULL, silminState->liquidComp[nl], r, NULL, NULL, NULL, NULL);

        gmixLiq (FIRST, silminState->T, silminState->P, r, &G, NULL, NULL);
        hmixLiq (FIRST, silminState->T, silminState->P, r, &H, NULL);
        smixLiq (FIRST, silminState->T, silminState->P, r, &S, NULL, NULL, NULL);
        vmixLiq (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, 
	    silminState->T, silminState->P, r, &V, NULL, NULL, &dVdT, &dVdP, &d2VdT2, &d2VdTdP, &d2VdP2, NULL, NULL, NULL);
        cpmixLiq(FIRST | SECOND, 
	    silminState->T, silminState->P, r, &Cp, &dCpdT, NULL);

        for (i=0, moles=0.0; i<nlc; i++) moles +=  (silminState->liquidComp)[nl][i];
        G       *= moles; 
	    H       *= moles; 
	    S       *= moles;
        V	    *= moles; 
	    Cp      *= moles;
	    dCpdT   *= moles; 
	    dVdT    *= moles; 
	    dVdP    *= moles; 
	    d2VdT2  *= moles; 
	    d2VdTdP *= moles; 
	    d2VdP2  *= moles;

        for (i=0; i<nlc; i++) {
          G       += (silminState->liquidComp)[nl][i]*(liquid[i].cur).g;
          H       += (silminState->liquidComp)[nl][i]*(liquid[i].cur).h;
          S       += (silminState->liquidComp)[nl][i]*(liquid[i].cur).s;
          V       += (silminState->liquidComp)[nl][i]*(liquid[i].cur).v;
          Cp      += (silminState->liquidComp)[nl][i]*(liquid[i].cur).cp;
	      dCpdT   += (silminState->liquidComp)[nl][i]*(liquid[i].cur).dcpdt;
	      dVdT    += (silminState->liquidComp)[nl][i]*(liquid[i].cur).dvdt;
	      dVdP    += (silminState->liquidComp)[nl][i]*(liquid[i].cur).dvdp;
	      d2VdT2  += (silminState->liquidComp)[nl][i]*(liquid[i].cur).d2vdt2;
	      d2VdTdP += (silminState->liquidComp)[nl][i]*(liquid[i].cur).d2vdtdp;
	      d2VdP2  += (silminState->liquidComp)[nl][i]*(liquid[i].cur).d2vdp2;
        }

        for (i=0; i<nc; i++) {
    	  for (j=0; j<nlc; j++) oxVal[i] += (liquid[j].liqToOx)[i]*(silminState->liquidComp)[nl][j]*bulkSystem[i].mw;
	      totalGrams += oxVal[i];
        }

        gLiq    += G;    hLiq    += H;    sLiq      += S;      vLiq    += V;       cpLiq     += Cp;     dcpdtLiq += dCpdT; 
	    dvdtLiq += dVdT; dvdpLiq += dVdP; d2vdt2Liq += d2VdT2; d2vdtdpLiq += d2VdTdP; d2vdp2Liq += d2VdP2;
	
      } /* end loop over all liquids */
      
      phaseProperties[columnLength+ 0] = gLiq;
      phaseProperties[columnLength+ 1] = hLiq;
      phaseProperties[columnLength+ 2] = sLiq;
      phaseProperties[columnLength+ 3] = vLiq*10.0;
      phaseProperties[columnLength+ 4] = cpLiq;
      phaseProperties[columnLength+ 5] = dcpdtLiq;
      phaseProperties[columnLength+ 6] = dvdtLiq*10.0;
      phaseProperties[columnLength+ 7] = dvdpLiq*10.0;
      phaseProperties[columnLength+ 8] = d2vdt2Liq*10.0;
      phaseProperties[columnLength+ 9] = d2vdtdpLiq*10.0;
      phaseProperties[columnLength+10] = d2vdp2Liq*10.0;
      for (i=0; i<nc; i++) phaseProperties[columnLength+11+i] = oxVal[i]; 
      phaseProperties[columnLength+11+nc  ] = vLiq*10.0;
      phaseProperties[columnLength+11+nc+1] = (vLiq != 0.0) ? 100.0*totalGrams/vLiq : 0.0;
      phaseProperties[columnLength+11+nc+2] = viscosityFromGRD(silminState->T, oxVal);

    } /* end liquid block */

    /* begin solid block */
    for (j=0; j<npc; j++) {
      int ns;
      for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
        double G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2, totalGrams=0.0;
	 
        if (solids[j].na == 1) {
          G	  = (silminState->solidComp)[j][ns]*(solids[j].cur).g;
          H	  = (silminState->solidComp)[j][ns]*(solids[j].cur).h;
          S	  = (silminState->solidComp)[j][ns]*(solids[j].cur).s;
          V	  = (silminState->solidComp)[j][ns]*(solids[j].cur).v;
          Cp      = (silminState->solidComp)[j][ns]*(solids[j].cur).cp;
          dCpdT   = (silminState->solidComp)[j][ns]*(solids[j].cur).dcpdt;
          dVdT    = (silminState->solidComp)[j][ns]*(solids[j].cur).dvdt;
          dVdP    = (silminState->solidComp)[j][ns]*(solids[j].cur).dvdp;
          d2VdT2  = (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdt2;
          d2VdTdP = (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdtdp;
          d2VdP2  = (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdp2;

          totalG       += (silminState->solidComp)[j][ns]*(solids[j].cur).g;
          totalH       += (silminState->solidComp)[j][ns]*(solids[j].cur).h;
          totalS       += (silminState->solidComp)[j][ns]*(solids[j].cur).s;
          totalV       += (silminState->solidComp)[j][ns]*(solids[j].cur).v;
          totalCp      += (silminState->solidComp)[j][ns]*(solids[j].cur).cp;
          totaldCpdT   += (silminState->solidComp)[j][ns]*(solids[j].cur).dcpdt;
          totaldVdT    += (silminState->solidComp)[j][ns]*(solids[j].cur).dvdt;
          totaldVdP    += (silminState->solidComp)[j][ns]*(solids[j].cur).dvdp;
          totald2VdT2  += (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdt2;
          totald2VdTdP += (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdtdp;
          totald2VdP2  += (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdp2;
      
          for (i=0; i<nc; i++) {
	        oxVal[i] = (solids[j].solToOx)[i]*bulkSystem[i].mw*(silminState->solidComp)[j][ns];
	        totalGrams += oxVal[i];
	      }
	  
        } else {
          for (i=0; i<solids[j].na; i++) m[i] = (silminState->solidComp)[j+1+i][ns];

          (*solids[j].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
          (*solids[j].gmix) (FIRST, silminState->T, silminState->P, r, &G, NULL, NULL, NULL);
          (*solids[j].hmix) (FIRST, silminState->T, silminState->P, r, &H);
          (*solids[j].smix) (FIRST, silminState->T, silminState->P, r, &S, NULL, NULL);
          (*solids[j].vmix) (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, 
	     silminState->T, silminState->P, r, &V, NULL, NULL, &dVdT, &dVdP, &d2VdT2, &d2VdTdP, &d2VdP2, NULL, NULL);
          (*solids[j].cpmix)(FIRST | SECOND, silminState->T, silminState->P, r, &Cp, &dCpdT, NULL);

          G       *= (silminState->solidComp)[j][ns]; 	  
          H       *= (silminState->solidComp)[j][ns]; 
          S       *= (silminState->solidComp)[j][ns];
          V       *= (silminState->solidComp)[j][ns];
          Cp      *= (silminState->solidComp)[j][ns];
	      dCpdT   *= (silminState->solidComp)[j][ns];
	      dVdT    *= (silminState->solidComp)[j][ns];
	      dVdP    *= (silminState->solidComp)[j][ns];
	      d2VdT2  *= (silminState->solidComp)[j][ns];
	      d2VdTdP *= (silminState->solidComp)[j][ns];
	      d2VdP2  *= (silminState->solidComp)[j][ns];
	  
          for (i=0; i<solids[j].na; i++) {
            G       += m[i]*(solids[j+1+i].cur).g;
            H	    += m[i]*(solids[j+1+i].cur).h;
            S	    += m[i]*(solids[j+1+i].cur).s;
            V	    += m[i]*(solids[j+1+i].cur).v;
            Cp      += m[i]*(solids[j+1+i].cur).cp;
	        dCpdT   += m[i]*(solids[j+1+i].cur).dcpdt;
	        dVdT    += m[i]*(solids[j+1+i].cur).dvdt;
	        dVdP    += m[i]*(solids[j+1+i].cur).dvdp;
	        d2VdT2  += m[i]*(solids[j+1+i].cur).d2vdt2;
	        d2VdTdP += m[i]*(solids[j+1+i].cur).d2vdtdp;
	        d2VdP2  += m[i]*(solids[j+1+i].cur).d2vdp2;
          }

          totalG       += G;
          totalH       += H;
          totalS       += S;
          totalV       += V;
          totalCp      += Cp;
          totaldCpdT   += dCpdT;
	      totaldVdT    += dVdT;
	      totaldVdP    += dVdT;
	      totald2VdT2  += dVdT;
	      totald2VdTdP += dVdT;
	      totald2VdP2  += dVdT;
	  
          for (i=0; i<nc; i++) {
            int k;
            for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
	        totalGrams += oxVal[i];
          }
	  
        }

        phaseProperties[(*numberPhases)*columnLength+ 0] = G;
        phaseProperties[(*numberPhases)*columnLength+ 1] = H;
        phaseProperties[(*numberPhases)*columnLength+ 2] = S;
        phaseProperties[(*numberPhases)*columnLength+ 3] = V*10.0;
        phaseProperties[(*numberPhases)*columnLength+ 4] = Cp;
        phaseProperties[(*numberPhases)*columnLength+ 5] = dCpdT;
        phaseProperties[(*numberPhases)*columnLength+ 6] = dVdT*10.0;
        phaseProperties[(*numberPhases)*columnLength+ 7] = dVdP*10.0;
        phaseProperties[(*numberPhases)*columnLength+ 8] = d2VdT2*10.0;
        phaseProperties[(*numberPhases)*columnLength+ 9] = d2VdTdP*10.0;
        phaseProperties[(*numberPhases)*columnLength+10] = d2VdP2*10.0;
        for (i=0; i<nc; i++) phaseProperties[(*numberPhases)*columnLength+11+i] = oxVal[i]; 
	    phaseProperties[(*numberPhases)*columnLength+11+nc  ] = V*10.0;
	    phaseProperties[(*numberPhases)*columnLength+11+nc+1] = (V != 0.0) ? 100.0*totalGrams/V : 0.0;
	    phaseProperties[(*numberPhases)*columnLength+11+nc+2] = 0.0;
	
        strncpy(phaseNames+(*numberPhases)*sizeof(char)*nCh,solids[j].label, nCh);
        phaseIndices[(*numberPhases)] = j*10 + ns + 10;
	    (*numberPhases)++;
	
      } /* end loop on ns */
    }  /* end loop on j */
    /* end solid block */

    /* system poperties */
    phaseProperties[ 0] = gLiq + totalG;
    phaseProperties[ 1] = hLiq + totalH;
    phaseProperties[ 2] = sLiq + totalS;
    phaseProperties[ 3] = (vLiq + totalV)*10.0;
    phaseProperties[ 4] = cpLiq + totalCp;
    phaseProperties[ 5] = dcpdtLiq + totaldCpdT;
    phaseProperties[ 6] = (dvdtLiq + totaldVdT)*10.0;
    phaseProperties[ 7] = (dvdpLiq + totaldVdP)*10.0;
    phaseProperties[ 8] = (d2vdt2Liq + totald2VdT2)*10.0;
    phaseProperties[ 9] = (d2vdtdpLiq + totald2VdTdP)*10.0;
    phaseProperties[10] = (d2vdp2Liq + totald2VdP2)*10.0;
    for (i=0, temp=0.0; i<nc; i++) {
      phaseProperties[11+i] = bulkComposition[i]; 
      temp += bulkComposition[i];
    }
    phaseProperties[11+nc  ] = 1.0;
    phaseProperties[11+nc+1] = ((vLiq+totalV) != 0.0) ? 100.0*temp/(vLiq+totalV) : 0.0;
    phaseProperties[11+nc+2] = 0.0;
    
    if ((vLiq+totalV) != 0.0) for (i=1; i<=(*numberPhases); i++) phaseProperties[i*columnLength+11+nc] /= 10.0*(vLiq+totalV);
    
    silminState->refEnthalpy = hLiq+totalH;

    /* final conditions */

    *enthalpy    = silminState->refEnthalpy;
    *temperature = silminState->T;

  } /* end output block */
}

/* ================================================================================== */
/* Returns explanatory string associated with input status                            */
/* Input:                                                                             */
/*   status      - status integer returned from meltsProcess                          */
/*   nCharInName - number of characters dimensioned for each name                     */
/*                 i.e. in FORTRAN : CHARACTER*100, where nCharInName is then 100     */
/* Output:                                                                            */
/*   errorString - character string describing status                                 */
/* ================================================================================== */

void meltsgeterrorstring_(int *status, char *errorString, int *nCharInName) {
  int nCh = *nCharInName;
  switch (*status) {
    case 0:
      strncpy(errorString, "Successful run.  No errors.", nCh);
      break;
    case 1:
      strncpy(errorString, "Quadratic iterations exceeded.", nCh);
      break;
    case 100:
      strncpy(errorString, "Steplength for linear search tending towards zero.", nCh);
      break;
    case 101:
      strncpy(errorString, "Steplength for linear search tending towards maximum.", nCh);
      break;
    case 102:
      strncpy(errorString, "Error condition detected in adding a liquid to the assemblage (1).", nCh);
      break;
    case 103:
      strncpy(errorString, "Error condition detected in adding a liquid to the assemblage (2)", nCh);
      break;
    case 104:
      strncpy(errorString, "Error condition detected in adding a liquid to the assemblage (3)", nCh);
      break;
    case 105:
      strncpy(errorString, "Rank deficiency coondition detected.  Most likely a consequence of phase rule violation.", nCh);
      break;
    case 106:
      strncpy(errorString, "Time limit exceeded.", nCh);
      break;
    case 107:
      strncpy(errorString, "Unspecified internal fatal error.", nCh);
      break;
    case 1000:
      strncpy(errorString, "Undefined error condition.", nCh);
      break;
    default:
      strncpy(errorString, "Unknown error condition.", nCh);
      break;
  }
}

/* =================================================================================== */
/* Input and Output (combination of the above, except):                                */
/*   phasePtr     - array of blank strings, assumed all to be of the same length       */
/*   numberPhases  - input lt or equal to amount of allocated storage, output as above */
/*   nCharInString - number of characters dimensioned for error string                 */
/*   propertiesPtr - this is double[][33], instead of double*, and rows and columns    */
/*                   are switched when calling from C rather than Fortran              */
/* =================================================================================== */

void driveMeltsProcess(int *nodeIndex, int *mode, double *pressure, double *bulkComposition,
		       double *enthalpy, double *temperature,
		       char *phasePtr[], int *nCharInName, int *numberPhases, int *iterations, 
		       char *errorString, int *nCharInString, double propertiesPtr[][nc+14], int phaseIndices[]) {
  int i, j, nCh = *nCharInName, np = *numberPhases, status;
  char phaseNames[nCh*np];
  double phaseProperties[(nc+14)*np];

  meltsprocess_(nodeIndex, mode, pressure, bulkComposition, enthalpy, temperature,
		phaseNames, nCharInName, numberPhases, iterations, &status, phaseProperties, phaseIndices);
  for (i=0; i<*numberPhases; i++) strncpy(phasePtr[i], &phaseNames[nCh*i], nCh);
  for (i=0; i<*numberPhases; i++) for (j=0; j<nc+14; j++) propertiesPtr[i][j] = phaseProperties[(nc+14)*i + j];

  meltsgeterrorstring_(&status, errorString, nCharInString);

}

/* ================================================================================== */
/* Adjust settings for a given node (if node does not exist it will be created)       */
/* Input:           								                                  */
/*   nodeIndex       - Index number of node (must be unique).                         */
/*   property        - a melts file like string to set fO2 or toggle fractionation:   */
/*                     = 'log fo2 path: value', value is fmq, qfm, coh, nno, iw or hm */
/*                     = 'log fo2 delta: value', value is an integer or real          */
/*                     = 'mode: fractionate phase' phase is solids, liquids or fluids */
/*                     = 'mode: batch phase', phase as above                          */
/* ================================================================================== */

void meltssetsystemproperty_(int *nodeIndex, char *property) {
  int i, len;
  float temporary;
  char line[REC];

  if (!iAmInitialized) initializeLibrary();

  if (numberNodes != 0) {
    NodeList key, *res;
    key.node = *nodeIndex;
    res = bsearch(&key, nodeList, (size_t) numberNodes, sizeof(struct _nodeList), compareNodes);
    if (res == NULL) {
      numberNodes++;
      nodeList = (NodeList *) realloc(nodeList, (size_t) numberNodes*sizeof(struct _nodeList));
      (nodeList[numberNodes-1]).silminState = createSilminState();
      (nodeList[numberNodes-1]).node = *nodeIndex;
      silminState = (nodeList[numberNodes-1]).silminState;
      qsort(nodeList, (size_t) numberNodes, sizeof(struct _nodeList), compareNodes);
    } else { 
      silminState = res->silminState;
    } 
  }  else {
    numberNodes = 1;
    nodeList = (NodeList *) realloc(nodeList, sizeof(struct _nodeList));
    (nodeList[0]).silminState = createSilminState();
    (nodeList[0]).node = *nodeIndex;
    silminState = (nodeList[0]).silminState;
  }

  len = strlen(property); for (i=0; i<MIN(len, REC); i++) line[i] = tolower(property[i]);

  if (!strncmp(line, "log fo2 path: ",          MIN(len,14))) {
    if        (!strncmp(&line[14], "none", MIN((len-14), 4))) {
      silminState->fo2Path = FO2_NONE;
    }  else if (!strncmp(&line[14], "fmq", MIN((len-14), 3))) {
      silminState->fo2Path = FO2_QFM;
    }  else if (!strncmp(&line[14], "qfm", MIN((len-14), 3))) {
      silminState->fo2Path = FO2_QFM;
    }  else if (!strncmp(&line[14], "coh", MIN((len-14), 3))) {
      silminState->fo2Path = FO2_COH;
    } else if (!strncmp(&line[14], "nno",  MIN((len-14), 3))) {
      silminState->fo2Path =  FO2_NNO;
    } else if (!strncmp(&line[14], "iw",   MIN((len-14), 2))) {
      silminState->fo2Path = FO2_IW; 
    } else if (!strncmp(&line[14], "hm",   MIN((len-14), 2))) {
      silminState->fo2Path = FO2_HM;
    }
  }
  else if (!strncmp(line, "log fo2 delta: ", MIN(len, 14))) {
    if (!(sscanf(&line[15], "%f", &temporary) == EOF)) silminState->fo2Delta = (double) temporary;
  }
  else if (!strncmp(line, "mode: ",                                MIN(len, 6))) {
    if        (!strncmp(&line[6],  "fractionate solids",             MIN((len-6), 18))) {
      silminState->fractionateSol = TRUE; 
    } else if (!strncmp(&line[6],  "fractionate liquids",            MIN((len-6), 19))) {
      silminState->fractionateLiq = TRUE;
    } else if (!strncmp(&line[6],  "fractionate fluids",             MIN((len-6), 18))) {
      silminState->fractionateFlu = TRUE;
    }
  }

 }

/* ================================================================================== */
/* Input (as above except):           			                 	      */
/*   properties      - array of strings one for each property to be set               */
/*   numberStrings   - number of strings                                              */
/* ================================================================================== */

void setMeltsSystemProperties(int *nodeIndex, char *properties[], int *numberStrings) {
  int i;

  for (i=0; i<*numberStrings; i++) meltssetsystemproperty_(nodeIndex, properties[i]);

}

/* ================================================================================== */
/* Retrieves properties of solid and liquid phases                                    */
/* Input:           								      */
/*   phaseName       - string as returned from meltsGetPhaseNames                     */
/*   temperature     - Temperature in Kelvins of the node                             */
/*   pressure        - Pressure in bars of the node                                   */
/*   bulkComposition - Bulk composition of the phase in grams of oxides               */ 
/* Output:                                                                            */
/*   phaseProperties - 1-d array, properties in the order                             */
/*                     G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2     */
/* ================================================================================== */

typedef struct _phaseList {
  int index;
  char *name;
} PhaseList;
static PhaseList *phaseList;

static int comparePhases(const void *aPt, const void *bPt) {
  PhaseList *a = (PhaseList *) aPt;
  PhaseList *b = (PhaseList *) bPt;
  return strcmp(a->name, b->name);
}

void meltsgetphaseproperties_(char *phaseName, double *temperature, 
         double *pressure, double *bulkComposition, double *phaseProperties) {
  static int np;
  static PhaseList key;
  PhaseList *res;

  if (!iAmInitialized) initializeLibrary();
  
  if (phaseList == NULL) {
    int i, maxLength = 7;
    for (i=0, np=1; i<npc; i++) if (solids[i].type == PHASE) np++;
    phaseList = (PhaseList *) malloc((size_t) np*sizeof(struct _phaseList));
    
    phaseList[0].index = -1;
    phaseList[0].name = (char *) malloc ((size_t) 7*sizeof(char));
    strcpy(phaseList[0].name, "liquid");
    
    for (i=0, np=1; i<npc; i++) if (solids[i].type == PHASE) {
      int length = strlen(solids[i].label)+1;
      maxLength = (maxLength < length) ? length : maxLength;
      phaseList[np].index = i;
      phaseList[np].name = (char *) malloc((size_t) length*sizeof(char));
      strcpy(phaseList[np].name, solids[i].label);
      np++;
    }
    
    qsort(phaseList, (size_t) np, sizeof(struct _phaseList), comparePhases);
    key.name = (char *) malloc((size_t) maxLength);
  }

  strcpy(key.name, phaseName);
  res = bsearch(&key, phaseList, (size_t) np, sizeof(struct _phaseList), comparePhases);
  
  if (res == NULL) { phaseProperties = NULL; return; }
  else { 
    int i, j = res->index;
    double G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2;  
    
    if (j < 0) { /* liquid */
      double *m, *r, mTot;
      int k;
      m = (double *) calloc((size_t) nlc,    sizeof(double));
      r = (double *) malloc((size_t) (nlc-1)*sizeof(double));
      for (k=0; k<nc; k++) for (i=0; i<nlc; i++) m[i] += (bulkSystem[k].oxToLiq)[i]*bulkComposition[k]/bulkSystem[k].mw;

      if (silminState->fo2Path != FO2_NONE) {
	silminState->fo2 = getlog10fo2(*temperature, *pressure, silminState->fo2Path);
	conLiq(FIRST | SEVENTH, FIRST, *temperature, *pressure, m, NULL, NULL, NULL, NULL, NULL, &(silminState->fo2));
	for (i=0; i<nc; i++) for (j=0, bulkComposition[i] = 0.0; j<nlc; j++) 
			       bulkComposition[i] += m[j]*(liquid[j].liqToOx)[i]*bulkSystem[i].mw;
      }

      conLiq(SECOND, THIRD, *temperature, *pressure, NULL, m, r, NULL, NULL, NULL, NULL);

      gmixLiq (FIRST, *temperature, *pressure, r, &G, NULL, NULL);
      hmixLiq (FIRST, *temperature, *pressure, r, &H, NULL);
      smixLiq (FIRST, *temperature, *pressure, r, &S, NULL, NULL, NULL);
      vmixLiq (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, 
        *temperature, *pressure, r, &V, NULL, NULL, &dVdT, &dVdP, &d2VdT2, &d2VdTdP, &d2VdP2, NULL, NULL, NULL);
      cpmixLiq(FIRST | SECOND, *temperature, *pressure, r, &Cp, &dCpdT, NULL);

      for (i=0, mTot=0.0; i<nlc; i++) {
        mTot +=  m[i];
	gibbs(*temperature, *pressure, phaseName, &liquid[i].ref, &liquid[i].liq, &liquid[i].fus, &liquid[i].cur);
      }
	
      G       *= mTot; 
      H       *= mTot; 
      S       *= mTot;
      V       *= mTot; 
      Cp      *= mTot;
      dCpdT   *= mTot; 
      dVdT    *= mTot; 
      dVdP    *= mTot; 
      d2VdT2  *= mTot; 
      d2VdTdP *= mTot; 
      d2VdP2  *= mTot;

      for (i=0; i<nlc; i++) {
        G	+= m[i]*(liquid[i].cur).g;
        H	+= m[i]*(liquid[i].cur).h;
        S	+= m[i]*(liquid[i].cur).s;
        V	+= m[i]*(liquid[i].cur).v;
        Cp	+= m[i]*(liquid[i].cur).cp;
        dCpdT	+= m[i]*(liquid[i].cur).dcpdt;
        dVdT	+= m[i]*(liquid[i].cur).dvdt;
        dVdP	+= m[i]*(liquid[i].cur).dvdp;
        d2VdT2  += m[i]*(liquid[i].cur).d2vdt2;
        d2VdTdP += m[i]*(liquid[i].cur).d2vdtdp;
        d2VdP2  += m[i]*(liquid[i].cur).d2vdp2;
      }
      
      free(m);
      free(r);

    } else if (solids[j].na == 1) {
      double mass = 0.0, factor = 1.0;
      for (i=0; i<nc; i++) mass += bulkComposition[i];
      gibbs(*temperature, *pressure, phaseName, &solids[j].ref, NULL, NULL, &solids[j].cur);
      factor = mass/solids[j].mw;
      
      G       = factor*(solids[j].cur).g;
      H       = factor*(solids[j].cur).h;
      S       = factor*(solids[j].cur).s;
      V       = factor*(solids[j].cur).v;
      Cp      = factor*(solids[j].cur).cp;
      dCpdT   = factor*(solids[j].cur).dcpdt;
      dVdT    = factor*(solids[j].cur).dvdt;
      dVdP    = factor*(solids[j].cur).dvdp;
      d2VdT2  = factor*(solids[j].cur).d2vdt2;
      d2VdTdP = factor*(solids[j].cur).d2vdtdp;
      d2VdP2  = factor*(solids[j].cur).d2vdp2;

    } else {
      double e[106], *m, *r, mTot; 
      int k;
      for (i=0; i<106; i++) e[i] = 0.0;
      for (i=0; i<nc; i++) {
        double mOx = bulkComposition[i]/bulkSystem[i].mw;
	for (k=0; k<106; k++) e[k] += mOx*(bulkSystem[i].oxToElm)[k];
      }
      m = (double *) malloc ((size_t) solids[j].na*sizeof(double));
      r = (double *) malloc ((size_t) solids[j].nr*sizeof(double));
      (*solids[j].convert)(FIRST, SECOND, *temperature, *pressure, e, m, NULL, NULL, NULL, NULL, NULL, NULL);
      (*solids[j].convert)(SECOND, THIRD, *temperature, *pressure, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
      for (i=0, mTot=0.0; i<solids[j].na; i++) {
        mTot += m[i];
	gibbs(*temperature, *pressure, phaseName, &solids[j+1+i].ref, NULL, NULL, &solids[j+1+i].cur);
      }
      
      (*solids[j].gmix) (FIRST, *temperature, *pressure, r, &G, NULL, NULL, NULL);
      (*solids[j].hmix) (FIRST, *temperature, *pressure, r, &H);
      (*solids[j].smix) (FIRST, *temperature, *pressure, r, &S, NULL, NULL);
      (*solids[j].vmix) (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, 
         *temperature, *pressure, r, &V, NULL, NULL, &dVdT, &dVdP, &d2VdT2, &d2VdTdP, &d2VdP2, NULL, NULL);
      (*solids[j].cpmix)(FIRST | SECOND, *temperature, *pressure, r, &Cp, &dCpdT, NULL);

      G       *= mTot;     
      H       *= mTot; 
      S       *= mTot;
      V       *= mTot;
      Cp      *= mTot;
      dCpdT   *= mTot;
      dVdT    *= mTot;
      dVdP    *= mTot;
      d2VdT2  *= mTot;
      d2VdTdP *= mTot;
      d2VdP2  *= mTot;
	  
      for (i=0; i<solids[j].na; i++) {
        G	+= m[i]*(solids[j+1+i].cur).g;
        H	+= m[i]*(solids[j+1+i].cur).h;
        S	+= m[i]*(solids[j+1+i].cur).s;
        V	+= m[i]*(solids[j+1+i].cur).v;
        Cp	+= m[i]*(solids[j+1+i].cur).cp;
        dCpdT	+= m[i]*(solids[j+1+i].cur).dcpdt;
        dVdT	+= m[i]*(solids[j+1+i].cur).dvdt;
        dVdP	+= m[i]*(solids[j+1+i].cur).dvdp;
        d2VdT2  += m[i]*(solids[j+1+i].cur).d2vdt2;
        d2VdTdP += m[i]*(solids[j+1+i].cur).d2vdtdp;
        d2VdP2  += m[i]*(solids[j+1+i].cur).d2vdp2;
      }
      
      free(m);
      free(r);

    }

    phaseProperties[ 0] = G;
    phaseProperties[ 1] = H;
    phaseProperties[ 2] = S;
    phaseProperties[ 3] = V*10.0;
    phaseProperties[ 4] = Cp;
    phaseProperties[ 5] = dCpdT;
    phaseProperties[ 6] = dVdT*10.0;
    phaseProperties[ 7] = dVdP*10.0;
    phaseProperties[ 8] = d2VdT2*10.0;
    phaseProperties[ 9] = d2VdTdP*10.0;
    phaseProperties[10] = d2VdP2*10.0;
	
  }
}

/* ================================================================================== */
/* Input and Output (as above)                  				      */
/* ================================================================================== */

void getMeltsPhaseProperties (char *phaseName, double *temperature, 
			      double *pressure, double *bulkComposition, double *phaseProperties) {

  meltsgetphaseproperties_(phaseName, temperature, pressure, bulkComposition, phaseProperties);

}
