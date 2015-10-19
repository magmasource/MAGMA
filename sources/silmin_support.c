const char *silmin_support_ver(void) { return "$Id: silmin_support.c,v 1.8 2009/04/24 20:51:09 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: silmin_support.c,v $
MELTS Source Code: RCS Revision 1.6  2008/03/06 17:51:23  ghiorso
MELTS Source Code: RCS New fluid fractionation mode and other enhancements.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2007/08/23 16:09:40  ghiorso
MELTS Source Code: RCS Database updates.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2007/06/08 17:25:43  ghiorso
MELTS Source Code: RCS Added code to allow regression of Ghiorso EOS parameters
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2006/10/20 00:59:22  ghiorso
MELTS Source Code: RCS (1) Made initial modifications for thread safe code.
MELTS Source Code: RCS (2) Added support for XML I/O in batch mode
MELTS Source Code: RCS (3) Added support for Melts-batch listener for eventual integration into VIGMCS
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
MELTS Source Code: RCS Revision 1.4  2003/05/03 18:43:56  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2003/05/01 17:33:54  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2003/04/28 20:44:46  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.12  1997/06/21  22:49:26  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.11  1997/05/03  20:23:06  ghiorso
 * *** empty log message ***
 *
 * Revision 3.10  1997/03/27  17:03:10  ghiorso
 * *** empty log message ***
 *
 * Revision 3.9  1996/09/24  20:33:20  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.8  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.7  1995/11/23  22:37:42  ghiorso
 * Final implementation of subsolidus fO2 buffering.
 *
 * Revision 3.6  1995/11/01  22:40:27  ghiorso
 * Implementation of subsolidus options after Asimow.
 * Additional implementation of nepheline solid solutions.
 *
 * Revision 3.5  1995/09/04  23:30:20  ghiorso
 * Added new function copySilminStateStructure, for copy the silminState
 * structure. Called in create_xy_plot.padb.c for allocating history records.
 *
 * Revision 3.4  1995/09/04  20:01:28  ghiorso
 * Update to allow display of bulk composition (in grams) in the text entry
 * fields of the main silmin display. Liquid composition is no longer
 * display here, and is available only through the popup selection.
 *
 * Revision 3.3  1995/09/01  23:53:03  ghiorso
 * Modifications made to update interface for V3.x and consolidate
 * Graph Widgets
 *
 * Revision 3.2  1995/08/31  00:25:55  ghiorso
 * Removed References to multiple user plots
 *
 * Revision 3.1  1995/08/18  19:14:22  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Collection of support functions for crystallization calculations
**
**      allocSilminStatePointer()
**      Function to allocate space for the SilminState structure
**
**      checkStateAgainstInterface()
**      Function to evaluate state of interface display contained in the 
**      INTERFACE.H structures:
**        (1) state of toggle button widgets:
**            tg_path_none, tg_path_hm, tg_path_nno, tg_path_fmq, tg_path_iw,
**            tg_isenthalpic, tg_isochoric, tg_fractionation,
**        (2) compositionValues
**        (3) debugEntries
**        (4) tpValues
**        (5) assimilantValues and assimilantUnits
**        (6) magmaValues
**        (7) includedSolids
**      and compare it to the state of the system contained in the SILMIN.H
**      structures:
**        (1) silminState. 
**      returning a flag (see global macros (defined below) indicating what has 
**      been done.
**
**      update*()
**      Functions to update the various display elements, including the
**      text widgets, label widgets and graphs. The "member" argument 
**      corresponds to a partricular entry to update. These are defined
**      by macros in INTERFACE.H. Passing a negative argument will 
**      update all entries.
**
**      (file: SILMIN_SUPPORT.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  September 5, 1991
**              function: checkStateAgainstInterface()
**                preliminary version finished September 10, 1991
**              function: evaluateSaturationState()
**                preliminary version finished September 11, 1991
**              function getEqualityConstraints()
**                preliminary version finished September 12, 1991
**              function getProjGradientAndHessian()
**                altered call to liqCon on September 13, 1991 as
**                  part of code development for the function
**                create code to transform intensive to extensive
**                  derivatives of the thermodynamic potential
**                altered call to (*solids[].convert) on September 14, 1991
**                  as part of code development for the function
**                preliminary version finished September 17, 1991
**              function linearSearch()
**                preliminary version finished September 18, 1991
**      V1.0-2  Mark S. Ghiorso  September 18, 1991
**              Removed major numerical routines, left those pertaining
**                to interface update and display
**      V1.0-3  Mark S. Ghiorso  September 19, 1991
**              Began work on update*() functions for interface display
**                               September 20, 1991
**              continues ...
**      V1.0-4  Mark S. Ghiorso  September 24, 1991
**              Altered parameter list to (*solids[].convert)
**      V1.0-5  Mark S. Ghiorso  October 15, 1991
**              (1) Modifications to references for arrays 
**                  silminState->solidComp and silminState->solidDelta
**                  to allow for immiscible solid phases
**              (2) Initialized silminState->nSolidCoexist to count number
**                  of solid phases
**              (3) The module updateSolidGW needs to be rewritten in light
**                  of these and other functionality considerations
**              (4) Complete reorganization of updateSolidGW logic (includes
**                  extensions for immiscible solid phases)
**      V1.0-6  Mark S. Ghiorso  October 18, 1991
**              (1) Added graph legend code
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  November 23, 1991
**              (1) Removed references to debug entries on interface
**                  display and menu bar
**      V2.0-3  Mark S. Ghiorso  November 27, 1991
**              (1) Complete rewrite of updateSolidADB to utilize the
**                  Vlist widget structure and output affinities
**      V2.0-4  Mark S. Ghiorso  December 10, 1991
**              (1) Reorganized assimilantValues references and removed
**                  magmaValues and magma_padb references
**      V2.0-5  Mark S. Ghiorso  December 14, 1991
**              (1) Revised assimilation algorithm and eliminated magma
**                  mixing code
**      V2.0-6  Mark S. Ghiorso  December 21, 1991
**              (1) Inserted code from silmin (SILMIN.C) to update 
**                  silminState->liquidComp when display composition of 
**                  liquid is altered
**      V2.0-7  Mark S. Ghiorso  January 2, 1992
**              (1) Implemented changes for fractionation mode
**      V2.0-8  Mark S. Ghiorso  January 4, 1992
**              (1) Altered resource declarations for graph widget from
**                  XtN -> GwN
**              (2) Altered calls to polyline() and polymarker() to
**                  GwPolyline() and GwPolymarker()
**              (3) Added calls to GwStartBatchUpdate() and GwEndBatchUpdate()
**                  surrounding the liquid and solid graph poly* calls
**              (4) Added support for display on user_graph (AFM only)
**      V2.0-9  Mark S. Ghiorso  January 6, 1992
**              (1) Corrected bound constraint algorithm in userGraph by
**                  eliminating multiple "identical" points connected by
**                  polylines.
**      V2.0-10 Mark S. Ghiorso  January 10, 1992
**              (1) Added wt % assimilation support 
**      V2.0-11 Mark S. Ghiorso  January 15, 1992
**              (1) removed definition of updateAssimilantPADB()
**                  (now defined in create_assimilant_padb.c - we needed
**                  locally static widget names)
**      V2.0-12 Mark S. Ghiorso  February 19, 1992
**              (1) Corrected minor casting violations for ANSI C compliance
**              (2) Removed global dependence on arg_set
**      V3.0-1  Mark S. Ghiorso  April 27, 1992
**              (1) Begin nodifications for f O2 buffering of reaction path
**      V3.0-2  Mark S. Ghiorso  May 1, 1992
**              (1) Added correction to silminState->oxygen value when
**                  user modifies bulk composition
**      V3.0-3  Mark S. Ghiorso  May 4, 1992
**              (1) Added initialization of space for cylSolids in
**                  allocSilminStatePointer() 
**      V3.1-1  Mark S. Ghiorso  July 13, 1992
**              (1) Added a nrw column (mineral formulas) to the phases
**                  vList widget
**      V3.1-2  Mark S. Ghiorso  September 29, 1992
**              Converted TextField to Text widgets as a bug workaround 
**              for DECWindows Motif V 1.1
**      V3.1-3  Mark S. Ghiorso  June 14, 1993
**              Added code for new fo2 path constraints
**      V3.1-4  Mark S. Ghiorso  September 21, 1993
**              XtFree -> XmStringFree
**      V3.1-5  Mark S. Ghiorso  September 29, 1993
**              Modified call to realloc to catch zero pointer (SPARC port)
**      V3.1-6  Mark S. Ghiorso  April 5, 1994
**              Added #ifdef __osf__ to correct 64 bit errors
**      V4.0-1  Mark S. Ghiorso  May 11, 1994
**              (1) Modified calls to *vmix to reflect additional derivatives
**              (2) Removed reference to grove, walker plots
**              (3) Added reference to isentropic constraints
**              (4) Removed warning dialogs if isenthalpic, isentropic or
**                  isochoric constraints are switched on
**                               June 9, 1994
**              (5) Added section to compute thermodynamic properties of 
**                  assimilant and store them in silminState->assimTD
**                               June 11, 1994
**              (6) Fixed logic error in computing assimTD structure
**                               June 13, 1994
**              (7) Added three new functions to adjust T and P for "update"
**                  changes in enthalpy, entropy or volume
**                  void correctTforChangeInEnthalpy(void)
**                  void correctTforChangeInEntropy(void)
**                  void correctPforChangeInVolume(void)
**                               June 15, 1994
**              (8) Added interface checks for enthalpy, entropy and 
**                  volume terms in tp_values[]
**                               June 16, 1994
**              (9) Corrected error in 4.0-1.7 routines on abnormal
**                  termination for negative residuals
**                               July 2, 1994
**              (10) Altered convergence criteria for 4.0-1.7 routines 
**                   (scaled test on residuals)
**      V4.1-1  Mark S. Ghiorso
**              (1) Experiments with convergence in correctTforChangeInEntropy
**      V4.1-2  Mark S. Ghiorso  February 27, 1995
**              (1) Altered convergence criteria in correctTforChangeInEnthalpy,
**                  correctTforChangeInEntropy, correctPforChangeInVolume
**      V4.1-3  Mark S. Ghiorso  March 25, 1995
**              (1) Disallowed constraints on both fo2 and enthalpy or
**                  entropy or volume
**      V5.1-1  Paul D. Asimow  April 26, 1995
**              (1) Increase storage size of incSolids to allow for liquid
**      V5.2-1  Paul D. Asimow  August 2, 1995
**              (1) Enable subsolidus buffering -- changes to correctTforChange
**              InEnthalpy, correctTforChangeInEntropy, and correctPforChangeIn
**              Volume.
**              (2) New functions copyStateInfo and copyThermoData
**              (3) New function subsolidusmuO2 for subsolidus buffering
**              (4) New function addOrDropLiquid supports liquid-absent
**                  phase drops and adds
**--
*/

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "silmin.h"                 /*SILMIN structures include file        */
#include "recipes.h"                /* numerical recipes include file       */

#ifndef BATCH_VERSION
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/Text.h>
#include <Xm/ToggleBG.h>

#include "interface.h"              /*Specific external declarations        */
#include "vframe.h"                 /*vframe widget include file            */
#include "vheader.h"                /*vheader widget include file           */
#include "vlist.h"                  /*vlist widget include file             */
#else
#define True '\001'
#endif

#ifdef DEBUG
#undef DEBUG
#endif

#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))

Constraints *allocConstraintsPointer(void)
{
  Constraints *p;
  
  p = (Constraints *) malloc((unsigned) sizeof(Constraints));
  /*p->lambda      = (double *)  malloc((unsigned) (nc+4)*sizeof(double));
  p->liquidDelta = (double *)  malloc((unsigned)    nlc*sizeof(double));
  p->solidDelta  = (double **) malloc((unsigned)    npc*sizeof(double *));
  for (i=0; i<npc; i++) p->solidDelta[i] = (double *) malloc((unsigned) sizeof(double));*/
  return p;
}

void destroyConstraintsStructure(void *pt)
{
  Constraints *p = pt;
  /*int i;

  for (i=0; i<npc; i++) free((p->solidDelta)[i]);
  free(p->lambda);
  free(p->liquidDelta);
  free(p->solidDelta);*/
  free(p);
}

SilminState *allocSilminStatePointer(void)
{
  int i;
  SilminState *p;
  
  /* assume initialization with zero bytes yields default entries */
  p = (SilminState *) calloc((size_t) 1, sizeof(SilminState));

  /* allocate space for mandatory entries with zero bytes         */
  p->bulkComp       = (double *)     calloc((size_t)  nc,     sizeof(double));
  p->dspBulkComp    = (double *)     calloc((size_t)  nc,     sizeof(double));
  p->liquidComp     = (double **)    calloc((size_t)   1,     sizeof(double *));
  p->liquidComp[0]  = (double *)     calloc((size_t) nlc,     sizeof(double));
  p->liquidDelta    = (double **)    calloc((size_t)   1,     sizeof(double *));
  p->liquidDelta[0] = (double *)     calloc((size_t) nlc,     sizeof(double));
  p->solidComp      = (double **)    calloc((size_t) npc,     sizeof(double *));
  p->nSolidCoexist  = (int *)        calloc((size_t) npc,     sizeof(int));
  p->solidDelta     = (double **)    calloc((size_t) npc,     sizeof(double *));
  p->incSolids      = (int *)        calloc((size_t) (npc+1), sizeof(int));   
  p->cylSolids      = (int *)        calloc((size_t) npc,     sizeof(int));   

  for (i=0; i<npc; i++) {
    (p->solidComp)[i]  = (double *) calloc((size_t) 1, sizeof(double));
    (p->solidDelta)[i] = (double *) calloc((size_t) 1, sizeof(double));
  }

  return p;
}

void destroySilminStateStructure(void *pt)
{
  SilminState *p = pt;
  int i;
  
  for (i=0; i<MAX(1,p->nLiquidCoexist);i++) {
    free((p->liquidComp)[i]);
    free((p->liquidDelta)[i]);
  }

  for (i=0; i<npc; i++) {
    free((p->solidComp)[i]);
    free((p->solidDelta)[i]);
  }
  
  free(p->bulkComp);
  free(p->dspBulkComp);
  free(p->liquidComp);
  free(p->liquidDelta);
  free(p->solidComp);
  free(p->nSolidCoexist);
  free(p->solidDelta);
  free(p->incSolids);   
  free(p->cylSolids);   
  
  free(p);
}

SilminState *copySilminStateStructure(SilminState *pOld, SilminState *pNew)
{
  int i, j, k, ns;

  if (pNew == (SilminState *) NULL) {
    /* allocate space for the SilminState structure and fill with defaults   */
    pNew = (SilminState *) calloc((size_t) 1, sizeof(SilminState));

    /* copy across non-pointer specific entries                              */
    memcpy(pNew, pOld, sizeof(SilminState));

    /* annihilate copies pointers of mandatory arrays                        */ 
    pNew->bulkComp       = (double *)     calloc((size_t)  nc,     sizeof(double));
    pNew->dspBulkComp    = (double *)     calloc((size_t)  nc,     sizeof(double));
    pNew->liquidComp     = (double **)    calloc((size_t)   1,     sizeof(double *));
    pNew->liquidComp[0]  = (double *)     calloc((size_t) nlc,     sizeof(double));
    pNew->liquidDelta    = (double **)    calloc((size_t)   1,     sizeof(double *));
    pNew->liquidDelta[0] = (double *)     calloc((size_t) nlc,     sizeof(double));
    pNew->solidComp      = (double **)    calloc((size_t) npc,     sizeof(double *));
    pNew->nSolidCoexist  = (int *)        calloc((size_t) npc,     sizeof(int));
    pNew->solidDelta     = (double **)    calloc((size_t) npc,     sizeof(double *));
    pNew->incSolids      = (int *)        calloc((size_t) (npc+1), sizeof(int));   
    pNew->cylSolids      = (int *)        calloc((size_t) npc,     sizeof(int));   

    /* copy across mandatory entry arrays (space has already been allocated) */
    for (i=0; i<nc; i++) {
      (pNew->bulkComp)[i]      = (pOld->bulkComp)[i];
      (pNew->dspBulkComp)[i]   = (pOld->dspBulkComp)[i];
    }
    for (i=0; i<nlc; i++) {
      (pNew->liquidComp)[0][i]    = (pOld->liquidComp)[0][i];
      (pNew->liquidDelta)[0][i]   = (pOld->liquidDelta)[0][i];
    }
    for (i=0; i<npc; i++) {
      (pNew->nSolidCoexist)[i] = (pOld->nSolidCoexist)[i];
      (pNew->incSolids)[i]     = (pOld->incSolids)[i];
      (pNew->cylSolids)[i]     = (pOld->cylSolids)[i];
    }
    (pNew->incSolids)[npc]     = (pOld->incSolids)[npc];

    /* Now copy the problem specific entries                                 */
    if (pNew->nLiquidCoexist > 1) {
      pNew->liquidComp  = (double **) realloc(pNew->liquidComp,  (size_t) (pNew->nLiquidCoexist)*sizeof(double *));
      pNew->liquidDelta = (double **) realloc(pNew->liquidDelta, (size_t) (pNew->nLiquidCoexist)*sizeof(double *));
      for (i=1; i<pNew->nLiquidCoexist; i++) {
        (pNew->liquidComp)[i]  = (double *) calloc((size_t) nlc, sizeof(double));
        (pNew->liquidDelta)[i] = (double *) calloc((size_t) nlc, sizeof(double));
	for (j=0; j<nlc; j++) {
	  (pNew->liquidComp)[i][j]  = (pOld->liquidComp)[i][j];
	  (pNew->liquidDelta)[i][j] = (pOld->liquidDelta)[i][j];
	}
      }
    }
    
    for (i=0; i<npc; i++) {
      if ((ns = (pOld->nSolidCoexist)[i]) > 0) {
        if (solids[i].type == PHASE) {
          (pNew->solidComp)[i]  = (double *) malloc((unsigned) ns*sizeof(double));
          (pNew->solidDelta)[i] = (double *) malloc((unsigned) ns*sizeof(double));
          for (j=0; j<ns; j++) {
            (pNew->solidComp)[i][j]  = (pOld->solidComp)[i][j];
            (pNew->solidDelta)[i][j] = (pOld->solidDelta)[i][j];
          }
          if (solids[i].na > 1) {
	    for (k=0; k<solids[i].na; k++) {
              (pNew->solidComp)[i+1+k]  = (double *) malloc((unsigned) ns*sizeof(double));
              (pNew->solidDelta)[i+1+k] = (double *) malloc((unsigned) ns*sizeof(double));
              for (j=0; j<ns; j++) {
                (pNew->solidComp)[i+1+k][j]  = (pOld->solidComp)[i+1+k][j];
                (pNew->solidDelta)[i+1+k][j] = (pOld->solidDelta)[i+1+k][j];
              }
            }
            i += solids[i].na;
	  }
        }
      } else {
        (pNew->solidComp)[i]  = (double *) calloc((unsigned) 1, sizeof(double));
        (pNew->solidDelta)[i] = (double *) calloc((unsigned) 1, sizeof(double));
      }
    }
  
    if ((pOld->fractionateSol || pOld->fractionateFlu) && (pOld->nFracCoexist != NULL) && (pOld->fracSComp != NULL)) {
      pNew->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
      pNew->nFracCoexist = (int *)     calloc((unsigned) npc, sizeof(int));
      for (i=0; i<npc; i++) {
        (pNew->nFracCoexist)[i] = (pOld->nFracCoexist)[i];
        if ((ns = (pOld->nFracCoexist)[i]) > 0) {
          (pNew->fracSComp)[i]  = (double *) malloc((unsigned) ns*sizeof(double));
          for (j=0; j<ns; j++) (pNew->fracSComp)[i][j] = (pOld->fracSComp)[i][j];
	  if (solids[i].na > 1) for (k=0; k<solids[i].na; k++) {
              (pNew->fracSComp)[i+1+k]  = (double *) malloc((unsigned) ns*sizeof(double));
              for (j=0; j<ns; j++) (pNew->fracSComp)[i+1+k][j] = (pOld->fracSComp)[i+1+k][j];
	  }
        }
      }  
    }

    if (pOld->fractionateLiq && (pOld->fracLComp != NULL)) {
      pNew->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
      for (i=0; i<nlc; i++) (pNew->fracLComp)[i] = (pOld->fracLComp)[i];
    }

    if (pOld->assimilate) {
      pNew->dspAssimComp  
        = (double **) calloc((unsigned) (npc+nc), sizeof(double *));
      pNew->assimComp     
        = (double **) calloc((unsigned) (npc+nlc), sizeof(double *));
      pNew->nDspAssimComp 
        = (int *)     calloc((unsigned) (npc+nc), sizeof(int));
      pNew->nAssimComp    
        = (int *)     calloc((unsigned) (npc+nlc), sizeof(int));
      for (i=0; i<(npc+nc); i++) {
        (pNew->nDspAssimComp)[i] = (pOld->nDspAssimComp)[i];
        if ((ns = (pOld->nDspAssimComp)[i]) > 0) {
          (pNew->dspAssimComp)[i]  
            = (double *) malloc((unsigned) ns*sizeof(double));
          for (j=0; j<ns; j++) 
            (pNew->dspAssimComp)[i][j] = (pOld->dspAssimComp)[i][j];
        }
      }
      for (i=0; i<(npc+nlc); i++) {
        (pNew->nAssimComp)[i] = (pOld->nAssimComp)[i];
        if ((ns = (pOld->nAssimComp)[i]) > 0) {
          (pNew->assimComp)[i] = (double *) malloc((unsigned) ns*sizeof(double));
          for (j=0; j<ns; j++) (pNew->assimComp)[i][j] = (pOld->assimComp)[i][j];
        }
      }
    }
  } else {
    /* copy across mandatory entries (space has already been allocated)      */
    for (i=0; i<nc; i++) (pNew->bulkComp)[i]    = (pOld->bulkComp)[i];
    for (i=0; i<nc; i++) (pNew->dspBulkComp)[i] = (pOld->dspBulkComp)[i];
    memcpy(&(pNew->bulkTD), &(pOld->bulkTD), sizeof(ThermoData));
    for (i=0; i<nlc; i++) (pNew->liquidComp)[0][i]  = (pOld->liquidComp)[0][i];
    for (i=0; i<nlc; i++) (pNew->liquidDelta)[0][i] = (pOld->liquidDelta)[0][i];
    pNew->liquidMass = pOld->liquidMass;
    memcpy(&(pNew->liquidTD), &(pOld->liquidTD), sizeof(ThermoData));

    if (pNew->nLiquidCoexist != pOld->nLiquidCoexist) {
      if (pNew->nLiquidCoexist > pOld->nLiquidCoexist) for (i=pOld->nLiquidCoexist; i<pNew->nLiquidCoexist; i++) {
        free((pNew->liquidComp)[i]);
        free((pNew->liquidDelta)[i]);
      }
      pNew->liquidComp  = (double **) realloc(pNew->liquidComp,  (size_t) (pNew->nLiquidCoexist)*sizeof(double *));
      pNew->liquidDelta = (double **) realloc(pNew->liquidDelta, (size_t) (pNew->nLiquidCoexist)*sizeof(double *));
      if (pNew->nLiquidCoexist < pOld->nLiquidCoexist) for (i=pNew->nLiquidCoexist; i<pOld->nLiquidCoexist; i++) {
        pNew->liquidComp[i]  = (double *) calloc((size_t) nlc, sizeof(double));
        pNew->liquidDelta[i] = (double *) calloc((size_t) nlc, sizeof(double));
      }
      for (i=1; i<pOld->nLiquidCoexist; i++) for (j=0; j<nlc; j++) {
        pNew->liquidComp[i][j]  = pOld->liquidComp[i][j];
        pNew->liquidDelta[i][j] = pOld->liquidDelta[i][j];
      }
      pNew->nLiquidCoexist = pOld->nLiquidCoexist;
    }

    for (i=0; i<npc; i++) {
      if ((solids[i].type == PHASE) && ((pNew->nSolidCoexist)[i] != (pOld->nSolidCoexist)[i])) {
        int newSize = MAX((pOld->nSolidCoexist)[i], 1);
        pNew->solidComp[i]  = (double *) realloc(pNew->solidComp[i], (unsigned) newSize*sizeof(double));
        pNew->solidDelta[i] = (double *) realloc(pNew->solidDelta[i],(unsigned) newSize*sizeof(double));
	if (solids[i].na > 1) {
	  for (j=0; j<solids[i].na; j++) {
            pNew->solidComp[i+1+j]  = (double *) realloc(pNew->solidComp[i+1+j], (unsigned) newSize*sizeof(double));
            pNew->solidDelta[i+1+j] = (double *) realloc(pNew->solidDelta[i+1+j],(unsigned) newSize*sizeof(double));
	  }
	  i += solids[i].na;
	}
      }
    }

    for (i=0; i<npc; i++) {
      for (j=0; j<(pOld->nSolidCoexist)[i]; j++) {
        pNew->solidComp[i][j]  = pOld->solidComp[i][j];
        pNew->solidDelta[i][j] = pOld->solidDelta[i][j];
        if (solids[i].type == PHASE && solids[i].na > 1) 
          for (k=0; k<solids[i].na; k++) {
            (pNew->solidComp)[i+1+k][j]  = (pOld->solidComp)[i+1+k][j];
            (pNew->solidDelta)[i+1+k][j] = (pOld->solidDelta)[i+1+k][j];
          }
      }
      (pNew->nSolidCoexist)[i] = (pOld->nSolidCoexist)[i];
    }

    pNew->solidMass = pOld->solidMass;
    for (i=0; i<(npc+1); i++) (pNew->incSolids)[i] = (pOld->incSolids)[i];
    for (i=0; i<npc; i++) (pNew->cylSolids)[i] = (pOld->cylSolids)[i];
    memcpy(&(pNew->solidTD), &(pOld->solidTD), sizeof(ThermoData));
    pNew->dspTstart = pOld->dspTstart;
    pNew->dspTstop  = pOld->dspTstop;
    pNew->dspTinc   = pOld->dspTinc;
    pNew->dspHstop  = pOld->dspHstop;
    pNew->dspHinc   = pOld->dspHinc;
    pNew->dspSstop  = pOld->dspSstop;
    pNew->dspSinc   = pOld->dspSinc;
    pNew->T         = pOld->T;
    pNew->dspPstart = pOld->dspPstart;
    pNew->dspPstop  = pOld->dspPstop;
    pNew->dspPinc   = pOld->dspPinc;
    pNew->dspVstop  = pOld->dspVstop;
    pNew->dspVinc   = pOld->dspVinc;
    pNew->dspDPDt   = pOld->dspDPDt;
    pNew->dspDPDH   = pOld->dspDPDH;
    pNew->dspDPDS   = pOld->dspDPDS;
    pNew->dspDVDt   = pOld->dspDVDt;
    pNew->P         = pOld->P;
    pNew->fo2       = pOld->fo2;
    pNew->fo2Path   = pOld->fo2Path;
    pNew->fo2Delta  = pOld->fo2Delta;
    pNew->oxygen    = pOld->oxygen;

    if ((pOld->fractionateSol || pOld->fractionateFlu) && (pOld->nFracCoexist != NULL) && (pOld->fracSComp != NULL)) {
      if (pNew->nFracCoexist == NULL) {
        pNew->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
        pNew->nFracCoexist = (int *)     calloc((unsigned) npc, sizeof(int));
      }
      for (i=0; i<npc; i++) {
        if ((pNew->nFracCoexist)[i] != (pOld->nFracCoexist)[i]) {
          int newSize = MAX((pOld->nFracCoexist)[i], 1);
          pNew->fracSComp[i]  = (double *) REALLOC(pNew->fracSComp[i],(unsigned) newSize*sizeof(double));
	  if (solids[i].na > 1) for (k=0; k<solids[i].na; k++) {
	    pNew->fracSComp[i+1+k]  = (double *) REALLOC(pNew->fracSComp[i+1+k],(unsigned) newSize*sizeof(double));
	  }
        }
        if ((pOld->nFracCoexist)[i] > 0) for (j=0; j<(pOld->nFracCoexist)[i]; j++) {
	  pNew->fracSComp[i][j] = pOld->fracSComp[i][j];
	  if (solids[i].na > 1) for (k=0; k<solids[i].na; k++) pNew->fracSComp[i+1+k][j] = pOld->fracSComp[i+1+k][j];
	}
        (pNew->nFracCoexist)[i] = (pOld->nFracCoexist)[i];
      }
    } else if ((pNew->fractionateSol || pNew->fractionateFlu) && (pNew->nFracCoexist != NULL) && (pNew->fracSComp != NULL)) {
      for (i=0; i<npc; i++) if (pNew->fracSComp[i] != NULL) free (pNew->fracSComp[i]);
      free(pNew->nFracCoexist); pNew->nFracCoexist = NULL;
      free(pNew->fracSComp);    pNew->fracSComp    = NULL;
    }
    pNew->fractionateSol = pOld->fractionateSol;
    pNew->fractionateFlu = pOld->fractionateFlu;

    if (pOld->fractionateLiq && (pOld->fracLComp != NULL)) {
      if (pNew->fracLComp == NULL) pNew->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
      for (i=0; i<nlc; i++) pNew->fracLComp[i] = pOld->fracLComp[i];      
    } else if ((pNew->fractionateSol || pNew->fractionateFlu) && (pNew->fracLComp != NULL)) {
      free(pNew->fracLComp);
      pNew->fracLComp = NULL;
    }
    pNew->fractionateLiq = pOld->fractionateLiq;

    pNew->fracMass       = pOld->fracMass;
    pNew->multipleLiqs   = pOld->multipleLiqs;
    pNew->isenthalpic    = pOld->isenthalpic;
    pNew->refEnthalpy    = pOld->refEnthalpy;
    pNew->isentropic     = pOld->isentropic;
    pNew->refEntropy     = pOld->refEntropy;
    pNew->tDelta         = pOld->tDelta;

    pNew->isochoric      = pOld->isochoric;
    pNew->refVolume      = pOld->refVolume;
    pNew->pDelta         = pOld->pDelta;

    if (pOld->assimilate) {
      pNew->dspAssimComp  
        = (double **) calloc((unsigned) (npc+nc), sizeof(double *));
      pNew->assimComp     
        = (double **) calloc((unsigned) (npc+nlc), sizeof(double *));
      pNew->nDspAssimComp 
        = (int *)     calloc((unsigned) (npc+nc), sizeof(int));
      pNew->nAssimComp    
        = (int *)     calloc((unsigned) (npc+nlc), sizeof(int));
      for (i=0; i<(nlc+npc); i++) {
        if ((pNew->nAssimComp)[i] != (pOld->nAssimComp)[i]) {
          int newSize = MAX((pOld->nAssimComp)[i], 1);
          (pNew->assimComp)[i]   = (double *) REALLOC((pNew->assimComp)[i],
            (unsigned) newSize*sizeof(double));
        }
      }
      for (i=0; i<(nc+npc); i++) {
        if ((pNew->nDspAssimComp)[i] != (pOld->nDspAssimComp)[i]) {
          int newSize = MAX((pOld->nDspAssimComp)[i], 1);
          (pNew->dspAssimComp)[i]   = (double *) REALLOC((pNew->dspAssimComp)[i],
            (unsigned) newSize*sizeof(double));
        }
      }
      for (i=0; i<(nc+npc); i++) {
        for (j=0; j<(pOld->nAssimComp)[i]; j++)
          (pNew->assimComp)[i][j]    = (pOld->assimComp)[i][j];
        for (j=0; j<(pOld->nDspAssimComp)[i]; j++)
          (pNew->dspAssimComp)[i][j] = (pOld->dspAssimComp)[i][j];
        (pNew->nAssimComp)[i]        = (pOld->nAssimComp)[i];
        (pNew->nDspAssimComp)[i]     = (pOld->nDspAssimComp)[i];
      }
    } else if (pNew->assimilate) {
      for (i=0; i<(nlc+npc); i++)
        if (pNew->assimComp[i] != NULL)    free (pNew->assimComp[i]);
      for (i=0; i<(nc+npc); i++)
        if (pNew->dspAssimComp[i] != NULL) free (pNew->dspAssimComp[i]);
      free(pNew->nAssimComp);    pNew->nAssimComp    = NULL;
      free(pNew->assimComp);     pNew->assimComp     = NULL;
      free(pNew->nDspAssimComp); pNew->nDspAssimComp = NULL;
      free(pNew->dspAssimComp);  pNew->dspAssimComp  = NULL;
    }
    pNew->assimilate    = pOld->assimilate;
    pNew->dspAssimUnits = pOld->dspAssimUnits;
    pNew->dspAssimMass  = pOld->dspAssimMass;
    pNew->dspAssimT     = pOld->dspAssimT;
    pNew->dspAssimInc   = pOld->dspAssimInc;
    pNew->dspAssimLiqM  = pOld->dspAssimLiqM;
    pNew->assimMass     = pOld->assimMass;
    pNew->assimT        = pOld->assimT;
    pNew->assimInc      = pOld->assimInc;
    memcpy(&(pNew->assimTD), &(pOld->assimTD), sizeof(ThermoData));

    pNew->plotState     = pOld->plotState;
  }

  return pNew;
}

#ifndef BATCH_VERSION

#define ERROR(string) \
{ \
  XmString csString = XmStringCreateLtoR(string, "ISO8859-1"); \
  XtVaSetValues(message, XmNmessageString, csString, NULL); \
  XtManageChild(message); \
  XmStringFree(csString); \
  free(diff); \
  return mask | SILMIN_STATE_CHANGE_FATAL_ERROR; \
}

int checkStateAgainstInterface(void)
{
  int mask = SILMIN_STATE_CHANGE_NONE;

  double *diff, sum;
  int i, j, ns;

  if (silminState == NULL) silminState = allocSilminStatePointer();
  diff = (double *) malloc((unsigned) nc*sizeof(double));
  
/* -> check displayed bulk composition against stored bulk composition      */
  for (i=0, sum=0.0; i<nc; i++) {
    diff[i] = 0.0;
    sum += compositionValues[i].value;
    if (compositionValues[i].value != (silminState->dspBulkComp)[i]) {
      mask |= SILMIN_STATE_CHANGE_BULK;
      diff[i] = compositionValues[i].value - (silminState->dspBulkComp)[i];
    }
  }
  if (sum <= 0.00) ERROR("Please specify a bulk composition first!")
  if (mask & SILMIN_STATE_CHANGE_BULK) {
    for (i=0; i<nc; i++) {
      (silminState->dspBulkComp)[i] += diff[i];             /* grams oxides */
      diff[i]                       /= bulkSystem[i].mw;
      (silminState->bulkComp)[i]    += diff[i];             /* moles oxides */
    }
    /* Add bulk composition change to the first liquid */
    if (silminState->nLiquidCoexist == 0) silminState->nLiquidCoexist = 1;
    for (i=0; i<nlc; i++) for (j=0; j<nc; j++) (silminState->liquidComp)[0][i] += diff[j]*(bulkSystem[j].oxToLiq)[i];
    for (i=0; i<nc; i++) silminState->liquidMass += diff[i]*bulkSystem[i].mw;
    if (silminState->oxygen != 0.0) for (i=0; i<nlc; i++) for (j=0; j<nc; j++) silminState->oxygen += diff[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
  }

/* -> If the included solids padb doesn't exist, create it and accept 
      default entries                                                       */
  if (solid_padb == NULL) create_solid_padb();
  for (i=0, j=0; i<npc; i++) {
    if (solids[i].type == PHASE) {
      if ( (silminState->incSolids)[j] != XmToggleButtonGadgetGetState(includedSolids[j].name) ) {
        mask |= SILMIN_STATE_CHANGE_INC_SOLIDS;
        (silminState->incSolids)[j] = !(silminState->incSolids)[j];
      }
      j++;
    } 
  }
  /* melts phase */
  if ( (silminState->incSolids)[npc] != XmToggleButtonGadgetGetState(includedSolids[j].name) ) {
    mask |= SILMIN_STATE_CHANGE_INC_SOLIDS;
    (silminState->incSolids)[npc] = !(silminState->incSolids)[npc];
  }

/* -> If tp_box padb doesn't exist, the user has not set t and p, exit      */
  if (tp_padb == NULL) ERROR("Please specify values for T and P first!")

/* -> check temperature entries for any changes                             */
  if (tpValues[TP_PADB_INDEX_T_INITIAL].value == 0.0 || tpValues[TP_PADB_INDEX_T_INITIAL].value != silminState->dspTstart) {
    if (tpValues[TP_PADB_INDEX_T_INITIAL].value <= 0.0) ERROR("Please specify a value for the temperature first!")
    mask |= SILMIN_STATE_CHANGE_T;
    silminState->dspTstart = tpValues[TP_PADB_INDEX_T_INITIAL].value;
    silminState->T = silminState->dspTstart + 273.15;
  }
  if (tpValues[TP_PADB_INDEX_T_FINAL].value != silminState->dspTstop)    silminState->dspTstop = tpValues[TP_PADB_INDEX_T_FINAL].value;
  if (tpValues[TP_PADB_INDEX_T_INCREMENT].value != silminState->dspTinc) silminState->dspTinc  = tpValues[TP_PADB_INDEX_T_INCREMENT].value;

/* -> check pressure entries for any changes                                */
  if (tpValues[TP_PADB_INDEX_P_INITIAL].value == 0.0 || tpValues[TP_PADB_INDEX_P_INITIAL].value != silminState->dspPstart) {
    if (tpValues[TP_PADB_INDEX_P_INITIAL].value <= 0.0) ERROR("Please specify a value for the pressure first!")
    mask |= SILMIN_STATE_CHANGE_P;
    silminState->dspPstart = tpValues[TP_PADB_INDEX_P_INITIAL].value;
    silminState->P = silminState->dspPstart;
  }
  if (tpValues[TP_PADB_INDEX_P_FINAL].value != silminState->dspPstop)    silminState->dspPstop = tpValues[TP_PADB_INDEX_P_FINAL].value;
  if (tpValues[TP_PADB_INDEX_P_INCREMENT].value != silminState->dspPinc) silminState->dspPinc = tpValues[TP_PADB_INDEX_P_INCREMENT].value;

/* -> check dPdT entry for a change                                         */
  if (tpValues[TP_PADB_INDEX_DPDT].value != silminState->dspDPDt) silminState->dspDPDt = tpValues[TP_PADB_INDEX_DPDT].value;

/* -> check enthalpy entries for a change                                   */
  if (tpValues[TP_PADB_INDEX_H_INCREMENT].value != silminState->dspHinc) silminState->dspHinc = tpValues[TP_PADB_INDEX_H_INCREMENT].value;
  if (tpValues[TP_PADB_INDEX_DPDH].value != silminState->dspDPDH)        silminState->dspDPDH = tpValues[TP_PADB_INDEX_DPDH].value;

/* -> check entropy entries for a change                                    */
  if (tpValues[TP_PADB_INDEX_S_INCREMENT].value != silminState->dspSinc) silminState->dspSinc = tpValues[TP_PADB_INDEX_S_INCREMENT].value;
  if (tpValues[TP_PADB_INDEX_DPDS].value != silminState->dspDPDS)        silminState->dspDPDS = tpValues[TP_PADB_INDEX_DPDS].value;

/* -> check volume entries for a change                                     */
  if (tpValues[TP_PADB_INDEX_V_INCREMENT].value != silminState->dspVinc) silminState->dspVinc = tpValues[TP_PADB_INDEX_V_INCREMENT].value;
  if (tpValues[TP_PADB_INDEX_DTDV].value != silminState->dspDVDt)        silminState->dspDVDt = tpValues[TP_PADB_INDEX_DTDV].value;

/* -> check fo2Path entry for change                                        */
  if        (XmToggleButtonGadgetGetState(tg_path_none)) {
    if (silminState->fo2Path != FO2_NONE) {
      silminState->fo2Path = FO2_NONE;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_hm))   {
    if (silminState->fo2Path != FO2_HM) {
      silminState->fo2Path = FO2_HM;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_nno))  {
    if (silminState->fo2Path != FO2_NNO) {
      silminState->fo2Path = FO2_NNO;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq))  {
    if (silminState->fo2Path != FO2_QFM) {
      silminState->fo2Path = FO2_QFM;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_coh))  {
    if (silminState->fo2Path != FO2_COH) {
      silminState->fo2Path = FO2_COH;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_iw))   {
    if (silminState->fo2Path != FO2_IW) {
      silminState->fo2Path = FO2_IW;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_p3))  {
    if (silminState->fo2Path != FO2_QFM_P3) {
      silminState->fo2Path = FO2_QFM_P3;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_p2))  {
    if (silminState->fo2Path != FO2_QFM_P2) {
      silminState->fo2Path = FO2_QFM_P2;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_p1))  {
    if (silminState->fo2Path != FO2_QFM_P1) {
      silminState->fo2Path = FO2_QFM_P1;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_m1))  {
    if (silminState->fo2Path != FO2_QFM_M1) {
      silminState->fo2Path = FO2_QFM_M1;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_m2))  {
    if (silminState->fo2Path != FO2_QFM_M2) {
      silminState->fo2Path = FO2_QFM_M2;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_m3))  {
    if (silminState->fo2Path != FO2_QFM_M3) {
      silminState->fo2Path = FO2_QFM_M3;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_m4))  {
    if (silminState->fo2Path != FO2_QFM_M4) {
      silminState->fo2Path = FO2_QFM_M4;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_m5))  {
    if (silminState->fo2Path != FO2_QFM_M5) {
      silminState->fo2Path = FO2_QFM_M5;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_m6))  {
    if (silminState->fo2Path != FO2_QFM_M6) {
      silminState->fo2Path = FO2_QFM_M6;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_m7))  {
    if (silminState->fo2Path != FO2_QFM_M7) {
      silminState->fo2Path = FO2_QFM_M7;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_m8))  {
    if (silminState->fo2Path != FO2_QFM_M8) {
      silminState->fo2Path = FO2_QFM_M8;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  } else if (XmToggleButtonGadgetGetState(tg_path_fmq_m9))  {
    if (silminState->fo2Path != FO2_QFM_M9) {
      silminState->fo2Path = FO2_QFM_M9;
      mask |= SILMIN_STATE_CHANGE_FO2PATH;
    }
  }  
  
/* -> check solid fractionation mode flag                                    */
  if (silminState->fractionateSol != XmToggleButtonGadgetGetState(tg_fractionate_solids)) {
    silminState->fractionateSol = !silminState->fractionateSol;
    mask |= SILMIN_STATE_CHANGE_FRAC_SOL;
  }
  if (silminState->fractionateSol && silminState->fracSComp == (double **) NULL) {
    silminState->fracSComp = (double **) calloc((unsigned) npc, sizeof(double *));
    silminState->nFracCoexist = (int *) calloc((unsigned) npc, sizeof(int));
  }

/* -> check liquid fractionation mode flag                                   */
  if (silminState->fractionateLiq != XmToggleButtonGadgetGetState(tg_fractionate_liquids)) {
    silminState->fractionateLiq = !silminState->fractionateLiq;
    mask |= SILMIN_STATE_CHANGE_FRAC_LIQ;
  }
  if (silminState->fractionateLiq && silminState->fracLComp == (double *) NULL) {
    silminState->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
  }

/* -> check fluid fractionation mode flag                                    */
  if (silminState->fractionateFlu != XmToggleButtonGadgetGetState(tg_fractionate_fluids)) {
    silminState->fractionateFlu = !silminState->fractionateFlu;
    mask |= SILMIN_STATE_CHANGE_FRAC_FLU;
  }
  if (silminState->fractionateFlu && silminState->fracSComp == (double **) NULL) {
    silminState->fracSComp = (double **) calloc((unsigned) npc, sizeof(double *));
    silminState->nFracCoexist = (int *) calloc((unsigned) npc, sizeof(int));
  }

/* -> check multiple liquid mode flag                                        */
  if (silminState->multipleLiqs != XmToggleButtonGadgetGetState(tg_multiple_liquids)) {
    silminState->multipleLiqs = !silminState->multipleLiqs;
    mask |= SILMIN_STATE_CHANGE_MUL_LIQUIDS;
  }

/* -> check isenthalpic mode flag                                            */
  if (silminState->isenthalpic != XmToggleButtonGadgetGetState(tg_isenthalpic)) {
    silminState->refEnthalpy = 0.0;
    silminState->isenthalpic = !silminState->isenthalpic;
    mask |= SILMIN_STATE_CHANGE_ISENTHALPIC;
  }

/* -> check isentropic mode flag                                            */
  if (silminState->isentropic != XmToggleButtonGadgetGetState(tg_isentropic)) {
    silminState->refEntropy = 0.0;
    silminState->isentropic = !silminState->isentropic;
    mask |= SILMIN_STATE_CHANGE_ISENTROPIC;
  }

/* -> check isochoric mode flag                                              */
  if (silminState->isochoric != XmToggleButtonGadgetGetState(tg_isochoric)) {
    silminState->refVolume = 0.0;
    silminState->isochoric = !silminState->isochoric;
    mask |= SILMIN_STATE_CHANGE_ISOCHORIC;
  }

/* -> check assimilant status                                                */
  if (assimilant_padb != NULL) {
    silminState->assimilate = 
      ((assimilantValues[npc+nc+ASSIM_PADB_INDEX_MASS].value)[0]      > 0.0) &
      ((assimilantValues[npc+nc+ASSIM_PADB_INDEX_T].value)[0]         > 0.0) &
      ((assimilantValues[npc+nc+ASSIM_PADB_INDEX_INCREMENT].value)[0] > 0.0);
    if (silminState->assimilate) {
      if (silminState->dspAssimComp == (double **) NULL) {
        silminState->dspAssimComp  = (double **) calloc((unsigned) (npc+nc),  sizeof(double *));
        silminState->assimComp     = (double **) calloc((unsigned) (npc+nlc), sizeof(double *));
        silminState->nDspAssimComp = (int *)     calloc((unsigned) (npc+nc),  sizeof(int));
        silminState->nAssimComp =    (int *)     calloc((unsigned) (npc+nlc), sizeof(int));
      }

      silminState->dspAssimUnits = assimilantUnits.units;
      if (silminState->dspAssimMass != (assimilantValues[npc+nc+ASSIM_PADB_INDEX_MASS].value)[0]) {
        silminState->dspAssimMass = (assimilantValues[npc+nc+ASSIM_PADB_INDEX_MASS].value)[0];
        mask |= SILMIN_STATE_CHANGE_ASSIM_MASS;
      }
      if (silminState->dspAssimInc != (assimilantValues[npc+nc+ASSIM_PADB_INDEX_INCREMENT].value)[0]) {
        silminState->dspAssimInc = (assimilantValues[npc+nc+ASSIM_PADB_INDEX_INCREMENT].value)[0];
        mask |= SILMIN_STATE_CHANGE_ASSIM_INC;
      }
      if (silminState->dspAssimT != (assimilantValues[npc+nc+ASSIM_PADB_INDEX_T].value)[0]) {
        silminState->dspAssimT = (assimilantValues[npc+nc+ASSIM_PADB_INDEX_T].value)[0];
        silminState->assimT = silminState->dspAssimT;
        mask |= SILMIN_STATE_CHANGE_ASSIM_T;
      }
      if (silminState->dspAssimLiqM != (assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value)[0]) {
        silminState->dspAssimLiqM = (assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value)[0];
        mask |= SILMIN_STATE_CHANGE_ASSIM_COMP;
      }

      for (i=0; i<(npc+nc); i++) {
        if ((ns = assimilantValues[i].ns) > silminState->nDspAssimComp[i]) {
          if (silminState->nDspAssimComp[i] == 0) {
            silminState->dspAssimComp[i] = (double *) malloc((unsigned) ns*sizeof(double));
            silminState->assimComp[i]    = (double *) malloc((unsigned) ns*sizeof(double));
          } else {
            silminState->dspAssimComp[i] = (double *) REALLOC(silminState->dspAssimComp[i], (unsigned) ns*sizeof(double));
            silminState->assimComp[i]    = (double *) REALLOC(silminState->assimComp[i], (unsigned) ns*sizeof(double));
          }
          for (j=silminState->nDspAssimComp[i]; j<ns; j++) {
            silminState->dspAssimComp[i][j] = 0.0; 
            silminState->assimComp[i][j] = 0.0;
          }
        }
        silminState->nDspAssimComp[i] = ns;  silminState->nAssimComp[i] = ns;
      }

      for (i=0; i<(npc+nc); i++) for (ns=0; ns<assimilantValues[i].ns; ns++) {
        if( (silminState->dspAssimComp)[i][ns] != (assimilantValues[i].value)[ns]) {
          (silminState->dspAssimComp)[i][ns] = (assimilantValues[i].value)[ns];
          mask |= SILMIN_STATE_CHANGE_ASSIM_COMP;
        }
      }

      if (mask & SILMIN_STATE_CHANGE_ASSIM_MASS || mask & SILMIN_STATE_CHANGE_ASSIM_COMP) {
        if      (assimilantUnits.units == ASSIM_PADB_UNITS_WEIGHT) {
          double *m = (double *) malloc((unsigned) nc*sizeof(double));
          for (i=0; i<npc; i++) if (solids[i].type == PHASE) {
            for (ns=0; ns<silminState->nAssimComp[i]; ns++) {
              if (solids[i].na == 1) {
                (silminState->assimComp)[i][ns] = (silminState->dspAssimComp)[i][ns]*(silminState->dspAssimMass)/(100.0*solids[i].mw); 
              } else {
                double mw = 0.0;
                for (j=0; j<solids[i].na; j++) mw += (silminState->dspAssimComp)[i+1+j][ns]*solids[i+1+j].mw/100.0;
                (silminState->assimComp)[i][ns] = (mw == 0.0) ? 0.0 : (silminState->dspAssimComp)[i][ns]*(silminState->dspAssimMass)/(100.0*mw); 
                for (j=0; j<solids[i].na; j++) (silminState->assimComp)[i+1+j][ns] = (silminState->dspAssimComp)[i+1+j][ns]*(silminState->assimComp)[i][ns]/100.0;
              }
            }
          }
          for (ns=0; ns<silminState->nAssimComp[1+npc]; ns++) {
            for (i=0; i<nc; i++) m[i] = (silminState->dspAssimComp)[i+npc][ns]*(silminState->dspAssimLiqM)*(silminState->dspAssimMass)/(100.0*100.0*bulkSystem[i].mw);
            for (i=0; i<nlc; i++) 
              for (j=0, (silminState->assimComp)[i+npc][ns]=0.0; j<nc; j++) (silminState->assimComp)[i+npc][ns] += m[j]*(bulkSystem[j].oxToLiq)[i]; 
          }
          free(m);
        } else if (assimilantUnits.units == ASSIM_PADB_UNITS_VOLUME) {
          ERROR("Code not yet implemented to convert a vol % assimilant !");
        }
      }

      if (mask & SILMIN_STATE_CHANGE_ASSIM_MASS ||
          mask & SILMIN_STATE_CHANGE_ASSIM_COMP ||
          mask & SILMIN_STATE_CHANGE_ASSIM_T) {
        double *m = (double *) malloc((unsigned)     nlc*sizeof(double));
        double *r = (double *) malloc((unsigned) (nlc-1)*sizeof(double));
        double enthalpy, entropy, volume, totalEnthalpy, totalEntropy,
          totalVolume;

        totalEnthalpy = 0.0;
        totalEntropy  = 0.0;
        totalVolume   = 0.0;

        for (j=0; j<npc; j++) if (solids[j].type == PHASE)
        for (ns=0; ns<(silminState->nAssimComp)[j]; ns++) {
          if (solids[j].na == 1) {
            gibbs(silminState->assimT+273.15, silminState->P, (char *) solids[j].label, &(solids[j].ref), NULL, NULL, &(silminState->assimTD));
            enthalpy = (silminState->assimComp)[j][ns]*(silminState->assimTD).h;
            entropy  = (silminState->assimComp)[j][ns]*(silminState->assimTD).s;
            volume   = (silminState->assimComp)[j][ns]*(silminState->assimTD).v;
          } else {
            for (i=0; i<solids[j].na; i++) m[i] = (silminState->assimComp)[j+1+i][ns];
            (*solids[j].convert)(SECOND, THIRD, silminState->assimT+273.15, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
            (*solids[j].hmix)(FIRST, silminState->assimT+273.15, silminState->P, r, &enthalpy);
            (*solids[j].smix)(FIRST, silminState->assimT+273.15, silminState->P, r, &entropy, NULL, NULL);
            (*solids[j].vmix)(FIRST, silminState->assimT+273.15, silminState->P, r, &volume, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            enthalpy     *= (silminState->assimComp)[j][ns];
            entropy      *= (silminState->assimComp)[j][ns];
            volume       *= (silminState->assimComp)[j][ns];
            for (i=0; i<solids[j].na; i++) {
              gibbs(silminState->assimT+273.15, silminState->P, (char *) solids[j+1+i].label, &(solids[j+1+i].ref), NULL, NULL, &(silminState->assimTD));
              enthalpy += m[i]*(silminState->assimTD).h;
              entropy  += m[i]*(silminState->assimTD).s;
              volume   += m[i]*(silminState->assimTD).v;
            }
          }
          totalEnthalpy += enthalpy;
          totalEntropy  += entropy;
          totalVolume   += volume;
        }

        for (ns=0; ns<(silminState->nAssimComp)[npc+1]; ns++) {
          double totalMoles;
          for (i=0, totalMoles=0.0; i<nlc; i++) {
            m[i] = (silminState->assimComp)[npc+i][ns];
            totalMoles += m[i];
          }
          conLiq(SECOND, THIRD, silminState->assimT+273.15, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL);
          hmixLiq(FIRST, silminState->assimT+273.15, silminState->P, r, &enthalpy, NULL);
          smixLiq(FIRST, silminState->assimT+273.15, silminState->P, r, &entropy,  NULL, NULL, NULL);
          vmixLiq(FIRST, silminState->assimT+273.15, silminState->P, r, &volume,   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
          enthalpy *= totalMoles;
          entropy  *= totalMoles;
          volume   *= totalMoles;
          for (i=0; i<nlc; i++) {
            gibbs(silminState->assimT+273.15, silminState->P, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(silminState->assimTD));
            enthalpy += m[i]*(silminState->assimTD).h;
            entropy  += m[i]*(silminState->assimTD).s;
            volume   += m[i]*(silminState->assimTD).v;
          }
          totalEnthalpy += enthalpy;
          totalEntropy  += entropy;
          totalVolume   += volume;
        }

        (silminState->assimTD).g       = 0.0;
        (silminState->assimTD).h       = totalEnthalpy;
        (silminState->assimTD).s       = totalEntropy;
        (silminState->assimTD).v       = totalVolume;
        (silminState->assimTD).cp      = 0.0;
        (silminState->assimTD).dcpdt   = 0.0;
        (silminState->assimTD).dvdt    = 0.0;
        (silminState->assimTD).dvdp    = 0.0;
        (silminState->assimTD).d2vdt2  = 0.0;
        (silminState->assimTD).d2vdp2  = 0.0;
        (silminState->assimTD).d2vdtdp = 0.0;

        free(m);
        free(r);
      }

    }
  }

  /* ISOCHORIC-FO2 ...
  if (silminState->fo2Path != FO2_NONE && (silminState->isenthalpic || silminState->isentropic || silminState->isochoric)) 
  ERROR("f O2 constraints cannot be used with constant H, S or V constraints!")
  ... END ISOCHORIC-FO2 */

  free(diff);
  return mask;
}

#undef ERROR

#endif /* Batch version */

/******************************************************************************
 * The screen update functions:
 ******************************************************************************/

void updateBulkADB(void)
{
#ifndef BATCH_VERSION
  static char compositionEntry[9];
#endif
  double sum, *temporary;
  int i, j, nl;
  int hasLiquid = (silminState->liquidMass != 0.0);

  temporary = (double *) calloc((size_t) nc, sizeof(double));

  /* convert moles of liquid components into grams of oxides */
  if (hasLiquid) for (i=0; i<nc; i++) for (nl=0, temporary[i]=0.0; nl<silminState->nLiquidCoexist; nl++) for (j=0; j<nlc; j++)  
    temporary[i] += (silminState->liquidComp)[nl][j]*(liquid[j].liqToOx)[i];

  if (silminState->fo2Path == FO2_NONE && hasLiquid) { /* This returns the AVERAGE log fO2 */
    double *oxides = (double *) malloc((size_t) nc*sizeof(double));
    double logfO2 = 0.0;
    for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
      for (i=0; i<nc; i++) for (j=0, oxides[i]=0.0; j<nlc; j++) oxides[i] += (silminState->liquidComp)[nl][j]*(liquid[j].liqToOx)[i];
      conLiq(FIRST, SEVENTH, silminState->T, silminState->P, oxides, NULL, NULL, NULL, NULL, NULL, &(silminState->fo2));
      logfO2 += silminState->fo2;
    }
    silminState->fo2 = logfO2/((double) nl);
    free(oxides);
  } else if (silminState->fo2Path == FO2_NONE && !hasLiquid) {
    double muO2;
    subsolidusmuO2(FIRST, &muO2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    silminState->fo2 = muO2/(R*silminState->T*log(10.0));
  }
  for (i=0, sum=0.0; i<nc; i++) {
    temporary[i] *= bulkSystem[i].mw;     /* grams of oxide components */
    sum          += temporary[i];         /* total grams of oxides     */
  }
  silminState->liquidMass = sum;

#ifndef BATCH_VERSION
  /* display grams oxides and preserve an exact reference copy */
  for (i=0; i<nc; i++) {
    temporary[i] = (silminState->bulkComp)[i]*bulkSystem[i].mw;
    if (temporary[i] != 0.0) { /* was > */
      (void) snprintf(compositionEntry, 9, "%8.4f", temporary[i]);
      XmTextSetString(compositionValues[i].name, compositionEntry);
      (silminState->dspBulkComp)[i] = atof(compositionEntry);
    }
  }
#endif

  free(temporary);
}

#ifndef BATCH_VERSION

typedef struct _clsStable {
  Widget   name;
  XmString label;
} ClsStable;

static ClsStable *updateCompADBaddButton(char *label)
{
  ClsStable *entry;

  entry = (ClsStable *) XtMalloc ((unsigned) sizeof(ClsStable));
  entry->name = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, compPDmenu,
    XtVaTypedArg, XmNlabelString, XmRString, label, (int) (strlen(label)+1), NULL);
  XtAddCallback(entry->name, XmNactivateCallback, compPDcallback, (XtPointer) NULL);
  /* entry->label = XmStringCreateLtoR(label, "ISO8859-1"); */
  entry->label = XmStringCreateLocalized(label);

  return entry;
}

static void updateCompADBoxides(double *oxVal)
{
  static char *string;

  int i;
  XmString csString;

  if (string == NULL) string = (char *) malloc((unsigned) 12*sizeof(char));
                                                  /* 11 == "1000000 ppm" */
  for (i=0; i<nc; i++) {
    if      (oxVal[i] > 0.1) (void) snprintf(string, 12, "%.3f", oxVal[i]);
    else if (oxVal[i] > 0.0) (void) snprintf(string, 12, "%.0f ppm", oxVal[i]*10000.0);
    else                     (void) snprintf(string, 12, "--------");
    /* csString = XmStringCreateLtoR(string, "ISO8859-1"); */
    csString = XmStringCreateLocalized(string);
    XtVaSetValues(compEntries[i].name, XmNlabelString, csString, NULL);
    XmStringFree(csString);
  }
}

void updateCompADB(void)
{
  static int naMax, nlCur, *nsCur;
  static double *oxVal, *rLiq, *mSol, *rSol;
  static ClsStable **clsSolid, *clsLiquid, noneString; 

  double sum;
  Widget selected;
  XmString csString;
  int i, j, k, l, n, nl, ns;

  XtVaGetValues(compPDmenu, XmNmenuHistory, &selected, NULL);
  if(selected == (Widget) NULL)
    csString = XmStringCreateLtoR("none", "ISO8859-1");
  else
    XtVaGetValues(selected,   XmNlabelString, &csString, NULL);

  if (nsCur == NULL) {
    noneString.label = XmStringCopy(csString);
    for (i=0; i<npc; i++) if (naMax < solids[i].na) naMax = solids[i].na;

    nsCur     = (int *)        calloc((size_t) npc, sizeof(int));   
    clsLiquid = (ClsStable *)  malloc((size_t) nlc*sizeof(ClsStable));
    clsSolid  = (ClsStable **) malloc((size_t) npc*sizeof(ClsStable *));
    for (i=0; i<npc; i++) clsSolid[i] = (ClsStable *) calloc((size_t) naMax, sizeof(ClsStable));

    oxVal   = (double *) malloc((size_t)        nc*sizeof(double));
    rLiq    = (double *) malloc((size_t)   (nlc-1)*sizeof(double));
    mSol    = (double *) malloc((size_t)     naMax*sizeof(double));
    rSol    = (double *) malloc((size_t) (naMax-1)*sizeof(double));
  }

  /* Default "no action" selection */
  if (XmStringCompare(csString, noneString.label)) {
    for (i=0; i<nc; i++) oxVal[i] = 0.0;
    updateCompADBoxides(oxVal);
  }

  if (silminState == NULL) { XmStringFree(csString); return; }

  /* Liquid phase entries */
  if (silminState->liquidMass != 0.0) {

    if (silminState->nLiquidCoexist > nlCur) {
      for (j=nlCur; j<silminState->nLiquidCoexist; j++) {
  	clsLiquid[j].name  = (Widget)   NULL;
  	clsLiquid[j].label = (XmString) NULL;
      }
    } else if (silminState->nLiquidCoexist < nlCur) {
      for (j=silminState->nLiquidCoexist; j<nlCur; j++) {
  	XtUnmanageChild(clsLiquid[j].name);
  	XtDestroyWidget(clsLiquid[j].name); 
  	XmStringFree(clsLiquid[j].label);
  	clsLiquid[j].name  = (Widget)	NULL; 
  	clsLiquid[j].label = (XmString) NULL; 
      }
    }
    nlCur = silminState->nLiquidCoexist;

    for (nl=0; nl<silminState->nLiquidCoexist; nl++) { 
      if (clsLiquid[nl].label == (XmString) NULL) {
  	ClsStable *temp;
	char *label = (char *) malloc((size_t) 10*sizeof(char));
	(void) snprintf(label, 10, "liquid-%2.2d", nl);
  	temp = updateCompADBaddButton(label);
  	clsLiquid[nl].name  = temp->name;
  	clsLiquid[nl].label = temp->label;
  	XtFree((char *) temp);
	free(label);
      } else if (XmStringCompare(csString, clsLiquid[nl].label) && clsLiquid[nl].name == selected) {
        for (i=0, sum=0.0; i<nc; i++) {
          for (j=0, oxVal[i]=0.0; j<nlc; j++) oxVal[i] += (liquid[j].liqToOx)[i]*(silminState->liquidComp)[nl][j];
          oxVal[i] *= bulkSystem[i].mw;
          sum += oxVal[i];
        }
        if (sum > 0.0) for (i=0; i<nc; i++) oxVal[i] *= 100.0/sum;
        updateCompADBoxides(oxVal);
      }
    }

  } else if (nlCur > 0) {
    for (j=0; j<nlCur; j++) {
      XtUnmanageChild(clsLiquid[j].name);
      XtDestroyWidget(clsLiquid[j].name); 
      XmStringFree(clsLiquid[j].label);
      clsLiquid[j].name  = (Widget)   NULL; 
      clsLiquid[j].label = (XmString) NULL; 
    }
    nlCur = 0;
  }

  /* Solid phase entries */
  for (i=0, n=0; i<npc; i++) {
    if ((ns = (silminState->nSolidCoexist)[i]) > 0) {

      if (ns > nsCur[i]) {
        for (j=nsCur[i]; j<ns; j++) {
          clsSolid[i][j].name  = (Widget)   NULL;
          clsSolid[i][j].label = (XmString) NULL;
        }
        nsCur[i] = ns;
      } else if (ns < nsCur[i]) {
        for (j=ns; j<nsCur[i]; j++) {
          XtUnmanageChild(clsSolid[i][j].name);
          XtDestroyWidget(clsSolid[i][j].name); 
          XmStringFree(clsSolid[i][j].label);
          clsSolid[i][j].name  = (Widget)   NULL; 
          clsSolid[i][j].label = (XmString) NULL; 
        }
        nsCur[i] = ns;
      }
      
      for (k=0; k<ns; k++) { 
        if (clsSolid[i][k].label == (XmString) NULL) {
          ClsStable *temp;
          temp = updateCompADBaddButton((char *) solids[i].label);
          clsSolid[i][k].name  = temp->name;
          clsSolid[i][k].label = temp->label;
          XtFree((char *) temp);
        } else if (XmStringCompare(csString, clsSolid[i][k].label) && clsSolid[i][k].name == selected) {
          if (solids[i].na == 1) {
            for (j=0, sum=0.0; j<nc; j++) {
              oxVal[j] = (solids[i].solToOx)[j]*(silminState->solidComp)[i][k];
              oxVal[j] *= bulkSystem[j].mw;
              sum += oxVal[j];
            }
            if (sum > 0.0) for (j=0; j<nc; j++) oxVal[j] *= 100.0/sum;
            updateCompADBoxides(oxVal);
          } else if (solids[i].na > 1) {
            for (l=0, sum=0.0; l<nc; l++) {
              for (j=0, oxVal[l]=0.0; j<solids[i].na; j++) oxVal[l] += (solids[i+1+j].solToOx)[l]*(silminState->solidComp)[i+1+j][k];
              oxVal[l] *= bulkSystem[l].mw;
              sum += oxVal[l];
            }
            if (sum > 0.0) for (j=0; j<nc; j++) oxVal[j] *= 100.0/sum;
            updateCompADBoxides(oxVal);
          }
        }
      }

    } else if (nsCur[i] > 0) {
      for (j=0; j<nsCur[i]; j++) {
        XtUnmanageChild(clsSolid[i][j].name);
        XtDestroyWidget(clsSolid[i][j].name); 
        XmStringFree(clsSolid[i][j].label);
        clsSolid[i][j].name  = (Widget)   NULL; 
        clsSolid[i][j].label = (XmString) NULL; 
      }
      nsCur[i] = 0;
    }
  }

  XmStringFree(csString);
}

void updateSolidADB(double *ySol, double *yLiq)
{
  static int nlCur, *nsCur, naMax, nField, nFieldStatic, nFieldDynamic, nAffn, nStable;
  static double    *mSol, *rLiq, *rSol, *valSol, *valLiq;        
  static Opaque    *clsAffn, **clsSolid, *clsLiquid, clsAffnLiq;
  static VListLine *vLine;
  static char      **phaseEntry, **formSol;

  double sum, volume, molTot;
  VListLine vLineP;
  int i, j, k, n=0, nl, ns, fieldP, rowP;
  int hasLiquid = (silminState->liquidMass != 0.0);

  /**************************
   * Initial static entries *
   **************************/

  if (nsCur == NULL) {
    for (i=0; i<npc; i++) if (naMax < solids[i].na) naMax = solids[i].na;

    nsCur     = (int *)     calloc((size_t) npc, sizeof(int));   
    clsAffn   = (Opaque *)  calloc((size_t) npc, sizeof(Opaque));
    clsSolid  = (Opaque **) malloc((size_t) npc*sizeof(Opaque *));
    clsLiquid = (Opaque *)  malloc((size_t) nlc*sizeof(Opaque));
    for (i=0; i<npc; i++) clsSolid[i] = (Opaque *) calloc((size_t) naMax, sizeof(Opaque));

    valSol  = (double *) malloc((size_t) npc*sizeof(double));
    valLiq  = (double *) malloc((size_t) nlc*sizeof(double));
    rLiq    = (double *) malloc((size_t) (nlc-1)*sizeof(double));
    mSol    = (double *) malloc((size_t) naMax*sizeof(double));
    rSol    = (double *) malloc((size_t) (naMax-1)*sizeof(double));
    formSol = (char  **) malloc((size_t) npc*sizeof(char *));
    for (i=0; i<npc; i++) formSol[i] = (char *) malloc((size_t) 199*sizeof(char));

    nFieldStatic  = 5;        /* Five static label fields             */
    nFieldDynamic = 2*naMax;  /* Number of Component/mole frac fields */
    nField        = nFieldStatic + nFieldDynamic;

    vLine      = (VListLine *) malloc((size_t) nField*sizeof(VListLine));
    phaseEntry = (char **)     malloc((size_t) nField*sizeof(char *));
    for (i=0; i<nField; i++) {
      vLine[i].mask      = VListLineTextMask | VListLineSensitiveMask;
      vLine[i].sensitive = False;
    }
    phaseEntry[0] = (char *) malloc((size_t)   3*sizeof(char)); /* <>        */
    phaseEntry[1] = (char *) malloc((size_t)  16*sizeof(char)); /* Phase     */
    phaseEntry[2] = (char *) malloc((size_t)   7*sizeof(char)); /* Units     */
    phaseEntry[3] = (char *) malloc((size_t)   9*sizeof(char)); /* Affinity  */
    phaseEntry[4] = (char *) malloc((size_t) 199*sizeof(char)); /* Formula   */

    vLine[1].sensitive = True;                                   /* Phase     */

    for (i=nFieldStatic; i<nField; i++) {
      vLine[i].sensitive  = True;
      phaseEntry[  i]     = (char *) malloc((size_t)  11*sizeof(char));
      phaseEntry[++i]     = (char *) malloc((size_t)   7*sizeof(char));/* X */
    }
  }

  /******************************************
   * Calculate entries for the units column *
   ******************************************/

  if (units_phase_display == SOLID_ADB_UNITS_GRAMS || units_phase_display == SOLID_ADB_UNITS_WEIGHT ) {
    for (nl=0; nl<silminState->nLiquidCoexist; nl++) for (i=0, valLiq[nl]=0.0; i<nc; i++)
      for (j=0; j<nlc; j++) valLiq[nl] += (liquid[j].liqToOx)[i]*(silminState->liquidComp)[nl][j]*bulkSystem[i].mw;

  } else if (units_phase_display == SOLID_ADB_UNITS_VOLUME) {
    for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
      conLiq(SECOND, THIRD, silminState->T, silminState->P, NULL, (silminState->liquidComp)[nl], rLiq, NULL, NULL, NULL, NULL);
      vmixLiq(FIRST, silminState->T, silminState->P, rLiq, &volume, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
      for (j=0; j<nlc; j++) volume += (silminState->liquidComp)[nl][j]*(liquid[j].cur).v;
      valLiq[nl] = volume;
    }
  }

  for (j=0, sum=0.0; j<npc; j++) {
    for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
      if (solids[j].na == 1) {
        sum += (silminState->solidComp)[j][ns]*solids[j].mw;

        if (units_phase_display == SOLID_ADB_UNITS_GRAMS || units_phase_display == SOLID_ADB_UNITS_WEIGHT ) {
          valSol[n] = (silminState->solidComp)[j][ns]*solids[j].mw;
        } else if (units_phase_display == SOLID_ADB_UNITS_VOLUME) {
          valSol[n] = (silminState->solidComp)[j][ns]*(solids[j].cur).v;
        }
        (void) strncpy(formSol[n], solids[j].formula, 198);

      } else {
        char *formula;
        
        for (k=0, molTot=0.0; k<solids[j].na; k++){ mSol[k] = (silminState->solidComp)[j+1+k][ns]; molTot += mSol[k]; }
        (*solids[j].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, mSol, rSol, NULL, NULL, NULL, NULL, NULL);
        (*solids[j].display)(FIRST, silminState->T, silminState->P, rSol, &formula);
        (void) strncpy(formSol[n], formula, 198); free(formula); 

        if (units_phase_display == SOLID_ADB_UNITS_GRAMS || units_phase_display == SOLID_ADB_UNITS_WEIGHT ) {
          valSol[n] = 0.0;
        } else if (units_phase_display == SOLID_ADB_UNITS_VOLUME) {
          (*solids[j].vmix)(FIRST, silminState->T, silminState->P, rSol, &volume, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
          valSol[n] = molTot*volume;
        }

        for (k=0; k<solids[j].na; k++) {
          sum += (silminState->solidComp)[j+1+k][ns]*solids[j+1+k].mw;

          if (units_phase_display == SOLID_ADB_UNITS_GRAMS || units_phase_display == SOLID_ADB_UNITS_WEIGHT ) {
            valSol[n] += (silminState->solidComp)[j+1+k][ns]*solids[j+1+k].mw;
          } else if (units_phase_display == SOLID_ADB_UNITS_VOLUME) {
            valSol[n] += (silminState->solidComp)[j+1+k][ns]*(solids[j+1+k].cur).v;
          }
        }

      }
      n++;
    }
  }
  silminState->solidMass = sum;

  if (units_phase_display == SOLID_ADB_UNITS_WEIGHT || units_phase_display == SOLID_ADB_UNITS_VOLUME ) {
    sum = 0.0;
    if (hasLiquid) for (nl=0; nl<silminState->nLiquidCoexist; nl++) sum += valLiq[nl];
    for (j=0; j<n; j++) sum += valSol[j];
    if (sum != 0.0) {
      if (hasLiquid) for (nl=0; nl<silminState->nLiquidCoexist; nl++) valLiq[nl] *= 100.0/sum;
      for (j=0; j<n; j++) valSol[j] *= 100.0/sum;
    }
  }
  
  /* **********************************
   * Initialize Vlist display entries *
   ************************************/

  VListStartBatchUpdate((VListWidget) phases);

  /* Update the liquid units value */
  if (hasLiquid) {
    if (silminState->nLiquidCoexist > nlCur) {
      for (j=nlCur; j<silminState->nLiquidCoexist; j++) clsLiquid[j] = (Opaque) NULL;
      nlCur = silminState->nLiquidCoexist;
    } else if (silminState->nLiquidCoexist < nlCur) {
      for (j=silminState->nLiquidCoexist; j<nlCur; j++) {
    	VListRemoveLine((VListWidget) phases, clsLiquid[j]); 
    	clsLiquid[j] = (Opaque) NULL; nStable--;
      }
      nlCur = silminState->nLiquidCoexist;
    }

    for (nl=0; nl<silminState->nLiquidCoexist; nl++) { 
      if (clsLiquid[nl] == (Opaque) NULL) {
    	(void) snprintf(phaseEntry[0],   3, "<>");
    	(void) snprintf(phaseEntry[1],  16, "liquid-%2.2d", nl);
    	(void) snprintf(phaseEntry[2],   7, "%.2f", valLiq[nl]);
    	(void) snprintf(phaseEntry[3],   9, "%s", "");
    	(void) snprintf(phaseEntry[4], 199, "%s", "");
    	for (j=nFieldStatic; j<nField; j++) (void) snprintf(phaseEntry[j], 7, "%s", "");
    	for (j=0; j<nField; j++) vLine[j].textP = phaseEntry[j]; 
    	clsLiquid[nl] = VListAddLine((VListWidget) phases, vLine, (nStable == 0) ? VListAddAtTop : nStable);
    	nStable++;
      } else {
    	(void) VListGetLineInfo((VListWidget) phases, clsLiquid[nl], &vLineP, &fieldP, &rowP);
    	(void) snprintf(phaseEntry[2], 7, "%.2f", valLiq[nl]);
    	VListChangeLineText((VListWidget) phases, VListFieldRowToLine((VListWidget) phases, 2, rowP), phaseEntry[2]);
      }
    }
    
    if (yLiq == NULL && clsAffnLiq != (Opaque) NULL) {
      VListRemoveLine((VListWidget) phases, clsAffnLiq); 
      clsAffnLiq = (Opaque) NULL; nStable--;
    }
    
  } else {
    if (nlCur > 0) {
      for (j=0; j<nlCur; j++) {
        VListRemoveLine((VListWidget) phases, clsLiquid[j]); 
        clsLiquid[j] = (Opaque) NULL; nStable--;
      }
      nlCur = 0;
    }

    if        (yLiq != NULL && clsAffnLiq == (Opaque) NULL) {
      char *formula;
      (void) snprintf(phaseEntry[0],  3, "%s",  "");
      (void) snprintf(phaseEntry[1], 16, "%.15s", "liquid");
      (void) snprintf(phaseEntry[2],  7, "%s",  "");
      (void) snprintf(phaseEntry[3],  9, "%.0f", yLiq[nlc-1]);
      dispLiq(FIRST, silminState->T, silminState->P, yLiq, &formula);
      strncpy(phaseEntry[4], formula, 198); free(formula);      
      for (j=nFieldStatic; j<nField; j++) (void) snprintf(phaseEntry[j], 7, "%s", "");
      for (j=0; j<nField; j++) vLine[j].textP = phaseEntry[j]; 
      clsAffnLiq = VListAddLine((VListWidget) phases, vLine, (nStable == 0) ? VListAddAtTop : nStable); 
      nStable++;

    } else if (yLiq != NULL && clsAffnLiq != (Opaque) NULL) {
      char *formula;
      (void) VListGetLineInfo((VListWidget) phases, clsAffnLiq, &vLineP, &fieldP, &rowP);
      (void) snprintf(phaseEntry[3], 9, "%.0f", yLiq[nlc-1]);
      VListChangeLineText((VListWidget) phases, VListFieldRowToLine((VListWidget) phases, 3, rowP), phaseEntry[3]);
      dispLiq(FIRST, silminState->T, silminState->P, yLiq, &formula);
      strncpy(phaseEntry[4], formula, 198); free(formula);
      VListChangeLineText((VListWidget) phases, VListFieldRowToLine((VListWidget) phases, 4, rowP), phaseEntry[4]);

    }

  }

  /* Update the solid values */
  for (i=0, n=0; i<npc; i++) {
    if ((ns = (silminState->nSolidCoexist)[i]) > 0) {

      if (ns > nsCur[i]) {
        for (j=nsCur[i]; j<ns; j++) clsSolid[i][j] = (Opaque) NULL;
        nsCur[i] = ns;
      } else if (ns < nsCur[i]) {
        for (j=ns; j<nsCur[i]; j++) {
          VListRemoveLine((VListWidget) phases, clsSolid[i][j]); 
          clsSolid[i][j] = (Opaque) NULL; nStable--;
        }
        nsCur[i] = ns;
      }

      for (k=0; k<ns; k++) { 
        if (clsSolid[i][k] == (Opaque) NULL) {
          (void) snprintf(phaseEntry[0],  3, "<>");
          (void) snprintf(phaseEntry[1], 16, "%.15s", solids[i].label);
          (void) snprintf(phaseEntry[2],  7, "%.2f",  valSol[n]);
          (void) snprintf(phaseEntry[3],  9, "%s", "");
          (void) strncpy(phaseEntry[4], formSol[n++], 198);
          if (solids[i].na == 1) for (j=nFieldStatic; j<nField; j++) (void) snprintf(phaseEntry[j], 7, "%s", "");
          else {
            for (j=0; j<solids[i].na; j++) {
              (void) snprintf(phaseEntry[nFieldStatic + 2*j],     11, "%.10s", solids[i+1+j].label);
              (void) snprintf(phaseEntry[nFieldStatic + 2*j + 1],  7, "%.3f",  (silminState->solidComp)[i+1+j][k]/(silminState->solidComp)[i][k]);
            }
            for (j=(nFieldStatic+2*solids[i].na); j<nField; j++) (void) snprintf(phaseEntry[j], 7, "%s", "");
          }
          for (j=0; j<nField; j++) vLine[j].textP = phaseEntry[j]; 
          clsSolid[i][k] = VListAddLine((VListWidget) phases, vLine, (nStable == 0) ? VListAddAtTop : nStable);
          nStable++;
        } else {
          (void) VListGetLineInfo((VListWidget) phases, clsSolid[i][k], &vLineP, &fieldP, &rowP);
          (void) snprintf(phaseEntry[2], 7, "%.2f", valSol[n]);
          VListChangeLineText((VListWidget) phases, VListFieldRowToLine((VListWidget) phases, 2, rowP), phaseEntry[2]);
          (void) strncpy(phaseEntry[4], formSol[n++], 198);
          VListChangeLineText((VListWidget) phases, VListFieldRowToLine((VListWidget) phases, 4, rowP), phaseEntry[4]);
          if (solids[i].na > 1) {
            for (j=0; j<solids[i].na; j++) {
              (void) snprintf(phaseEntry[nFieldStatic + 2*j + 1], 7, "%.3f", (silminState->solidComp)[i+1+j][k]/(silminState->solidComp)[i][k]);
              VListChangeLineText((VListWidget) phases, VListFieldRowToLine((VListWidget) phases, nFieldStatic + 2*j + 1, rowP), phaseEntry[nFieldStatic + 2*j + 1]);
            }
          }
        }
      }

    } else if (nsCur[i] > 0) {
      for (j=0; j<nsCur[i]; j++) {
        VListRemoveLine((VListWidget) phases, clsSolid[i][j]); 
        clsSolid[i][j] = (Opaque) NULL; nStable--;
      }
      nsCur[i] = 0;
    }
  }

  if (ySol == (double *) NULL) { VListEndBatchUpdate((VListWidget) phases); return; }

  /****************************************************************
   * Process and display chemical affinity information for solids *
   ****************************************************************/

  for (i=0; i<npc; i++) if (solids[i].type == PHASE) {
    if        (ySol[i] != 0.0 && clsAffn[i] == (Opaque) NULL) {
      (void) snprintf(phaseEntry[0],  3, "%s",  "");
      (void) snprintf(phaseEntry[1], 16, "%.15s", solids[i].label);
      (void) snprintf(phaseEntry[2],  7, "%s",  "");
      (void) snprintf(phaseEntry[3],  9, "%.0f", ySol[i]);
      if (solids[i].na == 1) {
        (void) strncpy(phaseEntry[4], solids[i].formula, 198);
        for (j=nFieldStatic; j<nField; j++) (void) snprintf(phaseEntry[j], 7, "%s", "");
      } else {
        char *formula;
        (*solids[i].convert)(THIRD, FOURTH, silminState->T, silminState->P, NULL, NULL, &ySol[i+1], mSol, NULL, NULL, NULL, NULL);
        (*solids[i].display)(FIRST, silminState->T, silminState->P, &ySol[i+1], &formula);
        (void) strncpy(phaseEntry[4], formula, 198); free(formula);
        for (j=0; j<solids[i].na; j++) {
          (void) snprintf(phaseEntry[nFieldStatic + 2*j], 11, "%.10s", solids[i+1+j].label);
          (void) snprintf(phaseEntry[nFieldStatic + 2*j + 1], 7, "%.3f", mSol[j]);
        }
        for (j=(nFieldStatic+2*solids[i].na); j<nField; j++) (void) snprintf(phaseEntry[j], 7, "%s", "");
      }
      for (j=0; j<nField; j++) vLine[j].textP = phaseEntry[j]; 
      clsAffn[i] = VListAddLine((VListWidget) phases, vLine, ((nStable+nAffn) == 0) ? VListAddAtTop : nStable+nAffn); 
      nAffn++;

    } else if (ySol[i] != 0.0 && clsAffn[i] != (Opaque) NULL) {
      (void) VListGetLineInfo((VListWidget) phases, clsAffn[i], &vLineP, &fieldP, &rowP);
      (void) snprintf(phaseEntry[3], 9, "%.0f", ySol[i]);
      VListChangeLineText((VListWidget) phases, VListFieldRowToLine((VListWidget) phases, 3, rowP), phaseEntry[3]);
      if (solids[i].na > 1) {
        char *formula;
        (*solids[i].display)(FIRST, silminState->T, silminState->P, &ySol[i+1], &formula);
        (void) strncpy(phaseEntry[4], formula, 198); free(formula);
        (*solids[i].convert)(THIRD, FOURTH, silminState->T, silminState->P, NULL, NULL, &ySol[i+1], mSol, NULL, NULL, NULL, NULL);
        VListChangeLineText((VListWidget) phases, VListFieldRowToLine((VListWidget) phases, 4, rowP), phaseEntry[4]);
        for (j=0; j<solids[i].na; j++) {
          (void) snprintf(phaseEntry[nFieldStatic + 2*j + 1], 7, "%.3f", mSol[j]);
          VListChangeLineText((VListWidget) phases, VListFieldRowToLine((VListWidget) phases, nFieldStatic+2*j+1, rowP), phaseEntry[nFieldStatic+2*j+1]);
        }
      }

    } else if (ySol[i] == 0.0 && clsAffn[i] != (Opaque) NULL) {
      VListRemoveLine((VListWidget) phases, clsAffn[i]); 
      clsAffn[i] = (Opaque) NULL; nAffn--;
    }
  }

  VListEndBatchUpdate((VListWidget) phases);
}

void updateTpPADB(int member) { }

#endif /* BATCH_VERSION */

void correctTforChangeInEnthalpy(void)
{
  static double *mSol, *rLiq, *rSol, *mOx;
  double pTemp, mTotal, hTotal, cpTotal, residual = DBL_MAX;
  int i, j, k, nl, ns, iter = 0;
  int hasLiquid = (silminState->liquidMass != 0.0);

  if (mSol == NULL) {
    for (i=0, j=1, k=1; i<npc; i++) if (solids[i].type == PHASE) 
      { j = MAX(j, solids[i].nr); k = MAX(k, solids[i].na); }

    mSol = (double *) malloc((size_t)       k*sizeof(double));
    rLiq = (double *) malloc((size_t) (nlc-1)*sizeof(double));
    rSol = (double *) malloc((size_t)       j*sizeof(double));
    mOx  = (double *) malloc((size_t)      nc*sizeof(double));
  }

  while ((fabs(residual) > 10.0*DBL_EPSILON*fabs(silminState->refEnthalpy)) && (iter < 50)) {

    if (silminState->fo2Path != FO2_NONE && hasLiquid) {
      silminState->fo2 = getlog10fo2(silminState->T, silminState->P, silminState->fo2Path);
      for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
        for (i=0; i<nc; i++) for (j=0, mOx[i]=0.0; j<nlc; j++) mOx[i] += (liquid[j].liqToOx)[i]*(silminState->liquidComp)[nl][j];
        conLiq(FIRST | SEVENTH, FIRST, silminState->T, silminState->P, mOx, NULL, NULL, NULL, NULL, NULL, &(silminState->fo2));
        for (i=0; i<nlc; i++) for (j=0, (silminState->liquidComp)[nl][i]=0.0; j<nc; j++) (silminState->liquidComp)[nl][i] += (bulkSystem[j].oxToLiq)[i]*mOx[j];
      }
    } else if (silminState->fo2Path != FO2_NONE && !hasLiquid) {
      double muO2;
      silminState->fo2 = getlog10fo2(silminState->T, silminState->P, silminState->fo2Path);
      muO2 = silminState->fo2*(R*silminState->T*log(10.0));
      if (!subsolidusmuO2(0,  &muO2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)) {
        printf("Failure to impose fo2 buffer in subsolidus.  Releasing buffer constraint from system.\n");
	silminState->fo2Path = FO2_NONE;
#ifndef BATCH_VERSION
        XmToggleButtonGadgetSetState(tg_path_none, True, True);
#endif
      }
    }

    hTotal  = 0.0;
    cpTotal = 0.0;
    if (hasLiquid) {
      for (i=0; i<nlc; i++) if ((silminState->liquidComp)[0][i] != 0.0) 
        gibbs(silminState->T, silminState->P, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
      for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
        for (i=0, mTotal= 0.0; i<nlc; i++) {
          mTotal  += (silminState->liquidComp)[nl][i];
          hTotal  += (silminState->liquidComp)[nl][i]*(liquid[i].cur).h;
          cpTotal += (silminState->liquidComp)[nl][i]*(liquid[i].cur).cp;
        }
        conLiq(SECOND, THIRD, silminState->T, silminState->P, NULL, (silminState->liquidComp)[nl], rLiq, NULL, NULL, NULL, NULL);
        hmixLiq(FIRST,  silminState->T, silminState->P, rLiq, &pTemp, NULL);
        hTotal += mTotal*pTemp;
        cpmixLiq(FIRST, silminState->T, silminState->P, rLiq, &pTemp, NULL, NULL);
        cpTotal += mTotal*pTemp;
      }
    }

    for (i=0; i<npc; i++) 
      for (ns=0; ns<(silminState->nSolidCoexist)[i]; ns++) {
        mTotal = (silminState->solidComp)[i][ns]; 
        if (solids[i].na == 1) {
          gibbs(silminState->T, silminState->P, (char *) solids[i].label, &(solids[i].ref), NULL, NULL, &(solids[i].cur));
          hTotal  += mTotal*(solids[i].cur).h;
          cpTotal += mTotal*(solids[i].cur).cp;
        } else {
          for (j=0; j<solids[i].na; j++) {
            mSol[j] = (silminState->solidComp)[i+1+j][ns];
            gibbs(silminState->T, silminState->P, (char *) solids[i+1+j].label, &(solids[i+1+j].ref), NULL, NULL, &(solids[i+1+j].cur));
            hTotal  += mSol[j]*(solids[i+1+j].cur).h;
            cpTotal += mSol[j]*(solids[i+1+j].cur).cp;
          }
          (*solids[i].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, mSol, rSol, NULL, NULL, NULL, NULL, NULL);
          (*solids[i].hmix)(FIRST, silminState->T, silminState->P, rSol, &pTemp);
          hTotal += mTotal*pTemp;
          (*solids[i].cpmix)(FIRST, silminState->T, silminState->P, rSol, &pTemp, NULL, NULL);
          cpTotal += mTotal*pTemp;
        }
      }

      residual = hTotal - silminState->refEnthalpy;
      silminState->T -= residual/cpTotal;
      iter++;

#ifdef DEBUG
  printf("Enthalpy corr: Iter = %d, T(C) = %.2f, H-Href = %g, Cp = %g\n", iter, silminState->T-273.15, residual, cpTotal);
#endif
  }
#ifdef DEBUG
  printf("Enthalpy corr: Iter = %d, T(C) = %.2f, H-Href = %g, Cp = %g\n", iter, silminState->T-273.15, residual, cpTotal);
#endif
}

void correctTforChangeInEntropy(void)
{
  static double *mSol, *rLiq, *rSol, *mOx;
  double pTemp, mTotal, sTotal, cpTotal, residual = DBL_MAX;
  int i, j, k, nl, ns, iter = 0;
  int hasLiquid = (silminState->liquidMass != 0.0);

  if (mSol == NULL) {
    for (i=0, j=1, k=1; i<npc; i++) if (solids[i].type == PHASE) 
      { j = MAX(j, solids[i].nr); k = MAX(k, solids[i].na); }

    mSol = (double *) malloc((size_t)       k*sizeof(double));
    rLiq = (double *) malloc((size_t) (nlc-1)*sizeof(double));
    rSol = (double *) malloc((size_t)       j*sizeof(double));
    mOx  = (double *) malloc((size_t)      nc*sizeof(double));
  }

  while ((fabs(residual) > 10.0*DBL_EPSILON*fabs(silminState->refEntropy)) && (iter < 50)) {

    if (silminState->fo2Path != FO2_NONE && hasLiquid) {
      silminState->fo2 = getlog10fo2(silminState->T, silminState->P, silminState->fo2Path);
      for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
        for (i=0; i<nc; i++) for (j=0, mOx[i]=0.0; j<nlc; j++) mOx[i] += (liquid[j].liqToOx)[i]*(silminState->liquidComp)[nl][j];
        conLiq(FIRST | SEVENTH, FIRST, silminState->T, silminState->P, mOx, NULL, NULL, NULL, NULL, NULL, &(silminState->fo2));
        for (i=0; i<nlc; i++) for (j=0, (silminState->liquidComp)[nl][i]=0.0; j<nc; j++) (silminState->liquidComp)[nl][i] += (bulkSystem[j].oxToLiq)[i]*mOx[j];
      }
    } else if (silminState->fo2Path != FO2_NONE && !hasLiquid) {
      double muO2;
      silminState->fo2 = getlog10fo2(silminState->T, silminState->P, silminState->fo2Path);
      muO2 = silminState->fo2*(R*silminState->T*log(10.0));
      if (!subsolidusmuO2(0, &muO2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)) {
        printf("Failure to impose fo2 buffer in subsolidus.  Releasing buffer constraint on the system.\n");
	silminState->fo2Path = FO2_NONE;
#ifndef BATCH_VERSION
        XmToggleButtonGadgetSetState(tg_path_none, True, True);
#endif
      }
    }

    sTotal  = 0.0;
    cpTotal = 0.0;
    if (hasLiquid) {
      for (i=0; i<nlc; i++) if ((silminState->liquidComp)[0][i] != 0.0)
        gibbs(silminState->T, silminState->P, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
      for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
        for (i=0, mTotal= 0.0; i<nlc; i++) {
          mTotal  += (silminState->liquidComp)[nl][i];
          sTotal  += (silminState->liquidComp)[nl][i]*(liquid[i].cur).s;
          cpTotal += (silminState->liquidComp)[nl][i]*(liquid[i].cur).cp;
        }
        conLiq(SECOND, THIRD, silminState->T, silminState->P, NULL, (silminState->liquidComp)[nl], rLiq, NULL, NULL, NULL, NULL);
        smixLiq(FIRST,  silminState->T, silminState->P, rLiq, &pTemp, NULL, NULL, NULL);
        sTotal += mTotal*pTemp;
        cpmixLiq(FIRST, silminState->T, silminState->P, rLiq, &pTemp, NULL, NULL);
        cpTotal += mTotal*pTemp;
      }
    }
 
    for (i=0; i<npc; i++) 
      for (ns=0; ns<(silminState->nSolidCoexist)[i]; ns++) {
        mTotal = (silminState->solidComp)[i][ns];
        if (solids[i].na == 1) {
          gibbs(silminState->T, silminState->P, (char *) solids[i].label, &(solids[i].ref), NULL, NULL, &(solids[i].cur));
          sTotal  += mTotal*(solids[i].cur).s;
          cpTotal += mTotal*(solids[i].cur).cp;
        } else {
          for (j=0; j<solids[i].na; j++) {
            mSol[j] = (silminState->solidComp)[i+1+j][ns];
            gibbs(silminState->T, silminState->P, (char *) solids[i+1+j].label, &(solids[i+1+j].ref), NULL, NULL, &(solids[i+1+j].cur));
            sTotal  += mSol[j]*(solids[i+1+j].cur).s;
            cpTotal += mSol[j]*(solids[i+1+j].cur).cp;
          }
          (*solids[i].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, mSol, rSol, NULL, NULL, NULL, NULL, NULL);
          (*solids[i].smix)(FIRST, silminState->T, silminState->P, rSol, &pTemp, NULL, NULL);
          sTotal += mTotal*pTemp;
          (*solids[i].cpmix)(FIRST, silminState->T, silminState->P, rSol, &pTemp, NULL, NULL);
          cpTotal += mTotal*pTemp;
        }
      }

      residual = sTotal - silminState->refEntropy;
      silminState->T -= residual*silminState->T/cpTotal;
      iter++;

#ifdef DEBUG
  printf("Entropy corr: Iter = %d, T(C) = %.2f, S-Sref = %g, Cp = %g\n", iter, silminState->T-273.15, residual, cpTotal);
#endif

  }
#ifdef DEBUG
  printf("Entropy corr: Iter = %d, T(C) = %.2f, S-Sref = %g, Cp = %g\n", iter, silminState->T-273.15, residual, cpTotal);
#endif
}

void correctPforChangeInVolume(void)
{
  static double *mSol, *rLiq, *rSol, *mOx;
  double pTemp, dpTemp, mTotal, vTotal, dvdpTotal, residual = DBL_MAX;
  int i, j, k, nl, ns, iter = 0;
  int hasLiquid = (silminState->liquidMass != 0.0);

  if (mSol == NULL) {
    for (i=0, j=1, k=1; i<npc; i++) if (solids[i].type == PHASE) { j = MAX(j, solids[i].nr); k = MAX(k, solids[i].na); }

    mSol = (double *) malloc((size_t)       k*sizeof(double));
    rLiq = (double *) malloc((size_t) (nlc-1)*sizeof(double));
    rSol = (double *) malloc((size_t)       j*sizeof(double));
    mOx  = (double *) malloc((size_t)      nc*sizeof(double));
  }

  while ((fabs(residual) > 10.0*DBL_EPSILON*fabs(silminState->refVolume)) && (iter < 50)) {

    if (silminState->fo2Path != FO2_NONE && hasLiquid) {
      silminState->fo2 = getlog10fo2(silminState->T, silminState->P, silminState->fo2Path);
      for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
        for (i=0; i<nc; i++) for (j=0, mOx[i]=0.0; j<nlc; j++) mOx[i] += (liquid[j].liqToOx)[i]*(silminState->liquidComp)[nl][j];
        conLiq(FIRST | SEVENTH, FIRST, silminState->T, silminState->P, mOx, NULL, NULL, NULL, NULL, NULL, &(silminState->fo2));
        for (i=0; i<nlc; i++) for (j=0, (silminState->liquidComp)[nl][i]=0.0; j<nc; j++) (silminState->liquidComp)[nl][i] += (bulkSystem[j].oxToLiq)[i]*mOx[j];
      }
    } else if (silminState->fo2Path != FO2_NONE && !hasLiquid) {
      double muO2;
      silminState->fo2 = getlog10fo2(silminState->T, silminState->P, silminState->fo2Path);
      muO2 = silminState->fo2*(R*silminState->T*log(10.0));
      if (!subsolidusmuO2(0, &muO2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)) {
        printf("Failure to impose fo2 buffer in subsolidus.  Releasing buffer constraint from the system.\n");
	silminState->fo2Path = FO2_NONE;
#ifndef BATCH_VERSION
        XmToggleButtonGadgetSetState(tg_path_none, True, True);
#endif
      }
    }

    vTotal  = 0.0;
    dvdpTotal = 0.0;
    if (hasLiquid) {
      for (i=0, mTotal= 0.0; i<nlc; i++) if ((silminState->liquidComp)[0][i] != 0.0) 
        gibbs(silminState->T, silminState->P, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
      for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
        for (i=0, mTotal= 0.0; i<nlc; i++) {
          mTotal    += (silminState->liquidComp)[nl][i];
          vTotal    += (silminState->liquidComp)[nl][i]*(liquid[i].cur).v;
          dvdpTotal += (silminState->liquidComp)[nl][i]*(liquid[i].cur).dvdp;
        }
        conLiq(SECOND, THIRD, silminState->T, silminState->P, NULL, (silminState->liquidComp)[nl], rLiq, NULL, NULL, NULL, NULL);
        vmixLiq(FIRST | FIFTH,  silminState->T, silminState->P, rLiq, &pTemp, NULL, NULL, NULL, &dpTemp, NULL, NULL, NULL, NULL, NULL, NULL);
        vTotal    += mTotal*pTemp;
        dvdpTotal += mTotal*dpTemp;
      }
    }

    for (i=0; i<npc; i++) 
      for (ns=0; ns<(silminState->nSolidCoexist)[i]; ns++) {
        mTotal = (silminState->solidComp)[i][ns]; 
        if (solids[i].na == 1) {
          gibbs(silminState->T, silminState->P, (char *) solids[i].label, &(solids[i].ref), NULL, NULL, &(solids[i].cur));
          vTotal    += mTotal*(solids[i].cur).v;
          dvdpTotal += mTotal*(solids[i].cur).dvdp;
        } else {
          for (j=0; j<solids[i].na; j++) {
            mSol[j] = (silminState->solidComp)[i+1+j][ns];
            gibbs(silminState->T, silminState->P, (char *) solids[i+1+j].label, &(solids[i+1+j].ref), NULL, NULL, &(solids[i+1+j].cur));
            vTotal    += mSol[j]*(solids[i+1+j].cur).v;
            dvdpTotal += mSol[j]*(solids[i+1+j].cur).dvdp;
          }
          (*solids[i].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, mSol, rSol, NULL, NULL, NULL, NULL, NULL);
          (*solids[i].vmix)(FIRST | FIFTH, silminState->T, silminState->P, rSol, &pTemp, NULL, NULL, NULL, &dpTemp, NULL, NULL, NULL, NULL, NULL);
          vTotal    += mTotal*pTemp;
          dvdpTotal += mTotal*dpTemp;
        }
      }

      residual = vTotal - silminState->refVolume;
      silminState->P -= residual/dvdpTotal;
      iter++;

#ifdef DEBUG
  printf("Volume corr: Iter = %d, P = %.2f, V-Vref = %g, dVdP = %g\n", iter, silminState->P, residual, dvdpTotal);
#endif

  }
#ifdef DEBUG
  printf("Volume corr: Iter = %d, P = %.2f, V-Vref = %g, dVdP = %g\n", iter, silminState->P, residual, dvdpTotal);
#endif
}

/*************************************************************************
   This (misnamed) function finds a way to adjust the solid assemblage
   so as to change the bulk solid composition by *deltaBulkComp (a vector
   of moles of oxides).  This is used to add or drop solids when liquid is
   absent or to add or drop liquid, without kludging the bulk composition.

   Additional twist, added 7/24/95 -- each column of SolToOx is weighted
   by the silminState->solidComp[], and the solution vector is then un-
   weighted after the SVD.  This forces a solution which changes most those
   phase-components which are most abundant, hence minimizing the reulting
   departure from equilibrium.

   8/10/95 -- add test of each solid, return failure is infeasible      
*************************************************************************/

int addOrDropLiquid(double *deltaBulkComp) {
  int i, j, k, l, n, result;
  double **reducedSolToOx;
  double *w, **v, *deltaSol, *weights;
  char *yes;

  result = TRUE;
  /* count solid phase-components in assemblage */
  for (i=0, n=0; i<npc; i++) if (silminState->nSolidCoexist[i]) n+= solids[i].na;

  /* allocate memory */
  reducedSolToOx = matrix(1, nc, 1, n);
  w = vector(1, n);
  v = matrix(1, n, 1, n);
  deltaSol = vector(1, n);
  weights = vector(1, n);
  yes = (char *) malloc((size_t) (nc+1)*sizeof(char));
  for (i=1; i<=nc; i++) yes[i] = True;

  /* construct reduced SolToLiq matrix */
  for (i=0, k=1; i<npc; i++) {
    if (silminState->nSolidCoexist[i]) {
      if (solids[i].na == 1) {
        weights[k] = silminState->solidComp[i][0];
        for (j=1; j<=nc; j++) reducedSolToOx[j][k] = (solids[i].solToOx)[j-1]*weights[k];
        k++;
      } else for (l=0; l<solids[i].na; l++) {
        weights[k] = silminState->solidComp[i+1+l][0];
        for(j=1; j<=nc; j++) reducedSolToOx[j][k] = (solids[i+1+l].solToOx)[j-1]*weights[k];
        k++;
      }
    }
  }

  /* SVD it and backsub deltaBulkComp to get correction vector */
  svdcmp(reducedSolToOx, nc, n, w, v);
  for (i=1;i<=n;i++) if (w[i] <= 1.0e-08) w[i] = 0.0;
  svbksb(reducedSolToOx, w, v, nc, n, (deltaBulkComp-1), yes, deltaSol);

  /* apply the correction */
  for (i=0, k=1; i<npc; i++) {
    if (silminState->nSolidCoexist[i]) {
      if (solids[i].na == 1) {
        silminState->solidComp[i][0] -= weights[k]*deltaSol[k]; k++;
        if (silminState->solidComp[i][0] <= 0.0) result = FALSE;
      } else {
        double *mSol = vector(0, solids[i].na);
        for (j=0;j<solids[i].na;j++) {
          silminState->solidComp[i][0] -= weights[k]*deltaSol[k];
          mSol[j] = (silminState->solidComp[i+1+j][0] -= weights[k]*deltaSol[k]); k++;
        }
        if (silminState->solidComp[i][0] <= 0.0) result = FALSE;
        else result = result & (*solids[i].test)(SIXTH, silminState->T, silminState->P, 0, 0, NULL, NULL, NULL, mSol);
        free_vector(mSol, 0, solids[i].na);
      }
    }
  }

  /* undo the correction on failure */
  if (result == FALSE) {
    for (i=0, k=1; i<npc; i++) {
      if (silminState->nSolidCoexist[i]) {
        if (solids[i].na == 1) {
          silminState->solidComp[i][0] += weights[k]*deltaSol[k]; k++;
        } else {
          for (j=0; j<solids[i].na; j++) {
            silminState->solidComp[i][0] += weights[k]*deltaSol[k];
            silminState->solidComp[i+1+j][0] += weights[k]*deltaSol[k]; k++;
          }
        }
      }
    }
  }
  free_matrix(reducedSolToOx, 1, nc, 1, n);
  free_matrix(v, 1, n, 1, n);
  free_vector(w, 1, n);
  free_vector(deltaSol, 1, n);
  free_vector(weights, 1, n);
  free(yes);

  return result;
}

/* end of file SILMIN_SUPPORT.C */
