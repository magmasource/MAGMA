const char *preclb_public_ver(void) { return "$Id: preclb-public.c,v 1.3 2007/11/29 05:32:13 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: preclb-public.c,v $
MELTS Source Code: RCS Revision 1.3  2007/11/29 05:32:13  ghiorso
MELTS Source Code: RCS Majorite testMaj corrections.  Fixed "O2" in sol_struct_data.h to "o2".
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:19  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.9  2003/09/29 13:41:20  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.8  2003/04/11 23:13:19  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.7  2001/12/26 19:20:02  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2001/12/21 06:59:03  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2001/12/21 06:09:08  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2001/12/21 05:49:06  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Toolkit work proceedure to drive a PRECLB iteration (file: PRECLB.C)
**
**--
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Xm/Xm.h> 
#include <Xm/ToggleBG.h>

#include "interface.h"
#include "silmin.h"               
#include "calibration.h"
#include "recipes.h"

#include "res_struct_data.h"

#ifdef GRACE_PIPE
#include <unistd.h>
#include <grace_np.h>
static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}
#endif /* GRACE_PIPE */

#ifndef __APPLE__
#include <g2c.h>
#else
#include <f2c.h>
#endif /* __APPLE__ */

int dn2gb_(    /* double version of n2gb routine from the PORT Library v.3          */
  integer    *n,      /* number of observations                                            */
  integer    *p,      /* number of parameters                                              */
  doublereal *x,      /* input: initial guess at optimal parameters. output: best estiamte */
  doublereal *b,      /* bounds, FORTRAN B(2,P) = {low, high, low, high, ....}             */
  S_fp       calcr,   /* int calcr(...) : function to calculate vector of residuals        */
  S_fp       calcj,   /* int calcj(...) : function to calculate the Jacobian matrix        */
  integer    *iv,     /* control array                                                     */
  integer    *liv,    /* of length 82 + 4*p                                                */
  integer    *lv,     /* control array                                                     */
  doublereal *v,      /* of length 105 + p*(n + 2*p + 21) + 2*n                            */
  integer    *uiparm, /* integer array passed to calcr, calcj                              */
  doublereal *urparm, /* double array passed to calcr, calcj                               */
  U_fp       ufparm   /* int ufparam(...) : user function passed to calcr, calcj           */
) {}
  
int divset_(   /* double version of ivset routine from the PORT Library v.3         */
  integer    *kind,   /* type of optimization routine, regression with simple bounds = 1   */
  integer    *iv,     /* control array  						   */
  integer    *liv,    /* of length 82 + 4*p						   */
  integer    *lv,     /* control array  						   */
  doublereal *v       /* of length 105 + p*(n + 2*p + 21) + 2*n 			   */
){}

logical stopx_(/* function called by PORT Library v.3 to test for interrupts               */
  integer dummy) {
  if (fopen("STOP_MELTS", "r") != NULL) return TRUE_;
  else return FALSE_;                           /* return TRUE_ to halt dn2gb              */
}

#ifndef TESTING
#define TESTING
#endif

#define SQUARE(x) ((x)*(x))
#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))

int     nEqn, *iData, *jData, *lData;
double  **aData, *bData, *fo2Data, *pData, *tData, *residual;
Boolean *zData;
static char *alternateDataBase = (char *) NULL;

#define DISPLAY(w, string) \
  valueCS = XmStringCreateLtoR(string, "ISO8859-1"); \
  i = 0; \
  XtSetArg(arg_set[i], XmNlabelString, valueCS); i++; \
  XtSetValues(w, arg_set, i); \
  XmStringFree(valueCS);

#define DISPLAYD(w, number) \
  sprintf(valueD, "%20.13g", number); \
  valueCS = XmStringCreateLtoR(valueD , "ISO8859-1"); \
  i = 0; \
  XtSetArg(arg_set[i], XmNlabelString, valueCS); i++; \
  XtSetValues(w, arg_set, i); \
  XmStringFree(valueCS);

#define DISPLAYI(w, number) \
  sprintf(valueI, "%6.6d", number); \
  valueCS = XmStringCreateLtoR(valueI, "ISO8859-1"); \
  i = 0; \
  XtSetArg(arg_set[i], XmNlabelString, valueCS); i++; \
  XtSetValues(w, arg_set, i); \
  XmStringFree(valueCS);
  
#define REC   134     /* Maximal record length for data file reads */

#define ABORT(string1, string2) \
  cstring1 = XmStringCreateLtoR(string1, "ISO8859-1"); \
  cstring2 = XmStringCreateLtoR(string2, "ISO8859-1"); \
  cstring3 = XmStringConcat(cstring1, cstring2); \
  i = 0; \
  XtSetArg(arg_set[i], XmNmessageString, cstring3); i++; \
  XtSetValues(message, arg_set, i); \
  XtManageChild(message); \
  XmStringFree(cstring1); \
  XmStringFree(cstring2); \
  XmStringFree(cstring3);
  
#define GETNEWLINE \
  if (fgets(line, REC, input) == NULL) { \
    cstring1 = XmStringCreateLtoR( \
      "Error during data file read, offending record:\n", "ISO8859-1"); \
    cstring2 = XmStringCreateLtoR(line, "ISO8859-1"); \
    cstring3 = XmStringConcat(cstring1, cstring2); \
    i = 0; \
    XtSetArg(arg_set[i], XmNmessageString, cstring3); i++; \
    XtSetValues(message, arg_set, i); \
    XtManageChild(message); \
    XmStringFree(cstring1); \
    XmStringFree(cstring2); \
    XmStringFree(cstring3); \
    workProcData->active = FALSE; \
    return TRUE; \
  }

#define PARSELINE1 \
  if ((len = strlen(line)) < 81) {for (i=len-1; i<81; i++) line[i] = ' ';} \
  for (i=0; i<8; i++) { strncpy(entry, &line[i*10], 10); wt[i] = atof(entry); }

#define PARSELINE2 \
  if ((len = strlen(line)) < 81) {for (i=len-1; i<81; i++) line[i] = ' ';} \
  for (i=0; i<8; i++) { strncpy(entry, &line[i*10], 10); wt[i+8] = atof(entry); }

#define TESTnLIQUID \
  if (nLiquid == nLiquidMAX) { \
    nLiquidMAX += 100; \
    aData   = (double **) REALLOC((void *) aData,   (size_t) nLiquidMAX*sizeof(double *)); \
    for (i=nLiquid; i<nLiquidMAX; i++) aData[i] = (double *) malloc((size_t) (nlc-1)*sizeof(double)); \
  }

#define TESTnEQN \
  if (nEqn == nEqnMAX) { \
    nEqnMAX += 100; \
    bData   = (double *)  REALLOC((void *) bData,   (size_t) nEqnMAX*sizeof(double)); \
    fo2Data = (double *)  REALLOC((void *) fo2Data, (size_t) nEqnMAX*sizeof(double)); \
    iData   = (int *)     REALLOC((void *) iData,   (size_t) nEqnMAX*sizeof(int)); \
    jData   = (int *)     REALLOC((void *) jData,   (size_t) nEqnMAX*sizeof(int)); \
    lData   = (int *)     REALLOC((void *) lData,   (size_t) nEqnMAX*sizeof(int)); \
    pData   = (double *)  REALLOC((void *) pData,   (size_t) nEqnMAX*sizeof(double)); \
    tData   = (double *)  REALLOC((void *) tData,   (size_t) nEqnMAX*sizeof(double)); \
    zData   = (Boolean *) REALLOC((void *) zData,   (size_t) nEqnMAX*sizeof(Boolean)); \
  }

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

#ifdef NEVER_DEFINED
  DISPLAYD(anovaADB[0], ssREG)
  DISPLAYI(anovaADB[1], dfREG)
  DISPLAYD(anovaADB[2], F)
  DISPLAYD(anovaADB[3], ssRES)
  DISPLAYI(anovaADB[4], dfRES)
  DISPLAYD(anovaADB[5], ssTOT)
  DISPLAYI(anovaADB[6], dfTOT)
#endif

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

static int getDeltaGofSolid(double *deltaG, double *x, double t, double p, Boolean *lowWtFlag, double a, int solidID)
{
  int i, j;

 *deltaG = 0.0;
 
 for (i=0; i<nlc; i++) {
    if( (solids[solidID].solToLiq)[i] != 0.0) {
      Boolean lowMolFlag;
      for (j=0, lowMolFlag=False; j<nc; j++) lowMolFlag |= ((liquid[i].liqToOx)[j] != 0.0) && lowWtFlag[j];
      if (x[i] == 0.0 || lowMolFlag) return FALSE; 
    }
  }

  if (a > 0.0) { *deltaG += R*t*log(a); } else { return FALSE; }
  
  gibbs(t, p, solids[solidID].label, &(solids[solidID].ref), NULL, NULL, &(solids[solidID].cur));
  *deltaG += (solids[solidID].cur).g;
   
  return TRUE;
}

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

int getAlternateDataBaseFile(char *fileName)
{
  if (alternateDataBase == NULL) alternateDataBase = (char *) malloc((unsigned) (strlen(fileName)+1)*sizeof(char));
  else                           alternateDataBase = (char *) REALLOC(alternateDataBase, (unsigned) (strlen(fileName)+1)*sizeof(char));

  (void) strcpy(alternateDataBase, fileName);

  return 0;
}

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

static void writeParameters(char *paramFileName)
{
  XmString valueCS = NULL;
  int i, j, k;
  time_t dateTime;

  FILE *paramFile;

  if ( (paramFile = fopen (paramFileName, "w")) == NULL) {
    valueCS = XmStringCreateLtoR("Cannot open file PARAM_STRUCT_DATA.NEW" , "ISO8859-1");
    MESSAGE(valueCS); XmStringFree(valueCS); return;
  }

  (void) time(&dateTime);

  fprintf(paramFile, "#ifndef _Param_Struct_Data_h\n");
  fprintf(paramFile, "#define _Param_Struct_Data_h\n");
  fprintf(paramFile, "\n");
  
  fprintf(paramFile, "/*\n");
  fprintf(paramFile, "**++\n");
  fprintf(paramFile, "**  FACILITY:  Silicate Melts Regression Crystallization Package\n");
  fprintf(paramFile, "**\n");
  fprintf(paramFile, "**  MODULE DESCRIPTION:\n");
  fprintf(paramFile, "**\n");
  fprintf(paramFile, "**      Include file for initializing values of liquid interaction\n");
  fprintf(paramFile, "**         parameters (file: PARAM_STRUCT_DATA.H)\n");
  fprintf(paramFile, "**\n");
  fprintf(paramFile, "**  This file produced on: %s", asctime(localtime(&dateTime)));
  fprintf(paramFile, "**--\n");
  fprintf(paramFile, "*/\n");
  fprintf(paramFile, "\n");
  fprintf(paramFile, "/*\n");
  fprintf(paramFile, " *=============================================================================\n");
  fprintf(paramFile, " * Initialize global values of interaction parameters\n");
  fprintf(paramFile, " */\n");
  fprintf(paramFile, "\n");
  fprintf(paramFile, "ModelParameters modelParameters[] = {\n");

  for (i=0, k=0; i<nls; i++) {
    if (i > 0) fprintf(paramFile,"\n"); 
    for (j=i+1; j<nls; j++, k++) {
      fprintf(paramFile,"  { \"W(%-10.10s,%-10.10s)\",", liquid[j].label, liquid[i].label);
      fprintf(paramFile,"%10.1f,%10.1f,%10.6f, %s, %s, %s, %s }", modelParameters[k].enthalpy, modelParameters[k].entropy, modelParameters[k].volume, 
	modelParameters[k].activeH ? " TRUE" : "FALSE", modelParameters[k].activeS ? " TRUE" : "FALSE", 
	modelParameters[k].activeV ? " TRUE" : "FALSE", modelParameters[k].activeF ? " TRUE" : "FALSE");
      fprintf(paramFile,", /* %3.3d %-17.17s */\n", k, (j < nlc) ? "Basis species" : "Dependent species");
      if (j == (nlc-1)) fprintf(paramFile,"\n");
    }
  }
  
  for (i=0; i<nls; i++, k++) {
    fprintf(paramFile,"  { \"%-24.24s\",", liquid[i].label);
    fprintf(paramFile,"%10.1f,%10.1f,%10.6f, %s, %s, %s, %s }", modelParameters[k].enthalpy, modelParameters[k].entropy, modelParameters[k].volume, 
      modelParameters[k].activeH ? " TRUE" : "FALSE", modelParameters[k].activeS ? " TRUE" : "FALSE", 
      modelParameters[k].activeV ? " TRUE" : "FALSE", modelParameters[k].activeF ? " TRUE" : "FALSE");
    fprintf(paramFile,"%c /* %3.3d %17.17s */\n", (i < (nls-1)) ? ',' : ' ', k, (i < nlc) ? "Basis species" : "Dependent species");
    if (i == (nlc-1)) fprintf(paramFile,"\n");
  }    

  fprintf(paramFile, "};\n");
  fprintf(paramFile, "\n");
  fprintf(paramFile, "#endif /* _Param_Struct_Data_h */\n");

  fclose(paramFile);
}

/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

static int lastNf, currentNf;

int calcr(/* Residual routine required by dn2gb                                    */
  integer    *pt_n,  /* nuumber of observations 				   */
  integer    *pt_p,  /* number of parameters					   */
  doublereal *x,     /* current parameter guess 				   */
  integer    *pt_nf, /* invocation count for calcr; set to 0 if x is infeasible    */
  doublereal *r,     /* FORTRAN: R(N), r[1:n]                 	                   */
  integer    *ui,    /* passed via dn2gb					   */
  doublereal *ur,    /* passed via dn2gb					   */
  U_fp       uf      /* passed via dn2gb					   */
) {
  static double *mu, **dmudw;
  static int nH2O = -1, nSiOH = -1, *equivH2O;
  int n = (int) *pt_n, p = (int) *pt_p, nf = (int) *pt_nf, i, index, lastLiqID = -1;
  double sumOfSquares = 0.0;
  int increment = n/50;

  printf("Entering CALCR with nf = %5.5d ", nf); fflush(stdout);

  if (mu == NULL) {
    int j, k;
    int **indIJ = imatrix(0, nls-1, 0, nls-1); 
    mu       = vector(0, nlc-1); 
    dmudw    = matrix(0, nlc-1, 0, 3*(nls*(nls-1)/2 + nls)-1);
    equivH2O = ivector(0, (nls*(nls-1)/2 + nls)-1);
    for (i=0; i<(nls*(nls-1)/2+nls); i++) equivH2O[i] = -1;
    for (i=0, k=0; i<(nls-1); i++) { indIJ[i][i] = -1; for (j=i+1; j<nls; j++) { indIJ[i][j] = k; indIJ[j][i] = k; k++; } } 

    for (i=0;   i<nlc; i++) if (strcmp(liquid[i].label, "H2O")      == 0) { nH2O  = i; break; }
    for (i=nlc; i<nls; i++) if (strcmp(liquid[i].label, "Si0.25OH") == 0) { nSiOH = i; break; }
    if ( (nH2O == -1) || (nSiOH == -1) ) { 
      printf("...failure to find index for both H2O and Si0.25OH.\n"); 
    } else {
      for (i=0, k=0; i<(nls-1); i++) for (j=i+1; j<nls; j++) {
        if ( (i == nSiOH) && (j != nH2O ) ) equivH2O[k] = indIJ[nH2O][j];
	if ( (i != nH2O ) && (j == nSiOH) ) equivH2O[k] = indIJ[i][nH2O];
	k++;  
      }
      equivH2O[nls*(nls-1)/2+nSiOH] =  nls*(nls-1)/2+nH2O;
    }
    
    free_imatrix(indIJ, 0, nls-1, 0, nls-1);
  }
  
  for (i=0; i<p; i++) {
    if      (ui[i] <   (nls*(nls-1)/2 + nls)) modelParameters[ui[i]                        ].enthalpy = x[i]*SCALE;
    else if (ui[i] < 2*(nls*(nls-1)/2 + nls)) modelParameters[ui[i]-  (nls*(nls-1)/2 + nls)].entropy  = x[i];
    else if (ui[i] < 3*(nls*(nls-1)/2 + nls)) modelParameters[ui[i]-2*(nls*(nls-1)/2 + nls)].volume   = x[i];
  }
  for (i=0; i<(nls*(nls-1)/2 + nls); i++) if (modelParameters[i].activeF)
    modelParameters[i].enthalpy = ((i < (nls*(nls-1)/2)) ? 1473.15 : (liquid[i-(nls*(nls-1)/2)].liq).tfus) * modelParameters[i].entropy;
  
  /* Special constraint on water: thermo prop correction is Si(1/4)OH = H2O/2 */ 
  if ( (nH2O != -1) && (nSiOH != -1) ) for (i=0; i<(nls*(nls-1)/2+nls); i++) if ( (equivH2O[i] != -1) && modelParameters[equivH2O[i]].activeH )
      modelParameters[i].enthalpy = modelParameters[equivH2O[i]].enthalpy/2.0 + 1.0; /* the 1.0 is a kludge */
  
  /* Save the Jocobian from the previous call for potential use by calcj; store current Jocobian for potential use by calcj */
  lastNf = currentNf; currentNf = nf; for (i=0; i<(n*p); i++) { ur[i] = ur[n*p + i]; ur[n*p + i] = 0.0; }

  for (index=0; index<n; index++) {
    int    sID = iData[index]; /* solid index number  */
    int    lID = lData[index]; /* liquid index number */
    int j;
    
    r[index] = bData[index];
    if (fmod((double) index, (double) increment) == 0.0) { printf("*"); fflush(stdout); }
    
    if (lastLiqID != lID) {
      for (j=0; j<(nls*(nls-1)/2 + nls); j++) if (modelParameters[j].activeF) modelParameters[j].activeH  = TRUE;
      
      if ( (nH2O != -1) && (nSiOH != -1) ) 
        for (j=0; j<(nls*(nls-1)/2+nls); j++) if(equivH2O[j] != -1 && modelParameters[equivH2O[j]].activeH) modelParameters[j].activeH  = TRUE;

      actLiq (SECOND | FOURTH, tData[index], pData[index], aData[lID], NULL, mu, NULL, dmudw);
      
      for (j=0; j<(nls*(nls-1)/2 + nls); j++) if (modelParameters[j].activeF) {
        double tFus = (j < (nls*(nls-1)/2)) ? 1473.15 : (liquid[j-(nls*(nls-1)/2)].liq).tfus;
	modelParameters[j].activeH  = FALSE;
        for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls) + j] += tFus*dmudw[i][j];
      }
      
      if ( (nH2O != -1) && (nSiOH != -1) ) 
        for (j=0; j<(nls*(nls-1)/2+nls); j++) if ( (equivH2O[j] != -1) && modelParameters[equivH2O[j]].activeH ) {
          modelParameters[j].activeH  = FALSE;
	  for (i=0; i<nlc; i++) dmudw[i][equivH2O[j]] += dmudw[i][j]/2.0;
        }
      lastLiqID = lID;
    }
 
    if(testLiq (SEVENTH, tData[index], pData[index], 0, 0, NULL, NULL, NULL,  NULL)) { /* Ordering state convergence verified */
      if (sID < npc) {
  	for (i=0; i<nlc; i++) if (solids[sID].solToLiq[i] != 0.0) {
	  int k = 0;
  	  r[index] -= (solids[sID].solToLiq[i])*mu[i]/SCALE;
  	  for (j=0; j<(nls*(nls-1)/2 + nls); j++) {
  	    if (modelParameters[j].activeH) ur[n*p + index + n*(k++)] -= (solids[sID].solToLiq[i])*dmudw[i][			      j]*SCALE/SCALE;
  	    if (modelParameters[j].activeS) ur[n*p + index + n*(k++)] -= (solids[sID].solToLiq[i])*dmudw[i][  (nls*(nls-1)/2 + nls) + j]/SCALE;
  	    if (modelParameters[j].activeV) ur[n*p + index + n*(k++)] -= (solids[sID].solToLiq[i])*dmudw[i][2*(nls*(nls-1)/2 + nls) + j]/SCALE;
  	  }
  	}
      } else {
  	for (i=0; i<nlc; i++) if (extraSolids[sID-npc].solToLiq[i] != 0.0) {
	  int k = 0;
  	  r[index] -= (extraSolids[sID-npc].solToLiq[i])*mu[i]/SCALE;
  	  for (j=0; j<(nls*(nls-1)/2 + nls); j++) {
  	    if (modelParameters[j].activeH) ur[n*p + index + n*(k++)] -= (extraSolids[sID-npc].solToLiq[i])*dmudw[i][			       j]*SCALE/SCALE;
  	    if (modelParameters[j].activeS) ur[n*p + index + n*(k++)] -= (extraSolids[sID-npc].solToLiq[i])*dmudw[i][  (nls*(nls-1)/2 + nls) + j]/SCALE;
  	    if (modelParameters[j].activeV) ur[n*p + index + n*(k++)] -= (extraSolids[sID-npc].solToLiq[i])*dmudw[i][2*(nls*(nls-1)/2 + nls) + j]/SCALE;
  	  }
  	}
      }
    } else {  /* otherwise, ordering failed and mu and dmudw are incorrect; restore state and exit */
      *pt_nf = 0;
      currentNf = lastNf; for (i=0; i<n*p; i++) ur[n*p + i] = ur[i];  
      break; /* out of index loop */ 
    }
 
    residual[index] = -r[index];
    sumOfSquares   += r[index]*r[index];
  }
  if (index == n) {
    printf(" SS = %g\n", sumOfSquares);
#ifdef GRACE_PIPE
    GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, (double) nf, sumOfSquares);
    GracePrintf("WITH G0\n"); GracePrintf("AUTOSCALE\n");
    for (i=0; i<p; i++) GracePrintf("g1.s%1.1d POINT %lf, %lf\n", i, (double) nf, x[i]);
    GracePrintf("WITH G1\n"); GracePrintf("AUTOSCALE\n");
    GracePrintf("REDRAW\n");
#endif /* GRACE_PIPE */
  }
  
  return(0);
}

int calcj(/* Jacobian routine required by dn2gb                                    */
  integer    *pt_n,  /* nuumber of observations                                    */
  integer    *pt_p,  /* number of parameters                                       */
  doublereal *x,     /* current parameter guess                                    */
  integer    *pt_nf, /* invocation count for calcr; set to 0 if x is infeasible    */
  doublereal *j,     /* FORTRAN: J(N,P), j[1:n(p=0), 1:n(p=1), ...., (1:n)(p)]     */
  integer    *ui,    /* passed via dn2gb                                           */
  doublereal *ur,    /* passed via dn2gb                                           */
  U_fp       uf      /* passed via dn2gb                                           */
 ) {
  int n = (int) *pt_n, p = (int) *pt_p, nf = (int) *pt_nf, offset, i;
  
  printf("Entering CALCJ with nf = %5.5d\n", nf);
  
  if      (nf == lastNf)    offset = 0;
  else if (nf == currentNf) offset = n*p;
  else {
    printf("calcj called with nf = %d, stored values are %d and %d.  Setting nf = 0 and exiting.\n", nf, lastNf, currentNf);
    *pt_nf = 0;
    return(0);
  }
  
  for (i=0; i<(n*p); i++) j[i] = ur[offset + i];  
  return(0);
}

int ufparm(void) { return(0);} /* User routine required by dn2gb                           */

static int funcEvals;

static int funcCalibration(double x, double *a, double *y, double *dyda, int ma) {
  int  index = (int) x;      /* equation number     */
  int    sID = iData[index]; /* solid index number  */
  int    lID = lData[index]; /* liquid index number */
  double   t = tData[index]; /* t (K)		    */
  double   p = pData[index]; /* p (bars)	    */
  double   b = bData[index]; /* mu solid component  */
  double  *r = aData[lID];   /* r vector for liquid */

  static double *mu, **dmudw, *shadow, lastLiqID = -1;
  int i, j, update = FALSE;
  
  funcEvals++;
  if (mu == NULL) { 
    mu     = vector(0, nlc-1); 
    dmudw  = matrix(0, nlc-1, 0, 3*(nls*(nls-1)/2 + nls)-1);
    shadow = vector(1, 3*(nls*(nls-1)/2 + nls));
    for (i=1; i<=(3*(nls*(nls-1)/2 + nls)); i++) shadow[i] = -123456789.0; 
  }
  
  /* Bound constraints */
  /* for (i=0; i<(nls*(nls-1)/2); i++) if (modelParameters[i].activeH && (a[i+1] < 0.0)) return (0); */ 
   
  for (i=1; i<=(3*(nls*(nls-1)/2 + nls)); i++) if (shadow[i] != a[i]) { shadow[i] = a[i]; update = TRUE; }
  
  if (update) for (i=0; i<(nls*(nls-1)/2 + nls); i++) {
    if (modelParameters[i].activeH) modelParameters[i].enthalpy = a[			      i + 1]*SCALE;
    if (modelParameters[i].activeS) modelParameters[i].entropy  = a[  (nls*(nls-1)/2 + nls) + i + 1];
    if (modelParameters[i].activeV) modelParameters[i].volume	= a[2*(nls*(nls-1)/2 + nls) + i + 1];
  }
  
  update |= (lastLiqID != lID);
  if (update) { 
    for (i=0; i<(nls*(nls-1)/2 + nls); i++) if (modelParameters[i].activeF) {
      double tFus = (i < (nls*(nls-1)/2)) ? 1473.15 : (liquid[i-(nls*(nls-1)/2)].liq).tfus;
      modelParameters[i].activeH  = TRUE;
      modelParameters[i].enthalpy = tFus*a[(nls*(nls-1)/2 + nls) + i + 1];
    }
    
    actLiq (SECOND | FOURTH, t, p, r, NULL, mu, NULL, dmudw);
    lastLiqID = lID; 
    
    for (j=0; j<(nls*(nls-1)/2 + nls); j++) if (modelParameters[j].activeF) {
      double tFus = (j < (nls*(nls-1)/2)) ? 1473.15 : (liquid[j-(nls*(nls-1)/2)].liq).tfus;
      modelParameters[j].activeH  = FALSE;
      for (i=0; i<nlc; i++) dmudw[i][(nls*(nls-1)/2 + nls) + j] += tFus*dmudw[i][j];
    }
  }
   
  *y = 0.0;
  if (dyda != NULL) for (i=1; i<=3*(nls*(nls-1)/2 + nls); i++) dyda[i] = 0.0;

  if(testLiq (SEVENTH, t, p, 0, 0, NULL, NULL, NULL,  NULL)) { /* Ordering state convergence verified */
    if (sID < npc) {
      for (i=0; i<nlc; i++) if (solids[sID].solToLiq[i] != 0.0) {
  	*y	+= (solids[sID].solToLiq[i])*mu[i]/SCALE;
  	if (dyda != NULL) for (j=0; j<(nls*(nls-1)/2 + nls); j++) {
  	  if (modelParameters[j].activeH) dyda[ 			 j + 1] += (solids[sID].solToLiq[i])*dmudw[i][  			j]*SCALE/SCALE;
  	  if (modelParameters[j].activeS) dyda[  (nls*(nls-1)/2 + nls) + j + 1] += (solids[sID].solToLiq[i])*dmudw[i][  (nls*(nls-1)/2 + nls) + j]/SCALE;
  	  if (modelParameters[j].activeV) dyda[2*(nls*(nls-1)/2 + nls) + j + 1] += (solids[sID].solToLiq[i])*dmudw[i][2*(nls*(nls-1)/2 + nls) + j]/SCALE;
  	}
      }
    } else {
      for (i=0; i<nlc; i++) if (extraSolids[sID-npc].solToLiq[i] != 0.0) {
  	*y	+= (extraSolids[sID-npc].solToLiq[i])*mu[i]/SCALE;
  	if (dyda != NULL) for (j=0; j<(nls*(nls-1)/2 + nls); j++) {
  	  if (modelParameters[j].activeH) dyda[ 			 j + 1] += (extraSolids[sID-npc].solToLiq[i])*dmudw[i][ 			j]*SCALE/SCALE;
  	  if (modelParameters[j].activeS) dyda[  (nls*(nls-1)/2 + nls) + j + 1] += (extraSolids[sID-npc].solToLiq[i])*dmudw[i][  (nls*(nls-1)/2 + nls) + j]/SCALE;
  	  if (modelParameters[j].activeV) dyda[2*(nls*(nls-1)/2 + nls) + j + 1] += (extraSolids[sID-npc].solToLiq[i])*dmudw[i][2*(nls*(nls-1)/2 + nls) + j]/SCALE;
  	}
      }
    }
  } else return (0); /* otherwise, ordering failed and mu and dmudw are incorrect */
    
  residual[index] = *y - b;
  printf("Liq %4.4d, %15.15s, t = %10.2f C, P = %10.3f kbars, res = %13.6g kJ\n",lID, (sID < npc) ? solids[sID].label : extraSolids[sID-npc].species, 
    t-273.15, p/1000.0, residual[index]);
    
  return (1);   
}

/* Modified from Numerical Recipes mrqmin routine (v 2.0) */

static void mrqcofWithBounds(double x[], double y[], double sig[], int ndata, double a[], int ia[],
  int ma, double **alpha, double beta[], double *chisq,
  int (*funcs)(double, double [], double *, double [], int))
{
  int i, j, k, l, m, mfit=0;
  double ymod, wt, sig2i, dy, *dyda;

  dyda = vector(1, ma);
  for (j=1; j<=ma; j++) if (ia[j]) mfit++;
  for (j=1; j<=mfit; j++) {
    for (k=1; k<=j; k++) alpha[j][k] = 0.0;
    beta[j] = 0.0;
  }
  
  *chisq = 0.0;
  for (i=1; i<=ndata; i++) {
    if (!(*funcs)(x[i], a, &ymod, dyda, ma)) { *chisq = DBL_MAX; break; }
    sig2i = 1.0/(sig[i]*sig[i]);
    dy = y[i] - ymod;
    for (j=0, l=1; l<=ma; l++) {
      if (ia[l]) {
        wt = dyda[l]*sig2i;
        for (j++,k=0,m=1;m<=l;m++) if (ia[m]) alpha[j][++k] += wt*dyda[m];
        beta[j] += dy*wt;
      }
    }
    *chisq += dy*dy*sig2i;
  }
  for (j=2; j<=mfit; j++) for (k=1; k<j; k++) alpha[k][j] = alpha[j][k];
  free_vector(dyda, 1, ma);
}

static void mrqminWithSVA(double x[], double y[], double sig[], int ndata, double a[], int ia[],
  int ma, double **covar, double **alpha, double *chisq,
  int (*funcs)(double, double [], double *, double [], int), double *alamda)
{
  int i, j, k, l, m, rank;
  double wMin, wMax;
  
  static char valueI[] = { "      " };               /*  6 */
  static char valueD[] = { "                    " }; /* 20 */
  static XmString  valueCS  = NULL;
  
  static int mfit, graphSet=0;
  static unsigned long *key;
  static double ochisq, *atry, *beta, *da, *wSVA, **vSVA;
  static char *eSVA;

  Arg arg_set[20];

  if (*alamda < 0.0) {
    atry = vector(1, ma);
    beta = vector(1, ma);
    da   = vector(1, ma);
    for (mfit=0,j=1; j<=ma; j++) if (ia[j]) mfit++;
    wSVA = vector(1, mfit);
    vSVA = matrix(1, mfit, 1, mfit);
    eSVA = (char *) malloc((size_t) (mfit+1)*sizeof(char));
    key  = (unsigned long *) malloc((size_t) (mfit+1)*sizeof(unsigned long));
    for (j=1; j<=mfit; j++) eSVA[j] = '1';
    *alamda = 0.001;
    mrqcofWithBounds(x, y, sig, ndata, a, ia, ma, alpha, beta, chisq, funcs);
    ochisq = (*chisq);
    for (j=1; j<=ma; j++) atry[j] = a[j];
  }
  for (j=0,l=1; l<=ma; l++) {
    if (ia[l]) {
      for (j++,k=0,m=1; m<=ma; m++) {
        if (ia[m]) {
          k++;
          covar[j][k]=alpha[j][k];
        }
      }
      covar[j][j] = alpha[j][j]*(1.0+(*alamda));
    }
  }
  /* Original call to gaussj(covar,mfit,oneda,1); removed (oneda[j][1] = beta[j]) */
  svdcmp(covar, mfit, mfit, wSVA, vSVA);
  
  indexx(mfit, wSVA, key);
#ifdef GRACE_PIPE
  GracePrintf("WITH G2\n"); graphSet++;
  if (graphSet > 1) GracePrintf("KILL g2.s1\n");
  for (j=1; j<=mfit; j++) GracePrintf("g2.s%d POINT %lf, %g\n", 1, (double) j, (wSVA[key[mfit+1-j]] > 0.0) ? wSVA[key[mfit+1-j]] : DBL_EPSILON);
  GracePrintf("AUTOSCALE\n");
  
  GracePrintf("WITH G3\n");
  if (graphSet == 1) {
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, (double ) (mfit+1), 1.0);
    GracePrintf("XAXIS TICK MAJOR 1.0\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS TICK MAJOR 0.2\n");
    GracePrintf("YAXIS TICK MINOR 0.1\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS TICK MINOR OFF\n");

    for (j=1, k=0; j<=ma; j++) if (ia[j]) {
      k++;
      GracePrintf("WITH STRING\n");
      GracePrintf("STRING ON\n");
      GracePrintf("STRING LOCTYPE VIEW\n");
      GracePrintf("STRING LINEWIDTH 1\n");
      GracePrintf("STRING ROT 0\n");
      GracePrintf("STRING FONT 4\n");
      GracePrintf("STRING JUST 0\n");
      GracePrintf("STRING CHAR SIZE 0.5\n");
      GracePrintf("STRING 0.86, %lf\n", 1.0 - ((double) k)/(mfit+1.0));
      GracePrintf("STRING COLOR %d\n", k - (int) (14 * floor(((double) k)/14.0)));
      GracePrintf("STRING DEF \"%1.1s %18.18s\"\n", (j < (nls+nls*(nls-1)/2+1)) ? "H" : "S",
        (j < (nls+nls*(nls-1)/2+1)) ? modelParameters[j-1].label : modelParameters[j-nls-nls*(nls-1)/2-1].label);
    }
    
    GracePrintf("G3 ON\n");

  } else { for (k=1; k<=mfit; k++) GracePrintf("KILL g3.s%d\n", k); }
  for (k=1; k<=mfit; k++) {  
    GracePrintf("s%d TYPE BAR\n", k);
    for (j=1; j<=mfit; j++) GracePrintf("g3.s%d POINT %lf, %lf\n", k, (double) j, vSVA[k][key[mfit+1-j]]*vSVA[k][key[mfit+1-j]]);
    GracePrintf("s%d SYMBOL COLOR %d\n",      k, k - (int) (14 * floor(((double) k)/14.0)));
    GracePrintf("s%d SYMBOL FILL COLOR %d\n", k, k - (int) (14 * floor(((double) k)/14.0)));
    if (k < 15) GracePrintf("s%d SYMBOL FILL PATTERN 1\n", k);
    else        GracePrintf("s%d SYMBOL FILL PATTERN 10\n", k);
    GracePrintf("s%d LINE TYPE 0\n", k);
  }
   
  GracePrintf("REDRAW\n");
#endif /* GRACE_PIPE */
  
  for (wMax=0.0, j=1; j<=mfit; j++) if (wSVA[j] > wMax) wMax = wSVA[j];
  wMin = wMax*10.0*DBL_EPSILON;
  for (j=1, rank=mfit; j<=mfit; j++) {
    printf("--->w: %20.13e (wMin: %20.13e, wMax: %20.13e)\n", wSVA[j], wMin, wMax);
    if (wSVA[j] < wMin) { wSVA[j] = 0.0; rank--; }
  }
  printf("--->In mrqmin (with SVA) computed rank is %d\n", rank);

  DISPLAYI(mrqrdtADB[2], mfit) 
  DISPLAYI(mrqrdtADB[3], rank) 
  DISPLAYD(mrqrdtADB[5], wMax) 
  DISPLAYD(mrqrdtADB[6], wSVA[key[1]])
  DISPLAYD(mrqrdtADB[7], wMin)
  
  svbksb(covar, wSVA, vSVA, mfit, mfit, beta, eSVA, da);
  
  if (*alamda == 0.0) {
    svdvar(vSVA, mfit, wSVA, covar);
    covsrt(covar, ma, ia, mfit);
    free_vector(da,   1, ma);
    free_vector(beta, 1, ma);
    free_vector(atry, 1, ma);
    free_vector(wSVA, 1, mfit);
    free_matrix(vSVA, 1, mfit, 1, mfit);
    free(eSVA);
    free(key);
    return;
  }
  for (j=0,l=1; l<=ma; l++) if (ia[l]) atry[l] = a[l] + da[++j];
  mrqcofWithBounds(x, y, sig, ndata, atry, ia, ma, covar, da, chisq, funcs);
  if (*chisq < ochisq) {
    *alamda *= 0.1;
    ochisq = (*chisq);
    for (j=0,l=1; l<=ma; l++) {
      if (ia[l]) {
        for (j++,k=0,m=1; m<=ma; m++) {
          if (ia[m]) {
            k++;
            alpha[j][k] = covar[j][k];
          }
        }
        beta[j] = da[j];
        a[l] = atry[l];
      }
    }
  } else {
    *alamda *= 10.0;
    *chisq = ochisq;
  }
}


/*************************************************************************************/
/*===================================================================================*/
/*************************************************************************************/

Boolean preclb(XtPointer client_data)
{
  static const char *database = "database.dat";
  static char entry[]    = { "          \0" };
  static char value[]    = { "     " };                /*  5 */
  static char valueI[]   = { "      " };               /*  6 */
  static char valueD[]   = { "                    " }; /* 20 */
  static XmString  valueCS  = NULL, cstring1 = NULL, cstring2 = NULL, cstring3 = NULL;
  static FILE *input = NULL;

  /* Variables and definitions dependent on database structure */
  static char    line[REC];
  static int     nEqnMAX, nLiquid, nLiquidMAX, ma, *iaMrqrdt, loop, o2Index; 
  static Boolean lowPonly, highPonly, anhydrousOnly, hydrousOnly, calibrateOxygen, useTrustRegionMethod, implementBounds;
  static Boolean *lowWtFlag, *zeroWtFlag, *phasesPresent, validLiquid=FALSE;
  static double  molesElmSol[107], *molesLiqCmp, *moles, *indep, *activity, *xMrqrdt, *yMrqrdt, *sigMrqrdt, *aMrqrdt, **covar, **alpha, 
                 chisq, alamda, oldChisq, oldAlamda, t, p, logfo2, *sigWeights;

  enum steps { INITIAL, READING, PREREGRESS, REGRESS, POSTREGRESS, SOLUTION, FINAL };
  static int curStep = 0;

  WorkProcData *workProcData = (WorkProcData *) client_data;

  int i, j, k, l, id, len;
  double wt[24], dummy;
  Arg arg_set[20];

  switch(curStep) {

/*=============================================================================
 * If the work procedure is being called for the first time, the data file
 * must be opened and some initialization of global and static variables 
 * must take place.
 *===========================================================================*/

  case INITIAL:

  if (input == NULL) { 
    /* 1-> attempt to open the data file */ 
    if (alternateDataBase == (char *) NULL) {
      if ((input = fopen (database, "r")) == NULL) { 
        ABORT("Failure to open file DATABASE.DAT.\n", "Exiting PRECLB procedure.")
        workProcData->active = FALSE; return TRUE;
      }
      /* 2-> notify user of impending action */
      DISPLAY(actionADB[0], "Processing data from file: DATABASE.DAT")
    } else {
      if ((input = fopen (alternateDataBase, "r")) == NULL) { ABORT("Failure to open <alt> database file.\n", "Exiting PRECLB procedure.")
        workProcData->active = FALSE; return TRUE;
      }
      /* 2-> notify user of impending action */
      DISPLAY(actionADB[0], "Processing data from alternate data base file.")
    }

    /* 3 -> allocate space and initialize for static arrays */
    if (molesLiqCmp   == NULL) molesLiqCmp   = (double *)  malloc((size_t) nlc*sizeof(double)); 
    if (lowWtFlag     == NULL) lowWtFlag     = (Boolean *) malloc((size_t)  nc*sizeof(Boolean)); 
    if (zeroWtFlag    == NULL) zeroWtFlag    = (Boolean *) malloc((size_t)  nc*sizeof(Boolean)); 
    if (phasesPresent == NULL) phasesPresent = (Boolean *) malloc((size_t) npc*sizeof(Boolean));
    for (i=0; i<npc; i++) { phasesPresent[i] = TRUE; preclbCount[i].np = 0; preclbCount[i].na = 0; }

    /* 4a -> compute maximal number of endmembers in any known solid solution, 
             and allocate an appropriate vectors for comp and activities     */
    for (i=0, j=1; i<npc; i++) j = MAX(j, solids[i].na);
    if (moles    == NULL) moles    = (double *) malloc((size_t) j*sizeof(double));
    if (activity == NULL) activity = (double *) malloc((size_t) j*sizeof(double));

    /* 4b -> compute maximal number of independent compositional variables in
             any known solid solution, and allocate an appropriate vector    */
    for (i=0, j=1; i<npc; i++) j = MAX(j, solids[i].nr);
    if (indep == NULL) indep = (double *) malloc((size_t) j*sizeof(double));

    /* 4c -> Get Pressure exclusion options                                  */
    lowPonly  = XmToggleButtonGadgetGetState(tg_low_p_only);
    if (lowPonly) printf("High P experiments will be excluded.\n");
    highPonly = XmToggleButtonGadgetGetState(tg_high_p_only);
    if (highPonly) printf("Low P experiments will be excluded.\n");

    /* 4d -> Get hydrous/anhydrous exclusion options                         */
    anhydrousOnly = XmToggleButtonGadgetGetState(tg_anhydrous_only);
    if (anhydrousOnly) printf("Hydrous experiments will be excluded.\n");
    hydrousOnly = XmToggleButtonGadgetGetState(tg_hydrous_only);
    if (hydrousOnly) printf("Anhydrous experiments will be excluded.\n");
    
    /* 4e -> Get oxygen constraint calibration option                       */
    if((calibrateOxygen = XmToggleButtonGadgetGetState(tg_oxygen_calib))) {
      for (j=0, o2Index = -1; j<npc; j++) if ((solids[j].type == PHASE) && !strcmp(solids[j].label, "o2")) { o2Index = j; break; }
      if (o2Index == -1) calibrateOxygen = FALSE;
      if (calibrateOxygen) printf("O2 chemical potential calibration statements will be excluded.\n");
    }
    
    /* 4f -> Get Regression method and constraint settings                  */
    useTrustRegionMethod = XmToggleButtonGadgetGetState(tg_trust_region_method);
    if (useTrustRegionMethod) printf("Regression method set to Trust Region algorithm.\n");
    implementBounds = XmToggleButtonGadgetGetState(tg_implement_bounds);
    if (implementBounds) printf("Bounds on W(H) parameters will be implemented.\n");

    /* 5a -> compute number of moles of elements in each solid              */
    sigWeights = (double *) calloc((size_t) (npc+nes), sizeof(double));
    for (i=0; i<npc; i++) for (j=0; j<107; j++) for (k=0; k<nc; k++) sigWeights[i] += (solids[i].solToOx)[k]*(bulkSystem[k].oxToElm)[j];

    /* 5b -> parse and determine conversion vectors for extra solid species */
    for(i=0; i<nes; i++) {
      extraSolids[i].index = -1;
      for (j=0; j<npc; j++) if ((solids[j].type == PHASE) && (solids[j].convert != NULL) && !strcmp(solids[j].label, extraSolids[i].phase)) { 
        extraSolids[i].index = j; break; 
      }
      if (extraSolids[i].index != -1) {
        for (j=0; j<107; j++) molesElmSol[j] = 0.0;
        (void) formulaToMwStoich(extraSolids[i].formula, molesElmSol);
        extraSolids[i].oxygen = molesElmSol[8]; 		   /* moles of oxygen	*/
        for (j=0; j<107; j++) sigWeights[npc+i] += molesElmSol[j]; /* moles of elements */
 
        extraSolids[i].m = (double *) malloc((size_t) (solids[extraSolids[i].index].na)*sizeof(double));
        (*solids[extraSolids[i].index].convert) (FIRST, SECOND, 1000.0, 1.0, molesElmSol, extraSolids[i].m, NULL, NULL, NULL, NULL, NULL, NULL);
        extraSolids[i].solToLiq = (double *) calloc((size_t) nlc, sizeof(double));
        for (j=0, extraSolids[i].norm=0.0; j<solids[extraSolids[i].index].na; j++) {
          extraSolids[i].norm += pow((extraSolids[i].m)[j], (double) 2.0);
      	  for (k=0; k<nlc; k++) (extraSolids[i].solToLiq)[k] += (extraSolids[i].m)[j]*(solids[extraSolids[i].index+1+j].solToLiq)[k];
        }
 
        printf("%s %s moles: ", extraSolids[i].phase, extraSolids[i].species);
        for (j=0; j<solids[extraSolids[i].index].na; j++) {
          if (fabs((extraSolids[i].m)[j]) < sqrt(DBL_EPSILON)) (extraSolids[i].m)[j] = 0.0;
          printf("%6.3f ", (extraSolids[i].m)[j]);
        }
        printf("\n solToLiq: ");
        for (j=0; j<nlc; j++) {
          if(fabs((extraSolids[i].solToLiq)[j]) < sqrt(DBL_EPSILON)) (extraSolids[i].solToLiq)[j] = 0.0;
          printf("%6.3f ", (extraSolids[i].solToLiq)[j]);
        }
        printf("\n");
      }
    }
     
    /* 6-> initialize remaining statics, and set initial size of arrays */
    nEqn = 0;
    nEqnMAX    = 100; 
    nLiquidMAX = 100;
    aData   = (double **) REALLOC((void *) aData,   (size_t) nLiquidMAX*sizeof(double *));
    for (i=0; i<nLiquidMAX; i++) aData[i] = (double *) malloc((size_t) (nlc-1)*sizeof(double));
    bData   = (double *)  REALLOC((void *) bData,   (size_t) nEqnMAX*sizeof(double));
    fo2Data = (double *)  REALLOC((void *) fo2Data, (size_t) nEqnMAX*sizeof(double));
    iData   = (int *)     REALLOC((void *) iData,   (size_t) nEqnMAX*sizeof(int));
    jData   = (int *)     REALLOC((void *) jData,   (size_t) nEqnMAX*sizeof(int));
    lData   = (int *)     REALLOC((void *) lData,   (size_t) nEqnMAX*sizeof(int));
    pData   = (double *)  REALLOC((void *) pData,   (size_t) nEqnMAX*sizeof(double));
    tData   = (double *)  REALLOC((void *) tData,   (size_t) nEqnMAX*sizeof(double));
    zData   = (Boolean *) REALLOC((void *) zData,   (size_t) nEqnMAX*sizeof(Boolean));
    nLiquid = 0;

  }

  curStep++;
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Continue reading and processing the data file:
 *===========================================================================*/

  case READING:

  if (fgets(line, REC, input) != NULL) {

    len = strlen(line); for (i=0; i<len; i++) line[i] = tolower(line[i]);
    
    /* Liquid entry: Title / t, p log fo2 / 8 wt % / 8 wt %                  */
    if (line[0] != '$') {

      for (j=0; j<npc; j++) {
        if (!phasesPresent[j] && preclbCount[j].absPhase) {
          double deltaG;

          if (validLiquid &&
	      ((lowPonly && (p < 2.0)) || !lowPonly) && ((highPonly && (p > 2.0)) || !highPonly) &&
	      ((anhydrousOnly && (molesLiqCmp[18] == 0.0)) || !anhydrousOnly) && ((hydrousOnly && (molesLiqCmp[18] > 0.0)) || !hydrousOnly)	   
	     ) {

            if (solids[j].convert == NULL) {
              if(getDeltaGofSolid(&deltaG, molesLiqCmp, t, p, zeroWtFlag, (double) 1.0, j)) { 
                preclbCount[j].na++;
                sprintf(value, "%5.5d", preclbCount[j].na);
                DISPLAY(preclbCount[j].absent, value)
                nEqn++;
                TESTnEQN
                bData[nEqn-1]   = deltaG/SCALE;
                fo2Data[nEqn-1] = logfo2;
                iData[nEqn-1]   = j;
                jData[nEqn-1]   = j;
                lData[nEqn-1]   = nLiquid;
                pData[nEqn-1]   = p;
                tData[nEqn-1]   = t;
                zData[nEqn-1]   = FALSE;
              }
            } else if (solids[j].convert != NULL) {
              for (k=0, l=0; k<solids[j].na; k++) {
                if(getDeltaGofSolid(&deltaG, molesLiqCmp, t, p, zeroWtFlag, (double) 1.0, j+1+k)) { 
                  nEqn++;
                  TESTnEQN
                  bData[nEqn-1]   = deltaG/SCALE;
                  fo2Data[nEqn-1] = logfo2;
                  iData[nEqn-1]   = j+1+k;
                  jData[nEqn-1]   = j;
                  lData[nEqn-1]   = nLiquid;
                  pData[nEqn-1]   = p;
                  tData[nEqn-1]   = t;
                  zData[nEqn-1]   = FALSE;
                  l++;
                }
              }
              if (l > 0) {
                preclbCount[j].na++;
                sprintf(value, "%5.5d", preclbCount[j].na);
                DISPLAY(preclbCount[j].absent, value)
              }
            }
          
          }
          
        }
        phasesPresent[j] = FALSE;
      }

      for (i=0; i<len; i++) { if (line[i] == '\n') line[i] = ' '; }
      DISPLAY(actionADB[1], line)

      GETNEWLINE
      if (sscanf(line, "%lf %lf %lf", &t, &p, &logfo2) == EOF) {
        ABORT("Illegal numeric value in datafile, offending record:\n", line)
        workProcData->active = FALSE; return TRUE; 
      }

      GETNEWLINE
      PARSELINE1

      GETNEWLINE
      PARSELINE2

      for (i=16; i<24; i++) wt[i] = 0.0;
      
      /* Convert wt % oxides to mole fractions of liquid components          */
      for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;
      conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL, NULL, NULL, &logfo2); /* FeO(T) -> Fe2O3, FeO */
      for (i=0; i<nc; i++)  lowWtFlag[i] = (wt[i]*bulkSystem[i].mw < 0.5);
      lowWtFlag[3] = (wt[3]*bulkSystem[3].mw < 0.1); /* Fe2O3 */
      lowWtFlag[4] = (wt[4]*bulkSystem[4].mw < 0.1); /* Cr2O3 */
      for (i=0; i<nc; i++) zeroWtFlag[i] = (wt[i] <= 0.0); 
      for (i=0; i<nlc; i++) for (j=0, molesLiqCmp[i]=0.0; j<nc; j++) molesLiqCmp[i] += wt[j]*(bulkSystem[j].oxToLiq)[i];

      if (testLiq(SIXTH, t, p, 0, 0, NULL, NULL, NULL, molesLiqCmp)) {
        static double *xSpecies;
	if (xSpecies == NULL) xSpecies = (double *) malloc((size_t) nls*sizeof(double));
        nLiquid++;
	TESTnLIQUID
        validLiquid = TRUE;
	conLiq(SECOND, THIRD,           t, p, NULL, molesLiqCmp, aData[nLiquid], NULL,     NULL, NULL, NULL);
	conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL,        aData[nLiquid], xSpecies, NULL, NULL, NULL);
	if (!testLiq(SEVENTH,0, 0, 0, 0, NULL, NULL, NULL, NULL)) { 
	  validLiquid = FALSE;
	  printf("-->Liquid %d fails ordering test.\n", nLiquid);
	  nLiquid--;
	} else {
	  double gTest;
	  gmixLiq(FIRST, t, p, aData[nLiquid], &gTest, NULL, NULL);
	  if (!testLiq(EIGHTH, 0, 0, 0, 0, NULL, NULL, NULL, NULL)) {
	    validLiquid = FALSE;
	    printf("-->Liquid %d causes failure (%d) in EOS algorithm.\n", nLiquid, liqERRstate);
	    nLiquid--;
          }
	}
      } else {
        validLiquid = FALSE;
        printf("-->Liquid %d fails validation test.\n", nLiquid);
      }
      
      /* Insert an equation for oxygen calibration */
      if (  validLiquid                                && 
            calibrateOxygen                            &&
            ((p < 2.0)                && !highPonly)   && 
            ((molesLiqCmp[18] == 0.0) && !hydrousOnly) 
	 ) {
        double deltaG;
        if(getDeltaGofSolid(&deltaG, molesLiqCmp, t, p, lowWtFlag, (double) 1.0, o2Index)) { 
              nEqn++;
              TESTnEQN
              bData[nEqn-1]   = (deltaG + R*t*log(10.0)*logfo2)/SCALE;
              fo2Data[nEqn-1] = logfo2;
              iData[nEqn-1]   = o2Index;
              jData[nEqn-1]   = o2Index;
              lData[nEqn-1]   = nLiquid;
              pData[nEqn-1]   = p;
              tData[nEqn-1]   = t;
              zData[nEqn-1]   = TRUE;
        }      
      }

    /* Solid entry: $NAME extra information / 8 wt % / 8 wt %                */
    } else {

      for (id=0; id<npc; id++) 
        if ( (solids[id].type == PHASE) &&  solids[id].inclInClb && (strncmp(solids[id].label, &line[1], strlen(solids[id].label)) == 0) ) break;

      if (id == npc) {
        ABORT("Illegal phase descriptor in data file: ", line)
        workProcData->active = FALSE; return TRUE;
      }

      GETNEWLINE
      PARSELINE1

      GETNEWLINE
      PARSELINE2
      
      for (i=16; i<24; i++) wt[i] = 0.0;

      if ( validLiquid &&
          ((lowPonly && (p < 2.0)) || !lowPonly) && ((highPonly && (p > 2.0)) || !highPonly) &&
          ((anhydrousOnly && (molesLiqCmp[18] == 0.0)) || !anhydrousOnly) && ((hydrousOnly && (molesLiqCmp[18] > 0.0)) || !hydrousOnly)
         ) {

        phasesPresent[id] = TRUE;
  
        preclbCount[id].np++;
        sprintf(value, "%5.5d", preclbCount[id].np);
        DISPLAY(preclbCount[id].present, value)

        /* Determine if phase data may be included */
        if (preclbCount[id].usePhase) {
          double deltaG;

          if (solids[id].convert != NULL) {
            /* Convert wt % oxides to moles of oxides */
            for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;
            /* Convert moles of oxides to moles of elements */
            for (i=0; i<107; i++) {
              molesElmSol[i] = 0.0;
              for (j=0; j<nc; j++) if ((bulkSystem[j].oxToElm)[i] != 0) molesElmSol[i] += ((double) (bulkSystem[j].oxToElm)[i])*wt[j];
            }
            /* Convert moles of elements to moles of endmember components     */
            (*solids[id].convert) (FIRST, SECOND, t, p, molesElmSol, moles, NULL, NULL, NULL, NULL, NULL, NULL);
	    
	    if ((*solids[id].test) (SIXTH, t, p, 0, 0, NULL, NULL, NULL, moles)) {

              /* Convert moles of endmember components to independent variables */
              (*solids[id].convert) (SECOND, THIRD, t, p, NULL, moles, indep, NULL, NULL, NULL, NULL, NULL);
              /* Compute activities of endmember components/exclude dilute comp */
              (*solids[id].activity) (FIRST | FOURTH, t, p, indep, activity, NULL, NULL);
              for (j=0; j<solids[id].na; j++) {
                if(getDeltaGofSolid(&deltaG, molesLiqCmp, t, p, lowWtFlag, activity[j], id+1+j)) {
                  nEqn++;
                  TESTnEQN
                  bData[nEqn-1]   = deltaG/SCALE;
                  fo2Data[nEqn-1] = logfo2;
                  iData[nEqn-1]   = id+1+j;
                  jData[nEqn-1]   = id;
                  lData[nEqn-1]   = nLiquid;
                  pData[nEqn-1]   = p;
                  tData[nEqn-1]   = t;
                  zData[nEqn-1]   = TRUE;
                }
              }
	    
	      /* dependent species used as regression constraints */
	      for (k=0; k<nes; k++) if (extraSolids[k].index == id) {
	        double sumMoles, newMoles = 0.0;
	        Boolean notSuitable = False;
	        for (j=0; j<solids[id].na; j++) newMoles += (extraSolids[k].m)[j]*moles[j];
	
	        newMoles = (extraSolids[k].norm > 0.0)   ? newMoles/extraSolids[k].norm 	: 0.0;
	        sumMoles = (extraSolids[k].oxygen > 0.0) ? molesElmSol[8]/extraSolids[k].oxygen : 0.0;
	
	        /* Exclusion criteria on mole fraction */
	        if ((sumMoles == 0.0) || (newMoles/sumMoles < extraSolids[k].threshold)) break;
	
	        for (j=0; j<solids[id].na; j++) if ( ((extraSolids[k].m)[j] != 0.0) &&
	          ((extraSolids[k].mLimits)[j] != 0.0) && (moles[j]/sumMoles < (extraSolids[k].mLimits)[j]) ) notSuitable = True;
                if (notSuitable) break;

                /* Compute activities of endmember components/do not exclude dilute comp */
                (*solids[id].activity) (FIRST, t, p, indep, activity, NULL, NULL);
	
                nEqn++;
                TESTnEQN
                bData[nEqn-1]	= 0.0;
                fo2Data[nEqn-1] = logfo2;
                iData[nEqn-1]	= npc+k;
                jData[nEqn-1]	= id;
                lData[nEqn-1]	= nLiquid;
                pData[nEqn-1]	= p;
                tData[nEqn-1]	= t;
                zData[nEqn-1]	= TRUE;
	
                for (j=0; j<solids[id].na; j++) {
                  if(getDeltaGofSolid(&deltaG, molesLiqCmp, t, p, lowWtFlag, activity[j], id+1+j)) {
                    bData[nEqn-1] += (extraSolids[k].m)[j]*deltaG/SCALE;
                  } else {
	    	    nEqn--;
	    	    break;
	    	  }
                }
	      }
	      
	    } else printf("-->Phase %s in liquid %d fails validation test.\n", solids[id].label, nLiquid);
	    
          } else {
            if(getDeltaGofSolid(&deltaG, molesLiqCmp, t, p, lowWtFlag, (double) 1.0, id)) { 
              nEqn++;
              TESTnEQN
              bData[nEqn-1]   = deltaG/SCALE;
              fo2Data[nEqn-1] = logfo2;
              iData[nEqn-1]   = id;
              jData[nEqn-1]   = id;
              lData[nEqn-1]   = nLiquid;
              pData[nEqn-1]   = p;
              tData[nEqn-1]   = t;
              zData[nEqn-1]   = TRUE;
            }
          }
  
        }
      
      }

    }
    workProcData->active = TRUE; 
    return FALSE;
  }

  DISPLAY(actionADB[1], "")
  if (useTrustRegionMethod) { DISPLAY(actionADB[0], "Processing of data file completed. initializing Trust Region Method analysis.") }
  else                      { DISPLAY(actionADB[0], "Processing of data file completed. initializing Marquardt analysis.") }

  curStep++;
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Redimension arrays, and setup Regression Analysis
 *===========================================================================*/

  case PREREGRESS: 

  fclose(input);
  input = NULL;

  free(molesLiqCmp);   molesLiqCmp   = NULL;
  free(lowWtFlag);     lowWtFlag     = NULL;
  free(zeroWtFlag);    zeroWtFlag    = NULL;
  free(phasesPresent); phasesPresent = NULL;
  free(moles);         moles         = NULL;
  free(indep);         indep         = NULL;
  free(activity);      activity      = NULL;

  aData   = (double **) REALLOC(aData,   (size_t) nLiquid*sizeof(double *));
  bData   = (double *)  REALLOC(bData,   (size_t) nEqn*sizeof(double));
  fo2Data = (double *)  REALLOC(fo2Data, (size_t) nEqn*sizeof(double));
  iData   = (int *)     REALLOC(iData,   (size_t) nEqn*sizeof(int));
  jData   = (int *)     REALLOC(jData,   (size_t) nEqn*sizeof(int));
  lData   = (int *)     REALLOC(lData,   (size_t) nEqn*sizeof(int));
  pData   = (double *)  REALLOC(pData,   (size_t) nEqn*sizeof(double));
  tData   = (double *)  REALLOC(tData,   (size_t) nEqn*sizeof(double));
  zData   = (Boolean *) REALLOC(zData,   (size_t) nEqn*sizeof(Boolean));

  residual  = vector(1, nEqn);

  if (useTrustRegionMethod) {

#ifdef GRACE_PIPE 
    GraceRegisterErrorFunction (grace_error_function);
    if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }
  
    GracePrintf("WITH G0\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.15, 0.10, 0.45, 0.90);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 1.0);

      GracePrintf("XAXIS TICK MAJOR 0.2\n");
      GracePrintf("XAXIS TICK MINOR 0.1\n");
      GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("XAXIS LABEL \"iterate\"\n");
      GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("XAXIS LABEL COLOR 2\n");

      GracePrintf("YAXIS TICK MAJOR 0.2\n");
      GracePrintf("YAXIS TICK MINOR 0.1\n");
      GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS LABEL \"Sum of Squares\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");
      
    GracePrintf("G0 ON\n");
 
    GracePrintf("WITH G1\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.60, 0.10, 0.90, 0.90);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 1.0);

      GracePrintf("XAXIS TICK MAJOR 0.2\n");
      GracePrintf("XAXIS TICK MINOR 0.1\n");
      GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("XAXIS LABEL \"iterate\"\n");
      GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("XAXIS LABEL COLOR 2\n");

      GracePrintf("YAXIS TICK MAJOR 0.2\n");
      GracePrintf("YAXIS TICK MINOR 0.1\n");
      GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS LABEL \"Parameters\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");
      
    GracePrintf("G1 ON\n");

    GracePrintf("REDRAW\n");
#endif /* GRACE_PIPE */
 
  } else { /* !useTrustRegionMethod */
    xMrqrdt   = vector(1, nEqn);
    yMrqrdt   = vector(1, nEqn);
    sigMrqrdt = vector(1, nEqn);
 
    for (i=0; i<nEqn; i++) {
      xMrqrdt[  i + 1] = (double) i;
      yMrqrdt[  i + 1] = bData[i];		    /* kJ					       */
      sigMrqrdt[i + 1] = sigWeights[iData[i]]/14.0; /* kJ - 7 atoms in molecule --> 0.5 kJ uncertainty */
    }
 
    ma = 3*(nls*(nls-1)/2 + nls);
    aMrqrdt  =  vector(1, ma);
    iaMrqrdt = ivector(1, ma);

    for (i=0; i<(nls*(nls-1)/2 + nls); i++) {
      aMrqrdt[  		      i + 1]	= modelParameters[i].enthalpy/SCALE;
      aMrqrdt[  (nls*(nls-1)/2 + nls)+i + 1]	= modelParameters[i].entropy;
      aMrqrdt[2*(nls*(nls-1)/2 + nls)+i + 1]	= modelParameters[i].volume;
      iaMrqrdt[ 			 i + 1] = modelParameters[i].activeH;
      iaMrqrdt[   nls + nls*(nls-1)/2  + i + 1] = modelParameters[i].activeS;
      iaMrqrdt[2*(nls + nls*(nls-1)/2) + i + 1] = modelParameters[i].activeV;
    }
 
    covar = matrix(1, ma, 1, ma);
    alpha = matrix(1, ma, 1, ma);
 
    alamda = -1.0;
 
    setModeToMixingLiq(FALSE);
    for (i=0, chisq=0.0; i<nEqn; i++) {
      if (!funcCalibration((double) i, aMrqrdt, &dummy, NULL, ma)) printf("Initial infeasibility in call to MRQRDT.\n");
      chisq += residual[i]*residual[i]/(sigMrqrdt[i+1]*sigMrqrdt[i+1]);
    }
    setModeToMixingLiq(TRUE);
 
#ifdef GRACE_PIPE
    GraceRegisterErrorFunction (grace_error_function);
    if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }
 
    GracePrintf("WITH G0\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.1, 0.4, 0.4);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, chisq);

      GracePrintf("XAXIS TICK MAJOR 5.0\n");
      GracePrintf("XAXIS TICK MINOR 1.0\n");
      GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("XAXIS LABEL \"iterate\"\n");
      GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("XAXIS LABEL COLOR 2\n");

      GracePrintf("YAXIS TICK MAJOR %lf\n", chisq/5.0);
      GracePrintf("YAXIS TICK MINOR %lf\n", chisq/10.0);
      GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS LABEL \"chi sqr\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");
      
    GracePrintf("G0 ON\n");
 
    GracePrintf("WITH G1\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.4, 0.40, 0.7);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, -9.0, 1.0, 1.0);

      GracePrintf("XAXIS TICK MAJOR 5.0\n");
      GracePrintf("XAXIS TICK MINOR 1.0\n");
      GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS TICK MAJOR 1.0\n");
      GracePrintf("YAXIS TICK MINOR 0.5\n");
      GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS LABEL \"log10 lambda\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");
      
    GracePrintf("G1 ON\n");

    GracePrintf("WITH G2\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1,  0.8, 0.40, 0.95);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0,  0.0, 10.0, 1.0);

      GracePrintf("XAXIS TICK MAJOR 2.0\n");
      GracePrintf("XAXIS TICK MINOR 1.0\n");
      GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("XAXIS LABEL \"rank\"\n");
      GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("XAXIS LABEL COLOR 2\n");

      GracePrintf("YAXIS TICK MAJOR 0.2\n");
      GracePrintf("YAXIS TICK MINOR 0.1\n");
      GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

      GracePrintf("YAXIS LABEL \"sing value\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");
      
    GracePrintf("G2 ON\n");

    GracePrintf("WITH G3\n");
      GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.50,  0.1, 0.85, 0.95);
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0,  0.0, 1.0, 1.0);

      GracePrintf("XAXIS LABEL \"V[*][->]\"\n");
      GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("XAXIS LABEL COLOR 2\n");
      
      GracePrintf("YAXIS LABEL \"V[->][*]\"\n");
      GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
      GracePrintf("YAXIS LABEL COLOR 2\n");

    GracePrintf("G3 ON\n");
    GracePrintf("G3 TYPE CHART\n");
    GracePrintf("G3 STACKED TRUE\n");

    GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, (double) 0, chisq);
    GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 1, (double) 0, -3.0);
    GracePrintf("REDRAW\n");
#endif /* GRACE_PIPE */
 
    loop   = 0;
    printf("Initial: chisq = %20.13g\n", chisq);
 
    DISPLAYI(mrqrdtADB[0], loop)
    DISPLAYI(mrqrdtADB[1], funcEvals)
    DISPLAYI(mrqrdtADB[4], nEqn)
    DISPLAYD(mrqrdtADB[8], chisq)
    DISPLAYD(mrqrdtADB[9], alamda)
 
    DISPLAY(actionADB[0], "Finished initializing Marquardt analysis. Execute to perfom an interation sequence")
  }
  
  curStep++;
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Perform a Trust Region Analysis or perform a Marquardt step
 *===========================================================================*/

  case REGRESS:
  
  if (useTrustRegionMethod) {
  
    integer n = (integer) nEqn, p = 0;
    
    for (i=0; i<(nls*(nls-1)/2 + nls); i++) { 
      if(modelParameters[i].activeH) p++;
      if(modelParameters[i].activeS) p++;
      if(modelParameters[i].activeV) p++;
    }    
    
    if ((n > 0) && (p > 0)) {
      integer    kind    = 1;
      integer    liv     = 82 + 4*p;
      integer    lv      = 105 + p*(n + 2*p + 21) + 2*n;
      integer    *iv     = (integer *)    malloc((size_t)     lv*sizeof(integer)); 
      integer    *uiparm = (integer *)    malloc((size_t)      p*sizeof(integer));
      doublereal *x      = (doublereal *) malloc((size_t)      p*sizeof(doublereal));  
      doublereal *b      = (doublereal *) malloc((size_t)    2*p*sizeof(doublereal)); 
      doublereal *v      = (doublereal *) malloc((size_t)     lv*sizeof(doublereal)); 
      doublereal *urparm = (doublereal *) calloc((size_t) 2*p*n, sizeof(doublereal));;
  
      for (i=0, j=0; i<(nls*(nls-1)/2 + nls); i++) {
        if (modelParameters[i].activeH) {
	  x[j]      = modelParameters[i].enthalpy/SCALE;
	  b[2*j  ]  = (implementBounds && (i < nls*(nls-1)/2)) ?      0.0       : -DBL_MAX;
	  b[2*j+1]  = (implementBounds && (i < nls*(nls-1)/2)) ? 500000.0/SCALE :  DBL_MAX;
	  uiparm[j] = i;
	  j++;
	}
	if (modelParameters[i].activeS) {
	  x[j]      = modelParameters[i].entropy;
	  b[2*j  ]  = -DBL_MAX;
	  b[2*j+1]  =  DBL_MAX;
	  uiparm[j] = i + nls*(nls-1)/2 + nls;
	  j++;
	}
	if (modelParameters[i].activeV) {
	  x[j]      = modelParameters[i].volume;
	  b[2*j  ]  = -DBL_MAX;
	  b[2*j+1]  =  DBL_MAX;
	  uiparm[j] = i + 2*(nls*(nls-1)/2 + nls);
	  j++;
	}
      }
      if (p != j) printf("Fatal logic error in setup for Trust Region Method.\n");

      (void) divset_(&kind, iv, &liv, &lv, v);
      
      /* uiparm -> storage of indexes for active parameters                                */
      /* urparm -> storage for saving jocobian matrix at two most recent parameter choices */
      setModeToMixingLiq(FALSE);
      (void) dn2gb_(&n, &p, x, b, calcr, calcj, iv, &liv, &lv, v, uiparm, urparm, ufparm);
      setModeToMixingLiq(TRUE);
      
      free(iv); free(uiparm); free(x); free(b); free(v); free(urparm);
    } else printf("Trust Region analysis bypassed.  Number of equations (%d) or parameters (%d) zero.\n", (int) n, (int) p);
        
    curStep++;
  
  } else { /* !useTrustRegionMethod */
    if (XmToggleButtonGadgetGetState(mrqrdtADB[10])) {
      curStep++;
      DISPLAY(actionADB[0], "Marquardt analysis terminated by user.")
      workProcData->active = TRUE;
      return FALSE;
    }

    funcEvals = 0;
    loop++;
    oldChisq  = chisq;
    oldAlamda = alamda;
 
    setModeToMixingLiq(FALSE);
    mrqminWithSVA(xMrqrdt, yMrqrdt, sigMrqrdt, nEqn, aMrqrdt, iaMrqrdt, ma, covar, alpha, &chisq, funcCalibration, &alamda);
    setModeToMixingLiq(TRUE);

    printf("Iter: %d chisq = %20.13g, lamba = %20.13g, funcEvals = %d\n", loop, chisq, alamda, funcEvals);
    for (i=1; i<=ma; i++) if (iaMrqrdt[i]) printf("Param[%20.20s] = %20.13g\n", (i < (nls+nls*(nls-1)/2+1)) ? modelParameters[i-1].label :
      modelParameters[i-nls-nls*(nls-1)/2-1].label, aMrqrdt[i]);
 
#ifdef GRACE_PIPE
    GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, (double) loop, chisq);
    GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 1, (double) loop, log10(alamda));
    GracePrintf("WITH G0\n"); GracePrintf("AUTOSCALE\n");
    GracePrintf("WITH G1\n"); GracePrintf("AUTOSCALE\n");
    GracePrintf("REDRAW\n");
#endif /* GRACE_PIPE */

    DISPLAYI(mrqrdtADB[0], loop)
    DISPLAYI(mrqrdtADB[1], funcEvals)
    DISPLAYD(mrqrdtADB[8], chisq)
    DISPLAYD(mrqrdtADB[9], alamda)
 
    DISPLAY(actionADB[0], "Completed intermediate step in Marquardt analysis.")
  }
  
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Perform post-regression error analysis
 *===========================================================================*/

  case POSTREGRESS:

  if (useTrustRegionMethod) {
  
  } else { /* !useTrustRegionMethod */
    alamda = 0.0; funcEvals = 0;

    if (loop > 0) {
      setModeToMixingLiq(FALSE);
      mrqminWithSVA(xMrqrdt, yMrqrdt, sigMrqrdt, nEqn, aMrqrdt, iaMrqrdt, ma, covar, alpha, &chisq, funcCalibration, &alamda);
      setModeToMixingLiq(TRUE);

      printf("Final: chisq = %20.13g, lamba = %20.13g, funcEvals = %d\n", chisq, alamda, funcEvals);
      for (i=1; i<=ma; i++) if (iaMrqrdt[i]) printf("Param[%20.20s] = %20.13g +/- %20.13g (1 sigma)\n", (i < (nls+nls*(nls-1)/2+1)) ? modelParameters[i-1].label :
  	modelParameters[i-nls-nls*(nls-1)/2-1].label, aMrqrdt[i], sqrt(covar[i][i]));
      printf("Correlation coefficient matrix:\n");
      for (i=1; i<=ma; i++) if (iaMrqrdt[i]) {
  	for (j=1; j<=ma; j++) if (iaMrqrdt[j]) printf("%6.2f ", covar[i][j]/(sqrt(covar[i][i])*sqrt(covar[j][j])));
  	printf("\n");
      }
    }
    DISPLAY(actionADB[0], "Completed final step in Marquardt analysis.")
  }

  curStep++;
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Write out solution
 *===========================================================================*/

  case SOLUTION:

  writeParameters("param_struct_data.preclb");

  curStep++;
  DISPLAY(actionADB[0], "New parameter written. Ready to analyze residuals.")
  workProcData->active = TRUE; 
  return FALSE;

/*=============================================================================
 * Return to interface, release temporary storage
 *===========================================================================*/
  
  case FINAL:

  curStep = 0;
  nLiquid = 0;

  workProcData->active = FALSE; 
  return TRUE;

  } /* end switch */

  return TRUE;
}

/* end of file PRECLB.C */
