const char *create_assimilant_padb_ver(void) { return "$Id: create_assimilant_padb.c,v 1.2 2006/08/17 16:47:18 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: create_assimilant_padb.c,v $
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
MELTS Source Code: RCS Revision 1.2  2004/12/03 22:59:51  cvsaccount
MELTS Source Code: RCS *** empty log message ***
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
 * Revision 3.6  1997/06/21  22:50:06  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:23:42  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:46  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:33:52  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  17:22:26  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  17:22:26  ghiorso
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
**        assimilant composition for the silmin interface
**
**      Defines callback routines for all children
**      (file: CREATE_ASSIMILANT_PADB.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  September 6, 1990   Original Version
**      V1.0-1  Mark S. Ghiorso  August 30, 1991
**              (1) Added private definition of ADD_BUTTON macro
**              (2) Added globally known widget definitions
**      V1.1-0  Mark S. Ghiorso  September 3, 1991
**              (1) Made phase selection dependent upon solid structure
**                  in silmin.h
**              (2) Added global macro defintions for extra widgets
**      V1.1-1  Mark S. Ghiorso  September 4, 1991
**              (1) Added global assimilantUnits structure
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V3.0-1  Mark S. Ghiorso  December 8. 1991
**              Complete revision and incorporation of magma_padb code
**                               December 17, 1991
**              Finished first working version
**      V3.0-2  Mark S. Ghiorso  January 10, 1992
**              Changed default units button to weight %
**      V3.0-3  Mark S. Ghiorso  January 15, 1992
**              (1) Added public function updateAssimilantPADB(char *member);
**      V3.0-4  Mark S. Ghiorso  January 28, 1992
**              (1) Altered arg[] initialization at line 244 to be compliant
**                  with RISC C compiler stipulation of constant initializers
**                  in this context
**      V3.0-5  Mark S. Ghiorso  March 24, 1992
**              (1) Corrected call to XmListDeleteItem (wrong argument number)
**              (2) Added macro to control DEBUG output
**      V3.0-6  Mark S. Ghiorso  March 27, 1992
**              Corrected a series of casting violations related to ANSI C
**              compliance of Xt routines
**      V3.0-7  Mark S. Ghiorso  April 23, 1992
**              Corrected errors in text_callback algorithm
**      V3.0-8  Mark S. Ghiorso  September 28, 1992
**              Corrected calls to XtFree() => free() for allocations made
**              with malloc()
**      V3.0-9  Mark S. Ghiorso  September 29, 1992
**              Converted TextField to Text widgets as a bug workaround 
**              for DECWindows Motif V 1.1
**      V3.0-10 Mark S. Ghiorso  September 29, 1993
**              Modified call to realloc to catch zero pointer (SPARC port)
**      V3.0-11 Mark S. Ghiorso  April 23, 1994
**              Corrected casting violations for callbacks
**--
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Xm/Form.h>
#include <Xm/LabelG.h>
#include <Xm/List.h>
#include <Xm/PanedW.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/Separator.h>
#include <Xm/SashP.h>     /* We need to stop keyboard traversal on the sashes */
#include <Xm/ScrolledW.h>
#include <Xm/Text.h>

#include "interface.h"            /*Specific external declarations          */
#include "silmin.h"               /*Global SILMIN structures                */

#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))

#ifdef DEBUG
#undef DEBUG
#endif

/******************************************************************************
 * Globally known widgets and symbols declared as extern in INTERFACE.H
 ******************************************************************************/

Widget assimilant_padb;

AssimilantValues *assimilantValues;
AssimilantUnits   assimilantUnits;

#define CHAR_LENGTH 8
#define ENTRIES     3

static void map_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void button_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void text_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void list_add_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void list_del_callback(Widget w, XtPointer cData, XtPointer cbDataGen);

enum buttonList { K_VOLUME_PERCENT, 
                  K_WEIGHT_PERCENT,
                  K_DELETE_PHASE,   
                  K_ADD_PHASE,
                  K_DONE,
                  K_CLEAR,
                  k_HELP };

static Widget buttonU[2], *labelC, labelP, labelU, listA, listD, optionU, 
              *textC, textP, textT[3];

void create_assimilant_padb()
{
  int i, j;
  Dimension h;
  static Widget actionArea, pane, hSeparator[3], sPane, vSeparator, workArea;

  /* allocate storage and default constants */
  assimilantValues = (AssimilantValues *) calloc((unsigned) (npc+nc+4), 
    sizeof(AssimilantValues));
  for (i=0; i<4; i++) assimilantValues[npc+nc+i].value = 
    (double *) calloc((unsigned) 1, sizeof(double));
  assimilantUnits.units = ASSIM_PADB_UNITS_WEIGHT;

  /* pop up form dialog box */
  {
    Arg args[] = { { XmNdialogStyle,     XmDIALOG_FULL_APPLICATION_MODAL },
                   { XmNdefaultPosition, True                            },
                   { XmNautoUnmanage,    False                           },
		   { XmNheight,          750                             },
		   { XmNwidth,           650                             } };
    assimilant_padb = XmCreateFormDialog(silmin_adb, "FormDialog", args,
      XtNumber(args));
    XtAddCallback(assimilant_padb, XmNmapCallback, map_callback, NULL);
    XtVaSetValues(XtParent(assimilant_padb),
      XmNdeleteResponse, XmUNMAP, XmNtitle, "Assimilant",
      NULL);
  }

  /***************************************************************************
   * create a Scrolled Window to hold teh dialog just in case the user has a
   * tiny monitor      
   ***************************************************************************/
  sPane = XtVaCreateWidget("sPane", xmScrolledWindowWidgetClass, assimilant_padb,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
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

  /* *************************************************************************
   * Working area of the pane window and vertical separator
   ***************************************************************************/
  workArea = XtVaCreateWidget("Form", xmFormWidgetClass, pane, NULL);
  vSeparator = XtVaCreateManagedWidget(
    "Separator", xmSeparatorWidgetClass, workArea,
    XmNorientation,      XmVERTICAL,
    XmNtopAttachment,    XmATTACH_FORM,                         
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition, 50,
    NULL);

  /*************************************************************************** 
   * Components in assimilant form box and horizontal separator
   ***************************************************************************/
  {
  static Widget form, label, rowcol, labelRC;
  form = XtVaCreateWidget("Form", xmFormWidgetClass, workArea, 
    XmNtopAttachment,    XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_WIDGET,  XmNleftWidget,  vSeparator,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  label = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form,
    XtVaTypedArg, XmNlabelString, XmRString, "Components in Selected Phase:",
      strlen("Components in Selected Phase:")+1,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  rowcol = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form,
    XmNpacking,          XmPACK_COLUMN,
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       nc+1,
    XmNisAligned,        True,
    XmNentryAlignment,   XmALIGNMENT_END,
    XmNtopAttachment,    XmATTACH_WIDGET,   XmNtopWidget,      label,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  labelC = (Widget *) malloc((unsigned) nc*sizeof(Widget));
  textC  = (Widget *) malloc((unsigned) nc*sizeof(Widget));

  labelRC = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, rowcol,
    XtVaTypedArg, XmNlabelString, XmRString, "Component", strlen("Component")+1,
      NULL);
  labelU  = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, rowcol,
    XtVaTypedArg, XmNlabelString, XmRString, "wt %", strlen("wt %")+1,
      NULL);

  for (j=0; j<nc; j++) {
    labelC[j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, rowcol,
      XtVaTypedArg, XmNlabelString, XmRString, " ", strlen(" ")+1,
      NULL);
    textC[j] = XtVaCreateManagedWidget(
      "Text", xmTextWidgetClass, rowcol,
#ifdef WHITE_TEXTW
      XmNbackground,       white,
#endif
      XmNcolumns,          CHAR_LENGTH,
      XmNmaxLength,        CHAR_LENGTH,
      XmNnavigationType,   XmNONE,
      XmNtraversalOn,      True,
      NULL);
    XtAddCallback(textC[j], XmNactivateCallback, (XtCallbackProc) XmProcessTraversal, (XtPointer) XmTRAVERSE_NEXT);
    {
    long jLong = (long) j;
    XtAddCallback(textC[j], XmNlosingFocusCallback,  text_callback, (XtPointer) jLong);
    XtAddCallback(textC[j], XmNmodifyVerifyCallback, text_callback, (XtPointer) jLong);
    XtAddCallback(textC[j], XmNvalueChangedCallback, text_callback, (XtPointer) jLong);
    }
  }
  XtManageChild(rowcol);
  XtManageChild(form);
  hSeparator[0] = XtVaCreateManagedWidget(
    "Separator", xmSeparatorWidgetClass, workArea,
    XmNtopAttachment,    XmATTACH_WIDGET,   XmNtopWidget,      form,
    XmNleftAttachment,   XmATTACH_WIDGET,   XmNleftWidget,     vSeparator,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  }
  /*************************************************************************** 
   * Proportion of phase in assimilant form box 
   ***************************************************************************/
  {
  static Widget form, label, menu, rowcol;
  XmString csString;
  form = XtVaCreateWidget("Form", xmFormWidgetClass, workArea, 
    XmNtopAttachment,    XmATTACH_WIDGET,   XmNtopWidget,      hSeparator[0],
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_WIDGET,   XmNleftWidget,     vSeparator,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  label = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form,
    XtVaTypedArg, XmNlabelString, XmRString, 
      "Proportion of Selected Phase in Assimilant:",
      strlen("Proportion of Selected Phase in Assimilant:")+1,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  menu = XmCreatePulldownMenu(form, "PulldownMenu", NULL, 0);
  buttonU[ASSIM_PADB_UNITS_VOLUME] = 
    XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, menu,
    XtVaTypedArg, XmNlabelString, XmRString, "vol %", strlen("vol %")+1,
    XmNmnemonic,  'v',
    NULL);
  XtAddCallback(buttonU[ASSIM_PADB_UNITS_VOLUME], XmNactivateCallback, 
    button_callback, (XtPointer) K_VOLUME_PERCENT);
  buttonU[ASSIM_PADB_UNITS_WEIGHT] =
    XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, menu,
    XtVaTypedArg, XmNlabelString, XmRString, "wt %", strlen("wt %")+1,
    XmNmnemonic,  'w',
    NULL);
  XtAddCallback(buttonU[ASSIM_PADB_UNITS_WEIGHT], XmNactivateCallback, 
    button_callback, (XtPointer) K_WEIGHT_PERCENT);
  csString = XmStringCreateLtoR("units: ", "ISO8859-1");
  {
    Arg args[7];
    XtSetArg(args[0], XmNsubMenuId,       menu);
    XtSetArg(args[1], XmNlabelString,     csString);
    XtSetArg(args[2], XmNmnemonic,        'u');
    XtSetArg(args[3], XmNmenuHistory,     buttonU[ASSIM_PADB_UNITS_WEIGHT]);
    XtSetArg(args[4], XmNtopAttachment,   XmATTACH_WIDGET);
    XtSetArg(args[5], XmNtopWidget,       label);
    XtSetArg(args[6], XmNrightAttachment, XmATTACH_FORM);
    optionU = XmCreateOptionMenu(form, "OptionMenu", args, XtNumber(args));
    XtManageChild(optionU);
  }
  XmStringFree(csString);

  rowcol = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form,
    XmNpacking,          XmPACK_COLUMN,
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       1,
    XmNisAligned,        True,
    XmNentryAlignment,   XmALIGNMENT_END,
    XmNtopAttachment,    XmATTACH_WIDGET,  
    XmNtopWidget,        optionU,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  labelP = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, rowcol,
    XtVaTypedArg, XmNlabelString, XmRString, " ", strlen(" ")+1,
    NULL);
  textP  = XtVaCreateManagedWidget("Text", xmTextWidgetClass, rowcol,
#ifdef WHITE_TEXTW
    XmNbackground,       white,
#endif
    XmNcolumns,          CHAR_LENGTH,
    XmNmaxLength,        CHAR_LENGTH,
    NULL);
  {
  long tempLong = (long) (nc+ENTRIES);
  XtAddCallback(textP, XmNlosingFocusCallback,  text_callback, (XtPointer) tempLong);
  XtAddCallback(textP, XmNmodifyVerifyCallback, text_callback, (XtPointer) tempLong);
  XtAddCallback(textP, XmNvalueChangedCallback, text_callback, (XtPointer) tempLong);
  }

  XtManageChild(rowcol);

  XtManageChild(form);
  }

  /*************************************************************************** 
   *  Assimilant properties form box and vertical separator
   ***************************************************************************/
  {
  static Widget form, label, labelRC[ENTRIES], rowcol;
  const char *strings[ENTRIES] = { "Mass (grams)", "T (C)", "Increments" };
  int j;
  form = XtVaCreateWidget("Form", xmFormWidgetClass, workArea, 
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_WIDGET,   XmNrightWidget,    vSeparator,
    NULL);
  label = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form,
    XtVaTypedArg, XmNlabelString, XmRString, "Total Assimilant:",
      strlen("Total Assimilant:")+1,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  rowcol = XtVaCreateWidget("RowColumn", xmRowColumnWidgetClass, form,
    XmNpacking,          XmPACK_COLUMN,
    XmNorientation,      XmHORIZONTAL,
    XmNnumColumns,       ENTRIES,
    XmNisAligned,        True,
    XmNentryAlignment,   XmALIGNMENT_END,
    XmNtopAttachment,    XmATTACH_WIDGET,   XmNtopWidget,      label,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  for (j=0; j<ENTRIES; j++) {
    labelRC[j] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, rowcol,
      XtVaTypedArg, XmNlabelString, XmRString, strings[j], strlen(strings[j])+1,
      NULL);
    textT[j]   = XtVaCreateManagedWidget(
      "Text", xmTextWidgetClass, rowcol,
#ifdef WHITE_TEXTW
      XmNbackground,       white,
#endif
      XmNcolumns,          CHAR_LENGTH,
      XmNmaxLength,        CHAR_LENGTH,
      XmNnavigationType,   XmNONE,
      XmNtraversalOn,      True,
      NULL);
    XtAddCallback(textT[j], XmNactivateCallback,     
      (XtCallbackProc) XmProcessTraversal, (XtPointer) XmTRAVERSE_NEXT);
    {
    long tempLong = (long) (nc+j);
    XtAddCallback(textT[j], XmNlosingFocusCallback,  text_callback, (XtPointer) tempLong);
    XtAddCallback(textT[j], XmNmodifyVerifyCallback, text_callback, (XtPointer) tempLong);
    XtAddCallback(textT[j], XmNvalueChangedCallback, text_callback, (XtPointer) tempLong);
    }
  }
  XtManageChild(rowcol);
  XtManageChild(form);
  hSeparator[1] = XtVaCreateManagedWidget(
    "Separator", xmSeparatorWidgetClass, workArea,
    XmNbottomAttachment, XmATTACH_WIDGET,   XmNbottomWidget,   form,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_WIDGET,   XmNrightWidget,    vSeparator,
    NULL);
  }
  /*************************************************************************** 
   * Phases in assimilant form box and horizontal separator
   ***************************************************************************/
  { 
  static Widget form, label, button;
  form = XtVaCreateWidget("Form", xmFormWidgetClass, workArea,
    XmNfractionBase,     3,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_WIDGET,   XmNrightWidget,   vSeparator,
    NULL);
  label = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form,
    XtVaTypedArg, XmNlabelString, XmRString, "List of Phases in Assimilant:",
      strlen("List of Phases in Assimilant:")+1,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  button = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, form,
    XtVaTypedArg, XmNlabelString, XmRString, "Delete Selected", 
      strlen("Delete Selected")+1,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  1,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 2,
    NULL);
  XtAddCallback(button, XmNactivateCallback, button_callback, 
    (XtPointer) K_DELETE_PHASE);

  listD = XmCreateScrolledList(form, "ScrolledList", NULL, 0);
  XtVaSetValues(listD, 
    XmNvisibleItemCount, 5,
    XmNselectionPolicy,  XmSINGLE_SELECT, 
    NULL);
  XtAddCallback(listD, XmNsingleSelectionCallback, list_del_callback, 
    (XtPointer) 0);
  XtAddCallback(listD, XmNdefaultActionCallback,   list_del_callback, 
    (XtPointer) 0);
  XtVaSetValues(XtParent(listD),
    XmNtopAttachment,    XmATTACH_WIDGET,   XmNtopWidget,     label,
    XmNbottomAttachment, XmATTACH_WIDGET,   XmNbottomWidget,  button,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  XtManageChild(listD);

  XtManageChild(form);
  hSeparator[2] = XtVaCreateManagedWidget(
    "Separator", xmSeparatorWidgetClass, workArea,
    XmNtopAttachment,    XmATTACH_WIDGET,   XmNtopWidget,      form,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_WIDGET,   XmNrightWidget,    vSeparator,
    NULL);
  }
  /*************************************************************************** 
   * Potential phases form box and horizontal separator
   ***************************************************************************/
  {
  static Widget form, label, button;
  XmString csString;
  int i;
  form = XtVaCreateWidget("Form", xmFormWidgetClass, workArea, 
    XmNfractionBase,     3,
    XmNtopAttachment,    XmATTACH_WIDGET,   XmNtopWidget,      hSeparator[2],
    XmNbottomAttachment, XmATTACH_WIDGET,   XmNbottomWidget,   hSeparator[1],
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_WIDGET,   XmNrightWidget,    vSeparator,
    NULL);
  label = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form,
    XtVaTypedArg, XmNlabelString, XmRString, "List of Potential Phases:",
      strlen("List of Potential Phases:")+1,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  button = XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, form,
    XtVaTypedArg, XmNlabelString, XmRString, "Add Selected", 
      strlen("Add Selected")+1,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  1,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 2,
    NULL);
  XtAddCallback(button, XmNactivateCallback, button_callback, 
    (XtPointer) K_ADD_PHASE);

  listA = XmCreateScrolledList(form, "ScrolledList", NULL, 0);
  XtVaSetValues(listA, 
    XmNselectionPolicy,  XmSINGLE_SELECT, 
    NULL);
  XtAddCallback(listA, XmNsingleSelectionCallback, list_add_callback, 
    (XtPointer) 0);
  XtAddCallback(listA, XmNdefaultActionCallback,   list_add_callback, 
    (XtPointer) 0);
  XtVaSetValues(XtParent(listA),
    XmNtopAttachment,    XmATTACH_WIDGET,   XmNtopWidget,     label,
    XmNbottomAttachment, XmATTACH_WIDGET,   XmNbottomWidget,  button,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);
  XtManageChild(listA);

  csString = XmStringCreateLtoR("liquid", "ISO8859-1");
  XmListAddItemUnselected(listA, csString, 0);
  XmStringFree(csString);
  for (i=0; i<npc; i++) if (solids[i].type == PHASE) {
    csString = XmStringCreateLtoR((char *) solids[i].label, "ISO8859-1");
    XmListAddItemUnselected(listA, csString, 0);
    XmStringFree(csString);
  }

  XtManageChild(form);
  }

  /***************************************************************************
   * Manage the workArea form widget
   ***************************************************************************/
  XtManageChild(workArea);

  /***************************************************************************
   * lower most cell of the pane window (action area) 
   ***************************************************************************/
  actionArea = XtVaCreateWidget("Form", xmFormWidgetClass, pane,
    XmNfractionBase, 7,
    NULL);

  {
  static Widget button;
  button = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, actionArea,
    XtVaTypedArg, XmNlabelString, XmRString, "Done", strlen("Done")+1,
    XmNshowAsDefault,    True,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  1,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 2,
    NULL);
  XtAddCallback(button, XmNactivateCallback, button_callback, 
    (XtPointer) K_DONE);
  XtVaGetValues(button, XmNheight, &h, NULL);
  }
  {
  static Widget button;
  button = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, actionArea,
    XtVaTypedArg, XmNlabelString, XmRString, "Clear", strlen("Clear")+1,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  3,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 4,
    NULL);
  XtAddCallback(button, XmNactivateCallback, button_callback, 
    (XtPointer) K_CLEAR);
  }
  {
  static Widget button;
  button = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, actionArea,
    XtVaTypedArg, XmNlabelString, XmRString, "Help", strlen("Help")+1,
    XmNsensitive,        False,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  5,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 6,
    NULL);
  XtAddCallback(button, XmNactivateCallback, button_callback, 
    (XtPointer) k_HELP);
  }

  XtManageChild(actionArea);
  XtVaSetValues(actionArea,   XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);

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

void updateAssimilantPADB(char *member)
{
  if (member == (char *) NULL) XmListDeleteAllItems(listD);
  else {
    XmString csString = XmStringCreateLtoR(member, "ISO8859-1");
    XmListAddItemUnselected(listD, csString, 0);
    XmListSelectPos(listD, 0, True);
    XmStringFree(csString);
  }
}

static char *curAddItem;
static char *curDelItem;
static int  curAddIndex;
static int  curDelIndex;
static int  curAddNs;
static int  curDelNs;

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
      output = (char *) malloc((unsigned) ((CHAR_LENGTH+1)*sizeof(char)));
      (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, atof(number));
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
          cbData->text->length = (int) strlen(cbData->text->ptr);
        }
        for (len=0; len<cbData->text->length; len++) {
          if (!isdigit(cbData->text->ptr[len]) && cbData->text->ptr[len] != '-' &&
            cbData->text->ptr[len] != '.' && cbData->text->ptr[len] != ' ') {
            int j;
            for (j=(int)len; (j+1)<cbData->text->length; j++)
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
    /* tag ==  0 through nc-1,         entries from component menus 
       tag == nc through nc+ENTRIES-1, total mass, T, and increment entries
       tag == nc+ENTRIES               solid or liquid proportion in units */
    number = XmTextGetString(w);
    if        (tag < nc) {
      if (curDelIndex == npc) (assimilantValues[npc+tag].value)[curDelNs] 
        = atof(number);
      else if (curDelIndex >= 0 && 
               assimilantValues[curDelIndex+1+tag].value != NULL) 
        (assimilantValues[curDelIndex+1+tag].value)[curDelNs] = atof(number);
    } else if (tag < nc+ENTRIES) {
      if (tag == (nc+ASSIM_PADB_INDEX_MASS)) 
        (assimilantValues[npc+nc+ASSIM_PADB_INDEX_MASS].value)[0] 
          = atof(number);
      else if (tag == (nc+ASSIM_PADB_INDEX_T)) 
        (assimilantValues[npc+nc+ASSIM_PADB_INDEX_T].value)[0] 
          = atof(number);
      else if (tag == (nc+ASSIM_PADB_INDEX_INCREMENT)) 
        (assimilantValues[npc+nc+ASSIM_PADB_INDEX_INCREMENT].value)[0] 
          = atof(number);
    } else {
      if (curDelIndex == npc) 
        (assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value)[curDelNs] 
          = atof(number);
      else if (curDelIndex >= 0 && assimilantValues[curDelIndex].value != NULL) 
        (assimilantValues[curDelIndex].value)[curDelNs] = atof(number);
    }
    XtFree(number);
    break;

  default:
    break;

  }
}

static void makeItemVisible(Widget list, XmString item)
{
  int top, visible, n = XmListItemPos(list, item);
  if (n > 0) {
    XtVaGetValues(list, 
      XmNtopItemPosition, &top, XmNvisibleItemCount, &visible, NULL);
    if      (n < top)          XmListSetPos(list, n);
    else if (n >= top+visible) XmListSetBottomPos(list, n);
  }
}

static void button_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmPushButtonCallbackStruct *cbData = (XmPushButtonCallbackStruct *) cbDataGen;
  
  switch (cbData->reason) {

  case XmCR_ACTIVATE :
    if      (tag == K_VOLUME_PERCENT) 
      assimilantUnits.units = ASSIM_PADB_UNITS_VOLUME;
    else if (tag == K_WEIGHT_PERCENT)
      assimilantUnits.units = ASSIM_PADB_UNITS_WEIGHT;
    else if (tag == K_DELETE_PHASE) {
      if (curDelItem != NULL) {
        int i, j;
        XmString csString = XmStringCreateLtoR(curDelItem, "ISO8859-1");
        XmListDeleteItem(listD, csString);
        XmStringFree(csString);
        XtFree(curDelItem); curDelItem = NULL;

        XtVaSetValues(labelU, XtVaTypedArg, XmNlabelString, XmRString, 
          "mole %", strlen("mole %")+1, NULL);
        XtVaSetValues(labelP, XtVaTypedArg, XmNlabelString, XmRString, 
          " ", strlen(" ")+1, NULL);
        XmTextSetString(textP, "");
        XtVaSetValues(textP, XmNsensitive, False, NULL);
        for (i=0; i<nc; i++) {
          XtVaSetValues(labelC[i], XtVaTypedArg, XmNlabelString, XmRString, 
            " ", strlen(" ")+1, NULL);
          XmTextSetString(textC[i], "");
          XtVaSetValues(textC[i], XmNsensitive, False, NULL);
        }
        if (curDelIndex == npc) {
          int ns = assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].ns;
          if  (ns == 1) {
            free(assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value);
            assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].ns = 0;
            for (i=0; i<nc; i++) {
              free(assimilantValues[curDelIndex+i].value);
              assimilantValues[curDelIndex+i].ns = 0;
            }
          } else {
            for (i=(curDelNs+1); i<ns; i++) {
            (assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value)[i-1]
             = (assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value)[i];
              for (j=0; j<nc; j++) 
                (assimilantValues[curDelIndex+j].value)[i-1] = 
                  (assimilantValues[curDelIndex+j].value)[i];
            }
            assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value 
              = (double *) REALLOC(
                assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value, 
                (unsigned) (ns-1)*sizeof(double));
            assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].ns--;
            for (i=0; i<nc; i++) {
              assimilantValues[curDelIndex+i].value 
                = (double *) REALLOC(assimilantValues[curDelIndex+i].value, 
                  (unsigned) (ns-1)*sizeof(double));
              assimilantValues[curDelIndex+i].ns--;
            }
          }
        } else {
          int ns = assimilantValues[curDelIndex].ns;
          if  (ns == 1) {
            free(assimilantValues[curDelIndex].value);
            assimilantValues[curDelIndex].ns = 0;
            for (i=0; i<solids[curDelIndex].na; i++) {
              free(assimilantValues[curDelIndex+1+i].value);
              assimilantValues[curDelIndex+1+i].ns = 0;
            }
          } else {
            for (i=(curDelNs+1); i<ns; i++) {
              (assimilantValues[curDelIndex].value)[i-1] = 
                (assimilantValues[curDelIndex].value)[i]; 
              for (j=0; j<solids[curDelIndex].na; j++)
                (assimilantValues[curDelIndex+1+j].value)[i-1] = 
                  (assimilantValues[curDelIndex+1+j].value)[i];
            }
            assimilantValues[curDelIndex].value 
              = (double *) REALLOC(assimilantValues[curDelIndex].value, 
                (unsigned) (ns-1)*sizeof(double));
            assimilantValues[curDelIndex].ns--;
            for (i=0; i<solids[curDelIndex].na; i++) {
              assimilantValues[curDelIndex+1+i].value 
                = (double *) REALLOC(assimilantValues[curDelIndex+1+i].value, 
                  (unsigned) (ns-1)*sizeof(double));
              assimilantValues[curDelIndex+1+i].ns--;
            }
          }
        }
        curDelIndex = -1; curDelNs = -1;
      }
    } else if (tag == K_ADD_PHASE) {
      if (curAddItem != NULL) {
        XmString csString = XmStringCreateLtoR(curAddItem, "ISO8859-1");
        XmListAddItemUnselected(listD, csString, 0);
        XmListSelectPos(listD, 0, True);
        makeItemVisible(listD, csString);
        XmStringFree(csString);
      }
    } else if (tag == K_DONE) XtUnmanageChild(assimilant_padb);
    else if (tag == K_CLEAR) {
      int i;
      XmListDeselectAllItems(listA);
      XmListDeleteAllItems(listD);
      XtVaSetValues(labelP, XtVaTypedArg, XmNlabelString, XmRString, 
        " ", strlen(" ")+1, NULL);
      XmTextSetString(textP, "");
      XtVaSetValues(textP, XmNsensitive, False, NULL);
      for (i=0; i<nc; i++) {
        XtVaSetValues(labelC[i], XtVaTypedArg, XmNlabelString, XmRString, 
          " ", strlen(" ")+1, NULL);
        XmTextSetString(textC[i], "");
        XtVaSetValues(textC[i], XmNsensitive, False, NULL);
      }
      for (i=0; i<3; i++) XmTextSetString(textT[i], "");
      curAddIndex = -1; curDelIndex = -1; curAddNs = -1; curDelNs = -1;
      (assimilantValues[npc+nc+ASSIM_PADB_INDEX_MASS].value)[0] = 0.0;
      (assimilantValues[npc+nc+ASSIM_PADB_INDEX_T].value)[0] = 0.0;
      (assimilantValues[npc+nc+ASSIM_PADB_INDEX_INCREMENT].value)[0] = 0.0;
      if(assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].ns > 0) {
        free(assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value);
        assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].ns = 0;
      }
      for (i=0; i<(npc+nc); i++) 
        if(assimilantValues[i].ns > 0) {
          free(assimilantValues[i].value); assimilantValues[i].ns = 0;
        }
    } else if (tag == k_HELP)
        ;
    break;

  case XmCR_HELP :
    break;

  default:
    break;
  }
}

static void list_add_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  XmListCallbackStruct *cbData = (XmListCallbackStruct *) cbDataGen;

  switch (cbData->reason) {

  case XmCR_DEFAULT_ACTION :
#ifdef DEBUG
    printf("Called the list (add) DEFAULT ACTION callback.\n");
#endif
    XmListAddItemUnselected(listD, cbData->item, 0);
    XmListSelectPos(listD, 0, True);
    makeItemVisible(listD, cbData->item);
    break;

  case XmCR_SINGLE_SELECT :
#ifdef DEBUG
    printf("Called the list (add) SINGLE SELECT callback.\n");
#endif
    if (curAddItem != NULL) XtFree(curAddItem);
    (void) XmStringGetLtoR(cbData->item, "ISO8859-1", &curAddItem);
    if (strcmp(curAddItem, "liquid") == 0) curAddIndex = npc;
    else {
      for (curAddIndex=0; curAddIndex<npc; curAddIndex++) 
        if (solids[curAddIndex].type == PHASE && 
          strcmp(curAddItem, solids[curAddIndex].label) == 0) break; 
    }
#ifdef DEBUG
    printf("     %s [index %d] has been selected.\n", curAddItem, curAddIndex);
#endif
    break;

  default:
    break;
  }
}

static void list_del_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  XmListCallbackStruct *cbData = (XmListCallbackStruct *) cbDataGen;
  int i, *pList, pCount;
  char *output;

  switch (cbData->reason) {

  case XmCR_DEFAULT_ACTION :
#ifdef DEBUG
    printf("Called the list (del) DEFAULT ACTION callback.\n");
#endif

  case XmCR_SINGLE_SELECT :
#ifdef DEBUG
    printf("Called the list (del) SINGLE SELECT callback.\n");
#endif
    if (curDelItem != NULL) XtFree(curDelItem);
    (void) XmStringGetLtoR(cbData->item, "ISO8859-1", &curDelItem);
    if (strcmp(curDelItem, "liquid") == 0) curDelIndex = npc;
    else {
      for (curDelIndex=0; curDelIndex<npc; curDelIndex++) 
        if (solids[curDelIndex].type == PHASE && 
          strcmp(curDelItem, solids[curDelIndex].label) == 0) break; 
    }
#ifdef DEBUG
    printf("     %s [index %d] has been selected.\n", curDelItem, curDelIndex);
#endif

    (void) XmListGetMatchPos(w, cbData->item, &pList, &pCount);
    output = (char *) malloc((unsigned) ((CHAR_LENGTH+1)*sizeof(char)));

    if (curDelIndex  == npc) { /* liquid */
      XtVaSetValues(labelU, XtVaTypedArg, XmNlabelString, XmRString, 
        "wt %", strlen("wt %")+1, NULL);
      XtVaSetValues(labelP, XtVaTypedArg, XmNlabelString, XmRString, 
        "liquid", strlen("liquid")+1, NULL);
      XtVaSetValues(textP, XmNsensitive, True, NULL);
      for (i=0; i<nc; i++) {
        XtVaSetValues(labelC[i], XtVaTypedArg, XmNlabelString, XmRString, 
          bulkSystem[i].label, strlen(bulkSystem[i].label)+1, NULL);
        XtVaSetValues(textC[i], XmNsensitive, True, NULL);
      }

      if (pCount == 1) {
        curDelNs = 0;
        if (assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].ns < pCount) {
          assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].ns = pCount;
          assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value = 
            (double *) calloc((unsigned) pCount, sizeof(double));
          for (i=0; i<nc; i++) {
            assimilantValues[curDelIndex+i].ns = pCount;
            assimilantValues[curDelIndex+i].value = 
              (double *) calloc((unsigned) pCount, sizeof(double));
          }
        }
      } else {
        for (curDelNs=0; curDelNs<pCount; curDelNs++)
          if (pList[curDelNs] == cbData->item_position) break;
        if (assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].ns < pCount) {
          assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].ns = pCount;
          assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value 
            = (double *) 
            REALLOC(assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value,
            (unsigned) pCount*sizeof(double));
         (assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value)[curDelNs]
            = 0.0;
          for (i=0; i<nc; i++) {
            assimilantValues[curDelIndex+i].ns = pCount;
            assimilantValues[curDelIndex+i].value = 
              (double *) REALLOC(assimilantValues[curDelIndex+i].value,
              (unsigned) pCount*sizeof(double));
            (assimilantValues[curDelIndex+i].value)[curDelNs] = 0.0;
          }
        }
      }

      if (
        (assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value)[curDelNs] 
          == 0.0) XmTextSetString(textP, "");
      else {
       (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, 
       (assimilantValues[npc+nc+ASSIM_PADB_INDEX_LIQUID_MASS].value)[curDelNs]);
       XmTextSetString(textP, output);
      }

      for (i=0; i<nc; i++) {
        if ((assimilantValues[npc+i].value)[curDelNs] == 0.0) 
          XmTextSetString(textC[i], "");
        else {
          (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, 
            (assimilantValues[npc+i].value)[curDelNs]);
          XmTextSetString(textC[i], output);
        }
      }


    } else { /* solid */
      XtVaSetValues(labelU, XtVaTypedArg, XmNlabelString, XmRString, 
        "mole %", strlen("mole %")+1, NULL);
      XtVaSetValues(labelP, XtVaTypedArg, XmNlabelString, XmRString, 
        solids[curDelIndex].label, strlen(solids[curDelIndex].label)+1, NULL);
      XtVaSetValues(textP, XmNsensitive, True, NULL);
      if (solids[curDelIndex].na == 1) i = 0;
      else for (i=0; i<solids[curDelIndex].na; i++) {
        XtVaSetValues(labelC[i], XtVaTypedArg, XmNlabelString, XmRString, 
          solids[curDelIndex+1+i].label, 
          strlen(solids[curDelIndex+1+i].label)+1, NULL);
        XtVaSetValues(textC[i], XmNsensitive, True, NULL);
      }
      while (i<nc) {
        XtVaSetValues(labelC[i], XtVaTypedArg, XmNlabelString, XmRString, 
          " ", strlen(" ")+1, NULL);
        XtVaSetValues(textC[i], XmNsensitive, False, NULL);
        XmTextSetString(textC[i], ""); i++;
      }

      if (pCount == 1) {
        curDelNs = 0;
        if (assimilantValues[curDelIndex].ns < pCount) {
          assimilantValues[curDelIndex].ns = pCount;
          assimilantValues[curDelIndex].value = 
          (double *) calloc((unsigned) pCount, sizeof(double));
          if (solids[curDelIndex].na > 1) 
            for (i=0; i<solids[curDelIndex].na; i++) {
              assimilantValues[curDelIndex+1+i].ns = pCount;
               assimilantValues[curDelIndex+1+i].value = 
                (double *) calloc((unsigned) pCount, sizeof(double));
            }
        }
      } else {
        for (curDelNs=0; curDelNs<pCount; curDelNs++)
          if (pList[curDelNs] == cbData->item_position) break;
        if (assimilantValues[curDelIndex].ns < pCount) {
          assimilantValues[curDelIndex].ns = pCount;
          assimilantValues[curDelIndex].value = 
            (double *) REALLOC(assimilantValues[curDelIndex].value,
             (unsigned) pCount*sizeof(double));
          (assimilantValues[curDelIndex].value)[curDelNs] = 0.0;
          if (solids[curDelIndex].na > 1) 
            for (i=0; i<solids[curDelIndex].na; i++) {
              assimilantValues[curDelIndex+1+i].ns = pCount;
              assimilantValues[curDelIndex+1+i].value = 
                (double *) REALLOC(assimilantValues[curDelIndex+1+i].value,
                (unsigned) pCount*sizeof(double));
              (assimilantValues[curDelIndex+1+i].value)[curDelNs] = 0.0;
            }
        }
      }

      if ((assimilantValues[curDelIndex].value)[curDelNs] == 0.0) 
        XmTextSetString(textP, "");
      else {
       (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, 
         (assimilantValues[curDelIndex].value)[curDelNs]);
       XmTextSetString(textP, output);
      }

      if (solids[curDelIndex].na > 1) for (i=0; i<solids[curDelIndex].na; i++) {
        if ((assimilantValues[curDelIndex+1+i].value)[curDelNs] == 0.0) 
          XmTextSetString(textC[i], "");
        else {
          (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, 
            (assimilantValues[curDelIndex+1+i].value)[curDelNs]);
          XmTextSetString(textC[i], output);
        }
      }

    }

    free(output);
    break;

  default:
    break;
  }
}

static void 
  map_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  int i;
  char *output;
  XmAnyCallbackStruct *cbData = (XmAnyCallbackStruct *) cbDataGen;

  switch (cbData->reason) {

  /* translate assimilantValues[].value and assimilantUnits.unit into 
     current display upon mapping */

  case XmCR_MAP : 
#ifdef DEBUG
    printf("Called the dialog MAP callback.\n");
#endif
    curAddIndex = -1; curDelIndex = -1; curAddNs = -1; curDelNs = -1;
    XmListDeselectAllItems(listA);
    XmListDeselectAllItems(listD);
    XtVaSetValues(labelP, XtVaTypedArg, XmNlabelString, XmRString, 
      " ", strlen(" ")+1, NULL);
    XmTextSetString(textP, "");
    XtVaSetValues(textP, XmNsensitive, False, NULL);
    for (i=0; i<nc; i++) {
      XtVaSetValues(labelC[i], XtVaTypedArg, XmNlabelString, XmRString, 
        " ", strlen(" ")+1, NULL);
      XmTextSetString(textC[i], "");
      XtVaSetValues(textC[i], XmNsensitive, False, NULL);
    }

    output = (char *) malloc((unsigned) ((CHAR_LENGTH+1)*sizeof(char)));
    if ((assimilantValues[npc+nc+ASSIM_PADB_INDEX_MASS].value)[0] != 0.0) {
      (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, 
        (assimilantValues[npc+nc+ASSIM_PADB_INDEX_MASS].value)[0]);
      XmTextSetString(textT[0], output);
    }
    if ((assimilantValues[npc+nc+ASSIM_PADB_INDEX_T].value)[0] != 0.0) {
      (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, 
        (assimilantValues[npc+nc+ASSIM_PADB_INDEX_T].value)[0]);
      XmTextSetString(textT[1], output);
    }
    if ((assimilantValues[npc+nc+ASSIM_PADB_INDEX_INCREMENT].value)[0] != 0.0) {
      (void) snprintf(output, CHAR_LENGTH+1, "%*.2f", CHAR_LENGTH, 
        (assimilantValues[npc+nc+ASSIM_PADB_INDEX_INCREMENT].value)[0]);
      XmTextSetString(textT[2], output);
    }
    free(output);

    XtVaSetValues(optionU, 
      XmNmenuHistory, buttonU[assimilantUnits.units], NULL);


    break;

  default:
    break;
  }
}

/* end of file CREATE_ASSIMILANT_PADB.C */
