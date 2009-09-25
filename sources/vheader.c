const char *vheader_ver(void) { return "$Id: vheader.c,v 1.3 2006/08/17 20:47:54 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: vheader.c,v $
MELTS Source Code: RCS Revision 1.3  2006/08/17 20:47:54  ghiorso
MELTS Source Code: RCS Clarified variable initialization issues in routines.  Problems discovered
MELTS Source Code: RCS when compiler optimization is turned on.
MELTS Source Code: RCS
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
 * Revision 3.6  1997/06/21  22:49:18  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:22:58  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:02  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:34:55  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  19:20:35  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  19:20:35  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include file for vHeader widget (file: VHEADER.C)
**
**      This module implements the VHeader widget.  It contains all the action
**      routines, special routines and widget data structures necessary
**      to create and manipulate a VHeader widget.  Compile this module and 
**      link the resulting object into any executable image that uses the 
**      VHeader widget.
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Original Version
**              COPYRIGHT (c) 1988, 1989  BY
**              DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASSACHUSETTS.
**              ALL RIGHTS RESERVED.
**              28-Dec-1989 (sjk) Version X2.0 update.
**              07-Dec-1989 (sjk) Initial entry.
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  November 25, 1991
**              Converted VHeaderNfontTable to a dynamic resource variable
**              which defaults to the XmlabelFontList of the manager 
**              parent or to the XmNdefaultFontList of the Vendor shell
**              parent. The resource VHeaderNfontTable is now 
**              VHeaderNfontList. Added error messages.
**      V2.0-3  Mark S. Ghiorso  February 19, 1992
**              Added redefinition of XtOffset macro for ANSI C compliance
**              and corected various non-ANSI problems
**      V2.0-4  Mark S. Ghiorso  March 28, 1992
**              Corrected R4 and ANSI C violations
**      V2.0-5  Mark S. Ghiorso  September 21, 1993
**              Corrected a number of X11/R5 Motif 1.2 function decl
**--
*/

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>

#include <Xm/Xm.h>
#include <Xm/BulletinB.h>

#include "vheader.h"

typedef struct {
    int			notused;
} VHeaderClassPart;

typedef struct _VHeaderClassRec {
    CoreClassPart	core_class;
    VHeaderClassPart	vheader_class;
} VHeaderClassRec;

extern VHeaderClassRec vheaderClassRec;

typedef struct {
    VHeaderLabel	vLabel;		/* clone of supplied values */
    int			textStrlen;	/* length in bytes of text */
    int			y;		/* y-position of text */
} LabelInfo;

typedef struct _VHeaderRec {		/* Widget record */
    CorePart		core;		/* Core widget fields */

    /* Resource fields */
    int			bottomMarginHeight;
    XmFontList		fontListP;
    Pixel		foreground;
    int			labelCnt;
    VHeaderLabel	*labelsP;
    int			spacingHeight;
    int			topMarginHeight;
    int			xAdjust;

    /* Private fields */
    Opaque		beginZeroInit;
    int			charHeight;	/* char height in pixels */
    int			externalXAdjust; /* recently acknowledged position */
    LabelInfo		*labelInfosP;	/* array of LabelInfo entries */
    GC			normgc;		/* graphics context */
    int			requestedXAdjust; /* recently requested position */
    int			scrollIsActive; /* XCopyArea is in progress */
    int			yFontAdjust;	/* adjustment for text positioning */
    Opaque		endZeroInit;
} VHeaderRec;

static void FreeLabels(w)
    VHeaderWidget w;
{
    LabelInfo *lInfoP;
    int label;

    for (label=0, lInfoP=w->labelInfosP; label<w->labelCnt; label++, lInfoP++)
	XtFree (lInfoP->vLabel.textP);
}

static void CopyLabels(w)
    VHeaderWidget w;
{
    VHeaderLabel *vLabelP;
    LabelInfo *lInfoP;
    int label;

    if (!w->labelCnt) return;

    w->labelInfosP = (LabelInfo *) XtRealloc ((char *) w->labelInfosP,
	w->labelCnt * sizeof (LabelInfo));

    for (label=0, vLabelP=w->labelsP, lInfoP=w->labelInfosP;
      label<w->labelCnt; label++, vLabelP++, lInfoP++) {
	lInfoP->vLabel = *vLabelP;
	lInfoP->vLabel.textP = XtNewString (lInfoP->vLabel.textP);
    }

    w->labelsP = (VHeaderLabel *) NULL; /* was -1; and don't look at it again */
}

static void ComputeLabelInfo(w)
    VHeaderWidget w;
{
    int label;
    LabelInfo *lInfoP;

    if (!w->labelCnt) return;

    for (label=0, lInfoP=w->labelInfosP; label<w->labelCnt; label++, lInfoP++) {
        lInfoP->textStrlen = strlen (lInfoP->vLabel.textP);

	lInfoP->y = w->topMarginHeight
	    + lInfoP->vLabel.row * (w->charHeight + w->spacingHeight);
    }
}

static void Draw(w, lInfoP)
    VHeaderWidget w;
    LabelInfo *lInfoP;
{
    XDrawString (XtDisplay (w), XtWindow (w), w->normgc,
	lInfoP->vLabel.x - w->requestedXAdjust, lInfoP->y + w->yFontAdjust,
	lInfoP->vLabel.textP, lInfoP->textStrlen);
}

static void DrawExposedRegion(w, vX, y, width, height)
    VHeaderWidget w;
    int vX, y, width, height;
{
    int label;
    LabelInfo *lInfoP;

    for (label=0, lInfoP=w->labelInfosP; label<w->labelCnt; label++, lInfoP++)
	if (((lInfoP->vLabel.x + lInfoP->vLabel.width) > vX)
	  && ((vX + width) > lInfoP->vLabel.x)
	  && ((lInfoP->y + w->charHeight) > y)
	  && ((y + height) > lInfoP->y)) Draw (w, lInfoP);
}

static void SetPosition(w)
    VHeaderWidget w;
{
    w->externalXAdjust = w->requestedXAdjust = w->xAdjust;
}

static void AdjustPosition(w)
    VHeaderWidget w;
{
    if (w->xAdjust == w->requestedXAdjust) return;	/* nothing to do */
    if (w->scrollIsActive) return;			/* already busy */

    XCopyArea (XtDisplay (w), XtWindow (w), XtWindow (w), w->normgc,
	w->xAdjust - w->externalXAdjust, 0,
	w->core.width, w->core.height, 0, 0);

    w->requestedXAdjust = w->xAdjust;
    w->scrollIsActive = 1;
}

static void NonmaskableEventHandler(Widget gW, XtPointer client_data, 
  XEvent *eventP, Boolean *continue_to_dispatch)
{
    VHeaderWidget w = (VHeaderWidget) gW;

    if ((eventP->xany.type != GraphicsExpose) &&
        (eventP->xany.type != NoExpose)) return;

    if (eventP->xany.type == GraphicsExpose) {
	DrawExposedRegion (w, eventP->xgraphicsexpose.x + w->requestedXAdjust,
	    eventP->xgraphicsexpose.y, eventP->xgraphicsexpose.width,
	    eventP->xgraphicsexpose.height);
    
	if (eventP->xgraphicsexpose.count) return;
    }

    w->externalXAdjust = w->requestedXAdjust;
    w->scrollIsActive = 0;

    AdjustPosition (w);
}

static void DoInitialize(Widget gRequest, Widget gW, 
  ArgList args, Cardinal *num_args)
{
    VHeaderWidget w       = (VHeaderWidget) gW;

    char *cP;
    XmFontContext context; 
    XmStringCharSet charset; 
    XFontStruct *fontP;

    for (cP = (char *)(&w->beginZeroInit); cP != (char *)(&w->endZeroInit); ) 
      *(cP++) = 0;

    /* Use first font in list. */

    if(XmFontListInitFontContext(&context, w->fontListP)) {
      if(XmFontListGetNextFont(context, &charset, &fontP)) {
        w->charHeight = fontP->max_bounds.descent + fontP->max_bounds.ascent;
        w->yFontAdjust = fontP->max_bounds.ascent;
        CopyLabels (w);
        XtFree(charset);
      } else
        XtAppErrorMsg(XtWidgetToApplicationContext((Widget) w), 
          "Internal Error", "wrongParameters", "VHeaderWidget", 
          "Cannot extract font from specified font list.",
          (String *) NULL, (Cardinal *) NULL);
      XmFontListFreeFontContext(context);
    } else
      XtAppErrorMsg(XtWidgetToApplicationContext((Widget) w), 
        "Internal Error", "wrongParameters", "VHeaderWidget", 
        "Cannot initialize font context from specified font list.",
        (String *) NULL, (Cardinal *) NULL);
}

static void DoRealize(w, maskP, attributesP)
    VHeaderWidget w;
    Mask *maskP;
    XSetWindowAttributes *attributesP;
{
    XGCValues values;
    XmFontContext context; 
    XmStringCharSet charset; 
    XFontStruct *fontP;

    ComputeLabelInfo (w);

    if (!w->core.width) w->core.width = 1;
    if (!w->core.height) w->core.height = 1;

    XtAddEventHandler ((Widget) w, (EventMask) 0, (Boolean) 1, 
      NonmaskableEventHandler, (XtPointer) w);

    XtCreateWindow ((Widget) w, InputOutput, CopyFromParent, *maskP, 
      attributesP);

    if(XmFontListInitFontContext(&context, w->fontListP)) {
      if(XmFontListGetNextFont(context, &charset, &fontP)) {
        values.font = fontP->fid;
        values.foreground = w->foreground;
        values.background = w->core.background_pixel;
        values.function = GXcopy;
        w->normgc = XtGetGC ((Widget) w,
	    GCFont | GCForeground | GCBackground | GCFunction, &values);
        XtFree(charset);
      } else
        XtAppErrorMsg(XtWidgetToApplicationContext((Widget) w), 
          "Internal Error", "wrongParameters", "VHeaderWidget", 
          "Cannot extract font from specified font list.",
          (String *) NULL, (Cardinal *) NULL);
      XmFontListFreeFontContext(context);
    } else
      XtAppErrorMsg(XtWidgetToApplicationContext((Widget) w), 
        "Internal Error", "wrongParameters", "VHeaderWidget", 
        "Cannot initialize font context from specified font list.",
        (String *) NULL, (Cardinal *) NULL);
}

static void DoExpose(Widget gW, XEvent *gEventP, Region region)
{
    VHeaderWidget w      = (VHeaderWidget) gW;
    XExposeEvent *eventP = (XExposeEvent *) gEventP;

    DrawExposedRegion (w, eventP->x + w->externalXAdjust, eventP->y,
	eventP->width, eventP->height);
}

#define Changed(f) (w->f != oldW->f)

static Boolean DoSetValues(Widget gOldW, Widget gRefW, Widget gW, 
    ArgList args, Cardinal *num_args)
{
    VHeaderWidget oldW = (VHeaderWidget) gOldW;
    VHeaderWidget w    = (VHeaderWidget) gW;

    int redraw = 0;

    if (Changed (labelsP) || Changed (labelCnt)) {
	FreeLabels (oldW);
	CopyLabels (w);
	if (XtIsRealized ((Widget) w)) ComputeLabelInfo (w);
	redraw = 1;
    }

    if (Changed (xAdjust)) {
	if (redraw || (!XtIsRealized ((Widget) w))) SetPosition (w);
	else AdjustPosition (w);
    }

    return (redraw);
}

static void getDefaultFontList(Widget w, int offset, XrmValue *value)
{
  static XmFontList defaultFontList;

  while((w = XtParent(w)) != (Widget) NULL) {
    if (XtIsSubclass(w, xmBulletinBoardWidgetClass)) {
      XtVaGetValues(w, XmNlabelFontList, &defaultFontList, NULL);   break;
    } else if (XtIsVendorShell(w)) {
      XtVaGetValues(w, XmNdefaultFontList, &defaultFontList, NULL); break;
    }
  }

  /* The vheader widget must be a descendent of either a Motif manager
     widget or a topLevel or dialog shell widget. Managers are subclasses 
     of the Bulletin Board and topLevel and dialog shells are subclasses
     of the Vendor shell                                                  */

  if (w == (Widget) NULL) XtAppErrorMsg(XtWidgetToApplicationContext(w), 
    "Internal Error", "wrongParentage", "VHeaderWidget", 
    "This widget is not descended from a Bulletin Board or Vendor Shell.",
    (String *) NULL, (Cardinal *) NULL);

  value->addr = (XtPointer) &defaultFontList;
}

#define Offset(x) XtOffsetOf (VHeaderRec, x)

static XtResource resources[] = {
 {VHeaderNbottomMarginHeight, XtCValue, XtRInt, sizeof(int),
  Offset(bottomMarginHeight), XtRString, "1"},
 {VHeaderNfontList, XtCValue, XmRFontList, sizeof(XmFontList),
  Offset(fontListP), XmRCallProc, (XtPointer) getDefaultFontList}, 
 {VHeaderNforeground, XtCForeground, XtRPixel, sizeof(Pixel),
  Offset(foreground), XtRString, XtDefaultForeground},
 {VHeaderNlabelCount, XtCValue, XtRInt, sizeof(int),
  Offset(labelCnt), XtRString, "0"},
 {VHeaderNlabels, XtCValue, XtRPointer, sizeof(VHeaderLabel *),
  Offset(labelsP), XtRImmediate, NULL},
 {VHeaderNspacingHeight, XtCValue, XtRInt, sizeof(int),
  Offset(spacingHeight), XtRString, "1"},
 {VHeaderNtopMarginHeight, XtCValue, XtRInt, sizeof(int),
  Offset(topMarginHeight), XtRString, "1"},
 {VHeaderNxAdjust, XtCValue, XtRInt, sizeof(int),
  Offset(xAdjust), XtRString, "0"},
};

VHeaderClassRec vheaderClassRec = {
    {/* core_class fields	*/
	/* superclass		*/	(WidgetClass) &widgetClassRec,
	/* class_name	  	*/	"VHeader",
	/* widget_size	  	*/	sizeof (VHeaderRec),
	/* class_initialize   	*/    	0,
	/* class_part_initialize */	0,
	/* class_inited       	*/	0,
	/* initialize	  	*/	DoInitialize,
	/* initialize_hook	*/	0,
	/* realize		*/	DoRealize,
	/* actions		*/    	0,
	/* num_actions	  	*/	0,
	/* resources	  	*/	resources,
	/* num_resources	*/	XtNumber (resources),
	/* xrm_class	  	*/	0,
	/* compress_motion	*/	0,
	/* compress_exposure  	*/	0,
	/* compress_enterleave	*/	0,
	/* visible_interest	*/	0,
	/* destroy		*/	0,
	/* resize		*/	0,
	/* expose		*/	DoExpose,
	/* set_values	  	*/	DoSetValues,
	/* set_values_hook	*/	0,
	/* set_values_almost  	*/	XtInheritSetValuesAlmost,
	/* get_values_hook    	*/	0,
	/* accept_focus	  	*/	0,
	/* version		*/	XtVersionDontCheck,
	/* callback_private   	*/	0,
	/* tm_table		*/	0,
	/* query_geometry	*/	0,
	/* display_accelerator	*/	0,
	/* extension		*/	0
  }
};

WidgetClass vheaderWidgetClass = (WidgetClass) &vheaderClassRec;

Widget VHeaderCreate(pW, nameP, argsP, argCnt)
    Widget pW;
    char *nameP;
    Arg *argsP;
    int argCnt;
{
    return (XtCreateWidget (nameP, vheaderWidgetClass, pW, argsP, argCnt));
}

int VHeaderComputeLabelWidth(pW, textP)
    Widget pW;
    char *textP;
{
    VHeaderWidget w = (VHeaderWidget) pW;
    XmFontContext context; 
    XmStringCharSet charset; 
    XFontStruct *fontP;
    XCharStruct *charP    = NULL;
    unsigned int firstCol = 0;
    unsigned int numCols  = 0;
    unsigned int c;
    int width = 0;
    char *chP = textP;

    if(XmFontListInitFontContext(&context, w->fontListP)) {
      if(XmFontListGetNextFont(context, &charset, &fontP)) {
        charP = fontP->per_char;
        firstCol = fontP->min_char_or_byte2;
        numCols = fontP->max_char_or_byte2 - firstCol + 1;
        XtFree(charset);
      } else
        XtAppErrorMsg(XtWidgetToApplicationContext((Widget) w), 
          "Internal Error", "wrongParameters", "VHeaderWidget", 
          "Cannot extract font from specified font list.",
          (String *) NULL, (Cardinal *) NULL);
      XmFontListFreeFontContext(context);
    } else
      XtAppErrorMsg(XtWidgetToApplicationContext((Widget) w), 
        "Internal Error", "wrongParameters", "VHeaderWidget", 
        "Cannot initialize font context from specified font list.",
        (String *) NULL, (Cardinal *) NULL);

    while (*chP) {
	c = *(chP++) - firstCol;
	if (c < numCols) width += (charP + c)->width;
    }

    return (width);
}

int VHeaderComputeLogicalHeight(pW, rows)
    Widget pW;
    int rows;
{
    VHeaderWidget w = (VHeaderWidget) pW;
    return (rows * w->charHeight + (rows - 1) * w->spacingHeight
        + w->topMarginHeight + w->bottomMarginHeight);
}

/* end of file VHEADER.C */
