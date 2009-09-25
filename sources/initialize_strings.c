const char *initialize_strings_ver(void) { return "$Id: initialize_strings.c,v 1.2 2006/08/17 16:47:18 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: initialize_strings.c,v $
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:18  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
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
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.7  1997/06/21  22:49:52  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.6  1997/05/03  20:23:30  ghiorso
 * *** empty log message ***
 *
 * Revision 3.5  1997/03/27  17:03:34  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1996/09/24  20:33:38  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.3  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.2  1995/08/30  17:52:00  ghiorso
 * Removed help library entry
 *
 * Revision 3.2  1995/08/30  17:52:00  ghiorso
 * Removed help library entry
 *
 * Revision 3.1  1995/08/18  17:36:43  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Function to initialize required compound strings.
**      (file: INIALIZE_STRINGS.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  August 24, 1990   Original Version
**      V1.0-2  Mark S. Ghiorso  September 7, 1991
**              Added more strings
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  March 30, 1992
**              Defined generic macro for help sources
**--
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Xm/Xm.h> 

#include "interface.h"            /*Specific external declarations          */

/******************************************************************************
 * Globally known compound strings declared extern in INTERFACE.H
 ******************************************************************************/

XmString cs_caution_exit, cs_caution_generic, cs_fs_nocontext,
              cs_fs_noconversion, cs_fs_nosuchfile, cs_fs_cancel,
              cs_fs_dirMask_io, cs_fs_dirMask_ps, cs_nohelp,
              cs_not_yet_implemented, cs_halt_me_first,
              cs_empty_string;


void initialize_strings()
{
  /* caution widget */
  cs_caution_exit = XmStringCreateLtoR(
    "Are you certain you want to exit the MELTS program?", "ISO8859-1");
  cs_caution_generic = XmStringCreateLtoR(
    "The caution widget has been managed for no particular reason!", 
    "ISO8859-1");

  /* file selection widget */
  cs_fs_nocontext = XmStringCreateLtoR(
    "Failure to initialize compound string context", "ISO8859-1");
  cs_fs_noconversion = XmStringCreateLtoR(
    "Failure of String Conversion routine.", "ISO8859-1");
  cs_fs_nosuchfile = XmStringCreateLtoR(
    "Error in file name. User action cancelled.", "ISO8859-1");
  cs_fs_cancel = XmStringCreateLtoR(
    "File name selection cancelled. User action cancelled." , "ISO8859-1");
  cs_fs_dirMask_io = XmStringCreateLtoR("*.melts", "ISO8859-1");
  cs_fs_dirMask_ps = XmStringCreateLtoR("*.ps", "ISO8859-1");

  /* general strings */
  cs_nohelp = XmStringCreateLtoR(
    "Sorry, context specific help is not available.", "ISO8859-1");
  cs_not_yet_implemented = XmStringCreateLtoR(
    "Selected option has not yet been implemented.", "ISO8859-1");
  cs_halt_me_first = XmStringCreateLtoR(
    "Please use the  Halt...  command before executing this option.", 
    "ISO8859-1");
  cs_empty_string = XmStringCreateLtoR("", "ISO8859-1");
}

/* end of file INITIALIZE_STRINGS.C */
