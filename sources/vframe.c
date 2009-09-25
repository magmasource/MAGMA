const char *vframe_ver(void) { return "$Id: vframe.c,v 1.2 2006/08/17 16:47:19 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: vframe.c,v $
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:19  ghiorso
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
 * Revision 3.6  1997/06/21  22:49:19  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:22:59  ghiorso
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
 * Revision 3.1  1995/08/18  19:19:42  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  19:19:42  ghiorso
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
**      This module implements the VFrame widget.  The VFrame widget is a 
**      simple container for other widgets.  The primary purpose of the 
**      VFrame widget is to provide a resize callback.
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
**      V2.0-2  Mark S. Ghiorso  February 19, 1992
**              Added redefinition of XtOffset macro for ANSI C compliance
**      V2.0-3  Mark S. Ghiorso  March 28, 1992
**              Corrected violation for R4 and ANSI C compliance
**      V3.0-1  Mark S. Ghiorso  September 24, 1993
**              (1) Brought code into strict compliance with X11 R5/Motif 1.2
**                  standards
**--
*/

#include <Xm/XmP.h>

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>

#include "vframe.h"

typedef struct {
    int			notused;
} VFrameClassPart;

typedef struct _VFrameClassRec {
    CoreClassPart	core_class;
    CompositeClassPart	composite_class;
    VFrameClassPart	vframe_class;
} VFrameClassRec;

extern VFrameClassRec vframeClassRec;

typedef struct _VFrameRec {
    CorePart		core;		/* core widget fields */
    CompositePart	composite;	/* composite widget fields */

    /* resources */
    XtCallbackList	resizeCallback;	/* resize callback */

    /* private context */
} VFrameRec;

static void DoChangeManaged(Widget w)
{
}

static XtGeometryResult DoGeometryManager(Widget w, 
  XtWidgetGeometry *requestP, XtWidgetGeometry *replyP)
{
    if (requestP->request_mode & CWX)      w->core.x = requestP->x;
    if (requestP->request_mode & CWY)      w->core.y = requestP->y;
    if (requestP->request_mode & CWWidth)  w->core.width = requestP->width;
    if (requestP->request_mode & CWHeight) w->core.height = requestP->height;
    if (requestP->request_mode & CWBorderWidth)
	w->core.border_width = requestP->border_width;

    return (XtGeometryYes);		/* just say yes */
}

static void DoResize(Widget gW)
{
    VFrameWidget w = (VFrameWidget) gW;
    VFrameResizeCallbackStruct cbData;

    cbData.reason = VFrameCRResize;
    cbData.event = 0;

    XtCallCallbacks ((Widget) w, VFrameNresizeCallback, (XtPointer) &cbData);
}

static void DoRealize(Widget gW, XtValueMask *maskP, 
  XSetWindowAttributes *attributesP)
{
    VFrameWidget w = (VFrameWidget) gW;

    if (!w->core.width) w->core.width = 1;
    if (!w->core.height) w->core.height = 1;

    XtCreateWindow ((Widget) w, InputOutput, CopyFromParent, *maskP, 
      attributesP);
}

#define Offset(x) XtOffsetOf (VFrameRec, x)

static XtResource resources[] = {
    {VFrameNresizeCallback, XtCCallback, XtRCallback, sizeof (XtCallbackList),
	Offset (resizeCallback), XtRCallback, 0}
};

CompositeClassExtensionRec compositeClassExtensionRec = {
        /* next_extenion        */      NULL,
        /* record_type          */      NULLQUARK,
        /* version              */      XtCompositeExtensionVersion,
        /* record_size          */      sizeof(CompositeClassExtensionRec),
        /* accepts_objects      */      False
};

VFrameClassRec vframeClassRec = {
    {/* core class fields	*/
	/* superclass		*/	(WidgetClass) &compositeClassRec,
	/* class_name		*/	"VFrame",
	/* widget_size		*/	sizeof (VFrameRec),
	/* class_initialize	*/	NULL,
	/* class_part_initialize */	NULL,
	/* class_inited		*/	FALSE,
	/* initialize		*/	NULL,
	/* initialize_hook	*/	NULL,
	/* realize		*/	DoRealize,
	/* actions		*/    	NULL,
	/* num_actions	  	*/	0,
	/* resources		*/	resources,
	/* num_resources	*/	XtNumber (resources),
	/* xrm_class		*/	NULLQUARK,
	/* compress_motion	*/	FALSE,
	/* compress_exposure	*/	FALSE,
	/* compress_enterleave	*/	FALSE,
	/* visible_interest	*/	FALSE,
	/* destroy		*/	NULL,
	/* resize		*/	DoResize,
	/* expose		*/	NULL,
	/* set_values		*/	NULL,
	/* set_values_hook	*/	NULL,
	/* set_values_almost	*/	XtInheritSetValuesAlmost,
	/* get_values_hook	*/	NULL,
	/* accept_focus		*/	NULL,
	/* version		*/	XtVersionDontCheck,
	/* callback_private	*/	NULL,
	/* tm_table		*/	NULL,
	/* query_geometry	*/	NULL,
	/* display_accelerator	*/	NULL,
	/* extension		*/	NULL
    },
    {/* composite class fields	*/
	/* geometry_manager	*/	DoGeometryManager,
	/* change_managed	*/	DoChangeManaged,
	/* insert_child		*/	XtInheritInsertChild,
	/* delete_child		*/	XtInheritDeleteChild,
	/* extension		*/	(XtPointer) &compositeClassExtensionRec
    }
};

WidgetClass vframeWidgetClass = (WidgetClass) &vframeClassRec;

Widget VFrameCreate(pW, nameP, argsP, argCnt)
    Widget pW;
    char *nameP;
    Arg *argsP;
    int argCnt;
{
    return (XtCreateWidget (nameP, vframeWidgetClass, pW, argsP, argCnt));
}

/* end of file VFRAME.C */
