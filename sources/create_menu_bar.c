const char *create_menu_bar_ver(void) { return "$Id: create_menu_bar.c,v 1.5 2008/03/06 17:51:23 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: create_menu_bar.c,v $
MELTS Source Code: RCS Revision 1.5  2008/03/06 17:51:23  ghiorso
MELTS Source Code: RCS New fluid fractionation mode and other enhancements.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2007/02/21 21:51:18  ghiorso
MELTS Source Code: RCS New regressions options and parameter selection buttons
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2006/10/20 00:59:22  ghiorso
MELTS Source Code: RCS (1) Made initial modifications for thread safe code.
MELTS Source Code: RCS (2) Added support for XML I/O in batch mode
MELTS Source Code: RCS (3) Added support for Melts-batch listener for eventual integration into VIGMCS
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
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.8  1997/06/21  22:50:02  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.7  1997/05/03  20:23:41  ghiorso
 * *** empty log message ***
 *
 * Revision 3.6  1997/03/27  17:03:45  ghiorso
 * *** empty log message ***
 *
 * Revision 3.5  1996/09/24  20:33:47  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.4  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.3  1995/08/31  00:32:56  ghiorso
 * Changed help widget to invoke dialogs and WEB browser.
 * Removed graphics menu entry and toggle button entries.
 *
 * Revision 3.3  1995/08/31  00:32:56  ghiorso
 * Changed help widget to invoke dialogs and WEB browser.
 * Removed graphics menu entry and toggle button entries.
 *
 * Revision 3.2  1995/08/30  15:30:28  ghiorso
 * Reinvoked help menu
 *
 * Revision 3.1  1995/08/18  17:24:00  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Function to set up menu bar (file: CREATE_MENU_BAR.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  August 24, 1990   Original Version
**      V1.1-1  Mark S. Ghiorso  August 30, 1991
**              (1) Added private definitions of ADD_BUTTON, ADD_TOGGLE
**                  and ADD_SEPARATOR macros
**              (2) Declared all menu entry widgets as external
**              (3) Declared certain button widgets of the command
**                  menu as extern
**              (4) Initially desensitized the edit menu entry
**      V1.1-2  Mark S. Ghiorso  September 3, 1991
**              Defined certain toggle button widgets and extern;
**              added ADD_GLOBAL_TOGGLE macro
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  November 23, 1991
**              (1) Removed debug entry from the menu bar
**      V2.0-3  Mark S. Ghiorso  November 30, 1991
**              (1) Conversion to R4 Varargs type calls
**              (2) Added mneumonics and accelerators
**      V2.0-4  Mark S. Ghiorso  December 10, 1991
**              (1) Removed Magma mixing entry from options menu
**      V2.0-5  Mark S. Ghiorso  March 17, 1992
**              Desensitized Help menu entry for non-DEC systems
**      V2.0-6  Mark S. Ghiorso  March 27, 1992
**              Corrected casting violations for ANSI-C compliance
**      V2.0-7  Mark S. Ghiorso  June 14, 1993
**              Added new fo2 path constraints
**      V2.0-8  Mark S. Ghiorso  March 12, 1994
**              Added include of ToggleB.h to get set and get functions
**      V3.0-1  Mark S. Ghiorso  May 11, 1994
**              (1) Added isentropic menu entry to options menu
**              (2) Removed Grove and Walker entries from plot menu
**      V3.0-2  Mark S. Ghiorso  March23, 1995
**              Permanently desensitized help menu entry
**--
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Xm/CascadeB.h>
#include <Xm/LabelG.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/SeparatoG.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>

#include "interface.h"

#define ADD_BUTTON(NAME, LABEL, PARENT, CALLBACK, TAG, MNEMONIC) \
  NAME = XtVaCreateManagedWidget( \
    "PushButton", xmPushButtonGadgetClass, PARENT, \
    XtVaTypedArg, XmNlabelString, XmRString, LABEL, (int) strlen(LABEL)+1, \
    XmNmnemonic,  MNEMONIC, \
    NULL); \
  { \
  long longTAG = (long) TAG; \
  XtAddCallback(NAME, XmNactivateCallback, CALLBACK, (XtPointer) longTAG); \
  }

#define ADD_PULL_DOWN(NAME_MENU, NAME_ENTRY, LABEL, PARENT, MNEMONIC) \
  NAME_MENU = XmCreatePulldownMenu(PARENT, "PulldownMenu", NULL, 0); \
  NAME_ENTRY = XtVaCreateWidget( \
    "CascadeButton", xmCascadeButtonWidgetClass, PARENT, \
    XtVaTypedArg, XmNlabelString, XmRString, LABEL, (int) strlen(LABEL)+1, \
    XmNmnemonic,  MNEMONIC, \
    XmNsubMenuId, NAME_MENU, \
    NULL);

#define ADD_SEPARATOR(NAME, PARENT, ORIENTATION) \
  { \
  static Widget NAME; \
  NAME = XtVaCreateManagedWidget("Separator", xmSeparatorGadgetClass, PARENT, \
    XmNorientation, ORIENTATION, NULL); \
  }

#define ADD_TOGGLE(NAME, LABEL, PARENT, CALLBACK, TAG, HIGHLIGHT, MNEMONIC) \
  NAME = XtVaCreateManagedWidget( \
    "ToggleButton", xmToggleButtonGadgetClass, PARENT, \
    XtVaTypedArg, XmNlabelString, XmRString, LABEL, (int) strlen(LABEL)+1, \
    XmNmnemonic,      MNEMONIC, \
    XmNindicatorType, XmONE_OF_MANY, \
    NULL); \
  { \
  long longTAG = (long) TAG; \
  XtAddCallback(NAME, XmNvalueChangedCallback, CALLBACK, (XtPointer) longTAG); \
  } \
  if (HIGHLIGHT) XmToggleButtonSetState(NAME, True, False); 


/******************************************************************************
 * Globally known symbols that are declared extern in INTERFACE.h
 ******************************************************************************/

Widget menu_bar;
Widget command_entry, edit_entry, composition_entry, intensive_entry, 
       options_entry, help_entry, mode_entry, fO2_path_entry;
Widget bt_exit, bt_liquidus, bt_open, bt_save, bt_save_as;
Widget tg_path_none, tg_path_hm, tg_path_nno, tg_path_fmq, tg_path_coh, tg_path_iw,
       tg_isenthalpic, tg_isochoric, tg_fractionate_solids, tg_fractionate_fluids,
       tg_fractionate_liquids, tg_multiple_liquids, tg_path_fmq_p3, 
       tg_path_fmq_p2, tg_path_fmq_p1, tg_path_fmq_m1, tg_path_fmq_m2, 
       tg_path_fmq_m3, tg_isentropic, tg_1_bar_only, tg_low_p_only, tg_high_p_only,
       tg_path_fmq_m4, tg_path_fmq_m5, tg_path_fmq_m6, tg_path_fmq_m7, 
       tg_path_fmq_m8, tg_path_fmq_m9, tg_anhydrous_only, tg_hydrous_only,
       tg_oxygen_calib, tg_trust_region_method, tg_implement_bounds;

int k_mb_tg_mode_normal                 =  1, /* mb_tg_callback     */
    k_mb_tg_mode_pre                    =  2,
    k_mb_tg_mode_post                   =  4,
    k_mb_tg_composition_fo2path_abs     =  5,
    k_mb_tg_composition_fo2path_HM      =  6,
    k_mb_tg_composition_fo2path_NNO     =  7,
    k_mb_tg_composition_fo2path_QFM     =  8,
    k_mb_tg_composition_fo2path_COH     =  9,
    k_mb_tg_composition_fo2path_IW      = 10,
    k_mb_tg_options_isenthalpic         = 11,
    k_mb_tg_options_isentropic          = 12,
    k_mb_tg_options_isochoric           = 13,
    k_mb_tg_compos_fo2path_QFM_P3       = 14,
    k_mb_tg_compos_fo2path_QFM_P2       = 15,
    k_mb_tg_compos_fo2path_QFM_P1       = 16,
    k_mb_tg_compos_fo2path_QFM_M1       = 17,
    k_mb_tg_compos_fo2path_QFM_M2       = 18,
    k_mb_tg_compos_fo2path_QFM_M3       = 19,
    k_mb_tg_compos_fo2path_QFM_M4       = 20,
    k_mb_tg_compos_fo2path_QFM_M5       = 21,
    k_mb_tg_compos_fo2path_QFM_M6       = 22,
    k_mb_tg_compos_fo2path_QFM_M7       = 23,
    k_mb_tg_compos_fo2path_QFM_M8       = 24,
    k_mb_tg_compos_fo2path_QFM_M9       = 25,
    k_mb_tg_options_fractionate_solids  = 26,
    k_mb_tg_options_fractionate_liquids = 27,
    k_mb_tg_options_fractionate_fluids  = 28,
    k_mb_tg_options_multiple_liquids    = 29,
    k_mb_tg_options_1_bar_only          = 30,
    k_mb_tg_options_low_p_only          = 31,
    k_mb_tg_options_high_p_only         = 32,
    k_mb_tg_options_anhydrous_only      = 33, 
    k_mb_tg_options_hydrous_only        = 34,
    k_mb_tg_options_oxygen_calib        = 35,
    k_mb_tg_options_trust_region_method = 36,
    k_mb_tg_options_implement_bounds    = 37;
int k_mb_bt_command_liquidus            =  1, /* mb_bt_callback     */
    k_mb_bt_command_execute_halt        =  2,
    k_mb_bt_command_open                =  3,
    k_mb_bt_command_save                =  4,
    k_mb_bt_command_save_as             =  5,
    k_mb_bt_command_exit                =  6,
    k_mb_bt_edit_copy                   =  7,
    k_mb_bt_edit_paste                  =  8,
    k_mb_bt_edit_select_all             =  9,
    k_mb_bt_composition_redox           = 10,
    k_mb_bt_composition_normalize       = 11,
    k_mb_bt_intensive_TP                = 12,
    k_mb_bt_options_assimilant          = 13,
    k_mb_bt_options_solids              = 14,
    k_mb_bt_help_about                  = 15,
    k_mb_bt_help_manual                 = 16,
    k_mb_bt_options_increase_quad_tol   = 17,
    k_mb_bt_options_restore_quad_tol    = 18;

/******************************************************************************/

void create_menu_bar()

{ 
  /* menu pull down widgets of the menu bar */ 
  static Widget command_menu, edit_menu, composition_menu, 
    intensive_menu, options_menu, help_menu;
  
  /* menu pull down widgets of the command and options menus */
  static Widget mode_menu, fO2_path_menu;

  /* buttons and toggles */
  static Widget bt_go_no_go, bt_copy, bt_paste, bt_select_all, bt_ferric, 
    bt_normalize, bt_TandP, bt_assimilant, bt_solids, bt_manual,
    bt_about, bt_normal, bt_clb_pre, bt_clb_post, bt_increase_quad_tol,
    bt_restore_quad_tol;

/*
 *============================================================================
 * (1) Create menu bar widget and add it the main window list
 *     (the spacing is 15 Pixels)
 */
  {
    Arg args[] = { { XmNorientation, XmHORIZONTAL },
                   { XmNspacing,     15           } };
    menu_bar = XmCreateMenuBar(main_window, "MenuBar", args, XtNumber(args));
  }
  XtVaSetValues(main_window, XmNmenuBar, menu_bar, NULL);

/*
 *=============================================================================
 * (1) Create Pull down menus in the order left to right.
 *     Each menu item has two parts:
 *     (a) A pull down menu (which is never managed but is declared a
 *         submenu of the ...
 *     (b) Pull down menu entry
 */
  ADD_PULL_DOWN(command_menu, command_entry, "Commands", menu_bar, 'C');
  ADD_PULL_DOWN(edit_menu, edit_entry, "Edit", menu_bar, 'E');
  ADD_PULL_DOWN(composition_menu, composition_entry, "Composition", 
    menu_bar, 'p');
  ADD_PULL_DOWN(intensive_menu, intensive_entry, "Intensive Variables", 
    menu_bar, 'I');
  ADD_PULL_DOWN(options_menu, options_entry, "Options", menu_bar, 'O');
  ADD_PULL_DOWN(help_menu, help_entry, "Help", menu_bar, 'H');

  /* The help widget is treated specially by the menu bar widget */
  XtVaSetValues(menu_bar, XmNmenuHelpWidget, help_entry, NULL);

/*
 *=============================================================================
 * (1) Add buttons to the various pull down menus in the order top to bottom.
 */
  ADD_PULL_DOWN(mode_menu, mode_entry, "Execution Mode", command_menu, 'M');
    ADD_TOGGLE(bt_normal, "Normal", mode_menu, mb_tg_callback, 
      k_mb_tg_mode_normal, TRUE, 'N');
    ADD_TOGGLE(bt_clb_pre, "Calibrate (Pre-pass)", mode_menu, mb_tg_callback, 
      k_mb_tg_mode_pre, FALSE, 'P');
    ADD_TOGGLE(bt_clb_post, "Calibrate (Post-pass)", mode_menu, mb_tg_callback, 
      k_mb_tg_mode_post, FALSE, 'o');
    XtVaSetValues(mode_menu, XmNradioBehavior, TRUE, NULL);
    XtManageChild(mode_entry);
  ADD_SEPARATOR(com1_separator, command_menu, XmHORIZONTAL);
  ADD_BUTTON(bt_liquidus, "Find Liquidus", command_menu, mb_bt_callback, 
    k_mb_bt_command_liquidus, 'L');
  XtVaSetValues(bt_liquidus, XmNaccelerator, "Ctrl<Key>L",
    XtVaTypedArg, XmNacceleratorText, XmRString, "Ctrl+L", strlen("Ctrl+L")+1,
    NULL);
  ADD_SEPARATOR(com2_separator, command_menu, XmHORIZONTAL);
  ADD_BUTTON(bt_go_no_go, "Execute/Halt", command_menu, mb_bt_callback, 
    k_mb_bt_command_execute_halt, 'E');
  XtVaSetValues(bt_go_no_go, XmNaccelerator, "Ctrl<Key>E",
    XtVaTypedArg, XmNacceleratorText, XmRString, "Ctrl+E", strlen("Ctrl+E")+1,
    NULL);
  ADD_SEPARATOR(com3_separator, command_menu, XmHORIZONTAL);
  ADD_BUTTON(bt_open, "Open...", command_menu, mb_bt_callback, 
    k_mb_bt_command_open, 'O');
  XtVaSetValues(bt_open, XmNaccelerator, "Ctrl<Key>O",
    XtVaTypedArg, XmNacceleratorText, XmRString, "Ctrl+O", strlen("Ctrl+O")+1,
    NULL);
  ADD_BUTTON(bt_save, "Save", command_menu, mb_bt_callback, 
    k_mb_bt_command_save, 'S');
  XtVaSetValues(bt_save, XmNaccelerator, "Ctrl<Key>S",
    XtVaTypedArg, XmNacceleratorText, XmRString, "Ctrl+S", strlen("Ctrl+S")+1,
    NULL);
  ADD_BUTTON(bt_save_as, "Save as...", command_menu, mb_bt_callback, 
    k_mb_bt_command_save_as, 'a');
  ADD_SEPARATOR(com4_separator, command_menu, XmHORIZONTAL);
  ADD_BUTTON(bt_exit, "Exit", command_menu, mb_bt_callback, 
    k_mb_bt_command_exit, 'x');
  XtVaSetValues(bt_exit, XmNaccelerator, "Ctrl<Key>C",
    XtVaTypedArg, XmNacceleratorText, XmRString, "Ctrl+C", strlen("Ctrl+C")+1,
    NULL);

  ADD_BUTTON(bt_copy, "Copy", edit_menu, mb_bt_callback, k_mb_bt_edit_copy, 
    'C');
  ADD_BUTTON(bt_paste, "Paste", edit_menu, mb_bt_callback, k_mb_bt_edit_paste,
    'P');
  ADD_SEPARATOR(edit_separator, edit_menu, XmHORIZONTAL);
  ADD_BUTTON(bt_select_all, "Select All", edit_menu, mb_bt_callback, 
    k_mb_bt_edit_select_all, 'A');
  XtSetSensitive(edit_entry, FALSE);

  ADD_BUTTON(bt_ferric, "Compute Redox State", composition_menu,
    mb_bt_callback, k_mb_bt_composition_redox, 'R');
  XtVaSetValues(bt_ferric, XmNaccelerator, "Ctrl<Key>R",
    XtVaTypedArg, XmNacceleratorText, XmRString, "Ctrl+R", strlen("Ctrl+R")+1,
    NULL);
  ADD_BUTTON(bt_normalize, "Normalize", composition_menu,
    mb_bt_callback, k_mb_bt_composition_normalize, 'N');
  XtVaSetValues(bt_normalize, XmNaccelerator, "Ctrl<Key>N",
    XtVaTypedArg, XmNacceleratorText, XmRString, "Ctrl+N", strlen("Ctrl+N")+1,
    NULL);

  ADD_BUTTON(bt_TandP, "T, P ...", intensive_menu, mb_bt_callback, 
    k_mb_bt_intensive_TP, 'T');
  ADD_PULL_DOWN(fO2_path_menu, fO2_path_entry, "f O2 Constraint", 
    intensive_menu, 'f');
    ADD_TOGGLE(tg_path_none, "Absent", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_composition_fo2path_abs, TRUE, 'A');
    ADD_TOGGLE(tg_path_hm, "Hm-Mt", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_composition_fo2path_HM, FALSE, 'H');
    ADD_TOGGLE(tg_path_nno, "Ni-NiO", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_composition_fo2path_NNO, FALSE, 'N');
    ADD_TOGGLE(tg_path_fmq, "Q-Fa-Mt", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_composition_fo2path_QFM, FALSE, 'Q');
    ADD_TOGGLE(tg_path_coh, "C-COH", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_composition_fo2path_COH, FALSE, 'C');
    ADD_TOGGLE(tg_path_iw, "Fe-FeO", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_composition_fo2path_IW, FALSE, 'F');
    ADD_SEPARATOR(fo2_separator, fO2_path_menu, XmHORIZONTAL);
    ADD_TOGGLE(tg_path_fmq_p3, "Q-Fa-Mt+3", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_P3, FALSE, 'Z');
    ADD_TOGGLE(tg_path_fmq_p2, "Q-Fa-Mt+2", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_P2, FALSE, 'Y');
    ADD_TOGGLE(tg_path_fmq_p1, "Q-Fa-Mt+1", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_P1, FALSE, 'X');
    ADD_TOGGLE(tg_path_fmq_m1, "Q-Fa-Mt-1", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_M1, FALSE, '9');
    ADD_TOGGLE(tg_path_fmq_m2, "Q-Fa-Mt-2", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_M2, FALSE, '8');
    ADD_TOGGLE(tg_path_fmq_m3, "Q-Fa-Mt-3", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_M3, FALSE, '7');      
    ADD_TOGGLE(tg_path_fmq_m4, "Q-Fa-Mt-4", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_M4, FALSE, '6');
    ADD_TOGGLE(tg_path_fmq_m5, "Q-Fa-Mt-5", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_M5, FALSE, '5');
    ADD_TOGGLE(tg_path_fmq_m6, "Q-Fa-Mt-6", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_M6, FALSE, '4');
    ADD_TOGGLE(tg_path_fmq_m7, "Q-Fa-Mt-7", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_M7, FALSE, '3');
    ADD_TOGGLE(tg_path_fmq_m8, "Q-Fa-Mt-8", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_M8, FALSE, '2');
    ADD_TOGGLE(tg_path_fmq_m9, "Q-Fa-Mt-9", fO2_path_menu, mb_tg_callback, 
      k_mb_tg_compos_fo2path_QFM_M9, FALSE, '1');      
    XtVaSetValues(fO2_path_menu, XmNradioBehavior, TRUE, NULL);
    XtManageChild(fO2_path_entry);
  
  ADD_TOGGLE(tg_isenthalpic, "Isenthalpic", options_menu, 
    mb_tg_callback, k_mb_tg_options_isenthalpic, FALSE, 'e');
  ADD_TOGGLE(tg_isentropic, "Isentropic", options_menu, 
    mb_tg_callback, k_mb_tg_options_isentropic, FALSE, 'n');
  ADD_TOGGLE(tg_isochoric, "Isochoric", options_menu, mb_tg_callback, 
    k_mb_tg_options_isochoric, FALSE, 'c');
  ADD_TOGGLE(tg_fractionate_solids, "Fractionate Solids", options_menu, 
    mb_tg_callback, k_mb_tg_options_fractionate_solids, FALSE, 'S');
  ADD_TOGGLE(tg_fractionate_liquids, "Fractionate Liquids", options_menu, 
    mb_tg_callback, k_mb_tg_options_fractionate_liquids, FALSE, 'L');
  ADD_TOGGLE(tg_fractionate_fluids, "Fractionate Fluids", options_menu, 
    mb_tg_callback, k_mb_tg_options_fractionate_fluids, FALSE, 'F');
  ADD_TOGGLE(tg_multiple_liquids, "Allow Multiple Liquids", options_menu, 
    mb_tg_callback, k_mb_tg_options_multiple_liquids, FALSE, 'M');
  ADD_SEPARATOR(op1_separator, options_menu, XmHORIZONTAL);
  ADD_BUTTON(bt_assimilant, "Assimilant ...", options_menu, mb_bt_callback, 
    k_mb_bt_options_assimilant, 'A');
  ADD_SEPARATOR(op2_separator, options_menu, XmHORIZONTAL);
  ADD_BUTTON(bt_solids, "Solid Phases ...", options_menu, mb_bt_callback, 
    k_mb_bt_options_solids,'S');
  XtVaSetValues(bt_solids, XmNaccelerator, "Ctrl<Key>P",
    XtVaTypedArg, XmNacceleratorText, XmRString, "Ctrl+P", strlen("Ctrl+P")+1,
    NULL);
  ADD_SEPARATOR(op3_separator, options_menu, XmHORIZONTAL);
  ADD_TOGGLE(tg_1_bar_only, "1 bar Only", options_menu, 
    mb_tg_callback, k_mb_tg_options_1_bar_only, FALSE, '1');
  XtSetSensitive(tg_1_bar_only, FALSE);
  ADD_TOGGLE(tg_low_p_only, "Low P Only", options_menu, 
    mb_tg_callback, k_mb_tg_options_low_p_only, FALSE, 'L');
  XtSetSensitive(tg_low_p_only, FALSE);
  ADD_TOGGLE(tg_high_p_only, "High P Only", options_menu, 
    mb_tg_callback, k_mb_tg_options_high_p_only, FALSE, 'H');
  XtSetSensitive(tg_high_p_only, FALSE);
  ADD_SEPARATOR(op4_separator, options_menu, XmHORIZONTAL);
  ADD_TOGGLE(tg_anhydrous_only, "Anhydrous Only", options_menu, 
    mb_tg_callback, k_mb_tg_options_anhydrous_only, FALSE, 'W');
  XtSetSensitive(tg_anhydrous_only, FALSE);
  ADD_TOGGLE(tg_hydrous_only, "Hydrous Only", options_menu, 
    mb_tg_callback, k_mb_tg_options_hydrous_only, FALSE, 'D');
  XtSetSensitive(tg_hydrous_only, FALSE);
  ADD_SEPARATOR(op5_separator, options_menu, XmHORIZONTAL);
  ADD_TOGGLE(tg_oxygen_calib, "Oxygen Calib", options_menu, 
    mb_tg_callback, k_mb_tg_options_oxygen_calib, FALSE, 'O');
  XtSetSensitive(tg_oxygen_calib, FALSE);
  ADD_SEPARATOR(op6_separator, options_menu, XmHORIZONTAL);
  ADD_TOGGLE(tg_trust_region_method, "Trust Region Method", options_menu, 
    mb_tg_callback, k_mb_tg_options_trust_region_method, FALSE, 'T');
  XtSetSensitive(tg_trust_region_method, FALSE);
  ADD_TOGGLE(tg_implement_bounds, "Bounds on W(H)", options_menu, 
    mb_tg_callback, k_mb_tg_options_implement_bounds, FALSE, 'B');
  XtSetSensitive(tg_implement_bounds, FALSE);
  ADD_SEPARATOR(op7_separator, options_menu, XmHORIZONTAL);
  ADD_BUTTON(bt_increase_quad_tol, "Increase Quad Tol (X 10)", options_menu, mb_bt_callback, 
    k_mb_bt_options_increase_quad_tol, 'I');
  ADD_BUTTON(bt_restore_quad_tol, "Restore Quad Tol", options_menu, mb_bt_callback, 
    k_mb_bt_options_restore_quad_tol, 'R');
    
  ADD_BUTTON(bt_about, "About", help_menu, mb_bt_callback, 
    k_mb_bt_help_about, 'A');
  ADD_BUTTON(bt_manual, "Manual", help_menu, mb_bt_callback,
    k_mb_bt_help_manual, 'M');
  XtVaSetValues(bt_manual, XmNaccelerator, "Ctrl<Key>H",
    XtVaTypedArg, XmNacceleratorText, XmRString, "Ctrl+H", strlen("Ctrl+H")+1,
    NULL);

/*
 *=============================================================================
 * (1) Manage the menu bar entries
 * (2) Manage the menu bar
 */
  XtManageChild(command_entry);
  XtManageChild(edit_entry);
  XtManageChild(composition_entry);
  XtManageChild(intensive_entry);
  XtManageChild(options_entry);
  XtManageChild(help_entry);

  XtManageChild(menu_bar);

}

/* end of file CREATE_MENU_BAR.C */
