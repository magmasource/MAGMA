const char *create_managed_ver(void) { return "$Id: create_managed.c,v 1.5 2008/03/06 17:51:23 ghiorso Exp $"; }

/*
MELTS Source Code: RCS $Log: create_managed.c,v $
MELTS Source Code: RCS Revision 1.5  2008/03/06 17:51:23  ghiorso
MELTS Source Code: RCS New fluid fractionation mode and other enhancements.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2007/06/08 17:25:42  ghiorso
MELTS Source Code: RCS Added code to allow regression of Ghiorso EOS parameters
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
MELTS Source Code: RCS Revision 1.2  2005/01/08 22:21:02  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Set tolerance in silmin (before HFTI call) to 10*DBL_EPSILON to insure
MELTS Source Code: RCS catching phase rule violations in simple system crystallization.
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
 * Revision 3.10  1997/06/21  22:50:06  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.9  1997/05/03  20:23:42  ghiorso
 * *** empty log message ***
 *
 * Revision 3.8  1997/03/27  17:03:45  ghiorso
 * *** empty log message ***
 *
 * Revision 3.7  1996/09/24  20:33:51  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.6  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.5  1995/11/23  22:37:42  ghiorso
 * Final implementation of subsolidus fO2 buffering.
 *
 * Revision 3.4  1995/11/01  22:40:27  ghiorso
 * Implementation of subsolidus options after Asimow.
 * Additional implementation of nepheline solid solutions.
 *
 * Revision 3.3  1995/09/04  20:01:28  ghiorso
 * Update to allow display of bulk composition (in grams) in the text entry
 * fields of the main silmin display. Liquid composition is no longer
 * display here, and is available only through the popup selection.
 *
 * Revision 3.2  1995/09/01  23:53:03  ghiorso
 * Modifications made to update interface for V3.x and consolidate
 * Graph Widgets
 *
 * Revision 3.1  1995/08/18  17:23:19  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Function to create the following children of the silmin_adb
**          Form widget (file: CREATE_MANAGED.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  August 24, 1990   Original Version
**      V1.0-2  Mark S. Ghiorso  August 30, 1991
**              (1) Added private definition of ADD_BUTTON macro
**              (2) Added globally known declarations for extern widgets
**                  and symbols
**      V1.1-0  Mark S. Ghiorso  September 3, 1991
**              (1) removed next entry from compositionValues structure
**              (2) removed compound strings from phases structure
**              (3) reorganized debugEntries structure
**              (4) reorganized statusEntries structure
**              (5) added global macro definitions to INTERFACE.H to describe
**                  order of label widgets
**      V1.1-1  Mark S. Ghiorso  September 4, 1991
**              Added Global macros to identify contents of extern
**              variable units_phase_display
**      V1.1-2  Mark S. Ghiorso  September 20, 1991
**              (1) Altered attachment of global label widgets for number
**                  display from left to right attachment
**              (2) Added updateSolidADB() to button callbacks in units
**                  option menu
**              (3) changed "incl fractionated" toggle to point to
**                  units_callback with a tag of zero; updateSolidADB() will
**                  inquire the state of the toggle.
**              (4) Cosmetic changes to status and debug label widget layout
**              (5) Altered titles on graph widgets
**      V1.2-0  Mark S. Ghiorso  October 18, 1991
**              (1) Added popup attached dialog box to right of main display.
**              (2) Added vlist child of the above for display of graph
**                  legends
**              (3) Added callback to the above to the color mixing widget
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V3.0-1  Mark S. Ghiorso  November 23, 1991
**              (1) Complete reorganization of code
**              (2) Removal of debug box and entries
**              (3) conversion of statusEntries[STATUS_ADB_INDEX_STATUS].name
**                  label widget into a scrolled text widget
**              (4) Preliminary implementation and position of vlist
**                  graph legend widget within the work window display
**              Mark S. Ghiorso  November 27, 1991
**              (1) Implementation of option menu for log10 fo2 display
**              (2) Reorganization of the solids display, including elimination
**                  of phases structure
**              Mark S. Ghiorso  November 28, 1991
**              (1) Greek characters in status display for fo2 buffers
**              (2) call initComputeDataStruct first to allow the vlist
**                  widget header to be correctly configured
**              Mark S. Ghiorso  December 18, 1991
**              (1) Removed magma mix statusEntry and repositioned remaining
**                  status label widgets
**      V3.0-2  Mark S. Ghiorso  December 19, 1991
**              (1) Removed mnemonic from include fractionated button
**              (2) Added popup dialog support for phase properties
**      V3.0-3  Mark S. Ghiorso  January 4, 1992
**              (1) Changed resource variables for graph widget (XtN -> GwN)
**      V3.0-4  Mark S. Ghiorso  January 17, 1992
**              (1) Completed code for preliminary implementation of popup
**                  dialog support for phase properties
**      V3.0-5  Mark S. Ghiorso  January 28, 1992
**              (1) Altered initialization of args[] arrays to be compatible
**                  with RISC DEC C requirement
**              (2) Added global initialization of the phases Widget
**      V3.0-6  Mark S. Ghiorso  February 18, 1992
**              (1) Assorted minor "casting" modifications for ANSI compliance
**              (2) Made i a local variable in create_solid()
**              (3) Removed redundant global declaration of silmin_adb
**      V3.0-7  Mark S. Ghiorso  March 14, 1992
**              (1) Initialized compositionValues[].value to zero when
**                  widget in [].name is created
**              (2) Added fractionation solids to popup display of system
**                  properties
**      V3.0-8  Mark S. Ghiorso  March 17, 1992
**              Added macros for non-DEC extensions to Motif
**      V3.0-9  Mark S. Ghiorso  March 27, 1992
**              Correceted numerous casting violations for callback routines
**              in accord with ANSI C compliance
**      V3.0-10 Mark S. Ghiorso  April 23, 1992
**              Corrected errors in text_callback algorithm
**      V3.1-1  Mark S. Ghiorso  July 13, 1992
**              (1) Added addition "Formula" column to the phases vList widget
**      V3.1-2  Mark S. Ghiorso  September 28, 1992
**              Corrected calls to XtFree() => free() in data allocated 
**              with malloc()
**      V3.1-3  Mark S. Ghiorso  September 29, 1992
**              Converted TextField to Text widgets as a bug workaround 
**              for DECWindows Motif V 1.1
**      V3.1-4  Mark S. Ghiorso September 22, 1993
**              Removed incorect resources in creation of vframe widget
**      V3.1-5  Mark S. Ghiorso September 27, 11993
**              Added option to code to make vheader, and vlist widgets
**              children of drawingArea rather than vframe (Motif 1.2)
**      V3.1-6  Mark S. Ghiorso March 12, 1994
**              Added ToggleB.h include statement for set and get functions
**      V3.1-7  Mark S. Ghiorso April 4, 1994
**              Added #ifdef __osf__ to fix 64 bit errors
**      V3.1-8  Mark S. Ghiorso April 23, 1994
**              Corrected casting violations for callbacks
**      V4.0-1  Mark S. Ghiorso May 11, 1994
**              (1) Modified calls to *cpmix and *vmix to reflect new 
**                  derivatives
**--
*/

#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Xm/DrawingA.h>
#include <Xm/DrawnB.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/PanedW.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/SashP.h>     /* We need to stop keyboard traversal on the sashes */
#include <Xm/Scale.h>
#include <Xm/ScrollBar.h>
#include <Xm/ScrolledW.h>
#include <Xm/Text.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>

#include <X11/Xatom.h>    /* Needed to obtain font properties */

#include "interface.h"
#include "silmin.h"
#ifdef DRAWINGA_VLIST_PARENT
#include <Xm/DrawingA.h>
#else
#include "vframe.h"
#endif
#include "vheader.h"
#include "vlist.h"

/******************************************************************************
 * Globally known symbols declared extern in INTERFACE.H
 ******************************************************************************/

Widget phases, compPDmenu;

CompositionValues *compositionValues;
int               units_phase_display;
int               units_logfo2_display;
StatusEntries     *statusEntries;
CompEntries       *compEntries;


/* 
 *=============================================================================
 * Layout and Macro definitions for create_managed():
 *
 ---------------------------------------------------------------------------
 |         |           |                                                   |
 |         |           |                                                   |
 |         |           |                                                   |
 |         |           |                    status_adb                     |
 |         |           |                                                   |
 |         R           R                                                   |
 | liquid  I  comp_adb I                                                   |
 |   _adb  G           G--------------------TOP_USER-----------------------|
 |         H           H                                                   |
 |         T           T                                                   |
 |         _           _                                                   |
 |         M           P                                                   |
 |         E           H                                                   |
 |         N           A                                                   |
 |         U           S                                                   |
 |         |           E                                                   |
 |---------------------------------TOP_S-----------------------------------|
 |                                                                         |
 |                                                                         |
 |                               solid_adb                                 |
 |                                                                         |
 |                                                                         |
 ---------------------------------------------------------------------------
*/

#define TOP_S       68
#define TOP_USER    54

#define RIGHT_MENU  15
#define RIGHT_PHASE 30

static void create_liquid_adb(void);
static void create_comp_adb(void);
static void create_solid_adb(void);
static void create_status_adb(void);
static void create_user_adb(void); 

void create_managed()
{
  create_liquid_adb();
  create_comp_adb();
  create_solid_adb();
  create_status_adb();
  create_user_adb(); 
}

/*
 *=============================================================================
 * Routines to create and manage the user attached dialog box
 */
 
static void redraw_button(Widget w, XtPointer cData, XtPointer cbDataGen);
static GC gc;

#include "xmgr_icon.h"
#include "graph_icon.h"
#include "calculator_icon.h"
#include "terminal_icon.h"

static void create_user_adb() 
{
  static Widget frame, form, label[5], rowcol, button[4];
  Pixmap pixmap;
  Pixel fg, bg;

  /* outer frame */
  frame = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, silmin_adb,
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition,    TOP_USER,
    XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, TOP_S,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,   RIGHT_PHASE,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  label[4] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, frame, 
    XtVaTypedArg, XmNlabelString, XmRString, "Click on Icon to Launch Option", (int) (strlen("Click on Icon to Launch Option")+1),
    XmNchildType, XmFRAME_TITLE_CHILD,
    NULL);

  form = XtVaCreateWidget("Form", xmFormWidgetClass, frame,
    XmNchildType, XmFRAME_WORKAREA_CHILD,
    NULL);
  rowcol = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form,
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       8,
    XmNspacing,          20,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  XtVaGetValues(rowcol, XmNforeground, &fg, XmNbackground, &bg, NULL);
  gc = XCreateGC(XtDisplay(rowcol), RootWindowOfScreen(XtScreen(rowcol)), 0, 0);
  XSetForeground(XtDisplay(rowcol), gc, fg);
  XSetBackground(XtDisplay(rowcol), gc, bg);
 
  pixmap = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
    (char *) xmgr_icon_bits, xmgr_icon_width, xmgr_icon_height, fg, bg, DefaultDepthOfScreen(XtScreen(topLevel)));

  button[0] = XtVaCreateManagedWidget("DrawnButton", xmDrawnButtonWidgetClass, 
    rowcol,
    XmNwidth,             64,
    XmNheight,            64,
    XmNpushButtonEnabled, True,
    XmNshadowType,        XmSHADOW_ETCHED_OUT,
    NULL);
  XtAddCallback(button[0], XmNactivateCallback, launch_callback, (XtPointer) LAUNCH_GRAPH_DISPLAY);
  XtAddCallback(button[0], XmNexposeCallback,   redraw_button,   (XtPointer) pixmap);
  XtAddCallback(button[0], XmNresizeCallback,   redraw_button,   (XtPointer) pixmap);

  label[0] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, rowcol, XtVaTypedArg, XmNlabelString, XmRString,
      "Graphics\nDisplay\nWindow", (int) (strlen("Graphics\nDisplay\nWindow")+1), NULL);

  pixmap = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
    (char *) graph_icon_bits, graph_icon_width, graph_icon_height, fg, bg, DefaultDepthOfScreen(XtScreen(topLevel)));

  button[1] = XtVaCreateManagedWidget("DrawnButton", xmDrawnButtonWidgetClass, 
    rowcol,
    XmNwidth,             64,
    XmNheight,            64,
    XmNpushButtonEnabled, True,
    XmNshadowType,        XmSHADOW_ETCHED_OUT,
    NULL);
  XtAddCallback(button[1], XmNactivateCallback, launch_callback, (XtPointer) LAUNCH_GRAPH_OPTIONS);
  XtAddCallback(button[1], XmNexposeCallback,   redraw_button,   (XtPointer) pixmap);
  XtAddCallback(button[1], XmNresizeCallback,   redraw_button,   (XtPointer) pixmap);

  label[1] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, rowcol, XtVaTypedArg, XmNlabelString, XmRString,
      "Graphics\nOptions\nDialog", (int) (strlen("Graphics\nOptions\nDialog")+1), NULL);

  pixmap = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
    (char *) calculator_icon_bits, calculator_icon_width, calculator_icon_height, fg, bg, DefaultDepthOfScreen(XtScreen(topLevel)));

  button[2] = XtVaCreateManagedWidget("DrawnButton", xmDrawnButtonWidgetClass, 
    rowcol,
    XmNwidth,             64,
    XmNheight,            64,
    XmNpushButtonEnabled, True,
    XmNshadowType,        XmSHADOW_ETCHED_OUT,
    NULL);
  XtAddCallback(button[2], XmNactivateCallback, launch_callback, (XtPointer) LAUNCH_CALCULATOR);
  XtAddCallback(button[2], XmNexposeCallback,   redraw_button,   (XtPointer) pixmap);
  XtAddCallback(button[2], XmNresizeCallback,   redraw_button,   (XtPointer) pixmap);

  label[2] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, rowcol, XtVaTypedArg, XmNlabelString, XmRString,
      "Supplemental\nCalculator", (int) (strlen("Supplemental\nCalculator")+1), NULL);

  pixmap = XCreatePixmapFromBitmapData(XtDisplay(topLevel), RootWindowOfScreen(XtScreen(topLevel)), 
    (char *) terminal_icon_bits, terminal_icon_width, terminal_icon_height, fg, bg, DefaultDepthOfScreen(XtScreen(topLevel)));

  button[3] = XtVaCreateManagedWidget("DrawnButton", xmDrawnButtonWidgetClass, 
    rowcol,
    XmNwidth,             64,
    XmNheight,            64,
    XmNpushButtonEnabled, True,
    XmNshadowType,        XmSHADOW_ETCHED_OUT,
    NULL);
  XtAddCallback(button[3], XmNactivateCallback, launch_callback, (XtPointer) LAUNCH_VIEWER);
  XtAddCallback(button[3], XmNexposeCallback,   redraw_button,   (XtPointer) pixmap);
  XtAddCallback(button[3], XmNresizeCallback,   redraw_button,   (XtPointer) pixmap);

  label[3] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, rowcol, XtVaTypedArg, XmNlabelString, XmRString,
      "View\nOutput\nFile", (int) (strlen("View\nOutput\nFile")+1), NULL);

  XtManageChild(rowcol);
  XtManageChild(form);
}

static void redraw_button(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  Pixmap pixmap = (Pixmap) cData;
  XmDrawnButtonCallbackStruct *cbData = (XmDrawnButtonCallbackStruct *) cbDataGen;
  unsigned int pix_w, pix_h;
  int srcx, srcy, destx, desty;
  int drawsize, border;
  Dimension bdr_w, w_width, w_height;
  short hlthick, shthick;
  Window root;

  /* get width and height of the pixmap. don't use srcx and root */
  XGetGeometry (XtDisplay (w), (Drawable) pixmap, &root, &srcx, &srcy, &pix_w, &pix_h, (unsigned int *) &srcx, (unsigned int *) &srcy);

  /* get the values of all the resources that affect the entire geometry of the button. */
  XtVaGetValues (w,
    XmNwidth,              &w_width,
    XmNheight,             &w_height,
    XmNborderWidth,        &bdr_w,
    XmNhighlightThickness, &hlthick,
    XmNshadowThickness,    &shthick,
    NULL);

  /* calculate available drawing area, width 1st */
  border = bdr_w + hlthick + shthick;

  /* if window is bigger than pixmap, center it; else clip pixmap */
  drawsize = w_width - 2 * border;
  if (drawsize > pix_w) {
    srcx = 0;
    destx = (drawsize - pix_w) / 2 + border;
  } else {
    srcx = (pix_w - drawsize) / 2;
    pix_w = drawsize;
    destx = border;
  }

  drawsize = w_height - 2 * border;
  if (drawsize > pix_h) {
    srcy = 0;
    desty = (drawsize - pix_h) / 2 + border;
  } else {
    srcy = (pix_h - drawsize) / 2;
    pix_h = drawsize;
    desty = border;
  }

  if (cbData->window != 0) XCopyArea (XtDisplay (w), pixmap, cbData->window, gc, srcx, srcy, pix_w, pix_h, destx, desty);
}

/*
 *=============================================================================
 * Routines to create and manage liquid attached dialog box
 */
#define TOP    6   /* relative offset of first label/text pair from */
                   /* top of dialog box */
#define LEFT_L 5   /* relative offset of left edge of label widget from */
                   /* left edge of dialog box */
#define RIGHT_T 95 /* relative offset of right edge of text widget from */
                   /* right edge of dialog box */

#define CHAR_LENGTH 7

static void text_callback(Widget w, XtPointer cData, XtPointer cbDataGen); 

static void create_liquid_adb()
{
  int j;
  static Widget *compositionLabels, form, frame, units, content;

  frame = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, silmin_adb,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, TOP_S,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition,  RIGHT_MENU,
    NULL);

  form = XtVaCreateWidget("Form", xmFormWidgetClass, frame, NULL);

  units = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form, 
    XtVaTypedArg,       XmNlabelString,     XmRString,        "grams",  (int) (strlen("grams")+1),
    XmNtopAttachment,   XmATTACH_POSITION,  XmNtopPosition,   1,
    XmNrightAttachment, XmATTACH_POSITION,  XmNrightPosition, RIGHT_T,
    NULL);

  compositionValues = (CompositionValues *) malloc((size_t) nc*sizeof(CompositionValues));
  compositionLabels = (Widget *) malloc((size_t) nc*sizeof(Widget));

  for (j = 0; j < nc ; j++) {

    if (j==0) compositionLabels[j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form, 
      XtVaTypedArg, XmNlabelString,   XmRString,         bulkSystem[j].label, (int) (strlen(bulkSystem[j].label)+1),
                    XmNtopAttachment, XmATTACH_POSITION, XmNtopPosition,      TOP, 
      NULL);
    else      compositionLabels[j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form, 
      XtVaTypedArg, XmNlabelString,   XmRString,       bulkSystem[j].label, (int) (strlen(bulkSystem[j].label)+1),
                    XmNtopAttachment, XmATTACH_WIDGET, XmNtopWidget,        compositionValues[j-1].name,
      NULL);

    compositionValues[j].name = XtVaCreateManagedWidget("Text", xmTextWidgetClass, form, 
#ifdef WHITE_TEXTW
      XmNbackground,          white,
#endif
      XmNcolumns,             CHAR_LENGTH,
      XmNmarginHeight,        0, 
      XmNmaxLength,           CHAR_LENGTH,
      XmNnavigationType,      XmNONE,
      XmNtraversalOn,         True,
      XmNrightAttachment,     XmATTACH_POSITION,        XmNrightPosition,     RIGHT_T,
      XmNtopAttachment,       XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,         compositionLabels[j],
      NULL);
    XtAddCallback(compositionValues[j].name, XmNactivateCallback, (XtCallbackProc) XmProcessTraversal, (XtPointer) XmTRAVERSE_NEXT);
    {
    long jLong = (long) j;
    XtAddCallback(compositionValues[j].name, XmNlosingFocusCallback,  text_callback, (XtPointer) jLong);
    XtAddCallback(compositionValues[j].name, XmNmodifyVerifyCallback, text_callback, (XtPointer) jLong);
    XtAddCallback(compositionValues[j].name, XmNvalueChangedCallback, text_callback, (XtPointer) jLong);
    }
    compositionValues[j].value = 0.0; 
  }

  content = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form, 
    XtVaTypedArg, XmNlabelString,      XmRString,         "Bulk System",     (int) (strlen("Bulk System")+1),
                  XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, 99,
    NULL);

  XtManageChild(form);
}

static void text_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmTextVerifyCallbackStruct *cbData = (XmTextVerifyCallbackStruct *) cbDataGen;
  char *number, *output;
  long len;

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
      output = (char *) malloc((size_t) ((CHAR_LENGTH+1)*sizeof(char)));
      (void) snprintf(output, CHAR_LENGTH+1, "%*.4f", CHAR_LENGTH, atof(number));
    } else {
      output = (char *) malloc((size_t) sizeof(char));
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
          cbData->text->length = (int) strlen(cbData->text->ptr);
        }
        for (len=0; len<cbData->text->length; len++) {
          if (!isdigit(cbData->text->ptr[len]) && cbData->text->ptr[len] != '.' && cbData->text->ptr[len] != ' ') {
            int j;
            for (j=(int)len; (j+1)<cbData->text->length; j++) cbData->text->ptr[j] = cbData->text->ptr[j+1];
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
    compositionValues[tag].value = atof(number);
    XtFree(number);
    break;

  default:
    break;

  }
}

#undef TOP
#undef LEFT_L
#undef RIGHT_T
#undef CHAR_LENGTH

/*
 *=============================================================================
 * Routines to create and manage the composition attached dialog box
 */
#define TOP    6  /* relative offset of first label/text pair from */
                  /* top of dialog box */
#define LEFT_L 5  /* relative offset of left edge of label widget from */
                  /* left edge of dialog box */
#define LEFT_T 40 /* relative offset of left edge of text widget from */
                  /* left edge of dialog box */

static void create_comp_adb()
{
  int j;
  static Widget *compositionLabels, form, frame, units, content_op_menu, none;
  XmString csString;

  frame = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, silmin_adb,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, TOP_S,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,   RIGHT_MENU,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition,  RIGHT_PHASE,
    NULL);

  form = XtVaCreateWidget("Form", xmFormWidgetClass, frame, NULL);

  units = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form, 
    XtVaTypedArg,      XmNlabelString,     XmRString,        "wt% (ppm)",  (int) (strlen("wt% (ppm)")+1),
    XmNtopAttachment,   XmATTACH_POSITION,  XmNtopPosition,  1,
    XmNrightAttachment, XmATTACH_FORM,
    NULL);

  compEntries  = (CompEntries *) malloc((size_t) nc*sizeof(CompEntries));
  compositionLabels = (Widget *) malloc((size_t) nc*sizeof(Widget));

  for (j=0; j<nc ; j++) {
    if (j==0) compositionLabels[j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form, 
        XtVaTypedArg, XmNlabelString,   XmRString,         bulkSystem[j].label, (int) (strlen(bulkSystem[j].label)+1),
                      XmNtopAttachment, XmATTACH_POSITION, XmNtopPosition,      TOP, 
        NULL);
    else compositionLabels[j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form, 
        XtVaTypedArg, XmNlabelString,   XmRString,       bulkSystem[j].label, (int) (strlen(bulkSystem[j].label)+1),
                      XmNtopAttachment, XmATTACH_WIDGET, XmNtopWidget,        compEntries[j-1].name,
        NULL);

    compEntries[j].name = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form, 
      XtVaTypedArg, XmNlabelString,     XmRString, "--------",    (int) (strlen("--------")+1),
                    XmNalignment,       XmALIGNMENT_END, 
                    XmNrightAttachment, XmATTACH_FORM,
                    XmNtopAttachment,   XmATTACH_OPPOSITE_WIDGET, XmNtopWidget, compositionLabels[j],
      NULL);
  }

  compPDmenu = XmCreatePulldownMenu(form, "PulldownMenu", NULL, 0);

  none = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, compPDmenu,
    XtVaTypedArg, XmNlabelString, XmRString, "none", (int) (strlen("none")+1), NULL);
  XtAddCallback(none, XmNactivateCallback, compPDcallback, (XtPointer) NULL);

  csString = XmStringCreateLtoR("Phase:", "ISO8859-1");
  {
    Arg args[8];
    XtSetArg(args[0], XmNsubMenuId,        compPDmenu);
    XtSetArg(args[1], XmNlabelString,      csString);
    XtSetArg(args[2], XmNmnemonic,         'h');
    XtSetArg(args[3], XmNmenuHistory,      none);
    XtSetArg(args[4], XmNtopAttachment,    XmATTACH_NONE);
    XtSetArg(args[5], XmNbottomAttachment, XmATTACH_FORM);
    XtSetArg(args[6], XmNleftAttachment,   XmATTACH_FORM);
    XtSetArg(args[7], XmNrightAttachment,  XmATTACH_FORM);
    content_op_menu = XmCreateOptionMenu(form, "OptionMenu", args, XtNumber(args));
    XtManageChild(content_op_menu);
  }
  XmStringFree(csString);

  XtManageChild(form);
}

/* This callback is used by both PushButtons and ToggleButtons */
void compPDcallback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  XmAnyCallbackStruct *cbData = (XmAnyCallbackStruct *) cbDataGen;
  switch (cbData->reason) {

  case XmCR_ACTIVATE :       /* Push button   */
  case XmCR_VALUE_CHANGED :  /* Toggle button */
    if (silminState != NULL) updateCompADB();
    break;
  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;
  default:
    break;

  }
}

#undef TOP
#undef LEFT_L
#undef LEFT_T

/*
 *=============================================================================
 * Routines to create and manage the solid attached dialog box
 */
#define NLABELS 5

static void units_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void vList_callback(Widget w, XtPointer cData, XtPointer cbDataGen);

static char *curPhase;
static int  curPhaseIndex;
static int  curPhaseNS, curPhaseNL;
static void dialog_popup(void);

static int k_tag_units_grams          = SOLID_ADB_UNITS_GRAMS;
static int k_tag_units_volume_percent = SOLID_ADB_UNITS_VOLUME;
static int k_tag_units_weight_percent = SOLID_ADB_UNITS_WEIGHT;

static void create_solid_adb()
{
  static Widget bt_grams, bt_vol, bt_wt, form[2], frame[3], hScroll, label,
                phase_units, phase_units_menu, vframe, vheader, vScroll;
  static const char *columnLabels[NLABELS] = { "  ", "Phase", "Units", "Affinity", "Formula" };
  static const char *extraLabels[2]        = { "Component", "mol frac" };

  int i, naMax;
  XmString csString;
  VListLabel *headerLabel;
  VListField *fieldChar;

  /* outer frame and form */
  frame[0] = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, silmin_adb,
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition,   TOP_S,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  form[0] = XtVaCreateWidget("Form", xmFormWidgetClass, frame[0], NULL);

  /* top frame and form */
  frame[1] = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, form[0],
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_NONE,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  form[1] = XtVaCreateWidget("Form", xmFormWidgetClass, frame[1], NULL);

  /* elements of the top form */
  label = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[1], 
    XtVaTypedArg,      XmNlabelString,     XmRString,
      "Double-click on phase name for physical properties display",  
      (int) 
      (strlen("Double-click on phase name for physical properties display")+1),
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_NONE,
    NULL);

  phase_units_menu = XmCreatePulldownMenu(form[1], "PulldownMenu", NULL, 0);

  bt_vol   = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, phase_units_menu,
             XmNmnemonic,  'v',
             XtVaTypedArg, XmNlabelString, XmRString, "vol %", (int) (strlen("vol %")+1), NULL);
  bt_grams = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, phase_units_menu,
             XmNmnemonic,  'g',
             XtVaTypedArg, XmNlabelString, XmRString, "grams", (int) (strlen("grams")+1), NULL);
  bt_wt    = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, phase_units_menu,
             XmNmnemonic,  'w',
             XtVaTypedArg, XmNlabelString, XmRString, "wt %", (int) (strlen("wt %")+1), NULL);

  {
  long longTag = (long) k_tag_units_volume_percent;
  XtAddCallback(bt_vol,   XmNactivateCallback, units_callback, (XtPointer) longTag);
  longTag = (long) k_tag_units_grams;
  XtAddCallback(bt_grams, XmNactivateCallback, units_callback, (XtPointer) longTag);
  longTag = (long) k_tag_units_weight_percent;
  XtAddCallback(bt_wt,    XmNactivateCallback, units_callback, (XtPointer) longTag);
  }
  units_phase_display = k_tag_units_grams; /* default entry */

  csString = XmStringCreateLtoR("Phase units:   ", "ISO8859-1");
  {
    Arg args[8];
    XtSetArg(args[0], XmNsubMenuId,        phase_units_menu);
    XtSetArg(args[1], XmNlabelString,      csString);
    XtSetArg(args[2], XmNmnemonic,         'u');
    XtSetArg(args[3], XmNmenuHistory,      bt_grams);
    XtSetArg(args[4], XmNtopAttachment,    XmATTACH_FORM);
    XtSetArg(args[5], XmNbottomAttachment, XmATTACH_FORM);
    XtSetArg(args[6], XmNleftAttachment,   XmATTACH_NONE);
    XtSetArg(args[7], XmNrightAttachment,  XmATTACH_FORM);
    phase_units = XmCreateOptionMenu(form[1], "OptionMenu", args, XtNumber(args));
    XtManageChild(phase_units);
  }
  XmStringFree(csString);

  XtManageChild(form[1]);

  /* lower frame and VList family of widgets */
  frame[2] = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, form[0],
    XmNtopAttachment,    XmATTACH_WIDGET,   XmNtopWidget   , frame[1],
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
#ifdef DRAWINGA_VLIST_PARENT
  vframe = XtVaCreateManagedWidget("vframe", xmDrawingAreaWidgetClass, frame[2],
    XmNmarginHeight,     0,
    XmNmarginWidth,      0,
    NULL);
#else
  vframe = XtVaCreateManagedWidget("vframe", vframeWidgetClass, frame[2], 
    XmNborderWidth,      0,                 /* Motif compliance */
    NULL);
#endif
  hScroll = XtVaCreateManagedWidget("ScrollBar", xmScrollBarWidgetClass, vframe,
    XmNorientation,      XmHORIZONTAL,
    XmNwidth,            (Dimension) 1,
    NULL);
  vScroll = XtVaCreateManagedWidget("ScrollBar", xmScrollBarWidgetClass, vframe,
    XmNorientation,      XmVERTICAL,
    XmNheight,           (Dimension) 1,
    NULL);
  vheader = XtVaCreateManagedWidget("vheader", vheaderWidgetClass, vframe, 
    XmNborderWidth,      0,                 /* Motif compliance */
    NULL);

  for (i=0, naMax=0; i<npc; i++) if (solids[i].na > naMax) naMax = solids[i].na;
  headerLabel = (VListLabel *) malloc((size_t) (NLABELS+2*naMax)*sizeof(VListLabel));
  fieldChar   = (VListField *) malloc((size_t) (NLABELS+2*naMax)*sizeof(VListField));
  for (i=0; i<(NLABELS+2*naMax); i++) {
    headerLabel[i].mask      = VListLabelTextMask | VListLabelAlignmentMask;
    headerLabel[i].alignment = VListAlignmentLeft;
    fieldChar[i].mask        = VListFieldAlignmentMask;
    fieldChar[i].alignment   = VListAlignmentLeft;          /* default */
  }
  for (i=0; i<NLABELS; i++) {
    headerLabel[i].textP = (char *) malloc((size_t) (strlen(columnLabels[i])+1)*sizeof(char));
    (void) strcpy(headerLabel[i].textP, columnLabels[i]);
  }
  fieldChar[2].alignment = VListAlignmentRight;             /* units    */
  fieldChar[3].alignment = VListAlignmentRight;             /* affinity */
  for (i=0; i<(2*naMax); i++) {
    headerLabel[NLABELS+i].textP = (char *) malloc((size_t) (strlen(extraLabels[0])+1)*sizeof(char));
    (void) strcpy(headerLabel[NLABELS+(i)].textP, extraLabels[0]);
    i++;
    headerLabel[NLABELS+i].textP = (char *) malloc((size_t) (strlen(extraLabels[1])+1)*sizeof(char));
    (void) strcpy(headerLabel[NLABELS+ i   ].textP, extraLabels[1]);
    fieldChar[NLABELS+i].alignment   = VListAlignmentRight; /* mole fraction */
  }

  phases = XtVaCreateManagedWidget("vlist", vlistWidgetClass, vframe, 
    XmNborderWidth,         0,                       /* Motif compliance */
    VListNcolumnStyle,      VListColumnStyleSingle,
    VListNfieldCount,       (NLABELS+2*naMax),
    VListNfields,           fieldChar,
    VListNlabelCount,       (NLABELS+2*naMax),
    VListNlabels,           headerLabel,
    VListNhScrollBarWidget, hScroll,
    VListNvScrollBarWidget, vScroll,
    VListNheaderWidget,     vheader,
    VListNselectUnit,       VListSelectUnitField,
    NULL);
  XtAddCallback(phases, VListNselectConfirmCallback, vList_callback, 
    (XtPointer) 0);
  free(headerLabel);
  free(fieldChar);

  XtManageChild(form[0]);
}

/* This callback is used by both PushButtons and ToggleButtons */
static void units_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmAnyCallbackStruct *cbData = (XmAnyCallbackStruct *) cbDataGen;
  switch (cbData->reason) {

  case XmCR_ACTIVATE :       /* Push button   */
  case XmCR_VALUE_CHANGED :  /* Toggle button */
    if (tag > 0) units_phase_display = (int) tag;
    if (silminState != NULL) updateSolidADB((double *) NULL, (double *) NULL);
    break;
  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;
  default:
    break;

  }
}

static void vList_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  VListSelectCallbackStruct *cbData = (VListSelectCallbackStruct *) cbDataGen;

  switch (cbData->reason) {

  case VListCRSelect:
    break;

  case VListCRSelectConfirm:
    if (cbData->vLine.closure != 0) {
      if (cbData->field == 1) {
        int i;
        curPhase = cbData->vLine.textP;
        for (i=0; i<npc; i++) if((silminState->nSolidCoexist)[i] > 0 && strcmp(solids[i].label, curPhase) == 0) {
          curPhaseIndex = i;
          if ((silminState->nSolidCoexist)[i] == 1) curPhaseNS = 0;
          else {
            VListLine vLineP;
            int j, fieldP, rowP;
            float value, test, zero = FLT_MAX;
            Opaque closure = VListFieldRowToLine((VListWidget) w, NLABELS+1, cbData->row);
            if (!VListGetLineInfo((VListWidget) w, closure, &vLineP, &fieldP, &rowP)) return;
            if (sscanf(vLineP.textP, "%f", &value) == EOF) return;
            for (j=0; j<(silminState->nSolidCoexist)[curPhaseIndex]; j++) {
              test = (silminState->solidComp)[curPhaseIndex+1][j]/(silminState->solidComp)[curPhaseIndex][j];
              if (ABS(value-test) < zero) { 
                zero = ABS(value-test); curPhaseNS = j; }
            }
          } 
          dialog_popup();
          break;
        }
        if (i == npc && strncmp("liquid", curPhase, 6) == 0) { 
          curPhaseIndex = npc; 	  
          if (silminState->liquidMass != 0.0) {
	    curPhaseNL = atoi(&curPhase[7]);    /* label is liquid-**, where ** is the liquid number */
	    dialog_popup();
	  }
        }
      }
    }
    break;

  default:
    break;

  }
}

#undef  NLABELS

typedef struct _entries {
  const char   *name;
  Widget label;
  Widget text;
} Entries;

static Entries entries[] = { 
  { "G (Joules): "            },
  { "H (Joules): "            },
  { "S (Joules/K): "          },
  { "V (cc): "                },
  { "Cp (Joules/K): "         },
  { "Density (gm/cc): "       },
  { "Viscosity (log poise): " }
};
#define NLABELS (sizeof entries / sizeof(Entries)) 
#define CHAR_LENGTH 14

static Widget labelPhaseDialog, formDialog, dismissButton, moreButton;

static void unmap_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void map_callback(Widget w, XtPointer cData, XtPointer cbDataGen);

static void dialog_popup(void)
{
  static Widget form[2], pane, rowcol;
  XmString csString1, csString2, csString3;
  Dimension h, w, hSum, wSum, wMax;
  int i;

  if (formDialog != (Widget) NULL) { XtManageChild(formDialog); return; }

  /* create pop up form dialog box */
  {
    Arg args[] = { { XmNdialogStyle,     XmDIALOG_FULL_APPLICATION_MODAL },
                   { XmNdefaultPosition, True                            },
                   { XmNautoUnmanage,    False                           } };
    formDialog = XmCreateFormDialog(silmin_adb, "FormDialog", args, XtNumber(args));
    XtAddCallback(formDialog, XmNmapCallback, map_callback, NULL);
    XtVaSetValues(XtParent(formDialog), XmNdeleteResponse, XmUNMAP, XmNtitle, "Physical and Chemical Properties", NULL);
  }

  /* pane window to hold everything */
  pane = XtVaCreateWidget("Pane", xmPanedWindowWidgetClass, formDialog,
    XmNsashWidth,        1,
    XmNsashHeight,       1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  /* top cell of the pane window */
  form[0] = XtVaCreateWidget("Form", xmFormWidgetClass, pane, NULL);

  /* Label */
  csString1 = XmStringCreateLtoR("Properties of ", "ISO8859-1");
  csString2 = XmStringCreateLtoR(curPhase, "ISO8859-1");
  csString3 = XmStringConcat(csString1, csString2); 
  XmStringFree(csString1); XmStringFree(csString2);
  labelPhaseDialog = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XmNlabelString,      csString3,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  XmStringFree(csString3);
#if (XmVERSION > 1) || (XmUPDATE_LEVEL > 3)
  XtVaGetValues(labelPhaseDialog, XmNheight, &h, XmNwidth, &w, NULL);
  hSum = h + 10; wSum = 0; wMax = w/2;
#endif

   /* row column */
   rowcol = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form[0],
    XmNpacking,          XmPACK_COLUMN,
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       NLABELS,
    XmNisAligned,        True,
    XmNentryAlignment,   XmALIGNMENT_END,
    XmNtopAttachment,    XmATTACH_WIDGET,   XmNtopWidget,     labelPhaseDialog,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  for (i=0; i<NLABELS; i++) {
    entries[i].label = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, rowcol,
      XtVaTypedArg, XmNlabelString, XmRString, entries[i].name, strlen(entries[i].name)+1,
      NULL);
#if (XmVERSION > 1) || (XmUPDATE_LEVEL > 3)
      XtVaGetValues(entries[i].label, XmNwidth, &w, NULL);
      if (w > wMax) wMax = w;
#endif
    entries[i].text =  XtVaCreateManagedWidget("Text", xmTextWidgetClass, rowcol,
      XmNcolumns,                CHAR_LENGTH,
      XmNmaxLength,              CHAR_LENGTH,
      XmNtraversalOn,            False,
      XmNeditable,               False, 
      XmNblinkRate,              0,
      XmNautoShowCursorPosition, True,
      XmNcursorPositionVisible,  False,
      NULL);
#if (XmVersion > 1) || (XmUPDATE_LEVEL > 3)
      XtVaGetValues(entries[i].text, XmNheight, &h, XmNwidth, &w, NULL);
      hSum += h;
      if (w > wMax) wMax = w;
#endif
  }

  XtManageChild(rowcol);
#if (XmVersion > 1) || (XmUPDATE_LEVEL > 3)
  XtVaGetValues(rowcol, XmNheight, &h, XmNwidth, &w, NULL);
  hSum += h; wSum += w;
#endif
  XtManageChild(form[0]);
#if (XmVersion > 1) || (XmUPDATE_LEVEL > 3)
  wSum += 2*wMax;
  XtVaSetValues(form[0], XmNheight, hSum, XmNwidth, wSum, NULL);
#endif

  /* lower most cell of the pane window (action area) */
  form[1] = XtVaCreateWidget("Form", xmFormWidgetClass, pane, XmNfractionBase, 5, NULL);

  dismissButton = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, form[1],
    XtVaTypedArg, XmNlabelString, XmRString, "Dismiss", strlen("Dismiss")+1,
    XmNshowAsDefault,    True,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  1,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 2,
    NULL);
  XtAddCallback(dismissButton, XmNactivateCallback, unmap_callback, NULL);
  moreButton = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, form[1],
    XtVaTypedArg, XmNlabelString, XmRString, "System", strlen("System")+1,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  3,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 4,
    NULL);
  XtAddCallback(moreButton, XmNactivateCallback, map_callback, NULL);

  XtManageChild(form[1]);
  XtVaGetValues(dismissButton, XmNheight, &h, NULL);
  XtVaSetValues(form[1],   XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);

  XtManageChild(pane);
  {
    Widget *children;
    int    num_children;
    XtVaGetValues(pane, XmNchildren, &children, XmNnumChildren, &num_children, NULL);
    while (num_children-- > 0) if (XtIsSubclass(children[num_children], xmSashWidgetClass)) XtVaSetValues(children[num_children], XmNtraversalOn, False, NULL);
  }

  XtManageChild(formDialog);
}

static double getLiquidProperties(int nl, double *value)
{
  double *m, mass, moles, *r;
  int i, na, nr;

  na = nlc;
  nr = nlc - 1;

  m = (double *) malloc((size_t) na*sizeof(double));
  r = (double *) malloc((size_t) nr*sizeof(double));
  mass = silminState->liquidMass;
  for (i=0, moles=0.0; i<na; i++) {
    m[i]  = (silminState->liquidComp)[nl][i]; moles += m[i];
  }
  (*conLiq)(SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL);

  /* The Gibbs energy of the phase (J)    */
  (*gmixLiq)(FIRST, silminState->T, silminState->P, r, &value[0], NULL, NULL);
  for (i=0, value[0] *= moles; i<na; i++) value[0] += m[i]*liquid[i].cur.g;

  /* The Enthalpy of the phase (J)        */
  (*hmixLiq)(FIRST, silminState->T, silminState->P, r, &value[1], NULL);
  for (i=0, value[1] *= moles; i<na; i++) value[1] += m[i]*liquid[i].cur.h;

  /* The Entropy of the phase (J/K)       */
  (*smixLiq)(FIRST, silminState->T, silminState->P, r, &value[2], NULL, NULL, NULL);
  for (i=0, value[2] *= moles; i<na; i++) value[2] += m[i]*liquid[i].cur.s;

  /* The Volume of the phase (cc)         */
  (*vmixLiq)(FIRST, silminState->T, silminState->P, r, &value[3], NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  for (i=0, value[3] *= moles; i<na; i++) value[3] += m[i]*liquid[i].cur.v;
  value[3] *= 10.0; /* joules/bar -> cc */

  /* The Heat Capacity of the phase (J/K) */
  (*cpmixLiq)(FIRST, silminState->T, silminState->P, r, &value[4], NULL, NULL);
  for (i=0, value[4] *= moles; i<na; i++) value[4] += m[i]*liquid[i].cur.cp;

  /* The Density of the phase (gm/cc)     */
  value[5] = (value[3] == 0.0) ? 0.0 : mass/value[3]; 

  /* The Viscosity of the phase (log poise)   */
  (*visLiq)(FIRST, silminState->T, silminState->P, r, &value[6]);

  free(m); if (na > 1) free(r);
  return mass;
}


static double getSolidProperties(int index, int ns, double *value)
{
  double *m, mass, moles, *r = NULL;
  int i, na, nr;

  na = solids[index].na;
  nr = solids[index].nr;

  m = (double *) malloc((size_t) na*sizeof(double));
  if (na == 1) {
    m[0]  = (silminState->solidComp)[index][ns];
    if ((silminState->fractionateSol || silminState->fractionateFlu) && ((silminState->fracSComp)[index] != NULL)) 
      m[0] += (silminState->fracSComp)[index][ns];
    mass  = m[0]*solids[index].mw; 
    moles = m[0];
  } else {
    for (i=0, mass=0.0, moles=0.0; i<na; i++) {
      m[i]   = (silminState->solidComp)[index+1+i][ns];
      if ((silminState->fractionateSol || silminState->fractionateFlu) && ((silminState->fracSComp)[index+1+i] != NULL)) 
        m[i] += (silminState->fracSComp)[index+1+i][ns]; 
      mass  += m[i]*solids[index+1+i].mw;
      moles += m[i]; 
    }
    r = (double *) malloc((size_t) nr*sizeof(double));
    (*solids[index].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
  }

  /* The Gibbs energy of the phase (J)    */
  if (na == 1) value[0] = m[0]*solids[index].cur.g;
  else {
    (*solids[index].gmix)(FIRST, silminState->T, silminState->P, r, &value[0], NULL, NULL, NULL);
    value[0] *= moles;
    for (i=0; i<na; i++) value[0] += m[i]*solids[index+1+i].cur.g;
  }

  /* The Enthalpy of the phase (J)        */
  if (na == 1) value[1] = m[0]*solids[index].cur.h;
  else {
    (*solids[index].hmix)(FIRST, silminState->T, silminState->P, r, &value[1]);
    value[1] *= moles;
    for (i=0; i<na; i++) value[1] += m[i]*solids[index+1+i].cur.h;
  }

  /* The Entropy of the phase (J/K)       */
  if (na == 1) value[2] = m[0]*solids[index].cur.s;
  else {
    (*solids[index].smix)(FIRST, silminState->T, silminState->P, r, &value[2], NULL, NULL);
    value[2] *= moles;
    for (i=0; i<na; i++) value[2] += m[i]*solids[index+1+i].cur.s;
  }

  /* The Volume of the phase (cc)         */
  if (na == 1) value[3] = m[0]*solids[index].cur.v;
  else {
    (*solids[index].vmix)(FIRST, silminState->T, silminState->P, r, &value[3], NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL);
    value[3] *= moles;
    for (i=0; i<na; i++) value[3] += m[i]*solids[index+1+i].cur.v;
  }
  value[3] *= 10.0; /* joules/bar -> cc */

  /* The Heat Capacity of the phase (J/K) */
  if (na == 1) value[4] = m[0]*solids[index].cur.cp;
  else {
    (*solids[index].cpmix)(FIRST, silminState->T, silminState->P, r, &value[4], NULL, NULL);
    value[4] *= moles;
    for (i=0; i<na; i++) value[4] += m[i]*solids[index+1+i].cur.cp;
  }

  /* The Density of the phase (gm/cc)     */
  value[5] = (value[3] == 0.0) ? 0.0 : mass/value[3]; 

  /* The Viscosity of the phase (poise)   */
  value[6] = 0.0;

  free(m); if (na > 1) free(r);
  return mass;
}

static void map_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  XmAnyCallbackStruct *cbData = (XmAnyCallbackStruct *) cbDataGen;
  static Boolean showSystem;
  double value[NLABELS];
  XmString csString1, csString2, csString3;
  char *output;
  int i;

  switch (cbData->reason) {

  case XmCR_ACTIVATE :
    if (!showSystem) {
      double temp[NLABELS], mass, volSol;
      int j, k, nl;
      int hasLiquid = (silminState->liquidMass != 0.0);
      showSystem = True;
      XtVaSetValues(moreButton, XtVaTypedArg, XmNlabelString, XmRString, curPhase, strlen(curPhase)+1, NULL);
      XtVaSetValues(labelPhaseDialog, XtVaTypedArg, XmNlabelString, XmRString, "Properties of System", strlen("Properties of System")+1, NULL);

      mass = 0.0;
      for (k=0; k<NLABELS; k++) value[k] = 0.0;
      
      if (hasLiquid) for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
        mass += getLiquidProperties(nl, temp);
        for (k=0; k<NLABELS; k++) value[k] += temp[k];
      }
      
      volSol = 0.0;
      for (i=0; i<npc; i++) for (j=0; j<(silminState->nSolidCoexist)[i]; j++) {
        mass += getSolidProperties(i, j, temp);
        for (k=0; k<NLABELS; k++) value[k] += temp[k];
        volSol += temp[3];
      }
      
      /* The Density of the system (gm/cc)     */
      value[5] = (value[3] == 0.0) ? 0.0 : mass/value[3]; 
      /* The Viscosity of the system (log poise)   A == 0.5 */
      value[6] = (volSol < 0.5*value[3]) ? value[6] - 2.0*log10(1.0 - 2.0*volSol/value[3]) : 0.0;

      output = (char *) malloc((size_t) ((CHAR_LENGTH+1)*sizeof(char)));
      for (i=0; i<NLABELS; i++) {
        if (value[i] != 0.0) (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, value[i]);
        else                 (void) snprintf(output, 2, "%s", " ");
        XmTextSetString(entries[i].text, output);
      }

      free(output);
      break;

    } else 
      XtVaSetValues(moreButton, XtVaTypedArg, XmNlabelString, XmRString, 
        "System", strlen("System")+1, NULL);

  case XmCR_MAP :
    showSystem = False;
    csString1  = XmStringCreateLtoR("Properties of ", "ISO8859-1");
    csString2  = XmStringCreateLtoR(curPhase, "ISO8859-1");
    csString3  = XmStringConcat(csString1, csString2); 
    XmStringFree(csString1); 
    XmStringFree(csString2);
    XtVaSetValues(labelPhaseDialog, XmNlabelString, csString3, NULL);
    XmStringFree(csString3);

    if (curPhaseIndex < npc) (void) getSolidProperties (curPhaseIndex, curPhaseNS, value);
    else                     (void) getLiquidProperties(               curPhaseNL, value);

    output = (char *) malloc((size_t) ((CHAR_LENGTH+1)*sizeof(char)));
    for (i=0; i<NLABELS; i++) {
      if (value[i] != 0.0) (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, value[i]);
      else                 (void) snprintf(output, 2, "%s", " ");
      XmTextSetString(entries[i].text, output);
    }

    free(output);
    break;

  default:
    break;
  }

}

static void unmap_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  XmAnyCallbackStruct *cbData = (XmAnyCallbackStruct *) cbDataGen;

  switch (cbData->reason) {

  case XmCR_ACTIVATE :
    XtVaSetValues(moreButton, XtVaTypedArg, XmNlabelString, XmRString, "System", strlen("System")+1, NULL);
    XtUnmanageChild(formDialog);
    break;

  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;

  default:
    break;

  }
}

#undef NLABELS

/*
 *=============================================================================
 * Routines to create and manage the status attached dialog box
 */

#define STATUS_ADB_MAX  11
#define MIDWAY          65
#define SPACER           6
#define DRAW_A_WIDTH   200
#define DRAW_A_HEIGHT   20

static void logfo2_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void redraw(Widget w, XtPointer cData, XtPointer cbDataGen);

static int k_tag_logfo2_value = LOGFO2_UNITS_VALUE;
static int k_tag_logfo2_hm    = LOGFO2_UNITS_HM;
static int k_tag_logfo2_nno   = LOGFO2_UNITS_NNO;
static int k_tag_logfo2_qfm   = LOGFO2_UNITS_QFM;
static int k_tag_logfo2_coh   = LOGFO2_UNITS_COH;
static int k_tag_logfo2_iw    = LOGFO2_UNITS_IW;

static Widget logfo2_scale;

typedef struct _statusButtons {
  Widget    w;
  GC        gc;
  Pixmap    pixmap;
  Dimension width;
  Dimension height;
} StatusButtons;

static StatusButtons *statusButtons;

typedef struct _stages {
  const char   *label;
  Widget w;
} Stages;

static Stages stages[] = {
  { "Wait"    },
  { "Blk Cmp" },  
  { "T/P"     },
  { "Satn Ck" },
  { "Add Ph"  }, 
  { "Proj"    },  
  { "Pre-Q"   },
  { "Con-Q"   },  
  { "Quad"    },  
  { "Soln"    },
  { "Linear"  },  
  { "Satn Ck" },
  { "Conv"    },
  { "Verify"  }, 
  { "Output"  },
  { "Update"  }
};
static int nStages = sizeof(stages)/sizeof(struct _stages);

#define MAKE_DRAW(index, top, right) \
  statusButtons[index].width  = DRAW_A_WIDTH; \
  statusButtons[index].height = DRAW_A_HEIGHT; \
  statusButtons[index].w \
    = XtVaCreateManagedWidget ("drawingArea", xmDrawingAreaWidgetClass, form[0], \
      XmNwidth,           statusButtons[index].width, \
      XmNheight,          statusButtons[index].height, \
      XmNresizePolicy,    XmNONE, \
      XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,   (top), \
      XmNrightAttachment, XmATTACH_POSITION, XmNrightPosition, (right), \
      NULL); \
  XtAddCallback (statusButtons[index].w, XmNexposeCallback, redraw, &(statusButtons[index])); \
  statusButtons[index].gc = XCreateGC (XtDisplay (topLevel), RootWindowOfScreen (XtScreen (topLevel)), GCForeground, &gcv); \
  statusButtons[index].pixmap \
    = XCreatePixmap (XtDisplay (topLevel), RootWindowOfScreen (XtScreen (topLevel)), \
        statusButtons[index].width, statusButtons[index].height, DefaultDepthOfScreen (XtScreen (topLevel))); \
  XSetForeground (XtDisplay (topLevel), statusButtons[index].gc, gray); \
  XFillRectangle (XtDisplay (topLevel), statusButtons[index].pixmap, \
    statusButtons[index].gc, 0, 0, statusButtons[index].width, \
    statusButtons[index].height);

static void create_status_adb()
{
  static Widget pushBG[6], form[2], frame[2], labelG[12], logfo2_units_menu, 
    logfo2_units, scrolled_w, rowcol;
  XmString csString, subString1, subString2;
  XmFontList      fontlist1, fontlist2;
  XmFontContext   context;
  XmStringCharSet charset;
  XFontStruct     *font1, *font2;
  unsigned long   ptSize;
  char            fontName[] = { "-*-symbol-*-*-*--*-XXX-*-*-*-*-*" };
  XGCValues       gcv;
  int i;

  statusEntries = (StatusEntries *) malloc((size_t) STATUS_ADB_MAX*sizeof(StatusEntries));
  statusButtons = (StatusButtons *) malloc((size_t) STATUS_ADB_MAX*sizeof(StatusButtons));
  gcv.foreground = WhitePixelOfScreen (XtScreen (topLevel));

  frame[0] = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, silmin_adb,
    XmNtopAttachment,    XmATTACH_FORM, 
    XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, TOP_USER,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,   RIGHT_PHASE,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  form[0] = XtVaCreateWidget("Form", xmFormWidgetClass, frame[0], NULL);
  XtVaGetValues(form[0], XmNbuttonFontList, &fontlist1, NULL);

  (void) XmFontListInitFontContext(&context, fontlist1);   /* must exist */
  (void) XmFontListGetNextFont(context, &charset, &font1); /* must exist */
  XmFontListFreeFontContext(context);

  if (!XGetFontProperty(font1, XA_POINT_SIZE, &ptSize)) ptSize = 120;
  (void) snprintf(fontName, 33, "-*-symbol-*-*-*--*-%u-*-*-*-*-*", (unsigned int) ptSize);
  font2 = XLoadQueryFont(XtDisplay(topLevel), fontName);

  fontlist2 = XmFontListCopy(fontlist1);
  if (font2 != NULL) fontlist2 = XmFontListAdd(fontlist2, font2, "symbol");
  else               fontlist2 = XmFontListAdd(fontlist2, font1, "symbol");
  XtVaSetValues(form[0], XmNbuttonFontList, fontlist2, NULL); 
  XtVaSetValues(form[0], XmNlabelFontList,  fontlist2, NULL); 

  labelG[0] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0], 
    XtVaTypedArg,      XmNlabelString,     XmRString, "System:",  (int) (strlen("System:")+1),
    XmNtopAttachment,  XmATTACH_FORM,
    XmNleftAttachment, XmATTACH_FORM,
    NULL);
  labelG[1] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0], 
    XtVaTypedArg,      XmNlabelString,     XmRString, "T (C)",    (int) (strlen("T (C)")+1),
    XmNtopAttachment,  XmATTACH_POSITION,  XmNtopPosition,  SPACER,
    XmNleftAttachment, XmATTACH_FORM,
    NULL);
  labelG[2] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XtVaTypedArg,      XmNlabelString,     XmRString, "P (bars)", (int) (strlen("P (bars)")+1),
    XmNtopAttachment,  XmATTACH_POSITION,  XmNtopPosition,  2*SPACER,
    XmNleftAttachment, XmATTACH_FORM,
    NULL);

  logfo2_units_menu = XmCreatePulldownMenu(form[0], "PulldownMenu", NULL, 0);

  csString  = XmStringCreate("log10", charset);
  pushBG[0] = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, logfo2_units_menu,
              XmNfontList,    fontlist2,
              XmNlabelString, csString,
              XmNmnemonic,    'l',
              NULL);
  XmStringFree(csString);

  subString1 = XmStringCreate("D",  "symbol");

  subString2 = XmStringCreate("HM", charset);
  csString   = XmStringConcat(subString1, subString2); XmStringFree(subString2);
  pushBG[1]  = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, logfo2_units_menu,
               XmNfontList,    fontlist2,
               XmNlabelString, csString,
               XmNmnemonic,    'H',
               NULL);
  XmStringFree(csString);

  subString2 = XmStringCreate("NNO", charset);
  csString   = XmStringConcat(subString1, subString2); XmStringFree(subString2);
  pushBG[2]  = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, logfo2_units_menu,
               XmNfontList,    fontlist2,
               XmNlabelString, csString,
               XmNmnemonic,    'N',
               NULL);
  XmStringFree(csString);

  subString2 = XmStringCreate("QFM", charset);
  csString   = XmStringConcat(subString1, subString2); XmStringFree(subString2);
  pushBG[3]  = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, logfo2_units_menu,
               XmNfontList,    fontlist2,
               XmNlabelString, csString,
               XmNmnemonic,    'Q',
               NULL);
  XmStringFree(csString);

  subString2 = XmStringCreate("C-COH", charset);
  csString   = XmStringConcat(subString1, subString2); XmStringFree(subString2);
  pushBG[4]  = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, logfo2_units_menu,
               XmNfontList,    fontlist2,
               XmNlabelString, csString,
               XmNmnemonic,    'C',
               NULL);
  XmStringFree(csString);

  subString2 = XmStringCreate("IW", charset);
  csString   = XmStringConcat(subString1, subString2); XmStringFree(subString2);
  pushBG[5]  = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, logfo2_units_menu,
               XmNfontList,    fontlist2,
               XmNlabelString, csString,
               XmNmnemonic,    'I',
               NULL);
  XmStringFree(csString); XmStringFree(subString1);

  XmFontListFree(fontlist2);
  XtFree(charset);

  {
  long longTag = (long) k_tag_logfo2_value;
  XtAddCallback(pushBG[0],   XmNactivateCallback, logfo2_callback, (XtPointer) longTag);
  longTag = (long) k_tag_logfo2_hm;  
  XtAddCallback(pushBG[1],   XmNactivateCallback, logfo2_callback, (XtPointer) longTag);
  longTag = (long) k_tag_logfo2_nno;  
  XtAddCallback(pushBG[2],   XmNactivateCallback, logfo2_callback, (XtPointer) longTag);
  longTag = (long) k_tag_logfo2_qfm;  
  XtAddCallback(pushBG[3],   XmNactivateCallback, logfo2_callback, (XtPointer) longTag);
  longTag = (long) k_tag_logfo2_coh;  
  XtAddCallback(pushBG[4],   XmNactivateCallback, logfo2_callback, (XtPointer) longTag);
  longTag = (long) k_tag_logfo2_iw;  
  XtAddCallback(pushBG[5],   XmNactivateCallback, logfo2_callback, (XtPointer) longTag);
  }
  units_logfo2_display = k_tag_logfo2_value;            /* default entry */

  csString = XmStringCreateLtoR("fO2:", "ISO8859-1");
  {
    Arg args[9]; 
    XtSetArg(args[0], XmNsubMenuId,        logfo2_units_menu);
    XtSetArg(args[1], XmNlabelString,      csString);
    XtSetArg(args[2], XmNmnemonic,         'f');
    XtSetArg(args[3], XmNmenuHistory,      pushBG[0]);
    XtSetArg(args[4], XmNtopAttachment,    XmATTACH_POSITION);
    XtSetArg(args[5], XmNtopPosition,      (int) (3.5*((float) SPACER)));
    XtSetArg(args[6], XmNbottomAttachment, XmATTACH_NONE);
    XtSetArg(args[7], XmNleftAttachment,   XmATTACH_FORM);
    XtSetArg(args[8], XmNrightAttachment,  XmATTACH_NONE);
    logfo2_units = XmCreateOptionMenu(form[0], "OptionMenu", args, XtNumber(args));
    XtManageChild(logfo2_units);
  }
  XmStringFree(csString);

  labelG[3] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0], 
    XtVaTypedArg,      XmNlabelString,     XmRString,      
      "Mass (grams) of:", (int) (strlen("Mass (grams) of:")+1),
    XmNtopAttachment,  XmATTACH_FORM,
    XmNleftAttachment, XmATTACH_POSITION,  XmNleftPosition, 44,
    NULL);
  labelG[4] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0], 
    XtVaTypedArg,      XmNlabelString,     XmRString,       
      "liquid",        (int) (strlen("liquid")+1),
    XmNtopAttachment,  XmATTACH_POSITION,  XmNtopPosition,  SPACER,
    XmNleftAttachment, XmATTACH_POSITION,  XmNleftPosition, 44,
    NULL);
  labelG[5] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0], 
    XtVaTypedArg,      XmNlabelString,     XmRString,       
      "solids",        (int) (strlen("solids")+1),
    XmNtopAttachment,  XmATTACH_POSITION,  XmNtopPosition,  2*SPACER,
    XmNleftAttachment, XmATTACH_POSITION,  XmNleftPosition, 44,
    NULL);
  labelG[6] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0], 
    XtVaTypedArg,      XmNlabelString,     XmRString,       
      "assimilant",    (int) (strlen("assimilant")+1),
    XmNtopAttachment,  XmATTACH_POSITION,  XmNtopPosition,  3*SPACER,
    XmNleftAttachment, XmATTACH_POSITION,  XmNleftPosition, 44,
    NULL);
  labelG[7] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0], 
    XtVaTypedArg,      XmNlabelString,     XmRString,       
      "fractionated",  (int) (strlen("fractionated")+1),
    XmNtopAttachment,  XmATTACH_POSITION,  XmNtopPosition,  4*SPACER,
    XmNleftAttachment, XmATTACH_POSITION,  XmNleftPosition, 44,
    NULL);

  csString = XmStringCreateLtoR(" ", "ISO8859-1");

  statusEntries[STATUS_ADB_INDEX_T].name = XtVaCreateManagedWidget(
    "Label", xmLabelGadgetClass, form[0],
    XmNlabelString,     csString,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,   SPACER,
    XmNrightAttachment, XmATTACH_POSITION, XmNrightPosition, 42,
    NULL);
  statusEntries[STATUS_ADB_INDEX_P].name = XtVaCreateManagedWidget(
    "Label", xmLabelGadgetClass, form[0], 
    XmNlabelString,     csString,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,   2*SPACER,
    XmNrightAttachment, XmATTACH_POSITION, XmNrightPosition, 42,
    NULL);
  statusEntries[STATUS_ADB_INDEX_LOGFO2].name = XtVaCreateManagedWidget(
    "Label", xmLabelGadgetClass, form[0], 
    XmNlabelString,     csString,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,   (int) (3.8*((float) SPACER)),
    XmNrightAttachment, XmATTACH_POSITION, XmNrightPosition, 42,
    NULL);

  statusEntries[STATUS_ADB_INDEX_MASS_LIQUID].name = XtVaCreateManagedWidget(
    "Label", xmLabelGadgetClass, form[0], 
    XmNlabelString,     csString,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,   1*SPACER,
    XmNrightAttachment, XmATTACH_POSITION, XmNrightPosition, 67,
    NULL);
  MAKE_DRAW(STATUS_ADB_INDEX_MASS_LIQUID, 1*SPACER, 99)

  statusEntries[STATUS_ADB_INDEX_MASS_SOLID].name = XtVaCreateManagedWidget(
    "Label", xmLabelGadgetClass, form[0], 
    XmNlabelString,     csString,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,   2*SPACER,
    XmNrightAttachment, XmATTACH_POSITION, XmNrightPosition, 67,
    NULL);
  MAKE_DRAW(STATUS_ADB_INDEX_MASS_SOLID, 2*SPACER, 99)

  statusEntries[STATUS_ADB_INDEX_MASS_ASSIM].name = XtVaCreateManagedWidget(
    "Label", xmLabelGadgetClass, form[0], 
    XmNlabelString,     csString,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,   3*SPACER,
    XmNrightAttachment, XmATTACH_POSITION, XmNrightPosition, 67,
    NULL);
  MAKE_DRAW(STATUS_ADB_INDEX_MASS_ASSIM, 3*SPACER, 99)

  statusEntries[STATUS_ADB_INDEX_MASS_FRAC].name = XtVaCreateManagedWidget(
    "Label", xmLabelGadgetClass, form[0], 
    XmNlabelString,     csString,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,   4*SPACER,
    XmNrightAttachment, XmATTACH_POSITION, XmNrightPosition, 67,
    NULL);
  MAKE_DRAW(STATUS_ADB_INDEX_MASS_FRAC, 4*SPACER, 99)

  XmStringFree(csString);

  subString1 = XmStringCreate("D",  "symbol");
  subString2 = XmStringCreate("QFM", charset);
  csString   = XmStringConcat(subString1, subString2); 
  XmStringFree(subString1); XmStringFree(subString2);
  logfo2_scale = XtVaCreateManagedWidget("Scale", xmScaleWidgetClass, form[0],
    XmNminimum,          -500,
    XmNmaximum,          500,
    XmNdecimalPoints,    2,
    XmNorientation,      XmHORIZONTAL,
    XmNvalue,            0, 
    XmNshowValue,        True,
    XmNtitleString,      csString,
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition, 3*SPACER,
    XmNleftAttachment,   XmATTACH_WIDGET,   XmNleftWidget,  logfo2_units,
    NULL);
  XtAddCallback(logfo2_scale, XmNvalueChangedCallback, logfo2_callback, NULL);
  XmStringFree(csString);

  frame[1] = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, form[0],
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition,    6*SPACER,
    XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, MIDWAY,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  form[1] = XtVaCreateWidget("Form", xmFormWidgetClass, frame[1], NULL);

  labelG[8] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[1], 
    XtVaTypedArg,      XmNlabelString,     XmRString,       
      "Status of Calc:",  (int) (strlen("Status of Calc:")+1),
    XmNtopAttachment,  XmATTACH_FORM,
    XmNleftAttachment, XmATTACH_FORM,
    NULL);
  labelG[9] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[1], 
    XtVaTypedArg,      XmNlabelString,     XmRString,       
      "Iterations",  (int) (strlen("Iterations:")+1),
    XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition, 25,
    XmNleftAttachment, XmATTACH_FORM,
    NULL);
  labelG[10] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[1], 
    XtVaTypedArg,      XmNlabelString,     XmRString,       
      "Quad:",  (int) (strlen("Quad")+1),
    XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition, 50,
    XmNleftAttachment, XmATTACH_FORM,
    NULL);
  labelG[11] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[1], 
    XtVaTypedArg,      XmNlabelString,     XmRString,       
      "Lin:",  (int) (strlen("Lin:")+1),
    XmNtopAttachment,  XmATTACH_POSITION, XmNtopPosition, 75,
    XmNleftAttachment, XmATTACH_FORM,
    NULL);

  rowcol = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form[1],
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       3,
    XmNisHomogeneous,    True,
    XmNentryClass,       xmToggleButtonGadgetClass,
    XmNradioBehavior,    True,
    XmNmarginHeight,     0,
    XmNmarginWidth,      0,
    XmNspacing,          0, 
    XmNpacking,          XmPACK_COLUMN,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  for (i=0; i<nStages; i++) stages[i].w = XtVaCreateManagedWidget("Toggle", xmToggleButtonGadgetClass, rowcol, 
        XtVaTypedArg, XmNlabelString, XmRString, stages[i].label,  (int) (strlen(stages[i].label)+1),
        XmNselectColor, red, 
        NULL);
  XmToggleButtonGadgetSetState(stages[0].w, True, True);
  XtManageChild(rowcol);

  csString = XmStringCreateLtoR(" ", "ISO8859-1");
  statusEntries[STATUS_ADB_INDEX_QUADRATIC].name = XtVaCreateManagedWidget(
    "Label", xmLabelGadgetClass, form[1],
    XmNlabelString,     csString,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,   50,
    XmNrightAttachment, XmATTACH_WIDGET,   XmNrightWidget,   rowcol,
    NULL);
  statusEntries[STATUS_ADB_INDEX_LINEAR].name = XtVaCreateManagedWidget(
    "Label", xmLabelGadgetClass, form[1],
    XmNlabelString,     csString,
    XmNtopAttachment,   XmATTACH_POSITION, XmNtopPosition,   75,
    XmNrightAttachment, XmATTACH_WIDGET,   XmNrightWidget,   rowcol,
    NULL);
  XmStringFree(csString);

  XtManageChild(form[1]);

  scrolled_w = XtVaCreateManagedWidget(
    "ScrolledWindow", xmScrolledWindowWidgetClass, form[0],
    XmNscrollingPolicy,        XmAPPLICATION_DEFINED,
    XmNvisualPolicy,           XmVARIABLE,
    XmNscrollBarDisplayPolicy, XmSTATIC,
    XmNshadowThickness,        0,
    XmNtopAttachment,          XmATTACH_POSITION, XmNtopPosition, MIDWAY, 
    XmNbottomAttachment,       XmATTACH_FORM,
    XmNleftAttachment,         XmATTACH_FORM,
    XmNrightAttachment,        XmATTACH_FORM,
    NULL);

  statusEntries[STATUS_ADB_INDEX_STATUS].name  = XtVaCreateManagedWidget(
    "Text", xmTextWidgetClass, scrolled_w,
    XmNeditable,               False,
    XmNeditMode,               XmMULTI_LINE_EDIT,
    XmNblinkRate,              0,
    XmNautoShowCursorPosition, True,
    XmNcursorPositionVisible,  False,
    NULL);

  wprintf(statusEntries[STATUS_ADB_INDEX_STATUS].name, "Waiting for command or user input.\n");

  XtManageChild(form[0]);
}

#undef MAKE_DRAW

static void redraw(Widget w, XtPointer client_data, XtPointer call_data)
{
    XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct *) call_data;
    StatusButtons *statusButtons = (StatusButtons *) client_data;
    Pixmap    pixmap = statusButtons->pixmap;
    GC        gc     = statusButtons->gc;
    Dimension width  = statusButtons->width;
    Dimension height = statusButtons->height;

    XCopyArea (cbs->event->xexpose.display, pixmap, cbs->window, gc, 0, 0, width, height, 0, 0);
}

static void logfo2_callback(Widget w, XtPointer cData, XtPointer cbDataGen) 
{
  long tag = (long) cData;
  XmPushButtonCallbackStruct *cbData = (XmPushButtonCallbackStruct *) cbDataGen;

  switch (cbData->reason) {

  case XmCR_ACTIVATE :
    units_logfo2_display = (int) tag;
    if (silminState != NULL) updateStatusADB(STATUS_ADB_INDEX_LOGFO2, &(silminState->fo2));
    break;
  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;
  default:
    break;

  }
}

#define UPDATE(index, value) \
  if ((value) != 0.0) { \
    (void) snprintf(statusEntry, 9, "%8.2f", (value)); \
    csString = XmStringCreateLtoR(statusEntry, "ISO8859-1"); \
  } else csString = XmStringCreateLtoR("", "ISO8859-1"); \
  i = 0; \
  XtSetArg(arg_set[i], XmNlabelString, csString); i++; \
  XtSetValues(statusEntries[index].name, arg_set, i); \
  XmStringFree(csString);

void updateStatusADB(int member, XtPointer ptValue)
{
  XmString csString;
  static char statusEntry[9];
  Arg arg_set[20];
  int i;

  if (member >= STATUS_ADB_INDEX_STRING) {
    member -= STATUS_ADB_INDEX_STRING;
    csString = XmStringCreateLtoR((char *) ptValue, "ISO8859-1");
    i = 0;
    XtSetArg(arg_set[i], XmNlabelString, csString); i++;
    XtSetValues(statusEntries[member].name, arg_set, i);
    XmStringFree(csString);
  } else if (member == STATUS_ADB_INDEX_LOGFO2) {
    double logfo2;

    logfo2 = *((double *) ptValue) - getlog10fo2(silminState->T, silminState->P, FO2_QFM);
    XmScaleSetValue(logfo2_scale, (int) (100.0*logfo2));

    if      (units_logfo2_display == LOGFO2_UNITS_HM)  logfo2 = *((double *) ptValue) - getlog10fo2(silminState->T, silminState->P, FO2_HM);
    else if (units_logfo2_display == LOGFO2_UNITS_NNO) logfo2 = *((double *) ptValue) - getlog10fo2(silminState->T, silminState->P, FO2_NNO);
    else if (units_logfo2_display == LOGFO2_UNITS_QFM) logfo2 = *((double *) ptValue) - getlog10fo2(silminState->T, silminState->P, FO2_QFM);
    else if (units_logfo2_display == LOGFO2_UNITS_COH) logfo2 = *((double *) ptValue) - getlog10fo2(silminState->T, silminState->P, FO2_COH);
    else if (units_logfo2_display == LOGFO2_UNITS_IW)  logfo2 = *((double *) ptValue) - getlog10fo2(silminState->T, silminState->P, FO2_IW);
    else                                               logfo2 = *((double *) ptValue);

    UPDATE(STATUS_ADB_INDEX_LOGFO2, logfo2)
  } else if (member == STATUS_ADB_INDEX_T) {
    UPDATE(STATUS_ADB_INDEX_T, *((double *) ptValue) - 273.15)
  } else if (member == STATUS_ADB_INDEX_MASS_LIQUID ||
             member == STATUS_ADB_INDEX_MASS_SOLID  ||
             member == STATUS_ADB_INDEX_MASS_ASSIM  ||
             member == STATUS_ADB_INDEX_MASS_FRAC)  {
    Dimension width;
    double fraction;

    UPDATE(member, *((double *) ptValue))

    XSetForeground (XtDisplay (topLevel), statusButtons[member].gc, gray);
    XFillRectangle (XtDisplay (topLevel), statusButtons[member].pixmap, statusButtons[member].gc, 0, 0, statusButtons[member].width, statusButtons[member].height);

    fraction = *((double *) ptValue) /100.0;
    width = (Dimension) (fraction *((double) statusButtons[member].width));
    XSetForeground (XtDisplay (topLevel), statusButtons[member].gc, red);
    XFillRectangle (XtDisplay (topLevel), statusButtons[member].pixmap, statusButtons[member].gc, 0, 0, width, statusButtons[member].height);

    XCopyArea (XtDisplay (statusButtons[member].w), statusButtons[member].pixmap, XtWindow (statusButtons[member].w), statusButtons[member].gc, 0, 0, 
      statusButtons[member].width, statusButtons[member].height, 0, 0);

  } else if (member == STATUS_ADB_INDEX_QUADRATIC ||
             member == STATUS_ADB_INDEX_LINEAR) {
    (void) snprintf(statusEntry, 9, "%d", *((int *) ptValue));
    csString = XmStringCreateLtoR(statusEntry, "ISO8859-1");
    i = 0;
    XtSetArg(arg_set[i], XmNlabelString, csString); i++;
    XtSetValues(statusEntries[member].name, arg_set, i);
    XmStringFree(csString);

  } else if (member == STATUS_ADB_INDEX_PHASE) {
    int index = *((int *) ptValue);
    XmToggleButtonGadgetSetState(stages[index].w, True, True); 

  } else if (member == STATUS_ADB_INDEX_P) {
    UPDATE(member, *((double *) ptValue))
  } else {
    printf("*****An illegal call has been made to updateStatusADB.\n");
  }
}

#undef UPDATE
#undef STATUS_ADB_MAX
#undef MIDWAY
#undef SPACER
#undef DRAW_A_WIDTH
#undef DRAW_A_HEIGHT

/* end of file CREATE_MANAGED.C */
