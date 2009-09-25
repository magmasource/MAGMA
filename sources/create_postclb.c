const char *create_postclb_ver(void) { return "$Id: create_postclb.c,v 1.2 2006/08/17 16:47:18 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: create_postclb.c,v $
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
 * Revision 3.5  1997/05/03  20:23:40  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:44  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:33:46  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  17:24:55  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  17:24:55  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Function to create the postclb_adb widget and its children
**      (file: CREATE_POSTCLB.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  September 5, 1990 Original Version
**      V1.1-0  Mark S. Ghiorso  July 8, 1991
**              Added T, P, and log fO2 graph widgets
**      V1.2-0  Mark S. Ghiorso  August 8, 1991
**              Added popup attached dialog box for residual statistics 
**              display
**      V1.2-1  Mark S. Ghiorso  August 9, 1991
**              Added color mixing widget callback to selections in
**              the residual popup attched dialog vList widget
**      V1.2-2  Mark S. Ghiorso  August 10, 1991
**              Added second popup attached dialog box for outlier
**              display
**      V1.2-3  Mark S. Ghiorso  August 30, 1991
**              Added globally known widget definitions
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  November 22, 1991
**              Reorganized the display and removed the popup dialogs
**      V2.0-3  Mark S. Ghiorso  January 4, 1992
**              (1) Altered resource declarations for graph wiidget from
**                  XtN -> GwN
**      V2.0-4  Mark S. Ghiorso  February 19, 1992
**              Removed global dependence on the variable i
**      V2.0-5  Mark S. Ghiorso  March 17, 1992
**              Added macros for non-DEC motif extensions
**      V2.0-6  Mark S. Ghiorso  March 27, 1992
**              Corrected non-ANSI casting violations (integers -> pointers)
**      V2.0-7  Mark S. Ghiorso  September 21, 1993
**              (1) XtFree -> XmStringFree
**              (2) Removed incorrect resources in creation of vframe widgets
**      V2.0-8  Mark S. Ghiorso  September 27, 1993
**              Added option to compile vheader and vlist widgets as
**              children of a drawingArea widget (Motif 1.2 problems)
**      V2.0-9  Mark S. Ghiorso  April 5, 1994
**              Added #ifdef __osf__ to fix 64 bit errors 
**--
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/LabelG.h>
#include <Xm/ScrollBar.h>

#include "interface.h"
#ifdef DRAWINGA_VLIST_PARENT
#include <Xm/DrawingA.h>
#else
#include "vframe.h"
#endif
#include "vheader.h"
#include "vlist.h"

/******************************************************************************
 * Globally known widgets declared extern in INTERFACE.H
 ******************************************************************************/

Widget postclb_adb, postclb_statistics, postclb_outliers;

/*
 *=============================================================================
 * Layout and macro definitions for create_postclb():
 *
 ------------------------------------------------------------------------------
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   	      postclb_statistics  	 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |                   					 		      |
 |------------------------------BOTTON_STAT-----------------------------------|
 |                                                                            |
 |                                                                            |
 |                             postclb_outliers                               |
 |                                                                            |
 |                                                                            |
 ------------------------------------------------------------------------------

 */

#define BOTTOM_STAT 75

static void create_padb1_postclb(void);
static void create_padb2_postclb(void);

static void vList_callback();

void create_postclb()
{
  postclb_adb = XtVaCreateWidget("Form", xmFormWidgetClass, main_window, NULL);
  create_padb1_postclb();
  create_padb2_postclb();
}

#define NLABELS              16

static int k_tag_vList_statistics = 1;

static void create_padb1_postclb(void)
{
  static Widget form, frame[2], hScroll, label, vframe, vheader, vScroll;
  /* postclb_statistics == vList */
  VListLabel headerLabel[NLABELS];
  static const char *columnLabels[NLABELS] = {
    "component", "N",         "aveDep",     "aveRes",     "avefO2",    
    "aveT",      "aveP",      "stdDep",     "stdRes",     "stdfO2",
    "stdT",      "stdP",      "rResDep",    "rResfO2",    "rResT", 
    "rResP"     
  };

  XmString csString;
  int i;

  frame[0] = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, postclb_adb,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_POSITION, XmNbottomPosition, BOTTOM_STAT,
    XmNrightAttachment,  XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    NULL);

  form = XtVaCreateWidget("Form", xmFormWidgetClass, frame[0], NULL);

  csString = XmStringCreateLtoR("Statistics for Melt Properties Calibration", "ISO8859-1");
  label = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form,
    XmNlabelString, csString,
    XmNtopAttachment,   XmATTACH_FORM,
    XmNrightAttachment, XmATTACH_FORM,
    XmNleftAttachment,  XmATTACH_FORM,
    NULL);
  XmStringFree(csString);

  frame[1] = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, form,
    XmNtopAttachment,    XmATTACH_WIDGET, XmNtopWidget, label,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
#ifdef DRAWINGA_VLIST_PARENT
  vframe = XtVaCreateManagedWidget("Vframe", xmDrawingAreaWidgetClass, frame[1],
    XmNmarginHeight,     0,
    XmNmarginWidth,      0,
    NULL);
#else
  vframe = XtVaCreateManagedWidget("Vframe", vframeWidgetClass, frame[1], 
    XmNborderWidth,      0,                              /* Motif compliance */
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

  vheader = XtVaCreateManagedWidget("Vheader", vheaderWidgetClass, vframe, 
    XmNborderWidth,      0,                              /* Motif compliance */
    NULL);

  for (i=0; i<NLABELS; i++) {
     headerLabel[i].mask       = VListLabelTextMask | VListLabelAlignmentMask;
     headerLabel[i].textP = (char *) malloc((size_t) (strlen(columnLabels[i])+1)*sizeof(char));
     (void) strcpy(headerLabel[i].textP, columnLabels[i]);
     headerLabel[i].alignment  = VListAlignmentCenter;
  }

  postclb_statistics = XtVaCreateManagedWidget(
    "Vlist", vlistWidgetClass, vframe, 
    XmNborderWidth,         0,                          /* Motif compliance */
    VListNcolumnStyle,      VListColumnStyleSingle,
    VListNfieldCount,       NLABELS,
    VListNlabelCount,       NLABELS,
    VListNlabels,           headerLabel,
    VListNhScrollBarWidget, hScroll,
    VListNvScrollBarWidget, vScroll,
    VListNheaderWidget,     vheader,
    VListNselectUnit,       VListSelectUnitField,
    NULL);
  {
  long longTag = (long) k_tag_vList_statistics;
  XtAddCallback(postclb_statistics, VListNselectConfirmCallback, vList_callback, (XtPointer) longTag);
  }

  XtManageChild(form);
}

#undef NLABELS

#define NLABELS               9

static int k_tag_vList_outliers   = 2;

static void create_padb2_postclb(void)
{
  static Widget form, frame[2], hScroll, label, vframe, vheader, vScroll;
  /* postclb_outliers == vList */
  VListLabel headerLabel[NLABELS];
  static const char *columnLabels[NLABELS] = {
     "component", "N liq", "stdDep", "stdRes", "log fO2", "T C", "P kbars", "Afn kJ", "Composition"
  };

  XmString csString;
  int i;

  frame[0] = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, postclb_adb,
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition, BOTTOM_STAT,
    XmNbottomAttachment, XmATTACH_FORM, 
    XmNrightAttachment,  XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    NULL);

  form = XtVaCreateWidget("Form", xmFormWidgetClass, frame[0], NULL);

  csString = XmStringCreateLtoR("Outliers", "ISO8859-1");
  label = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form,
    XmNlabelString, csString,
    XmNtopAttachment,   XmATTACH_FORM,
    XmNrightAttachment, XmATTACH_FORM,
    XmNleftAttachment,  XmATTACH_FORM,
    NULL);
  XmStringFree(csString);

  frame[1] = XtVaCreateManagedWidget("Frame", xmFrameWidgetClass, form,
    XmNtopAttachment,    XmATTACH_WIDGET, XmNtopWidget, label,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

#ifdef DRAWINGA_VLIST_PARENT
  vframe = XtVaCreateManagedWidget("Vframe", xmDrawingAreaWidgetClass, frame[1],
    XmNmarginHeight,     0,
    XmNmarginWidth,      0,
    NULL);
#else
  vframe = XtVaCreateManagedWidget("Vframe", vframeWidgetClass, frame[1], 
    XmNborderWidth,      0,                              /* Motif compliance */
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

  vheader = XtVaCreateManagedWidget("Vheader", vheaderWidgetClass, vframe, 
    XmNborderWidth,      0,                              /* Motif compliance */
    NULL);

  for (i=0; i<NLABELS; i++) {
     headerLabel[i].mask       = VListLabelTextMask | VListLabelAlignmentMask;
     headerLabel[i].textP = (char *) malloc((size_t) (strlen(columnLabels[i])+1)*sizeof(char));
     (void) strcpy(headerLabel[i].textP, columnLabels[i]);
     headerLabel[i].alignment  = VListAlignmentCenter;
  }

  postclb_outliers = XtVaCreateManagedWidget("Vlist", vlistWidgetClass, vframe, 
    XmNborderWidth,         0,                          /* Motif compliance */
    VListNcolumnStyle,      VListColumnStyleSingle,
    VListNfieldCount,       NLABELS,
    VListNlabelCount,       NLABELS,
    VListNlabels,           headerLabel,
    VListNhScrollBarWidget, hScroll,
    VListNvScrollBarWidget, vScroll,
    VListNheaderWidget,     vheader,
    VListNselectUnit,       VListSelectUnitField,
    NULL);
  {
  long longTag = (long) k_tag_vList_outliers;
  XtAddCallback(postclb_outliers, VListNselectConfirmCallback, vList_callback, (XtPointer) longTag);
  }

  XtManageChild(form);
}

static void vList_callback(Widget w, int tag, VListSelectCallbackStruct *callback_data)
{
  switch (callback_data->reason) {

  case VListCRSelect:
    break;

  case VListCRSelectConfirm:
    break;

  default:
    break;

  }
}

/* end of file CREATE_POSTCLB.C */
