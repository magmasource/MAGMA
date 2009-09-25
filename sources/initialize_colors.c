const char *initialize_colors_ver(void) { return "$Id: initialize_colors.c,v 1.2 2006/08/17 16:47:18 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: initialize_colors.c,v $
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
 * Revision 3.6  1997/06/21  22:49:52  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:23:31  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:34  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:33:38  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  17:36:03  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  17:36:03  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Function to acquire Pixel values for required colors. Method is to 
**      interegate the default colormap (file: INIALIZE_COLORS.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  August 24, 1990   Original Version
**      V1.0-2  Mark S. Ghiorso  August 31, 1991
**              Supressed output of purely informational messages.
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  February 18, 1992
**              (1) Minor corrections for ANSI compliant casting
**              (2) Removed global dependence on i
**      V2.0-3  Mark S. Ghiorso  March 28, 1992
**              Corrected casting violations for ANSI C compliance
**--
*/

#include <stdlib.h>
#include <stdio.h>
#include <Xm/Xm.h> 

#include "interface.h"                      /*Specific external declarations  */

Pixel white, black, red, green, blue, gray; /* These variables are extern     */

void initialize_colors()
{
  white = WhitePixel(XtDisplay(topLevel), DefaultScreen(XtDisplay(topLevel)));
  black = BlackPixel(XtDisplay(topLevel), DefaultScreen(XtDisplay(topLevel)));
  {
    String color = "red";
    XColor col, unused;
    if (XAllocNamedColor (XtDisplay (topLevel), DefaultColormapOfScreen (XtScreen (topLevel)), color, &col, &unused)) red = col.pixel;
    else red = black; 
  }
  {
    String color = "blue";
    XColor col, unused;
    if (XAllocNamedColor (XtDisplay (topLevel), DefaultColormapOfScreen (XtScreen (topLevel)), color, &col, &unused)) blue = col.pixel;
    else blue = black; 
  }
  {
    String color = "green";
    XColor col, unused;
    if (XAllocNamedColor (XtDisplay (topLevel), DefaultColormapOfScreen (XtScreen (topLevel)), color, &col, &unused)) green = col.pixel;
    else green = black; 
  }
  {
    String color = "gray";
    XColor col, unused;
    if (XAllocNamedColor (XtDisplay (topLevel), DefaultColormapOfScreen (XtScreen (topLevel)), color, &col, &unused)) gray = col.pixel;
    else gray = black;
  }
}

/* end of file INITIALIZE_COLORS.C */
