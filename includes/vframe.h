#ifndef _vFrame_h
#define _vFrame_h

/*
MELTS Source Code: RCS $Log: vframe.h,v $
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
 * Revision 3.6  1997/06/21  22:49:19  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:22:58  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:03  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:34:56  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  19:20:06  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  19:20:06  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include file for vframe widget (file: VFRAME.H)
**
**      This module contains the C-language declarations needed to use the 
**      VFrame widget.  Include this file into any C module that directly 
**      uses a VFrame widget.
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Original Version
**              COPYRIGHT (c) 1988, 1989  BY
**              DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASSACHUSETTS.
**              ALL RIGHTS RESERVED.
**              28-Dec-1989 (sjk) Version X2.0 update.
**              01-Aug-1989 (sjk) Initial entry.
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**--
*/

extern WidgetClass vframeWidgetClass;

#define VFrameNresizeCallback	"resizeCallback"
#define VFrameCRResize		1

typedef struct _VFrameClassRec *VFrameWidgetClass;
typedef struct _VFrameRec      *VFrameWidget;

typedef struct {
    int		reason;
    XEvent	*event;
} VFrameResizeCallbackStruct;

Widget VFrameCreate(Widget w, char *name, Arg *args, int argCnt);

#endif /* _vFrame_h */
