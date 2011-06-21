const char *create_preclb_ver(void) { return "$Id: create_preclb.c,v 1.17 2008/11/12 01:24:47 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: create_preclb.c,v $
MELTS Source Code: RCS Revision 1.13  2008/05/20 17:32:21  ghiorso
MELTS Source Code: RCS Added FeSiO3 and FeAlO2.5 species to balance Mg-equivalents.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.12  2008/05/02 19:03:52  ghiorso
MELTS Source Code: RCS Revised liquid speciation model.
MELTS Source Code: RCS Created new test routine for homogeneous equilibrium fO2 at P.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.11  2007/11/01 15:44:06  ghiorso
MELTS Source Code: RCS Permit volume regression for solid phases.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.10  2007/10/03 21:33:47  ghiorso
MELTS Source Code: RCS Updated liquid eos thermodynamics.
MELTS Source Code: RCS Added regression of ferric/ferrous parameters from data file.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.9  2007/09/13 16:12:02  ghiorso
MELTS Source Code: RCS (1) Revised standard state liquid properties.
MELTS Source Code: RCS (2) Revised standard state solid properties (removed non-Berman) Cp, and
MELTS Source Code: RCS     removed Saxena EOS treatment.  All EOS parameterizations are Vinet.
MELTS Source Code: RCS     Updated K, K', alpha to conform to Knittle (1995) and Fei (1995)
MELTS Source Code: RCS     except where refitted Berman (1988) makes more sense.
MELTS Source Code: RCS (3) Updated code to allow for fusion entropies of liquid components to
MELTS Source Code: RCS     be adjusted (fusion enthalpies are dependent).
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.8  2007/06/16 01:01:55  ghiorso
MELTS Source Code: RCS Revised EOS regression to have K', K'', and K''' as parameters.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.7  2007/06/08 17:25:42  ghiorso
MELTS Source Code: RCS Added code to allow regression of Ghiorso EOS parameters
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2007/03/11 22:51:21  ghiorso
MELTS Source Code: RCS Added ability to regress H and S of solid phases and components.
MELTS Source Code: RCS Added abviity to select individual solid phase components for calibration.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2007/02/21 21:51:18  ghiorso
MELTS Source Code: RCS New regressions options and parameter selection buttons
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2007/02/13 21:48:29  ghiorso
MELTS Source Code: RCS Modifications to read XML database files for LEPER calibration.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2006/08/17 20:47:54  ghiorso
MELTS Source Code: RCS Clarified variable initialization issues in routines.  Problems discovered
MELTS Source Code: RCS when compiler optimization is turned on.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:18  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:35  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2004/09/25 19:01:50  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2004/09/21 16:07:51  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2003/09/27 15:35:22  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.6  1997/06/21  22:50:01  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:23:40  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:43  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:33:46  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  17:25:37  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  17:25:37  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Function to create the preclb_adb widget and its children
**      (file: CREATE_PRECLB.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  September 5, 1990 Original Version
**      V1,0-2  Mark S. Ghiorso  June 26, 1991
**              Modified preclbRank structure to point to work procedures
**              and external functions in PRECLB.C and PRECLB_SUPPORT.C  
**      V1.0-3  Mark S. Ghiorso  August 30, 1991
**              Added globally known widget definitions and symbols
**      V1.0-4  Mark S. Ghiorso  August 31, 1991
**              Added double click facility to invoke cmw from parameter
**              selection toggles. When DecWindows supports Xt toolkit R4,
**              the multiclick interval should be gotten from the 
**              server and set here using XtgetMultiClickRate
**      V1.0-5  Mark S. Ghiorso  September 13, 1991
**              Added reference to preclbRank.client_data
**      V1.0-6  Mark S. Ghiorso  November 9, 1991
**              Corrected error in initialization of preclbCount structure
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  December 20, 1991
**              Corrected error in XtAddCallback call for phaseAbsent toggles
**      V2.0-3  Mark S. Ghiorso  January 4, 1992
**              (1) Altered resource declarations for graph widget from
**                  XtN -> GwN
**      V2.0-4  Mark S. Ghiorso  March 17, 1992
**              Added macros for non-DEC motif extensions
**      V2.0-5  Mark S. Ghiorso  March 27, 1992
**              Corrected casting violations for callback structures
**      V3.0-1  Mark S. Ghiorso  July 13, 1993
**              (1) Added new button to component_adb to allow toggles
**                  to display active enthapy parameters as well as
**                  entropy parameters
**      V3.0-2  Mark S. Ghiorso  July 19, 1993
**              (1) Revised logic to include excess volume terms
**      V3.0-3  Mark S. Ghiorso  September 21, 1993
**              XtFree -> XmStringFree
**      V3.0-4  Mark S. Ghiorso  April 5, 1994
**              Added #ifdef __osf__ to fix 64 bit errors
**      V3.0-5  Mark S. Ghiorso  April 23, 1994
**              Corrected casting violations to callback structures
**--
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/PanedW.h>
#include <Xm/PushBG.h>
#include <Xm/Scale.h>
#include <Xm/SashP.h>     /* We need to stop keyboard traversal on the sashes */
#include <Xm/ScrolledW.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>

#include "interface.h"
#include "silmin.h"

/******************************************************************************
 * Globally known symbols declared extern in INTERFACE.H
 ******************************************************************************/

Widget preclb_adb, action_adb, phase_adb, component_adb, std_adb, mrqrdt_adb;
Widget *actionADB, *mrqrdtADB;

PreclbCount *preclbCount;

/*
 *=============================================================================
 * Layout and Macro definitions for create_preclb():
 *
 -----------------------------------------------------------------------------
 |                                     |				     | 
 |             action_adb              L				     |
 |                                     E				     |
 |-------------TOP_MRQRDT--------------F				     |
 |                                     T				     |
 |                                     _				     |
 |             mrqrdt_adb              C				     |
 |                                     O				     |
 |                                     M	   component_adb	     |
 |                                     P				     |
 |                                     |				     |
 |-------------TOP_PHASE---------------|-------------BOTTOM_COMP-------------|
 |                                      	         |		     |
 |                                      	         L		     |
 |                         	        	         E		     |
 |             phase_adb                	         F		     |
 |                                      	         T		     |
 |                         	        	         _	std_adb      |
 |                         	        	         S		     |
 |                                      	         T		     |
 |                                      	         D		     |
 |                                      	         |		     |
 -----------------------------------------------------------------------------
*/

#define TOP_MRQRDT   15
#define TOP_PHASE    40
#define LEFT_COMP    50
#define BOTTOM_COMP  40
#define LEFT_STD     75

static void create_action_adb();
static void create_phase_adb();
static void create_component_adb();
static void create_std_adb();
static void create_mrqrdt_adb();

void create_preclb()
{
/*
 *=============================================================================
 * Create the form widget container for the pre-calibration display
 * (1) The widget is not managed. This is done within the push button callback 
 *     routines when command mode is set to pre-calibration
 * (2) All the widget's children are managed however.
 * (3) This form widget will be made the work window widget of the main 
 *     window
 */
  preclb_adb = XmCreateForm(main_window, "Form", NULL, 0);

  create_action_adb();
  create_phase_adb();
  create_component_adb();
  create_std_adb();
  create_mrqrdt_adb();
}

static void preclb_bt_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static int k_preclb_bt_select = 1; 
static int k_preclb_bt_clearW = 2; 
static int k_preclb_bt_clearK = 3; 
static int k_preclb_bt_clearS = 4; 
static int k_preclb_bt_clearM = 5; 

/*
 *==============================================================================
 * Create action sub region
 */

static void create_action_adb() {

  static Widget frame, label;
  XmString csString;

  actionADB = (Widget *) XtMalloc( (unsigned) 3*sizeof(Widget));

  frame = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, preclb_adb, 
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, TOP_MRQRDT,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition,  LEFT_COMP,
    NULL);

  action_adb = XtVaCreateWidget("Form", xmFormWidgetClass, frame, NULL);

  csString = XmStringCreateLtoR("Status:", "ISO8859-1");
  label = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, action_adb,
    XmNlabelString,     csString,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,  2,
    XmNleftAttachment,  XmATTACH_POSITION, XmNleftPosition, 2,
    NULL);
  XmStringFree(csString);

  csString = XmStringCreateLtoR(
    "Awaiting user configuration and Execute command", "ISO8859-1");
  actionADB[0] = XtVaCreateManagedWidget("Label", xmLabelWidgetClass, action_adb,
    XmNlabelString,     csString,
    XmNforeground,      red,
    XmNalignment,       XmALIGNMENT_BEGINNING,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,  27,
    XmNleftAttachment,  XmATTACH_POSITION, XmNleftPosition, 2,
    XmNrightAttachment, XmATTACH_FORM, 
    NULL);
  XmStringFree(csString);

  csString = XmStringCreateLtoR(" ", "ISO8859-1");
  actionADB[1] = XtVaCreateManagedWidget("Label", xmLabelWidgetClass, action_adb,
    XmNlabelString,     csString,
    XmNalignment,       XmALIGNMENT_BEGINNING,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,  52,
    XmNleftAttachment,  XmATTACH_POSITION, XmNleftPosition, 2,
    XmNrightAttachment, XmATTACH_FORM, 
    NULL);
  actionADB[2] = XtVaCreateManagedWidget("Label", xmLabelWidgetClass, action_adb,
    XmNlabelString,     csString,
    XmNalignment,       XmALIGNMENT_BEGINNING,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,  77,
    XmNleftAttachment,  XmATTACH_POSITION, XmNleftPosition, 2,
    XmNrightAttachment, XmATTACH_FORM, 
    NULL);
  XmStringFree(csString);

  XtManageChild(action_adb);
}

/*
 *==============================================================================
 * Create phase-selection region  
 */

#define COL1  2
#define COL2 15
#define COL3 17
#define COL4 21
#define COL5 23
#define COL6 27
#define COL7 29
#define COL8 31

static void phtg_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static Widget *hTogglesMin;
static Widget *sTogglesMin;
static Widget *vTogglesMin;

static void create_phase_adb() {

  int j, top, left, offset;
  XmString csString1, csString2;
  static Widget *phaseLabels;
  static Widget *presentToggles;
  static Widget *absentToggles;
  static Widget frame, button;
  static struct {
    const char *label;  /* Widget label           */
    Widget     name;    /* Widget ID              */
    int        top;     /* top relative position  */
    int        left;    /* left relative position */
  } privLabels[24] = {
    { "Phase", (Widget) NULL,  2, COL1      } ,
    { "Inc"  , (Widget) NULL,  2, COL2      } ,
    { "N",     (Widget) NULL,  2, COL3+1    } ,
    { "Abs"  , (Widget) NULL,  2, COL4      } ,
    { "N ",    (Widget) NULL,  2, COL5+1    } ,
    { "H",     (Widget) NULL,  2, COL6      } ,
    { "S",     (Widget) NULL,  2, COL7      } ,
    { "V",     (Widget) NULL,  2, COL8      } ,
    { "Phase", (Widget) NULL,  2, COL1+33   } ,
    { "Inc"  , (Widget) NULL,  2, COL2+33   } ,
    { "N ",    (Widget) NULL,  2, COL3+33+1 } ,
    { "Abs"  , (Widget) NULL,  2, COL4+33   } ,
    { "N ",    (Widget) NULL,  2, COL5+33+1 } ,
    { "H",     (Widget) NULL,  2, COL6+33   } ,
    { "S",     (Widget) NULL,  2, COL7+33   } ,
    { "V",     (Widget) NULL,  2, COL8+33   } ,
    { "Phase", (Widget) NULL,  2, COL1+66   } ,
    { "Inc"  , (Widget) NULL,  2, COL2+66   } ,
    { "N ",    (Widget) NULL,  2, COL3+66+1 } ,
    { "Abs"  , (Widget) NULL,  2, COL4+66   } ,
    { "N ",    (Widget) NULL,  2, COL5+66+1 } ,
    { "H",     (Widget) NULL,  2, COL6+66   } ,
    { "S",     (Widget) NULL,  2, COL7+66   } ,
    { "V",     (Widget) NULL,  2, COL8+66   }
  };

  frame = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, preclb_adb, 
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition,    TOP_PHASE,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition,  LEFT_STD,
    NULL);

  phase_adb = XtVaCreateWidget("Form", xmFormWidgetClass, frame, NULL);

  for (j = 0; j < 24; j++) {
    csString1 = XmStringCreateLtoR((char *) privLabels[j].label, "ISO8859-1");
    privLabels[j].name = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, phase_adb,
      XmNlabelString,    csString1,
      XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  privLabels[j].top,
      XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, privLabels[j].left,
      NULL);
    XmStringFree(csString1);
  }

  preclbCount = (PreclbCount *) XtCalloc( npc, (int) sizeof(PreclbCount));
  phaseLabels    = (Widget *) XtMalloc( (unsigned) (npc*sizeof(Widget)));
  presentToggles = (Widget *) XtMalloc( (unsigned) (npc*sizeof(Widget)));
  absentToggles  = (Widget *) XtMalloc( (unsigned) (npc*sizeof(Widget)));
  hTogglesMin    = (Widget *) XtMalloc( (unsigned) (npc*sizeof(Widget)));
  sTogglesMin    = (Widget *) XtMalloc( (unsigned) (npc*sizeof(Widget)));
  vTogglesMin    = (Widget *) XtMalloc( (unsigned) (npc*sizeof(Widget)));

  top = 6;
  offset = 0;
  csString1 = XmStringCreateLtoR("-----", "ISO8859-1");
  for (j = 0; j < npc; j++) {
    preclbCount[j].usePhase = FALSE;
    preclbCount[j].np = 0;
    preclbCount[j].absPhase = FALSE;
    preclbCount[j].na = 0;
    if (/* (solids[j].type == PHASE) && */ solids[j].inclInClb) {

      /* phase label widget */
      left = COL1 + offset;
      csString2 = XmStringCreateLtoR((char *) solids[j].label, "ISO8859-1");
      phaseLabels[j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, phase_adb, 
        XmNlabelString,    csString2,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
	XmNforeground, (solids[j].type == PHASE) ? blue : black,
        NULL);
      XmStringFree(csString2);

      /* phase present toggle widget */
      preclbCount[j].usePhase = (solids[j].activity != NULL) ||
                                (solids[j].ref.h    != 0.0 );
      left = COL2 + offset;
      presentToggles[j] = XtVaCreateManagedWidget("Toggle", xmToggleButtonGadgetClass, phase_adb, 
        XmNlabelString,    cs_empty_string, 
        XmNindicatorType,  XmONE_OF_MANY,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
        XmNsensitive,      (preclbCount[j].usePhase) ? True : False,
        XmNindicatorOn,    (preclbCount[j].usePhase) ? True : False, 
	XmNselectColor,    red,
        NULL);
      {
      long jLong = (long) j;
      XtAddCallback(presentToggles[j], XmNvalueChangedCallback, phtg_callback, (XtPointer) jLong);
      }
      XmToggleButtonSetState(presentToggles[j], preclbCount[j].usePhase, False);
 
      /* phase present label widget */
      left = COL3 + offset;
      preclbCount[j].present = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, phase_adb,
        XmNlabelString,    csString1,
        XmNrecomputeSize,  False,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
        NULL);

      /* phase absent toggle widget */
      left = COL4 + offset;
      absentToggles[j] = XtVaCreateManagedWidget("Toggle", xmToggleButtonGadgetClass, phase_adb, 
        XmNlabelString,    cs_empty_string,
        XmNindicatorType,  XmONE_OF_MANY,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
        XmNsensitive,      (preclbCount[j].usePhase) ? True : False,
        XmNindicatorOn,    (preclbCount[j].usePhase) ? True : False, 
	XmNselectColor,    red,
        NULL);
      {
      long longTag = (long) (j+npc);
      XtAddCallback(absentToggles[j], XmNvalueChangedCallback, phtg_callback, (XtPointer) longTag);
      }
      XmToggleButtonSetState(absentToggles[j], preclbCount[j].absPhase, False);

      /* phase absent label widget */
      left = COL5 + offset;
      preclbCount[j].absent = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, phase_adb,  
        XmNlabelString,    csString1,
        XmNrecomputeSize,  False,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top, 
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
        NULL);
	
      /* regress enthalpy toggle widget */
      left = COL6 + offset;
      hTogglesMin[j] = XtVaCreateManagedWidget("Toggle", xmToggleButtonGadgetClass, phase_adb, 
        XmNlabelString,    cs_empty_string,
        XmNindicatorType,  XmONE_OF_MANY,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
        XmNsensitive,      (preclbCount[j].usePhase) ? True : False,
        XmNindicatorOn,    (preclbCount[j].usePhase) ? True : False, 
	XmNselectColor,    red,
        NULL);
      {
      long longTag = (long) (j+2*npc);
      XtAddCallback(hTogglesMin[j], XmNvalueChangedCallback, phtg_callback, (XtPointer) longTag);
      }
      XmToggleButtonSetState(hTogglesMin[j], modelParameters[nls*(nls-1)/2+nls+j].activeH, False);

      /* regress entropy toggle widget */
      left = COL7 + offset;
      sTogglesMin[j] = XtVaCreateManagedWidget("Toggle", xmToggleButtonGadgetClass, phase_adb, 
        XmNlabelString,    cs_empty_string,
        XmNindicatorType,  XmONE_OF_MANY,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
        XmNsensitive,      (preclbCount[j].usePhase) ? True : False,
        XmNindicatorOn,    (preclbCount[j].usePhase) ? True : False, 
	XmNselectColor,    red,
        NULL);
      {
      long longTag = (long) (j+3*npc);
      XtAddCallback(sTogglesMin[j], XmNvalueChangedCallback, phtg_callback, (XtPointer) longTag);
      }
      XmToggleButtonSetState(sTogglesMin[j], modelParameters[nls*(nls-1)/2+nls+j].activeS, False);

      /* regress volume toggle widget */
      left = COL8 + offset;
      vTogglesMin[j] = XtVaCreateManagedWidget("Toggle", xmToggleButtonGadgetClass, phase_adb, 
        XmNlabelString,    cs_empty_string,
        XmNindicatorType,  XmONE_OF_MANY,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
        XmNsensitive,      (preclbCount[j].usePhase) ? True : False,
        XmNindicatorOn,    (preclbCount[j].usePhase) ? True : False, 
	XmNselectColor,    red,
        NULL);
      {
      long longTag = (long) (j+4*npc);
      XtAddCallback(vTogglesMin[j], XmNvalueChangedCallback, phtg_callback, (XtPointer) longTag);
      }
      XmToggleButtonSetState(vTogglesMin[j], modelParameters[nls*(nls-1)/2+nls+j].activeV, False);

      top = top + 2;
      if (top > 95) {
        offset += 33;
        top = 6;
      }
    }
  }
  XmStringFree(csString1);
  
  /* Create Parameter clear button */
  csString1 = XmStringCreateLtoR("ClearM", "ISO8859-1");
  button = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, phase_adb, 
    XmNlabelString,      csString1,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  {
  long longTag = (long) k_preclb_bt_clearM;
  XtAddCallback(button, XmNactivateCallback, preclb_bt_callback, (XtPointer) longTag);
  }
  XmStringFree(csString1);

  XtManageChild(phase_adb);
}

#undef COL1
#undef COL2
#undef COL3
#undef COL4
#undef COL5
#undef COL6
#undef COL7
#undef COL8

static void phtg_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmToggleButtonCallbackStruct *callback_data = (XmToggleButtonCallbackStruct *) cbDataGen;

  switch (callback_data->reason) {

  case XmCR_VALUE_CHANGED :
    if      (tag <   npc) preclbCount[tag      ].usePhase = callback_data->set;
    else if (tag < 2*npc) preclbCount[tag  -npc].absPhase = callback_data->set;
    else if (tag < 3*npc) modelParameters[nls*(nls-1)/2+nls+tag-2*npc].activeH = callback_data->set;
    else if (tag < 4*npc) modelParameters[nls*(nls-1)/2+nls+tag-3*npc].activeS = callback_data->set;
    else if (tag < 5*npc) modelParameters[nls*(nls-1)/2+nls+tag-4*npc].activeV = callback_data->set;
    break;

  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;

  default:
    break;

  }
}

/*
 *==============================================================================
 * Create parameter-selection regions
 */

#define BITMAP_WIDTH  7
#define BITMAP_HEIGHT 7
static char bits[] = { /* this is a 6 x 6 bit filled in square */
                       0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f };
   
static void cmptg_callback(Widget w, XtPointer cData, XtPointer cbDataGen);

#define SELECT_WH 1
#define SELECT_WS 2
#define SELECT_WV 3
static int paramSetChoice = SELECT_WH;
static Widget *paramSetToggles, *stdSetToggles;

static void create_component_adb() {

  Pixmap square, empty, set;
  unsigned int width  = BITMAP_WIDTH;
  unsigned int height = BITMAP_HEIGHT;
  int j, k, l, top, left, bot;
  XmString csString;
  static Widget *labels, button, pane, sPane;

  /***************************************************************************
   * create a Scrolled Window to hold the display      
   ***************************************************************************/
  sPane = XtVaCreateWidget("sPane", xmScrolledWindowWidgetClass, preclb_adb,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, BOTTOM_COMP,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,   LEFT_COMP,
    XmNrightAttachment,  XmATTACH_FORM,
    XmNscrollingPolicy,  XmAUTOMATIC,
    NULL);

  /***************************************************************************
   * pane window to hold everything - this is the only child of the Scrolled 
   * Window
   ***************************************************************************/
  pane = XtVaCreateWidget("Pane", xmPanedWindowWidgetClass, sPane,
    XmNsashWidth,        1,
    XmNsashHeight,       1,
    NULL);

  /* ********************************************************************************
   * Working area of the pane window and vertical separator
   * height: 2*nls, spacing is 2 (top,bot + *). Note, 5+2*nls+5 should not exceed 100
   * width: 2*nls, spacing is 2 (left + *). Note, 15+2*nls+15 should not exceed 100
   * 6 is the conversion from spacing to pixels (arbitrary; whatever looks good).
   **********************************************************************************/
  component_adb = XtVaCreateWidget("Form", xmFormWidgetClass, pane, 
    XmNheight,         ( 5+2*nls+ 5)*6*2,
    XmNwidth,          (15+2*nls+15)*6*2,
  NULL);

  /* make labels for left edge and diagonal entries */
  labels  = (Widget *) XtMalloc( (unsigned) ( 2*(nls-1)*sizeof(Widget)) );
  
  top  = 5;
  left =  2;
  for (j=1; j<nls; j++) {
    size_t lenA = strcspn(liquid[j].label, " ");
    size_t lenB = strcspn(liquid[j].label, ")")+1;
    size_t len  = (lenA < lenB) ? lenA : lenB;
    char *temp  = (char *) malloc((size_t) (len+1)*sizeof(char));
    temp = strncpy(temp, liquid[j].label, len); temp[len] = '\0';
    csString = XmStringCreateLtoR(temp, "ISO8859-1");
    free(temp);
    labels[j-1] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, component_adb,
      XmNlabelString,    csString,
      XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
      XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
      NULL);
    XmStringFree(csString);
    top = top + 3;
  }

  bot  = 5; left = 15;
  for (j=0; j<(nls-1); j++) {
    size_t lenA = strcspn(liquid[j].label, " ");
    size_t lenB = strcspn(liquid[j].label, ")")+1;
    size_t len  = (lenA < lenB) ? lenA : lenB;
    char *temp = (char *) malloc((size_t) (len+1)*sizeof(char));
    temp = strncpy(temp, liquid[j].label, len); temp[len] = '\0';
    csString = XmStringCreateLtoR(temp, "ISO8859-1");
    free(temp);
    labels[nls-1+j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, component_adb, 
      XmNlabelString,      csString,
      XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, bot,
      XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,   left,
      NULL);
    XmStringFree(csString);
    bot = bot + 3; left = left + 3;
  }

  /* make toggle button entries to fill in the matrix */
  paramSetToggles = (Widget *) XtMalloc( (unsigned) (nls*(nls-1)*sizeof(Widget)/2) );
  empty = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
            bits, width, height, white, white, DefaultDepthOfScreen(XtScreen(topLevel)));
  set   = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
            bits, width, height, black, black, DefaultDepthOfScreen(XtScreen(topLevel)));

  left = 15;
  for (j=0, l=0; j<nls; j++) {
    top = 5 + j*3;
    for (k =(j+1); k<nls; k++,l++) {
      square = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
                 bits, width, height, red, white, DefaultDepthOfScreen(XtScreen(topLevel)));
      paramSetToggles[l] = XtVaCreateManagedWidget(
        "Toggle", xmToggleButtonWidgetClass, component_adb,
        XmNindicatorOn,    False,
        XmNlabelType,      XmPIXMAP,
        XmNvisibleWhenOff, True,
        XmNlabelPixmap,    (modelParameters[l].enthalpy != 0.0) ? set : empty,
        XmNselectPixmap,   square,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
        NULL);
      {
      long longTag = (long) l;
      XtAddCallback(paramSetToggles[l], XmNvalueChangedCallback, cmptg_callback, (XtPointer) longTag);
      }
      XmToggleButtonSetState(paramSetToggles[l], modelParameters[l].activeH, False);    
      top = top + 3;
    }
    left = left + 3;
  }      

  /* Create Parameter selection button */
  csString = XmStringCreateLtoR("Select WH", "ISO8859-1");
  button = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, component_adb, 
    XmNlabelString,      csString,
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition,     5,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition,  95,
    NULL);
  {
  long longTag = (long) k_preclb_bt_select;
  XtAddCallback(button, XmNactivateCallback, preclb_bt_callback, (XtPointer) longTag);
  }
  XmStringFree(csString);

  /* Create Parameter clear button */
  csString = XmStringCreateLtoR("ClearW", "ISO8859-1");
  button = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, component_adb, 
    XmNlabelString,      csString,
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition,    20,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition,  95,
    NULL);
  {
  long longTag = (long) k_preclb_bt_clearW;
  XtAddCallback(button, XmNactivateCallback, preclb_bt_callback, (XtPointer) longTag);
  }
  XmStringFree(csString);

  XtManageChild(component_adb);
  
  XtManageChild(pane);
  {
    Widget *children;
    int    num_children;
    XtVaGetValues(pane,
      XmNchildren, &children, XmNnumChildren, &num_children, NULL);
    while (num_children-- > 0)
      if (XtIsSubclass(children[num_children], xmSashWidgetClass))
        XtVaSetValues(children[num_children], XmNtraversalOn, False, NULL);
  }
  
  XtManageChild(sPane);
}

static void cmptg_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmToggleButtonCallbackStruct *callback_data = (XmToggleButtonCallbackStruct *) cbDataGen;

  switch (callback_data->reason) {

  case XmCR_VALUE_CHANGED :
    if      (paramSetChoice == SELECT_WH) modelParameters[tag].activeH = callback_data->set;
    else if (paramSetChoice == SELECT_WS) modelParameters[tag].activeS = callback_data->set;
    else if (paramSetChoice == SELECT_WV) modelParameters[tag].activeV = callback_data->set;
    break;

  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;

  default:
    break;

  }
}

static void std_callback(Widget w, XtPointer cData, XtPointer cbDataGen);

static void create_std_adb() {

  Pixmap square, empty, set, trigger;
  unsigned int width  = BITMAP_WIDTH;
  unsigned int height = BITMAP_HEIGHT;
  int j, k, l, top, left;
  XmString csString;
  static Widget frame, *labels, buttonK, buttonS;
  const char *headings[] = { "H", "S", "F", "K'", "K''", "K'''" };

  frame = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, preclb_adb, 
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition,   BOTTOM_COMP,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  LEFT_STD,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL); 
  std_adb = XtVaCreateWidget("Form", xmFormWidgetClass, frame, NULL);

  /* make labels */
  labels  = (Widget *) XtMalloc( (unsigned) (nls+6+nc+1)*sizeof(Widget) );
  
  top  = 9;
  left =  4;
  for (j=0; j<nls; j++) {
    size_t lenA = strcspn(liquid[j].label, " ");
    size_t lenB = strcspn(liquid[j].label, ")")+1;
    size_t len  = (lenA < lenB) ? lenA : lenB;
    char *temp = (char *) malloc((size_t) (len+1)*sizeof(char));
    temp = strncpy(temp, liquid[j].label, len); temp[len] = '\0';
    csString = XmStringCreateLtoR(temp, "ISO8859-1");
    free(temp);
    labels[j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, std_adb,
      XmNlabelString,    csString,
      XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
      XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
      NULL);
    XmStringFree(csString);
    top = top + 3;
  }

  top  = 9;
  left = 50;
  for (j=0; j<=nc; j++) {
    size_t len = strcspn(bulkSystem[j].label, " ");
    char *temp = (char *) malloc((size_t) (len+1)*sizeof(char));
    temp = strncpy(temp, bulkSystem[j].label, len); temp[len] = '\0';
    csString = XmStringCreateLtoR(temp, "ISO8859-1");
    free(temp);
    labels[nls+j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, std_adb,
      XmNlabelString,    csString,
      XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
      XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
      NULL);
    XmStringFree(csString);
    top = top + 3;
  }

  /* make toggle button entries to fill in the matrix */
  stdSetToggles = (Widget  *) XtMalloc( (unsigned) (3*nls+3*(nc+1))*sizeof(Widget) );
  empty = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
            bits, width, height, white, white, DefaultDepthOfScreen(XtScreen(topLevel)));
  set   = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
            bits, width, height, black, black, DefaultDepthOfScreen(XtScreen(topLevel)));

  left = 25;
  for (j=0; j<3; j++) {
    top = 5;
    csString = XmStringCreateLtoR((char *) headings[j], "ISO8859-1");
    labels[nls+nc+j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, std_adb,
      XmNlabelString,    csString,
      XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
      XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
      NULL);
    XmStringFree(csString);
    
    top = 9;
    for (k=0; k<nls; k++) {
      l = j*nls + k;
      
      if      ((j == 0) && (modelParameters[nls*(nls-1)/2+k].enthalpy != 0.0)) trigger = set;
      else if ((j == 1) && (modelParameters[nls*(nls-1)/2+k].entropy  != 0.0)) trigger = set;
      else if ((j == 3) && (modelParameters[nls*(nls-1)/2+k].volume   != 0.0)) trigger = set;
      else trigger = empty;

      square = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
                 bits, width, height, red, white, DefaultDepthOfScreen(XtScreen(topLevel)));
      stdSetToggles[l] = XtVaCreateManagedWidget("Toggle", xmToggleButtonWidgetClass, std_adb,
        XmNindicatorOn,    False,
        XmNlabelType,      XmPIXMAP,
        XmNvisibleWhenOff, True,
        XmNlabelPixmap,    trigger,
        XmNselectPixmap,   square,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
        NULL);
      {
      long longTag = (long) l;
      XtAddCallback(stdSetToggles[l], XmNvalueChangedCallback, std_callback, (XtPointer) longTag);
      }
      if      (j == 0) XmToggleButtonSetState(stdSetToggles[l], modelParameters[nls*(nls-1)/2+k].activeH, False);
      else if (j == 1) XmToggleButtonSetState(stdSetToggles[l], modelParameters[nls*(nls-1)/2+k].activeS, False);
      else if (j == 2) XmToggleButtonSetState(stdSetToggles[l], modelParameters[nls*(nls-1)/2+k].activeF, False);
      else if (j == 3) XmToggleButtonSetState(stdSetToggles[l], modelParameters[nls*(nls-1)/2+k].activeV, False);
      top = top + 3;
    }
    left = left + 7;
  }      

  left = 70;
  for (j=0; j<3; j++) {
    top = 5;
    csString = XmStringCreateLtoR((char *) headings[j+3], "ISO8859-1");
    labels[nls+nc+1+j+3] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, std_adb,
      XmNlabelString,    csString,
      XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
      XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
      NULL);
    XmStringFree(csString);
    
    top = 9;
    for (k=0; k<=nc; k++) {
      l = 3*nls + j*(nc+1) + k;
      square = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
                 bits, width, height, red, white, DefaultDepthOfScreen(XtScreen(topLevel)));
      stdSetToggles[l] = XtVaCreateManagedWidget("Toggle", xmToggleButtonWidgetClass, std_adb,
        XmNindicatorOn,    False,
        XmNlabelType,      XmPIXMAP,
        XmNvisibleWhenOff, True,
        XmNlabelPixmap,    empty,
        XmNselectPixmap,   square,
        XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  top,
        XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, left,
        NULL);
      {
      long longTag = (long) l;
      XtAddCallback(stdSetToggles[l], XmNvalueChangedCallback, std_callback, (XtPointer) longTag);
      }
      if      (j == 0) XmToggleButtonSetState(stdSetToggles[l], eosModelParameters[k].activeKp,   False);
      else if (j == 1) XmToggleButtonSetState(stdSetToggles[l], eosModelParameters[k].activeKpp,  False);
      else if (j == 2) XmToggleButtonSetState(stdSetToggles[l], eosModelParameters[k].activeKppp, False);
      top = top + 3;
    }
    left = left + 10;
  }      

  /* Create Parameter clear button */
  csString = XmStringCreateLtoR("ClearS", "ISO8859-1");
  buttonS = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, std_adb, 
    XmNlabelString,      csString,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition,  35,
    NULL);
  {
  long longTag = (long) k_preclb_bt_clearS;
  XtAddCallback(buttonS, XmNactivateCallback, preclb_bt_callback, (XtPointer) longTag);
  }
  XmStringFree(csString);

  /* Create Parameter clear button */
  csString = XmStringCreateLtoR("ClearK", "ISO8859-1");
  buttonK = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, std_adb, 
    XmNlabelString,      csString,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition,  85,
    NULL);
  {
  long longTag = (long) k_preclb_bt_clearK;
  XtAddCallback(buttonK, XmNactivateCallback, preclb_bt_callback, (XtPointer) longTag);
  }
  XmStringFree(csString);

  XtManageChild(std_adb);
}

static void std_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmToggleButtonCallbackStruct *callback_data = (XmToggleButtonCallbackStruct *) cbDataGen;

  switch (callback_data->reason) {

  case XmCR_VALUE_CHANGED :
    if      (tag < nls)   modelParameters[nls*(nls-1)/2 + tag        ].activeH   = callback_data->set;
    else if (tag < 2*nls) modelParameters[nls*(nls-1)/2 + tag -   nls].activeS   = callback_data->set;
    else if (tag < 3*nls) modelParameters[nls*(nls-1)/2 + tag - 2*nls].activeF   = callback_data->set;
    else if (tag < 3*nls+  (nc+1)) eosModelParameters[tag - 3*nls           ].activeKp   = callback_data->set;
    else if (tag < 3*nls+2*(nc+1)) eosModelParameters[tag - 3*nls -   (nc+1)].activeKpp  = callback_data->set;
    else if (tag < 3*nls+3*(nc+1)) eosModelParameters[tag - 3*nls - 2*(nc+1)].activeKppp = callback_data->set;
    break;

  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;

  default:
    break;

  }
}

/*
 *==============================================================================
 * Create MRQRDT region
 */

static void create_mrqrdt_adb() {

  int j;
  XmString csString;

  typedef struct _pubLabels {
    int        left;      /* left relative coordinate */
    int        top;       /* top relative coordinate  */
    const char *label;    /* default label            */
  } PubLabels;
  static PubLabels pubLabels[10] = {
    { 15, 17, "------"        } , /* iters          */  
    { 15, 34, "------"        } , /* funcs          */  
    { 15, 51, "------"        } , /* params         */  
    { 15, 69, "------"        } , /* rank           */
    { 15, 86, "------"        } , /* n Eqn          */
    
    { 45, 34, "--------------------" } , /* max sing value */  
    { 45, 51, "--------------------" } , /* min sing value */  
    { 45, 69, "--------------------" } , /* cut sing value */
    
    { 45, 17, "--------------------" } , /* chi sqr        */
    { 78, 17, "--------------------" }   /* lambda         */
  };

  typedef struct _privLabels {
    const char *label; /* label of widget          */
    Widget     name;   /* Widget ID of the labels  */ 
    int        left;   /* left relative coordinate */
    int        top;    /* top relative coordinate  */
  } PrivLabels;
  static PrivLabels privLabels[11] = {
    { "MRQRDT results"   , (Widget) NULL,  5,  2 } , 
    { "iters"            , (Widget) NULL,  5, 17 } ,
    { "funcs"            , (Widget) NULL,  5, 34 } , 
    { "params"           , (Widget) NULL,  5, 51 } ,
    { "rank"             , (Widget) NULL,  5, 69 } ,
    { "n Eqn"            , (Widget) NULL,  5, 86 } ,

    { "max sing value"   , (Widget) NULL, 30, 34 } ,
    { "min sing value"   , (Widget) NULL, 30, 51 } ,
    { "cutoff value"     , (Widget) NULL, 30, 69 } ,

    { "chi sqr"          , (Widget) NULL, 30, 17 } ,
    { "lambda"           , (Widget) NULL, 68, 17 }

  };

  static Widget frame; 

  mrqrdtADB = (Widget *) XtMalloc( (unsigned) 11*sizeof(Widget));

  frame = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, preclb_adb, 
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition,    TOP_MRQRDT,
    XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, TOP_PHASE,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, LEFT_COMP,
    NULL);
  mrqrdt_adb = XtVaCreateWidget("Form", xmFormWidgetClass, frame, NULL);

  for (j=0; j<11; j++) {
    csString = XmStringCreateLtoR((char *) privLabels[j].label, "ISO8859-1");
    privLabels[j].name = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, mrqrdt_adb, 
      XmNlabelString,    csString,
      XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  privLabels[j].top,
      XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, privLabels[j].left,
      NULL);
    XmStringFree(csString);
  }

  for (j=0; j<10; j++) {
    csString = XmStringCreateLtoR((char *) pubLabels[j].label, "ISO8859-1");
    mrqrdtADB[j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, mrqrdt_adb, 
      XmNlabelString,    csString,
      XmNrecomputeSize,  False,
      XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition,  pubLabels[j].top,
      XmNleftAttachment, XmATTACH_POSITION, XmNleftPosition, pubLabels[j].left,
      NULL);
    XmStringFree(csString);
  }

  csString = XmStringCreateLtoR("Exit Marquardt loop on next Execute", "ISO8859-1");
  mrqrdtADB[10] = XtVaCreateManagedWidget("Toggle", xmToggleButtonGadgetClass, mrqrdt_adb, 
    XmNlabelString,      csString, 
    XmNbottomAttachment, XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    XmNindicatorOn,      True, 
    NULL);
  XmStringFree(csString);

  XtManageChild(mrqrdt_adb);
}

static void preclb_bt_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmPushButtonCallbackStruct *callback_data = (XmPushButtonCallbackStruct *) cbDataGen;
  int j, k, l;

  switch (callback_data->reason) {

  case XmCR_ACTIVATE :
    if (tag == k_preclb_bt_select) {
      XmString csString = NULL;
      if        (paramSetChoice == SELECT_WH) {
        csString = XmStringCreateLtoR("Select WS", "ISO8859-1");
        for (j=0, l=0; j<nls; j++) for (k=j+1; k<nls; k++, l++) XmToggleButtonSetState(paramSetToggles[l], modelParameters[l].activeS, False);
        paramSetChoice = SELECT_WS;
      } else if (paramSetChoice == SELECT_WS) {
        csString = XmStringCreateLtoR("Select WV", "ISO8859-1");
        for (j=0, l=0; j<nls; j++) for (k=j+1; k<nls; k++, l++) XmToggleButtonSetState(paramSetToggles[l], modelParameters[l].activeV, False);
        paramSetChoice = SELECT_WV;
      } else if (paramSetChoice == SELECT_WV) {
        csString = XmStringCreateLtoR("Select WH", "ISO8859-1");
        for (j=0, l=0; j<nls; j++) for (k=j+1; k<nls; k++, l++) XmToggleButtonSetState(paramSetToggles[l], modelParameters[l].activeH, False);
        paramSetChoice = SELECT_WH;
      }
      XtVaSetValues(w, XmNlabelString, csString, NULL);
      XmStringFree(csString);
    } else if (tag == k_preclb_bt_clearW) {
      for (j=0, l=0; j<nls; j++) for (k=j+1; k<nls; k++, l++) {
        XmToggleButtonSetState(paramSetToggles[l], False, False);
        if      (paramSetChoice == SELECT_WH) modelParameters[l].activeH = False;
        else if (paramSetChoice == SELECT_WS) modelParameters[l].activeS = False;
        else if (paramSetChoice == SELECT_WV) modelParameters[l].activeV = False;
      }
    } else if (tag == k_preclb_bt_clearK) {
      for (j=0; j<(nc+1); j++) {
        XmToggleButtonSetState(stdSetToggles[3*nls	   +j], False, False);
        XmToggleButtonSetState(stdSetToggles[3*nls+  (nc+1)+j], False, False);
        XmToggleButtonSetState(stdSetToggles[3*nls+2*(nc+1)+j], False, False);
        eosModelParameters[j].activeKp   = FALSE;
        eosModelParameters[j].activeKpp  = FALSE;
        eosModelParameters[j].activeKppp = FALSE;
      }
    } else if (tag == k_preclb_bt_clearS) {
      for (j=0; j<nls; j++) {
        XmToggleButtonSetState(stdSetToggles[	   j], False, False);
        XmToggleButtonSetState(stdSetToggles[  nls+j], False, False);
        XmToggleButtonSetState(stdSetToggles[2*nls+j], False, False);
        modelParameters[nls*(nls-1)/2+j].activeH = FALSE;
        modelParameters[nls*(nls-1)/2+j].activeS = FALSE;
        modelParameters[nls*(nls-1)/2+j].activeF = FALSE;
      }
    } else if (tag == k_preclb_bt_clearM) {
      for (j=0; j<npc; j++) if (solids[j].inclInClb) {
        XmToggleButtonSetState(hTogglesMin[j], False, False);
        XmToggleButtonSetState(sTogglesMin[j], False, False);
        XmToggleButtonSetState(vTogglesMin[j], False, False);
        modelParameters[nls*(nls-1)/2+nls+j].activeH = FALSE;
        modelParameters[nls*(nls-1)/2+nls+j].activeS = FALSE;
        modelParameters[nls*(nls-1)/2+nls+j].activeV = FALSE;
      }
    }
    break;

  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;

  default:
    break;
  }
}

/* end of file CREATE_PRECLB.C */
