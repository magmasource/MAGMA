#ifndef _Interface_h
#define _Interface_h

/*
MELTS Source Code: RCS $Log: interface.h,v $
MELTS Source Code: RCS Revision 1.3  2007/02/21 21:51:18  ghiorso
MELTS Source Code: RCS New regressions options and parameter selection buttons
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2006/10/20 00:59:22  ghiorso
MELTS Source Code: RCS (1) Made initial modifications for thread safe code.
MELTS Source Code: RCS (2) Added support for XML I/O in batch mode
MELTS Source Code: RCS (3) Added support for Melts-batch listener for eventual integration into VIGMCS
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:48:56  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.9  1997/06/21  22:49:51  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.8  1997/05/03  20:23:30  ghiorso
 * *** empty log message ***
 *
 * Revision 3.7  1997/03/27  17:03:33  ghiorso
 * *** empty log message ***
 *
 * Revision 3.6  1996/09/24  20:33:37  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.5  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.4  1995/09/04  19:59:58  ghiorso
 * Update to allow display of bulk composition (in grams) in the text entry
 * fields of the main silmin display. Liquid composition is no longer
 * display here, and is available only through the popup selection.
 *
 * Revision 3.4  1995/09/04  19:59:58  ghiorso
 * Update to allow display of bulk composition (in grams) in the text entry
 * fields of the main silmin display. Liquid composition is no longer
 * display here, and is available only through the popup selection.
 *
 * Revision 3.3  1995/09/01  23:54:46  ghiorso
 * Modifications made to update interface for V3.x and consolidate
 * Graph Widgets
 *
 * Revision 3.2  1995/08/31  00:31:48  ghiorso
 * Changed help widget to invoke dialogs and WEB browser.
 * Removed graphics menu entry and toggle button entries.
 *
 * Revision 3.1  1995/08/18  17:44:18  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      User Interface include file (file: INTERFACE.H)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  August 23, 1990   Original Version
**      V1.0-2  Mark S. Ghiorso  August 30, 1991
**              (1) Removed widget creation macro definitions
**              (2) Made menu bar entry and button widgets globally
**                  known
**              (3) Removed hardcopy menu entry and button widgets
**              (4) Removed callback tags and callback declarations that
**                  needn't be global
**      V1.0-3  Mark S. Ghiorso  August 31, 1991
**              Cleaned-up a number of extern/global declarations. All
**              extern variables are now defined globally in the appropriate
**              module
**      V1.0-4  Mark S. Ghiorso  September 1, 1991
**              Added getInputDataFromFile global declaration and 
**              made extern declarations of other functions ANSI 
**      V1.0-5  Mark S. Ghiorso  September 3, 1991
**              (1) Removed separate storage for status in includedSolids
**                  structure
**              (2) altered magmaValues, assimilantValues and tpValues 
**                  structures
**              (3) Defined certain toggle button widgets of the menu bar
**                  as global as in (V1.0-2)
**              (4) altered phases and debugEntries structures and defined
**                  more global macros for debug label widgets
**              (5) as in (4) for statusEntries
**              (6) added global macros for extra assimilant and magma mixing
**                  text widgets
**      V1.0-6  Mark S. Ghiorso  September 4, 1991
**              (1) Added units display information structure for
**                  assimilant_padb
**              (2) Added global macros to describe units display in
**                  solid_adb
**      V1.0-7  Mark S. Ghiorso  September 6, 1991
**              Added workProcData structure, and ANSI function defns for
**              XtWorkProcedures
**      V1.0-8  Mark S. Ghiorso  September 7, 1991
**              (1) Added declaraction of new liquidus work procedure
**              (2) Added cs_strings halt_me_first and empty_string
**      V1.0-9  Mark S. Ghiorso  September 9, 1991
**              (1) Made debug and plot toggles global widgets
**      V1.0-10 Mark S. Ghiorso  September 13, 1991
**              Added client_data pointer to the preclbRank structure
**      V1.0-11 Mark S. Ghiorso  September 20, 1991
**              (1) Added tg_incl_frac to global widget list
**              (2) Removed nyi_callback() declaration
**      V1.0-12 Mark S. Ghiorso  October 18, 1991
**              (1) Added globally known widget for silmin display popup
**                  attached dialog box for graph legend
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**              (1) Added declaration of wprintf function which is 
**                  temporarily defined in create_minos.c
**      V2.0-2  Mark S. Ghiorso  November 23, 1991
**              (1) Removed debug entries from silmin display and menu bar
**              (2) Removed unreferenced global widgets for the silmin 
**                  display and the popup dialog for graph legends
**              (3) Removed postclb_padb1 and postclb_padb2 widget declarations
**              (4) Added more message widgets
**      V2.0-3  Mark S. Ghiorso  November 27, 1991
**              (1) Removed phases[] array and changed graph_legend widget
**                  to phases widget.
**              (2) Added popup menu option to choose mode of display for
**                  log fo2 in the status box
**      V2.0-4  Mark S. Ghiorso  December 10, 1991
**              (1) Removed magma_padb and related buttons and callbacks
**      V2.0-5  Mark S. Ghiorso  December 13, 1991
**              (1) changed caddr_t pointer declaration (R3) to 
**                  XtPointer (R4)
**              (2) changed tpValues structures to eliminate widgets 
**              (3) altered preclbRank structure to eliminate pseudovariable
**                  in function declaration, i.e...
**                  void (*fillANOVA) (int rank);  => void (*fillANOVA) (int);
**                  (this is necessary for RISC C compliance)
**                               December 18, 1991
**              (4) Removed magma mix status entry
**              (5) item (3) revoked, RISC C is non-ANSI
**      V2.0-6  Mark S. Ghiorso  January 6, 1992
**              (1) Added declaration of two new functions:
**                  putInputDataToFile(), putOutputDataToFile()
**      V2.0-7  Mark S. Ghiorso  February 19, 1992
**              Removed references to all local variables. These became
**              multiply defined in ANSI C implementations
**      V2.0-8  Mark S. Ghiorso  March 27, 1992
**              Corrected prototype definitions for global callback procs
**      V2.0-9  Mark S. Ghiorso  June 14, 1993
**              Added new fo2 path toggle constants
**      V2.0-10 Mark S. Ghiorso March 12, 1994
**              (1) Added external declaration of create_minos().
**      V2.0-11 Mark S. Ghiorso April 23, 1994
**              Corrected declaration of typedef for preclb work_proc structure
**      V3.0-1  Mark S. Ghiorso May 11, 1994
**              (1) Added declaration of global toggle button tg_isentropic
**              (2) Added external declaration of k_mb_tg_options_isentropic
**              (3) Removed Grove and Walker entries from graphics options
**                              June 10, 1994
**              (4) Added new defines for TP_PADB tpValues instances
**              (5) Rearranged TP_PADB entries
**--
*/

/*
 *=============================================================================
 * List of globally known Widgets:
 *
 *     Name:                 Type of widget:
 */
extern
Widget caution,              /* caution dialog box = warning_message */
       cmw,                  /* color mixing dialog box              */
       error_message,        /* error message dialog box             */
       file_selection,       /* file selection dialog box            */
       info_message,         /* informational message dialog box     */
       main_window,          /* main window                          */ 
       menu_bar,             /* menu bar                             */
       message,              /* message dialog box = info_message    */
       question_message,     /* question message dialog box          */
       topLevel,             /* shell                                */
       warning_message,      /* warning message dialog box           */
       working_message,      /* working message dialog box           */

       called_caution,       /* widget identifier for widget which   */
                             /*   invoked the caution widget         */
       called_fs,            /* widget identifier for widget which   */
                             /*   invoked the file selection widget  */

       /* menu bar menu entry widgets which must be external so they */
       /*   can be de-sensitized as command mode changes             */
       command_entry, edit_entry, composition_entry, intensive_entry, 
       options_entry, help_entry, mode_entry, fO2_path_entry,

       /* button widgets of the command menu that must be external   */
       /*   they can be de-sensitized or identified                  */
       bt_exit, bt_liquidus, bt_open, bt_save, bt_save_as,

       /* toggle button widgets of the various menus that must be    */
       /* external so that they can be set from getInputDataFromFile */
       /* or read by DwtGetToggleButtonState                         */

       /* !!!!! The following gadgets form a radio group -> */
       tg_path_none, tg_path_hm, tg_path_nno, tg_path_fmq, tg_path_coh, 
       tg_path_iw,
       tg_path_fmq_p3, tg_path_fmq_p2, tg_path_fmq_p1, tg_path_fmq_m1,
       tg_path_fmq_m2, tg_path_fmq_m3, tg_path_fmq_m4, tg_path_fmq_m5,
       tg_path_fmq_m6, tg_path_fmq_m7, tg_path_fmq_m8, tg_path_fmq_m9,  
       /* <- end radio group !!!!! */
       /* !!!!! The following gadgets form a radio group -> */
       tg_isenthalpic, tg_isentropic, tg_isochoric, 
       /* <- end radio group !!!!! */
       tg_fractionate_solids, tg_fractionate_liquids, tg_multiple_liquids,
       tg_fractionate_fluids, 
       /* !!!!! The following gadgets form a radio group -> */
       tg_1_bar_only, tg_low_p_only, tg_high_p_only, 
       /* <- end radio group !!!!! */
       /* !!!!! The following gadgets form a radio group -> */
       tg_anhydrous_only, tg_hydrous_only, 
       /* <- end radio group !!!!! */
       /* !!!!! The following gadgets are either on or off -> */
       tg_oxygen_calib, tg_trust_region_method, tg_implement_bounds, 
       tg_t_regression,
       /* <- end radio group !!!!! */


       /* Widgets of silmin display                                  */  
       phases, silmin_adb, compPDmenu,

       /* pop up attached dialog box widgets of the silmin display   */
       tp_padb, solid_padb, assimilant_padb, xy_plot_padb,

       /* attached dialog box widgets of pre-calibration display     */
       preclb_adb, action_adb, phase_adb, component_adb, mrqrdt_adb, 

       /* Widget ID's for label widgets in action and mrqrdt boxes of */
       /*   of the preclb display (note: these point to array)       */
       *actionADB, *mrqrdtADB,

       /* attached dialog box, popup dialog box and vlist widgets of */
       /*   the post-calibration display                             */
       postclb_adb, postclb_statistics, postclb_outliers;
 
/*
 *=============================================================================
 * List of known colors: white and black are guaranteed to exist.
 *                       on a B/W system red, green and blue are set to black
 */
extern Pixel white, black, red, green, blue, gray;

/*
 *=============================================================================
 * List of globally known compound strings:
 *
 *            Name:
 */
extern
XmString cs_caution_exit,
         cs_caution_generic,
         cs_fs_nocontext,
         cs_fs_noconversion,
         cs_fs_nosuchfile,
         cs_fs_cancel,
         cs_fs_dirMask_io,
         cs_fs_dirMask_ps,
         cs_nohelp,
         cs_not_yet_implemented,
         cs_halt_me_first,
         cs_empty_string;

/*
 *=============================================================================
 * Global macros
 *
 */

#define MESSAGE(COMPOUND_STRING) \
  XtVaSetValues(message, XmNmessageString, COMPOUND_STRING, NULL); \
  XtManageChild(message)

/*
 *=============================================================================
 * Callback tags that must be declared global:
 */
extern /* toggle widgets (toggle_callback) defined in create_menu_bar.c      */
int k_mb_tg_mode_normal, k_mb_tg_mode_pre,
    k_mb_tg_mode_post, k_mb_tg_composition_fo2path_abs, 
    k_mb_tg_composition_fo2path_HM, k_mb_tg_composition_fo2path_NNO,
    k_mb_tg_composition_fo2path_QFM, k_mb_tg_composition_fo2path_COH, 
    k_mb_tg_composition_fo2path_IW,
    k_mb_tg_compos_fo2path_QFM_P3, k_mb_tg_compos_fo2path_QFM_P2, 
    k_mb_tg_compos_fo2path_QFM_P1, k_mb_tg_compos_fo2path_QFM_M1, 
    k_mb_tg_compos_fo2path_QFM_M2, k_mb_tg_compos_fo2path_QFM_M3, 
    k_mb_tg_compos_fo2path_QFM_M4, k_mb_tg_compos_fo2path_QFM_M5, 
    k_mb_tg_compos_fo2path_QFM_M6, k_mb_tg_compos_fo2path_QFM_M7, 
    k_mb_tg_compos_fo2path_QFM_M8, k_mb_tg_compos_fo2path_QFM_M9, 
    k_mb_tg_options_isenthalpic, k_mb_tg_options_isochoric,
    k_mb_tg_options_fractionate_solids, k_mb_tg_options_isentropic,
    k_mb_tg_options_fractionate_liquids, k_mb_tg_options_multiple_liquids,
    k_mb_tg_options_1_bar_only, k_mb_tg_options_low_p_only, k_mb_tg_options_high_p_only,
    k_mb_tg_options_anhydrous_only, k_mb_tg_options_hydrous_only,
    k_mb_tg_options_oxygen_calib, k_mb_tg_options_trust_region_method, 
    k_mb_tg_options_implement_bounds, k_mb_tg_options_t_regression, 
    k_mb_tg_options_fractionate_fluids;

extern /* button widdgets (button_callback) defined in create_menu_bar.c     */
int k_mb_bt_command_liquidus, k_mb_bt_command_execute_halt, 
    k_mb_bt_command_open, k_mb_bt_command_save, k_mb_bt_command_save_as,
    k_mb_bt_command_exit, k_mb_bt_edit_copy, k_mb_bt_edit_paste, 
    k_mb_bt_edit_select_all, k_mb_bt_composition_redox,
    k_mb_bt_composition_normalize, k_mb_bt_intensive_TP, 
    k_mb_bt_options_assimilant, k_mb_bt_options_solids,
    k_mb_bt_help_about, k_mb_bt_help_manual, k_mb_bt_options_increase_quad_tol,
    k_mb_bt_options_restore_quad_tol;

/*
 *=============================================================================
 * Callback tags associated with launch buttons on the main window:
 */
#define LAUNCH_GRAPH_DISPLAY 0
#define LAUNCH_GRAPH_OPTIONS 1
#define LAUNCH_CALCULATOR    2
#define LAUNCH_VIEWER        3

/*
 *=============================================================================
 * Global functions used as callbacks:
 *
 *   Name:                 Widget: (bt = button gadget)
 */
void mb_bt_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
void mb_tg_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
void compPDcallback(Widget w, XtPointer cData, XtPointer cbDataGen);
void launch_callback(Widget w, XtPointer cData, XtPointer cbDataGen);

/*
 *=============================================================================
 * Other external functions and return value macros:
 */
void create_assimilant_padb(void);
void create_managed(void);
void create_menu_bar(void);
void create_popup_table(void);
void create_postclb(void);
void create_preclb(void);
void create_solid_padb(void);
void create_tp_padb(void);
void create_unmanaged(void);
void create_xy_plot_padb(void);
void debugMainLoop(XtAppContext app_context);
int  getAlternateDataBaseFile(char *fileName);
int  getInputDataFromFile(char *fileName);
void initialize_colors(void);
void initialize_strings(void);
void killChildren(void);
Boolean launchUserGraphGW(Widget w);
int  putInputDataToFile(char *fileName);
int  putOutputDataToFile(char *fileName);
void signalDeathOfChild(int dummy);
void updateStatusADB(int member, XtPointer value);
int  wprintf(Widget w, char *fmt, ...);

#define GET_INPUT_SUCCESS        0
#define GET_INPUT_ERROR_BAD_FILE 1
#define GET_INPUT_ERROR_BAD_READ 2

/*
 *=============================================================================
 *      Work proceedures:
 */

typedef struct _workProcData {
  Boolean active;     /* TRUE if workProc is currently active, FALSE if idle  */
  Boolean mode;       /* tag: TRUE if user has altered something on the
                              interface, FALSE if this a simple return        */
} WorkProcData;


Boolean liquidus(XtPointer);  /* (file LIQUIDUS.C)                           */
Boolean postclb(XtPointer);   /* (file POSTCLB.C)                            */
Boolean preclb(XtPointer);    /* (file PRECLB.C)                             */
Boolean silmin(XtPointer);    /* (file SILMIN.C)                             */

/*
 *=============================================================================
 * Globally accessible variables (silmin structures):
 */
typedef struct _compositionValues {
  Widget name;    /* widget identifier of the text entry widget */
  double value;   /* current value of contents of text entry    */
} CompositionValues;

extern CompositionValues *compositionValues;

extern int units_phase_display;   /* units for solid_adb display */

#define SOLID_ADB_UNITS_GRAMS  1
#define SOLID_ADB_UNITS_VOLUME 2
#define SOLID_ADB_UNITS_WEIGHT 3

typedef struct _statusEntries {
  Widget name;          /* label widget ID */
} StatusEntries;

extern StatusEntries *statusEntries;

typedef struct _compEntries {
  Widget name;          /* label widget ID */
} CompEntries;

extern CompEntries *compEntries;

#define STATUS_ADB_INDEX_T             0
#define STATUS_ADB_INDEX_P             1
#define STATUS_ADB_INDEX_LOGFO2        2
#define STATUS_ADB_INDEX_MASS_LIQUID   3
#define STATUS_ADB_INDEX_MASS_SOLID    4
#define STATUS_ADB_INDEX_MASS_ASSIM    5
#define STATUS_ADB_INDEX_MASS_FRAC     6
#define STATUS_ADB_INDEX_STATUS        7
#define STATUS_ADB_INDEX_PHASE         8
#define STATUS_ADB_INDEX_QUADRATIC     9
#define STATUS_ADB_INDEX_LINEAR       10
#define STATUS_ADB_INDEX_STRING      100

extern int units_logfo2_display; /* units for status_adb display */

#define LOGFO2_UNITS_VALUE   0
#define LOGFO2_UNITS_HM      1
#define LOGFO2_UNITS_NNO     2
#define LOGFO2_UNITS_QFM     3
#define LOGFO2_UNITS_COH     4
#define LOGFO2_UNITS_IW      5

typedef struct _tpValues {
  double value;                  /* value of display */
} TpValues;

extern TpValues *tpValues;

#define TP_PADB_INDEX_T_INITIAL    0
#define TP_PADB_INDEX_T_FINAL      1
#define TP_PADB_INDEX_T_INCREMENT  2
#define TP_PADB_INDEX_P_INITIAL    3
#define TP_PADB_INDEX_P_FINAL      4
#define TP_PADB_INDEX_P_INCREMENT  5
#define TP_PADB_INDEX_DPDT         6
#define TP_PADB_INDEX_H_INCREMENT  7
#define TP_PADB_INDEX_DPDH         8
#define TP_PADB_INDEX_S_INCREMENT  9
#define TP_PADB_INDEX_DPDS        10
#define TP_PADB_INDEX_V_INCREMENT 11
#define TP_PADB_INDEX_DTDV        12

typedef struct _assimilantValues {
  double *value;        /* displayed value of assimilant in assimilant_padb  */
  int    ns;            /* number of elements in value[]                     */
} AssimilantValues;

extern AssimilantValues *assimilantValues;

#define ASSIM_PADB_INDEX_MASS        0  /* + npc + nc */
#define ASSIM_PADB_INDEX_T           1  /* + npc + nc */
#define ASSIM_PADB_INDEX_INCREMENT   2  /* + npc + nc */
#define ASSIM_PADB_INDEX_LIQUID_MASS 3  /* + npc + nc */

typedef struct _assimilantUnits {
  int    units;        /* current value of units display - see macro below   */
} AssimilantUnits;

extern AssimilantUnits assimilantUnits;

#define ASSIM_PADB_UNITS_VOLUME 0
#define ASSIM_PADB_UNITS_WEIGHT 1

typedef struct _includedSolids {
  Widget  name;   /* ID of toggle button widget                     */
} IncludedSolids;

extern IncludedSolids *includedSolids;

/*
 *=============================================================================
 * Globally accessible variables (preclb structures involving the user
 *                                interface):
 */

typedef struct _preclbCount {
   Boolean usePhase; /* TRUE/FALSE flag for including exp data on a phase    */ 
   Boolean absPhase; /* TRUE/FALSE flag for generating phase absent 
                        constraints for a particular phase                   */ 
   Widget  present;  /* Widget ID of label widget to display count of number 
                        of experimental data for a particular solid phase    */ 
   int     np;       /* Number of entries in the database                    */
   Widget  absent;   /* Widget ID of label widget to display count of number 
                        of generated phase absent constraints for a 
                        particular solid phase                               */
   int     na;       /* Number of generated phase absent constraints         */
} PreclbCount;
extern PreclbCount *preclbCount; /* entries in phase present/absent box      */

/*
 *=============================================================================
 * Globally accessible environment and option variables:
 */

typedef struct _meltsEnviron {
  char *AUTHOR_LIST;
  char *DATA_DIR;
  char *DATA_SUFFIX;
  char *HARDWARE_VERSION;
  char *INPUT_DIR;
  char *INPUT_SUFFIX;
  char *MOTIF_VERSION;
  char *OS_VERSION;
  char *OUTPUT_FILE;
  char *WWW_BROWSER;
  char *WWW_CALCULATOR;
  char *WWW_MANUAL;
  char *X_VERSION;
  char *RELEASE_DATE;
  char *RELEASE_VERSION;
  int  DEBUG;
} MeltsEnviron;

extern MeltsEnviron meltsEnviron;

#endif /* _Interface_h */
