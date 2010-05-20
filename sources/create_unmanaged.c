const char *create_unmanaged_ver(void) { return "$Id: create_unmanaged.c,v 1.2 2006/08/17 16:47:18 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: create_unmanaged.c,v $
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
 * Revision 3.7  1997/06/21  22:50:00  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.6  1997/05/03  20:23:39  ghiorso
 * *** empty log message ***
 *
 * Revision 3.5  1997/03/27  17:03:42  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1996/09/24  20:33:45  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.3  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.2  1995/08/31  00:32:56  ghiorso
 * Changed help widget to invoke dialogs and WEB browser.
 * Removed graphics menu entry and toggle button entries.
 *
 * Revision 3.2  1995/08/31  00:32:56  ghiorso
 * Changed help widget to invoke dialogs and WEB browser.
 * Removed graphics menu entry and toggle button entries.
 *
 * Revision 3.1  1995/08/18  17:27:31  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Function to create the following dialog children of the main_window
**        caution         - a warning dialog box
**        message         - a message dialog box
**        file_selection  - a file selection dialog box
**        if DIGITAL ->
**        cmw             - a color mixing dialog box
**        help            - a help dialog box
**
**      Defines callback routines for
**        caution        (message_callback)
**        cmw            (cmw_callback)
**        file_selection (fs_callback)
**        help           (help_callback)
**      (file: CREATE_UNMANAGED.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  August 24, 1990   Original Version
**      V1.0-2                                     Added caution widget
**      V1.0-3  Mark S. Ghiorso  August  9, 1991   Added color mixing widget
**      V1.0-4  Mark S. Ghiorso  August 29, 1991
**              Modified fs_callback to be more generic by testing for
**              the widget identifier (stored in called_fs) that invoked
**              the callback. Also defined global space for called_caution,
**              called_fs and called_help widget identifiers
**              Modified caution widget to be called generically and display
**              various messages
**      V1.0-5  Mark S. Ghiorso  August 31, 1991
**              reassigned global symbols as static to clean up INTERFACE.H
**      V1.0-6  Mark S. Ghiorso  September 1, 1991
**              Added call to getInputDataFromFile when file selection
**              widget is invoked from the open button of the command menu
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  November 26, 1991
**              (1) Motif enhancements including the full set of
**                  message dialog boxes
**                               December 6, 1991
**              (2) Corrected DXm color mix callback reason for ok...
**              (3) Numerous cosmetic changes to widget sensitivity. Removed
**                  Cancel button from information dialog.
**      V2.0-3  Mark S. Ghiorso  December 21, 1991
**              (1) Made cancel button in error_message insensitive
**      V2.0-4  Mark S. Ghiorso  January 4, 1992
**              (1) Altered resource declarations for graph widget from
**                  XtN -> GwN
**              (2) Altered hardcopy() -> GwHardcopy()
**      V2.0-5  Mark S. Ghiorso  January 6, 1992
**              (1) added call to putInputDataToFile()
**      V2.0-6  Mark S. Ghiorso  February 18, 1992
**              (1) Minor modifications for "casting" rules in ANSI C
**              (2) Removed global dependence on arg_set and i
**      V2.0-7  Mark S. Ghiorso  March 17, 1992
**              Added macros for non-DEC Motif extensions
**      V2.0-8  Mark S. Ghiorso  March 27, 1992
**              Corrected casting violations in callback routines
**      V2.0-9  Mark S. Ghiorso  June 14, 1993
**              Removed call to desensitize "Apply" button in file selection
**              widget. This allows file Filtering.
**      V2.0-10 Mark S. Ghiorso  March 21, 1994
**              Fixed XtFree(topic) to XmStringFree(topic)
**      V2.0-11 Mark S. Ghiorso  April 23, 1994
**              Corrected casting violations in callback routines
**--
*/

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <Xm/FileSB.h>
#include <Xm/MessageB.h>
#include <Xm/SelectioB.h>
#include <Xm/Text.h>

#include "interface.h"

#define _DO_NOT_DISABLE_WPRINTF

/******************************************************************************
 * Globally known widgets and tags declared extern in INTERFACE.H
 ******************************************************************************/

Widget caution, cmw, error_message, file_selection, info_message,
       message, question_message, warning_message, working_message;

Widget called_caution,         /* These pseudo-widget declarations are used */ 
       called_fs;              /* in the callback routines in this module   */ 

static void fs_callback(Widget w, XtPointer cData, XtPointer cbDataGen);
static void message_callback(Widget w, XtPointer cData, XtPointer cbDataGen);

void create_unmanaged()
{
  Arg arg_set[20];
  /* SELECTION DIALOGS------------------------------------------------------ */
  file_selection = XmCreateFileSelectionDialog(main_window, "FileSelection", 
    NULL, 0);
  XtAddCallback(file_selection, XmNokCallback,     fs_callback, (XtPointer) 0);
  XtAddCallback(file_selection, XmNcancelCallback, fs_callback, (XtPointer) 0);
  XtAddCallback(file_selection, XmNhelpCallback,   fs_callback, (XtPointer) 0);
  XtSetSensitive(
    XmSelectionBoxGetChild(file_selection, XmDIALOG_HELP_BUTTON),  False);
  XtVaSetValues(XtParent(file_selection), XmNtitle, "File Selection", NULL);

  /* MESSAGE DIALOGS-------------------------------------------------------- */
  XtSetArg(arg_set[0], XmNdefaultButtonType, XmDIALOG_CANCEL_BUTTON);
  warning_message = XmCreateWarningDialog(main_window, "Warning", arg_set, 1);
  XtAddCallback(warning_message, XmNokCallback,     message_callback,
                (XtPointer) XmDIALOG_WARNING);
  XtAddCallback(warning_message, XmNcancelCallback, message_callback,
                (XtPointer) XmDIALOG_WARNING);
  XtAddCallback(warning_message, XmNhelpCallback,   message_callback,
                (XtPointer) XmDIALOG_WARNING);
  XtSetSensitive(
    XmMessageBoxGetChild(warning_message, XmDIALOG_HELP_BUTTON),  False);
  XtVaSetValues(XtParent(warning_message), XmNtitle, "Warning Message", NULL);
  caution = warning_message;

  XtSetArg(arg_set[0], XmNdefaultButtonType, XmDIALOG_OK_BUTTON);
  info_message = XmCreateInformationDialog(main_window, "Information", 
    arg_set, 1);
  XtAddCallback(info_message, XmNokCallback,     message_callback,
                (XtPointer) XmDIALOG_INFORMATION);
  XtAddCallback(info_message, XmNhelpCallback,   message_callback,
                (XtPointer) XmDIALOG_INFORMATION);
  XtUnmanageChild(XmMessageBoxGetChild(info_message, XmDIALOG_CANCEL_BUTTON));
  XtSetSensitive(
    XmMessageBoxGetChild(info_message, XmDIALOG_HELP_BUTTON),  False);
  XtVaSetValues(XtParent(info_message), XmNtitle, "Information", NULL);
  message = info_message;

  XtSetArg(arg_set[0], XmNdefaultButtonType, XmDIALOG_OK_BUTTON);
  error_message = XmCreateErrorDialog(main_window, "Error", arg_set, 1);
  XtAddCallback(error_message, XmNokCallback,     message_callback,
                (XtPointer) XmDIALOG_ERROR);
  XtAddCallback(error_message, XmNcancelCallback, message_callback,
                (XtPointer) XmDIALOG_ERROR);
  XtAddCallback(error_message, XmNhelpCallback,   message_callback,
                (XtPointer) XmDIALOG_ERROR);
  XtSetSensitive(
    XmMessageBoxGetChild(error_message, XmDIALOG_CANCEL_BUTTON),  False);
  XtSetSensitive(
    XmMessageBoxGetChild(error_message, XmDIALOG_HELP_BUTTON),  False);
  XtVaSetValues(XtParent(error_message), XmNtitle, "Error", NULL);

  XtSetArg(arg_set[0], XmNdefaultButtonType, XmDIALOG_OK_BUTTON);
  question_message = XmCreateQuestionDialog(main_window, "Question", 
    arg_set, 1);
  XtAddCallback(question_message, XmNokCallback,     message_callback,
                (XtPointer) XmDIALOG_QUESTION);
  XtAddCallback(question_message, XmNcancelCallback, message_callback,
                (XtPointer) XmDIALOG_QUESTION);
  XtAddCallback(question_message, XmNhelpCallback,   message_callback,
                (XtPointer) XmDIALOG_QUESTION);
  XtSetSensitive(
    XmMessageBoxGetChild(question_message, XmDIALOG_HELP_BUTTON),  False);
  XtVaSetValues(XtParent(question_message), XmNtitle, "Question", NULL);

  XtSetArg(arg_set[0], XmNdefaultButtonType, XmDIALOG_OK_BUTTON);
  working_message = XmCreateWorkingDialog(main_window, "Working", arg_set, 1);
  XtAddCallback(working_message, XmNokCallback,     message_callback,
                (XtPointer) XmDIALOG_WORKING);
  XtAddCallback(working_message, XmNcancelCallback, message_callback,
                (XtPointer) XmDIALOG_WORKING);
  XtAddCallback(working_message, XmNhelpCallback,   message_callback,
                (XtPointer) XmDIALOG_WORKING);
  XtSetSensitive(
    XmMessageBoxGetChild(working_message, XmDIALOG_HELP_BUTTON),  False);
  XtVaSetValues(XtParent(working_message), XmNtitle, "Working", NULL);
}

static void message_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{

  long tag = (long) cData; 
  XmAnyCallbackStruct *callback_data = (XmAnyCallbackStruct *) cbDataGen;

  switch (callback_data->reason) {

  case XmCR_OK :
    if (tag == XmDIALOG_WARNING && called_caution == bt_exit) exit(0);
  case XmCR_CANCEL :
    break;
  case XmCR_HELP :
    break;
  default:
    break;

  }
}

static void fs_callback(Widget w, XtPointer cData, XtPointer cbDataGen)
{
  XmFileSelectionBoxCallbackStruct *callback_data = 
    (XmFileSelectionBoxCallbackStruct *) cbDataGen;
  char *text;
  XmStringCharSet charset = XmSTRING_DEFAULT_CHARSET;
  static char *file_name = NULL;
  size_t n;

  switch (callback_data->reason) {

  case XmCR_OK :
    XtUnmanageChild(file_selection);
    if (!XmStringGetLtoR(callback_data->value, charset, &text)) {
      MESSAGE(cs_fs_noconversion);
      break;
    }
    n = strcspn(text,";");
    if(n != 0) {
      file_name = (char *) XtRealloc((char *) file_name, (unsigned) (n+1));
      (void) strcpy(file_name,"");
      (void) strncat(file_name, text, n);
      XtFree(text);

      if (called_fs == bt_open) {
        if(XtIsManaged(silmin_adb)) 
          (void) getInputDataFromFile(file_name);
        else if(XtIsManaged(preclb_adb)) 
          (void) getAlternateDataBaseFile(file_name);

      } else if (called_fs == bt_save_as) {
        (void) putInputDataToFile(file_name);
      }

    } else {
      MESSAGE(cs_fs_nosuchfile);
    }
    break;
  case XmCR_CANCEL :
    XtUnmanageChild(file_selection);
    MESSAGE(cs_fs_cancel);
    break;
  case XmCR_HELP :
    break;
  default:
    break;
  }

}

#define BUFFERSIZE        256  /* maximum number of char in an output record */
#define MAX_STORED_CHAR 40000  /* maximum number of char in text buffer      */
#define CHAR_DEC_COUNT  15000  /* decrement count for char in text buffer    */

int wprintf(Widget w, char *fmt, ...)
{
  static XmTextPosition position;
  char buffer[BUFFERSIZE];
  va_list args;

  if (w == NULL) return -1;

  va_start(args, fmt);
  (void) vsnprintf(buffer, BUFFERSIZE, fmt, args);
  va_end(args);

#ifdef DISABLE_WPRINTF
  printf("%s", buffer);
#else
  /* position = XmTextGetLastPosition(w); */
  
  XmTextInsert(w, position, buffer); position += strlen(buffer);

  if (position > MAX_STORED_CHAR) {
    XmTextReplace(w, 0, CHAR_DEC_COUNT, ""); position -= CHAR_DEC_COUNT;
  }

  XtVaSetValues(w, XmNcursorPosition, position, NULL);
  XmTextShowPosition(w, position);
  
  /* XmUpdateDisplay(w); */
#endif

  return (int) strlen(buffer);
}

/* end of file CREATE_UNMANAGED.C */
