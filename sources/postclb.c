const char *postclb_ver(void) { return "$Id: postclb.c,v 1.28 2009/05/14 04:24:00 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: postclb.c,v $
MELTS Source Code: RCS Revision 1.21  2008/05/09 20:07:36  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.20  2008/05/09 17:21:51  ghiorso
MELTS Source Code: RCS Corrected error in dealing with dependency of Al 1/3 OH species
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.19  2007/11/22 04:08:14  ghiorso
MELTS Source Code: RCS Corrected infinite loop error in order() in albite.c
MELTS Source Code: RCS Removed arbitrary volume corrections in sol_struct_data.h
MELTS Source Code: RCS Turned on non-quadrilateral cpx endmembers for regression.
MELTS Source Code: RCS Added MgSiO3 species to liquid model.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.18  2007/10/29 19:58:02  ghiorso
MELTS Source Code: RCS Updated ss volume terms for new regression.
MELTS Source Code: RCS Miscellaneous fixes.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.17  2007/10/24 18:53:36  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.16  2007/08/26 21:38:30  ghiorso
MELTS Source Code: RCS Normalized residuals (for xMELTS calibration) to the number of atoms in the
MELTS Source Code: RCS endmember mineral formula.  Revised residual-statistics.out file accordingly.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.15  2007/05/15 21:47:54  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.14  2007/05/15 17:44:21  ghiorso
MELTS Source Code: RCS More useful output to residual tables
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.13  2007/05/15 15:51:03  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.12  2007/05/15 00:19:38  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.11  2007/05/15 00:01:20  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.10  2007/05/14 21:46:19  ghiorso
MELTS Source Code: RCS Extended table files produced in postclb with additional information.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.9  2007/05/09 21:00:03  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.8  2007/05/07 18:23:21  ghiorso
MELTS Source Code: RCS Modifications to LEPR and calibration algorithms following visit by
MELTS Source Code: RCS Marc and Tim.  Mostly work on cpx and opx inclusion and reclassification.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.7  2007/03/12 21:17:18  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2007/02/20 21:50:19  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2007/02/20 21:25:47  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2007/02/20 19:41:13  ghiorso
MELTS Source Code: RCS New liqList file and reformatting of residual-statistics.out file.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2007/02/13 21:48:30  ghiorso
MELTS Source Code: RCS Modifications to read XML database files for LEPER calibration.
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
MELTS Source Code: RCS Revision 1.3  2004/12/11 23:15:01  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2004/09/15 02:47:56  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2001/12/26 19:20:02  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
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
**      Toolkit work proceedure to drive a POSTCLB iteration (file: POSTCLB.C)
**
**--
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Xm/Xm.h> 

#include "interface.h"
#include "silmin.h"
#include "calibration.h"
#include "vframe.h"                 /*vframe widget include file            */
#include "vheader.h"                /*vheader widget include file           */
#include "vlist.h"                  /*vlist widget include file             */

#ifdef GRACE_PIPE
#include <unistd.h>
#include <grace_np.h>
#endif /* GRACE_PIPE */

#define SQUARE(x) ((x)*(x))
#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))

static void updatePostclbOutliersDisplay(
  int curSolid, char *component, int nLiq, 
  double stdDep, double stdRes, double logfO2, double T, double P, double *Afn,
  double *moleFrac)
{
   int i;
   static VListLine vLine[9] = {
      {VListLineTextMask},
      {VListLineTextMask}, {VListLineTextMask}, {VListLineTextMask},
      {VListLineTextMask}, {VListLineTextMask}, {VListLineTextMask},
      {VListLineTextMask}, {VListLineTextMask}
   }; 
   static char *text[9] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
   static int na = 0;
   
   if (text[0] == NULL) { text[0] = (char *) malloc((size_t) 11*sizeof(char)); (text[0])[10] = '\0'; }
   if (text[1] == NULL) { text[1] = (char *) malloc((size_t)  5*sizeof(char)); (text[1])[ 4] = '\0'; }
   if (text[2] == NULL) { text[2] = (char *) malloc((size_t)  9*sizeof(char)); (text[2])[ 8] = '\0'; }
   if (text[3] == NULL) { text[3] = (char *) malloc((size_t)  9*sizeof(char)); (text[3])[ 8] = '\0'; }
   if (text[4] == NULL) { text[4] = (char *) malloc((size_t)  9*sizeof(char)); (text[4])[ 8] = '\0'; }
   if (text[5] == NULL) { text[5] = (char *) malloc((size_t)  9*sizeof(char)); (text[5])[ 8] = '\0'; }
   if (text[6] == NULL) { text[6] = (char *) malloc((size_t)  9*sizeof(char)); (text[6])[ 8] = '\0'; }
   if (text[7] == NULL) { text[7] = (char *) malloc((size_t)  9*sizeof(char)); (text[7])[ 8] = '\0'; }

   if ((curSolid < npc) && (solids[curSolid].na > na)) {
     na = solids[curSolid].na;
     if (text[8] == NULL) {
       text[8] = (char *) malloc((unsigned) (na*9+1)*sizeof(char));
     } else {
       text[8] = (char *) REALLOC(text[8], (unsigned) (na*9+1)*sizeof(char));
     }
     (text[8])[na*9] = '\0';
   }

   (void) snprintf(text[0], 11, "%-10.10s", component);
   (void) snprintf(text[1],  5, "%4.4d",    nLiq);
   (void) snprintf(text[2],  9, "%8.2f",    stdDep);
   (void) snprintf(text[3],  9, "%8.2f",    stdRes);
   (void) snprintf(text[4],  9, "%8.3f",    logfO2);
   (void) snprintf(text[5],  9, "%8.2f",    T);
   (void) snprintf(text[6],  9, "%8.3f",    P);

   if (Afn == NULL) {
     (void) snprintf(text[7], 9, "%8.8s", "        ");
   } else {
     (void) snprintf(text[7], 9, "%8.3f", *Afn);
   }

   if (moleFrac == NULL || curSolid >= npc) for (i=0; i<na; i++)                  (void) snprintf(&(text[8])[i*9], 10, " %8.8s", "        ");
   else                                     for (i=0; i<solids[curSolid].na; i++) (void) snprintf(&(text[8])[i*9], 10, " %8.5f", moleFrac[i]);

   for (i=0; i<9; i++) vLine[i].textP = text[i];
   
   (void) VListAddLine ((VListWidget) postclb_outliers, vLine, VListAddAtBottom);
}

static void updatePostclbStatisticsDisplay(
  int curSolid, char *component, int n, 
  double aveDep,  double aveRes, double avefo2,  double aveT,  double aveP,
  double stdDep,  double stdRes, double stdfo2,  double stdT,  double stdP,
  double rResDep,                double rResfo2, double rResT, double rResP)
{
   int i;
   static VListLine vLine[16] = {
      {VListLineTextMask},
      {VListLineTextMask}, {VListLineTextMask}, {VListLineTextMask},
      {VListLineTextMask}, {VListLineTextMask}, {VListLineTextMask},
      {VListLineTextMask}, {VListLineTextMask}, {VListLineTextMask},
      {VListLineTextMask}, {VListLineTextMask}, {VListLineTextMask},
      {VListLineTextMask}, {VListLineTextMask}, {VListLineTextMask}
   }; 
   static char *text[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
   
   if (text[ 0] == NULL) { text[ 0] = (char *) malloc((size_t) 11*sizeof(char)); (text[ 0])[10] = '\0'; }
   if (text[ 1] == NULL) { text[ 1] = (char *) malloc((size_t)  5*sizeof(char)); (text[ 1])[ 4] = '\0'; }
   if (text[ 2] == NULL) { text[ 2] = (char *) malloc((size_t)  9*sizeof(char)); (text[ 2])[ 8] = '\0'; }
   if (text[ 3] == NULL) { text[ 3] = (char *) malloc((size_t)  9*sizeof(char)); (text[ 3])[ 8] = '\0'; }
   if (text[ 4] == NULL) { text[ 4] = (char *) malloc((size_t)  9*sizeof(char)); (text[ 4])[ 8] = '\0'; }
   if (text[ 5] == NULL) { text[ 5] = (char *) malloc((size_t)  9*sizeof(char)); (text[ 5])[ 8] = '\0'; }
   if (text[ 6] == NULL) { text[ 6] = (char *) malloc((size_t)  9*sizeof(char)); (text[ 6])[ 8] = '\0'; }
   if (text[ 7] == NULL) { text[ 7] = (char *) malloc((size_t)  9*sizeof(char)); (text[ 7])[ 8] = '\0'; }
   if (text[ 8] == NULL) { text[ 8] = (char *) malloc((size_t)  9*sizeof(char)); (text[ 8])[ 8] = '\0'; }
   if (text[ 9] == NULL) { text[ 9] = (char *) malloc((size_t)  9*sizeof(char)); (text[ 9])[ 8] = '\0'; }
   if (text[10] == NULL) { text[10] = (char *) malloc((size_t)  9*sizeof(char)); (text[10])[ 8] = '\0'; }
   if (text[11] == NULL) { text[11] = (char *) malloc((size_t)  9*sizeof(char)); (text[11])[ 8] = '\0'; }
   if (text[12] == NULL) { text[12] = (char *) malloc((size_t)  9*sizeof(char)); (text[12])[ 8] = '\0'; }
   if (text[13] == NULL) { text[13] = (char *) malloc((size_t)  9*sizeof(char)); (text[13])[ 8] = '\0'; }
   if (text[14] == NULL) { text[14] = (char *) malloc((size_t)  9*sizeof(char)); (text[14])[ 8] = '\0'; }
   if (text[15] == NULL) { text[15] = (char *) malloc((size_t)  9*sizeof(char)); (text[15])[ 8] = '\0'; }

   (void) snprintf(text[ 0], 11, "%-10.10s", component);
   (void) snprintf(text[ 1],  5, "%4.4d",    n);
   (void) snprintf(text[ 2],  9, "%8.2f",    aveDep);
   (void) snprintf(text[ 3],  9, "%8.2f",    aveRes);
   (void) snprintf(text[ 4],  9, "%8.3f",    avefo2);
   (void) snprintf(text[ 5],  9, "%8.2f",    aveT);
   (void) snprintf(text[ 6],  9, "%8.3f",    aveP);
   (void) snprintf(text[ 7],  9, "%8.2f",    stdDep);
   (void) snprintf(text[ 8],  9, "%8.2f",    stdRes);
   (void) snprintf(text[ 9],  9, "%8.3f",    stdfo2);
   (void) snprintf(text[10],  9, "%8.2f",    stdT);
   (void) snprintf(text[11],  9, "%8.3f",    stdP);
   (void) snprintf(text[12],  9, "%8.5f",    rResDep);
   (void) snprintf(text[13],  9, "%8.5f",    rResfo2);
   (void) snprintf(text[14],  9, "%8.5f",    rResT);
   (void) snprintf(text[15],  9, "%8.5f",    rResP);

   for (i=0; i<16; i++) vLine[i].textP = text[i];
   
   (void) VListAddLine ((VListWidget) postclb_statistics, vLine, VListAddAtBottom);
}

static int isNAN (double x) { return x != x; }

Boolean postclb(XtPointer client_data)
{
  static double *xvec = NULL, *yvec = NULL, *tvec = NULL, *pvec = NULL, *fo2vec = NULL, *wtSiO2vec = NULL;
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
  static double *wtALKvec = NULL;
#endif
  static int    *mtypevec = NULL;
  static char   **name = NULL;
  static XmString valueCS = NULL;

  static FILE *resFile;
  static char *resFileName;

  static FILE *sumFile;
  static const char *sumFileName = "residual-statistics.out";

  static int curStep = 0, curSolid = 0;
#ifdef GRACE_PIPE
  static int curGraphSet = 0;
#endif /* GRACE_PIPE */
  enum steps { INITIAL, RESOUTPUT, TABLES, FINAL };
  static double bAVE, bSTD, resAVE, resSTD;

  WorkProcData *workProcData = (WorkProcData *) client_data;

  double aveRes, stdRes, aveDep, stdDep, aveT, stdT, aveP, stdP, avefo2, stdfo2;
  double rResDep, rResT, rResP, rResfo2;
  int i, j, k, l, kk, nRES, nSol;
  
  switch(curStep) {

  /*=========================================================================*/

  case INITIAL:

  if (nEqn <= 2) { workProcData->active = FALSE; return(TRUE); }

  wtSiO2vec = (double *) malloc((unsigned) nEqn*sizeof(double));
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
  wtALKvec  = (double *) malloc((unsigned) nEqn*sizeof(double));
#endif
  fo2vec    = (double *) malloc((unsigned) nEqn*sizeof(double));
  pvec      = (double *) malloc((unsigned) nEqn*sizeof(double));
  tvec      = (double *) malloc((unsigned) nEqn*sizeof(double));
  xvec      = (double *) malloc((unsigned) nEqn*sizeof(double));
  yvec      = (double *) malloc((unsigned) nEqn*sizeof(double));
  mtypevec  = (int *)    malloc((unsigned) nEqn*sizeof(int));
  name      = (char **)  malloc((unsigned) nEqn*sizeof(char *));
  for (i=0; i<nEqn; i++) {
    name[i]  = (char *) malloc((unsigned) 11*sizeof(char));
    for (j=0; j<10; j++) name[i][j] = ' ';
    name[i][10] = '\0';
  }
  for (i=0, bAVE = 0.0, bSTD = 0.0, resAVE = 0.0, resSTD = 0.0; i<nLiquid; i++) {
    int nSol = residualDataInput[i].nSol;
    if(nSol > 0) for (j=0; j<nSol; j++) {
      if (isNAN((residualDataInput[i].depenG)[j])) {
        (residualDataInput[i].depenG)[j] = 0.0;
	printf("postclb [postclb.c at line %d]--> NaN detected for liquid %d on constraint %d\n", __LINE__, i, j);
      }
      bAVE +=   ((residualDataInput[i].isEqual)[j]) ? (residualDataInput[i].depenG)[j]          : 0.0; 
      bSTD +=   ((residualDataInput[i].isEqual)[j]) ? SQUARE((residualDataInput[i].depenG)[j])  : 0.0; 
      resAVE += ((residualDataInput[i].isEqual)[j]) ? (residualOutput[i].residuals)[j]          : 0.0;
      resSTD += ((residualDataInput[i].isEqual)[j]) ? SQUARE((residualOutput[i].residuals)[j])  : 0.0;
    }
  }
  resAVE = resAVE/nEqn;
  resSTD = sqrt(resSTD/(nEqn-1));
  bAVE   = bAVE/nEqn;
  bSTD   = sqrt((bSTD-nEqn*SQUARE(bAVE))/(nEqn-1));

/*
  if (resSTD < DBL_EPSILON) { curStep = FINAL; workProcData->active = TRUE; return(FALSE); }
  if (bSTD   < DBL_EPSILON) { curStep = FINAL; workProcData->active = TRUE; return(FALSE); }
*/

  if ( (sumFile = fopen (sumFileName, "w")) == NULL) {
    valueCS = XmStringCreateLtoR("Cannot open file RESIDUAL-STATISTICS.OUT", "ISO8859-1");
    MESSAGE(valueCS); XmStringFree(valueCS); workProcData->active = FALSE; 
    return(TRUE);
  }

  fprintf(sumFile, "Std Dep,%g,kJ,Ave Dep,%g,kJ\n", bSTD, bAVE); 
  fprintf(sumFile, "Std Res,%g,kJ,Ave Res,%g,kJ\n", resSTD, resAVE); 

  fprintf(sumFile,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,", "component", "N", "aveDep", "aveRes", "aveRes (kJ/N)", "nAtom", "aveRes (kJ)", "avefo2", "aveT", "aveP");
  fprintf(sumFile,"%s,%s,%s,%s,%s,%s,%s,", "stdDep", "stdRes", "stdRes (kJ/N)", "stdRes (kJ)", "stdfo2", "stdT", "stdP");
  fprintf(sumFile,"%s,%s,%s,%s\n", "rResDep", "rResfo2", "rResT", "rResP");

#ifdef GRACE_PIPE
  GracePrintf("FLUSH\n");

#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
  GracePrintf("WITH G0\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.1, 1.15, 0.35);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 1.0);

    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"T (C)\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS LABEL \"residual\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
    
    GracePrintf("LEGEND ON\n");
    GracePrintf("LEGEND X1 1.10\n");
    GracePrintf("LEGEND Y1 0.98\n");
    GracePrintf("LEGEND CHAR SIZE 0.65\n");
  GracePrintf("G0 on\n");
    
  GracePrintf("WITH G1\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.4, 1.15, 0.65);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 1.0);

    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"Wt%% SiO2\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS LABEL \"residual\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
    
    GracePrintf("LEGEND OFF\n");
  GracePrintf("G1 on\n");

  GracePrintf("WITH G2\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.7, 1.15, 0.95);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 1.0);

    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"Wt%% [(Na2O+K2O)-Al2O3]/(100-SiO2)\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS LABEL \"residual\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
    
    GracePrintf("LEGEND OFF\n");
  GracePrintf("G2 on\n");

  GracePrintf("g0.s%1.1d LINESTYLE 1\n",     curGraphSet);
  GracePrintf("g1.s%1.1d LINESTYLE 1\n",     curGraphSet);
  GracePrintf("g2.s%1.1d LINESTYLE 1\n",     curGraphSet);
  GracePrintf("g0.s%1.1d SYMBOL 0\n",        curGraphSet);
  GracePrintf("g1.s%1.1d SYMBOL 0\n",        curGraphSet);
  GracePrintf("g2.s%1.1d SYMBOL 0\n",        curGraphSet);
  GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 0,  500.0, 0.0);
  GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 0,    0.0, 0.0);	  
  GracePrintf("g2.s%1.1d POINT %lf, %lf\n", 0, -100.0, 0.0);	  
  GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 0, 2200.0, 0.0);
  GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 0,  100.0, 0.0);	  
  GracePrintf("g2.s%1.1d POINT %lf, %lf\n", 0,  100.0, 0.0);	  

#else
  GracePrintf("WITH G0\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.1, 0.9, 0.45);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 1.0);

    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"T (C)\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS LABEL \"residual\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
    
    GracePrintf("LEGEND ON\n");
    GracePrintf("LEGEND X1 1.10\n");
    GracePrintf("LEGEND Y1 0.98\n");
    GracePrintf("LEGEND CHAR SIZE 0.65\n");
  GracePrintf("G0 on\n");
    
  GracePrintf("WITH G1\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.6, 0.9, 0.95);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 1.0);

    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"P (kbars)\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS LABEL \"residual\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
    
    GracePrintf("LEGEND OFF\n");
  GracePrintf("G1 on\n");

  GracePrintf("g0.s%1.1d LINESTYLE 1\n",     curGraphSet);
  GracePrintf("g1.s%1.1d LINESTYLE 1\n",     curGraphSet);
  GracePrintf("g0.s%1.1d SYMBOL 0\n",        curGraphSet);
  GracePrintf("g1.s%1.1d SYMBOL 0\n",        curGraphSet);
  GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 0,    0.0, 0.0);
  GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 0,    0.0, 0.0);	  
  GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 0, 5000.0, 0.0);
  GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 0,  400.0, 0.0);	
    
#endif /* BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION */
#endif /* GRACE_PIPE */

  curStep++;
  workProcData->active = TRUE;
  return(FALSE);

  /*=========================================================================*/

  case RESOUTPUT:

  for (i=0; i<npc; i++) if (solids[i].type == PHASE)  {
    Boolean firstTime = TRUE;
    int lastComponent = npc+1;
    int lastLiquid    = -1;
    Boolean printMe = FALSE;
    int ne=0, *neIndex = NULL;
    double *depVar, *resVar, *xVar;
  
    if (solids[i].convert != NULL) {
      for (j=0; j<nes; j++) if (extraSolids[j].index == i) {
        ne++;
        if (neIndex == NULL) neIndex = (int *) malloc(          (size_t)    sizeof(int));
        else                 neIndex = (int *) realloc(neIndex, (size_t) ne*sizeof(int));
        neIndex[ne-1] = j;
      }
    }
    depVar = (double *) calloc((size_t) ((solids[i].na == 0) ? 1 : solids[i].na) + ne, sizeof(double));
    resVar = (double *) calloc((size_t) ((solids[i].na == 0) ? 1 : solids[i].na) + ne, sizeof(double));
    xVar   = (double *) calloc((size_t) ((solids[i].na == 0) ? 1 : solids[i].na) + ne, sizeof(double));
    
    /* i is index over all solid phase/components */
    /* j is index over nLiquid                    */
    /* l is index over residualDataInput[j].nSol  */
    for (j=0; j<nLiquid; j++) if ((nSol = residualDataInput[j].nSol) > 0) for (l=0; l<nSol; l++) 
      if ((residualDataInput[j].pIndex)[l] == i) { /* (residualDataInput[j].isEqual)[l] &&  */
      int isEqual   = (residualDataInput[j].isEqual)[l];
      double *xLiq  = (double *) malloc((size_t) nls*sizeof(double)); 
      double *wtLiq = (double *) malloc((size_t) nlc*sizeof(double));
      double wtSiO2, wtCaO, wtH2O, wtCO2, sumOx, FEspecies[3], H2Ospecies[3]; 
      int aluminousIndex[3];
#if BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
      double wtAl2O3, wtNa2O, wtK2O; 
#else
      double wtMgO, MgNum, alkIndex; 
#endif      
      conLiq(THIRD, FOURTH, residualDataInput[j].t,  residualDataInput[j].p/10000.0, NULL, NULL,
        (residualDataInput[j].rLiq)[0], xLiq, NULL, NULL, NULL);
      for (k=0, sumOx=0.0; k<nc; k++) {
        for (kk=0, wtLiq[k]=0.0; kk<nlc; kk++) wtLiq[k] += (liquid[kk].liqToOx)[k]*xLiq[kk];
	    sumOx += wtLiq[k]*bulkSystem[k].mw;
      }

#ifdef BUILD_MGO_SIO2_VERSION
      wtSiO2   = 100.0*wtLiq[0]*bulkSystem[0].mw/sumOx;
      wtMgO    = 100.0*wtLiq[1]*bulkSystem[1].mw/sumOx;
      wtCaO    = 0.0;
      alkIndex = 0.0;
      wtH2O    = 0.0;
      wtCO2    = 0.0;
      MgNum    = 100.0;
      aluminousIndex[0] = FALSE; /* peralkaline  */
      aluminousIndex[1] = FALSE; /* metaluminous */
      aluminousIndex[2] = FALSE; /* peraluminous */
      FEspecies[0]  = 0.0;
      FEspecies[1]  = 0.0;
      FEspecies[2]  = 0.0;
      H2Ospecies[0] = 0.0;
      H2Ospecies[1] = 0.0;
      H2Ospecies[2] = 0.0;
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
      wtSiO2   = 100.0*wtLiq[0]*bulkSystem[0].mw/sumOx;
      wtAl2O3  = 100.0*wtLiq[1]*bulkSystem[1].mw/sumOx;
      wtCaO    = 100.0*wtLiq[2]*bulkSystem[2].mw/sumOx;
      wtNa2O   = 100.0*wtLiq[3]*bulkSystem[3].mw/sumOx;
      wtK2O    = 100.0*wtLiq[4]*bulkSystem[4].mw/sumOx;
      wtH2O    = 100.0*wtLiq[5]*bulkSystem[5].mw/sumOx;
      wtCO2    = 0.0;
      aluminousIndex[0] =  (wtLiq[3]+wtLiq[4]  > wtLiq[1])                                              ? TRUE : FALSE; /* peralkaline  */
      aluminousIndex[1] = ((wtLiq[3]+wtLiq[4] <= wtLiq[1]) && (wtLiq[2]+wtLiq[3]+wtLiq[4] >= wtLiq[1])) ? TRUE : FALSE; /* metaluminous */
      aluminousIndex[2] =                                     (wtLiq[2]+wtLiq[3]+wtLiq[4]  < wtLiq[1])  ? TRUE : FALSE; /* peraluminous */
      FEspecies[0]  = 0.0;
      FEspecies[1]  = 0.0;
      FEspecies[2]  = 0.0;
      H2Ospecies[0] = 0.0;
      H2Ospecies[1] = 0.0;
      H2Ospecies[2] = 0.0;
#else      
      wtSiO2   = 100.0*wtLiq[ 0]*bulkSystem[ 0].mw/sumOx;
      wtMgO    = 100.0*wtLiq[ 7]*bulkSystem[ 7].mw/sumOx;
      wtCaO    = 100.0*wtLiq[10]*bulkSystem[10].mw/sumOx;
      alkIndex = 100.0*wtLiq[11]*bulkSystem[11].mw/sumOx + 100.0*wtLiq[12]*bulkSystem[12].mw/sumOx;
      wtH2O    = 100.0*wtLiq[14]*bulkSystem[14].mw/sumOx;
      wtCO2    = 100.0*wtLiq[15]*bulkSystem[15].mw/sumOx;
      MgNum    = 100.0*wtLiq[ 5]*bulkSystem[ 5].mw/sumOx + 100.0*wtLiq[ 7]*bulkSystem[ 7].mw/sumOx;
      if (MgNum > 0.0) MgNum = (100.0*wtLiq[ 7]*bulkSystem[ 7].mw/sumOx)/MgNum;
      aluminousIndex[0] =  (wtLiq[11]+wtLiq[12]  > wtLiq[2])                                                 ? TRUE : FALSE; /* peralkaline  */
      aluminousIndex[1] = ((wtLiq[11]+wtLiq[12] <= wtLiq[2]) && (wtLiq[10]+wtLiq[11]+wtLiq[12] >= wtLiq[2])) ? TRUE : FALSE; /* metaluminous */
      aluminousIndex[2] =                                       (wtLiq[10]+wtLiq[11]+wtLiq[12]  < wtLiq[2])  ? TRUE : FALSE; /* peraluminous */
      
      conLiq(THIRD, FOURTH | EIGHTH, residualDataInput[j].t,  residualDataInput[j].p/10000.0, NULL, NULL,
        (residualDataInput[j].rLiq)[0], xLiq, NULL, NULL, NULL);
#ifndef RHYOLITE_ADJUSTMENTS
      FEspecies[0]  = xLiq[ 3]; /* Fe2SiO5   */
      FEspecies[1]  = xLiq[ 5]; /* Fe2SiO4   */
      FEspecies[2]  = xLiq[19]; /* Fe2SiO4.6 */
      H2Ospecies[0] = xLiq[18]; /* H2O       */
      H2Ospecies[1] = xLiq[20]; /* Si 1/4 OH */
      H2Ospecies[2] = xLiq[29]; /* Al 1/3 OH */
#else
      FEspecies[0]  = 0.0;
      FEspecies[1]  = 0.0;
      FEspecies[2]  = 0.0;
      H2Ospecies[0] = 0.0;
      H2Ospecies[1] = 0.0;
      H2Ospecies[2] = 0.0;
#endif
#endif
      free(xLiq);
      free(wtLiq);
      
      if (firstTime) {
        /* Out a file to output residuals for this phase */
        if (resFileName != NULL) free(resFileName);
        resFileName = (char *) calloc((unsigned) (strlen(solids[i].label)+5), sizeof(char));
        resFileName = strncpy(resFileName, solids[i].label, strlen(solids[i].label));
        for (k=0; k<strlen(solids[k].label); k++) if(resFileName[k] == ' ') resFileName[k] = '-';
        resFileName = strncat(resFileName, ".res", 4);	   
        if ( (resFile = fopen (resFileName, "w")) == NULL) {
          valueCS = XmStringCreateLtoR(strcat("Cannot open file", resFileName), "ISO8859-1");
          MESSAGE(valueCS); XmStringFree(valueCS); workProcData->active = FALSE; 
          return(TRUE);
        }
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
	fprintf(resFile,"LEPR N,T (C),P (GPa),log fO2,Palk,Mal,Pal,L SiO2,L Al2O3,L CaO,L Na2O,L K2O,L H2O,L CO2, S Fe2SiO5,S Fe2SiO4,S Fe2SiO4.6,S H2O,S Si0.25OH,S Al0.33OH");
#else
	fprintf(resFile,"LEPR N,T (C),P (GPa),log fO2,Palk,Mal,Pal,L SiO2,L MgNum,L ALKind,L MgO,L CaO,L H2O,L CO2,S Fe2SiO5,S Fe2SiO4,S Fe2SiO4.6,S H2O,S Si0.25OH,S Al0.33OH");
#endif
	if (solids[i].convert == NULL) {
	  fprintf(resFile,",Dep %s (kJ),Res %s (kJ),Afn %s (kJ)\n", solids[i].label, solids[i].label, solids[i].label);
	} else {
	  for (k=0; k<solids[i].na; k++) 
	    fprintf(resFile,",X %s,Dep %s (kJ),Res %s (kJ)", solids[i+1+k].label, solids[i+1+k].label, solids[i+1+k].label);
	  for (k=0; k<nes; k++) if (!strcmp(extraSolids[k].phase,solids[i].label))
	    fprintf(resFile,",X %s,Dep %s (kJ),Res %s (kJ)", extraSolids[k].species, extraSolids[k].species, extraSolids[k].species);
	  fprintf(resFile,"\n");
	}
	firstTime = FALSE;
	printMe   = FALSE;
      }
              
      /* One-component phase */
      if (solids[i].convert == NULL) {
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
        if ((residualDataInput[j].depenG)[l] != 0.0) 
          fprintf(resFile, "%d,%g,%g,%g,%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g", residualDataInput[j].LEPRnum, residualDataInput[j].t-273.15, 
	    residualDataInput[j].p/10000.0, residualDataInput[j].fo2, aluminousIndex[0], aluminousIndex[1], aluminousIndex[2], 
	    wtSiO2, wtAl2O3, wtCaO, wtNa2O, wtK2O, wtH2O, wtCO2, FEspecies[0], FEspecies[1], FEspecies[2], H2Ospecies[0], H2Ospecies[1], H2Ospecies[2],
	    (residualDataInput[j].depenG)[l], (isEqual) ? (residualOutput[j].residuals)[l] : 0.0, (isEqual) ? 0.0 : (residualOutput[j].residuals)[l]);
	else
          fprintf(resFile, "%d,%g,%g,%g,%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,,", residualDataInput[j].LEPRnum, residualDataInput[j].t-273.15, 
	    residualDataInput[j].p/10000.0, residualDataInput[j].fo2, aluminousIndex[0], aluminousIndex[1], aluminousIndex[2], 
	    wtSiO2, wtAl2O3, wtCaO, wtNa2O, wtK2O, wtH2O, wtCO2, FEspecies[0], FEspecies[1], FEspecies[2], H2Ospecies[0], H2Ospecies[1], H2Ospecies[2]);
#else
        if ((residualDataInput[j].depenG)[l] != 0.0) 
          fprintf(resFile, "%d,%g,%g,%g,%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g", residualDataInput[j].LEPRnum, residualDataInput[j].t-273.15, 
	    residualDataInput[j].p/10000.0, residualDataInput[j].fo2, aluminousIndex[0], aluminousIndex[1], aluminousIndex[2], 
	    wtSiO2, MgNum, alkIndex, wtMgO, wtCaO, wtH2O, wtCO2, FEspecies[0], FEspecies[1], FEspecies[2], H2Ospecies[0], H2Ospecies[1], H2Ospecies[2],
	    (residualDataInput[j].depenG)[l], (isEqual) ? (residualOutput[j].residuals)[l] : 0.0, (isEqual) ? 0.0 : (residualOutput[j].residuals)[l]);
	else
          fprintf(resFile, "%d,%g,%g,%g,%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,,", residualDataInput[j].LEPRnum, residualDataInput[j].t-273.15, 
	    residualDataInput[j].p/10000.0, residualDataInput[j].fo2, aluminousIndex[0], aluminousIndex[1], aluminousIndex[2], 
	    wtSiO2, MgNum, alkIndex, wtMgO, wtCaO, wtH2O, wtCO2, FEspecies[0], FEspecies[1], FEspecies[2], H2Ospecies[0], H2Ospecies[1], H2Ospecies[2]);
#endif	  

        if (!strcmp(solids[i].label, "h2oduan")) {
	      double wtH2Otemp, xLiq[19], rLiq[18], mu[19], targetMu, xOpt, xOptOld, f, fOld, df;
	      int first = TRUE, iter = 0;
	      printf("---> h2oduan\n");
	        
	      setModeToMixingLiq(FALSE);
	      actLiq(SECOND, residualDataInput[j].t, residualDataInput[j].p, (residualDataInput[j].rLiq)[0], NULL, mu, NULL, NULL);
	      conLiq(THIRD, FOURTH, residualDataInput[j].t,  residualDataInput[j].p, NULL, NULL, (residualDataInput[j].rLiq)[0], xLiq, NULL, NULL, NULL);
	      for (k=0; k<nlc; k++) fprintf(resFile, ",%g", xLiq[k]);
	        
	      targetMu = mu[18] + (residualOutput[j].residuals)[l]*1000.0*3.0;
	      printf("target mu[H2O] = %g X[H2O] = %g\n", targetMu, xLiq[18]);
	      f = 1000.0;
	      xOpt = xLiq[18];
	        
	      while ((fabs(f) > 1.0e-1) && (iter < 100)) {
	        xLiq[18] = xOpt;
	        conLiq(SECOND, THIRD, residualDataInput[j].t,  residualDataInput[j].p, NULL, xLiq, rLiq, NULL, NULL, NULL, NULL);
	        actLiq(SECOND, residualDataInput[j].t, residualDataInput[j].p, rLiq, NULL, mu, NULL, NULL);
	        f = mu[18] - targetMu;
	            
	        if (first) {
	          xOptOld = xLiq[18];
	          if ((residualOutput[j].residuals)[l] > 0.0)  xOpt = 1.05*xLiq[18]; else xOpt = xLiq[18]/1.05;
	          fOld = f;
	          first = FALSE;
	        } else {
	          df = (xOpt != xOptOld) ? (f-fOld)/(xOpt-xOptOld) : 1.0;
	          xOptOld = xOpt;
	          fOld = f;
	          xOpt -= f/df;
	          if (xOpt < 0.0) xOpt = 0.0001;
	          if (xOpt > 1.0) xOpt = 0.9999;
	        }
	        iter++;
	      }
	        
	      double wtLiq[16];
	      for (k=0, sumOx=0.0; k<nc; k++) {
            for (kk=0, wtLiq[k]=0.0; kk<nlc; kk++) wtLiq[k] += (liquid[kk].liqToOx)[k]*xLiq[kk];
			sumOx += wtLiq[k]*bulkSystem[k].mw;
          }
          wtH2Otemp    = 100.0*wtLiq[14]*bulkSystem[14].mw/sumOx;
      	  printf("iter = %d, wt%% H2O = %g, wt%%\n", iter, wtH2Otemp);
      	  fprintf(resFile, ",%d,%g\n", iter, wtH2Otemp);

        } else if (!strcmp(solids[i].label, "co2duan")) {
          double wtCO2temp, xLiq[19], rLiq[18], mu[19], targetMu, xOpt, xOptOld, f, fOld, df;
	      int first = TRUE, iter = 0;
	      printf("---> co2duan\n");
	        
	      setModeToMixingLiq(FALSE);
	      actLiq(SECOND, residualDataInput[j].t, residualDataInput[j].p, (residualDataInput[j].rLiq)[0], NULL, mu, NULL, NULL);
	      conLiq(THIRD, FOURTH, residualDataInput[j].t,  residualDataInput[j].p, NULL, NULL, (residualDataInput[j].rLiq)[0], xLiq, NULL, NULL, NULL);
	      for (k=0; k<nlc; k++) fprintf(resFile, ",%g", xLiq[k]);
	        
	      targetMu = mu[14] + (residualOutput[j].residuals)[l]*1000.0*3.0;
	      printf("target mu[CO2] = %g X[CO2] = %g\n", targetMu, xLiq[14]);
	      f = 1000.0;
	      xOpt = xLiq[14];
	        
	      while ((fabs(f) > 1.0e-1) && (iter < 100)) {
	        xLiq[14] = xOpt;
	        conLiq(SECOND, THIRD, residualDataInput[j].t,  residualDataInput[j].p, NULL, xLiq, rLiq, NULL, NULL, NULL, NULL);
	        actLiq(SECOND, residualDataInput[j].t, residualDataInput[j].p, rLiq, NULL, mu, NULL, NULL);
	        f = mu[14] - targetMu;
	            
	        if (first) {
	          xOptOld = xLiq[14];
	          if ((residualOutput[j].residuals)[l] > 0.0)  xOpt = 1.05*xLiq[14]; else xOpt = xLiq[14]/1.05;
	          fOld = f;
	          first = FALSE;
	        } else {
	          df = (f-fOld)/(xOpt-xOptOld);
	          xOptOld = xOpt;
	          fOld = f;
	          xOpt -= f/df;
	          if (xOpt < 0.0) xOpt = 0.000001;
	          if (xOpt > 2.0) xOpt = 1.999999;
	        }
	        if (xOpt ==	xOptOld) iter = 100;   
	        iter++;
	      }
	        
	      double wtLiq[16];
	      for (k=0, sumOx=0.0; k<nc; k++) {
            for (kk=0, wtLiq[k]=0.0; kk<nlc; kk++) wtLiq[k] += (liquid[kk].liqToOx)[k]*xLiq[kk];
			sumOx += wtLiq[k]*bulkSystem[k].mw;
          }
      	  wtCO2temp    = 100.0*wtLiq[15]*bulkSystem[15].mw/sumOx;
      	  printf("iter = %d, wt%% CO2 = %g\n", iter, wtCO2temp);
      	  fprintf(resFile, ",%d,%g\n", iter, wtCO2temp);
        
        } else { // end h2oduan, co2duan test
          fprintf(resFile, "\n");
        }
      
      /* Multi-component phase */
      } else {
        if (lastComponent > (residualDataInput[j].cIndex)[l] || lastLiquid != j) {
	      if (printMe) {
	      for (k=0; k<(solids[i].na+ne); k++) {
	        if (depVar[k] != 0.0) fprintf(resFile, ",%g,%g,%g", xVar[k], depVar[k], resVar[k]); else fprintf(resFile, ",,,");
	      }
	    
	    if (!strcmp(solids[i].label, "fluid")) {
	      double wtH2Otemp, wtCO2temp;
	      printf("Got fluid with x[H2O] = %g and res[H2O] = %g and x[CO2] = %g and res[CO2] = %g\n", xVar[0], resVar[0], xVar[1], resVar[1]);
	      if (xVar[1] == 0.0) { // pure water case
	        double xLiq[19], rLiq[18], mu[19], targetMu, xOpt, xOptOld, f, fOld, df;
	        int first = TRUE, iter = 0;
	        
	        setModeToMixingLiq(FALSE);
	        actLiq(SECOND, residualDataInput[lastLiquid].t, residualDataInput[lastLiquid].p, (residualDataInput[lastLiquid].rLiq)[0], NULL, mu, NULL, NULL);
	        conLiq(THIRD, FOURTH, residualDataInput[lastLiquid].t,  residualDataInput[lastLiquid].p, NULL, NULL, (residualDataInput[lastLiquid].rLiq)[0], xLiq, NULL, NULL, NULL);
	        for (k=0; k<nlc; k++) fprintf(resFile, ",%g", xLiq[k]);
	        
	        targetMu = mu[18] + resVar[0]*1000.0*3.0;
	        printf("target mu[H2O] = %g X[CO2] = %g X[H2O] = %g\n", targetMu, xLiq[14], xLiq[18]);
	        f = 1000.0;
	        xOpt    =  xLiq[18];
	        
	        while ((fabs(f) > 1.0e-1) && (iter < 100)) {
	        	xLiq[18] = xOpt;
	        	conLiq(SECOND, THIRD, residualDataInput[lastLiquid].t,  residualDataInput[lastLiquid].p, NULL, xLiq, rLiq, NULL, NULL, NULL, NULL);
	        	actLiq(SECOND, residualDataInput[lastLiquid].t, residualDataInput[lastLiquid].p, rLiq, NULL, mu, NULL, NULL);
	            f = mu[18] - targetMu;
	            
	            if (first) {
	                xOptOld = xLiq[18];
	            	if (resVar[0] > 0.0)  xOpt = 1.05*xLiq[18]; else xOpt = xLiq[18]/1.05;
	            	fOld = f;
	            	first = FALSE;
	            } else {
	        		df = (xOpt != xOptOld) ? (f-fOld)/(xOpt-xOptOld) : 1.0;
	        		xOptOld = xOpt;
	        		fOld = f;
	        		xOpt -= f/df;
	        		if (xOpt < 0.0) xOpt = 0.0001;
	        		if (xOpt > 1.0) xOpt = 0.9999;
	            }
	            iter++;
	            // printf("iter = %d, f = %g, df = %g, xOpt = %g, xOptOld = %g\n", iter, f, df, xOpt, xOptOld);
	        }
	        
	        double wtLiq[16];
	        for (k=0, sumOx=0.0; k<nc; k++) {
             	for (kk=0, wtLiq[k]=0.0; kk<nlc; kk++) wtLiq[k] += (liquid[kk].liqToOx)[k]*xLiq[kk];
				sumOx += wtLiq[k]*bulkSystem[k].mw;
            }
            wtH2Otemp    = 100.0*wtLiq[14]*bulkSystem[14].mw/sumOx;
      		wtCO2temp    = 100.0*wtLiq[15]*bulkSystem[15].mw/sumOx;
      		printf("iter = %d, wt%% H2O = %g, wt%% CO2 = %g\n", iter, wtH2Otemp, wtCO2temp);
      		fprintf(resFile, ",%d,%g,%g\n", iter, wtH2Otemp, wtCO2temp);
	        
	      } else if (xVar[0] == 0.0) { // pure carbon dioxide
	        double xLiq[19], rLiq[18], mu[19], targetMu, xOpt, xOptOld, f, fOld, df;
	        int first = TRUE, iter = 0;
	        
	        setModeToMixingLiq(FALSE);
	        actLiq(SECOND, residualDataInput[lastLiquid].t, residualDataInput[lastLiquid].p, (residualDataInput[lastLiquid].rLiq)[0], NULL, mu, NULL, NULL);
	        conLiq(THIRD, FOURTH, residualDataInput[lastLiquid].t,  residualDataInput[lastLiquid].p, NULL, NULL, (residualDataInput[lastLiquid].rLiq)[0], xLiq, NULL, NULL, NULL);
	        for (k=0; k<nlc; k++) fprintf(resFile, ",%g", xLiq[k]);
	        
	        targetMu = mu[14] + resVar[1]*1000.0*3.0;
	        //printf("target mu[CO2] = %g X[CO2] = %g X[H2O] = %g\n", targetMu, xLiq[14], xLiq[18]);
	        f = 1000.0;
	        xOpt    =  xLiq[14];
	        
	        while ((fabs(f) > 1.0e-1) && (iter < 100)) {
	        	xLiq[14] = xOpt;
	        	conLiq(SECOND, THIRD, residualDataInput[lastLiquid].t,  residualDataInput[lastLiquid].p, NULL, xLiq, rLiq, NULL, NULL, NULL, NULL);
	        	actLiq(SECOND, residualDataInput[lastLiquid].t, residualDataInput[lastLiquid].p, rLiq, NULL, mu, NULL, NULL);
	            f = mu[14] - targetMu;
	            
	            if (first) {
	                xOptOld = xLiq[14];
	            	if (resVar[1] > 0.0)  xOpt = 1.05*xLiq[14]; else xOpt = xLiq[14]/1.05;
	            	fOld = f;
	            	first = FALSE;
	            } else {
	        		df = (f-fOld)/(xOpt-xOptOld);
	        		xOptOld = xOpt;
	        		fOld = f;
	        		xOpt -= f/df;
	        		if (xOpt < 0.0) xOpt = 0.000001;
	        		if (xOpt > 2.0) xOpt = 1.999999;
	            }
	            if (xOpt ==	xOptOld) iter = 100;
	            
	            iter++;
	            // printf("iter = %d, f = %g, xOpt = %g\n", iter, f, xOpt);
	        }
	        
	        double wtLiq[16];
	        for (k=0, sumOx=0.0; k<nc; k++) {
             	for (kk=0, wtLiq[k]=0.0; kk<nlc; kk++) wtLiq[k] += (liquid[kk].liqToOx)[k]*xLiq[kk];
				sumOx += wtLiq[k]*bulkSystem[k].mw;
            }
            wtH2Otemp    = 100.0*wtLiq[14]*bulkSystem[14].mw/sumOx;
      		wtCO2temp    = 100.0*wtLiq[15]*bulkSystem[15].mw/sumOx;
      		printf("iter = %d, wt%% H2O = %g, wt%% CO2 = %g\n", iter, wtH2Otemp, wtCO2temp);
      		fprintf(resFile, ",%d,%g,%g\n", iter, wtH2Otemp, wtCO2temp);
	        
	      } else { // mixed H2O-CO2 case
	        double xLiq[19], rLiq[18], mu[19], targetMu[2], xOpt[2], xOptOld[2], f[2], fOld[2], df[2];
	        int first = TRUE, iter = 0;
	        
	        setModeToMixingLiq(FALSE);
	        actLiq(SECOND, residualDataInput[lastLiquid].t, residualDataInput[lastLiquid].p, (residualDataInput[lastLiquid].rLiq)[0], NULL, mu, NULL, NULL);
	        conLiq(THIRD, FOURTH, residualDataInput[lastLiquid].t,  residualDataInput[lastLiquid].p, NULL, NULL, (residualDataInput[lastLiquid].rLiq)[0], xLiq, NULL, NULL, NULL);
	        for (k=0; k<nlc; k++) fprintf(resFile, ",%g", xLiq[k]);
	        
	        targetMu[0] = mu[18] + resVar[0]*1000.0*3.0;
	        targetMu[1] = mu[14] + resVar[1]*1000.0*3.0;
	        printf("target mu[H2O] = %g mu[CO2] = %g X[CO2] = %g X[H2O] = %g\n", targetMu[0], targetMu[1], xLiq[14], xLiq[18]);
	        f[0] = 1000.0;
	        f[1] = 1000.0;
	        xOpt[0]    =  xLiq[18];
	        xOpt[1]    =  xLiq[14];
	        
	        while (((fabs(f[0]) > 1.0e-1) || (fabs(f[1]) > 1.0e-1)) && (iter < 100)) {
	        	xLiq[18] = xOpt[0];
	        	xLiq[14] = xOpt[1];
	        	conLiq(SECOND, THIRD, residualDataInput[lastLiquid].t,  residualDataInput[lastLiquid].p, NULL, xLiq, rLiq, NULL, NULL, NULL, NULL);
	        	actLiq(SECOND, residualDataInput[lastLiquid].t, residualDataInput[lastLiquid].p, rLiq, NULL, mu, NULL, NULL);
	            f[0] = mu[18] - targetMu[0];
	            f[1] = mu[14] - targetMu[1];
	            
	            if (first) {
	                xOptOld[0] = xLiq[18];
	                xOptOld[1] = xLiq[14];
	            	if (resVar[0] > 0.0)  xOpt[0] = 1.05*xLiq[18]; else xOpt[0] = xLiq[18]/1.05;
	            	if (resVar[1] > 0.0)  xOpt[1] = 1.05*xLiq[14]; else xOpt[1] = xLiq[14]/1.05;
	            	fOld[0] = f[0];
	            	fOld[1] = f[1];
	            	first = FALSE;
	            } else {
	                int update0 = (xOpt[0] != xOptOld[0]);
	                int update1 = (xOpt[1] != xOptOld[1]);
	        		df[0] = (f[0]-fOld[0])/(xOpt[0]-xOptOld[0]);
	        		df[1] = (f[1]-fOld[1])/(xOpt[1]-xOptOld[1]);
	        		xOptOld[0] = xOpt[0];
	        		xOptOld[1] = xOpt[1];
	        		fOld[0] = f[0];
	        		fOld[1] = f[1];
	        		if (update0) xOpt[0] -= f[0]/df[0];
	        		if (update1) xOpt[1] -= f[1]/df[1];
	        		if (xOpt[0] < 0.0) xOpt[0] = 0.0001;
	        		if (xOpt[0] > 2.0) xOpt[0] = 1.9999;
	        		if (xOpt[1] < 0.0) xOpt[1] = 0.0001;
	        		if (xOpt[1] > 2.0) xOpt[1] = 1.9999;
	            }
	            iter++;
	            printf("iter = %d, f[0] = %g, xOpt[0] = %g, f[1] = %g, xOpt[1] = %g\n", iter, f[0], xOpt[0], f[1], xOpt[1]);
	        }
	        
	        double wtLiq[16];
	        for (k=0, sumOx=0.0; k<nc; k++) {
             	for (kk=0, wtLiq[k]=0.0; kk<nlc; kk++) wtLiq[k] += (liquid[kk].liqToOx)[k]*xLiq[kk];
				sumOx += wtLiq[k]*bulkSystem[k].mw;
            }
            wtH2Otemp    = 100.0*wtLiq[14]*bulkSystem[14].mw/sumOx;
      		wtCO2temp    = 100.0*wtLiq[15]*bulkSystem[15].mw/sumOx;
      		printf("iter = %d, wt%% H2O = %g, wt%% CO2 = %g\n", iter, wtH2Otemp, wtCO2temp);
      		fprintf(resFile, ",%d,%g,%g\n", iter, wtH2Otemp, wtCO2temp);
	       
	        /*
	        // estimate pressure for mixed fluid
	        first = TRUE;
	        iter = 0;
	        f[0] = 1000.0;
	        f[1] = 1000.0;
	        conLiq(THIRD, FOURTH, residualDataInput[lastLiquid].t,  residualDataInput[lastLiquid].p, NULL, NULL, (residualDataInput[lastLiquid].rLiq)[0], xLiq, NULL, NULL, NULL);
	        double pOpt = residualDataInput[lastLiquid].p*1.05, pOptOld;
	        
	        while (((fabs(f[0]) > 1.0e-1) || (fabs(f[1]) > 1.0e-1)) && (iter < 100)) {
	        	conLiq(SECOND, THIRD, residualDataInput[lastLiquid].t,  pOpt, NULL, xLiq, rLiq, NULL, NULL, NULL, NULL);
	        	actLiq(SECOND, residualDataInput[lastLiquid].t, pOpt, rLiq, NULL, mu, NULL, NULL);
	            f[0] = mu[18] - targetMu[0];
	            f[1] = mu[14] - targetMu[1];
	            
	            if (first) {
	                pOptOld = pOpt;
	            	pOpt *= 1.05;
	            	fOld[0] = f[0];
	            	fOld[1] = f[1];
	            	first = FALSE;
	            } else {
	                df[0] = (f[0]-fOld[0])/(pOpt-pOptOld);
	        		df[1] = (f[1]-fOld[1])/(pOpt-pOptOld);
	        		pOptOld = pOpt;
	        		fOld[0] = f[0];
	        		fOld[1] = f[1];
	        		pOpt -= (f[0]/df[0] + f[1]/df[1])/2.0;
	        		if (pOpt <     1.0) pOpt =     1.0;
	        		if (pOpt > 50000.0) pOpt = 50000.0;
	            }
	            iter++;
	            printf("iter = %d, f[0] = %g, f[1] = %g, pOpt = %g\n", iter, f[0], f[1], pOpt);
	        }
	        
      		printf("iter = %d, p = %g\n", iter, pOpt);
      		fprintf(resFile, ",%d,%g\n", iter, pOpt);
	        */
	      }
	    // end of test on fluid phase
	    } else { 
	    	fprintf(resFile, "\n");
	    }
	    for (k=0; k<(solids[i].na+ne); k++) { xVar[k] = 0.0; depVar[k] = 0.0; resVar[k] = 0.0; }
	  } 
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
	  fprintf(resFile, "%d,%g,%g,%g,%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g", residualDataInput[j].LEPRnum, residualDataInput[j].t-273.15, 
	    residualDataInput[j].p/10000.0, residualDataInput[j].fo2, aluminousIndex[0], aluminousIndex[1], aluminousIndex[2], 
	    wtSiO2, wtAl2O3, wtCaO, wtNa2O, wtK2O, wtH2O, wtCO2, FEspecies[0], FEspecies[1], FEspecies[2], H2Ospecies[0], H2Ospecies[1], H2Ospecies[2]);
#else
	  fprintf(resFile, "%d,%g,%g,%g,%d,%d,%d,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g", residualDataInput[j].LEPRnum, residualDataInput[j].t-273.15, 
	    residualDataInput[j].p/10000.0, residualDataInput[j].fo2, aluminousIndex[0], aluminousIndex[1], aluminousIndex[2], 
	    wtSiO2, MgNum, alkIndex, wtMgO, wtCaO, wtH2O, wtCO2, FEspecies[0], FEspecies[1], FEspecies[2], H2Ospecies[0], H2Ospecies[1], H2Ospecies[2]);
#endif
	}
	
        for (k=0; k<solids[i].na; k++) if ( (i+1+k) == (residualDataInput[j].cIndex)[l]) { 
	  double *xSol = (double *) malloc((size_t) (solids[i].na)*sizeof(double));
	  (*solids[i].convert)(THIRD, FOURTH, residualDataInput[j].t, residualDataInput[j].p, NULL, NULL, 
	    (residualDataInput[j].rSol)[l], xSol, NULL, NULL, NULL, NULL);
	    xVar[k] = xSol[k];
	  depVar[k] = (residualDataInput[j].depenG)[l]; 
	  resVar[k] = (residualOutput[j].residuals)[l]; 
	  break; 
	}
	if (ne > 0) for (k=0; k<ne; k++) if ( (npc+neIndex[k]) == (residualDataInput[j].cIndex)[l]) {
	    xVar[solids[i].na+k] = 0.0;
	  depVar[solids[i].na+k] = (residualDataInput[j].depenG)[l]; 
	  resVar[solids[i].na+k] = (residualOutput[j].residuals)[l]; 
	  break;
	} 
	printMe = TRUE;
      }
      
      lastComponent = (residualDataInput[j].cIndex)[l];
      lastLiquid    = j;
    }

    if (printMe) {
      for (k=0; k<(solids[i].na+ne); k++) {
        if (depVar[k] != 0.0) fprintf(resFile, ",%g,%g,%g", xVar[k], depVar[k], resVar[k]); else fprintf(resFile, ",,,");
      }
      fprintf(resFile, "\n");
      for (k=0; k<(solids[i].na+ne); k++) { xVar[k] = 0.0; depVar[k] = 0.0; resVar[k] = 0.0; }
    }
    if (!firstTime) fclose(resFile);
    free(depVar);
    free(resVar);
    free(xVar);
    if (ne > 0) free(neIndex);
  }

  curStep++;
  workProcData->active = TRUE;
  return(FALSE);

  /*=========================================================================*/

  case TABLES:

    /*
    ******************************************************************************************************************************
    double  *aData;   The A[nEqn][(nW+nSdH+nSdS+nSdV)] matrix for the regression problem. Stored in C-style format for 2-d arrays.
    double  *bData;   bData[nEqn]: Dependent vector of the regression problem.
    double  *fo2Data; pData[nEqn]: pressure (bars)  			  
    int     *iData;   iData[nEqn]: index vector, entry equals solid component.
    int     *jData;   jData[nEqn]: index vector, entry equals solid phase.    
    int     *lData;   lData[nEqn]: index vector, entry equals liquid number.  
    double  *pData;   pData[nEqn]: pressure (bars)  			  
    double  *tData;   tData[nEqn]: temperature (K)  			  
    Boolean *zData;   zData[nEqn]: TRUE if equality constraint, FALSE if bound.
    ******************************************************************************************************************************
    */

  while (curSolid < (npc+nes)) {
#ifdef GRACE_PIPE
    Boolean updateGraph  = False;
#endif /* GRACE_PIPE */
    /*------------------------------------------------------------------------*/
    aveRes = 0.0; stdRes = 0.0; aveDep = 0.0; stdDep = 0.0;
    aveT   = 0.0; stdT   = 0.0; aveP   = 0.0; stdP   = 0.0; 
    avefo2 = 0.0; stdfo2 = 0.0;
    rResDep = 0.0; rResT = 0.0; rResP = 0.0; rResfo2 = 0.0;


    /*------------------------------------------------------------------------*/
    for (i=0, nRES=0; i<nLiquid; i++) if((nSol = residualDataInput[i].nSol) > 0) for (l=0; l<nSol; l++) {
      double  *xLiq = (double *) malloc((size_t) nls*sizeof(double));
      double *wtLiq = (double *) malloc((size_t) nlc*sizeof(double));
      if ((residualDataInput[i].cIndex)[l] == curSolid) {  /* (residualDataInput[i].isEqual)[l] == TRUE && */ 
        int isEqual = (residualDataInput[i].isEqual)[l];
	double sumOx;
        nRES++; 
        conLiq(THIRD, FOURTH, residualDataInput[i].t,  residualDataInput[i].p/10000.0, NULL, NULL,
          (residualDataInput[i].rLiq)[0], xLiq, NULL, NULL, NULL);
        for (k=0, sumOx=0.0; k<nc; k++) {
          for (kk=0, wtLiq[k]=0.0; kk<nlc; kk++) wtLiq[k] += (liquid[kk].liqToOx)[k]*xLiq[kk];
	  sumOx += wtLiq[k]*bulkSystem[k].mw;
        }
        /*--------------------------------------------------------------------*/
        wtSiO2vec[nRES-1] = 100.0*wtLiq[0]*bulkSystem[0].mw/sumOx;
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
        wtALKvec[nRES-1]  = 100.0*wtLiq[3]*bulkSystem[3].mw/sumOx + 100.0*wtLiq[4]*bulkSystem[4].mw/sumOx
	                  - 100.0*wtLiq[1]*bulkSystem[1].mw/sumOx; /* wt%: Na2O + K2O - Al2O3 */
	if ((1.0 - wtLiq[0]*bulkSystem[0].mw/sumOx) > 0.0)
	  wtALKvec[nRES-1] /= 1.0 - wtLiq[0]*bulkSystem[0].mw/sumOx; /* Normalized to SiO2 */
#endif
        /*--------------------------------------------------------------------*/
        fo2vec[nRES-1] = residualDataInput[i].fo2 /* - (-24441.9/residualDataInput[i].t + 8.290) */;
        avefo2 += (isEqual) ? fo2vec[nRES-1]         : 0.0;
        stdfo2 += (isEqual) ? SQUARE(fo2vec[nRES-1]) : 0.0;
        /*--------------------------------------------------------------------*/
        pvec[nRES-1] = residualDataInput[i].p/1000.0;
        aveP += (isEqual) ? pvec[nRES-1]         : 0.0;
        stdP += (isEqual) ? SQUARE(pvec[nRES-1]) : 0.0;
        /*--------------------------------------------------------------------*/
        tvec[nRES-1] = residualDataInput[i].t - 273.15;
        aveT += (isEqual) ? tvec[nRES-1]         : 0.0;
        stdT += (isEqual) ? SQUARE(tvec[nRES-1]) : 0.0;
        /*--------------------------------------------------------------------*/
        xvec[nRES-1] = ((residualDataInput[i].depenG)[l]-bAVE)/((bSTD > DBL_EPSILON) ? bSTD : 1.0);
        aveDep += (isEqual) ? xvec[nRES-1]         : 0.0;
        stdDep += (isEqual) ? SQUARE(xvec[nRES-1]) : 0.0;
        /*--------------------------------------------------------------------*/
        yvec[nRES-1] = (residualOutput[i].residuals)[l]/((resSTD > DBL_EPSILON) ? resSTD : 1.0);
        aveRes  += (isEqual) ? yvec[nRES-1]                : 0.0;
        stdRes  += (isEqual) ? SQUARE(yvec[nRES-1])        : 0.0;
        rResDep += (isEqual) ? yvec[nRES-1]*  xvec[nRES-1] : 0.0;
        rResT   += (isEqual) ? yvec[nRES-1]*  tvec[nRES-1] : 0.0;
        rResP   += (isEqual) ? yvec[nRES-1]*  pvec[nRES-1] : 0.0;
        rResfo2 += (isEqual) ? yvec[nRES-1]*fo2vec[nRES-1] : 0.0;
        /*--------------------------------------------------------------------*/
        mtypevec[nRES-1] = 1;
        if (curSolid < npc) for (j=0; j<10; j++) name[nRES-1][j] = (solids[curSolid].label)[j];
	else                for (j=0; j<10; j++) name[nRES-1][j] = (extraSolids[curSolid-npc].species)[j];

        if (yvec[nRES-1] < -2.0 || yvec[nRES-1] > 2.0) 
          updatePostclbOutliersDisplay(curSolid, (char *) ((curSolid < npc) ? solids[curSolid].label : extraSolids[curSolid-npc].species), 
            i, xvec[nRES-1], (isEqual) ? yvec[nRES-1] : 0.0, fo2vec[nRES-1], tvec[nRES-1], pvec[nRES-1], (isEqual) ? NULL : &yvec[nRES-1], NULL);
	    
#ifdef GRACE_PIPE
	if (!updateGraph) {  
	  updateGraph = True; 
	  curGraphSet++;
	  GracePrintf("g0.s%1.1d LINESTYLE 0\n",        curGraphSet);
	  GracePrintf("g1.s%1.1d LINESTYLE 0\n",        curGraphSet);
	  GracePrintf("g0.s%1.1d SYMBOL 2\n",           curGraphSet);
	  GracePrintf("g1.s%1.1d SYMBOL 2\n",           curGraphSet);
	  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",      curGraphSet);
	  GracePrintf("g1.s%1.1d SYMBOL FILL 1\n",      curGraphSet);
	  GracePrintf("g0.s%1.1d SYMBOL SIZE 0.5\n",    curGraphSet);
	  GracePrintf("g1.s%1.1d SYMBOL SIZE 0.5\n",    curGraphSet);
	  GracePrintf("g0.s%1.1d SYMBOL COLOR %d\n",    curGraphSet, curGraphSet - (int) (14 * floor(((double) curGraphSet)/14.0)));
	  GracePrintf("g1.s%1.1d SYMBOL COLOR %d\n",    curGraphSet, curGraphSet - (int) (14 * floor(((double) curGraphSet)/14.0)));
          GracePrintf("g0.s%1.1d LEGEND \"%10.10s\"\n", curGraphSet, (curSolid < npc) ? solids[curSolid].label : extraSolids[curSolid-npc].species);
          GracePrintf("g1.s%1.1d LEGEND \"%10.10s\"\n", curGraphSet, (curSolid < npc) ? solids[curSolid].label : extraSolids[curSolid-npc].species);
	  
	  GracePrintf("g0.s%1.1d LINESTYLE 0\n",        curGraphSet+npc+nes);
	  GracePrintf("g1.s%1.1d LINESTYLE 0\n",        curGraphSet+npc+nes);
	  GracePrintf("g0.s%1.1d SYMBOL 8\n",           curGraphSet+npc+nes);
	  GracePrintf("g1.s%1.1d SYMBOL 8\n",           curGraphSet+npc+nes);
	  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",      curGraphSet+npc+nes);
	  GracePrintf("g1.s%1.1d SYMBOL FILL 1\n",      curGraphSet+npc+nes);
	  GracePrintf("g0.s%1.1d SYMBOL SIZE 0.5\n",    curGraphSet+npc+nes);
	  GracePrintf("g1.s%1.1d SYMBOL SIZE 0.5\n",    curGraphSet+npc+nes);
	  GracePrintf("g0.s%1.1d SYMBOL COLOR %d\n",    curGraphSet+npc+nes, curGraphSet - (int) (14 * floor(((double) curGraphSet)/14.0)));
	  GracePrintf("g1.s%1.1d SYMBOL COLOR %d\n",    curGraphSet+npc+nes, curGraphSet - (int) (14 * floor(((double) curGraphSet)/14.0)));
          GracePrintf("g0.s%1.1d LEGEND \"%10.10s\"\n", curGraphSet+npc+nes, (curSolid < npc) ? solids[curSolid].label : extraSolids[curSolid-npc].species);
          GracePrintf("g1.s%1.1d LEGEND \"%10.10s\"\n", curGraphSet+npc+nes, (curSolid < npc) ? solids[curSolid].label : extraSolids[curSolid-npc].species);
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
	  GracePrintf("g2.s%1.1d LINESTYLE 0\n",        curGraphSet);
	  GracePrintf("g2.s%1.1d SYMBOL 2\n",           curGraphSet);
	  GracePrintf("g2.s%1.1d SYMBOL FILL 1\n",      curGraphSet);
	  GracePrintf("g2.s%1.1d SYMBOL SIZE 0.5\n",    curGraphSet);
	  GracePrintf("g2.s%1.1d SYMBOL COLOR %d\n",    curGraphSet, curGraphSet - (int) (14 * floor(((double) curGraphSet)/14.0)));
          GracePrintf("g2.s%1.1d LEGEND \"%10.10s\"\n", curGraphSet, (curSolid < npc) ? solids[curSolid].label : extraSolids[curSolid-npc].species);
	  
	  GracePrintf("g2.s%1.1d LINESTYLE 0\n",        curGraphSet+npc+nes);
	  GracePrintf("g2.s%1.1d SYMBOL 8\n",           curGraphSet+npc+nes);
	  GracePrintf("g2.s%1.1d SYMBOL FILL 1\n",      curGraphSet+npc+nes);
	  GracePrintf("g2.s%1.1d SYMBOL SIZE 0.5\n",    curGraphSet+npc+nes);
	  GracePrintf("g2.s%1.1d SYMBOL COLOR %d\n",    curGraphSet+npc+nes, curGraphSet - (int) (14 * floor(((double) curGraphSet)/14.0)));
          GracePrintf("g2.s%1.1d LEGEND \"%10.10s\"\n", curGraphSet+npc+nes, (curSolid < npc) ? solids[curSolid].label : extraSolids[curSolid-npc].species);
#endif
	}
	if (isEqual || (!isEqual && (yvec[nRES-1] != 0.0))) {
          GracePrintf("g0.s%1.1d POINT %lf, %lf\n", (isEqual) ? curGraphSet : curGraphSet+npc+nes, tvec[nRES-1], yvec[nRES-1]*resSTD);
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
          GracePrintf("g1.s%1.1d POINT %lf, %lf\n", (isEqual) ? curGraphSet : curGraphSet+npc+nes, wtSiO2vec[nRES-1], yvec[nRES-1]*resSTD);	
          GracePrintf("g2.s%1.1d POINT %lf, %lf\n", (isEqual) ? curGraphSet : curGraphSet+npc+nes, wtALKvec[nRES-1], yvec[nRES-1]*resSTD);	
#else
          GracePrintf("g1.s%1.1d POINT %lf, %lf\n", (isEqual) ? curGraphSet : curGraphSet+npc+nes, pvec[nRES-1], yvec[nRES-1]*resSTD);	
#endif
	}
#endif /* GRACE_PIPE */

      }
      free(xLiq);
      free(wtLiq);
    }
    
#ifdef GRACE_PIPE
    if (updateGraph) {
      GracePrintf("WITH G0\n"); GracePrintf("AUTOSCALE\n"); 
      GracePrintf("WITH G1\n"); GracePrintf("AUTOSCALE\n"); 
#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
      GracePrintf("WITH G2\n"); GracePrintf("AUTOSCALE\n"); 
#endif
      GracePrintf("REDRAW\n");   
    }
#endif /* GRACE_PIPE */
 
    if (nRES > 0) {
      double nAtoms = (curSolid < npc) ? solids[curSolid].nAtoms : extraSolids[curSolid-npc].nAtoms;
      aveRes /= (double) nRES; stdRes = (nRES > 1) ? sqrt((stdRes - ((double) nRES)*SQUARE(aveRes))/((double) (nRES-1))) : 0.0;
      aveDep /= (double) nRES; stdDep = (nRES > 1) ? sqrt((stdDep - ((double) nRES)*SQUARE(aveDep))/((double) (nRES-1))) : 0.0;
      aveT   /= (double) nRES; stdT   = (nRES > 1) ? sqrt((stdT   - ((double) nRES)*SQUARE(aveT))  /((double) (nRES-1))) : 0.0;
      aveP   /= (double) nRES; stdP   = (nRES > 1) ? sqrt((stdP   - ((double) nRES)*SQUARE(aveP))  /((double) (nRES-1))) : 0.0;
      avefo2 /= (double) nRES; stdfo2 = (nRES > 1) ? sqrt((stdfo2 - ((double) nRES)*SQUARE(avefo2))/((double) (nRES-1))) : 0.0;

      fprintf(sumFile,"%s,%d,%g,%g,%g,%g,%g,%g,%g,%g,", (curSolid < npc) ? solids[curSolid].label : extraSolids[curSolid-npc].species, 
	nRES, aveDep, aveRes, aveRes*resSTD, nAtoms, aveRes*resSTD*nAtoms, avefo2, aveT, aveP);
      fprintf(sumFile,"%g,%g,%g,%g,%g,%g,%g,", stdDep, stdRes, stdRes*resSTD, stdRes*resSTD*nAtoms, stdfo2, stdT, stdP);

      rResDep = (nRES > 1 && stdRes > 0.0 && stdDep > 0.0) ? (rResDep - ((double) nRES)*aveRes*aveDep) / ( ((double) (nRES-1))*stdRes*stdDep ) : 0.0;
      rResT   = (nRES > 1 && stdRes > 0.0 && stdT > 0.0)   ? (rResT   - ((double) nRES)*aveRes*aveT  ) / ( ((double) (nRES-1))*stdRes*stdT   ) : 0.0;
      rResP   = (nRES > 1 && stdRes > 0.0 && stdP > 0.0)   ? (rResP   - ((double) nRES)*aveRes*aveP  ) / ( ((double) (nRES-1))*stdRes*stdP   ) : 0.0;
      rResfo2 = (nRES > 1 && stdRes > 0.0 && stdfo2 > 0.0) ? (rResfo2 - ((double) nRES)*aveRes*avefo2) / ( ((double) (nRES-1))*stdRes*stdfo2 ) : 0.0;

      fprintf(sumFile,"%g,%g,%g,%g\n", rResDep, rResfo2, rResT, rResP);

      updatePostclbStatisticsDisplay(curSolid, (char *) ((curSolid < npc) ? solids[curSolid].label : extraSolids[curSolid-npc].species), 
	 nRES, aveDep, aveRes, avefo2, aveT, aveP, stdDep, stdRes, stdfo2, stdT, stdP, rResDep, rResfo2, rResT, rResP);
    }  

    curSolid++;
    workProcData->active = TRUE;
    return(FALSE);
  }

  curStep++;
  workProcData->active = TRUE;
  return(FALSE);

  /*=========================================================================*/

  case FINAL:

  fclose(sumFile);

  free(fo2vec);
  free(pvec);
  free(tvec);
  free(xvec);
  free(yvec);
  free(mtypevec);
  for (i=0; i<nEqn; i++) free(name[i]);
  free(name);

  curStep = 0;
  curSolid = 0;
  workProcData->active = FALSE;
  return(TRUE);

  } /* end switch */

  return(TRUE);
}

/* end of file POSTCLB.C */
