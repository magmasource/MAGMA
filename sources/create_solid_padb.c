const char *create_solid_padb_ver(void) { return "$Id: create_solid_padb.c,v 1.2 2006/08/17 16:47:18 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: create_solid_padb.c,v $
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
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
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
 * Revision 3.5  1997/05/03  20:23:39  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:43  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:33:45  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/11/23  22:37:42  ghiorso
 * Final implementation of subsolidus fO2 buffering.
 *
 * Revision 3.2  1995/11/23  22:37:42  ghiorso
 * Final implementation of subsolidus fO2 buffering.
 *
 * Revision 3.1  1995/08/18  17:26:27  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Function to create the pop up dialog box for entering
**        included solids for the silmin interface
**
**      Defines callback routines for all children
**      (file: CREATE_SOLID_PADB.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  September 7, 1990   Original Version
**      V1.0-2  Mark S. Ghiorso  August 30, 1991
**              Added globally known widget definitions
**      V1.1-1  Mark S. Ghiorso  September 1, 1991
**              Eliminated phase-order specific logic, generalized
**              includedSolids structure and automated positioning
**              of toggles and buttons
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  November 30, 1991
**              Reorganization and enhancements
**      V3.0-1  Mark S. Ghiorso  December 7, 1991
**              Reorganization according to Motif Style Guide/ addition of
**              paned window and removal of frame widget
**      V3.0-2  Mark S. Ghiorso  March 27, 1992
**              Corrected casting violations in callback routines
**      V3.0-3  Mark S. Ghiorso  March 12, 1994
**              Added include of ToggleB.h to get set and get functions
**      V3.0-4  Mark S. Ghiorso  April 23, 1994
**              Corrected casting violations in callback structures
**--
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Xm/Form.h>
#include <Xm/Label.h>
#include <Xm/PanedW.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/SashP.h>     /* We need to stop keyboard traversal on the sashes */
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>

#include "interface.h"            /*Specific external declarations          */
#include "silmin.h"               /*Get silmin solid structures             */

/******************************************************************************
 * Globally known widgets declared extern in INTERFACE.H
 ******************************************************************************/

Widget solid_padb;

IncludedSolids *includedSolids;

#define COLS 9 /* Number of columns in the display */

static void button_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void toggle_callback(Widget w, XtPointer cData, XtPointer cbDataGen);

static const long SOLID_STANDARD_SET   = 1;
static const long SOLID_NO_SOLID_SOLNS = 2;
static const long SOLID_RESET_ALL      = 3;

void create_solid_padb()
{
  int j, k;
  Dimension h;
  static Widget button[5], form, label, pane, rowcol;

  /* pop up form dialog box */
  { 
    Arg args[] = { { XmNdialogStyle,     XmDIALOG_FULL_APPLICATION_MODAL },
                   { XmNdefaultPosition, True                            },
                   { XmNautoUnmanage,    False                           } };
    solid_padb = XmCreateFormDialog(silmin_adb, "FormDialog", args, 
      XtNumber(args));
    XtVaSetValues(XtParent(solid_padb), 
      XmNdeleteResponse, XmUNMAP, XmNtitle, "Solid Phases",
      NULL);
  }

  /* pane window to hold everything */
  pane = XtVaCreateWidget("Pane", xmPanedWindowWidgetClass, solid_padb,
    XmNsashWidth,        1,
    XmNsashHeight,       1,
    XmNtopAttachment,    XmATTACH_FORM, 
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM, 
    XmNrightAttachment,  XmATTACH_FORM,
    NULL); 

  /* label for top cell of pane */
  label = XtVaCreateManagedWidget("Label", xmLabelWidgetClass, pane, 
    XtVaTypedArg, XmNlabelString, XmRString, 
    "Checked phases will be allowed to precipitate from the liquid.", 
    strlen("Checked phases will be allowed to precipitate from the liquid.")+1,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    NULL); 

  XtVaGetValues(label, XmNheight, &h, NULL);
  XtVaSetValues(label, XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);

  for (j=0, k=0; j<npc; j++) if (solids[j].type == PHASE) k++;
  k++; /* additional entry for melt */
  includedSolids = (IncludedSolids *)
                   malloc((unsigned) k*sizeof(IncludedSolids));

  /* Container for the toggle buttons (middle cell of pane) */
  rowcol = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, pane,
    XmNpacking,          XmPACK_COLUMN,
    XmNorientation,      XmVERTICAL,
    XmNnumColumns,       COLS,
    NULL); 

  /* toggle buttons */
  for (j=0, k=0; j<npc; j++) {
    if (solids[j].type == PHASE) {
      includedSolids[k].name = XtVaCreateManagedWidget(
        "ToggleButton", xmToggleButtonGadgetClass, rowcol, 
        XtVaTypedArg, XmNlabelString, XmRString, solids[j].label, 
          strlen(solids[j].label)+1,
        XmNindicatorType,  XmONE_OF_MANY,
        XmNsensitive,      (solids[j].nr == 0 || 
          (solids[j].nr > 0 && solids[j].convert != NULL)) ? True : False,
        NULL);
      {
      long longTag = (long) k;
      XtAddCallback(includedSolids[k].name, XmNvalueChangedCallback, toggle_callback, (XtPointer) longTag);
      }
      if ( solids[j].nr == 0 || 
           (solids[j].nr > 0 && solids[j].convert != NULL) ) 
        XmToggleButtonSetState(includedSolids[k].name, True, False);
      k++;
    }
  }
  /* additional entry for the melt */
  includedSolids[k].name = XtVaCreateManagedWidget(
    "ToggleButton", xmToggleButtonGadgetClass, rowcol,
    XtVaTypedArg, XmNlabelString, XmRString, "melt", strlen("melt")+1,
    XmNindicatorType,  XmONE_OF_MANY,
    XmNsensitive,      True,
    NULL);
  {
  long longTag = (long) k;
  XtAddCallback(includedSolids[k].name, XmNvalueChangedCallback, toggle_callback, (XtPointer) longTag);
  }
  XmToggleButtonSetState(includedSolids[k].name, True, False);

  XtManageChild(rowcol);

  /* action area buttons (lower most cell of pane) */
  form = XtVaCreateWidget("Form", xmFormWidgetClass, pane, 
    XmNfractionBase, 11,
    NULL);

  button[0] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form, 
    XtVaTypedArg, XmNlabelString, XmRString, "Done", strlen("Done")+1,
    XmNshowAsDefault,    True,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  1,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 2,
    NULL);
  XtAddCallback(button[0], XmNactivateCallback, button_callback, (XtPointer) XmCR_ACTIVATE); 
  button[1] = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, form, 					     
    XtVaTypedArg, XmNlabelString, XmRString, "Std Set", strlen("Std Set")+1,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  3,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 4,
    NULL);
  XtAddCallback(button[1], XmNactivateCallback, button_callback, (XtPointer) SOLID_STANDARD_SET);
  button[2] = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, form, 
    XtVaTypedArg, XmNlabelString, XmRString, "No Solid Solns", strlen("No Solid Solns")+1,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  5,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 6,
    NULL);
  XtAddCallback(button[2], XmNactivateCallback, button_callback, (XtPointer) SOLID_NO_SOLID_SOLNS);
  button[3] = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, form, 
    XtVaTypedArg, XmNlabelString, XmRString, "All Solids", strlen("All Solids")+1,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  7,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 8,
    NULL);
  XtAddCallback(button[3], XmNactivateCallback, button_callback, (XtPointer) SOLID_RESET_ALL);
  button[4] = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, form, 
    XtVaTypedArg, XmNlabelString, XmRString, "Help", strlen("Help")+1,
    XmNsensitive,        False,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,   9,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 10,
    NULL);
  XtAddCallback(button[4], XmNactivateCallback, button_callback, (XtPointer) XmCR_HELP);

  XtManageChild(form);
  XtVaGetValues(button[0], XmNheight, &h, NULL);
  XtVaSetValues(form, XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);

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

}

static void button_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmPushButtonCallbackStruct *cbData = (XmPushButtonCallbackStruct *) cbDataGen;
  int j, k;

  switch (cbData->reason) {

  case XmCR_ACTIVATE :
    if        (tag == XmCR_ACTIVATE) {
      XtUnmanageChild(solid_padb);

    } else if (tag == SOLID_STANDARD_SET) {
      for (j=0, k=0; j<npc; j++) if (solids[j].type == PHASE) {
        if (solids[j].inStdSet && (solids[j].nr == 0 || (solids[j].nr > 0 && solids[j].convert != NULL))) 
	     XmToggleButtonSetState(includedSolids[k].name, True, False);
	else XmToggleButtonSetState(includedSolids[k].name, False, False);
        k++;
      }
      XmToggleButtonSetState(includedSolids[k].name, True, False);

    } else if (tag == SOLID_NO_SOLID_SOLNS) {
      for (j=0, k=0; j<npc; j++) if (solids[j].type == PHASE) {
        if (solids[j].nr == 0) XmToggleButtonSetState(includedSolids[k].name, True, False);
	else                   XmToggleButtonSetState(includedSolids[k].name, False, False);
        k++;
      }
      XmToggleButtonSetState(includedSolids[k].name, True, False);

    } else if (tag == SOLID_RESET_ALL) {
      for (j=0, k=0; j<npc; j++) if (solids[j].type == PHASE) {
        if (solids[j].nr == 0 || (solids[j].nr > 0 && solids[j].convert != NULL)) 
	  XmToggleButtonSetState(includedSolids[k].name, True, False);
        k++;
      }
      XmToggleButtonSetState(includedSolids[k].name, True, False);
      
    } else if (tag == XmCR_HELP) ;
      
    break;

  case XmCR_HELP :
    break;

  default:
    break;

  }
}

static void toggle_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  XmToggleButtonCallbackStruct *cbData = 
    (XmToggleButtonCallbackStruct *) cbDataGen;
  switch (cbData->reason) {

  case XmCR_VALUE_CHANGED :
    if (cbData->event != NULL && cbData->event->type == KeyPress)
      (void) XmProcessTraversal(w, XmTRAVERSE_NEXT);
    break;
  case XmCR_HELP :
    break;
  default:
    break;
  }
}


/* end of file CREATE_SOLID_PADB.C */
