const char *create_xy_plot_padb_ver(void) { return "$Id: create_xy_plot_padb.c,v 1.2 2006/08/17 16:47:18 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: create_xy_plot_padb.c,v $
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
MELTS Source Code: RCS Revision 1.2  2001/12/26 19:20:02  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.10  1997/06/21  22:49:59  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.9  1997/05/03  20:23:38  ghiorso
 * *** empty log message ***
 *
 * Revision 3.8  1997/03/27  17:03:41  ghiorso
 * *** empty log message ***
 *
 * Revision 3.7  1996/09/24  20:33:44  ghiorso
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
 * Revision 3.3  1995/09/08  23:55:04  ghiorso
 * Preliminary revisions for user graphs (not complete)
 *
 * Revision 3.2  1995/09/01  23:53:03  ghiorso
 * Modifications made to update interface for V3.x and consolidate
 * Graph Widgets
 *
 * Revision 3.1  1995/08/18  17:28:09  ghiorso
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
**        x-y plot information for the silmin interface
**
**      Defines callback routines for all children
**      (file: CREATE_XY_PLOT_PADB.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  September 11, 1990   Original Version
**      V1.0-2  Mark S. Ghiorso  August 30, 1991
**              Added globally known widget definitions
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V3.0-1  Mark S. Ghiorso  December 18, 1991
**              (1) Reorganization of code for Motif style guide
**                               December 19, 1991 - completed
**      V3.0-2  Mark S. Ghiorso  January 28, 1992
**              Altered initialzation of args[] lists to be compliant with 
**              DEC C RISC compiler
**      V3.0-3  Mark S. Ghiorso  March 27, 1992
**              Corrected casting violations for callback routines
**      V3.0-4  Mark S. Ghiorso  September 29, 1992
**              Converted TextField to Text widgets as a bug workaround 
**              for DECWindows Motif V 1.1
**      V3.0-5  Mark S. Ghiorso  April 23, 1994
**              Corrected casting violations for callback structures
**--
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef GRACE_PIPE
#include <unistd.h>
#include <grace_np.h>
#endif /* GRACE_PIPE */

#include <Xm/Form.h>
#include <Xm/LabelG.h>
#include <Xm/PanedW.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/SashP.h>     /* We need to stop keyboard traversal on the sashes */
#include <Xm/Text.h>

#include "interface.h"            /*Specific external declarations          */
#include "silmin.h"               /*Specific external declarations          */

#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))

/******************************************************************************
 * Globally known widgets declared extern in INTERFACE.H
 ******************************************************************************/

Widget xy_plot_padb;

#define YES 1
#define NO  0

typedef struct _optionMenus {
  const char *label;   /* label descriptor for button item in option menu */
  Widget     name;     /* Widget ID for button menu item                  */
  int        selected; /* YES or NO                                       */
} OptionMenus;

static OptionMenus menu0[] = {
  { "x" },                            /*  0 */
  { "y" }                             /*  1 */
};
#define NM0 (sizeof menu0 / sizeof(OptionMenus))

static OptionMenus menu1[] = {
  { "wt %"          },                /*  0 */
  { "mole %"        },                /*  1 */
  { "grams"         },                /*  2 */
  { "moles"         },                /*  3 */
  { "mass fraction" },                /*  4 */
  { "mole fraction" },                /*  5 */
  { "activity"      },                /*  6 */
  { "norm"          },                /*  7 */
  { "T (C)"         },                /*  8 */
  { "log f O2"      },                /*  9 */
  { "G (kJ)"        },                /* 10 */
  { "H (kJ)"        },                /* 11 */
  { "S (J/K)"       },                /* 12 */
  { "V (cc)"        },                /* 13 */
  { "Cp (J/K)"      },                /* 14 */
  { "constant"      }                 /* 15 */
};
#define NM1 (sizeof menu1 / sizeof(OptionMenus))

static OptionMenus menu2[] = {
  { "total"               },          /*  0 */
  { "Oxide ..."           },          /*  1 */
  { "solid phase ..."     },          /*  2 */
  { "solid component ..." }           /*  3 */
};
#define NM2 (sizeof menu2 / sizeof(OptionMenus))

static OptionMenus menu3[] = {
  { "system"                     },   /*  0 */
  { "liquid"                     },   /*  1 */
  { "coexisting solids"          },   /*  2 */
  { "cumulative solids"          },   /*  3 */
  { "assimilant"                 },   /*  4 */
  { "coexisting solid phase ..." },   /*  5 */
  { "cumulative solid phase ..." }    /*  6 */
};
#define NM3 (sizeof menu3 / sizeof(OptionMenus))

static int np;                                     /* Number of solid phases */
static int naMax;           /* Maximum number of solid components in a phase */

#define CHAR_LENGTH 100     /* maximum number of characters in a text widget */

static void button_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void text_callback(Widget w, XtPointer cData, XtPointer cbDataGen);

#define K_BT_MAKE_PLOT 9999
#define K_BT_CLEAR_X   9000
#define K_BT_CLEAR_Y   9001
#define K_BT_ENTER     9002
#define K_BT_PLUS      9003
#define K_BT_MINUS     9004
#define K_BT_TIMES     9005
#define K_BT_DIVIDE    9006
#define K_BT_CANCEL    9007
#define K_BT_HELP      9008

#define K_TEXT_X_AXIS   0
#define K_TEXT_Y_AXIS   1
#define K_TEXT_CONSTANT 2

void create_xy_plot_padb()
{
  static Widget menu0_pd, menu0_op, menu1_pd, menu1_op, 
                menu2_pd, menu2_op, menu3_pd, menu3_op;
  static Widget menu4_pd, menu4_op, *menu4_bt; /* oxide ...             */
  static Widget menu5_pd, menu5_op, *menu5_bt; /* solid phase ...       */
  static Widget menu6_pd, menu6_op, *menu6_bt; /* solid component ...   */
  static Widget buttons[10], form[2], labels[4], pane, text[3];
  Dimension h;
  int j, k;

  /* pop up form dialog box */
  {
    Arg args[] = { { XmNdialogStyle,     XmDIALOG_FULL_APPLICATION_MODAL },
                   { XmNdefaultPosition, True                            },
                   { XmNautoUnmanage,    False                           } };
    xy_plot_padb = XmCreateFormDialog(silmin_adb, "FormDialog", args,
      XtNumber(args));
    XtVaSetValues(XtParent(xy_plot_padb),
      XmNdeleteResponse, XmUNMAP, XmNtitle, "X-Y Plot Specification",
      NULL);
  }

  /* pane window to hold everything */
  pane = XtVaCreateWidget("Pane", xmPanedWindowWidgetClass, xy_plot_padb,
    XmNsashWidth,        1,
    XmNsashHeight,       1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    XmNrightAttachment,  XmATTACH_FORM,
    NULL);

  /* top cell of the pane window */
  form[0] = XtVaCreateWidget("Form", xmFormWidgetClass, pane, NULL);


/*
 *=============================================================================
 * Create labels (rows 1, 2 and 3)
 *
 */

  /* top row */
  labels[0] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "On x axis: ",
      strlen("On x axis: ")+1,
    XmNalignment,        XmALIGNMENT_BEGINNING,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNmarginLeft,       5, 
    XmNtopAttachment,    XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_FORM,
    NULL);

  text[0] = XtVaCreateManagedWidget(
    "Text", xmTextWidgetClass, form[0],
    XmNnavigationType,  XmNONE,
    XmNtraversalOn,     True,
    XmNtopAttachment,   XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,  labels[0],
    XmNleftAttachment,  XmATTACH_WIDGET,          XmNleftWidget, labels[0],
    XmNrightAttachment, XmATTACH_FORM,
    NULL);
  XtAddCallback(text[0], XmNactivateCallback, 
    (XtCallbackProc) XmProcessTraversal, (XtPointer) XmTRAVERSE_NEXT);
  XtAddCallback(text[0], XmNlosingFocusCallback,  text_callback, 
    (XtPointer) K_TEXT_X_AXIS);
  XtAddCallback(text[0], XmNmodifyVerifyCallback, text_callback, 
    (XtPointer) K_TEXT_X_AXIS);
  XtAddCallback(text[0], XmNvalueChangedCallback, text_callback, 
    (XtPointer) K_TEXT_X_AXIS);

  /* second row */
  labels[1] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "On y axis: ",
      strlen("On y axis: ")+1,
    XmNalignment,        XmALIGNMENT_BEGINNING,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNmarginLeft,       5,
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition,  16,
    XmNleftAttachment,   XmATTACH_FORM,
    NULL);

  text[1] = XtVaCreateManagedWidget(
    "Text", xmTextWidgetClass, form[0],
    XmNnavigationType,  XmNONE,
    XmNtraversalOn,     True,
    XmNtopAttachment,   XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,  labels[1],
    XmNleftAttachment,  XmATTACH_WIDGET,          XmNleftWidget, labels[1],
    XmNrightAttachment, XmATTACH_FORM,
    NULL);
  XtAddCallback(text[1], XmNactivateCallback, 
    (XtCallbackProc) XmProcessTraversal, (XtPointer) XmTRAVERSE_NEXT);
  XtAddCallback(text[1], XmNlosingFocusCallback,  text_callback, 
    (XtPointer) K_TEXT_Y_AXIS);
  XtAddCallback(text[1], XmNmodifyVerifyCallback, text_callback, 
    (XtPointer) K_TEXT_Y_AXIS);
  XtAddCallback(text[1], XmNvalueChangedCallback, text_callback, 
    (XtPointer) K_TEXT_Y_AXIS);

  /* third row */
  labels[2] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "Specification: ",
      strlen("Specification: ")+1,
    XmNalignment,        XmALIGNMENT_BEGINNING,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNmarginLeft,       5,
    XmNtopAttachment,    XmATTACH_POSITION, XmNtopPosition,  32,
    XmNleftAttachment,   XmATTACH_FORM,
    NULL);

  buttons[0] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "clear x", strlen("clear x")+1,
    XmNtopAttachment,  XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,    labels[2],
    XmNleftAttachment, XmATTACH_POSITION,        XmNleftPosition, 50,
    NULL);
  XtAddCallback(buttons[0], XmNactivateCallback, button_callback, 
    (XtPointer) K_BT_CLEAR_X);

  buttons[1] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "clear y", strlen("clear y")+1,
    XmNtopAttachment,  XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,    buttons[0],
    XmNleftAttachment, XmATTACH_POSITION,        XmNleftPosition, 70,
    NULL);
  XtAddCallback(buttons[1], XmNactivateCallback, button_callback, 
    (XtPointer) K_BT_CLEAR_Y);

  buttons[2] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, 
      "enter on axis", strlen("enter on axis")+1,
    XmNtopAttachment,   XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,    buttons[1],
    XmNrightAttachment, XmATTACH_FORM,
    NULL);
  XtAddCallback(buttons[2], XmNactivateCallback, button_callback, 
    (XtPointer) K_BT_ENTER);

/*
 *=============================================================================
 * rows 4 and 5
 * Create various option menu popups:
 *
 *   on [menu0] axis         plot [menu1]         of [menu2]      in [menu3]
 *               oxide: [menu4] solid phase: [menu5] solid component [menu6]
 */

  /* pop up menu items on menu 0 */
  menu0_pd = XmCreatePulldownMenu(form[0], "PullDownMenu", NULL, 0);
  for (j = 0; j < NM0; j++) {
    menu0[j].name = 
      XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, menu0_pd,
      XtVaTypedArg, XmNlabelString, XmRString, 
        menu0[j].label, strlen(menu0[j].label)+1,
      NULL);
    {
    long longTag = (long) j;
    XtAddCallback(menu0[j].name, XmNactivateCallback, button_callback, (XtPointer) longTag);
    }
  }
  {
    XmString csString = XmStringCreateLtoR("on ", "ISO8859-1");
    Arg args[8];
    XtSetArg(args[0], XmNsubMenuId,      menu0_pd);
    XtSetArg(args[1], XmNlabelString,    csString);
    XtSetArg(args[2], XmNmnemonic,       'n');
    XtSetArg(args[3], XmNmenuHistory,    menu0[0].name);
    XtSetArg(args[4], XmNtopAttachment,  XmATTACH_POSITION);
    XtSetArg(args[5], XmNtopPosition,    48);
    XtSetArg(args[6], XmNleftAttachment, XmATTACH_POSITION);
    XtSetArg(args[7], XmNleftPosition,   5);
    menu0_op = XmCreateOptionMenu(form[0], "OptionMenu", args, XtNumber(args));
    XtManageChild(menu0_op);
    XmStringFree(csString);
  }

  /* pop up menu items on menu 1 */
  menu1_pd = XmCreatePulldownMenu(form[0], "PullDownMenu", NULL, 0);
  for (j = 0; j < NM1; j++) {
    menu1[j].name = 
      XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, menu1_pd,
      XtVaTypedArg, XmNlabelString, XmRString, 
        menu1[j].label, strlen(menu1[j].label)+1,
      NULL);
    XtAddCallback(menu1[j].name, XmNactivateCallback, button_callback, 
      (XtPointer) (NM0+j));
  }
  {
    XmString csString = XmStringCreateLtoR(" axis plot ", "ISO8859-1");
    Arg args[8];
    XtSetArg(args[0], XmNsubMenuId,      menu1_pd);
    XtSetArg(args[1], XmNlabelString,    csString);
    XtSetArg(args[2], XmNmnemonic,       'a');
    XtSetArg(args[3], XmNmenuHistory,    menu1[0].name);
    XtSetArg(args[4], XmNtopAttachment,  XmATTACH_OPPOSITE_WIDGET);
    XtSetArg(args[5], XmNtopWidget,      menu0_op);
    XtSetArg(args[6], XmNleftAttachment, XmATTACH_WIDGET);
    XtSetArg(args[7], XmNleftWidget,     menu0_op);
    menu1_op = XmCreateOptionMenu(form[0], "OptionMenu", args, XtNumber(args));
    XtManageChild(menu1_op);
    XmStringFree(csString);
  }

  /* pop up menu items on menu 2 */
  menu2_pd = XmCreatePulldownMenu(form[0], "PullDownMenu", NULL, 0);
  for (j = 0; j < NM2; j++) {
    menu2[j].name = 
      XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, menu2_pd,
      XtVaTypedArg, XmNlabelString, XmRString, 
        menu2[j].label, strlen(menu2[j].label)+1,
      NULL);
    XtAddCallback(menu2[j].name, XmNactivateCallback, button_callback, 
      (XtPointer) (NM0+NM1+j));
  }
  {
    XmString csString = XmStringCreateLtoR(" of ", "ISO8859-1");
    Arg args[8];
    XtSetArg(args[0], XmNsubMenuId,      menu2_pd);
    XtSetArg(args[1], XmNlabelString,    csString);
    XtSetArg(args[2], XmNmnemonic,       'f');
    XtSetArg(args[3], XmNmenuHistory,    menu2[0].name);
    XtSetArg(args[4], XmNtopAttachment,  XmATTACH_OPPOSITE_WIDGET);
    XtSetArg(args[5], XmNtopWidget,      menu1_op);
    XtSetArg(args[6], XmNleftAttachment, XmATTACH_WIDGET);
    XtSetArg(args[7], XmNleftWidget,     menu1_op);
    menu2_op = XmCreateOptionMenu(form[0], "OptionMenu", args, XtNumber(args));
    XtManageChild(menu2_op);
    XmStringFree(csString);
  }

  /* pop up menu items on menu 3 */
  menu3_pd = XmCreatePulldownMenu(form[0], "PullDownMenu", NULL, 0);
  for (j = 0; j < NM3; j++) {
    menu3[j].name = 
      XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, menu3_pd,
      XtVaTypedArg, XmNlabelString, XmRString, 
        menu3[j].label, strlen(menu3[j].label)+1,
      NULL);
    XtAddCallback(menu3[j].name, XmNactivateCallback, button_callback, 
      (XtPointer) (NM0+NM1+NM2+j));
  }
  {
    XmString csString = XmStringCreateLtoR(" in ", "ISO8859-1");
    Arg args[8];
    XtSetArg(args[0], XmNsubMenuId,      menu3_pd);
    XtSetArg(args[1], XmNlabelString,    csString);
    XtSetArg(args[2], XmNmnemonic,       'i');
    XtSetArg(args[3], XmNmenuHistory,    menu3[0].name);
    XtSetArg(args[4], XmNtopAttachment,  XmATTACH_OPPOSITE_WIDGET);
    XtSetArg(args[5], XmNtopWidget,      menu2_op);
    XtSetArg(args[6], XmNleftAttachment, XmATTACH_WIDGET);
    XtSetArg(args[7], XmNleftWidget,     menu2_op);
    menu3_op = XmCreateOptionMenu(form[0], "OptionMenu", args, XtNumber(args));
    XtManageChild(menu3_op);
    XmStringFree(csString);
  }

  /* find the number of solid phases (npc-np will be the number of comp) */
  for (j=0, np=0; j<npc; j++) if(solids[j].type == PHASE) {
    np++;
    if (solids[j].na > naMax) naMax = solids[j].na;
  }

  /* pop up menu items on menu 6 */
  menu6_bt = (Widget *) XtMalloc((unsigned) naMax*sizeof(Widget));
  menu6_pd = XmCreatePulldownMenu(form[0], "PullDownMenu", NULL, 0);
  for (j=0; j<solids[0].na; j++) {
    menu6_bt[j] = 
      XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, menu6_pd,
      XtVaTypedArg, XmNlabelString, XmRString, solids[j+1].label, 
        strlen(solids[j+1].label)+1,
      NULL);
    XtAddCallback(menu6_bt[j], XmNactivateCallback, button_callback, 
      (XtPointer) (NM0+NM1+NM2+NM3+nc+np+j));
  }
  {
    XmString csString = XmStringCreateLtoR(" solid component: ", "ISO8859-1");
    Arg args[8];
    XtSetArg(args[0], XmNsubMenuId,       menu6_pd);
    XtSetArg(args[1], XmNlabelString,     csString);
    XtSetArg(args[2], XmNmnemonic,        'c');
    XtSetArg(args[3], XmNmenuHistory,     menu6_bt[0]);
    XtSetArg(args[4], XmNtopAttachment,   XmATTACH_WIDGET);
    XtSetArg(args[5], XmNtopWidget,       menu3_op);
    XtSetArg(args[6], XmNrightAttachment, XmATTACH_OPPOSITE_WIDGET);
    XtSetArg(args[7], XmNrightWidget,     menu3_op);
    menu6_op = XmCreateOptionMenu(form[0], "OptionMenu", args, XtNumber(args));
    XtManageChild(menu6_op);
    XmStringFree(csString);
  }

  /* pop up menu items on menu 5 */
  menu5_bt = (Widget *) XtMalloc( (unsigned) (np*sizeof(Widget)));
  menu5_pd = XmCreatePulldownMenu(form[0], "PullDownMenu", NULL, 0);
  for (j=0, k=0; j<npc; j++) if (solids[j].type == PHASE) {
    menu5_bt[k] = 
      XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, menu5_pd,
      XtVaTypedArg, XmNlabelString, XmRString, solids[j].label, 
        strlen(solids[j].label)+1,
      NULL);
    XtAddCallback(menu5_bt[k], XmNactivateCallback, button_callback, 
      (XtPointer) (NM0+NM1+NM2+NM3+nc+k));
    k++;
  }
  {
    XmString csString = XmStringCreateLtoR(" solid phase: ", "ISO8859-1");
    Arg args[8];
    XtSetArg(args[0], XmNsubMenuId,       menu5_pd);
    XtSetArg(args[1], XmNlabelString,     csString);
    XtSetArg(args[2], XmNmnemonic,        'p');
    XtSetArg(args[3], XmNmenuHistory,     menu5_bt[0]);
    XtSetArg(args[4], XmNtopAttachment,   XmATTACH_OPPOSITE_WIDGET);
    XtSetArg(args[5], XmNtopWidget,       menu6_op);
    XtSetArg(args[6], XmNrightAttachment, XmATTACH_WIDGET);
    XtSetArg(args[7], XmNrightWidget,     menu6_op);
    menu5_op = XmCreateOptionMenu(form[0], "OptionMenu", args, XtNumber(args));
    XtManageChild(menu5_op);
    XmStringFree(csString);
  }

  /* pop up menu items on menu 4 */
  menu4_bt = (Widget *) XtMalloc((unsigned) (nc*sizeof(Widget)));
  menu4_pd = XmCreatePulldownMenu(form[0], "PullDownMenu", NULL, 0);
  for (j=0; j<nc; j++) {
    menu4_bt[j] = 
      XtVaCreateManagedWidget("PushButton", xmPushButtonGadgetClass, menu4_pd,
      XtVaTypedArg, XmNlabelString, XmRString, 
        bulkSystem[j].label, strlen(bulkSystem[j].label)+1,
      NULL);
    XtAddCallback(menu4_bt[j], XmNactivateCallback, button_callback, 
      (XtPointer) (NM0+NM1+NM2+NM3+j));
  }
  {
    XmString csString = XmStringCreateLtoR("oxide: ", "ISO8859-1");
    Arg args[8];
    XtSetArg(args[0], XmNsubMenuId,       menu4_pd);
    XtSetArg(args[1], XmNlabelString,     csString);
    XtSetArg(args[2], XmNmnemonic,        'o');
    XtSetArg(args[3], XmNmenuHistory,     menu4_bt[0]);
    XtSetArg(args[4], XmNtopAttachment,   XmATTACH_OPPOSITE_WIDGET);
    XtSetArg(args[5], XmNtopWidget,       menu5_op);
    XtSetArg(args[6], XmNrightAttachment, XmATTACH_WIDGET);
    XtSetArg(args[7], XmNrightWidget,     menu5_op);
    menu4_op = XmCreateOptionMenu(form[0], "OptionMenu", args, XtNumber(args));
    XtManageChild(menu4_op);
    XmStringFree(csString);
  }

/*
 *=============================================================================
 * Create lower lines of buttons
 */

  /* plus button */
  buttons[3] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "+", strlen("+")+1,
    XmNtopAttachment,  XmATTACH_POSITION,        XmNtopPosition,  80,         
    XmNleftAttachment, XmATTACH_POSITION,        XmNleftPosition, 2,
    NULL);
  XtAddCallback(buttons[3], XmNactivateCallback, button_callback, 
    (XtPointer) K_BT_PLUS);

  /* minus button */
  buttons[4] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "-", strlen("-")+1,
    XmNtopAttachment,  XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,    buttons[3], 
    XmNleftAttachment, XmATTACH_POSITION,        XmNleftPosition,  17,
    NULL);
  XtAddCallback(buttons[4], XmNactivateCallback, button_callback, 
    (XtPointer) K_BT_MINUS);

  /* times button */
  buttons[5] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "*", strlen("*")+1,
    XmNtopAttachment,  XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,    buttons[4], 
    XmNleftAttachment, XmATTACH_POSITION,        XmNleftPosition, 32,
    NULL);
  XtAddCallback(buttons[5], XmNactivateCallback, button_callback, 
    (XtPointer) K_BT_TIMES);

  /* divide button */
  buttons[6] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "/", strlen("/")+1,
    XmNtopAttachment,  XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,    buttons[5], 
    XmNleftAttachment, XmATTACH_POSITION,        XmNleftPosition, 47,
    NULL);
  XtAddCallback(buttons[6], XmNactivateCallback, button_callback, 
    (XtPointer) K_BT_DIVIDE);

  /* constant label */
  labels[3] = XtVaCreateManagedWidget("Label", xmLabelGadgetClass, form[0],
    XtVaTypedArg, XmNlabelString, XmRString, "constant: ",
      strlen("constant: ")+1,
    XmNalignment,      XmALIGNMENT_BEGINNING,
    XmNmarginTop,        5, /* Pixels */
    XmNmarginBottom,     5,
    XmNtopAttachment,  XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,    buttons[6], 
    XmNleftAttachment, XmATTACH_POSITION,        XmNleftPosition, 60,
    NULL);

  /* constant value */
  text[2] = XtVaCreateManagedWidget(
    "Text", xmTextWidgetClass, form[0],
    XmNnavigationType, XmNONE,
    XmNtraversalOn,    True,
    XmNtopAttachment,   XmATTACH_OPPOSITE_WIDGET, XmNtopWidget,  labels[3],
    XmNleftAttachment,  XmATTACH_WIDGET,          XmNleftWidget, labels[3],
    XmNrightAttachment, XmATTACH_FORM,
    NULL);
  XtAddCallback(text[2], XmNactivateCallback, 
    (XtCallbackProc) XmProcessTraversal, (XtPointer) XmTRAVERSE_NEXT);
  XtAddCallback(text[2], XmNlosingFocusCallback,  text_callback, 
    (XtPointer) K_TEXT_CONSTANT);
  XtAddCallback(text[2], XmNmodifyVerifyCallback, text_callback, 
    (XtPointer) K_TEXT_CONSTANT);
  XtAddCallback(text[2], XmNvalueChangedCallback, text_callback, 
    (XtPointer) K_TEXT_CONSTANT);

  /* manage the top pane */
  XtManageChild(form[0]);
#if (XmVersion > 1) || (XmUPDATE_LEVEL > 3)
  XtVaSetValues(form[0], XmNwidth, 750, NULL);
#endif

  /* lower most cell of the pane window (action area) */
  form[1] = XtVaCreateWidget("Form", xmFormWidgetClass, pane,
    XmNfractionBase, 7,
    NULL);

  buttons[7] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[1],
    XtVaTypedArg, XmNlabelString, XmRString, "Make Plot", strlen("Make Plot")+1,
    XmNshowAsDefault,    True,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  1,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 2,
    NULL);
  XtAddCallback(buttons[7], XmNactivateCallback, button_callback, 
    (XtPointer) K_BT_MAKE_PLOT);
  buttons[8] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[1],
    XtVaTypedArg, XmNlabelString, XmRString, "Cancel", strlen("Cancel")+1,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  3,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 4,
    NULL);
  XtAddCallback(buttons[8], XmNactivateCallback, button_callback, 
    (XtPointer) K_BT_CANCEL);
  buttons[9] = XtVaCreateManagedWidget(
    "PushButton", xmPushButtonGadgetClass, form[1],
    XtVaTypedArg, XmNlabelString, XmRString, "Help", strlen("Help")+1,
    XmNsensitive,        False,
    XmNshowAsDefault,    False,
    XmNdefaultButtonShadowThickness, 1,
    XmNtopAttachment,    XmATTACH_FORM,
    XmNbottomAttachment, XmATTACH_FORM,
    XmNleftAttachment,   XmATTACH_POSITION, XmNleftPosition,  5,
    XmNrightAttachment,  XmATTACH_POSITION, XmNrightPosition, 6,
    NULL);
  XtAddCallback(buttons[9], XmNactivateCallback, button_callback, 
    (XtPointer) K_BT_HELP);

  XtManageChild(form[1]);
  XtVaGetValues(buttons[7], XmNheight, &h, NULL);
  XtVaSetValues(form[1], XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);
  h *= 6; /* make upper pain five times the height of lower pane - aesthetic */
  XtVaSetValues(form[0], XmNpaneMinimum, h, NULL);

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

  switch (cbData->reason) {

  case XmCR_ACTIVATE :

    /* items from menu 0:
       "x"   0 
       "y"   1 
    */
    if (tag < NM0) {
      ;    
 
    /* items from menu 1 
       "wt %"           0 
       "mole %"         1 
       "grams"          2 
       "moles"          3 
       "mass fraction"  4 
       "mole fraction"  5 
       "activity"       6 
       "norm"           7 
       "T (C)"          8 
       "log f O2"       9 
       "G (kJ)"        10 
       "H (kJ)"        11 
       "S (J/K)"       12 
       "V (cc)"        13 
       "Cp (J/K)"      14 
       "constant"      15 
    */
    } else if (tag < (NM0+NM1) ) {
      ;

    /* items from menu 2 
       "total"                 0 
       "Oxide ..."             1 
       "solid phase ..."       2 
       "solid component ..."   3 
    */
    } else if (tag < (NM0+NM1+NM2) ) {
      ;

    /* items from menu 3 
       "system"                       0 
       "liquid"                       1 
       "coexisting solids"            2 
       "cumulative solids"            3 
       "assimilant"                   4 
       "second magma"                 5 
       "coexisting solid phase ..."   6 
       "cumulative solid phase ..."   7 
    */
    } else if (tag < (NM0+NM1+NM2+NM3) ) {
      ;

    /* items from menu 4
       oxide labels from bulkSystem[nc].labels
    */
    } else if (tag < (NM0+NM1+NM2+NM3+nc) ) {
      ;

    /* items from menu 5
       phase labels from solids[np].labels
    */
    } else if (tag < (NM0+NM1+NM2+NM3+nc+np) ) {
      ;

    /* items from menu 6
       component labels from solids[npc-np].labels
    */
    } else if (tag < (NM0+NM1+NM2+NM3+npc) ) {
      ;

    } else if (tag == K_BT_CLEAR_X) {
      ;

    } else if (tag == K_BT_CLEAR_Y) {
      ;

    } else if (tag == K_BT_ENTER) {
      ;

    } else if (tag == K_BT_PLUS) {
      ;

    } else if (tag == K_BT_MINUS) {
      ;

    } else if (tag == K_BT_TIMES) {
      ;

    } else if (tag == K_BT_DIVIDE) {
      ;

    } else if (tag == K_BT_MAKE_PLOT) {
      MESSAGE(cs_not_yet_implemented);
      XtUnmanageChild(xy_plot_padb);

    } else if (tag == K_BT_CANCEL) {
      XtUnmanageChild(xy_plot_padb);

    } else if (tag == K_BT_HELP) {
      ;

    }
    break;

  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;

  default:
    break;
  }
}

static void text_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmTextVerifyCallbackStruct *cbData = (XmTextVerifyCallbackStruct *) cbDataGen;
  char *value;
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
    value = XmTextGetString(w);
    /* xxx = atof(value); or evaluate string */
    XtFree(value);
    break;

  case XmCR_MODIFYING_TEXT_VALUE :
    if (cbData->startPos >= cbData->currInsert) {
      if ((len = XmTextGetLastPosition(w)) == CHAR_LENGTH) cbData->doit = False;
      else {
        if (len + cbData->text->length > CHAR_LENGTH) {
          cbData->text->ptr[CHAR_LENGTH-len] = 0;
          cbData->text->length = strlen(cbData->text->ptr);
        }
        if (tag == K_TEXT_CONSTANT) {       /* if constant, must be a number */
          for (len=0; len<cbData->text->length; len++) {
            if (!isdigit(cbData->text->ptr[len]) &&
              cbData->text->ptr[len] != '.' && cbData->text->ptr[len] != ' ' &&
              cbData->text->ptr[len] != '-' ) {
              int j;
              for (j=len; (j+1)<cbData->text->length; j++)
                cbData->text->ptr[j] = cbData->text->ptr[j+1];
              cbData->text->length--;  len--;
            }
          }
        }
        if (cbData->text->length == 0) cbData->doit = False;
      }
    }
    break;

  case XmCR_MOVING_INSERT_CURSOR :
    break;

  case XmCR_VALUE_CHANGED :
    value = XmTextGetString(w);
    /* xxx = atof(value); or evaluate string */
    XtFree(value);
    break;

  default:
    break;

  }
}

#ifdef GRACE_PIPE

static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}

Boolean launchUserGraphGW(Widget w)
{
  GraceRegisterErrorFunction (grace_error_function);
  if(GraceOpen (2048) < 0) return False;
  XtSetSensitive(w, False);
  return True;
}

#else

Boolean launchUserGraphGW(Widget w)
{
  return True;
}

#endif /* GRACE_PIPE */

void updateUserGraphGW(void)
{
  static Boolean firstTime = True;

  if (silminHistory == NULL && silminState != NULL) {
    silminHistory  = (SilminHistory *) calloc((unsigned) 1, sizeof(SilminHistory));
    silminHistory->state = copySilminStateStructure(silminState, NULL);

  } else if (silminState != NULL) {
    SilminHistory *current = silminHistory->next;
    while (current != NULL) current = current->next;
    current = (SilminHistory *) calloc((unsigned) 1, sizeof(SilminHistory));
    current->state = copySilminStateStructure(silminState, NULL);
  }

#ifdef GRACE_PIPE

  if (GraceIsOpen()) {
    if(silminState->liquidMass != 0.0) {
      double totalMass, x, sum;
      double *y = (double *) malloc((size_t) nc*sizeof(double));
      int i, j, nl;

      for (i=0, totalMass=0.0; i<nc; i++) totalMass += (silminState->bulkComp)[i]*bulkSystem[i].mw;

      x = totalMass - silminState->liquidMass;
 
      if (firstTime) {
    	firstTime = False;
    	GracePrintf("TITLE \"MELTS User Graph\"\n");
    	GracePrintf("TITLE SIZE 0.8\n");
    	GracePrintf("SUBTITLE \"Mass solids vrs wt %% oxides in liquid\"\n");
    	GracePrintf("SUBTITLE SIZE 0.8\n");
    	GracePrintf("SUBTITLE COLOR 2\n");
    	for (i=0, j=0; i<nc; i++) if (y[i] > 0.0) {
    	  GracePrintf("g0.s%1.1d SYMBOL %2.2d\n",	  j, 2);
    	  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",	  j);
    	  GracePrintf("g0.s%1.1d SYMBOL COLOR %2.2d\n",   j, j+1);
    	  GracePrintf("g0.s%1.1d SYMBOL SIZE 0.5\n",	  j);
    	  GracePrintf("g0.s%1.1d FILL WITH COLOR\n",	  j);
    	  GracePrintf("g0.s%1.1d FILL COLOR %2.2d\n",	  j, j+1);
    	  GracePrintf("LEGEND STRING %1.1d \"%s\"\n", j, bulkSystem[i].label);
    	  j++;
    	}
    	GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.2, 0.15, 0.75, 0.85);
    	GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, totalMass, 100.0);

    	GracePrintf("XAXIS TICK MAJOR 20.0\n");
    	GracePrintf("XAXIS TICK MINOR 10.0\n");
    	GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    	GracePrintf("XAXIS LABEL \"%%Solid\"\n");
    	GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    	GracePrintf("XAXIS LABEL COLOR 2\n");

    	GracePrintf("YAXIS TICK MAJOR 20.0\n");
    	GracePrintf("YAXIS TICK MINOR 10.0\n");
    	GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    	GracePrintf("YAXIS LABEL \"Wt %% Oxide\"\n");
    	GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    	GracePrintf("YAXIS LABEL COLOR 2\n");

    	GracePrintf("LEGEND ON\n");
    	GracePrintf("LEGEND BOX ON\n");
    	GracePrintf("LEGEND BOX FILL ON\n");
    	GracePrintf("LEGEND BOX FILL WITH COLOR\n");
    	GracePrintf("LEGEND BOX FILL COLOR 0\n");
    	GracePrintf("LEGEND BOX FILL PATTERN 0\n");
    	GracePrintf("LEGEND X1 0.8\n");
    	GracePrintf("LEGEND Y1 0.85\n");
    	GracePrintf("LEGEND CHAR SIZE 0.7\n");

    	GracePrintf("REDRAW\n");
      }

      for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
    	for (i=0, sum=0.0; i<nc; i++) {
    	  for (j=0, y[i]=0.0; j<nlc; j++) y[i] += (silminState->liquidComp)[nl][j]*(liquid[j].liqToOx)[i];
    	  y[i] *= bulkSystem[i].mw;
    	  sum  += y[i];
    	}
    	if (sum > 0.0) for (i=0; i<nc; i++) y[i] *= 100/sum;

    	for (i=0, j=0; i<nc; i++) if (y[i] > 0.0) {
    	  GracePrintf("g0.s%1.1d POINT %lf, %lf\n", j, x, y[i]);
    	  j++;
    	}
      }

      GracePrintf("REDRAW\n");
      free(y);
    }
  } else firstTime = True;
  
#endif /* GRACE_PIPE */  
  
}

/* end of file CREATE_XY_PLOT_PADB.C */
