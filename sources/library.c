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

#define XOR(a,b) ((a) ? !(b) : (b))
#define REC   134

/* For SEH this is used to indicate whether the calculation failed. */
int doInterrupt = FALSE;

#ifdef MINGW
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#define MAX_CONSOLE_LINES 5000
BOOL WINAPI windows_console_handler(DWORD dwType);
#endif

#ifdef USESJLJ
#include <signal.h>
#include <setjmp.h>
static void setErrorHandler(void);
static jmp_buf env;
#elif defined(USESEH)
void raise_sigabrt(DWORD dwType);
#endif

static void doBatchFractionation(void);

int calculationMode = MODE__MELTS;
int quad_tol_modifier = 1;

void (*additionalOutput) (char *filename) = NULL;
char *addOutputFileName = NULL;

/* ================================================================================== */
/* ================================================================================== */
/* Private functions to support libMelts                                              */
/* ================================================================================== */
/* ================================================================================== */

static int iAmInitialized = FALSE;

static void initializeLibrary(void) {

  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_xMELTS)) {
    liquid = meltsLiquid;
    solids = meltsSolids;
    nlc    = meltsNlc;
    nls    = meltsNls;
    npc    = meltsNpc;
  } else if ((calculationMode == MODE__MELTSandCO2) || (calculationMode == MODE__MELTSandCO2_H2O)) {
    liquid = meltsFluidLiquid;
    solids = meltsFluidSolids;
    nlc = meltsFluidNlc;
    nls = meltsFluidNls;
    npc = meltsFluidNpc;
  } else if (calculationMode == MODE_pMELTS) {
    liquid = pMeltsLiquid;
    solids = pMeltsSolids;
    nlc    = pMeltsNlc;
    nls    = pMeltsNls;
    npc    = pMeltsNpc;
  }
  InitComputeDataStruct();
  iAmInitialized = TRUE;
}

/* ================================================================================== */
/* ================================================================================== */
/* Public interface for libMelts                                                      */
/* ================================================================================== */
/* ================================================================================== */

/* ================================================================================== */
/* Set calculation mode if not already initialized                                    */
/* ================================================================================== */

void addConsole(void) {
#ifdef MINGW
  int hConHandle;
  intptr_t lStdHandle;
  CONSOLE_SCREEN_BUFFER_INFO coninfo;
  FILE *fp;
  
  AllocConsole();
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
  coninfo.dwSize.Y = MAX_CONSOLE_LINES;
  SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
  // redirect unbuffered STDOUT to the console
  lStdHandle = (intptr_t) GetStdHandle(STD_OUTPUT_HANDLE);
  hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
  fp = _fdopen( hConHandle, "w" );
  *stdout = *fp;
  setvbuf( stdout, NULL, _IONBF, 0 );
  // redirect unbuffered STDERR to the console
  lStdHandle = (intptr_t) GetStdHandle(STD_ERROR_HANDLE);
  hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
  fp = _fdopen( hConHandle, "w" );
  *stderr = *fp;
  setvbuf( stderr, NULL, _IONBF, 0 );

  if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE) windows_console_handler, TRUE)) 
    fprintf(stderr, "...Error in installing Console Handler.\n");

#endif
}

void closeConsole(void) {
#ifdef MINGW
    HWND consoleWnd;
    if ((consoleWnd = GetConsoleWindow()) != NULL) FreeConsole();
#endif
}

int getCalculationMode(void) {
  if (!iAmInitialized) initializeLibrary();
  return calculationMode;
}

int setCalculationMode(int mode) {
  if (!iAmInitialized) {
    calculationMode = mode;
    initializeLibrary();
    return TRUE;
  } else {
    if (silminState != NULL) {
      int i, np;
      for (i=0, np=0; i<npc; i++) if (solids[i].type == PHASE) (silminState->incSolids)[np] = TRUE;
      (silminState->incSolids)[npc] = TRUE;
      silminState->nLiquidCoexist  = 1;
      silminState->fo2Path  = FO2_NONE;
      silminState->fo2Delta = 0.0;

      silminState->fractionateFlu = FALSE;  /* Could be set */
      silminState->fractionateSol = FALSE; 
      silminState->fractionateLiq = FALSE;      
    }
    return FALSE;
  }
}

/* ================================================================================== */
/* Returns oxide names and order for bulk composition vector                          */
/* Input:                                                                             */
/*   nCharInName  - number of characters dimensioned for each name                    */
/*                  i.e. in FORTRAN : CHARACTER*20, where nCharInName is then 20      */
/* Output:                                                                            */
/*   oxideNames   - array of oxide names, ordered as in MELTS                         */
/*                  memory must be allocated by calling FORTRAN program, i.e.         */
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
/* Input and Output (as above except):                                                */
/*   oxidePtr     - array of blank strings, assumed all to be of the same length      */
/*   numberOxides - input lt or equal to amount of allocated storage, output as above */
/* ================================================================================== */

void getMeltsOxideNames(int *failure, char *oxidePtr, int *nCharInName, int *numberOxides) {
  int i, nCh = *nCharInName, nox = *numberOxides;
  char *oxideNames = (char *) malloc(sizeof(char)*nCh*nox);

#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif
    for (i=0; i<nCh*nox; i++) oxidePtr[i] = '\0';
    meltsgetoxidenames_(oxideNames, nCharInName, numberOxides);
    nox = *numberOxides;
    for (i=0; i<nCh*nox; i++) {
      if (oxideNames[i] == '\0') oxidePtr[i] = ' ';
      else oxidePtr[i] = oxideNames[i];
    }
    free(oxideNames);
    *failure = FALSE;
#ifdef USESEH
    *failure = doInterrupt;
#elif defined(USESJLJ)
  }
#endif
}

/* ================================================================================== */
/* Returns oxide mw and order for bulk composition vector                             */
/* Input:                                                                             */
/* Output:                                                                            */
/*   oxideWeights - array of oxide molecular weights, ordered as in MELTS             */
/*                  memory must be allocated by calling FORTRAN program               */
/*   numberOxides - number of oxides in the system                                    */
/* ================================================================================== */

void meltsgetoxideweights_(double *oxideWeights, int *numberOxides) {
  int i;
  if (!iAmInitialized) initializeLibrary();
  for (i=0; i<nc; i++) oxideWeights[i] = bulkSystem[i].mw;
  *numberOxides = nc;
}        

/* ================================================================================== */
/* Input and Output (as above except):                                                */
/*   numberOxides - input lt or equal to amount of allocated storage, output as above */
/* ================================================================================== */

void getMeltsOxideWeights(int *failure, double *oxideWeights, int *numberOxides) {

#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif
    meltsgetoxideweights_(oxideWeights, numberOxides);
    *failure = FALSE;
#ifdef USESEH
    *failure = doInterrupt;
#elif defined(USESJLJ)
  }
#endif
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
  
#ifdef TESTDYNAMICLIB  
  strncpy(phaseNames + np*sizeof(char)*nCh, "bulk", nCh);   phaseIndices[np] = -10; np++; 
  strncpy(phaseNames + np*sizeof(char)*nCh, "liquid", nCh); phaseIndices[np] = 0; np++;
#else
  strncpy(phaseNames + np*sizeof(char)*nCh, "system", nCh); phaseIndices[np] = 1; np++; 
  strncpy(phaseNames + np*sizeof(char)*nCh, "liquid", nCh); phaseIndices[np] = 2; np++;
#endif 

  for (i=0; i<npc; i++) if (solids[i].type == PHASE) { 
      strncpy(phaseNames + np*sizeof(char)*nCh, solids[i].label, nCh); 
      phaseIndices[np] = 10*i + 10;
      np++; 
  }
  *numberPhases = np;
}        

/* ================================================================================== */
/* Input and Output (as above except):                                                */
/*   phasePtr     - array of blank strings, assumed all to be of the same length      */
/*   numberPhases - input lt or equal to amount of allocated storage, output as above */
/* ================================================================================== */

void getMeltsPhaseNames(int *failure, char *phasePtr, int *nCharInName, int *numberPhases, int phaseIndices[]) {
  int i, nCh = *nCharInName, np = *numberPhases;
  char *phaseNames = (char *) malloc((size_t) nCh*np*sizeof(char));
  
#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif
    for (i=0; i<nCh*np; i++) phasePtr[i] = '\0';    
    meltsgetphasenames_(phaseNames, nCharInName, numberPhases, phaseIndices);
    np = *numberPhases;
    for (i=0; i<nCh*np; i++) {
      if (phaseNames[i] == '\0') phasePtr[i] = ' ';
      else phasePtr[i] = phaseNames[i];
    }
    free(phaseNames);
    *failure = FALSE;
#ifdef USESEH
    *failure = doInterrupt;
#elif defined(USESJLJ)
  }
#endif
}

/* ================================================================================== */
/* Returns end-member formulae and order for output properties vector                 */
/* Input:                                                                             */
/*   phaseName       - string as returned from meltsGetPhaseNames                     */
/*   nCharInName     - number of characters dimensioned for each name                 */
/*                     i.e. in FORTRAN : CHARACTER*20, where nCharInName is then 20   */
/* Output:                                                                            */
/*   endMemberNames   - array of end-member formulae, ordered as in MELTS             */
/*                      memory must be allocated by calling FORTRAN program, i.e.     */
/*                      CHARACTER*20 phaseNames(25)                                   */
/*   numberEndMembers - number of unique end members for phase                        */
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

static int np;
static PhaseList key;

static void initializePhaseList (void) {
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

void meltsgetweightsandformulas_(char *phaseName, double *endMemberWeights, char endMemberNames[], int *nCharInName, int *numberEndMembers) {
  int nCh = *nCharInName;
  PhaseList *res;

  if (!iAmInitialized) initializeLibrary();

  if (phaseList == NULL) {
    initializePhaseList();
  }

  strcpy(key.name, phaseName);
  res = bsearch(&key, phaseList, (size_t) np, sizeof(struct _phaseList), comparePhases);

  if (res == NULL) { numberEndMembers = 0; return; }
  else { 
    int i, j = res->index;
    if (j < 0) { /* liquid */
#ifdef TESTDYNAMICLIB
      for (i=0; i<nls; i++) {
        for(j=0, endMemberWeights[i] = 0.0; j<nc; j++)
          endMemberWeights[i] += (bulkSystem[j].oxToLiq)[i]*bulkSystem[j].mw;
        strncpy(endMemberNames + i*sizeof(char)*nCh,liquid[i].label, nCh);
      }
      (*numberEndMembers) = nls;
#else
      for (i=0; i<nlc; i++) {
        for(j=0, endMemberWeights[i] = 0.0; j<nc; j++)
          endMemberWeights[i] += (bulkSystem[j].oxToLiq)[i]*bulkSystem[j].mw;
        strncpy(endMemberNames + i*sizeof(char)*nCh,liquid[i].label, nCh);0
      }
      (*numberEndMembers) = nlc;
#endif
    } else if (solids[j].na == 1) {
      endMemberWeights[0] = solids[j].mw;
      strncpy(endMemberNames, solids[j].formula, nCh); 
      (*numberEndMembers) = 1;
    }
    else {
      for (i=0; i<solids[j].na; i++) {
        endMemberWeights[i] = solids[j+1+i].mw;
        strncpy(endMemberNames + i*sizeof(char)*nCh,solids[j+1+i].formula, nCh);
      }
      (*numberEndMembers) = solids[j].na;
    }
  }

}        

/* ================================================================================== */
/* Input and Output (as above except):                                                */
/*   phasePtr     - array of blank strings, assumed all to be of the same length      */
/*   numberPhases - input lt or equal to amount of allocated storage, output as above */
/* ================================================================================== */

void getMeltsWeightsAndFormulas(int *failure, char *phaseName, double *endMemberWeights, char *formulaPtr, int *nCharInName, int *numberEndMembers) {
  int i, nCh = *nCharInName, np = *numberEndMembers;
  char *endMemberNames = (char *) malloc((size_t) nCh*np*sizeof(char));
  
#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif
    for (i=0; i<nCh*np; i++) formulaPtr[i] = '\0';    
    meltsgetweightsandformulas_(phaseName, endMemberWeights, endMemberNames, nCharInName, numberEndMembers);
    np = *numberEndMembers;
    for (i=0; i<nCh*np; i++) {
      if (endMemberNames[i] == '\0') formulaPtr[i] = ' ';
      else formulaPtr[i] = endMemberNames[i];
    }
    free(endMemberNames);
    if (np > 0) *failure = FALSE;
#ifdef USESEH
    *failure = (*failure) ? (*failure) : doInterrupt;  
#elif defined(USESJLJ)
  }
#endif
}

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

/* ================================================================================== */
/* Model: Giordano D, Russell JK, Dingwell DB (2008)                                  */
/* Viscosity of magmatic liquids: A model. EPSL 271, 123-134                          */
/* ================================================================================== */

static double viscosityFromGRD(double t, double *oxValues) {
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

/* ================================================================================== */
/* Model (as in MELTS GUI): Shaw (1972) AJS November 1972 vol. 272 no. 9 870-893      */
/* Viscosities of Magmatic Silicate Liquids: An Empirical Method of Prediction        */
/* ================================================================================== */

static double viscosityFromShaw(double t, double *oxValues) {

  double coeff[nlc], factor[nlc], x[nlc], sum, viscosity;
  int nSiO2 = -1, i, j;

  struct _shawModel {
    char   *oxide;
    double coeff;
    double factor;
  } shawModel[] = {
    { "TiO2",	4.5, 1.0 }, { "Al2O3",  6.7, 2.0 }, 
    { "Fe2O3",  3.4, 2.0 }, { "FeO",	3.4, 1.0 }, 
    { "MgO",	3.4, 1.0 }, { "CaO",	4.5, 1.0 },
    { "Na2O",	2.8, 1.0 }, { "K2O",	2.8, 1.0 }, 
    { "H2O",	2.0, 1.0 }
  };
  const int nShaw = (sizeof shawModel / sizeof(struct _shawModel));

  for (j=0; j<nlc; j++) { coeff[j] = 0.0; factor[j] = 0.0; }
  for (i=0; i<nShaw; i++) {
    for (j=0; j<nlc; j++) if (strcmp(shawModel[i].oxide, bulkSystem[j].label) == 0) {
      coeff[j]  = shawModel[i].coeff; 
      factor[j] = shawModel[i].factor;
      break; 
    }
  } 
  for (i=0; i<nlc; i++) if (strcmp("SiO2", bulkSystem[i].label) == 0) { nSiO2 = i; break; } 

  if (nSiO2 == -1) { viscosity = 0.0; return viscosity; }

  /* m[0] --> m[NA-1] is an array of mole fractions of liquid components      */
  /* convert m[] -> x[] : mole fractions of liquid comp -> moles of oxides    */
  /* Convert to the Shaw mole fractions                                       */
  for (i=0, sum=0.0; i<nlc; i++) {
    x[i] =  oxValues[i]/bulkSystem[i].mw;
    if (factor[i] > 0.0) x[i] *= factor[i];
    sum += x[i];
  }
  for (i=0; i<nlc; i++) x[i] /= (sum != 0.0) ? sum : 1.0;

  for (i=0, viscosity=0.0; i<nlc; i++) viscosity += coeff[i]*x[nSiO2]*x[i];
  viscosity /= (x[nSiO2] < 1.0) ? 1.0 - x[nSiO2] : 1.0; 
  viscosity  = (viscosity)*(10000.0/t - 1.50)  - 6.40; 
  viscosity /= log(10.0);

  return viscosity;
}

/* ================================================================================== */
/* Input and Output (as above)                                                        */
/* ================================================================================== */

void getMeltsViscosity(int *failure, char *model, double *temperature, double *bulkComposition, double *viscosity) {

#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif  
    if (!strncmp(model, "GRD", MAX(strlen(model), 3)))
      (*viscosity) = viscosityFromGRD(*temperature, bulkComposition);
    else
      (*viscosity) = viscosityFromShaw(*temperature, bulkComposition);
    if (*viscosity != 0.0) *failure = FALSE;
#ifdef USESEH
    *failure = (*failure) ? (*failure) : doInterrupt;
#elif defined(USESJLJ)
  }
#endif  
}

/* ================================================================================== */
/* MELTS processing call                                                              */
/* Input:                                                                             */
/*   nodeIndex       - Index number of node (must be unique). First time a given node */
/*                     is used the system is set to the input conditions and a single */
/*                     (mode = 1) calculation performed. Subsequent calls pickup from */
/*                     the last successful call and may be isothermal or isenthalpic. */
/*                     Isentropic calculations can be substituted for isenthalpic.    */
/*   mode            - for continuation call (i.e. node has already been initialised) */
/*                     NOTE: THE INDEX FOR ISENTHALPIC MODE HAS CHANGED (from 0 to 2) */
/*                     = 0, initial temperature is input and liquidus is calculated   */
/*                     = 1, temperature is input in place of enthalpy                 */
/*                     = 2, isenthalpic, temperature is output (unless enthalpy = 0)  */
/*                     = 3, isentropic, temperature is output (unless entropy = 0)    */
/*                     = 4, isochoric, pressure is output (unless volume = 0)         */ 
/*   bulkComposition - Bulk composition in grams of oxides                            */ 
/*   nCharInName     - number of characters dimensioned for each name                 */
/*                     i.e. in FORTRAN : CHARACTER*20, where nCharInName is then 20   */
/* Input and Output                                                                   */
/*   enthalpy        - Input: Total enthalpy in J of the node, if mode = 2            */
/*                     Output: Computed system enthalpy if mode = 1                   */
/*                     Output: Computed system enthalpy if mode = 2 + Input value = 0 */
/*   entropy         - Input: Total entropy in J/K of the node, if mode = 3           */
/*                     Output: Computed system entropy if mode = 3 + Input value = 0  */
/*   volume          - Input: Total volume in cc of the node, if mode = 4             */
/*                     Output: Computed system volume if mode = 4 + Input value = 0   */
/*   temperature     - Input: Temperature of the node (K), if mode = 1                */
/*                     Output: Computed temperature if mode = 2 or 3                  */
/*   pressure        - Input: Pressure in bars of the node                            */
/*                     Output: Computed pressure if mode = 4                          */
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

void meltsprocess_(int *nodeIndex, int *mode, double *pressure, double *bulkComposition, 
         double *enthalpy, double *temperature, 
           char phaseNames[], int *nCharInName, int *numberPhases, int *iterations, int *status, 
           double *phaseProperties, int phaseIndices[]) {
  int update = FALSE;
  int nCh = *nCharInName, output = 0;
  int fractionateSol, fractionateFlu, fractionateLiq; 
  double *entropy = enthalpy, *volume = enthalpy;
  if (!iAmInitialized) initializeLibrary();

  /* Set output = 0 for properties to return after equilibration (like alphaMELTS menu option 3) */
  /* Set output = 1 for properties after equilibration before fractionation (like menu option 4) */
  /* Set output = 2 for properties after any fractionation */
  
  /* For backwards compatibility if not coming from PyMELTS or Matlab: */
  /* 'iterations' is unused but is still set to -1 after return from silmin() */
#ifdef TESTDYNAMICLIB
  output = *iterations;
#endif
  
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
  } else {
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
    for (i=0; i<nlc; i++) {
      for (j=0; j<nc; j++) {
        (silminState->liquidComp)[0][i] += changeBC[j]*(bulkSystem[j].oxToLiq)[i];
        silminState->oxygen += changeBC[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
      }
    }
  } else {
    int i, j;
    for (i=0, silminState->liquidMass=0.0; i<nc; i++) {
      (silminState->bulkComp)[i] = bulkComposition[i]/bulkSystem[i].mw;
      silminState->liquidMass += bulkComposition[i];
    }
    for (i=0; i<nlc; i++) {
      for ((silminState->liquidComp)[0][i]=0.0, silminState->oxygen=0.0, j=0; j<nc; j++) {
        (silminState->liquidComp)[0][i] += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i];
        silminState->oxygen += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
      }
    }
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

  /* For backwards compatibility if not coming from PyMELTS or Matlab: */
  /* Previously mode = 0 was isenthalpic, rather than 'find liquidus', */
  /* but this should only have been invoked with non-zero enthalpy.    */
#ifndef TESTDYNAMICLIB
  if (*mode == 0 && *enthalpy != 0.0) *mode = 2;
#endif
  
  switch (*mode) {
  case 2:
    if (*enthalpy != 0.0) {
      silminState->isenthalpic = TRUE;  
      silminState->dspHstop    = *enthalpy; 
      silminState->dspHinc     = *enthalpy - silminState->refEnthalpy; 
      silminState->dspTstart   = 0.0;
      silminState->dspTstop    = 0.0;
    }
    else silminState->refEnthalpy = 0.0;
    break;
  case 3:
    if (*entropy != 0.0) {
      silminState->isentropic = TRUE;  
      silminState->dspSstop    = *entropy; 
      silminState->dspSinc     = *entropy - silminState->refEntropy;
      silminState->dspTstart   = 0.0;
      silminState->dspTstop    = 0.0;
    }
    else silminState->refEntropy = 0.0;
    break;
  case 4:
    if (*volume != 0.0) {
      silminState->isochoric   = TRUE;
      silminState->dspVstop    = *volume/10.0;
      silminState->dspVinc     = *volume/10.0 - silminState->refVolume;
      silminState->dspPstart   = 0.0;
      silminState->dspPstop    = 0.0;
    }
    else silminState->refVolume = 0.0;
    break;
  default: /* isothermal, isobaric mode */
    silminState->refEntropy  = 0.0;
    silminState->refEnthalpy = 0.0;
    silminState->refVolume   = 0.0;
    break;
  }

  if ((silminState->fractionateSol || silminState->fractionateFlu) && silminState->fracSComp == NULL) {
    silminState->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
    silminState->nFracCoexist = (int *) calloc((unsigned) npc, sizeof(int));
  }
  if (silminState->fractionateLiq && silminState->fracLComp == NULL) {
    silminState->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
  }

  fractionateFlu = silminState->fractionateFlu;
  fractionateSol = silminState->fractionateSol;
  fractionateLiq = silminState->fractionateLiq;
  
  if (output < 2) {
    silminState->fractionateFlu = FALSE;
    silminState->fractionateSol = FALSE; 
    silminState->fractionateLiq = FALSE;
  }
  
  if (*mode)
    while(!silmin());
  else
    while(!liquidus());
  
#ifdef TESTDYNAMICLIB
  strncpy(phaseNames, "bulk", nCh);
  *numberPhases = 1;
  phaseIndices[0] = -10;
#else
  strncpy(phaseNames, "system", nCh);
  *numberPhases = 1;
  phaseIndices[0] = 1;

#endif
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
    case LIQUIDUS_SUCCESS:
      *status = 500;
      break;
    case LIQUIDUS_MAX_T:
      *status = 501;
      break;
    case LIQUIDUS_MIN_T:
      *status = 502;
      break;
    case LIQUIDUS_TIME:
      *status = 503;
      break;
    case LIQUIDUS_MULTIPLE:
      *status = 504;
      break;
    default:
      *status = 1000;
      break;
  }

  { /* output block */
    double gLiq = 0.0, hLiq = 0.0, sLiq = 0.0, vLiq = 0.0, cpLiq = 0.0, dcpdtLiq = 0.0, 
           dvdtLiq = 0.0, dvdpLiq = 0.0, d2vdt2Liq = 0.0, d2vdtdpLiq = 0.0, d2vdp2Liq = 0.0;
    double totalG=0.0, totalH=0.0, totalS=0.0, totalV=0.0, totalCp=0.0, totaldCpdT=0.0, 
           totaldVdT=0.0, totaldVdP=0.0, totald2VdT2=0.0, totald2VdTdP=0.0, totald2VdP2=0.0, totalGrams, totalMoles;
    static double *m, *r, *oxVal;
    int i, j;
    int columnLength = 11 + nc + 3; /* G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2, + nc oxides + volume fraction, density, viscosity */
    
    if (m == NULL)       m = (double *) malloc((size_t)      nc*sizeof(double));
    if (r == NULL)       r = (double *) malloc((size_t) (nlc-1)*sizeof(double));
    if (oxVal == NULL) oxVal = (double *) malloc((size_t)      nc*sizeof(double));
    
    /* liquid is the second "phase" reported */
    if (silminState->liquidMass != 0.0) {
      int nl;
      double gramTot=0.0, mTot = 0.0;
      strncpy(phaseNames + sizeof(char)*nCh, "liquid", nCh);
#ifdef TESTDYNAMICLIB
      /* multiple liquids not actually allowed yet... */
      *numberPhases = silminState->nLiquidCoexist + 1;
      phaseIndices[1] = 0; // set within nl loop
#else
      *numberPhases = 2;
      phaseIndices[1] = 2;      
#endif

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
        V       *= moles; 
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
          gramTot += oxVal[i];
        }
        mTot += moles;

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
#ifndef TESTDYNAMICLIB
      phaseProperties[columnLength+11+nc  ] = vLiq*10.0;
      phaseProperties[columnLength+11+nc+1] = (vLiq != 0.0) ? 100.0*gramTot/vLiq : 0.0;
      phaseProperties[columnLength+11+nc+2] = viscosityFromGRD(silminState->T, oxVal);
#else
      phaseProperties[columnLength+11+nc  ] = (mTot != 0.0) ? gramTot/mTot : 0.0;
      phaseProperties[columnLength+11+nc+1] = (vLiq != 0.0) ? 100.0*gramTot/vLiq : 0.0;
      //phaseProperties[columnLength+11+nc+2] = gramTot;
      phaseProperties[columnLength+11+nc+2] = viscosityFromShaw(silminState->T, oxVal);
#endif
    } /* end liquid block */

    /* begin solid block */
    for (j=0; j<npc; j++) {
      int ns;
      for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
        double G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2, gramTot=0.0, mTot = 0.0;
     
        if (solids[j].na == 1) {
          G       = (silminState->solidComp)[j][ns]*(solids[j].cur).g;
          H       = (silminState->solidComp)[j][ns]*(solids[j].cur).h;
          S       = (silminState->solidComp)[j][ns]*(solids[j].cur).s;
          V       = (silminState->solidComp)[j][ns]*(solids[j].cur).v;
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
            gramTot += oxVal[i];
          }
          mTot = (silminState->solidComp)[j][ns];
      
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
            H       += m[i]*(solids[j+1+i].cur).h;
            S       += m[i]*(solids[j+1+i].cur).s;
            V       += m[i]*(solids[j+1+i].cur).v;
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
            gramTot += oxVal[i];
          }
          for (i=0; i<solids[j].na; i++) mTot += m[i];
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
#ifndef TESTDYNAMICLIB
        phaseProperties[(*numberPhases)*columnLength+11+nc  ] = V*10.0;
        phaseProperties[(*numberPhases)*columnLength+11+nc+1] = (V != 0.0) ? 100.0*gramTot/V : 0.0;
        phaseProperties[(*numberPhases)*columnLength+11+nc+2] = 0.0;
#else
        phaseProperties[(*numberPhases)*columnLength+11+nc  ] = (mTot != 0.0) ? gramTot/mTot : 0.0;
        phaseProperties[(*numberPhases)*columnLength+11+nc+1] = (V != 0.0) ? 100.0*gramTot/V : 0.0;
        phaseProperties[(*numberPhases)*columnLength+11+nc+2] = gramTot;
#endif
    
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
    for (i=0, totalGrams=0.0, totalMoles = 0.0; i<nc; i++) {
      phaseProperties[11+i] = (silminState->bulkComp)[i]*bulkSystem[i].mw;
      totalGrams += phaseProperties[11+i];
      totalMoles += (silminState->bulkComp)[i];
    }
#ifndef TESTDYNAMICLIB
    phaseProperties[11+nc  ] = 1.0;
    phaseProperties[11+nc+1] = ((vLiq+totalV) != 0.0) ? 100.0*totalGrams/(vLiq+totalV) : 0.0;
    phaseProperties[11+nc+2] = 0.0;
#else
    phaseProperties[11+nc  ] = (totalMoles != 0.0) ? totalGrams/totalMoles : 0.0;
    phaseProperties[11+nc+1] = ((vLiq+totalV) != 0.0) ? 100.0*totalGrams/(vLiq+totalV) : 0.0;
    //phaseProperties[11+nc+2] = totalGrams;
    phaseProperties[11+nc+2] = silminState->fo2;
#endif

#ifndef TESTDYNAMICLIB
    if ((vLiq+totalV) != 0.0) for (i=1; i<=(*numberPhases); i++) phaseProperties[i*columnLength+11+nc] /= 10.0*(vLiq+totalV);
#endif

    if (output < 2) {
      silminState->fractionateFlu = fractionateFlu;
      silminState->fractionateSol = fractionateSol;
      silminState->fractionateLiq = fractionateLiq;
    }
    if (output == 1) {
      doBatchFractionation();
    }
      
    /* final conditions */
    switch (*mode) {     
    case 0:
      *enthalpy    = 0.0;
      break;
    case 1:
      *enthalpy    = hLiq+totalH;
      break;
    case 2:
      silminState->refEnthalpy = hLiq+totalH;
      *enthalpy    = silminState->refEnthalpy;
      break;
    case 3:
      silminState->refEntropy = sLiq+totalS;
      *entropy     = silminState->refEntropy;
      break;
    case 4:
      silminState->refVolume = vLiq+totalV;
      *volume      = 10.0*silminState->refVolume;
      break;
    default:
      break;
    }
      
    *temperature = silminState->T;
    *pressure    = silminState->P;

    for (i=0; i<nc; i++) {
      bulkComposition[i] = (silminState->bulkComp)[i]*bulkSystem[i].mw;
    }
    
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
    case 500:
      strncpy(errorString, "Successfully found liquidus.  No errors detected.", nCh);
      break;
    case 501:
      strncpy(errorString, "Liquidus not found.  Maximum temperature reached.", nCh);
      break;
    case 502:
      strncpy(errorString, "Liquidus not found.  Minimum temperature reached.", nCh);
      break;
    case 503:
      strncpy(errorString, "Liquidus not found.  Time limit exceeded.", nCh);
      break;
    case 504:
      strncpy(errorString, "Liquidus not found.  Solids / multiple liquids present.", nCh);
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
/*   phasePtr      - array of blank strings, assumed all to be of the same length      */
/*   numberPhases  - input lt or equal to amount of allocated storage, output as above */
/*   nCharInString - number of characters dimensioned for error string                 */
/*   propertiesPtr - this is double[][33], instead of double*, and rows and columns    */
/*                   are switched when calling from C rather than Fortran              */
/* =================================================================================== */

void driveMeltsProcess(int *failure, int *mode, double *pressure, double *bulkComposition,
               double *enthalpy, double *temperature,
               char *phasePtr, int *nCharInName, int *numberPhases, int *output, 
               char *errorString, int *nCharInString, double *phaseProperties, int phaseIndices[]) {
  int i, nCh = *nCharInName, np = *numberPhases, status, nodeIndex = 1, iterations = 0;
  char *phaseNames = (char *) malloc((size_t) nCh*np);

#ifdef TESTDYNAMICLIB
  iterations = *output;
#endif

#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif
    for (i=0; i<nCh*np; i++) phasePtr[i] = '\0';    
    meltsprocess_(&nodeIndex, mode, pressure, bulkComposition, enthalpy, temperature,
		  phaseNames, nCharInName, numberPhases, &iterations, &status, phaseProperties, phaseIndices);
    np = *numberPhases;
    for (i=0; i<nCh*np; i++) {
      if (phaseNames[i] == '\0') phasePtr[i] = ' ';
      else phasePtr[i] = phaseNames[i];
    }

    meltsgeterrorstring_(&status, errorString, nCharInString);
    free(phaseNames);
    if (XOR(status && (status == 500), *mode)) *failure = FALSE;
#ifdef USESEH
    *failure = (*failure) ? (*failure) : doInterrupt;  
#elif defined(USESJLJ)
  }
#endif
}

/* ================================================================================== */
/* Adjust settings for a given node (if node does not exist it will be created)       */
/* Input:                                                                             */
/*   nodeIndex       - Index number of node (must be unique).                         */
/*   property        - a melts file like string to set fO2 or toggle fractionation:   */
/*                     = 'log fo2 path: value', value is fmq, qfm, coh, nno, iw or hm */
/*                     = 'log fo2 delta: value', value is an integer or real          */
/*                     = 'mode: fractionate phase' phase is solids, liquids or fluids */
/* ================================================================================== */

void meltssetsystemproperty_(int *nodeIndex, char *property) {
  int i, len;
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

  /* -> log fo2 path record */
  if (!strncmp(line, "log fo2 path: ",          MIN(len,14))) {
    if      (!strncmp(&line[14], "none",  MIN((len-14), 4))) silminState->fo2Path  = FO2_NONE;
    else if (!strncmp(&line[14], "fmq",   MIN((len-14), 3))) silminState->fo2Path  = FO2_QFM;
    else if (!strncmp(&line[14], "coh",   MIN((len-14), 3))) silminState->fo2Path  = FO2_COH;
    else if (!strncmp(&line[14], "nno",   MIN((len-14), 3))) silminState->fo2Path  = FO2_NNO;
    else if (!strncmp(&line[14], "iw",    MIN((len-14), 2))) silminState->fo2Path  = FO2_IW;
    else if (!strncmp(&line[14], "hm",    MIN((len-14), 2))) silminState->fo2Path  = FO2_HM;
    else if (!strncmp(&line[14], "+3fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_P3;
    else if (!strncmp(&line[14], "+2fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_P2;
    else if (!strncmp(&line[14], "+1fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_P1;
    else if (!strncmp(&line[14], "-1fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M1;
    else if (!strncmp(&line[14], "-2fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M2;
    else if (!strncmp(&line[14], "-3fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M3;
    else if (!strncmp(&line[14], "-4fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M4;
    else if (!strncmp(&line[14], "-5fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M5;
    else if (!strncmp(&line[14], "-6fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M6;
    else if (!strncmp(&line[14], "-7fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M7;
    else if (!strncmp(&line[14], "-8fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M8;
    else if (!strncmp(&line[14], "-9fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M9;
    else if (!strncmp(&line[14], "+0.5fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_P0_5;
    else if (!strncmp(&line[14], "+1.5fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_P1_5;

    /* -> suppress a solid phase record */
  } else if (!strncmp(line, "suppress: ",              MIN(len,10))) {
    if (!strncmp(&line[10], "none", MIN(len-10, 4))) {
      int np;
      for (i=0, np=0; i<npc; i++) if (solids[i].type == PHASE) { (silminState->incSolids)[np] = TRUE; np++; }
      (silminState->incSolids)[npc] = TRUE;
    }
    else if (!strncmp(&line[10], "liquid", MIN(len-10, 6))) {
      (silminState->incSolids)[npc] = FALSE;
    }
    else {
      int j;
      for (i=0, j=0; i<npc; i++) {
        if (solids[i].type == PHASE) {
          int phaseStrLen = (int) strlen(solids[i].label); 
          if (((len-10-phaseStrLen)  == 0) && !strncmp(&line[10], solids[i].label, phaseStrLen)) {
            if ( solids[i].nr == 0 || (solids[i].nr > 0 && solids[i].convert != NULL)) {
              silminState->incSolids[j] = FALSE;
            }
            break;
          }
        j++;
        }
      }
    }

    /* -> mode record */
  } else if (!strncmp(line, "mode: ",                   MIN(len, 6))) {
    /* Multiple liquids are not allowed here yet, and constraints are added separately */
    if      (!strncmp(&line[6],  "fractionate solids",  MIN((len-6), 18))) silminState->fractionateSol = TRUE;
    else if (!strncmp(&line[6],  "fractionate liquids", MIN((len-6), 19))) silminState->fractionateLiq = TRUE;
    else if (!strncmp(&line[6],  "fractionate fluids",  MIN((len-6), 18))) silminState->fractionateFlu = TRUE;
    /* Was previously 'mode: batch'... */
    else if (!strncmp(&line[10],  "fractionate none",  MIN((len-10), 18))) {
      silminState->fractionateSol = FALSE; silminState->fractionateLiq = FALSE; silminState->fractionateFlu = FALSE;
    }
    /*else if (!strncmp(&line[6],  "multiple liquids",    MIN((len-6), 16))) silminState->multipleLiqs   = TRUE;*/
  }
}

/* ================================================================================== */
/* Input (as above except):                                                           */
/*   properties      - array of strings one for each property to be set               */
/*   numberStrings   - number of strings                                              */
/* ================================================================================== */

void setMeltsSystemProperties(int *failure, char *strings, int *nCharInString, int *numberStrings) {
  int i, j, nodeIndex = 1, nCh = *nCharInString, np = *numberStrings;
  char *properties = (char *) malloc((size_t) nCh);

#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif
    for (i=0; i<np; i++) {
      properties[0] = strings[i*nCh];
      for (j=1; j<nCh; j++) {
        if ((strings[i*nCh+j] == ' ') && (strings[i*nCh+j-1] == ' ')) {
          /* Leave no spaces on end */
          properties[j-1] = '\0';
          break;
        }
        else properties[j] = strings[i*nCh+j];
      }    
      meltssetsystemproperty_(&nodeIndex, properties);
    }
    free(properties);
    *failure = FALSE;
#ifdef USESEH
    *failure = doInterrupt;
#elif defined(USESJLJ)
  }
#endif
}

/* ================================================================================== */
/* Retrieves properties of solid and liquid phases                                    */
/* Input:                                                                             */
/*   phaseName       - string as returned from meltsGetPhaseNames                     */
/*   temperature     - Temperature in Kelvins of the node                             */
/*   pressure        - Pressure in bars of the node                                   */
/*   bulkComposition - Bulk composition of the phase in grams of oxides               */ 
/* Output:                                                                            */
/*   phaseProperties - 1-d array, properties in the order                             */
/*                     G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2     */
/* ================================================================================== */

void meltsgetphaseproperties_(char *phaseName, double *temperature, 
         double *pressure, double *bulkComposition, double *phaseProperties) {
  PhaseList *res;

  if (!iAmInitialized) initializeLibrary();
  
  if (phaseList == NULL) {
    initializePhaseList();
  }

  strcpy(key.name, phaseName);
  res = bsearch(&key, phaseList, (size_t) np, sizeof(struct _phaseList), comparePhases);
  
  if (res == NULL) { phaseProperties = NULL; return; }
  else { 
    int i, j = res->index;
    double G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2, totalGrams, totalMoles;
    
    if (j < 0) { /* liquid */
      double *m, *r, mTot, *mu;
      int k;
      m = (double *) calloc((size_t) nlc,    sizeof(double));
      r = (double *) malloc((size_t) (nlc-1)*sizeof(double));
      for (k=0; k<nc; k++) for (i=0; i<nlc; i++) m[i] += (bulkSystem[k].oxToLiq)[i]*bulkComposition[k]/bulkSystem[k].mw;
      mu = (double *) calloc((size_t) nlc, sizeof(double));

      if ((silminState != NULL) && (silminState->fo2Path != FO2_NONE)) {
        silminState->fo2 = getlog10fo2(*temperature, *pressure, silminState->fo2Path);
        conLiq(FIRST | SEVENTH, FIRST, *temperature, *pressure, m, NULL, NULL, NULL, NULL, NULL, &(silminState->fo2));
      }
      conLiq(SECOND, THIRD, *temperature, *pressure, NULL, m, r, NULL, NULL, NULL, NULL);

      gmixLiq (FIRST, *temperature, *pressure, r, &G, NULL, NULL);
      hmixLiq (FIRST, *temperature, *pressure, r, &H, NULL);
      smixLiq (FIRST, *temperature, *pressure, r, &S, NULL, NULL, NULL);
      vmixLiq (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, 
        *temperature, *pressure, r, &V, NULL, NULL, &dVdT, &dVdP, &d2VdT2, &d2VdTdP, &d2VdP2, NULL, NULL, NULL);
      cpmixLiq(FIRST | SECOND, *temperature, *pressure, r, &Cp, &dCpdT, NULL);
      actLiq(SECOND, *temperature, *pressure, r, NULL, mu, NULL, NULL);

      for (i=0, mTot=0.0; i<nlc; i++) {
        mTot +=  m[i];
        gibbs(*temperature, *pressure, (char *) liquid[i].label, &liquid[i].ref, &liquid[i].liq, &liquid[i].fus, &liquid[i].cur);
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
        G       += m[i]*(liquid[i].cur).g;
        H       += m[i]*(liquid[i].cur).h;
        S       += m[i]*(liquid[i].cur).s;
        V       += m[i]*(liquid[i].cur).v;
        Cp      += m[i]*(liquid[i].cur).cp;
        dCpdT   += m[i]*(liquid[i].cur).dcpdt;
        dVdT    += m[i]*(liquid[i].cur).dvdt;
        dVdP    += m[i]*(liquid[i].cur).dvdp;
        d2VdT2  += m[i]*(liquid[i].cur).d2vdt2;
        d2VdTdP += m[i]*(liquid[i].cur).d2vdtdp;
        d2VdP2  += m[i]*(liquid[i].cur).d2vdp2;
#ifndef TESTDYNAMICLIB
        phaseProperties[11+i] = mu[i] +  (liquid[i].cur).g;
#endif
      }

#ifdef TESTDYNAMICLIB
      for (i=0; i<nc; i++) {
        phaseProperties[11+i] = 0.0;
        for (j=0; j<nlc; j++) phaseProperties[11+i] += (liquid[j].liqToOx)[i]*m[j]*bulkSystem[i].mw;
      }
      totalMoles = mTot;
#endif

      free(m);
      free(r);
      free(mu);

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

#ifdef TESTDYNAMICLIB
      for (i=0; i<nc; i++) {
        phaseProperties[11+i] = (solids[j].solToOx)[i]*bulkSystem[i].mw*factor;
      }      
      totalMoles = factor;
#endif

    } else {
      double e[106], *m, *r, mTot, *mu; 
      int k;
      for (i=0; i<106; i++) e[i] = 0.0;
      for (i=0; i<nc; i++) {
        double mOx = bulkComposition[i]/bulkSystem[i].mw;
        for (k=0; k<106; k++) e[k] += mOx*(bulkSystem[i].oxToElm)[k];
      }
      m = (double *) malloc ((size_t) solids[j].na*sizeof(double));
      r = (double *) malloc ((size_t) solids[j].nr*sizeof(double));

      if (!strncmp(solids[j].label,"clinopyroxene", MIN((int) strlen(solids[j].label), 13)) || 
        !strncmp(solids[j].label,"orthopyroxene", MIN((int) strlen(solids[j].label), 13))) {
        // use input Fe2O3 for Opx/Cpx as entered (see marc.c)
        double sumcat, sumchg, fe2, fe3;
        static const int Na = 11;
        static const int Mg = 12;
        static const int Al = 13;
        static const int Si = 14;
        static const int Ca = 20;
        static const int Ti = 22;
        static const int Cr = 24;
        static const int Mn = 25;
        static const int Fe = 26;

        /* Sum the cations and correct the analysis for silica deficiency */
        sumcat  = e[Na] +     e[Mg] +     e[Al] +     e[Si] +     e[Ca] +     e[Ti] +     e[Cr] +     e[Mn] + e[Fe];
        sumchg  = e[Na] + 2.0*e[Mg] + 3.0*e[Al] + 4.0*e[Si] + 2.0*e[Ca] + 4.0*e[Ti] + 3.0*e[Cr] + 2.0*e[Mn];

        /* Compute the ferric/ferrous ratio */
        fe3 = 3.0*sumcat - sumchg - 2.0*e[Fe];
        fe2 = e[Fe] - fe3;
        if (fe3 < 0.0) { fe3 = 0.0; fe2 = e[Fe]; }
        if (fe2 < 0.0) { fe2 = 0.0; fe3 = e[Fe]; }
          
        /* Assign moles of endmembers */
        m[0] = -fe3/2.0 - fe2 - e[Mn] - e[Al]/2.0 - e[Cr]/2.0 + e[Ca] + e[Na]/2.0 - e[Ti];
        m[1] =  fe3/4.0 + fe2/2.0 + e[Mn]/2.0 + e[Al]/4.0 + e[Cr]/4.0 - e[Ca]/2.0 + e[Mg]/2.0 - e[Na]/4.0;
        m[2] =  fe2 + e[Mn];
        m[3] = -fe3/2.0 + e[Al]/2.0 + e[Cr]/2.0 - e[Na]/2.0 + e[Ti];
        m[4] =  fe3/2.0 - e[Al]/2.0 - e[Cr]/2.0 + e[Na]/2.0 + e[Ti];
        m[5] =  fe3/2.0 + e[Al]/2.0 + e[Cr]/2.0 - e[Na]/2.0 - e[Ti];
        m[6] =  e[Na];
      }
      else {
        (*solids[j].convert)(FIRST, SECOND, *temperature, *pressure, e, m, NULL, NULL, NULL, NULL, NULL, NULL);
      }

      (*solids[j].convert)(SECOND, THIRD, *temperature, *pressure, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
      mu = (double *) malloc ((size_t) solids[j].na*sizeof(double));

      for (i=0, mTot=0.0; i<solids[j].na; i++) {
        mTot += m[i];
        gibbs(*temperature, *pressure, (char *) solids[j+1+i].label, &solids[j+1+i].ref, NULL, NULL, &solids[j+1+i].cur);
      }
      
      (*solids[j].gmix) (FIRST, *temperature, *pressure, r, &G, NULL, NULL, NULL);
      (*solids[j].hmix) (FIRST, *temperature, *pressure, r, &H);
      (*solids[j].smix) (FIRST, *temperature, *pressure, r, &S, NULL, NULL);
      (*solids[j].vmix) (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, 
         *temperature, *pressure, r, &V, NULL, NULL, &dVdT, &dVdP, &d2VdT2, &d2VdTdP, &d2VdP2, NULL, NULL);
      (*solids[j].cpmix)(FIRST | SECOND, *temperature, *pressure, r, &Cp, &dCpdT, NULL);
      (*solids[j].activity)(SECOND, *temperature, *pressure, r, NULL, mu, NULL);

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
        G       += m[i]*(solids[j+1+i].cur).g;
        H       += m[i]*(solids[j+1+i].cur).h;
        S       += m[i]*(solids[j+1+i].cur).s;
        V       += m[i]*(solids[j+1+i].cur).v;
        Cp      += m[i]*(solids[j+1+i].cur).cp;
        dCpdT   += m[i]*(solids[j+1+i].cur).dcpdt;
        dVdT    += m[i]*(solids[j+1+i].cur).dvdt;
        dVdP    += m[i]*(solids[j+1+i].cur).dvdp;
        d2VdT2  += m[i]*(solids[j+1+i].cur).d2vdt2;
        d2VdTdP += m[i]*(solids[j+1+i].cur).d2vdtdp;
        d2VdP2  += m[i]*(solids[j+1+i].cur).d2vdp2;
#ifndef TESTDYNAMICLIB
        phaseProperties[11+i] = mu[i] + (solids[j+1+i].cur).g;
#endif
      }

#ifdef TESTDYNAMICLIB
      for (i=0; i<nc; i++) {
        phaseProperties[11+i]=0.0;
        for (k=0; k<solids[j].na; k++) phaseProperties[11+i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
      }
      totalMoles = mTot;
#endif

      free(m);
      free(r);
      free(mu);

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

#ifdef TESTDYNAMICLIB
    for (i=0, totalGrams = 0.0; i<nc; i++) {
      totalGrams += bulkComposition[i];
    }
    phaseProperties[11+nc  ] = (totalMoles != 0.0) ? totalGrams/totalMoles : 0.0;
    phaseProperties[11+nc+1] = (V != 0.0) ? 100.0*totalGrams/V : 0.0;
    phaseProperties[11+nc+2] = totalGrams;
#endif

  }
}

/* ================================================================================== */
/* Input and Output (as above)                                                        */
/* ================================================================================== */

void getMeltsPhaseProperties(int *failure, char *phaseName, double *temperature, 
                 double *pressure, double *bulkComposition, double *phaseProperties) {
  /* don't return mu for Matlab version (put actual MELTS composition instead) */
  double *propertiesPtr = phaseProperties;

#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif  
    meltsgetphaseproperties_(phaseName, temperature, pressure, bulkComposition, phaseProperties);
    if (phaseProperties != NULL) *failure = FALSE;
    else phaseProperties = propertiesPtr;
#ifdef USESEH
    *failure = (*failure) ? (*failure) : doInterrupt;
#elif defined(USESJLJ)
  }
#endif  
}
/* ================================================================================== */
/* Retrieves properties of solid and liquid phases using mole fractions of endmembers */
/* Input:                                                                             */
/*   phaseName       - string as returned from meltsGetPhaseNames                     */
/*   temperature     - Temperature in Kelvins of the node                             */
/*   pressure        - Pressure in bars of the node                                   */
/*   bulkComposition - Bulk composition of the phase in mole fractions (or moles)     */ 
/* Output:                                                                            */
/*   phaseProperties - 1-d array, properties in the order                             */
/*                     G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2     */
/* ================================================================================== */

void meltsgetmolarproperties_(char *phaseName, double *temperature, 
         double *pressure, double *bulkComposition, double *phaseProperties) {
  PhaseList *res;

  if (!iAmInitialized) initializeLibrary();
  
  if (phaseList == NULL) {
    initializePhaseList();
  }

  strcpy(key.name, phaseName);
  res = bsearch(&key, phaseList, (size_t) np, sizeof(struct _phaseList), comparePhases);
  
  if (res == NULL) { phaseProperties = NULL; return; }
  else { 
    int i, j = res->index;
    double G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2, totalGrams;
    
    if (j < 0) { /* liquid */
      double *m, *r, mTot, *mu;

      m = (double *) calloc((size_t) nlc,    sizeof(double));
      r = (double *) malloc((size_t) (nlc-1)*sizeof(double));
      for (i=0; i<nlc; i++) m[i] = bulkComposition[i];
      mu = (double *) calloc((size_t) nlc, sizeof(double));

      if ((silminState != NULL) && (silminState->fo2Path != FO2_NONE)) {
        silminState->fo2 = getlog10fo2(*temperature, *pressure, silminState->fo2Path);
        conLiq(FIRST | SEVENTH, FIRST, *temperature, *pressure, m, NULL, NULL, NULL, NULL, NULL, &(silminState->fo2));
      }
      conLiq(SECOND, THIRD, *temperature, *pressure, NULL, m, r, NULL, NULL, NULL, NULL);

      gmixLiq (FIRST, *temperature, *pressure, r, &G, NULL, NULL);
      hmixLiq (FIRST, *temperature, *pressure, r, &H, NULL);
      smixLiq (FIRST, *temperature, *pressure, r, &S, NULL, NULL, NULL);
      vmixLiq (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, 
        *temperature, *pressure, r, &V, NULL, NULL, &dVdT, &dVdP, &d2VdT2, &d2VdTdP, &d2VdP2, NULL, NULL, NULL);
      cpmixLiq(FIRST | SECOND, *temperature, *pressure, r, &Cp, &dCpdT, NULL);
      actLiq(SECOND, *temperature, *pressure, r, NULL, mu, NULL, NULL);

      for (i=0, mTot=0.0; i<nlc; i++) {
        mTot +=  m[i];
        gibbs(*temperature, *pressure, (char *) liquid[i].label, &liquid[i].ref, &liquid[i].liq, &liquid[i].fus, &liquid[i].cur);
      }

      for (i=0; i<nlc; i++) {
        G       += m[i]*(liquid[i].cur).g/mTot;
        H       += m[i]*(liquid[i].cur).h/mTot;
        S       += m[i]*(liquid[i].cur).s/mTot;
        V       += m[i]*(liquid[i].cur).v/mTot;
        Cp      += m[i]*(liquid[i].cur).cp/mTot;
        dCpdT   += m[i]*(liquid[i].cur).dcpdt/mTot;
        dVdT    += m[i]*(liquid[i].cur).dvdt/mTot;
        dVdP    += m[i]*(liquid[i].cur).dvdp/mTot;
        d2VdT2  += m[i]*(liquid[i].cur).d2vdt2/mTot;
        d2VdTdP += m[i]*(liquid[i].cur).d2vdtdp/mTot;
        d2VdP2  += m[i]*(liquid[i].cur).d2vdp2/mTot;
#ifndef TESTDYNAMICLIB
        phaseProperties[11+i] = mu[i] +  (liquid[i].cur).g;
#endif
      }

#ifdef TESTDYNAMICLIB
      for (i=0, totalGrams = 0.0; i<nc; i++) {
        phaseProperties[11+i] = 0.0;
        for (j=0; j<nlc; j++) phaseProperties[11+i] += (liquid[j].liqToOx)[i]*m[j]*bulkSystem[i].mw/mTot;
        totalGrams += phaseProperties[11+i];
      }
#endif

      free(m);
      free(r);
      free(mu);

    } else if (solids[j].na == 1) {
      gibbs(*temperature, *pressure, phaseName, &solids[j].ref, NULL, NULL, &solids[j].cur);
      
      G       = (solids[j].cur).g;
      H       = (solids[j].cur).h;
      S       = (solids[j].cur).s;
      V       = (solids[j].cur).v;
      Cp      = (solids[j].cur).cp;
      dCpdT   = (solids[j].cur).dcpdt;
      dVdT    = (solids[j].cur).dvdt;
      dVdP    = (solids[j].cur).dvdp;
      d2VdT2  = (solids[j].cur).d2vdt2;
      d2VdTdP = (solids[j].cur).d2vdtdp;
      d2VdP2  = (solids[j].cur).d2vdp2;

#ifdef TESTDYNAMICLIB
      for (i=0, totalGrams = 0.0; i<nc; i++) {
        phaseProperties[11+i] = (solids[j].solToOx)[i]*bulkSystem[i].mw;
        totalGrams += phaseProperties[11+i];
      }
#endif

    } else {
      double *m, *r, mTot, *mu; 
      int k;
      m = (double *) malloc ((size_t) solids[j].na*sizeof(double));
      r = (double *) malloc ((size_t) solids[j].nr*sizeof(double));

      for (i=0; i<solids[j].na; i++) m[i] = bulkComposition[i];

      (*solids[j].convert)(SECOND, THIRD, *temperature, *pressure, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
      mu = (double *) malloc ((size_t) solids[j].na*sizeof(double));

      for (i=0, mTot=0.0; i<solids[j].na; i++) {
        mTot += m[i];
        gibbs(*temperature, *pressure, (char *) solids[j+1+i].label, &solids[j+1+i].ref, NULL, NULL, &solids[j+1+i].cur);
      }
      
      (*solids[j].gmix) (FIRST, *temperature, *pressure, r, &G, NULL, NULL, NULL);
      (*solids[j].hmix) (FIRST, *temperature, *pressure, r, &H);
      (*solids[j].smix) (FIRST, *temperature, *pressure, r, &S, NULL, NULL);
      (*solids[j].vmix) (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, 
         *temperature, *pressure, r, &V, NULL, NULL, &dVdT, &dVdP, &d2VdT2, &d2VdTdP, &d2VdP2, NULL, NULL);
      (*solids[j].cpmix)(FIRST | SECOND, *temperature, *pressure, r, &Cp, &dCpdT, NULL);
      (*solids[j].activity)(SECOND, *temperature, *pressure, r, NULL, mu, NULL);
 
      for (i=0; i<solids[j].na; i++) {
        G       += m[i]*(solids[j+1+i].cur).g/mTot;
        H       += m[i]*(solids[j+1+i].cur).h/mTot;
        S       += m[i]*(solids[j+1+i].cur).s/mTot;
        V       += m[i]*(solids[j+1+i].cur).v/mTot;
        Cp      += m[i]*(solids[j+1+i].cur).cp/mTot;
        dCpdT   += m[i]*(solids[j+1+i].cur).dcpdt/mTot;
        dVdT    += m[i]*(solids[j+1+i].cur).dvdt/mTot;
        dVdP    += m[i]*(solids[j+1+i].cur).dvdp/mTot;
        d2VdT2  += m[i]*(solids[j+1+i].cur).d2vdt2/mTot;
        d2VdTdP += m[i]*(solids[j+1+i].cur).d2vdtdp/mTot;
        d2VdP2  += m[i]*(solids[j+1+i].cur).d2vdp2/mTot;
#ifndef TESTDYNAMICLIB
        phaseProperties[11+i] = mu[i] + (solids[j+1+i].cur).g;
#endif
      }

#ifdef TESTDYNAMICLIB
      for (i=0, totalGrams = 0.0; i<nc; i++) {
        phaseProperties[11+i]=0.0;
        for (k=0; k<solids[j].na; k++) phaseProperties[11+i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw/mTot;
        totalGrams += phaseProperties[11+i];
      }
#endif

      free(m);
      free(r);
      free(mu);

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

#ifdef TESTDYNAMICLIB
    phaseProperties[11+nc  ] = totalGrams;
    phaseProperties[11+nc+1] = (V != 0.0) ? 100.0*totalGrams/V : 0.0;
    phaseProperties[11+nc+2] = totalGrams;
#endif

  }
}

/* ================================================================================== */
/* Input and Output (as above)                                                        */
/* ================================================================================== */

void getMeltsMolarProperties(int *failure, char *phaseName, double *temperature, 
                 double *pressure, double *bulkComposition, double *phaseProperties) {
  /* don't return mu for Matlab version (put actual MELTS composition instead) */
  double *propertiesPtr = phaseProperties;

#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif  
    meltsgetmolarproperties_(phaseName, temperature, pressure, bulkComposition, phaseProperties);
    if (phaseProperties != NULL) *failure = FALSE;
    else phaseProperties = propertiesPtr;
#ifdef USESEH
    *failure = (*failure) ? (*failure) : doInterrupt;
#elif defined(USESJLJ)
  }
#endif  
}

/* ================================================================================== */
/* Retrieves properties of solid and liquid phase end members                         */
/* Input:                                                                             */
/*   phaseName           - string as returned from meltsGetPhaseNames                 */
/*   temperature         - Temperature in Kelvins of the node                         */
/*   pressure            - Pressure in bars of the node                               */
/*   bulkComposition     - Bulk composition of the phase in grams of oxides           */ 
/*   nCharInName         - number of characters dimensioned for each name             */
/*                         i.e. in FORTRAN : CHARACTER*20, where nCharInName is 20    */
/* Output:                                                                            */
/*   endMemberNames      - array of formulae for columns of endMemberProperties       */
/*                         memory must be allocated for this array by the calling     */
/*                         program, e.g. CHARACTER*20 endMemberNames(20)              */
/*   numberEndMembers    - number of entries in endMemberNames and columns in         */
/*                         endMemberProperties                                        */
/*   endMemberProperties - 1-d array, properties in the order X, mu0, mu              */
/* ================================================================================== */

void meltsgetendmemberproperties_(char *phaseName, double *temperature, 
         double *pressure, double *bulkComposition, char endMemberNames[], 
	 int *nCharInName, int *numberEndMembers, double *endMemberProperties) {
  PhaseList *res;
  int nCh = *nCharInName;

  if (!iAmInitialized) initializeLibrary();

  if (phaseList == NULL) {
    initializePhaseList();
  }

  strcpy(key.name, phaseName);
  res = bsearch(&key, phaseList, (size_t) np, sizeof(struct _phaseList), comparePhases);
  
  if (res == NULL) { endMemberProperties = NULL; return; }
  else { 
    int i, j = res->index;
    int columnLength = 4; /* X, act, mu0, mu */
    
    if (j < 0) { /* liquid */
      double *m, *r, mTot;
      double *aLiq, *muLiq;
      int k;

      m = (double *) calloc((size_t) nls,    sizeof(double));
      r = (double *) malloc((size_t) (nlc-1)*sizeof(double));
      muLiq = (double *) calloc((size_t) nls, sizeof(double));
      aLiq = (double *) calloc((size_t) nls, sizeof(double));
      for (k=0; k<nc; k++) for (i=0; i<nlc; i++) m[i] += (bulkSystem[k].oxToLiq)[i]*bulkComposition[k]/bulkSystem[k].mw;

      if ((silminState != NULL) && (silminState->fo2Path != FO2_NONE)) {
      	silminState->fo2 = getlog10fo2(*temperature, *pressure, silminState->fo2Path);
	      conLiq(FIRST | SEVENTH, FIRST, *temperature, *pressure, m, NULL, NULL, NULL, NULL, NULL, &(silminState->fo2));
      }

      conLiq(SECOND, THIRD, *temperature, *pressure, NULL, m, r, NULL, NULL, NULL, NULL);
      actLiq(FIRST | SECOND, *temperature, *pressure, r, aLiq, muLiq, NULL, NULL);

      for (i=0, mTot = 0.0; i<nlc; i++) {
        mTot +=  m[i];
        gibbs(*temperature, *pressure, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
        muLiq[i] += (liquid[i].cur).g;
      }

#ifdef TESTDYNAMICLIB
      if ((calculationMode == MODE__MELTSandCO2) || (calculationMode == MODE__MELTSandCO2_H2O)) {
        static int nSiO2 = -1, nCaSiO3 = -1, nCO2 = -1;
    
        if ( (nSiO2 == -1) || (nCaSiO3 == -1) || (nCO2 == -1) ) {
            int i;
            for (i=0; i<nlc; i++) if (strcmp(liquid[i].label, "SiO2")   == 0) { nSiO2   = i; break; }
            for (i=0; i<nlc; i++) if (strcmp(liquid[i].label, "CaSiO3") == 0) { nCaSiO3 = i; break; }
            for (i=0; i<nlc; i++) if (strcmp(liquid[i].label, "CO2")    == 0) { nCO2    = i; break; }
            if ( (nSiO2 == -1) || (nCaSiO3 == -1) || (nCO2 == -1)) {
                printf("FATAL ERROR in library.c. Request for CaCO3 properties when nSiO2 = %d, nCaSiO3 = %d and nCO2 = %d.\n", nSiO2, nCaSiO3, nCO2);
                endMemberProperties = NULL; return;
            }
        }

        gibbs(*temperature, *pressure, (char *) liquid[nlc].label, &(liquid[nlc].ref), &(liquid[nlc].liq), &(liquid[nlc].fus), &(liquid[nlc].cur));

        /* reaction: CaSiO3 + CO2 - SiO2 = CaCO3 */
        muLiq[nlc] = muLiq[nCaSiO3] + muLiq[nCO2] - muLiq[nSiO2];
        aLiq[nlc] = exp((muLiq[nlc]-liquid[nlc].cur.g)/(*temperature*R));

        actLiq(0, *temperature, *pressure, r, &m[nlc], NULL, NULL, NULL);
        m[nlc] *= mTot; m[nSiO2] += m[nlc];
        m[nCaSiO3] -= m[nlc]; m[nCO2] -= m[nlc];

      }
      (*numberEndMembers) = nls;

      for (i=0; i<nls; i++) {
#else
      (*numberEndMembers) = nlc;

      for (i=0; i<nlc; i++) {
#endif
      	endMemberProperties[i*columnLength+ 0] = (mTot != 0.0) ? m[i]/mTot : 0.0;
        endMemberProperties[i*columnLength+ 1] = (m[i] != 0.0) ? aLiq[i] : 0.0;
        endMemberProperties[i*columnLength+ 2] = (m[i] != 0.0) ? (liquid[i].cur).g : 0.0;
        endMemberProperties[i*columnLength+ 3] = (m[i] != 0.0) ? muLiq[i] : 0.0;
        strncpy(endMemberNames+i*sizeof(char)*nCh,liquid[i].label, nCh);
      }
      
      free(m);
      free(r);
      free(muLiq);
      free(aLiq);

    } else if (solids[j].na == 1) {
      gibbs(*temperature, *pressure, phaseName, &solids[j].ref, NULL, NULL, &(solids[j].cur));

      endMemberProperties[ 0] = 1.0;
      endMemberProperties[ 1] = 1.0;
      endMemberProperties[ 2] = (solids[j].cur).g;
      endMemberProperties[ 3] = (solids[j].cur).g;
      strncpy(endMemberNames,solids[j].formula, nCh);
      (*numberEndMembers) = 1;

    } else {
      double e[106], *m, *r, mTot; 
      double *aSol, *muSol;
      int k;
      for (i=0; i<106; i++) e[i] = 0.0;
      for (i=0; i<nc; i++) {
        double mOx = bulkComposition[i]/bulkSystem[i].mw;
      	for (k=0; k<106; k++) e[k] += mOx*(bulkSystem[i].oxToElm)[k];
      }
      m = (double *) calloc ((size_t) solids[j].na, sizeof(double));
      r = (double *) malloc ((size_t) solids[j].nr*sizeof(double));
      muSol = (double *) calloc((size_t) solids[j].na, sizeof(double));
      aSol = (double *) calloc((size_t) solids[j].na, sizeof(double));

      if (!strncmp(solids[j].label,"clinopyroxene", MIN((int) strlen(solids[j].label), 13)) || 
        !strncmp(solids[j].label,"orthopyroxene", MIN((int) strlen(solids[j].label), 13))) {
        // use input Fe2O3 for Opx/Cpx as entered (see marc.c)
        double sumcat, sumchg, fe2, fe3;
        static const int Na = 11;
        static const int Mg = 12;
        static const int Al = 13;
        static const int Si = 14;
        static const int Ca = 20;
        static const int Ti = 22;
        static const int Cr = 24;
        static const int Mn = 25;
        static const int Fe = 26;

        /* Sum the cations and correct the analysis for silica deficiency */
        sumcat  = e[Na] +     e[Mg] +     e[Al] +     e[Si] +     e[Ca] +     e[Ti] +     e[Cr] +     e[Mn] + e[Fe];
        sumchg  = e[Na] + 2.0*e[Mg] + 3.0*e[Al] + 4.0*e[Si] + 2.0*e[Ca] + 4.0*e[Ti] + 3.0*e[Cr] + 2.0*e[Mn];

        /* Compute the ferric/ferrous ratio */
        fe3 = 3.0*sumcat - sumchg - 2.0*e[Fe];
        fe2 = e[Fe] - fe3;
        if (fe3 < 0.0) { fe3 = 0.0; fe2 = e[Fe]; }
        if (fe2 < 0.0) { fe2 = 0.0; fe3 = e[Fe]; }
          
        /* Assign moles of endmembers */
        m[0] = -fe3/2.0 - fe2 - e[Mn] - e[Al]/2.0 - e[Cr]/2.0 + e[Ca] + e[Na]/2.0 - e[Ti];
        m[1] =  fe3/4.0 + fe2/2.0 + e[Mn]/2.0 + e[Al]/4.0 + e[Cr]/4.0 - e[Ca]/2.0 + e[Mg]/2.0 - e[Na]/4.0;
        m[2] =  fe2 + e[Mn];
        m[3] = -fe3/2.0 + e[Al]/2.0 + e[Cr]/2.0 - e[Na]/2.0 + e[Ti];
        m[4] =  fe3/2.0 - e[Al]/2.0 - e[Cr]/2.0 + e[Na]/2.0 + e[Ti];
        m[5] =  fe3/2.0 + e[Al]/2.0 + e[Cr]/2.0 - e[Na]/2.0 - e[Ti];
        m[6] =  e[Na];
      }
      else {
        (*solids[j].convert)(FIRST, SECOND, *temperature, *pressure, e, m, NULL, NULL, NULL, NULL, NULL, NULL);
      }

      (*solids[j].convert)(SECOND, THIRD, *temperature, *pressure, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
      (*solids[j].activity)(0, *temperature, *pressure, r, aSol, NULL, NULL);
      (*solids[j].activity)(SECOND, *temperature, *pressure, r, NULL, muSol, NULL);

      for (i=0, mTot=0.0; i<solids[j].na; i++) {
        mTot +=  m[i];
        gibbs(*temperature, *pressure, (char *) solids[j+1+i].label, &solids[j+1+i].ref, NULL, NULL, &(solids[j+1+i].cur));
        muSol[i] += (solids[j+1+i].cur).g;
      }

      for (i=0; i<solids[j].na; i++) {
        endMemberProperties[i*columnLength+ 0] = (mTot != 0.0) ? m[i]/mTot : 0.0;
        endMemberProperties[i*columnLength+ 1] = (m[i] != 0.0) ? aSol[i] : 0.0;
        endMemberProperties[i*columnLength+ 2] = (m[i] != 0.0) ? (solids[j+1+i].cur).g : 0.0;
        endMemberProperties[i*columnLength+ 3] = (m[i] != 0.0) ? muSol[i] : 0.0;
        strncpy(endMemberNames+i*sizeof(char)*nCh,solids[j+1+i].formula, nCh);
      }
      (*numberEndMembers) = solids[j].na;
      
      free(m);
      free(r);
      free(muSol);
      free(aSol);
      
    }
    
  }
}

/* ================================================================================== */
/* Input and Output (as above except):                                                */
/*   phaseName        - string as returned from meltsGetPhaseNames, can also use      */
/*                      'garnet' or 'pyroxene', with 'clino / ortho / super' optional */
/*   endMemberPtr     - array of blank strings, assumed all to be of the same length  */
/*   numberEndMembers - input lt or equal to amount of allocated storage, output a/a  */
/*   propertiesPtr    - this is double[][3], instead of double*, and rows and columns */
/*                      are switched when calling from C rather than Fortran          */
/* ================================================================================== */

void getMeltsEndMemberProperties(int *failure, char *phaseName, double *temperature, 
          double *pressure, double *bulkComposition,
				  char *endMemberPtr, int *nCharInName, int *numberEndMembers, 
          double *endMemberProperties) {
  int i, nCh = *nCharInName, np = *numberEndMembers;
  char *endMemberNames = (char *) malloc((size_t) nCh*np*sizeof(char));
  double *propertiesPtr = endMemberProperties;

#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif
    for (i=0; i<nCh*np; i++) endMemberPtr[i] = '\0';
    meltsgetendmemberproperties_(phaseName, temperature, pressure, bulkComposition,
				 endMemberNames, nCharInName, numberEndMembers, endMemberProperties);
    np = *numberEndMembers;
    for (i=0; i<nCh*np; i++) {
      if (endMemberNames[i] == '\0') endMemberPtr[i] = ' ';
      else endMemberPtr[i] = endMemberNames[i];
    }
    free(endMemberNames);
    if (endMemberProperties != NULL) *failure = FALSE;
    else endMemberProperties = propertiesPtr;
#ifdef USESEH
    *failure = (*failure) ? (*failure) : doInterrupt;
#elif defined(USESJLJ)
  }
#endif  
}

/* ================================================================================== */
/* Retrieves properties of solid and liquid phases in oxide components                */
/* Input:                                                                             */
/*   phaseName           - string as returned from meltsGetPhaseNames                 */
/*   temperature         - Temperature in Kelvins of the node                         */
/*   pressure            - Pressure in bars of the node                               */
/*   bulkComposition     - Bulk composition of the phase in grams of oxides           */ 
/*   nCharInName         - number of characters dimensioned for each name             */
/*                         i.e. in FORTRAN : CHARACTER*20, where nCharInName is 20    */
/* Output:                                                                            */
/*   oxideNames          - array of phase names for columns of oxideProperties        */
/*                         memory must be allocated for this array by the calling     */
/*                         program, e.g. CHARACTER*20 oxideNames(20)                  */
/*   numberOxides        - number of entries in oxideNames and columns in             */
/*                         oxideProperties                                            */
/*   oxideProperties - 1-d array, properties in the order X, mu0, mu                  */
/* ================================================================================== */

void meltsgetoxideproperties_(char *phaseName, double *temperature, 
         double *pressure, double *bulkComposition, char oxideNames[], 
	 int *nCharInName, int *numberOxides, double *oxideProperties) {
  PhaseList *res;
  int nCh = *nCharInName;

  if (!iAmInitialized) initializeLibrary();

  if (phaseList == NULL) {
    initializePhaseList();
  }

  strcpy(key.name, phaseName);
  res = bsearch(&key, phaseList, (size_t) np, sizeof(struct _phaseList), comparePhases);
  
  if (res == NULL) { oxideProperties = NULL; return; }
  else { 
    int i, j = res->index;
    int columnLength = 4; /* X, act, mu0, mu */
    
    if (j < 0) { /* liquid */
      double *m, *r, mTot;
      double *muLiq;
      int k;

      m = (double *) calloc((size_t) nlc,    sizeof(double));
      r = (double *) malloc((size_t) (nlc-1)*sizeof(double));
      muLiq = (double *) malloc((size_t) nlc*sizeof(double));
      for (k=0; k<nc; k++) for (i=0; i<nlc; i++) m[i] += (bulkSystem[k].oxToLiq)[i]*bulkComposition[k]/bulkSystem[k].mw;
      
      if ((silminState != NULL) && (silminState->fo2Path != FO2_NONE)) {
        silminState->fo2 = getlog10fo2(*temperature, *pressure, silminState->fo2Path);
        conLiq(FIRST | SEVENTH, FIRST, *temperature, *pressure, m, NULL, NULL, NULL, NULL, NULL, &(silminState->fo2));
      }

      conLiq(SECOND, THIRD, *temperature, *pressure, NULL, m, r, NULL, NULL, NULL, NULL);
      actLiq(SECOND, *temperature, *pressure, r, NULL, muLiq, NULL, NULL);

      for (i=0; i<nlc; i++) {
        gibbs(*temperature, *pressure, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
        muLiq[i] += (liquid[i].cur).g;
      }   

      for (k=0; k<columnLength*nc; k++) oxideProperties[k] = 0.0;
      for (i=0; i<nlc; i++) for (k=0; k<nc; k++) oxideProperties[k*columnLength+ 0] += (liquid[i].liqToOx)[k] * m[i];
      for (k=0; k<nc; k++) for (i=0; i<nlc; i++) oxideProperties[k*columnLength+ 3] += (bulkSystem[k].oxToLiq)[i] * muLiq[i];
      for (k=0, mTot=0.0; k<nc; k++) mTot += oxideProperties[k*columnLength +0];

      for (k=0; k<nc; k++) {
        if (oxideProperties[k*columnLength +0] != 0.0) {
          int len = strlen(bulkSystem[k].label);
          for (i=0; i<nlc; i++) {
            if (!strncmp(bulkSystem[k].label, liquid[i].label, MIN(len, strlen(liquid[i].label)))) {
              muLiq[k] = oxideProperties[k*columnLength +3] - (liquid[i].cur).g;
              oxideProperties[k*columnLength+ 1] = exp(muLiq[k]/(*temperature*R));
              oxideProperties[k*columnLength+ 2] = (liquid[i].cur).g;
              break;
            }
          }
          if (mTot != 0.0) oxideProperties[k*columnLength +0] /= mTot;
        }
        else oxideProperties[k*columnLength +3] = 0.0;
      }

      for (k=0; k<nc; k++) strncpy(oxideNames+k*sizeof(char)*nCh,bulkSystem[k].label, nCh);
      (*numberOxides) = nc;
      
      free(m);
      free(r);
      free(muLiq);

    }
    /* else if (solids[j].na == 1) {*/ /* never used */
    /* else { */
    /* should not be used except for Lattice strain model, and is probably not correct even for that... */
    /* } */
    
  }
}

/* ================================================================================== */
/* Input and Output (as above except):                                                */
/*   phaseName        - string as returned from meltsGetPhaseNames, can also use      */
/*                      'garnet' or 'pyroxene', with 'clino / ortho / super' optional */
/*   oxidePtr         - array of blank strings, assumed all to be of the same length  */
/*   numberOxides     - input lt or equal to amount of allocated storage, output a/a  */
/*   propertiesPtr    - this is double[][3], instead of double*, and rows and columns */
/*                      are switched when calling from C rather than Fortran          */
/* ================================================================================== */

void getMeltsOxideProperties(int *failure, char *phaseName, double *temperature, 
          double *pressure, double *bulkComposition,
          char *oxidePtr, int *nCharInName, int *numberOxides, 
          double *oxideProperties) {
  int i, nCh = *nCharInName, nox = *numberOxides;
  char *oxideNames = (char *) malloc((size_t) nCh*nox*sizeof(char));
  double *propertiesPtr = oxideProperties;

#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined (USESEH)
    doInterrupt = FALSE;
#endif  
    for (i=0; i<nCh*nox; i++) oxidePtr[i] = '\0';
    meltsgetoxideproperties_(phaseName, temperature, pressure, bulkComposition,
                 oxideNames, nCharInName, numberOxides, oxideProperties);
    nox = *numberOxides;
    for (i=0; i<nCh*nox; i++) {
      if (oxideNames[i] == '\0') oxidePtr[i] = ' ';
      else oxidePtr[i] = oxideNames[i];
    }    
    free(oxideNames);
    if (oxideProperties != NULL) *failure = FALSE;
    else oxideProperties = propertiesPtr;
#ifdef USESEH
    *failure = (*failure) ? (*failure) : doInterrupt;
#elif defined(USESJLJ)
  }
#endif  
}

/* ================================================================================== */
/* ================================================================================== */

void meltssaturationstate_(int *nodeIndex, double *pressure, double *bulkComposition, double *temperature, 
        char phaseNames[], int *nCharInName, int *numberPhases, double *phaseProperties, int phaseIndices[]) {
  int update = FALSE;
  int i, j, k, np=0, nCh = *nCharInName, columnLength = nlc+1;
  double *m = (double *) calloc((size_t) nlc,    sizeof(double));
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
  } else {
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
    for (i=0; i<nlc; i++) {
      for (j=0; j<nc; j++) {
        (silminState->liquidComp)[0][i] += changeBC[j]*(bulkSystem[j].oxToLiq)[i];
        silminState->oxygen += changeBC[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
      }
    }
    for (i=0; i<nc; i++) {
      if (((silminState->bulkComp)[i] != 0.0) && (bulkSystem[i].type != FE2O3)) {
        if ((silminState->bulkComp)[i] <  MASSOUT)
          update = FALSE;
        else for (j=0; j<nlc; j++)
          if ((liquid[j].liqToOx[i] != 0.0) && (silminState->liquidComp[0][j] <= 0.0))
            update = FALSE;
      }
    }
  }
  if (!update) {
    int i, j;
    for (i=0, silminState->liquidMass=0.0; i<nc; i++) {
      (silminState->bulkComp)[i] = bulkComposition[i]/bulkSystem[i].mw;
      silminState->liquidMass += bulkComposition[i];
    }
    for (i=0; i<nlc; i++) {
      for ((silminState->liquidComp)[0][i]=0.0, silminState->oxygen=0.0, j=0; j<nc; j++) {
        (silminState->liquidComp)[0][i] += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i];
        silminState->oxygen += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
      }
    }
  }

  silminState->T           = *temperature;
  silminState->P           = *pressure;  
  
  /* -> Calculate liquid end-member properties                                  */
  for (i=0; i<nlc; i++) gibbs(silminState->T, silminState->P, (char *) liquid[i].label, &(liquid[i].ref),
                          &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));

  /* -> Calculate solid  end-member properties                                  */
  for (i=0, j=0; i<npc; i++) {
    if (solids[i].type == PHASE) {
      if ((silminState->incSolids)[j]) {
        if(solids[i].na == 1) gibbs(silminState->T, silminState->P, (char *) solids[i].label, &(solids[i].ref), NULL, NULL, &(solids[i].cur));
        else {
          for (k=0; k<solids[i].na; k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[i+1+k].label, &(solids[i+1+k].ref), NULL, NULL, &(solids[i+1+k].cur));
          }
          i += solids[i].na;
        }
      }
      j++;
    }
  }

  /* -> Calculate O2 end-member properties if path is buffered                  */          
           
  /* -> Redistribute Fe2O3 and FeO in liquid phase to establish buffer at this T and P */
  if (silminState->fo2Path != FO2_NONE) {
    double *moles = (double *) malloc((unsigned) nc*sizeof(double));
    gibbs(silminState->T, silminState->P, "o2", &(oxygen.ref), NULL, NULL, &(oxygen.cur));
    silminState->fo2 = getlog10fo2(silminState->T, silminState->P, silminState->fo2Path);
    for (i=0; i<nc; i++) {
      for (j=0, moles[i]=0.0; j<nlc; j++) moles[i] += (silminState->liquidComp)[0][j]*(liquid[j].liqToOx)[i];
      (silminState->bulkComp)[i] -= moles[i];
    }
    conLiq(FIRST | SEVENTH, FIRST, silminState->T, silminState->P, moles, NULL, NULL, NULL, NULL, NULL, &(silminState->fo2));
    for (i=0; i<nc; i++) (silminState->bulkComp)[i] += moles[i];  
    for (i=0; i<nlc; i++) for (j=0, (silminState->liquidComp)[0][i]=0.0; j<nc; j++)
          (silminState->liquidComp)[0][i] += moles[j]*(bulkSystem[j].oxToLiq)[i];
    free(moles);

  }

  if ((silminState->ySol) == NULL) {
    (silminState->ySol) = (double *) malloc((size_t) npc*sizeof(double));
    (silminState->yLiq) = (double *) malloc((size_t) nlc*sizeof(double));
  }
  evaluateSaturationState((silminState->ySol), (silminState->yLiq));

#ifdef TESTDYNAMICLIB  
  strncpy(phaseNames + np*sizeof(char)*nCh, "bulk", nCh);   phaseIndices[np] = -10; np++; 
  strncpy(phaseNames + np*sizeof(char)*nCh, "liquid", nCh); phaseIndices[np] = 0; np++;
#else
  strncpy(phaseNames + np*sizeof(char)*nCh, "system", nCh); phaseIndices[np] = 1; np++; 
  strncpy(phaseNames + np*sizeof(char)*nCh, "liquid", nCh); phaseIndices[np] = 2; np++;
#endif 
  *numberPhases = 2;

  phaseProperties[0] = -100000.0; // system
  for (i=0; i<nlc; i++) phaseProperties[0*columnLength+ i+1] = 0.0;

  for (i=0; i<nlc; i++) phaseProperties[1*columnLength+ i+1] = 0.0;
  if (silminState->liquidMass != 0.0) {
    phaseProperties[1*columnLength+ 0] = 0.0;     /* Affinity should be zero */
  }
  else {
    phaseProperties[1*columnLength+ 0] = (silminState->yLiq[nlc-1] == 0.0) ? -100000.0 : silminState->yLiq[nlc-1];
    for (i=0; i<nlc; i++) phaseProperties[1*columnLength+ i+1] = 0.0;
    if (silminState->yLiq[nlc-1] != 0.0) {
      conLiq(THIRD, FOURTH, *temperature, *pressure, NULL, NULL, silminState->yLiq, m, NULL, NULL, NULL);
      for (i=0; i<nlc; i++) phaseProperties[1*columnLength+ i+1] = m[i];
    }
  }

  for (j=0; j<npc; j++) if (solids[j].type == PHASE) { 
      strncpy(phaseNames + np*sizeof(char)*nCh, solids[j].label, nCh); 
      phaseIndices[np] = 10*j + 10;

      for (i=0; i<nlc; i++) phaseProperties[(*numberPhases)*columnLength+ i+1] = 0.0;
      if (silminState->nSolidCoexist[j] != 0) {
        phaseProperties[(*numberPhases)*columnLength+ 0] = 0.0;    /* Affinity should be zero */
      }
      else {
        phaseProperties[(*numberPhases)*columnLength+ 0] = (silminState->ySol[j] == 0.0) ? -100000.0 : silminState->ySol[j];
        if (solids[j].na > 1 && (silminState->ySol[j] != 0.0)) {
          (*solids[j].convert)(THIRD, FOURTH, *temperature, *pressure, NULL, NULL, &silminState->ySol[j+1], m, NULL, NULL, NULL, NULL);
          for (i=0; i<solids[j].na; i++) phaseProperties[(*numberPhases)*columnLength+ i+1] = m[i];
        }
      }
      (*numberPhases)++; np++;
  }
  free(m);

}

/* ================================================================================== */
/* ================================================================================== */

void getMeltsSaturationState(int *failure, double *pressure, double *bulkComposition, double *temperature, 
        char *phasePtr, int *nCharInName, int *numberPhases, double *phaseProperties, int phaseIndices[]) {
  int i, nodeIndex = 1, nCh = *nCharInName, np = *numberPhases;
  char *phaseNames = (char *) malloc((size_t) nCh*np*sizeof(char));
  
#ifdef USESJLJ
  if (setjmp(env) == 0) {
    setErrorHandler();
#elif defined(USESEH)
    doInterrupt = FALSE;
#endif
    for (i=0; i<nCh*np; i++) phasePtr[i] = '\0';    
    meltssaturationstate_(&nodeIndex, pressure, bulkComposition, temperature, phaseNames, nCharInName, 
      numberPhases, phaseProperties, phaseIndices);
    np = *numberPhases;
    for (i=0; i<nCh*np; i++) {
      if (phaseNames[i] == '\0') phasePtr[i] = ' ';
      else phasePtr[i] = phaseNames[i];
    }
    free(phaseNames);
    *failure = FALSE;
#ifdef USESEH
    *failure = doInterrupt;
#elif defined(USESJLJ)
  }
#endif
}

/* ================================================================================== */
/* From interface.c                                                                   */
/* ================================================================================== */

#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))

static void doBatchFractionation(void) {
    int i, j, k, ns, nl;
    int hasLiquid = ((silminState != NULL) && (silminState->liquidMass != 0.0));
    
    /* Solid Phase Fractionation */
    if ((silminState->fractionateSol || silminState->fractionateFlu) && !hasLiquid) fprintf(stderr, "...Cannot do solid/fluid fractionation without a liquid phase.\n");
    
    if ((silminState->fractionateSol || silminState->fractionateFlu) && hasLiquid) {
        double *m = (double *) malloc((size_t) nlc*sizeof(double));
        double *r = (double *) malloc((size_t) nlc*sizeof(double));
        for (i=0; i<npc; i++) if (solids[i].type == PHASE) {
            if ((silminState->nSolidCoexist)[i] > (silminState->nFracCoexist)[i]) {
                int ns = (silminState->nSolidCoexist)[i];
                int nf = (silminState->nFracCoexist)[i];
                (silminState->nFracCoexist)[i] = ns;
                if (nf == 0) {
                    (silminState->fracSComp)[i] = (double *) calloc((size_t) ns, sizeof(double));
                    if (solids[i].na > 1) for (j=0; j<solids[i].na; j++) (silminState->fracSComp)[i+1+j] = (double *) calloc((size_t) ns, sizeof(double));
                } else {
                    (silminState->fracSComp)[i] = (double *) REALLOC((silminState->fracSComp)[i], (size_t) ns*sizeof(double));
                    for (j=nf; j<ns; j++) (silminState->fracSComp)[i][j] = 0.0;
                    if (solids[i].na > 1) for (j=0; j<solids[i].na; j++) {
                        (silminState->fracSComp)[i+1+j] = (double *) REALLOC((silminState->fracSComp)[i+1+j], (size_t) ns*sizeof(double));
                        for (k=nf; k<ns; k++) (silminState->fracSComp)[i+1+j][k] = 0.0;
                    }
                }
            }
        }
	int haveWater = ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS));
        for (i=0; i<npc; i++) {
	    if ( haveWater &&  silminState->fractionateSol && !silminState->fractionateFlu && !strcmp((char *) solids[i].label, "water")) continue;
	    if ( haveWater && !silminState->fractionateSol &&  silminState->fractionateFlu &&  strcmp((char *) solids[i].label, "water")) continue;
	    if (!haveWater &&  silminState->fractionateSol && !silminState->fractionateFlu && !strcmp((char *) solids[i].label, "fluid")) continue;
	    if (!haveWater && !silminState->fractionateSol &&  silminState->fractionateFlu &&  strcmp((char *) solids[i].label, "fluid")) continue;
            for (ns=0; ns<(silminState->nSolidCoexist)[i]; ns++) {
                if (solids[i].na == 1) {
                    (silminState->fracSComp)[i][ns] += (silminState->solidComp)[i][ns]-MASSIN;
                    if (silminState->fo2Path != FO2_NONE) silminState->oxygen -= (oxygen.solToOx)[i]*((silminState->solidComp)[i][ns]-MASSIN);
                    silminState->fracMass += ((silminState->solidComp)[i][ns]-MASSIN)*solids[i].mw;
                    for (j=0; j<nc; j++) (silminState->bulkComp)[j] -= (solids[i].solToOx)[j]*((silminState->solidComp)[i][ns]-MASSIN);
                    
                    /* Subtract off H, S or V if appropriate                          */
                    if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0))
                        silminState->refEnthalpy -= ((silminState->solidComp)[i][ns]-MASSIN)*(solids[i].cur).h;
                    if (silminState->isentropic && (silminState->refEntropy != 0.0))
                        silminState->refEntropy -= ((silminState->solidComp)[i][ns]-MASSIN)*(solids[i].cur).s;
                    if (silminState->isochoric && (silminState->refVolume != 0.0))
                        silminState->refVolume -= ((silminState->solidComp)[i][ns]-MASSIN)*(solids[i].cur).v;
                    
                    (silminState->solidComp)[i][ns] = MASSIN;
                } else {
                    double moleF, totalMoles=0.0;
                    (silminState->fracSComp)[i][ns] += (silminState->solidComp)[i][ns] - MASSIN;
                    for (j=0; j<solids[i].na; j++) {
                        moleF = (silminState->solidComp)[i+1+j][ns]/(silminState->solidComp)[i][ns];
                        m[j] = (silminState->solidComp)[i+1+j][ns] - MASSIN*moleF;
                        totalMoles += m[j];
                        (silminState->fracSComp)[i+1+j][ns] += m[j];
                        if (silminState->fo2Path != FO2_NONE) silminState->oxygen -= (oxygen.solToOx)[i+1+j]*m[j];
                        silminState->fracMass += m[j]*solids[i+1+j].mw;
                        for (k=0; k<nc; k++) (silminState->bulkComp)[k] -= (solids[i+1+j].solToOx)[k]*m[j];
                        (silminState->solidComp)[i+1+j][ns] = MASSIN*moleF;
                        
                        /* Subtract off H, S or V if appropriate                        */
                        if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) silminState->refEnthalpy -= m[j]*(solids[i+1+j].cur).h;
                        if (silminState->isentropic && (silminState->refEntropy != 0.0))   silminState->refEntropy  -= m[j]*(solids[i+1+j].cur).s;
                        if (silminState->isochoric && (silminState->refVolume != 0.0))     silminState->refVolume   -= m[j]*(solids[i+1+j].cur).v;
                    }
                    (silminState->solidComp)[i][ns] = MASSIN;
                    
                    /* Subtract off H, S or V if appropriate                          */
                    if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) {
                        double enthalpy;
                        (*solids[i].convert)(SECOND, THIRD, silminState->T,silminState->P, NULL, m, r, NULL,  NULL, NULL, NULL, NULL);
                        (*solids[i].hmix)(FIRST, silminState->T, silminState->P, r, &enthalpy);
                        silminState->refEnthalpy -= totalMoles*enthalpy;
                    }
                    if (silminState->isentropic && (silminState->refEntropy != 0.0)) {
                        double entropy;
                        (*solids[i].convert)(SECOND, THIRD,silminState->T,silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                        (*solids[i].smix)(FIRST, silminState->T, silminState->P, r, &entropy, (double *) NULL, (double **) NULL);
                        silminState->refEntropy  -= totalMoles*entropy;
                    }
                    if (silminState->isochoric && (silminState->refVolume != 0.0)) {
                        double volume;
                        (*solids[i].convert)(SECOND, THIRD, silminState->T,silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                        (*solids[i].vmix)(FIRST, silminState->T, silminState->P, r, &volume, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                        silminState->refVolume   -= totalMoles*volume;
                    }
                    
                }
            }
        }
        
        for (i=0; i<nc; i++) {
            if ((silminState->bulkComp)[i] != 0.0 && (silminState->bulkComp)[i] <  MASSOUT && bulkSystem[i].type != FE2O3) {
                fprintf(stderr, "  Moles of %5.5s in system (%g) < %g\n.", bulkSystem[i].label, (silminState->bulkComp)[i], MASSOUT);
                (silminState->bulkComp)[i] = 0.0;
                for (j=0; j<nlc; j++) if ((liquid[j].liqToOx)[i] != 0.0) {
                    for (nl=0; nl<silminState->nLiquidCoexist; nl++) (silminState->liquidComp)[nl][j] = 0.0;
                    fprintf(stderr, "    Moles of %s in liquid(s) set to zero.\n", liquid[j].label);
                }
                for (j=0; j<npc; j++) {
                    for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
                        if (solids[j].na == 1) {
                            if ((solids[j].solToOx)[i] != 0.0) {
                                (silminState->solidComp)[j][ns] = 0.0;
                                fprintf(stderr, "    Moles of %s in solid set to zero.\n", solids[j].label);
                            }
                        } else {
                            for (k=0; k<solids[j].na; k++) {
                                if ((solids[j+1+k].solToOx)[i] != 0.0) {
                                    (silminState->solidComp)[j][ns] -= (silminState->solidComp)[j+1+k][ns];
                                    (silminState->solidComp)[j+1+k][ns] = 0.0;
                                    fprintf(stderr, "    Moles of %s in %s solid set to zero.\n", solids[j+1+k].label, solids[j].label);
                                }
                            }
                        }
                    }
                }
            }
        }
        free(m);
        free(r);
    }
    
    /* Liquid Phase Fractionation */
    if (silminState->fractionateLiq && !hasLiquid) fprintf(stderr, "...Cannot do liquid fractionation without a liquid phase.\n");
    
    if (silminState->fractionateLiq && hasLiquid) {
        double *m = (double *) malloc((size_t) nlc*sizeof(double));
        double *r = (double *) malloc((size_t) nlc*sizeof(double));
        for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
            double refMoles, totalMoles;
            for (i=0, refMoles=0.0; i<nlc; i++) refMoles += (silminState->liquidComp)[nl][i];
            
            for (i=0, totalMoles=0.0; i<nlc; i++) {
                if (((silminState->liquidComp)[nl][i] != 0.0) && (refMoles != 0.0)) {
                    double mw;
                    double moleF = (silminState->liquidComp)[nl][i]/refMoles;
                    
                    for (j=0, mw = 0.0; j<nc; j++) mw += (liquid[i].liqToOx)[j]*bulkSystem[j].mw;
                    m[i] = (silminState->liquidComp)[nl][i] - MASSIN*moleF;
                    totalMoles += m[i];
                    (silminState->fracLComp)[i] += m[i];
                    if (silminState->fo2Path != FO2_NONE) silminState->oxygen -= (oxygen.liqToOx)[i]*m[i];
                    silminState->fracMass += m[i]*mw;
                    for (j=0; j<nc; j++) (silminState->bulkComp)[j] -= (liquid[i].liqToOx)[j]*m[i];
                    (silminState->liquidComp)[nl][i] = MASSIN*moleF;
                    
                    /* Subtract off H, S or V if appropriate			    */
                    if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) silminState->refEnthalpy -= m[i]*(liquid[i].cur).h;
                    if (silminState->isentropic  && (silminState->refEntropy  != 0.0)) silminState->refEntropy  -= m[i]*(liquid[i].cur).s;
                    if (silminState->isochoric   && (silminState->refVolume   != 0.0)) silminState->refVolume	-= m[i]*(liquid[i].cur).v;
                } else m[i] = 0.0;
            }
            
            /* Subtract off H, S or V if appropriate			  */
            if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) {
                double enthalpy;
                conLiq (SECOND, THIRD, silminState->T,silminState->P, NULL, m, r, NULL,  NULL, NULL, NULL);
                hmixLiq(FIRST, silminState->T, silminState->P, r, &enthalpy, NULL);
                silminState->refEnthalpy -= totalMoles*enthalpy;
            }
            if (silminState->isentropic && (silminState->refEntropy != 0.0)) {
                double entropy;
                conLiq (SECOND, THIRD,silminState->T,silminState->P, NULL, m, r, NULL, NULL, NULL, NULL);
                smixLiq(FIRST, silminState->T, silminState->P, r, &entropy, NULL, NULL, NULL);
                silminState->refEntropy  -= totalMoles*entropy;
            }
            if (silminState->isochoric && (silminState->refVolume != 0.0)) {
                double volume;
                conLiq (SECOND, THIRD, silminState->T,silminState->P, NULL, m, r, NULL, NULL, NULL, NULL);
                vmixLiq(FIRST, silminState->T, silminState->P, r, &volume, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                silminState->refVolume   -= totalMoles*volume;
            }
            
        }
        
        for (i=0; i<nc; i++) {
            if ((silminState->bulkComp)[i] != 0.0 && (silminState->bulkComp)[i] <  MASSOUT && bulkSystem[i].type != FE2O3) {
                fprintf(stderr, "  Moles of %5.5s in system (%g) < %g\n.", bulkSystem[i].label, (silminState->bulkComp)[i], MASSOUT);
                (silminState->bulkComp)[i] = 0.0;
                for (j=0; j<nlc; j++) if ((liquid[j].liqToOx)[i] != 0.0) {
                    for (nl=0; nl<silminState->nLiquidCoexist; nl++) (silminState->liquidComp)[nl][j] = 0.0;
                    fprintf(stderr, "    Moles of %s in liquid(s) set to zero.\n", liquid[j].label);
                }
                for (j=0; j<npc; j++) {
                    for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
                        if (solids[j].na == 1) {
                            if ((solids[j].solToOx)[i] != 0.0) {
                                (silminState->solidComp)[j][ns] = 0.0;
                                fprintf(stderr, "    Moles of %s in solid set to zero.\n", solids[j].label);
                            }
                        } else {
                            for (k=0; k<solids[j].na; k++) {
                                if ((solids[j+1+k].solToOx)[i] != 0.0) {
                                    (silminState->solidComp)[j][ns] -= (silminState->solidComp)[j+1+k][ns];
                                    (silminState->solidComp)[j+1+k][ns] = 0.0;
                                    fprintf(stderr, "    Moles of %s in %s solid set to zero.\n", solids[j+1+k].label, solids[j].label);
                                }
                            }
                        }
                    }
                }
            }
        }
        free(m);
        free(r);
    }
}

#ifdef MINGW
BOOL WINAPI windows_console_handler(DWORD dwType) {
  int msgboxID = 0;
  switch(dwType) {
    case CTRL_C_EVENT:
      fputs("Warning: CTRL_C_EVENT\n", stderr);
      break;
    case CTRL_BREAK_EVENT:
      fputs("Warning: CTRL_BREAK_EVENT\n", stderr);
      break;
    case CTRL_CLOSE_EVENT:
      fputs("Warning: CTRL_CLOSE_EVENT\n", stderr);
      fputs("[To just close the console in future runs, type 'MELTSdynamic' instead.]\n", stderr);
      fputs("Closing MELTS for MATLAB! This cannot be undone without restarting MATLAB.\n", stderr);
      fputs("Please save your work and click 'X' again to exit the program.", stderr);
      fflush(stderr);
      ExitThread(0);
      break;
    default:
      fputs("Warning: Unrecognized Event\n", stderr);
      break;
  }
  fflush(stderr);
  return FALSE;
}
#endif

#ifdef USESEH
void raise_sigabrt(DWORD dwType) {
    HWND consoleWnd;
    DWORD dwProcessId;
    if ((consoleWnd = GetConsoleWindow()) == NULL) {
      addConsole();
      consoleWnd = GetConsoleWindow();
    }
    GetWindowThreadProcessId(consoleWnd, &dwProcessId);
    if (GetCurrentProcessId()==dwProcessId)
      GenerateConsoleCtrlEvent(CTRL_C_EVENT, 1);
    else
      RaiseException(dwType, 0, 0, NULL);
}
#endif

#ifdef USESJLJ
static void almost_c99_signal_handler(int sig) {
  switch(sig) {
  case SIGABRT:
    fputs("Caught SIGABRT: usually caused by an abort() or assert()\n", stderr);
    break;
  case SIGFPE:
    fputs("Caught SIGFPE: arithmetic exception, such as divide by zero\n", stderr);
    break;
  case SIGILL:
    fputs("Caught SIGILL: illegal instruction\n", stderr);
    break;
      /*
	case SIGINT:
	fputs("Caught SIGINT: interactive attention signal, probably a ctrl+c\n", stderr);
	break; 
	case SIGSEGV:
	fputs("Caught SIGSEGV: segfault\n", stderr);
	break;
      */
  default:
    fputs("Caught SIGTERM: a termination request was sent to the program\n", stderr);
    break;
  }
  /* was: _Exit(1); */
  longjmp(env, 0);
}

void setErrorHandler(void) {
  if (signal(SIGABRT, &almost_c99_signal_handler) == SIG_ERR) fprintf(stderr, "...Error in installing SIGABRT handler.\n");
  if (signal(SIGFPE, &almost_c99_signal_handler) == SIG_ERR) fprintf(stderr, "...Error in installing SIGFPE handler.\n");
  if (signal(SIGILL, &almost_c99_signal_handler) == SIG_ERR) fprintf(stderr, "...Error in installing SIGILL handler.\n");
  /*if (signal(SIGSEGV, &almost_c99_signal_handler) == SIG_ERR) fprintf(stderr, "...Error in installing SIGSEGV handler.\n");*/
  if (signal(SIGTERM, &almost_c99_signal_handler) == SIG_ERR) fprintf(stderr, "...Error in installing SIGTERM handler.\n");
}
#endif
