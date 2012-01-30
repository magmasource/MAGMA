const char *create_tp_padb_ver(void) { return "$Id: create_tp_padb.c,v 1.2 2006/08/17 16:47:18 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: create_tp_padb.c,v $
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
 * Revision 3.6  1997/06/21  22:50:00  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:23:39  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:42  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:33:45  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  17:27:02  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  17:27:02  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Function to create the pop up attached dialog box for entering
**        T and P for the silmin interface
**
**      Defines callback routines for all children
**      (file: CREATE_TP_PADB.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  September 6, 1990   Original Version
**      V1.0-2  Mark S. Ghiorso  August 30, 1991
**              Added globally known widget declarations
**      V1.1-0  Mark S. Ghiorso  September 3, 1991
**              Reorganized global structure tpValues and added global
**              macros to interface.h that point to elements in the
**              array of structures
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V3.0-1  Mark S. Ghiorso  December 7, 1991
**              Reorganization according to Motif Style Guide/ addition of
**              paned window and removal of frame widget
**      V3.0-2  Mark S. Ghiorso  December 14, 1991
**              (1) Added callback for mapping of dialog box to reset
**                  values of text widgets
**              (2) Added global static text field widget array
**      V3.0-3  Mark S. Ghiorso  January 10, 1992
**              Changed button_callback() to invoke "compute" calculations
**              when dialog is unmanaged
**      V3.0-4  Mark S. Ghiorso  March 27, 1992
**              Corrected casting violations in callback procs
**      V3.0-5  Mark S. Ghiorso  April 23, 1992
**              Corrected errors in text_callback algorithm
**      V3.0-6  Mark S. Ghiorso  September 28, 1992
**              Corrected calls to XtFree() => free() for allocations made
**              with malloc()
**      V3.0-7  Mark S. Ghiorso  September 29, 1992
**              Converted TextField to Text widgets as a bug workaround 
**              for DECWindows Motif V 1.1
**      V3.0-8  Mark S. Ghiorso  April 23, 1994
**              Corrected casting violations for callback structures
**      V4.0-1  Mark S. Ghiorso  June 14, 1994
**              (1) Added new entries for enthalpy, entropy and volume 
**                  constraints
**                               June 15, 1994
**              (2) Finished
**
**--
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Xm/Form.h>
#include <Xm/LabelG.h>
#include <Xm/PanedW.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/SashP.h>     /* We need to stop keyboard traversal on the sashes */
#include <Xm/Text.h>
#include <Xm/ToggleBG.h>

#include "interface.h"            /*Specific external declarations          */
#include "silmin.h"               /*Global SILMIN declarations              */

/******************************************************************************
 * Globally known widgets declared extern in INTERFACE.H
 ******************************************************************************/

Widget   tp_padb;
TpValues *tpValues;

#define CHAR_LENGTH  8  /* Maximum number of characters in text widget */
#define COL_ONE      3  /* Number of public entries in column one      */
#define COL_TWO      4  /* Number of public entries in column two      */
#define COL_THREE    2  /* Number of public entries in column two      */
#define COL_FOUR     2  /* Number of public entries in column two      */
#define COL_FIVE     2  /* Number of public entries in column two      */
#define ENTRIES      (COL_ONE + COL_TWO + COL_THREE + COL_FOUR + COL_FIVE)

static void map_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void button_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void text_callback(Widget w, XtPointer cData, XtPointer cbDataGen);

static Widget *textF;

void create_tp_padb()
{
  int j;
  Dimension h, hSum, w, wSum;
  static Widget button[3], labels[5], form[3], pane, rowcol[5];

  static struct _tpLabels {
    const char *label;                   /* name of label widget (displayed) */
    Widget     name;                     /* label widget ID                  */
  } tpLabels[ENTRIES] = { 
    { "Start:" }, { "Stop:"  }, { "Inc:"   },                /* Column one   */
    { "Start:" }, { "Stop:"  }, { "Inc:"   }, { "dP/dT:" },  /* Column two   */
    { "Inc:"   }, { "dP/dH:" },                              /* Column three */
    { "Inc:"   }, { "dP/dS:" },                              /* Column four  */
    { "Inc:"   }, { "dT/dV:" }                               /* Column five  */
  };
  tpValues = (TpValues *) calloc((unsigned) ENTRIES, sizeof(TpValues));
  textF    = (Widget *)   malloc((unsigned) ENTRIES*sizeof(Widget));

  /* pop up form dialog box */
  {
    Arg args[] = { { XmNdialogStyle,     XmDIALOG_FULL_APPLICATION_MODAL },
                   { XmNdefaultPosition, True                            },
                   { XmNautoUnmanage,    False                           } };
    tp_padb = XmCreateFormDialog(silmin_adb, "FormDialog", args, 
      XtNumber(args));
    XtAddCallback(tp_padb, XmNmapCallback, map_callback, NULL);
    XtVaSetValues(XtParent(tp_padb), 
      XmNdeleteResponse, XmUNMAP, XmNtitle, 
        "Temperature, Pressure, Enthalpy, Entropy, and Volume",
      NULL);
  }

  /* pane window to hold everything */
  pane = XtVaCreateWidget("Pane", xmPanedWindowWidgetClass, tp_padb,
    XmNsashWidth,        1,
    XmNsashHeight,       1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  /* top cell of the pane window */
  form[0] = XtVaCreateWidget("Form", xmFormWidgetClass, pane, NULL);

  /* Label for the first column */
  labels[0] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "Temperature (C):",
      strlen("Temperature (C):")+1,
    XmNalignment,        XmALIGNMENT_BEGINNING,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_NONE,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 20,
    NULL);
  /* Label for the second column */
  labels[1] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "Pressure (bars):", 
      strlen("Pressure (bars):")+1,
    XmNalignment,        XmALIGNMENT_BEGINNING,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_NONE,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 40,
    NULL);
  /* Label for the second column */
  labels[2] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "Enthalpy (J):", 
    strlen("Enthalpy (J):")+1,
    XmNalignment,        XmALIGNMENT_BEGINNING,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_NONE,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 60,
    NULL);
  /* Label for the second column */
  labels[3] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "Entropy (J/K):", 
    strlen("Entropy (J/K):")+1,
    XmNalignment,        XmALIGNMENT_BEGINNING,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_NONE,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 80,
    NULL);
  /* Label for the second column */
  labels[4] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "Volume (cc):", 
    strlen("Volume (cc):")+1,
    XmNalignment,        XmALIGNMENT_BEGINNING,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_NONE,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  XtManageChild(form[0]);
  XtVaGetValues(labels[0], XmNheight, &h, NULL);
  XtVaSetValues(form[0],   XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);

  /* middle cell of the pane window */
  form[1] = XtVaCreateWidget("Form", xmFormWidgetClass, pane, NULL);

  rowcol[0] = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form[1],
    XmNpacking,          XmPACK_COLUMN,
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       COL_ONE,
    XmNisAligned,        True,
    XmNentryAlignment,   XmALIGNMENT_END,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_NONE,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 20,
    NULL);

  /* Label, text entry widgets for the first column. Number = COL_ONE */
  for (j=0; j<COL_ONE; j++) {
    tpLabels[j].name = XtVaCreateManagedWidget(
      "Label", xmLabelGadgetClass, rowcol[0],
      XtVaTypedArg, XmNlabelString, XmRString, tpLabels[j].label,
        strlen(tpLabels[j].label)+1,
      NULL); 
    textF[j] = XtVaCreateManagedWidget(
      "Text", xmTextWidgetClass, rowcol[0],
#ifdef WHITE_TEXTW
      XmNbackground,       white,
#endif
      XmNcolumns,          CHAR_LENGTH,
      XmNmaxLength,        CHAR_LENGTH,
      XmNnavigationType,   XmNONE,
      XmNtraversalOn,      True,
      NULL);
    {
    long longTag = (long) ((j == (COL_ONE-1)) ? XmTRAVERSE_NEXT_TAB_GROUP : XmTRAVERSE_NEXT);
    XtAddCallback(textF[j], XmNactivateCallback, (XtCallbackProc) XmProcessTraversal, (XtPointer) longTag);
    longTag = (long) j;
    XtAddCallback(textF[j], XmNlosingFocusCallback,  text_callback, (XtPointer) longTag);
    XtAddCallback(textF[j], XmNmodifyVerifyCallback, text_callback, (XtPointer) longTag);
    XtAddCallback(textF[j], XmNvalueChangedCallback, text_callback, (XtPointer) longTag);
    }
  }

  XtManageChild(rowcol[0]);

  rowcol[1] = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form[1],
    XmNpacking,          XmPACK_COLUMN,
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       COL_TWO,
    XmNisAligned,        True,
    XmNentryAlignment,   XmALIGNMENT_END,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  20,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 40,
    NULL);

  /* Label, text entry widgets for the second column. Number = COL_TWO */
  for (j=COL_ONE; j<(COL_ONE+COL_TWO); j++) {
    tpLabels[j].name = XtVaCreateManagedWidget(
      "Label", xmLabelGadgetClass, rowcol[1],
      XtVaTypedArg, XmNlabelString, XmRString, tpLabels[j].label,
        strlen(tpLabels[j].label)+1,
      NULL); 
    textF[j] = XtVaCreateManagedWidget(
      "Text", xmTextWidgetClass, rowcol[1],
#ifdef WHITE_TEXTW
      XmNbackground,       white,
#endif
      XmNcolumns,          CHAR_LENGTH,
      XmNmaxLength,        CHAR_LENGTH,
      XmNnavigationType,   XmNONE,
      XmNtraversalOn,      True,
      NULL);
    {
    long longTag = (long) ((j == (COL_ONE+COL_TWO-1)) ? XmTRAVERSE_NEXT_TAB_GROUP : XmTRAVERSE_NEXT);
    XtAddCallback(textF[j], XmNactivateCallback, (XtCallbackProc) XmProcessTraversal, (XtPointer) longTag);
    longTag = (long) j;
    XtAddCallback(textF[j], XmNlosingFocusCallback,  text_callback, (XtPointer) longTag);
    XtAddCallback(textF[j], XmNmodifyVerifyCallback, text_callback, (XtPointer) longTag);
    XtAddCallback(textF[j], XmNvalueChangedCallback, text_callback, (XtPointer) longTag);
    }
  }

  XtManageChild(rowcol[1]);

  rowcol[2] = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form[1],
    XmNpacking,          XmPACK_COLUMN,
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       COL_THREE,
    XmNisAligned,        True,
    XmNentryAlignment,   XmALIGNMENT_END,
    XmNtopAttachment,    XmATTACH_NONE,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  40,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 60,
    NULL);

  /* Label, text entry widgets for the third column. Number = COL_THREE */
  for (j=(COL_ONE+COL_TWO); j<(COL_ONE+COL_TWO+COL_THREE); j++) {
    tpLabels[j].name = XtVaCreateManagedWidget(
      "Label", xmLabelGadgetClass, rowcol[2],
      XtVaTypedArg, XmNlabelString, XmRString, tpLabels[j].label,
        strlen(tpLabels[j].label)+1,
      NULL); 
    textF[j] = XtVaCreateManagedWidget(
      "Text", xmTextWidgetClass, rowcol[2],
#ifdef WHITE_TEXTW
      XmNbackground,       white,
#endif
      XmNcolumns,          CHAR_LENGTH,
      XmNmaxLength,        CHAR_LENGTH,
      XmNnavigationType,   XmNONE,
      XmNtraversalOn,      True,
      NULL);
    {
    long longTag = (long) ((j == (COL_ONE+COL_TWO+COL_THREE-1)) ? XmTRAVERSE_NEXT_TAB_GROUP : XmTRAVERSE_NEXT);
    XtAddCallback(textF[j], XmNactivateCallback, (XtCallbackProc) XmProcessTraversal, (XtPointer) longTag);
    longTag = (long) j;
    XtAddCallback(textF[j], XmNlosingFocusCallback,  text_callback, (XtPointer) longTag);
    XtAddCallback(textF[j], XmNmodifyVerifyCallback, text_callback, (XtPointer) longTag);
    XtAddCallback(textF[j], XmNvalueChangedCallback, text_callback, (XtPointer) longTag);
    }
  }

  XtManageChild(rowcol[2]);

  rowcol[3] = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form[1],
    XmNpacking,          XmPACK_COLUMN,
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       COL_FOUR,
    XmNisAligned,        True,
    XmNentryAlignment,   XmALIGNMENT_END,
    XmNtopAttachment,    XmATTACH_NONE,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  60,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 80,
    NULL);

  /* Label, text entry widgets for the fourth column. Number = COL_FOUR */
  for (j=(COL_ONE+COL_TWO+COL_THREE); j<(COL_ONE+COL_TWO+COL_THREE+COL_FOUR); 
    j++) {
    tpLabels[j].name = XtVaCreateManagedWidget(
      "Label", xmLabelGadgetClass, rowcol[3],
      XtVaTypedArg, XmNlabelString, XmRString, tpLabels[j].label,
        strlen(tpLabels[j].label)+1,
      NULL); 
    textF[j] = XtVaCreateManagedWidget(
      "Text", xmTextWidgetClass, rowcol[3],
#ifdef WHITE_TEXTW
      XmNbackground,       white,
#endif
      XmNcolumns,          CHAR_LENGTH,
      XmNmaxLength,        CHAR_LENGTH,
      XmNnavigationType,   XmNONE,
      XmNtraversalOn,      True,
      NULL);
    {
    long longTag = (long) ((j == (COL_ONE+COL_TWO+COL_THREE+COL_FOUR-1)) ? XmTRAVERSE_NEXT_TAB_GROUP : XmTRAVERSE_NEXT);
    XtAddCallback(textF[j], XmNactivateCallback, (XtCallbackProc) XmProcessTraversal, (XtPointer) longTag);
    longTag = (long) j;
    XtAddCallback(textF[j], XmNlosingFocusCallback,  text_callback, (XtPointer) longTag);
    XtAddCallback(textF[j], XmNmodifyVerifyCallback, text_callback, (XtPointer) longTag);
    XtAddCallback(textF[j], XmNvalueChangedCallback, text_callback, (XtPointer) longTag);
    }
  }

  XtManageChild(rowcol[3]);

  rowcol[4] = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form[1],
    XmNpacking,          XmPACK_COLUMN,
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       COL_FIVE,
    XmNisAligned,        True,
    XmNentryAlignment,   XmALIGNMENT_END,
    XmNtopAttachment,    XmATTACH_NONE,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition, 80,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  /* Label, text entry widgets for the fifth column. Number = COL_FIFTH */
  for (j=(COL_ONE+COL_TWO+COL_THREE+COL_FOUR); j<ENTRIES; j++) {
    tpLabels[j].name = XtVaCreateManagedWidget(
      "Label", xmLabelGadgetClass, rowcol[4],
      XtVaTypedArg, XmNlabelString, XmRString, tpLabels[j].label,
        strlen(tpLabels[j].label)+1,
      NULL); 
    textF[j] =  XtVaCreateManagedWidget(
      "Text", xmTextWidgetClass, rowcol[4],
#ifdef WHITE_TEXTW
      XmNbackground,       white,
#endif
      XmNcolumns,          CHAR_LENGTH,
      XmNmaxLength,        CHAR_LENGTH,
      XmNnavigationType,   XmNONE,
      XmNtraversalOn,      True,
      NULL);
    {
    long longTag = (long) ((j == (ENTRIES-1)) ? XmTRAVERSE_NEXT_TAB_GROUP : XmTRAVERSE_NEXT);
    XtAddCallback(textF[j], XmNactivateCallback, (XtCallbackProc) XmProcessTraversal, (XtPointer) longTag);
    longTag = (long) j;
    XtAddCallback(textF[j], XmNlosingFocusCallback,  text_callback, (XtPointer) longTag);
    XtAddCallback(textF[j], XmNmodifyVerifyCallback, text_callback, (XtPointer) longTag);
    XtAddCallback(textF[j], XmNvalueChangedCallback, text_callback, (XtPointer) longTag);
    }
  }

  XtManageChild(rowcol[4]);
  XtManageChild(form[1]);

#ifndef linux
#if (XmVersion > 1) || (XmUPDATE_LEVEL > 3)
  XtVaGetValues(rowcol[0], XmNwidth,  &w, NULL); wSum = w;
  XtVaGetValues(rowcol[0], XmNheight, &h, NULL); hSum = h;
  XtVaGetValues(textF[0],  XmNheight, &h, XmNwidth, &w, NULL);
  hSum += 4*h; wSum += 10*w;
  XtVaSetValues(form[1], XmNheight, hSum, XmNwidth, wSum, NULL);
#endif
#endif

  /* lower most cell of the pane window (action area) */
  form[2] = XtVaCreateWidget("Form", xmFormWidgetClass, pane, 
    XmNfractionBase, 7,
    NULL);

  button[0] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[2],
    XtVaTypedArg, XmNlabelString, XmRString, "Done", strlen("Done")+1,
    XmNshowAsDefault,    True,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  1,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 2,
    NULL);
  XtAddCallback(button[0], XmNactivateCallback, button_callback, 
    (XtPointer) XmCR_ACTIVATE);
  button[1] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[2],
    XtVaTypedArg, XmNlabelString, XmRString, "Compute", strlen("Compute")+1,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  3,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 4,
    NULL);
  XtAddCallback(button[1], XmNactivateCallback, button_callback, 
    (XtPointer) XmCR_APPLY);
  button[2] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[2],
    XtVaTypedArg, XmNlabelString, XmRString, "Help", strlen("Help")+1,
    XmNsensitive,        False,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  5,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 6,
    NULL);
  XtAddCallback(button[2], XmNactivateCallback, button_callback, 
    (XtPointer) XmCR_HELP);

  XtManageChild(form[2]);
  XtVaGetValues(button[0], XmNheight, &h, NULL);
  XtVaSetValues(form[2],   XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);

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

static void text_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmTextVerifyCallbackStruct *cbData = (XmTextVerifyCallbackStruct *) cbDataGen;
  char *number, *output;
  int len;

  switch (cbData->reason) {

  case XmCR_ACTIVATE :
    break;

  case XmCR_GAIN_PRIMARY :
    break;

  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;

  case XmCR_LOSE_PRIMARY :
    break;

  case XmCR_LOSING_FOCUS :
    number = XmTextGetString(w);
    if (atof(number) != 0.0) {
      double value = atof(number);
      output = (char *) malloc((unsigned) ((CHAR_LENGTH+1)*sizeof(char)));
      if      ((value < 99999.99) && (value > -9999.99) ) (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, value);
      else if ((value < 999999.9) && (value > -99999.9) ) (void) snprintf(output, CHAR_LENGTH+1, "%*.1f", CHAR_LENGTH, value);
      else if ((value < 9999999.) && (value > -999999.) ) (void) snprintf(output, CHAR_LENGTH+1, "%*.0f", CHAR_LENGTH, value);
      else                                                (void) snprintf(output, CHAR_LENGTH+1, "%*.0f", CHAR_LENGTH, 0.0);
    } else {
      output = (char *) malloc((unsigned) sizeof(char));
      output[0] = '\0';
    }
    XmTextSetString(w, output);
    free(output);
    XtFree(number);
    break;

  case XmCR_MODIFYING_TEXT_VALUE :
    if (cbData->event != (XEvent *) NULL &&      /* capture only user typing */
        cbData->startPos >= cbData->currInsert && cbData->text->length > 0) {
      if ((len = XmTextGetLastPosition(w)) == CHAR_LENGTH) cbData->doit = False;
      else {
        if (len + cbData->text->length > CHAR_LENGTH) {
          cbData->text->ptr[CHAR_LENGTH-len] = 0;
          cbData->text->length = strlen(cbData->text->ptr);
        }
        for (len=0; len<cbData->text->length; len++) {
          if (!isdigit(cbData->text->ptr[len]) &&
            cbData->text->ptr[len] != '.' && cbData->text->ptr[len] != ' ' &&
            cbData->text->ptr[len] != '-') {
            int j;
            for (j=len; (j+1)<cbData->text->length; j++)
              cbData->text->ptr[j] = cbData->text->ptr[j+1];
            cbData->text->length--;  len--;
          }
        }
        if (cbData->text->length == 0) cbData->doit = False;
      }
    }
    break;

  case XmCR_MOVING_INSERT_CURSOR :
    break;

  case XmCR_VALUE_CHANGED :
    number = XmTextGetString(w);
    tpValues[tag].value = atof(number);
    XtFree(number);
    break;

  default:
    break;

  }
}

#define UPDATE(index, value) \
  if	  ((value < 99999.99) && (value > -9999.99) ) (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, value); \
  else if ((value < 999999.9) && (value > -99999.9) ) (void) snprintf(output, CHAR_LENGTH+1, "%*.1f", CHAR_LENGTH, value); \
  else if ((value < 9999999.) && (value > -999999.) ) (void) snprintf(output, CHAR_LENGTH+1, "%*.0f", CHAR_LENGTH, value); \
  else                                                (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, 0.0  ); \
  XmTextSetString(textF[index], output);

static void button_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmPushButtonCallbackStruct *cbData = (XmPushButtonCallbackStruct *) cbDataGen;

  switch (cbData->reason) {

  case XmCR_ACTIVATE :
    if (tag == XmCR_ACTIVATE || tag == XmCR_APPLY) {
      char *output = (char *) malloc((unsigned) ((CHAR_LENGTH+1)*sizeof(char)));
      double tFinal, tInitial, tInc, pFinal, pInitial, pInc, dpdt;
      double hInc, dpdh, sInc, dpds, vInc, dtdv;

      if (tag == XmCR_ACTIVATE) XtUnmanageChild(tp_padb);

      if ((tInitial = tpValues[TP_PADB_INDEX_T_INITIAL].value) == 0.0) return;
      if ((pInitial = tpValues[TP_PADB_INDEX_P_INITIAL].value) == 0.0) return;

      if        (XmToggleButtonGadgetGetState(tg_isenthalpic)) {
        tpValues[TP_PADB_INDEX_T_INCREMENT].value = 0.0;
	hInc = tpValues[TP_PADB_INDEX_H_INCREMENT].value;
        if ((tFinal = tpValues[TP_PADB_INDEX_T_FINAL].value) == 0.0) 
          { UPDATE(TP_PADB_INDEX_T_FINAL, tInitial); }
        if ((dpdh = tpValues[TP_PADB_INDEX_DPDH].value) != 0.0) {
          pInc   = fabs(hInc*dpdh);
          UPDATE(TP_PADB_INDEX_P_INCREMENT, pInc);
          if ((pFinal = tpValues[TP_PADB_INDEX_P_FINAL].value) == 0.0)
            { UPDATE(TP_PADB_INDEX_P_FINAL, pInitial); }
        } else {
          if ((pFinal = tpValues[TP_PADB_INDEX_P_FINAL].value) != 0.0) {
            if ((pInc = tpValues[TP_PADB_INDEX_P_INCREMENT].value) == 0.0) {
              pInc = fabs(pFinal-pInitial);
              UPDATE(TP_PADB_INDEX_P_INCREMENT, pInc);
            }
            if (hInc != 0.0) { UPDATE(TP_PADB_INDEX_DPDH, fabs(pInc/hInc)); }
            else if (pInc == 0.0) { UPDATE(TP_PADB_INDEX_DPDH, 0.0); }
            else
              XmTextSetString(textF[TP_PADB_INDEX_DPDH], "");
          } else { 
            UPDATE(TP_PADB_INDEX_P_FINAL,     pInitial);
            UPDATE(TP_PADB_INDEX_P_INCREMENT, 0.0);
            UPDATE(TP_PADB_INDEX_DPDH,        0.0);
          }
        }
      } else if (XmToggleButtonGadgetGetState(tg_isentropic)) {
        tpValues[TP_PADB_INDEX_T_INCREMENT].value = 0.0;
	sInc = tpValues[TP_PADB_INDEX_S_INCREMENT].value;
        if ((tFinal = tpValues[TP_PADB_INDEX_T_FINAL].value) == 0.0) 
          { UPDATE(TP_PADB_INDEX_T_FINAL, tInitial); }
        if ((dpds = tpValues[TP_PADB_INDEX_DPDS].value) != 0.0) {
          pInc   = fabs(sInc*dpds);
          UPDATE(TP_PADB_INDEX_P_INCREMENT, pInc);
          if ((pFinal = tpValues[TP_PADB_INDEX_P_FINAL].value) == 0.0)
            { UPDATE(TP_PADB_INDEX_P_FINAL, pInitial); }
        } else {
          if ((pFinal = tpValues[TP_PADB_INDEX_P_FINAL].value) != 0.0) {
            if ((pInc = tpValues[TP_PADB_INDEX_P_INCREMENT].value) == 0.0) {
              pInc = fabs(pFinal-pInitial);
              UPDATE(TP_PADB_INDEX_P_INCREMENT, pInc);
            }
            if (sInc != 0.0) { UPDATE(TP_PADB_INDEX_DPDS, fabs(pInc/sInc)); }
            else if (pInc == 0.0) { UPDATE(TP_PADB_INDEX_DPDS, 0.0); }
            else
              XmTextSetString(textF[TP_PADB_INDEX_DPDS], "");
          } else { 
            UPDATE(TP_PADB_INDEX_P_FINAL,     pInitial);
            UPDATE(TP_PADB_INDEX_P_INCREMENT, 0.0);
            UPDATE(TP_PADB_INDEX_DPDS,        0.0);
          }
        }
      } else if (XmToggleButtonGadgetGetState(tg_isochoric)) {
        tpValues[TP_PADB_INDEX_P_INCREMENT].value = 0.0;
	vInc = tpValues[TP_PADB_INDEX_V_INCREMENT].value;
        if ((pFinal = tpValues[TP_PADB_INDEX_P_FINAL].value) == 0.0) 
          { UPDATE(TP_PADB_INDEX_P_FINAL, pInitial); }
        if ((dtdv = tpValues[TP_PADB_INDEX_DTDV].value) != 0.0) {
          tInc   = fabs(vInc*dtdv);
          UPDATE(TP_PADB_INDEX_T_INCREMENT, tInc);
          if ((tFinal = tpValues[TP_PADB_INDEX_T_FINAL].value) == 0.0)
            { UPDATE(TP_PADB_INDEX_T_FINAL, tInitial); }
        } else {
          if ((tFinal = tpValues[TP_PADB_INDEX_T_FINAL].value) != 0.0) {
            if ((tInc = tpValues[TP_PADB_INDEX_T_INCREMENT].value) == 0.0) {
              tInc = fabs(tFinal-tInitial);
              UPDATE(TP_PADB_INDEX_T_INCREMENT, tInc);
            }
            if (vInc != 0.0) { UPDATE(TP_PADB_INDEX_DTDV, fabs(tInc/vInc)); }
            else if (tInc == 0.0) { UPDATE(TP_PADB_INDEX_DTDV, 0.0); }
            else
              XmTextSetString(textF[TP_PADB_INDEX_DTDV], "");
          } else { 
            UPDATE(TP_PADB_INDEX_T_FINAL,     tInitial);
            UPDATE(TP_PADB_INDEX_T_INCREMENT, 0.0);
            UPDATE(TP_PADB_INDEX_DTDV,        0.0);
          }
        }
      } else {
        if ((tFinal = tpValues[TP_PADB_INDEX_T_FINAL].value) != 0.0) {
          if ((tInc = tpValues[TP_PADB_INDEX_T_INCREMENT].value) == 0.0) {
            tInc = fabs(tFinal-tInitial);
            UPDATE(TP_PADB_INDEX_T_INCREMENT, tInc);
          }
          if ((dpdt = tpValues[TP_PADB_INDEX_DPDT].value) != 0.0) {
            pFinal = dpdt*(tFinal-tInitial) + pInitial;
            pInc   = fabs(tInc*dpdt);
            UPDATE(TP_PADB_INDEX_P_FINAL,     pFinal);
            UPDATE(TP_PADB_INDEX_P_INCREMENT, pInc);
          } else {
            if ((pFinal = tpValues[TP_PADB_INDEX_P_FINAL].value) != 0.0) {
              if ((pInc = tpValues[TP_PADB_INDEX_P_INCREMENT].value) == 0.0) {
                pInc = fabs(pFinal-pInitial);
                UPDATE(TP_PADB_INDEX_P_INCREMENT, pInc);
              }
              if (tInc != 0.0)      { UPDATE(TP_PADB_INDEX_DPDT, pInc/tInc); }
              else if (pInc == 0.0) { UPDATE(TP_PADB_INDEX_DPDT, 0.0); }
              else
                XmTextSetString(textF[TP_PADB_INDEX_DPDT], "");
            } else { 
              UPDATE(TP_PADB_INDEX_P_FINAL,     pInitial);
              UPDATE(TP_PADB_INDEX_P_INCREMENT, 0.0);
              UPDATE(TP_PADB_INDEX_DPDT,        0.0);
            }
          }
        } else {
          UPDATE(TP_PADB_INDEX_T_FINAL,     tInitial);
          UPDATE(TP_PADB_INDEX_T_INCREMENT, 0.0);
          if ((pFinal = tpValues[TP_PADB_INDEX_P_FINAL].value) != 0.0) {
            if (tpValues[TP_PADB_INDEX_P_INCREMENT].value == 0.0) 
              { UPDATE(TP_PADB_INDEX_P_INCREMENT, fabs(pFinal-pInitial)); }
            XmTextSetString(textF[TP_PADB_INDEX_DPDT], "");
          } else {
            UPDATE(TP_PADB_INDEX_P_FINAL,     pInitial);
            UPDATE(TP_PADB_INDEX_P_INCREMENT, 0.0);
            UPDATE(TP_PADB_INDEX_DPDT,        0.0);
          }
        }
      }
      free(output);
    } else if (tag == XmCR_HELP) ;
    break;

  case XmCR_HELP :
    break;

  default:
    break;

  }
}

#undef UPDATE

static void map_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  XmAnyCallbackStruct *cbData = (XmAnyCallbackStruct *) cbDataGen;
  int i;
  char *output = (char *) malloc((unsigned) ((CHAR_LENGTH+1)*sizeof(char)));

  switch (cbData->reason) {

  case XmCR_MAP :
    for (i=0; i<ENTRIES; i++) {
      if (tpValues[i].value == 0.0) XmTextSetString(textF[i], "");
      else {
        (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, tpValues[i].value);
        XmTextSetString(textF[i], output);
      }
    }

    if        (XmToggleButtonGadgetGetState(tg_isenthalpic)) {
      XmTextSetEditable(textF[TP_PADB_INDEX_T_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_P_INCREMENT], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_H_INCREMENT], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_S_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_V_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDH], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDS], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DTDV], False);
      XmTextSetString(textF[TP_PADB_INDEX_T_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_S_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_V_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DPDT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DPDS], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DTDV], "  n.a.  ");
    } else if (XmToggleButtonGadgetGetState(tg_isentropic)) {
      XmTextSetEditable(textF[TP_PADB_INDEX_T_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_P_INCREMENT], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_H_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_S_INCREMENT], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_V_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDH], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDS], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_DTDV], False);
      XmTextSetString(textF[TP_PADB_INDEX_T_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_H_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_V_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DPDT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DPDH], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DTDV], "  n.a.  ");
    } else if (XmToggleButtonGadgetGetState(tg_isochoric)) {
      XmTextSetEditable(textF[TP_PADB_INDEX_T_INCREMENT], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_P_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_H_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_S_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_V_INCREMENT], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDH], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDS], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DTDV], True );
      XmTextSetString(textF[TP_PADB_INDEX_P_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_H_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_S_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DPDT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DPDH], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DPDS], "  n.a.  ");
    } else {
      XmTextSetEditable(textF[TP_PADB_INDEX_T_INCREMENT], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_P_INCREMENT], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_H_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_S_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_V_INCREMENT], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDT], True );
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDH], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DPDS], False);
      XmTextSetEditable(textF[TP_PADB_INDEX_DTDV], False);
      XmTextSetString(textF[TP_PADB_INDEX_H_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_S_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_V_INCREMENT], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DPDH], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DPDS], "  n.a.  ");
      XmTextSetString(textF[TP_PADB_INDEX_DTDV], "  n.a.  ");
    }

    break;

  default:
    break;
  }

  free(output);
}

/* end of file CREATE_TP_PADB.C */
