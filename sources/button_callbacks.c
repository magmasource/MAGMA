const char *button_callbacks_ver(void) { return "$Id: button_callbacks.c,v 1.6 2008/03/06 17:51:23 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: button_callbacks.c,v $
MELTS Source Code: RCS Revision 1.6  2008/03/06 17:51:23  ghiorso
MELTS Source Code: RCS New fluid fractionation mode and other enhancements.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2007/02/21 21:51:18  ghiorso
MELTS Source Code: RCS New regressions options and parameter selection buttons
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2006/10/20 00:59:22  ghiorso
MELTS Source Code: RCS (1) Made initial modifications for thread safe code.
MELTS Source Code: RCS (2) Added support for XML I/O in batch mode
MELTS Source Code: RCS (3) Added support for Melts-batch listener for eventual integration into VIGMCS
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
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.9  1997/06/21  22:50:09  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.8  1997/05/03  20:23:44  ghiorso
 * *** empty log message ***
 *
 * Revision 3.7  1997/03/27  17:03:52  ghiorso
 * *** empty log message ***
 *
 * Revision 3.6  1996/09/24  20:33:53  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.5  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.4  1995/09/04  20:01:28  ghiorso
 * Update to allow display of bulk composition (in grams) in the text entry
 * fields of the main silmin display. Liquid composition is no longer
 * display here, and is available only through the popup selection.
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
 * Revision 3.2  1995/08/31  00:32:56  ghiorso
 * Changed help widget to invoke dialogs and WEB browser.
 * Removed graphics menu entry and toggle button entries.
 *
 * Revision 3.1  1995/08/18  17:17:15  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Callbacks for all buttons on the menu bar widget
**        (file: BUTTON_CALLBACKS.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  August 24, 1990   Original Version
**      V1.0-2  Mark S. Ghiorso  August 30, 1991
**              (1) Implemented open ... and save/save as... callbacks 
**              (2) Removed hardcopy callbacks
**              (3) Manage sensitivity of button widgets on command menu
**                  according to mode of operation
**              (4) Updated file_selection and caution management and strings
**      V1.0-3  Mark S. Ghiorso  September 6, 1991
**              (1) Added implementation of HALT phase of Execute/Halt button
**              (2) Added implementation of find_liquidus call
**              (3) Added normalize button and reference to include file
**                  SILMIN.H
**              (4) implemented all toggle buttons by doing nothing, i.e.
**                  consequences will be dealt with in work procedure
**      V1.0-4  Mark S. Ghiorso  September 7, 1991
**              (1) added trap for command execution when a work procedure
**                  is active
**              (2) added computeNormalized and computeRedoxState functions
**              (3) added status uppdates for fo2 toggle buttons
**      V1.0-5  Mark S. Ghiorso  September 13, 1991
**              (1) altered parameter list in call to conLiq
**      V1.0-6  Mark S. Ghiorso  September 20, 1991
**              (1) Removed nyi_callback()
**              (2) Removed all references to phases[]
**      V1.0-7  Mark S. Ghiorso  October 18, 1991
**              (1) Added manage/unmanage logic for silmin_padb (container
**                  for graph widget legends)
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  November 23, 1991
**              (1) Removed references to debug menu entry and callbacks
**              (2) removed references to silmin_padb, postclb_padb1 and
**                  postclb_padb2
**              (3) Added open button to menu bar in preclb work window
**      V2.0-3  Mark S. Ghiorso  December 10, 1991
**              (1) Removed callback for second magma dialog
**      V2.0-4  Mark S. Ghiorso  January 6, 1992
**              (1) Added call to putInputDataToFile() on invocation of 
**                  save command
**      V2.0-5  Mark S. Ghiorso  February 19, 1992
**              Removed global dependence on i and arg_set
**      V2.0-6  Mark S. Ghiorso  March 27, 1992
**              (1) Corrected illegal use of statusEntries structure in 
**                  XtSetValues calls
**              (2) Corrected function declarations for callback procs
**      V2.0-7  Mark S. Ghiorso  September 29, 1992
**              Converted TextField to Text widgets as a bug workaround 
**              for DECWindows Motif V 1.1
**      V2.0-8  Mark S. Ghiorso  June 14, 1993
**              Added toggle button callbacks for new fo2 path constraints
**      V2.0-9  Mark S. Ghiorso  September 21, 1993
**              XtFree -> XmStringFree
**      V2.0-10 Mark S. Ghiorso  April 23, 1994
**              Corrected callback casting violations for OSF/1 c compiler
**      V3.0-1  Mark S. Ghiorso  May 11, 1994
**              (1) Removed references to grove and walker plots
**              (2) Added isentropic toggle button test
**              (3) Made isenthalpic, isentropic, and isochoric a radio group
**--
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define __USE_POSIX
#include <signal.h>
#ifndef SYSV
#include <sys/wait.h>
#else
#define SIGCHLD SIGCLD
#endif
#include <unistd.h>

#include <Xm/Text.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>

#include "interface.h"
#include "silmin.h"

extern const char *albite_ver(void); 		 
extern const char *alloy_liquid_ver(void);		 
extern const char *alloy_solid_ver(void);		 
extern const char *amphibole_ver(void);		 
extern const char *biotite_ver(void);		 
extern const char *button_callbacks_ver(void);	 
extern const char *check_coexisting_liquids_ver(void);
extern const char *check_coexisting_solids_ver(void); 
extern const char *clinopyroxene_ver(void);    
extern const char *create_assimilant_padb_ver(void);
extern const char *create_managed_ver(void);   
extern const char *create_menu_bar_ver(void);  
extern const char *create_postclb_ver(void);   
extern const char *create_preclb_ver(void);    
extern const char *create_solid_padb_ver(void);	 
extern const char *create_tp_padb_ver(void);   
extern const char *create_unmanaged_ver(void); 
extern const char *create_xy_plot_padb_ver(void);
extern const char *cummingtonite_ver(void);    
extern const char *debugMainLoop_ver(void);    
extern const char *equality_constraints_ver(void);
extern const char *est_saturation_state_ver(void);	 
extern const char *evaluate_saturation_ver(void);
extern const char *feldspar_ver(void);	  
extern const char *fluid_ver(void);  	  
extern const char *garnet_ver(void); 	  
extern const char *gibbs_ver(void);  	  
extern const char *gradient_hessian_ver(void); 
extern const char *hornblende_ver(void);		 
extern const char *ilmenite_ver(void);	  
extern const char *initialize_colors_ver(void);
extern const char *initialize_strings_ver(void);
extern const char *interface_ver(void);	  
extern const char *kalsilite_ver(void);	  
extern const char *lawson_hanson_ver(void);    
extern const char *leucite_ver(void);		 
extern const char *linear_search_ver(void);    
extern const char *liquid_ver(void); 	  
extern const char *liquid_v34_ver(void);	  
extern const char *liquidus_ver(void);	  
extern const char *majorite_ver(void);	  
extern const char *melilite_ver(void);	  
extern const char *melts_support_ver(void);  	 
extern const char *nash_ver(void);		  
extern const char *nepheline_ver(void);	  
extern const char *olivine_sx_ver(void);	  
extern const char *olivine_ver(void);	  
extern const char *ortho_oxide_ver(void);	  
extern const char *orthopyroxene_ver(void);    
extern const char *perovskite_ver(void);		 
extern const char *preclb_ver(void);	  
extern const char *preclb_slave_ver(void);	  
extern const char *postclb_ver(void);	  
extern const char *read_write_ver(void);	  
extern const char *recipes_ver(void);	  
extern const char *rhombohedral_ver(void);	  
extern const char *rhomsghiorso_ver(void);	  
extern const char *ringwoodite_ver(void);	  
extern const char *silmin_ver(void); 		 
extern const char *silmin_support_ver(void);   
extern const char *spinel_ver(void); 	  
extern const char *subSolidusMuO2_ver(void);   
extern const char *vframe_ver(void); 	  
extern const char *vheader_ver(void);	  
extern const char *vlist_ver(void);  	  
extern const char *wadsleyite_ver(void);		 
extern const char *water_ver(void);  	  
extern const char *wustite_ver(void);	  

static Boolean      (*workProc)(XtPointer);
static WorkProcData workProcData;
static XtWorkProcId workProcId; 

static void computeRedoxState(void);
static void computeNormalized(void);

typedef struct {
  Widget button;
  pid_t  pid;
} ExecItem;

#define BC_LAUNCH_MANUAL     0
#define BC_LAUNCH_CALCULATOR 1
#define BC_LAUNCH_VIEWER     3

static ExecItem execItem[3];
static int nExecItem = 3;

/*
 *=============================================================================
 * Menu bar button gadgets
 */

#define INFORMATION(STRING) \
{ \
  XmString cs_string = XmStringCreateLtoR(STRING, "ISO8859-1"); \
  i = 0; \
  XtSetArg(arg_set[i], XmNmessageString, cs_string); i++; \
  XtSetValues(message, arg_set, i); \
  XtManageChild(message); \
  XmStringFree(cs_string); \
}

#define ERROR(STRING) \
{ \
  XmString cs_string = XmStringCreateLtoR(STRING, "ISO8859-1"); \
  i = 0; \
  XtSetArg(arg_set[i], XmNmessageString, cs_string); i++; \
  XtSetValues(message, arg_set, i); \
  XtManageChild(message); \
  XmStringFree(cs_string); \
  return; \
}

void mb_bt_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData; 
  XmPushButtonCallbackStruct *callback_data = 
    (XmPushButtonCallbackStruct *) cbDataGen;
  Arg arg_set[20];
  int i;
  switch (callback_data->reason) {

  case XmCR_ACTIVATE :

    if (workProcData.active) { 
      XtRemoveWorkProc(workProcId);
      workProcData.active = FALSE; 
      if (tag == k_mb_bt_command_execute_halt) return;
    }

    if (tag == k_mb_bt_command_liquidus) {
      workProc = NULL; workProcData.active = TRUE; workProcData.mode = TRUE;
      workProcId = XtAppAddWorkProc(XtWidgetToApplicationContext(w), 
        (*liquidus), (XtPointer) &workProcData);

    } else if (tag == k_mb_bt_command_execute_halt) {
      if (workProc == NULL) workProc = silmin; 
      workProcData.active = TRUE; workProcData.mode = TRUE;
      workProcId = XtAppAddWorkProc(XtWidgetToApplicationContext(w), 
        (*workProc), (XtPointer) &workProcData);

    } else if (tag == k_mb_bt_command_open) {
      called_fs = bt_open;
      if (XtIsManaged(silmin_adb)) XtVaSetValues(file_selection, 
        XtVaTypedArg, XmNdirectory, XmRString, meltsEnviron.INPUT_DIR, 
          strlen(meltsEnviron.INPUT_DIR)+1,
        XtVaTypedArg, XmNpattern, XmRString, meltsEnviron.INPUT_SUFFIX, 
          strlen(meltsEnviron.INPUT_SUFFIX)+1,
        NULL);
      else if (XtIsManaged(preclb_adb)) XtVaSetValues(file_selection,
        XtVaTypedArg, XmNdirectory, XmRString, meltsEnviron.DATA_DIR, 
          strlen(meltsEnviron.DATA_DIR)+1,
        XtVaTypedArg, XmNpattern, XmRString, meltsEnviron.DATA_SUFFIX, 
          strlen(meltsEnviron.DATA_SUFFIX)+1,
        NULL);
      XtManageChild(file_selection);

    } else if (tag == k_mb_bt_command_save) {
      (void) putInputDataToFile((char *) NULL);

    } else if (tag == k_mb_bt_command_save_as) {
      called_fs = bt_save_as;
      i = 0;
      XtSetArg(arg_set[i], XmNdirMask, cs_fs_dirMask_io); i++;
      XtSetValues(file_selection, arg_set, i);
      XtManageChild(file_selection);

    } else if (tag == k_mb_bt_command_exit) {
      called_caution = bt_exit;
      i = 0;
      XtSetArg(arg_set[i], XmNmessageString, cs_caution_exit); i++;
      XtSetValues(caution, arg_set, i);
      XtManageChild(caution); 

    } else if (tag == k_mb_bt_edit_copy) {
      MESSAGE(cs_not_yet_implemented);

    } else if (tag == k_mb_bt_edit_paste) {
      MESSAGE(cs_not_yet_implemented);

    } else if (tag == k_mb_bt_edit_select_all) {
      MESSAGE(cs_not_yet_implemented);

    } else if (tag == k_mb_bt_composition_redox) {
      computeRedoxState();

    } else if (tag == k_mb_bt_composition_normalize) {
      computeNormalized();

    } else if (tag == k_mb_bt_intensive_TP) {
      if (tp_padb == (Widget) NULL) create_tp_padb();
      XtManageChild(tp_padb);

    } else if (tag == k_mb_bt_options_assimilant) {
      if (assimilant_padb == (Widget) NULL) create_assimilant_padb();
      XtManageChild(assimilant_padb);

    } else if (tag == k_mb_bt_options_solids) {
      if (solid_padb == (Widget) NULL) create_solid_padb();
      XtManageChild(solid_padb);

    } else if (tag == k_mb_bt_help_about) {
      char *string;
      int len = 7; /* "MELTS V" */
      len += strlen(meltsEnviron.RELEASE_VERSION)   +  2; /* " ("	   */
      len += strlen(meltsEnviron.HARDWARE_VERSION)  +  1; /* " " 	   */
      len += strlen(meltsEnviron.OS_VERSION)        +  2; /* ")\n"	   */
      len += strlen(meltsEnviron.RELEASE_DATE)      +  7; /* "\nMotif "    */
      len += strlen(meltsEnviron.MOTIF_VERSION)     +  3; /* ", X"	   */
      len += strlen(meltsEnviron.X_VERSION)         + 10; /* "\nAuthors: " */
      len += strlen(meltsEnviron.AUTHOR_LIST)       +  2; /* "\n\n"	   */
      len += strlen(albite_ver())                   +  1; /* "\n"  	   */
      len += strlen(alloy_liquid_ver())             +  1; /* "\n"  	   */
      len += strlen(alloy_solid_ver())              +  1; /* "\n"  	   */
      len += strlen(amphibole_ver())                +  1; /* "\n"  	   */
      len += strlen(biotite_ver())                  +  1; /* "\n"  	   */
      len += strlen(button_callbacks_ver())         +  1; /* "\n"  	   */
      len += strlen(check_coexisting_liquids_ver()) +  1; /* "\n"  	   */
      len += strlen(check_coexisting_solids_ver())  +  1; /* "\n"  	   */
      len += strlen(clinopyroxene_ver())            +  1; /* "\n"  	   */
      len += strlen(create_assimilant_padb_ver())   +  1; /* "\n"  	   */
      len += strlen(create_managed_ver())           +  1; /* "\n"  	   */
      len += strlen(create_menu_bar_ver())          +  1; /* "\n"  	   */
      len += strlen(create_postclb_ver())           +  1; /* "\n"  	   */
      len += strlen(create_preclb_ver())            +  1; /* "\n"  	   */
      len += strlen(create_solid_padb_ver())        +  1; /* "\n"  	   */
      len += strlen(create_tp_padb_ver())           +  1; /* "\n"  	   */
      len += strlen(create_unmanaged_ver())         +  1; /* "\n"  	   */
      len += strlen(create_xy_plot_padb_ver())      +  1; /* "\n"  	   */
      len += strlen(cummingtonite_ver())            +  1; /* "\n"  	   */
      len += strlen(debugMainLoop_ver())            +  1; /* "\n"  	   */
      len += strlen(equality_constraints_ver())     +  1; /* "\n"  	   */
      len += strlen(est_saturation_state_ver())     +  1; /* "\n"  	   */
      len += strlen(evaluate_saturation_ver())      +  1; /* "\n"  	   */
      len += strlen(feldspar_ver())                 +  1; /* "\n"  	   */
      len += strlen(fluid_ver())                    +  1; /* "\n"  	   */
      len += strlen(garnet_ver())                   +  1; /* "\n"  	   */
      len += strlen(gibbs_ver())                    +  1; /* "\n"  	   */
      len += strlen(gradient_hessian_ver())         +  1; /* "\n"  	   */
      len += strlen(hornblende_ver())               +  1; /* "\n"  	   */
      len += strlen(ilmenite_ver())                 +  1; /* "\n"  	   */
      len += strlen(initialize_colors_ver())        +  1; /* "\n"  	   */
      len += strlen(initialize_strings_ver())       +  1; /* "\n"  	   */
      len += strlen(interface_ver())                +  1; /* "\n"  	   */
      len += strlen(kalsilite_ver())                +  1; /* "\n"  	   */
      len += strlen(lawson_hanson_ver())            +  1; /* "\n"  	   */
      len += strlen(leucite_ver())                  +  1; /* "\n"  	   */
      len += strlen(linear_search_ver())            +  1; /* "\n"  	   */
      len += strlen(liquid_ver())                   +  1; /* "\n"  	   */
      len += strlen(liquid_v34_ver())               +  1; /* "\n"  	   */
      len += strlen(liquidus_ver())      	    +  1; /* "\n"  	   */
      len += strlen(majorite_ver())      	    +  1; /* "\n"  	   */
      len += strlen(melilite_ver())      	    +  1; /* "\n"  	   */
      len += strlen(melts_support_ver())            +  1; /* "\n"  	   */
      len += strlen(nash_ver())                     +  1; /* "\n"  	   */
      len += strlen(nepheline_ver())                +  1; /* "\n"  	   */
      len += strlen(olivine_sx_ver())               +  1; /* "\n"  	   */
      len += strlen(olivine_ver())                  +  1; /* "\n"  	   */
      len += strlen(ortho_oxide_ver())              +  1; /* "\n"  	   */
      len += strlen(orthopyroxene_ver())            +  1; /* "\n"  	   */
      len += strlen(perovskite_ver())               +  1; /* "\n"  	   */
      len += strlen(preclb_ver())                   +  1; /* "\n"  	   */
      len += strlen(preclb_slave_ver())             +  1; /* "\n"  	   */
      len += strlen(postclb_ver())                  +  1; /* "\n"  	   */
      len += strlen(read_write_ver())               +  1; /* "\n"  	   */
      len += strlen(recipes_ver())                  +  1; /* "\n"  	   */
      len += strlen(rhombohedral_ver())             +  1; /* "\n"  	   */
      len += strlen(rhomsghiorso_ver())             +  1; /* "\n"  	   */
      len += strlen(ringwoodite_ver())              +  1; /* "\n"  	   */
      len += strlen(silmin_ver())                   +  1; /* "\n"  	   */
      len += strlen(silmin_support_ver())           +  1; /* "\n"  	   */
      len += strlen(spinel_ver())                   +  1; /* "\n"  	   */
      len += strlen(subSolidusMuO2_ver())           +  1; /* "\n"  	   */
      len += strlen(vframe_ver())                   +  1; /* "\n"  	   */
      len += strlen(vheader_ver())                  +  1; /* "\n"  	   */
      len += strlen(vlist_ver())                    +  1; /* "\n"  	   */
      len += strlen(wadsleyite_ver())               +  1; /* "\n"  	   */
      len += strlen(water_ver())                    +  1; /* "\n"          */
      len += strlen(wustite_ver())                  +  1; /* "\0"          */
      
      string = (char *) calloc((size_t) len, sizeof(char));
      
      string = strcat (string, "MELTS V");
      
      string = strcat (string, meltsEnviron.RELEASE_VERSION);   string = strcat (string, " (");
      string = strcat (string, meltsEnviron.HARDWARE_VERSION);  string = strcat (string, " ");
      string = strcat (string, meltsEnviron.OS_VERSION);        string = strcat (string, ")\n");
      string = strcat (string, meltsEnviron.RELEASE_DATE);      string = strcat (string, "\nMotif ");
      string = strcat (string, meltsEnviron.MOTIF_VERSION);     string = strcat (string, ", X");
      string = strcat (string, meltsEnviron.X_VERSION);         string = strcat (string, "\nAuthors: ");
      string = strcat (string, meltsEnviron.AUTHOR_LIST);       string = strcat (string, "\n\n");

      string = strcat (string, albite_ver());                   string = strcat (string, "\n");
      string = strcat (string, alloy_liquid_ver());             string = strcat (string, "\n");
      string = strcat (string, alloy_solid_ver());              string = strcat (string, "\n");
      string = strcat (string, amphibole_ver());                string = strcat (string, "\n");
      string = strcat (string, biotite_ver());                  string = strcat (string, "\n");
      string = strcat (string, button_callbacks_ver());         string = strcat (string, "\n");
      string = strcat (string, check_coexisting_liquids_ver()); string = strcat (string, "\n");
      string = strcat (string, check_coexisting_solids_ver());  string = strcat (string, "\n");
      string = strcat (string, clinopyroxene_ver());		string = strcat (string, "\n");
      string = strcat (string, create_assimilant_padb_ver());	string = strcat (string, "\n");
      string = strcat (string, create_managed_ver());		string = strcat (string, "\n");
      string = strcat (string, create_menu_bar_ver());		string = strcat (string, "\n");
      string = strcat (string, create_postclb_ver());		string = strcat (string, "\n");
      string = strcat (string, create_preclb_ver());		string = strcat (string, "\n");
      string = strcat (string, create_solid_padb_ver());        string = strcat (string, "\n");
      string = strcat (string, create_tp_padb_ver());		string = strcat (string, "\n");
      string = strcat (string, create_unmanaged_ver()); 	string = strcat (string, "\n");
      string = strcat (string, create_xy_plot_padb_ver());	string = strcat (string, "\n");
      string = strcat (string, cummingtonite_ver());		string = strcat (string, "\n");
      string = strcat (string, debugMainLoop_ver());		string = strcat (string, "\n");
      string = strcat (string, equality_constraints_ver());	string = strcat (string, "\n");
      string = strcat (string, est_saturation_state_ver());     string = strcat (string, "\n");
      string = strcat (string, evaluate_saturation_ver());	string = strcat (string, "\n");
      string = strcat (string, feldspar_ver()); 		string = strcat (string, "\n");
      string = strcat (string, fluid_ver());			string = strcat (string, "\n");
      string = strcat (string, garnet_ver());			string = strcat (string, "\n");
      string = strcat (string, gibbs_ver());			string = strcat (string, "\n");
      string = strcat (string, gradient_hessian_ver()); 	string = strcat (string, "\n");
      string = strcat (string, hornblende_ver());               string = strcat (string, "\n");
      string = strcat (string, ilmenite_ver()); 		string = strcat (string, "\n");
      string = strcat (string, initialize_colors_ver());	string = strcat (string, "\n");
      string = strcat (string, initialize_strings_ver());	string = strcat (string, "\n");
      string = strcat (string, interface_ver());		string = strcat (string, "\n");
      string = strcat (string, kalsilite_ver());		string = strcat (string, "\n");
      string = strcat (string, lawson_hanson_ver());		string = strcat (string, "\n");
      string = strcat (string, leucite_ver());                  string = strcat (string, "\n");
      string = strcat (string, linear_search_ver());		string = strcat (string, "\n");
      string = strcat (string, liquid_ver());			string = strcat (string, "\n");
      string = strcat (string, liquid_v34_ver());		string = strcat (string, "\n");
      string = strcat (string, liquidus_ver()); 		string = strcat (string, "\n");
      string = strcat (string, majorite_ver()); 		string = strcat (string, "\n");
      string = strcat (string, melilite_ver()); 		string = strcat (string, "\n");
      string = strcat (string, melts_support_ver());            string = strcat (string, "\n");
      string = strcat (string, nash_ver());			string = strcat (string, "\n");
      string = strcat (string, nepheline_ver());		string = strcat (string, "\n");
      string = strcat (string, olivine_sx_ver());		string = strcat (string, "\n");
      string = strcat (string, olivine_ver());			string = strcat (string, "\n");
      string = strcat (string, ortho_oxide_ver());		string = strcat (string, "\n");
      string = strcat (string, orthopyroxene_ver());		string = strcat (string, "\n");
      string = strcat (string, perovskite_ver());               string = strcat (string, "\n");
      string = strcat (string, preclb_ver());			string = strcat (string, "\n");
      string = strcat (string, preclb_slave_ver());		string = strcat (string, "\n");
      string = strcat (string, postclb_ver());			string = strcat (string, "\n");
      string = strcat (string, read_write_ver());		string = strcat (string, "\n");
      string = strcat (string, recipes_ver());			string = strcat (string, "\n");
      string = strcat (string, rhombohedral_ver());		string = strcat (string, "\n");
      string = strcat (string, rhomsghiorso_ver());		string = strcat (string, "\n");
      string = strcat (string, ringwoodite_ver());		string = strcat (string, "\n");
      string = strcat (string, silmin_ver());                   string = strcat (string, "\n");
      string = strcat (string, silmin_support_ver());		string = strcat (string, "\n");
      string = strcat (string, spinel_ver());			string = strcat (string, "\n");
      string = strcat (string, subSolidusMuO2_ver());		string = strcat (string, "\n");
      string = strcat (string, vframe_ver());			string = strcat (string, "\n");
      string = strcat (string, vheader_ver());			string = strcat (string, "\n");
      string = strcat (string, vlist_ver());			string = strcat (string, "\n");
      string = strcat (string, wadsleyite_ver());               string = strcat (string, "\n");
      string = strcat (string, water_ver());			string = strcat (string, "\n");
      string = strcat (string, wustite_ver());			

      INFORMATION(string)

      free(string);
    } else if (tag == k_mb_bt_help_manual) {
      char *argv[3];
      argv[0] = meltsEnviron.WWW_BROWSER; 
      argv[1] = meltsEnviron.WWW_MANUAL;
      argv[2] = NULL;

      INFORMATION(
      "Launching local WWWeb Browser to access the manual.")

      execItem[BC_LAUNCH_MANUAL].pid    = 0;
      execItem[BC_LAUNCH_MANUAL].button = NULL;

      switch (execItem[BC_LAUNCH_MANUAL].pid = fork()) {
        case 0: 
          execvp(argv[0], argv);
          perror(argv[0]);
          _exit(255);
        case -1:
          ERROR("Lanuch failed.\nCannot find WWW browser.")
      }
      if (execItem[BC_LAUNCH_MANUAL].pid > 0) {
        execItem[BC_LAUNCH_MANUAL].button = w;
        XtSetSensitive (w, False);
      }

    } else if (tag == k_mb_bt_options_increase_quad_tol) {
      quad_tol_modifier *= 10;
      wprintf(statusEntries[STATUS_ADB_INDEX_STATUS].name,
        "...Quadratic convergence tolerance increased by a factor of %d.\n",
	quad_tol_modifier);
    
    } else if (tag == k_mb_bt_options_restore_quad_tol) {
      quad_tol_modifier = 1;
      wprintf(statusEntries[STATUS_ADB_INDEX_STATUS].name,
        "...Quadratic convergence tolerance restored to default.\n");
    
    }
    break;
  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;
  default:
    break;
  }
}

static void computeNormalized(void)
{
  int j;
  double sum  = 0.0, value;
  char entry[] = { "     \0" };

  for (j=0; j<nc; j++) sum += compositionValues[j].value;
  if (sum > 0.0) {
    for (j=0; j<nc; j++) {
      compositionValues[j].value *= 100.0/sum;
      if (compositionValues[j].value != 0.0) {
        sprintf(entry, "%7.4f", compositionValues[j].value);
        XmTextSetString(compositionValues[j].name, entry);
      }
    }
    value = 100.0;
    updateStatusADB(STATUS_ADB_INDEX_MASS_LIQUID, &value);
  }
}

static void computeRedoxState(void)
{
  int i, j;
  Arg arg_set[20];
  char compositionEntry[] = { "     \0" };
  double log10fo2, *moles, p, sum, t;

  if (tp_padb == NULL) 
    ERROR("Please set initial T and P first, then reinvoke this command.")

  t = tpValues[TP_PADB_INDEX_T_INITIAL].value + 273.15;
  if (t <= 0.0) 
    ERROR("Please set the temperature first, then reinvoke this command.")

  p = tpValues[TP_PADB_INDEX_P_INITIAL].value;
  if (p <= 0.0) 
    ERROR("Please set the pressure first, then reinvoke this command.")

  if (XmToggleButtonGadgetGetState(tg_path_none)) 
    ERROR("Please specify an fO2 path first, then reinvoke this command.")
  else if (XmToggleButtonGadgetGetState(tg_path_hm)) 
    log10fo2 = getlog10fo2(t, p, FO2_HM);
  else if (XmToggleButtonGadgetGetState(tg_path_nno)) 
    log10fo2 = getlog10fo2(t, p, FO2_NNO);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM);
  else if (XmToggleButtonGadgetGetState(tg_path_coh)) 
    log10fo2 = getlog10fo2(t, p, FO2_COH);
  else if (XmToggleButtonGadgetGetState(tg_path_iw)) 
    log10fo2 = getlog10fo2(t, p, FO2_IW);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_p3)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_P3);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_p2)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_P2);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_p1)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_P1);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_m1)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_M1);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_m2)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_M2);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_m3)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_M3);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_m4)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_M4);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_m5)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_M5);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_m6)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_M6);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_m7)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_M7);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_m8)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_M8);
  else if (XmToggleButtonGadgetGetState(tg_path_fmq_m9)) 
    log10fo2 = getlog10fo2(t, p, FO2_QFM_M9);

  moles = (double *) malloc((unsigned) nc*sizeof(double));
  for (j=0; j<nc; j++) moles[j] = compositionValues[j].value/bulkSystem[j].mw;
  conLiq(FIRST | SEVENTH, FIRST, t, p, moles, (double *) NULL, (double *) NULL,
    (double *) NULL, (double **) NULL, (double ***) NULL, &log10fo2);
  for (j=0, sum=0.0; j<nc; j++) {
    compositionValues[j].value = moles[j]*bulkSystem[j].mw;
    sum += compositionValues[j].value;
    if (compositionValues[j].value != 0.0) {
      sprintf(compositionEntry, "%7.4f", compositionValues[j].value);
      XmTextSetString(compositionValues[j].name, compositionEntry);
    }
  }

  updateStatusADB(STATUS_ADB_INDEX_MASS_LIQUID, &sum);

  free(moles);
}

/*
 *=============================================================================
 * Menu bar toggle button gadgets
 */

void mb_tg_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData; 
  XmToggleButtonCallbackStruct *callback_data = 
    (XmToggleButtonCallbackStruct *) cbDataGen;
  Arg arg_set[20];
  int i;
  switch (callback_data->reason) {

  case XmCR_VALUE_CHANGED :

    if (workProcData.active) {
       XtRemoveWorkProc(workProcId);
       workProcData.active = FALSE;
    } 

    if (tag == k_mb_tg_mode_normal) {
      if (callback_data->set) {

        workProc          = silmin;
        
        if ((preclb_adb != (Widget) NULL) && XtIsManaged(preclb_adb)) {
          XtUnmanageChild(preclb_adb);
        } else if ((postclb_adb != (Widget) NULL) && XtIsManaged(postclb_adb)) {
          XtUnmanageChild(postclb_adb);
        }

        if (!XtIsManaged(silmin_adb)) {
          i = 0;
          XtSetArg(arg_set[i], XmNworkWindow, silmin_adb); i++;
          XtSetValues(main_window, arg_set, i);
          XtManageChild(silmin_adb);
        }

        if (!XtIsSensitive(bt_liquidus))            XtSetSensitive(bt_liquidus, TRUE);
        if (!XtIsSensitive(bt_open))                XtSetSensitive(bt_open,     TRUE);
        if (!XtIsSensitive(bt_save))                XtSetSensitive(bt_save,     TRUE);
        if (!XtIsSensitive(bt_save_as))             XtSetSensitive(bt_save_as,  TRUE);

        if (!XtIsSensitive(composition_entry))      XtSetSensitive(composition_entry, TRUE);
        if (!XtIsSensitive(intensive_entry))        XtSetSensitive(intensive_entry, TRUE);
        
        if (!XtIsSensitive(tg_isenthalpic))         XtSetSensitive(tg_isenthalpic, TRUE);           
        if (!XtIsSensitive(tg_isentropic))          XtSetSensitive(tg_isentropic, TRUE);
        if (!XtIsSensitive(tg_isochoric))           XtSetSensitive(tg_isochoric, TRUE);
        if (!XtIsSensitive(tg_fractionate_solids))  XtSetSensitive(tg_fractionate_solids, TRUE);
        if (!XtIsSensitive(tg_fractionate_liquids)) XtSetSensitive(tg_fractionate_liquids, TRUE);
        if (!XtIsSensitive(tg_fractionate_fluids))  XtSetSensitive(tg_fractionate_fluids, TRUE);
        if (!XtIsSensitive(tg_multiple_liquids))    XtSetSensitive(tg_multiple_liquids, TRUE);
        
        if (XtIsSensitive(tg_1_bar_only))           XtSetSensitive(tg_1_bar_only, FALSE);
        if (XtIsSensitive(tg_low_p_only))           XtSetSensitive(tg_low_p_only, FALSE);
        if (XtIsSensitive(tg_high_p_only))          XtSetSensitive(tg_high_p_only, FALSE);
             
        if (XtIsSensitive(tg_anhydrous_only))       XtSetSensitive(tg_anhydrous_only, FALSE);
        if (XtIsSensitive(tg_hydrous_only))         XtSetSensitive(tg_hydrous_only, FALSE);

        if (XtIsSensitive(tg_oxygen_calib))         XtSetSensitive(tg_oxygen_calib, FALSE);

        if (XtIsSensitive(tg_trust_region_method))  XtSetSensitive(tg_trust_region_method, FALSE);
        if (XtIsSensitive(tg_implement_bounds))     XtSetSensitive(tg_implement_bounds, FALSE);
        if (XtIsSensitive(tg_t_regression))         XtSetSensitive(tg_t_regression, FALSE);
      }

    } else if (tag == k_mb_tg_mode_pre) {
      if (callback_data->set) {

        if (preclb_adb == (Widget) NULL) create_preclb();
        workProc          = preclb;

        if (XtIsManaged(silmin_adb)) {
          XtUnmanageChild(silmin_adb);
        } else if ((postclb_adb != (Widget) NULL) && XtIsManaged(postclb_adb)) {
          XtUnmanageChild(postclb_adb);
        }

        if (!XtIsManaged(preclb_adb)) {
          i = 0;
          XtSetArg(arg_set[i], XmNworkWindow, preclb_adb); i++;
          XtSetValues(main_window, arg_set, i);
          XtManageChild(preclb_adb);
        }

        if (XtIsSensitive(bt_liquidus))             XtSetSensitive(bt_liquidus, FALSE);
        if (!XtIsSensitive(bt_open))                XtSetSensitive(bt_open,     TRUE);
        if (XtIsSensitive(bt_save))                 XtSetSensitive(bt_save,     FALSE);
        if (XtIsSensitive(bt_save_as))              XtSetSensitive(bt_save_as,  FALSE);

        if (XtIsSensitive(composition_entry))       XtSetSensitive(composition_entry, FALSE);
        if (XtIsSensitive(intensive_entry))         XtSetSensitive(intensive_entry, FALSE);
        
        if (XtIsSensitive(tg_isenthalpic))          XtSetSensitive(tg_isenthalpic, FALSE);           
        if (XtIsSensitive(tg_isentropic))           XtSetSensitive(tg_isentropic, FALSE);
        if (XtIsSensitive(tg_isochoric))            XtSetSensitive(tg_isochoric, FALSE);
        if (XtIsSensitive(tg_fractionate_solids))   XtSetSensitive(tg_fractionate_solids, FALSE);
        if (XtIsSensitive(tg_fractionate_liquids))  XtSetSensitive(tg_fractionate_liquids, FALSE);
        if (XtIsSensitive(tg_fractionate_fluids))   XtSetSensitive(tg_fractionate_fluids, FALSE);
        if (XtIsSensitive(tg_multiple_liquids))     XtSetSensitive(tg_multiple_liquids, FALSE);
        
        if (!XtIsSensitive(tg_1_bar_only))          XtSetSensitive(tg_1_bar_only, TRUE);
        if (!XtIsSensitive(tg_low_p_only))          XtSetSensitive(tg_low_p_only, TRUE);
        if (!XtIsSensitive(tg_high_p_only))         XtSetSensitive(tg_high_p_only, TRUE);
	
        if (!XtIsSensitive(tg_anhydrous_only))      XtSetSensitive(tg_anhydrous_only, TRUE);
        if (!XtIsSensitive(tg_hydrous_only))        XtSetSensitive(tg_hydrous_only, TRUE);

        if (!XtIsSensitive(tg_oxygen_calib))        XtSetSensitive(tg_oxygen_calib, TRUE);

        if (!XtIsSensitive(tg_trust_region_method)) XtSetSensitive(tg_trust_region_method, TRUE);
        if (!XtIsSensitive(tg_implement_bounds))    XtSetSensitive(tg_implement_bounds, TRUE);
        if (!XtIsSensitive(tg_t_regression))        XtSetSensitive(tg_t_regression, TRUE);
      }

    } else if (tag == k_mb_tg_mode_post) {
      if (callback_data->set) {

        if (postclb_adb == (Widget) NULL) create_postclb();
        workProc          = postclb;

        if (XtIsManaged(silmin_adb)) {
          XtUnmanageChild(silmin_adb);
        } else if ((preclb_adb != (Widget) NULL) && XtIsManaged(preclb_adb)) {
          XtUnmanageChild(preclb_adb);
        }

        if (!XtIsManaged(postclb_adb)) {
          i = 0;
          XtSetArg(arg_set[i], XmNworkWindow, postclb_adb); i++;
          XtSetValues(main_window, arg_set, i);
          XtManageChild(postclb_adb);
        }

        if (XtIsSensitive(bt_liquidus))             XtSetSensitive(bt_liquidus, FALSE);
        if (XtIsSensitive(bt_open))                 XtSetSensitive(bt_open,     FALSE);
        if (XtIsSensitive(bt_save))                 XtSetSensitive(bt_save,     FALSE);
        if (XtIsSensitive(bt_save_as))              XtSetSensitive(bt_save_as,  FALSE);

        if (XtIsSensitive(composition_entry))       XtSetSensitive(composition_entry, FALSE);
        if (XtIsSensitive(intensive_entry))         XtSetSensitive(intensive_entry, FALSE);
             
        if (XtIsSensitive(tg_isenthalpic))          XtSetSensitive(tg_isenthalpic, FALSE);           
        if (XtIsSensitive(tg_isentropic))           XtSetSensitive(tg_isentropic, FALSE);
        if (XtIsSensitive(tg_isochoric))            XtSetSensitive(tg_isochoric, FALSE);
        if (XtIsSensitive(tg_fractionate_solids))   XtSetSensitive(tg_fractionate_solids, FALSE);
        if (XtIsSensitive(tg_fractionate_liquids))  XtSetSensitive(tg_fractionate_liquids, FALSE);
        if (XtIsSensitive(tg_fractionate_fluids))   XtSetSensitive(tg_fractionate_fluids, FALSE);
        if (XtIsSensitive(tg_multiple_liquids))     XtSetSensitive(tg_multiple_liquids, FALSE);
        
        if (!XtIsSensitive(tg_1_bar_only))          XtSetSensitive(tg_1_bar_only, TRUE);
        if (!XtIsSensitive(tg_low_p_only))          XtSetSensitive(tg_low_p_only, TRUE);
        if (!XtIsSensitive(tg_high_p_only))         XtSetSensitive(tg_high_p_only, TRUE);
	
        if (!XtIsSensitive(tg_anhydrous_only))      XtSetSensitive(tg_anhydrous_only, TRUE);
        if (!XtIsSensitive(tg_hydrous_only))        XtSetSensitive(tg_hydrous_only, TRUE);

        if (!XtIsSensitive(tg_oxygen_calib))        XtSetSensitive(tg_oxygen_calib, TRUE);

        if (!XtIsSensitive(tg_trust_region_method)) XtSetSensitive(tg_trust_region_method, TRUE);
        if (!XtIsSensitive(tg_implement_bounds))    XtSetSensitive(tg_implement_bounds, TRUE);
        if (!XtIsSensitive(tg_t_regression))        XtSetSensitive(tg_t_regression, TRUE);
      }

    } else if (tag == k_mb_tg_composition_fo2path_abs) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "undef");

    } else if (tag == k_mb_tg_composition_fo2path_HM) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "HM");

    } else if (tag == k_mb_tg_composition_fo2path_NNO) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "NNO");

    } else if (tag == k_mb_tg_composition_fo2path_QFM) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ");

    } else if (tag == k_mb_tg_composition_fo2path_COH) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "C-COH");

    } else if (tag == k_mb_tg_composition_fo2path_IW) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "IW");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_P3) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ+3");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_P2) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ+2");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_P1) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ+1");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_M1) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ-1");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_M2) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ-2");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_M3) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ-3");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_M4) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ-4");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_M5) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ-5");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_M6) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ-6");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_M7) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ-7");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_M8) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ-8");

    } else if (tag == k_mb_tg_compos_fo2path_QFM_M9) {
      if (callback_data->set) 
        updateStatusADB(STATUS_ADB_INDEX_LOGFO2+STATUS_ADB_INDEX_STRING, "FMQ-9");

    } else if (tag == k_mb_tg_options_isenthalpic) {
      if (callback_data->set) {
        XmToggleButtonSetState(tg_isentropic, False, False);
        XmToggleButtonSetState(tg_isochoric,  False, False);
      }

    } else if (tag == k_mb_tg_options_isentropic) {
      if (callback_data->set) {
        XmToggleButtonSetState(tg_isenthalpic, False, False);
        XmToggleButtonSetState(tg_isochoric,   False, False);
      }

    } else if (tag == k_mb_tg_options_isochoric) {
      if (callback_data->set) {
        XmToggleButtonSetState(tg_isenthalpic, False, False);
        XmToggleButtonSetState(tg_isentropic,  False, False);
      }

    } else if (tag == k_mb_tg_options_fractionate_solids) {
      if (callback_data->set) {
        ;
      }

    } else if (tag == k_mb_tg_options_fractionate_liquids) {
      if (callback_data->set) {
        ;
      }

    } else if (tag == k_mb_tg_options_fractionate_fluids) {
      if (callback_data->set) {
        ;
      }

    } else if (tag == k_mb_tg_options_multiple_liquids) {
      if (callback_data->set) {
        ;
      }
      
    } else if (tag == k_mb_tg_options_1_bar_only) {
      if (callback_data->set) {
        XmToggleButtonSetState(tg_low_p_only, False, False);
        XmToggleButtonSetState(tg_high_p_only, False, False);
      }
      
    } else if (tag == k_mb_tg_options_low_p_only) {
      if (callback_data->set) {
        XmToggleButtonSetState(tg_1_bar_only, False, False);
        XmToggleButtonSetState(tg_high_p_only, False, False);
      }

    } else if (tag == k_mb_tg_options_high_p_only) {
      if (callback_data->set) {
        XmToggleButtonSetState(tg_1_bar_only, False, False);
        XmToggleButtonSetState(tg_low_p_only, False, False);
      }

    } else if (tag == k_mb_tg_options_anhydrous_only) {
      if (callback_data->set) {
        XmToggleButtonSetState(tg_hydrous_only, False, False);
      }

    } else if (tag == k_mb_tg_options_hydrous_only) {
      if (callback_data->set) {
        XmToggleButtonSetState(tg_anhydrous_only, False, False);
      }

    } else if (tag == k_mb_tg_options_oxygen_calib) {
      if (callback_data->set) {
        ;
      }

    } else if (tag == k_mb_tg_options_trust_region_method) {
      if (callback_data->set) {
        ;
      }

    } else if (tag == k_mb_tg_options_implement_bounds) {
      if (callback_data->set) {
        ;
      }

    } else if (tag == k_mb_tg_options_t_regression) {
      if (callback_data->set) {
        ;
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

/*
 *=============================================================================
 * Main window drawn button widgets
 */

void launch_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  long tag = (long) cData;
  XmAnyCallbackStruct *cbData = (XmAnyCallbackStruct *) cbDataGen;
  Arg arg_set[20];
  int i;

  switch (cbData->reason) {
  case XmCR_ACTIVATE :
    if        (tag == LAUNCH_GRAPH_DISPLAY) {
      if (!launchUserGraphGW(w)) {
        ERROR("Launch failed.\nCannot find xmgr.");
      }

    } else if (tag == LAUNCH_GRAPH_OPTIONS) {
      if (xy_plot_padb == (Widget) NULL) create_xy_plot_padb();
      XtManageChild(xy_plot_padb);

    } else if (tag == LAUNCH_CALCULATOR) {
      char *argv[3];
      argv[0] = meltsEnviron.WWW_BROWSER;
      argv[1] = meltsEnviron.WWW_CALCULATOR;
      argv[2] = NULL;

      INFORMATION(
      "Launching local WWWeb Browser to access the calculator.")

      execItem[BC_LAUNCH_CALCULATOR].pid    = 0;
      execItem[BC_LAUNCH_CALCULATOR].button = NULL;

      switch (execItem[BC_LAUNCH_CALCULATOR].pid = fork()) {
        case 0:
          execvp(argv[0], argv);
          perror(argv[0]);
          _exit(255);
        case -1:
          ERROR("Launch failed.\nCannot find WWW browser.");
      }
      if (execItem[BC_LAUNCH_CALCULATOR].pid > 0) {
        execItem[BC_LAUNCH_CALCULATOR].button = w;
        XtSetSensitive (w, False);
      }

    } else if (tag == LAUNCH_VIEWER) {

    }
    break;
  case XmCR_HELP :
    MESSAGE(cs_nohelp);
    break;
  default:
    break;

  }
}

#undef INFORMATION
#undef ERROR

static void reset_btn(XtPointer client_data, XtIntervalId *id)
{
  Widget w = (Widget) client_data;
  XtSetSensitive(w, True);
  return;
}

void signalDeathOfChild(int dummy)
{
  int pid, status, i;

  if ((pid = wait(&status)) == -1) return;
  for (i=0; i<nExecItem; i++) {
    if (execItem[i].pid == pid) {
      XtAppContext app = XtDisplayToApplicationContext(XtDisplay(topLevel));
      execItem[i].pid = 0;
      XtAppAddTimeOut(app, 0, reset_btn, execItem[i].button);
      execItem[i].button = NULL;
      return;
    }
  }
  printf ("Pid #%d ???\n", pid);
  return;
}

void killChildren(void)
{
  int i;

  for(i=0; i<nExecItem; i++) 
    if (execItem[i].pid != 0) (void) kill(execItem[i].pid, SIGKILL);
  return;
}

/* end of file BUTTON_CALLBACKS.C */
