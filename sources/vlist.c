const char *vlist_ver(void) { return "$Id: vlist.c,v 1.3 2006/08/17 20:47:54 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: vlist.c,v $
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
 * Revision 3.5  1997/05/03  20:22:57  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:01  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:34:54  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  19:21:22  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  19:21:22  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include file for vList widget (file: VLIST.C)
**
**      This module implements the VList widget.  It contains all the action
**      routines, special routines and widget data structures necessary
**      to create and manipulate a VList widget.  Compile this module and 
**      link the resulting object into any executable image that uses the 
**      VList widget.
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Original Version
**              COPYRIGHT (c) 1988, 1989  BY
**              DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASSACHUSETTS.
**              ALL RIGHTS RESERVED.
**              16-Jan-1990 (sjk) Bugfix - Column layout was sometimes 
**                recomputed unnecessarily. The column width reference count 
**                was not maintained properly in all cases.
**              11-Jan-1990 (sjk) Add segmented string support.  Delete lines 
**                in reverse order to minimize shuffling.
**              10-Jan-1990 (sjk) Bugfix - In VListSelectStyleSingle, 
**                downclick must not select any line that is not directly 
**                under the mouse.  Also, don't return a closure on a 
**                double-click that is over deadspace.
**              09-Jan-1990 (sjk) Add VListComputePreferredWidth routine.
**              05-Jan-1990 (sjk) Bugfix - VListGetLineInfo returns 1 on 
**                success. 
**                Bugfix - don't try to redraw lines that are not visible 
**                during an autoscrolled drag select.
**              04-Jan-1990 (sjk) Don't allow user to assign a zero closure 
**                value. 
**              03-Jan-1990 (sjk) Add VListAlignmentLeft and ~Right, and 
**                remove column and tier fields from VListSelectCallbackStruct.
**                Bugfix recalculation of logicalHeight and tierCnt when 
**                adding and removing a line.
**              28-Dec-1989 (sjk) Version X2.0 update.  Contributions from Tom
**                Foley, Keith Fieldhouse, and Dave Burleigh, among others.
**              17-Nov-1988 (sjk) Changes for stand-alone usage and public 
**                consumption.
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  November 22, 1991
**              Expanded the page increment and decrement callbacks to the 
**              horizontal and vertical scroll bar widgets to include 
**              screen updates. This is becuase a set values in Motif
**              on the scroll bar does not automatically invoke the
**              value changed callback. Also set XmNpageIncrement to an
**              arbitrary value of 1 (consistent with the arrow button 
**              increment length of the scroll bar)
**      V2.0-3  Mark S. Ghiorso  November 25, 1991
**              Converted VListNfontTable to a dynamic resource variable
**              which defaults to the XmNlabelFontList of the manager
**              parent or to the XmNdefaultFontList of the Vendor shell
**              parent. The resource VListNfontTable is now VListNfontList. 
**              Added error messages.
**      V2.0-4  Mark S. Ghiorso  January 31, 1992
**              Altered automatic declarations to conform to the ANSI standard
**              (DEC C RISC)
**      V2.0-5  Mark S. Ghiorso  February 19, 1992
**              ANSI C compliance->
**              (1) Added redefinition of XtOffset macro 
**              (2) Assorted type cast clarifications
**      V2.0-6  Mark S. Ghiorso  March 28, 1992
**              Corrected casting violations for ANSI C and R4 compliance
**      V2.0-7  Mark S. Ghiorso  September 21, 1993
**              Corrected several function declaration for R5/Motif 1.2
**              compliance
**
**--
*/


#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>

#include <Xm/Xm.h>
#include <Xm/BulletinB.h>

#include "vlist.h"
#ifdef DRAWINGA_VLIST_PARENT
#include <Xm/DrawingA.h>
#else
#include "vframe.h"
#endif
#include "vheader.h"
 
typedef struct {			/* widget class contribution */
    int			notused;
} VListClassPart;

typedef struct _VListClassRec {		/* widget class record */
    CoreClassPart	core_class;
    VListClassPart	vlist_class;
} VListClassRec;

extern VListClassRec vlistClassRec;

typedef struct {
    VListField		vField;		/* copy of user-supplied entry */
} FieldInfo;

typedef struct {
    int			x;		/* position within virtual window */
    int			width;		/* actual width */
    int			alignment;	/* alignment option */
    int			widthCnt;	/* how many have that width? */
} ColumnInfo;

typedef struct {
    VListLabel		vLabel;		/* copy of user-supplied entry */
    int			width;		/* width of label in pixels */
    int			widthPerColumn;	/* width contribution */
} LabelInfo;

typedef struct {
    VListSegment	vSegment;	/* copy of user-supplied entry */
    int			textWidth;	/* segment text width in pixels */
} SegmentInfo;

typedef struct {
    VListLine		vLine;		/* copy of user-supplied entry */
    int			textStrlen;	/* length in bytes of text */
    int			textWidth;	/* overall width of text in pixels */
    char		expose;		/* line marked for expose (1/0) */
    char		delete;		/* line marked for delete (1/0) */
    char		undoSelect;	/* selected at ButtonPress (1/0) */
    char		undragSelect;	/* selected at start of drag (1/0) */
    SegmentInfo		*segmentInfosP;	/* list of segments */
} LineInfo;

typedef struct _VListRec {		/* Widget record */
    CorePart		core;		/* Core widget fields */

    /* Resource fields */
    int			alignment;
    int			autoScrollRate;
    Pixmap		colorList;
    int			columnStyle;
    int			doubleClickDelay;
    int			fieldCnt;
    int			fieldSpacingWidth;
    VListField		*fieldsP;
    XmFontList		fontListP;
    Pixel		foreground;
    int			hScrollPolicy;
    Widget		hScrollW;
    int			labelCnt;
    VListLabel		*labelsP;
    int			marginHeight;
    int			marginWidth;
    int			rowSpacingHeight;
    XtCallbackList	selectCallback;
    XtCallbackList	selectConfirmCallback;
    int			selectStyle;
    int			selectUnit;
    int			textMarginWidth;
    Widget		vHeaderW;
    int			vScrollPolicy;
    int			vScrollPosition;
    Widget		vScrollW;

    /* Private fields */

    Opaque		beginZeroInit;
    int			anyAreDeleted;	/* some lines may be pending delete */
    int			anyAreExposed;	/* some exposures may be pending */
    int			batchUpdate;	/* batch update depth */
    int			cellHeight;	/* cell height in pixels */
    int			charHeight;	/* char height in pixels */
    int			charWidth;	/* char '0' width in pixels */
    int			colorCnt;	/* number of colors in colorTable */
    Pixel		*colorTableP;	/* array of color values */
    int			columnCnt;	/* number of physical columns */
    ColumnInfo		*columnInfosP;	/* address of ColumnInfo array */
    int			currentColoridx; /* color currently set */
    int			currentFontidx;	/* font currently set */
    int			doubleClickIsPending; /* doubleClick in progress */
    int			downColumn;	/* downclick column */
    int			downTier;	/* downclick tier */
    int			externalXAdjust; /* acknowleged scrolling position */
    int			externalYAdjust; /* acknowleged scrolling position */
    FieldInfo		*fieldInfosP;	/* address of FieldInfo array */
    GC			flipgc;		/* reverse video graphics context */
    int			fontCnt;	/* number of fonts in fontList */
    int			groupCnt;	/* number of field groups */
    int			headerHeight;	/* height desired by vHeader widget */
    int			ignoreScrollValueChanged; /* ignore callback */
    int			internalXAdjust; /* desired scrolling position */
    int			internalYAdjust; /* desired scrolling position */
    GC			invgc;		/* highlit graphics context */
    LabelInfo		*labelInfosP;	/* address of LabelInfo array */
    int			lastUsedClosure; /* widget-supplied closure counter */
    int			layoutIsValid;	/* layout is ok */
    int			lineCnt;	/* number of logical line(item)s */
    LineInfo		*lineInfosP;	/* address of LineInfo array */
    int			listIsGrabbed;	/* downclick in list area */
    int			logicalHeight;	/* virtual window's height */
    int			logicalWidth;	/* virtual window's width */
    int			maxLineCnt;	/* lines allocated in LineInfo array */
    int			mouseColumn;	/* column where mouse was last seen */
    int			mouseTier;	/* tier where mouse was last seen */
    GC			normgc;   	/* normal graphics context */
    int			requestedXAdjust; /* requested scrolling position */
    int			requestedYAdjust; /* requested scrolling position */
    int			rowCnt;		/* number of logical rows */
    int			scrollIsActive;	/* XCopyArea in progress */
    int			selectParity;	/* flavor of drag select (1/0) */
    int			selectionCnt;	/* number of selected lines */
    int			shownHeaderXAdjust; /* current header setting */
    int			shownScrollXAdjust; /* current scroll bar setting */
    int			shownScrollYAdjust; /* current scroll bar setting */
    int			tierCnt;	/* number of physical tiers */
    int			topMarginHeight; /* (pretty) top margin */
    int			undoXAdjust;	/* internalXAdjust at downclick */
    int			undoYAdjust;	/* internalYAdjust at downclick */
    int			upColumn;	/* upclick column */
    int			upTier;		/* upclick tier */
    int			upTime;		/* start time for doubleClick */
    int			visibleClosure;	/* line to be made visible */
    int			visiblePosition; /* and where */
    int			xScrollStrength; /* autoscroll speed factor */
    int			yFontAdjust;	/* adjustment for text positioning */
    int			yScrollStrength; /* autoscroll speed factor */
    Opaque		endZeroInit;
} VListRec;

static void MinMax(a, b, minP, maxP)
    int a, b, *minP, *maxP;
{
    if (a < b) {*minP = a; *maxP = b;}
    else {*minP = b; *maxP = a;}
}

static int ComputeTextWidth(w, fontidx, textP, textStrlen)
    VListWidget w;
    int fontidx, textStrlen;
    char *textP;
{
    XmFontContext context;
    XmStringCharSet charset;
    XFontStruct *fontP;
    int i, width = 0;
    char *chP = textP;
    XCharStruct *charP;
    unsigned int firstCol, numCols, c;

    if (!w->fontCnt) fontidx = 0;
    else fontidx = (fontidx % w->fontCnt);

    (void) XmFontListInitFontContext(&context, w->fontListP);

    for (i=0; i<=fontidx; i++) {
      (void) XmFontListGetNextFont(context, &charset, &fontP);
      XtFree(charset);
    }
    XmFontListFreeFontContext(context);

    charP = fontP->per_char;
    firstCol = fontP->min_char_or_byte2;
    numCols = fontP->max_char_or_byte2 - firstCol + 1;

    while (textStrlen--) {
      c = *(chP++) - firstCol;
      if (c < numCols) width += (charP+c)->width;
    }

    return (width);
}

static void ComputeSegmentDefaults(w, lineInfoP)
    VListWidget w;
    LineInfo *lineInfoP;
{
    int segment;
    SegmentInfo *segmentInfoP;

    if (!lineInfoP->vLine.segmentCount) return;

    for (segment = 0, segmentInfoP = lineInfoP->segmentInfosP;
      segment < lineInfoP->vLine.segmentCount; segment++, segmentInfoP++) {
	if (!(segmentInfoP->vSegment.mask & VListSegmentFontidxMask))
	    segmentInfoP->vSegment.fontidx = lineInfoP->vLine.fontidx;

	if (!(segmentInfoP->vSegment.mask & VListSegmentColoridxMask))
	    segmentInfoP->vSegment.coloridx = lineInfoP->vLine.coloridx;
    }
}

static void ComputeTextInfo(w, lineInfoP)
    VListWidget w;
    LineInfo *lineInfoP;
{
    int segment;
    SegmentInfo *segmentInfoP;

    if (!lineInfoP->vLine.segmentCount) {
	lineInfoP->textWidth = ComputeTextWidth (w, lineInfoP->vLine.fontidx,
	    lineInfoP->vLine.textP, lineInfoP->textStrlen);
    } else {
	lineInfoP->textWidth = 0;

	for (segment = 0, segmentInfoP = lineInfoP->segmentInfosP;
	  segment < lineInfoP->vLine.segmentCount; segment++, segmentInfoP++) {
	    segmentInfoP->textWidth = ComputeTextWidth (w,
		segmentInfoP->vSegment.fontidx,
		lineInfoP->vLine.textP + segmentInfoP->vSegment.textPosition,
		segmentInfoP->vSegment.textStrlen);

	    lineInfoP->textWidth += segmentInfoP->textWidth;
	}
    }
}

static LineInfo *LineToLineInfo(w, line)
    VListWidget w;
    int line;
{
    return (&w->lineInfosP[line]);
}

static FieldInfo *FieldToFieldInfo(w, field)
    VListWidget w;
    int field;
{
    return (&w->fieldInfosP[field]);
}

static ColumnInfo *ColumnToColumnInfo(w, column)
    VListWidget w;
    int column;
{
    return (&w->columnInfosP[column]);
}

static int ClosureToLine(w, closure)
    VListWidget w;
    Opaque closure;
{
    int line;
    LineInfo *lineInfoP;

    for (line=0, lineInfoP=w->lineInfosP; line<w->lineCnt; line++, lineInfoP++)
	if (lineInfoP->vLine.closure == closure) break;

    if (line == w->lineCnt) return (-1);
    else return (line);
}

static int LineToFirstLineInRow(w, line)
    VListWidget w;
    int line;
{
    return (line / w->fieldCnt * w->fieldCnt);
}

static int FieldRowToLine(w, field, row)
    VListWidget w;
    int field, row;
{
    if ((field < 0) || (field >= w->fieldCnt)
      || (row < 0) || (row >= w->rowCnt)) return (-1);
    else return (row * w->fieldCnt + field);
}

static void LineToFieldRow(w, line, fieldP, rowP)
    VListWidget w;
    int line;
    int *fieldP, *rowP;
{
    *fieldP = line - ((*rowP = line / w->fieldCnt) * w->fieldCnt);
}

static int CellIsVisible(w, x, y, width, height)
    VListWidget w;
    int x, y, width, height;
{
    /* Cast width and height to avoid unsigned comparison problems. */

    if ((x >= (int)w->core.width) || ((x + width) <= 0)
      || (y >= (int)w->core.height) || ((y + height) <= 0)) return (0);
    else return (1);
}

static void ColumnTierToCell(w, column, tier, xP, yP, widthP)
    VListWidget w;
    int column, tier;
    int *xP, *yP, *widthP;
{
    ColumnInfo *columnInfoP = ColumnToColumnInfo (w, column);

    *xP = columnInfoP->x - w->requestedXAdjust;
    *yP = w->topMarginHeight + tier * w->cellHeight - w->requestedYAdjust;
    *widthP = columnInfoP->width;
}

static void ColumnToGroupField(w, column, groupP, fieldP)
    VListWidget w;
    int column;
    int *groupP, *fieldP;
{
    int group = *groupP = column / w->fieldCnt;
    *fieldP = column - group * w->fieldCnt;
}

static int GroupFieldToColumn(w, group, field)
    VListWidget w;
    int group, field;
{
    return (group * w->fieldCnt + field);
}

static void GroupFieldToLines(w, group, field, firstLineP, lastLineP)
    VListWidget w;
    int group, field;
    int *firstLineP, *lastLineP;
{
    int firstLine = *firstLineP = group * w->tierCnt * w->fieldCnt + field;
    int lastLine = firstLine + (w->tierCnt - 1) * w->fieldCnt;
    if (lastLine >= w->lineCnt) lastLine = (w->lineCnt - w->fieldCnt + field);
    *lastLineP = lastLine;
}

static int ColumnTierToLine(w, column, tier)
    VListWidget w;
    int column, tier;
{
    int line;

    if ((column < 0) || (column >= w->columnCnt)
      || (tier < 0) || (tier >= w->tierCnt)) return (-1);

    line = ((column/w->fieldCnt) * (w->tierCnt-1) + tier) * w->fieldCnt
	+ column;

    if (line >= w->lineCnt) return (-1);

    return (line);
}

static void LineToColumnTier(w, line, columnP, tierP)
    VListWidget w;
    int line;
    int *columnP, *tierP;
{
    int row = line / w->fieldCnt;
    int group = row / w->tierCnt;

    *columnP = line - (row - group) * w->fieldCnt;
    *tierP = row - group * w->tierCnt;
}

static int VXToColumn(w, vX)
    VListWidget w;
    int vX;
{
    int column;
    ColumnInfo *columnInfoP;

    for (column = 0, columnInfoP = ColumnToColumnInfo (w, 0);
      (column < w->columnCnt) && (vX >= columnInfoP->x);
      column++, columnInfoP++) ;

    if (column == w->columnCnt) {
	columnInfoP--;
	if (vX >= (columnInfoP->x + columnInfoP->width)) return (column);
    }

    return (column - 1);
}

static int VYToTier(w, vY)
    VListWidget w;
    int vY;
{
    int tier;

    if (vY < w->topMarginHeight) return (-1);

    if ((tier = (vY - w->topMarginHeight) / w->cellHeight) > w->tierCnt)
	return (w->tierCnt);

    return (tier);
}

static int RectangleToLines(w, vX, vY, width, height, firstColumnP,
	lastColumnP, firstTierP, lastTierP)
    VListWidget w;
    int vX, vY, width, height;
    int *firstColumnP, *lastColumnP, *firstTierP, *lastTierP;
{
    int firstColumn, lastColumn, firstTier, lastTier;

    firstColumn = VXToColumn (w, vX);
    lastColumn = VXToColumn (w, vX + width - 1);

    if ((firstColumn == lastColumn) &&
      ((firstColumn == -1) || (firstColumn == w->columnCnt))) return (0);

    if (firstColumn == -1) firstColumn++;
    if (lastColumn == w->columnCnt) lastColumn--;

    firstTier = VYToTier (w, vY);
    lastTier = VYToTier (w, vY + height - 1);

    if ((firstTier == lastTier)
      && ((firstTier == -1) || (firstTier == w->tierCnt))) return (0);

    if (firstTier == -1) firstTier++;
    if (lastTier == w->tierCnt) lastTier--;

    *firstColumnP = firstColumn;
    *lastColumnP = lastColumn;
    *firstTierP = firstTier;
    *lastTierP = lastTier;

    return (1);
}

static int ColumnToFirstColumnInGroup(w, column)
    VListWidget w;
    int column;
{
    return (column / w->fieldCnt * w->fieldCnt);
}

static void XYToColumnTier(w, x, y, columnP, tierP)
    VListWidget w;
    int x, y, *columnP, *tierP;
{
    int column;

    if (x < 0) *columnP = -1;
    else if (x >= w->core.width) *columnP = w->columnCnt;
    else {
        column = VXToColumn (w, x + w->externalXAdjust);

	if ((w->selectUnit == VListSelectUnitRow)
	  && (column != -1) && (column != w->columnCnt))
	    column = ColumnToFirstColumnInGroup (w, column);

	*columnP = column;
    }

    if (y < 0) *tierP = -1;
    else if (y >= w->core.height) *tierP = w->tierCnt;
    else *tierP = VYToTier (w, y + w->externalYAdjust);
}

static void ColumnTierToFieldRow(w, column, tier, fieldP, rowP)
    VListWidget w;
    int column, tier;
    int *fieldP, *rowP;
{
    int group;

    if (column < 0) {
	*fieldP = -1;
	group = 0;
    } else if (column == w->columnCnt) {
	*fieldP = w->fieldCnt;
	group = w->groupCnt - 1;
    } else ColumnToGroupField (w, column, &group, fieldP);

    if (tier < 0) tier = 0;
    if (tier >= w->tierCnt) tier = w->tierCnt - 1;

    *rowP = group * w->tierCnt + tier;
}

static void CopyColors(w)
    VListWidget w;
{
    Window rootWindow;
    int i, x, y;
    unsigned int width, height, borderWidth, depth;
    XImage *imageP;

    /* If no color list was supplied, just use the foreground color. */

    if (!w->colorList) {
	w->colorCnt = 1;
	w->colorTableP = (Pixel *) XtMalloc (sizeof (Pixel));
	w->colorTableP[0] = w->foreground;
	return;
    }

    /* What is the width of the color pixmap? */

    XGetGeometry (XtDisplay (w), w->colorList, &rootWindow, &x, &y,
	&width, &height, &borderWidth, &depth);

    /* Allocate the color table. */

    w->colorCnt = width;
    w->colorTableP = (Pixel *) XtMalloc (w->colorCnt * sizeof (Pixel));

    /* Get an image of the color pixmap, copy the pixel values from that
     * image to the color table, and destroy the image. */

    imageP = XGetImage (XtDisplay (w), w->colorList, 0, 0, width, 1, -1,
	ZPixmap);

    for (i=0; i<width; i++) w->colorTableP[i] = XGetPixel (imageP, i, 0);

    XDestroyImage (imageP);
}

static void CopyFonts(w)
    VListWidget w;
{
    XmFontContext context;
    XmStringCharSet charset;
    XFontStruct *fontP;

    /* Determine how many fonts are in the font table.  The list is terminated
     * by a null entry (or so the story goes). */

    if(XmFontListInitFontContext(&context, w->fontListP)) {
      while(XmFontListGetNextFont(context, &charset, &fontP)) {
        if (w->fontCnt == 0) {
          /* Use the height of the first font in the font table to 
           * determine the character width and height for the widget. */
          w->charWidth = fontP->per_char['0' - fontP->min_char_or_byte2].width;
          w->charHeight = fontP->max_bounds.descent + fontP->max_bounds.ascent;
        }
        w->fontCnt++;
        XtFree(charset);
      }
      XmFontListFreeFontContext(context);
    } else
      XtAppErrorMsg(XtWidgetToApplicationContext((Widget) w), 
        "Internal Error", "wrongParameters", "VListWidget",
        "Cannot initialize font context from specified font list.",
        (String *) NULL, (Cardinal *) NULL);
    
}

static void ComputeCellHeight(w)
    VListWidget w;
{
    w->cellHeight = w->charHeight + w->rowSpacingHeight;

    if (w->vScrollW)
	XtVaSetValues (w->vScrollW, XmNincrement, w->cellHeight, NULL);
}

static void CopyLabels(w)
    VListWidget w;
{
    VListLabel *labelP;
    LabelInfo *labelInfoP;
    int label;

    if (!w->labelCnt) return;

    w->labelInfosP = (LabelInfo *) XtRealloc ((char *) w->labelInfosP,
	w->labelCnt * sizeof (LabelInfo));

    for (label=0, labelP=w->labelsP, labelInfoP=w->labelInfosP;
      label<w->labelCnt; label++, labelP++, labelInfoP++) {
	labelInfoP->vLabel = *labelP;

	if (!(labelInfoP->vLabel.mask & VListLabelTextMask))
	    labelInfoP->vLabel.textP = "";

	if (!(labelInfoP->vLabel.mask & VListLabelRowMask))
	    labelInfoP->vLabel.row = 0;

	if (!(labelInfoP->vLabel.mask & VListLabelFirstFieldMask))
	    labelInfoP->vLabel.firstField = label % w->fieldCnt;

	if (!(labelInfoP->vLabel.mask & VListLabelLastFieldMask))
	    labelInfoP->vLabel.lastField = labelInfoP->vLabel.firstField;

	if (!(labelInfoP->vLabel.mask & VListLabelAlignmentMask))
	    labelInfoP->vLabel.alignment = w->alignment;

	labelInfoP->vLabel.textP = XtNewString (labelInfoP->vLabel.textP);
    }

    w->labelsP = (VListLabel *) NULL; /* was -1; and don't look at it again */
}

static void CopyFields(w)
    VListWidget w;
{
    VListField *fieldP;
    FieldInfo *fieldInfoP;
    int field;

    w->fieldInfosP = (FieldInfo *) XtRealloc ((char *) w->fieldInfosP,
	w->fieldCnt * sizeof (FieldInfo));

    fieldP = w->fieldsP;

    for (field = 0, fieldInfoP = w->fieldInfosP; field < w->fieldCnt;
      field++, fieldInfoP++) {
	if (fieldP) fieldInfoP->vField = *(fieldP++);
	else fieldInfoP->vField.mask = 0;

	if (!(fieldInfoP->vField.mask & VListFieldAlignmentMask))
	    fieldInfoP->vField.alignment = w->alignment;
    }

    w->fieldsP = (VListField *) NULL; /* -1; and don't look at it again */
}

static void CopySegments(w, lineInfoP)
    VListWidget w;
    LineInfo *lineInfoP;
{
    int segCnt, segment;
    VListSegment *segmentP;
    SegmentInfo *segmentInfoP;

    if (!(segCnt = lineInfoP->vLine.segmentCount)) return;

    lineInfoP->segmentInfosP = 
      (SegmentInfo *) XtRealloc ((char *) lineInfoP->segmentInfosP,
	sizeof (SegmentInfo) * segCnt);

    for (segment = 0, segmentP = (VListSegment *) lineInfoP->vLine.segmentsP, segmentInfoP = lineInfoP->segmentInfosP; segment < segCnt;
      segment++, segmentP++, segmentInfoP++) {
	segmentInfoP->vSegment = *segmentP;
    }
}

static void ComputeLabelInfo(w)
    VListWidget w;
{
    LabelInfo *labelInfoP;
    int label, rows, fields;

    if ((!w->vHeaderW) || (!w->labelCnt)) {
	w->headerHeight = 0;
	return;
    }

    rows = 1;
    for (label = 0, labelInfoP = w->labelInfosP; label < w->labelCnt;
      label++, labelInfoP++) {
	labelInfoP->width = VHeaderComputeLabelWidth (w->vHeaderW,
	    labelInfoP->vLabel.textP);

	fields = labelInfoP->vLabel.lastField - labelInfoP->vLabel.firstField
	  + 1;

        labelInfoP->widthPerColumn =
	  (labelInfoP->width + 2 * w->textMarginWidth + fields - 1) / fields;

	if (labelInfoP->vLabel.row >= rows) rows = labelInfoP->vLabel.row + 1;
    }

    w->headerHeight = VHeaderComputeLogicalHeight (w->vHeaderW, rows);
}

static void FreeLabels(w)
    VListWidget w;
{
    LabelInfo *labelInfoP;
    int label;

    for (label = 0, labelInfoP = w->labelInfosP; label < w->labelCnt;
      label++, labelInfoP++) XtFree (labelInfoP->vLabel.textP);
}

static void SetHeaderLabels(w)
    VListWidget w;
{
    int label, group, firstColumn, lastColumn, vLabelCnt;
    ColumnInfo *firstColumnInfoP, *lastColumnInfoP;
    LabelInfo *labelInfoP;
    VHeaderLabel *vLabelsP, *vLabelP;

    if ((!w->vHeaderW) || (!w->labelCnt)) return;

    vLabelCnt = w->labelCnt * w->groupCnt;
    vLabelP = vLabelsP = 
      (VHeaderLabel *) XtMalloc (vLabelCnt * sizeof (VHeaderLabel));

    for (group = 0; group < w->groupCnt; group++)
	for (label = 0, labelInfoP = w->labelInfosP; label < w->labelCnt;
	  label++, labelInfoP++) {
	    vLabelP->textP = labelInfoP->vLabel.textP;
	    vLabelP->width = labelInfoP->width;
	    vLabelP->row = labelInfoP->vLabel.row;

	    firstColumn = GroupFieldToColumn (w, group,
		labelInfoP->vLabel.firstField);

	    firstColumnInfoP = ColumnToColumnInfo (w, firstColumn);

	    lastColumn = GroupFieldToColumn (w, group,
		labelInfoP->vLabel.lastField);

	    lastColumnInfoP = ColumnToColumnInfo (w, lastColumn);

	    if ((labelInfoP->vLabel.alignment == VListAlignmentEnd) ||
	      (labelInfoP->vLabel.alignment == VListAlignmentRight))
		vLabelP->x = lastColumnInfoP->x + lastColumnInfoP->width
		  - labelInfoP->width - w->textMarginWidth;
	    else if (labelInfoP->vLabel.alignment == VListAlignmentCenter)
		vLabelP->x = (lastColumnInfoP->x + lastColumnInfoP->width
		  + firstColumnInfoP->x - labelInfoP->width) / 2;
	    else vLabelP->x = firstColumnInfoP->x + w->textMarginWidth;
    
	    vLabelP++;
	}

    XtVaSetValues (w->vHeaderW, VHeaderNlabelCount, vLabelCnt, 
      VHeaderNlabels, vLabelsP, NULL);

    XtFree ((char *) vLabelsP);
}

static void SetInternalXYAdjust(w, xAdjust, yAdjust)
    VListWidget w;
    int xAdjust, yAdjust;
{
    /* Keep both adjustments within bounds. */

    {int maxXAdjust = w->logicalWidth - w->core.width;
    if ((maxXAdjust <= 0) || (xAdjust <= 0)) w->internalXAdjust = 0;
    else if (xAdjust > maxXAdjust) w->internalXAdjust = maxXAdjust;
    else w->internalXAdjust = xAdjust;}

    {int maxYAdjust = w->logicalHeight - w->core.height;
    if ((maxYAdjust <= 0) || (yAdjust <= 0)) w->internalYAdjust = 0;
    else if (yAdjust > maxYAdjust) w->internalYAdjust = maxYAdjust;
    else w->internalYAdjust = yAdjust;}
}

static void SetHeaderXAdjust(w)
    VListWidget w;
{
    if ((w->requestedXAdjust != w->shownHeaderXAdjust) && w->vHeaderW)
      XtVaSetValues (w->vHeaderW, 
        VHeaderNxAdjust, w->shownHeaderXAdjust = w->requestedXAdjust, NULL);
}

static void SetScrollBarValues(w)
    VListWidget w;
{
    w->ignoreScrollValueChanged = 1;

    if ((w->requestedXAdjust != w->shownScrollXAdjust) && w->hScrollW)
      XtVaSetValues (w->hScrollW, 
        XmNvalue, w->shownScrollXAdjust = w->requestedXAdjust, NULL);

    if ((w->requestedYAdjust != w->shownScrollYAdjust) && w->vScrollW)
      XtVaSetValues (w->vScrollW, 
        XmNvalue, w->shownScrollYAdjust = w->requestedYAdjust, NULL);

    w->ignoreScrollValueChanged = 0;
}

static void SetPosition(w)
    VListWidget w;
{
    w->externalXAdjust = w->requestedXAdjust = w->internalXAdjust;
    w->externalYAdjust = w->requestedYAdjust = w->internalYAdjust;
    SetHeaderXAdjust (w);
    SetScrollBarValues (w);
}

static void AdjustPosition(w)
    VListWidget w;
{
    int x, y, width, height;

    if (w->batchUpdate) return;		/* wait until done */
    if (w->scrollIsActive) return;	/* still busy */

    /* Check for autoscrolling */

    if (w->listIsGrabbed && (w->xScrollStrength || w->yScrollStrength))
	SetInternalXYAdjust (w,
	    w->internalXAdjust + w->xScrollStrength,
	    w->internalYAdjust + w->yScrollStrength);

    /* If the scroll position is already consistent, just return. */

    if ((w->internalXAdjust == w->requestedXAdjust)
      && (w->internalYAdjust == w->requestedYAdjust)) return;

    /* Compute the CopyArea parameters and ask the server to scroll the window
     * contents.  Keep track of the fact that the server is busy, and keep
     * track of the scroll position we requested the server to establish. */

    x = w->internalXAdjust - w->requestedXAdjust;
    y = w->internalYAdjust - w->requestedYAdjust;
    width = w->core.width;
    height = w->core.height;

    w->requestedXAdjust = w->internalXAdjust;
    w->requestedYAdjust = w->internalYAdjust;

    SetScrollBarValues (w);
    SetHeaderXAdjust (w);

    XCopyArea (XtDisplay (w), XtWindow (w), XtWindow (w), w->normgc, x, y,
	width, height, 0, 0);

    w->scrollIsActive = 1;
}

static void SetColor(w, coloridx)
    VListWidget w;
    int coloridx;
{
    Pixel color;

    if (coloridx == w->currentColoridx) return;	/* get off very cheap */

    coloridx = (coloridx % w->colorCnt);

    if (coloridx == w->currentColoridx) return;	/* get off pretty cheap */

    w->currentColoridx = coloridx;
    color = w->colorTableP[coloridx];

    XSetForeground (XtDisplay (w), w->normgc, color);
    XSetBackground (XtDisplay (w), w->invgc, color);
    XSetPlaneMask (XtDisplay (w), w->flipgc, w->core.background_pixel ^ color);
}

static void SetFont(w, fontidx)
    VListWidget w;
    int fontidx;
{
    XFontStruct *fontP;
    XmFontContext context;
    XmStringCharSet charset;
    int i;

    if (fontidx == w->currentFontidx) return;	/* get off very cheap */

    fontidx = (fontidx % w->fontCnt);

    if (fontidx == w->currentFontidx) return;	/* get off pretty cheap */

    w->currentFontidx = fontidx;

    (void) XmFontListInitFontContext(&context, w->fontListP);
    for (i=0; i<=fontidx; i++) {
      (void) XmFontListGetNextFont(context, &charset, &fontP);
      XtFree(charset);
    }
    XmFontListFreeFontContext(context);

    w->yFontAdjust = fontP->max_bounds.ascent;

    XSetFont (XtDisplay (w), w->normgc, fontP->fid);
    XSetFont (XtDisplay (w), w->invgc, fontP->fid);
}

static void HPageIncCallback(sbW, w, reason)
    Widget sbW;	/* scrollbar */
    VListWidget w;
    int reason;
{
    int maxXAdjust, xAdjust;

    xAdjust = w->internalXAdjust + w->core.width - w->charWidth;

    if (w->logicalWidth <= w->core.width) maxXAdjust = 0;
    else maxXAdjust = w->logicalWidth - w->core.width;

    if (xAdjust > maxXAdjust) xAdjust = maxXAdjust;

    XtVaSetValues (w->hScrollW, 
      XmNvalue, w->shownScrollXAdjust = xAdjust, NULL);

    /* Following two lines added for motif - MSG 11/22/91 */
    w->internalXAdjust = w->shownScrollXAdjust;
    if (!XtIsRealized ((Widget) w)) SetPosition (w); else AdjustPosition (w);
}

static void HPageDecCallback(sbW, w, reason)
    Widget sbW; /* scrollbar */
    VListWidget w;
    int reason;
{
    int xAdjust;

    xAdjust = w->internalXAdjust - w->core.width + w->charWidth;
    if (xAdjust < 0) xAdjust = 0;

    XtVaSetValues (w->hScrollW, 
      XmNvalue, w->shownScrollXAdjust = xAdjust, NULL);

    /* Following two lines added for motif - MSG 11/22/91 */
    w->internalXAdjust = w->shownScrollXAdjust;
    if (!XtIsRealized ((Widget) w)) SetPosition (w); else AdjustPosition (w);
}

static void HValueChangedCallback(sbW, w, reasonP)
    Widget sbW; /* scrollbar */
    VListWidget w;
    XmScrollBarCallbackStruct *reasonP;
{
    if (w->ignoreScrollValueChanged) return;

    w->shownScrollXAdjust = w->internalXAdjust = reasonP->value;

    if (!XtIsRealized ((Widget) w)) SetPosition (w); else AdjustPosition (w);
}

static void VPageIncCallback(sbW, w, reason)
    Widget sbW;	/* scrollbar */
    VListWidget w;
    int reason;
{
    int yAdjust, maxYAdjust;

    yAdjust = w->internalYAdjust + w->core.height - w->cellHeight;

    if (w->logicalHeight <= w->core.height) maxYAdjust = 0;
    else maxYAdjust = w->logicalHeight - w->core.height;

    if (yAdjust > maxYAdjust) yAdjust = maxYAdjust;

    XtVaSetValues (w->vScrollW, 
      XmNvalue, w->shownScrollYAdjust = yAdjust, NULL);

    /* following two lines added for motif - MSG 11/22/91 */
    w->internalYAdjust = w->shownScrollYAdjust;
    if (!XtIsRealized ((Widget) w)) SetPosition (w); else AdjustPosition (w);
}

static void VPageDecCallback(sbW, w, reason)
    Widget sbW; /* scrollbar */
    VListWidget w;
    int reason;
{
    int yAdjust;

    yAdjust = w->internalYAdjust - w->core.height + w->cellHeight;
    if (yAdjust < 0) yAdjust = 0;

    XtVaSetValues (w->vScrollW, 
      XmNvalue, w->shownScrollYAdjust = yAdjust, NULL);

    /* following two lines added for motif - MSG 11/22/91 */
    w->internalYAdjust = w->shownScrollYAdjust;
    if (!XtIsRealized ((Widget) w)) SetPosition (w); else AdjustPosition (w);
}

static void VValueChangedCallback(sbW, w, reasonP)
    Widget sbW; /* scrollbar */
    VListWidget w;
    XmScrollBarCallbackStruct *reasonP;
{
    if (w->ignoreScrollValueChanged) return;

    w->shownScrollYAdjust = w->internalYAdjust = reasonP->value;

    if (!XtIsRealized ((Widget) w)) SetPosition (w); else AdjustPosition (w);
}

static void Draw(w, line, clear, checkVisibility)
    VListWidget w;
    int line, clear, checkVisibility;
{
    LineInfo *lineInfoP, *firstLineInfoP;
    ColumnInfo *columnInfoP;
    int column, tier, x0, x, y, width, height, flip, segment, textX0;
    SegmentInfo *segmentInfoP;

    if (!XtIsRealized ((Widget) w)) return;

    LineToColumnTier (w, line, &column, &tier);
    ColumnTierToCell (w, column, tier, &x, &y, &width);
    height = w->charHeight;

    if (checkVisibility && (!CellIsVisible (w, x, y, width, height))) return;

    lineInfoP = LineToLineInfo (w, line);

    if (w->selectUnit == VListSelectUnitField) flip = lineInfoP->vLine.select;
    else {
	firstLineInfoP = LineToLineInfo (w, LineToFirstLineInRow (w, line));
	flip = firstLineInfoP->vLine.select;
    }

    x0 = x;		/* save left edge of field */

    columnInfoP = ColumnToColumnInfo (w, column);

    if ((columnInfoP->alignment == VListAlignmentBeginning) ||
      (columnInfoP->alignment == VListAlignmentLeft))
	x += w->textMarginWidth;
    else if (columnInfoP->alignment == VListAlignmentCenter)
        x += ((columnInfoP->width - lineInfoP->textWidth) / 2);
    else x += (columnInfoP->width - w->textMarginWidth - lineInfoP->textWidth);

    textX0 = x;		/* save starting point for text */

    if (clear) XClearArea (XtDisplay (w), XtWindow (w), x0, y, width, height,
        0);

    if (!lineInfoP->vLine.segmentCount) {
	SetColor (w, lineInfoP->vLine.coloridx);
	SetFont (w, lineInfoP->vLine.fontidx);
    
	if (flip) XFillRectangle (XtDisplay (w), XtWindow (w), w->normgc, x0, y,
	    width, height);
    
	if (lineInfoP->textStrlen) {
	    XDrawString (XtDisplay (w), XtWindow (w),
		(flip ? w->invgc : w->normgc), x, y + w->yFontAdjust,
		lineInfoP->vLine.textP, lineInfoP->textStrlen);
        }
    } else {
	if (flip) {
	    /* Flip the left margin. */

	    SetColor (w, lineInfoP->vLine.coloridx);

	    XFillRectangle (XtDisplay (w), XtWindow (w), w->normgc, x0, y,
		x - x0, height);

	    /* Flip all internal segment areas.  Do this before drawing any
	     * text to avoid problems when text is kerned. */
    
	    for (segment = 0, segmentInfoP = lineInfoP->segmentInfosP;
	      segment < lineInfoP->vLine.segmentCount; segment++, segmentInfoP++) {
		SetColor (w, segmentInfoP->vSegment.coloridx);
    
		XFillRectangle (XtDisplay (w), XtWindow (w), w->normgc,
		    x, y, segmentInfoP->textWidth, height);
    
		x += segmentInfoP->textWidth;	
	    }

	    /* Flip the right margin. */

	    SetColor (w, lineInfoP->vLine.coloridx);

	    XFillRectangle (XtDisplay (w), XtWindow (w), w->normgc, x, y,
		width - (x - x0), height);
	}

	/* Draw all text segments. */

	x = textX0;

	for (segment = 0, segmentInfoP = lineInfoP->segmentInfosP;
	  segment < lineInfoP->vLine.segmentCount; segment++, segmentInfoP++) {
	    SetColor (w, segmentInfoP->vSegment.coloridx);
	    SetFont (w, segmentInfoP->vSegment.fontidx);

	    if (segmentInfoP->vSegment.textStrlen) XDrawString (XtDisplay (w),
		XtWindow (w), (flip ? w->invgc : w->normgc), x,
		y + w->yFontAdjust,
		lineInfoP->vLine.textP + segmentInfoP->vSegment.textPosition,
		segmentInfoP->vSegment.textStrlen);

	    x += segmentInfoP->textWidth;	
	}
    }
}

static void Flip(w, line)
    VListWidget w;
    int line;
{
    int column, tier, x0, x, y, width, height, segment;
    LineInfo *lineInfoP;
    SegmentInfo *segmentInfoP;
    ColumnInfo *columnInfoP;

    if (!XtIsRealized ((Widget) w)) return;	/* not realized yet */

    LineToColumnTier (w, line, &column, &tier);
    ColumnTierToCell (w, column, tier, &x, &y, &width);
    height = w->charHeight;

    if (!CellIsVisible (w, x, y, width, height)) return;

    if (w->scrollIsActive) {		/* if we're busy scrolling... */
	Draw (w, line, 1, 1);		/* previous contents are undefined */
	return;
    }

    lineInfoP = LineToLineInfo (w, line);

    if (!lineInfoP->vLine.segmentCount) {
	SetColor (w, lineInfoP->vLine.coloridx);

        XFillRectangle (XtDisplay (w), XtWindow (w), w->flipgc, x, y, width,
	    height);
    } else {
	x0 = x;		/* save left edge of field */

	columnInfoP = ColumnToColumnInfo (w, column);
    
	if ((columnInfoP->alignment == VListAlignmentBeginning) ||
	  (columnInfoP->alignment == VListAlignmentLeft))
	    x += w->textMarginWidth;
	else if (columnInfoP->alignment == VListAlignmentCenter)
	    x += ((columnInfoP->width - lineInfoP->textWidth) / 2);
	else x += (columnInfoP->width - w->textMarginWidth
    	    - lineInfoP->textWidth);

	/* Flip the left margin. */

	SetColor (w, lineInfoP->vLine.coloridx);

        XFillRectangle (XtDisplay (w), XtWindow (w), w->flipgc, x0, y,
	    x - x0, height);

	/* Flip each segment using the appropriate color. */

	for (segment = 0, segmentInfoP = lineInfoP->segmentInfosP;
	  segment < lineInfoP->vLine.segmentCount; segment++, segmentInfoP++) {
	    SetColor (w, segmentInfoP->vSegment.coloridx);
	    
	    XFillRectangle (XtDisplay (w), XtWindow (w), w->flipgc, x, y,
	        segmentInfoP->textWidth, height);

	    x += segmentInfoP->textWidth;
	}

	/* Flip the right margin. */

	SetColor (w, lineInfoP->vLine.coloridx);

	XFillRectangle (XtDisplay (w), XtWindow (w), w->flipgc, x, y,
	    width - (x - x0), height);
    }
}

static int AddWidthContribution(w, column, width)
    VListWidget w;
    int column, width;
{
    ColumnInfo *columnInfoP = ColumnToColumnInfo (w, column);

    if (width > columnInfoP->width) {
	columnInfoP->width = width;
	columnInfoP->widthCnt = 1;
	return (1);
    }

    if (width == columnInfoP->width) columnInfoP->widthCnt++;

    return (0);
}

static int RemoveWidthContribution(w, column, width)
    VListWidget w;
    int column, width;
{
    ColumnInfo *columnInfoP = ColumnToColumnInfo (w, column);

    if (width == columnInfoP->width) if (!(--columnInfoP->widthCnt)) return (1);
    return (0);
}

static void ComputeColumnWidth(w, column)
    VListWidget w;
    int column;
{
    int group, field, label, line, lastLine;
    ColumnInfo *columnInfoP = ColumnToColumnInfo (w, column);
    LineInfo *lineInfoP;
    LabelInfo *labelInfoP;

    ColumnToGroupField (w, column, &group, &field);
    GroupFieldToLines (w, group, field, &line, &lastLine);

    columnInfoP->width = columnInfoP->widthCnt = 0;

    for (lineInfoP = LineToLineInfo (w, line); line <= lastLine;
      line += w->fieldCnt, lineInfoP += w->fieldCnt)
	AddWidthContribution (w, column,
	    lineInfoP->textWidth + 2 * w->textMarginWidth);

    for (label = 0, labelInfoP = w->labelInfosP; label < w->labelCnt;
      label++, labelInfoP++)
	if ((labelInfoP->vLabel.firstField <= field)
   	  && (labelInfoP->vLabel.lastField >= field))
	    AddWidthContribution (w, column, labelInfoP->widthPerColumn);
}

static int ChangeWidthContribution(w, column, oldWidth, newWidth)
    VListWidget w;
    int column, oldWidth, newWidth;
{
    ColumnInfo *columnInfoP = ColumnToColumnInfo (w, column);
    int changed = 0;

    if (newWidth > columnInfoP->width) {
	columnInfoP->width = newWidth;
	columnInfoP->widthCnt = 1;
	changed = 1;
    } else if (newWidth == columnInfoP->width) {
	columnInfoP->widthCnt++;
    } else if (oldWidth == columnInfoP->width)
	if (!(--columnInfoP->widthCnt)) changed = 1;

    return (changed);
}

#define TryLayoutCheckNone		0
#define TryLayoutCheckAllVisible	1
#define TryLayoutCheckTwoVisible	2

static int TryLayout(w, check, width, height)
    VListWidget w;
    int check, width, height;
{
    int column, x, group, field, minHeight;
    ColumnInfo *columnInfoP, *previousColumnInfoP;
    FieldInfo *fieldInfoP;

    if (height < (minHeight = (2 * w->marginHeight + w->cellHeight)))
	w->logicalHeight = minHeight;
    else w->logicalHeight = height;

    w->tierCnt = (w->logicalHeight - 2 * w->marginHeight) / w->cellHeight;

    if (!w->rowCnt) w->groupCnt = 1;
    else w->groupCnt = (w->rowCnt - 1) / w->tierCnt + 1;

    w->columnCnt = w->groupCnt * w->fieldCnt;
    w->columnInfosP = (ColumnInfo *) XtRealloc ((char *) w->columnInfosP,
	w->columnCnt * sizeof (ColumnInfo));

    if (w->groupCnt == 1) w->topMarginHeight = w->marginHeight;
    else w->topMarginHeight = (w->logicalHeight - w->tierCnt * w->cellHeight
	+ w->rowSpacingHeight + 1) / 2;

    x = w->marginWidth;

    for (column = 0, columnInfoP = ColumnToColumnInfo (w, 0);
      column < w->columnCnt; column++, columnInfoP++) {
	columnInfoP->x = x;
	ComputeColumnWidth (w, column);
	x += columnInfoP->width;
	
	ColumnToGroupField (w, column, &group, &field);

	fieldInfoP = FieldToFieldInfo (w, field);
	columnInfoP->alignment = fieldInfoP->vField.alignment;

	if (field != (w->fieldCnt - 1)) x += w->fieldSpacingWidth;
	else if (group != (w->groupCnt - 1)) x += (2 * w->marginWidth);

	if (check == TryLayoutCheckAllVisible) {
	    if ((x + w->marginWidth) > width) return (0);
	} else if (check == TryLayoutCheckTwoVisible) {
	    if ((field == (w->fieldCnt - 1)) && group) {
	        previousColumnInfoP = ColumnToColumnInfo (w,
		  (column - w->fieldCnt * 2 + 1));

		if ((x - previousColumnInfoP->x + 2 * w->marginWidth) > width)
		    return (0);
	    }
	}
    }

    w->logicalWidth = x + w->marginWidth;
    return (1);
}

static void DrawExposedLines(w)
    VListWidget w;
{
    int column, tier, line, firstColumn, lastColumn, firstTier, lastTier;
    LineInfo *lineInfoP;

    if (!w->anyAreExposed) return;	/* nothing to do */

    w->anyAreExposed = 0;

    /* Loop through visible lines, redrawing requested ones. */

    if (!RectangleToLines (w, w->requestedXAdjust, w->requestedYAdjust,
      w->core.width, w->core.height, &firstColumn, &lastColumn, &firstTier,
      &lastTier)) return;

    for (column=firstColumn; column <= lastColumn; column++)
        for (tier=firstTier; tier <= lastTier; tier++)
	    if ((line = ColumnTierToLine (w, column, tier)) != -1) {
		lineInfoP = LineToLineInfo (w, line);
    
		if (lineInfoP->expose) {
		    Draw (w, line, 0, 0);
		    lineInfoP->expose = 0;
		}
    	    }
}

static void SaveExposeRegion(w, vX, vY, width, height)
    VListWidget w;
    int vX, vY, width, height;
{
    int firstColumn, lastColumn, firstTier, lastTier, column, tier, line;
    LineInfo *lineInfoP;

    if (!RectangleToLines (w, vX, vY, width, height, &firstColumn,
      &lastColumn, &firstTier, &lastTier)) return;

    for (column = firstColumn; column <= lastColumn; column++)
        for (tier = firstTier; tier <= lastTier; tier++)
    	    if ((line = ColumnTierToLine (w, column, tier)) != -1) {
	        lineInfoP = LineToLineInfo (w, line);
	        lineInfoP->expose = 1;
	    }

    w->anyAreExposed = 1;
}

static void DoColumnLayout(w)
    VListWidget w;
{
    int width, height;

    width = w->core.parent->core.width;
    if (w->vScrollPolicy == VListScrollBarPolicyAlways)
        width -= (w->vScrollW->core.width + w->vScrollW->core.border_width);

    if ((w->columnStyle == VListColumnStyleMultiple) ||
      (w->columnStyle == VListColumnStyleBestFit)) {
	height = w->core.parent->core.height;
	if (w->headerHeight)
	    height -= (w->headerHeight + w->core.border_width);

	if (w->hScrollPolicy == VListScrollBarPolicyNever) {
	    TryLayout (w, TryLayoutCheckNone, width, height);
	    return;
	}

	if (w->hScrollPolicy == VListScrollBarPolicyAsNeeded)
	    if (TryLayout (w, TryLayoutCheckAllVisible, width, height)) return;

	height -= (w->hScrollW->core.height + w->hScrollW->core.border_width);

	if (w->columnStyle == VListColumnStyleMultiple) {
            TryLayout (w, TryLayoutCheckNone, width, height);
	    return;
        }

	if (TryLayout (w, TryLayoutCheckTwoVisible, width, height)) return;
    }

    height = w->rowCnt * w->cellHeight + 2 * w->marginHeight;
    TryLayout (w, TryLayoutCheckNone, width, height);
}

static void ApplyLayoutPolicy(w, xP, yP, widthP, heightP, hScrollP, vScrollP)
    VListWidget w;
    int *xP, *yP, *widthP, *heightP, *hScrollP, *vScrollP;
{
    int x, y, width, height, hScroll, vScroll, temp;

    hScroll = vScroll = x = y = 0;
    width = w->core.parent->core.width;
    height = w->core.parent->core.height;

    if (w->headerHeight) {
	temp = w->headerHeight + w->core.border_width;
	y += temp;
	if ((height -= temp) <= 0) height = 1;
    }

    if ((w->hScrollPolicy == VListScrollBarPolicyAlways)
      || ((w->hScrollPolicy == VListScrollBarPolicyAsNeeded)
      && (w->logicalWidth > width))) {
	temp = w->hScrollW->core.height + w->hScrollW->core.border_width;
	if ((height -= temp) <= 0) height = 1;
	hScroll = 1;
    }

    if ((w->vScrollPolicy == VListScrollBarPolicyAlways)
      || ((w->vScrollPolicy == VListScrollBarPolicyAsNeeded)
      && (w->logicalHeight > height))) {
	temp = w->vScrollW->core.width + w->vScrollW->core.border_width;
	if (w->vScrollPosition == VListScrollBarPositionLeft) x += temp;
	if ((width -= temp) <= 0) width = 1;
	vScroll = 1;

	if ((!hScroll) && (w->hScrollPolicy == VListScrollBarPolicyAsNeeded)
	  && (w->logicalWidth > width)) {
	    temp = w->hScrollW->core.height + w->hScrollW->core.border_width;
	    if ((height -= temp) <= 0) height = 1;
	    hScroll = 1;
	}
    }

    *hScrollP = hScroll;
    *vScrollP = vScroll;
    *xP = x;
    *yP = y;
    *widthP = width;
    *heightP = height;
}

static void ArrangeWidgets(w)
    VListWidget w;
{
    int x, y, width, height, needHScroll, needVScroll;
    int newX, newY;
    Widget vHeaderW = w->vHeaderW;
    Widget hScrollW = w->hScrollW;
    Widget vScrollW = w->vScrollW;

    ApplyLayoutPolicy (w, &x, &y, &width, &height, &needHScroll, &needVScroll);

    if ((!w->headerHeight) && vHeaderW && XtIsManaged (vHeaderW))
	XtUnmanageChild (vHeaderW);

    if ((!needHScroll) && hScrollW && XtIsManaged (hScrollW))
	XtUnmanageChild (hScrollW);

    if ((!needVScroll) && vScrollW && XtIsManaged (vScrollW))
	XtUnmanageChild (vScrollW);

    newX = x - w->core.border_width;
    newY = y - w->core.border_width;

    if ((w->core.x != newX) || (w->core.y != newY)
      || (w->core.width != width) || (w->core.height != height))
	XtVaSetValues ((Widget) w, 
	  XtNx, newX, XtNy, newY, XtNwidth, width, XtNheight, height, NULL);

    if (w->headerHeight) {
	if (!XtIsManaged (vHeaderW)) XtManageChild (vHeaderW);

	newX = x - vHeaderW->core.border_width;
	newY = (-vHeaderW->core.border_width);

        if ((vHeaderW->core.x != newX) || (vHeaderW->core.y != newY)
    	  || (vHeaderW->core.width != width)
	  || (vHeaderW->core.height != w->headerHeight))
	    XtVaSetValues (vHeaderW, XtNx, newX, XtNy, newY, XtNwidth, width, 
              XtNheight, w->headerHeight, NULL);
    }

    if (needHScroll) {
	int logicalWidth = w->logicalWidth;
	if (logicalWidth < width) logicalWidth = width;

	/* Do separate XtSetValues to get around a scroll bar widget bug. */

	newX = x - hScrollW->core.border_width;
	newY = y + height;

	w->ignoreScrollValueChanged = 1;

	if ((hScrollW->core.x != newX) || (hScrollW->core.y != newY))
          XtVaSetValues (hScrollW, XtNx, newX, XtNy, newY, NULL);

    	XtVaSetValues (hScrollW, XtNwidth, width, XmNsliderSize, width,
	  XmNmaximum, logicalWidth, 
          XmNvalue, w->shownScrollXAdjust = w->requestedXAdjust, NULL);

	w->ignoreScrollValueChanged = 0;

	if (!XtIsManaged (hScrollW)) XtManageChild (hScrollW);
    }

    if (needVScroll) {
        int logicalHeight = w->logicalHeight;
	if (logicalHeight < height) logicalHeight = height;

	if (w->vScrollPosition == VListScrollBarPositionRight) x = width;
	else x = (-vScrollW->core.border_width);

	/* Do separate XtSetValues to get around a scroll bar widget bug. */

	newY = y - vScrollW->core.border_width;

	w->ignoreScrollValueChanged = 1;

        if ((vScrollW->core.x != x) || (vScrollW->core.y != newY))
          XtVaSetValues (vScrollW, XtNx, x, XtNy, newY, NULL);

	XtVaSetValues (vScrollW, XtNheight, height, XmNsliderSize, height,
          XmNmaximum, logicalHeight,
          XmNvalue, w->shownScrollYAdjust = w->requestedYAdjust, NULL);

	w->ignoreScrollValueChanged = 0;

	if (!XtIsManaged (vScrollW)) XtManageChild (vScrollW);
    }
} 

void VListMakeLineVisible(w, closure, visible)
    VListWidget w;
    Opaque closure;
    int visible;
{
    int line, firstVY, lastVYP1, yAdjust, firstVX, lastVXP1, xAdjust;
    int column, tier, x, y, width, height;

    if (!XtIsRealized ((Widget) w) || w->batchUpdate) {
	w->visibleClosure = (long) closure;
	w->visiblePosition = visible;
	return;
    }

    if ((line = ClosureToLine (w, closure)) == -1) return;

    LineToColumnTier (w, line, &column, &tier);
    ColumnTierToCell (w, column, tier, &x, &y, &width);
    height = w->charHeight;

    firstVX = x + w->requestedXAdjust - w->marginWidth;
    lastVXP1 = x + w->requestedXAdjust + width + w->marginWidth;

    firstVY = y + w->requestedYAdjust - w->marginHeight;
    lastVYP1 = y + w->requestedYAdjust + height + w->marginHeight;

    if ((visible == VListVisibleAtRight)
      || (visible == VListVisibleAtTopRight)
      || (visible == VListVisibleAtBottomRight)
      || ((visible == VListVisibleInWindow)
      && (lastVXP1 > (w->internalXAdjust + w->core.width))))
	xAdjust = lastVXP1 - w->core.width;
    else if ((visible == VListVisibleAtLeft)
      || (visible == VListVisibleAtTopLeft)
      || (visible == VListVisibleAtBottomLeft)
      || ((visible == VListVisibleInWindow)
      && (firstVX < w->internalXAdjust))) xAdjust = firstVX;
    else xAdjust = w->internalXAdjust;

    if ((visible == VListVisibleAtBottom)
      || (visible == VListVisibleAtBottomLeft)
      || (visible == VListVisibleAtBottomRight)
      || ((visible == VListVisibleInWindow)
      && (lastVYP1 > (w->internalYAdjust + w->core.height))))
	yAdjust = lastVYP1 - w->core.height;
    else if ((visible == VListVisibleAtTop)
      || (visible == VListVisibleAtTopLeft)
      || (visible == VListVisibleAtTopRight)
      || ((visible == VListVisibleInWindow)
      && (firstVY < w->internalYAdjust))) yAdjust = firstVY;
    else yAdjust = w->internalYAdjust;

    SetInternalXYAdjust (w, xAdjust, yAdjust);
    AdjustPosition (w);
}

void VListStartBatchUpdate(w)
    VListWidget w;
{
    w->batchUpdate++;
    w->scrollIsActive = 0;	/* cancel outstanding scroll, if any */
}

static void ComputeLayout(w)
    VListWidget w;
{
    DoColumnLayout (w);
    ArrangeWidgets (w);
    SetHeaderLabels (w);
    SetInternalXYAdjust (w, w->internalXAdjust, w->internalYAdjust);
    SetPosition (w);
    w->layoutIsValid = 1;
}

static void Redraw(w)
    VListWidget w;
{
    SetPosition (w);

    if (!XtIsRealized ((Widget) w)) return;

    XClearArea (XtDisplay (w), XtWindow (w), 0, 0, w->core.width,
	w->core.height, 0);

    SaveExposeRegion (w, w->internalXAdjust, w->internalYAdjust, w->core.width,
	w->core.height);

    DrawExposedLines (w);
}

void VListEndBatchUpdate(w)
    VListWidget w;
{
    if (--w->batchUpdate) return;	/* still batching? */
    if (!XtIsRealized ((Widget) w)) return;	/* not real yet */

    if (!w->layoutIsValid) ComputeLayout (w);

    if (w->visibleClosure) {
	VListMakeLineVisible (w, (Opaque) ((long)w->visibleClosure), 
          w->visiblePosition);
	w->visibleClosure = 0;
    }

    Redraw (w);
}

static void StartUpdateSweep(w)
    VListWidget w;
{
    XEvent event;			/* allocate full event buffer */

    VListStartBatchUpdate (w);

    event.xclient.type = ClientMessage;
    event.xclient.display = XtDisplay (w);
    event.xclient.window = XtWindow (w);
    event.xclient.message_type = 0;
    event.xclient.format = 32;

    XSendEvent (XtDisplay (w), XtWindow (w), 0, 0, &event);
}

static void ResizeCallback(Widget pW, XtPointer client_data, XtPointer cbDataP)
{
    VListWidget w = (VListWidget) client_data;

    if (!XtIsRealized ((Widget) w)) return;

    ComputeLayout (w);
    StartUpdateSweep (w);
}

static int FindLastDeletedLine(w)
    VListWidget w;
{
    int line;
    LineInfo *lineInfoP;

    for (line = w->lineCnt, lineInfoP = LineToLineInfo (w, line);
      ((line -= w->fieldCnt) >= 0) && (!(lineInfoP -= w->fieldCnt)->delete); ) ;

    if (line < 0) {
	w->anyAreDeleted = 0;
	return (-1);
    }

    return (line);
}

static void HandlePendingDeletes(w)
    VListWidget w;
{
    int line, firstVY, lastVYP1, row, x, fromY, toY, width, height;
    int field, layoutIsValid, firstLine;
    LineInfo *lineInfoP, *otherLineInfoP;

    if (!w->anyAreDeleted) return;	/* nothing to do */
    if (w->listIsGrabbed) return;	/* not while user is selecting */
    if (w->scrollIsActive) return;	/* and not while scrolling */

    if ((firstLine = FindLastDeletedLine (w)) == (-1)) return;

    if ((w->groupCnt == 1) && XtIsRealized ((Widget) w) && (!w->batchUpdate))
	layoutIsValid = 1;
    else layoutIsValid = 0;

    for (field = 0, line = firstLine, lineInfoP = LineToLineInfo (w, line);
      field < w->fieldCnt; field++, line++, lineInfoP++) {
	XtFree (lineInfoP->vLine.textP);
	XtFree ((char *) lineInfoP->segmentInfosP);

	if (layoutIsValid)
	    if (RemoveWidthContribution (w, field,
	      lineInfoP->textWidth + 2 * w->textMarginWidth)) layoutIsValid = 0;
    }	

    /* Collapse the row from the array. */

    w->lineCnt -= w->fieldCnt;
    w->rowCnt--;

    for (line = firstLine, lineInfoP = LineToLineInfo (w, line),
      otherLineInfoP = LineToLineInfo (w, line + w->fieldCnt);
      line < w->lineCnt; line++, lineInfoP++, otherLineInfoP++)
	*lineInfoP = *otherLineInfoP;

    if (!layoutIsValid) w->layoutIsValid = 0;

    if ((!XtIsRealized ((Widget) w)) || w->batchUpdate) {
	HandlePendingDeletes (w);
	return;
    }

    if (!w->layoutIsValid) {
	StartUpdateSweep (w);
        HandlePendingDeletes (w);
	return;
    }

    row = firstLine / w->fieldCnt;
    firstVY = w->marginHeight + row * w->cellHeight;
    lastVYP1 = firstVY + w->cellHeight;

    w->tierCnt = w->rowCnt;
    w->logicalHeight = w->tierCnt * w->cellHeight + 2 * w->marginHeight
	- w->rowSpacingHeight;

    ArrangeWidgets (w);

    /* Removed row is above top of window? */

    if (w->internalYAdjust >= lastVYP1) {
	w->internalYAdjust -= w->cellHeight;
	SetPosition (w);
	HandlePendingDeletes (w);
	return;
    }

    /* Removed row is below bottom of window? */

    if ((w->internalYAdjust + w->core.height) <= firstVY) {
	HandlePendingDeletes (w);
	return;
    }

    /* Removed row is visible.  Scroll window contents. */

    x = 0;
    fromY = lastVYP1 - w->requestedYAdjust;
    toY = firstVY - w->requestedYAdjust;
    width = w->core.width;
    height = (w->rowCnt - row + 1) * w->cellHeight + w->marginHeight;

    XCopyArea (XtDisplay (w), XtWindow (w), XtWindow (w), w->normgc,
	x, fromY, width, height, x, toY);

    w->scrollIsActive = 1;

    /* Possibly adjust to avoid trailing deadspace. */

    SetInternalXYAdjust (w, w->internalXAdjust, w->internalYAdjust);
}

static void DoExpose(Widget gW, XEvent *gEventP, Region region)
{
    VListWidget w        = (VListWidget) gW;
    XExposeEvent *eventP = (XExposeEvent *) gEventP;

    if (w->batchUpdate) return;

    XClearArea (XtDisplay (w), XtWindow (w),
	eventP->x + w->externalXAdjust - w->requestedXAdjust,
	eventP->y + w->externalYAdjust - w->requestedYAdjust,
	eventP->width, eventP->height, 0);

    SaveExposeRegion (w, eventP->x + w->externalXAdjust,
	eventP->y + w->externalYAdjust, eventP->width, eventP->height);

    /* If this is not a primary Expose event, simply return. */

    if (eventP->count) return;		/* more expose events are coming */
    if (w->scrollIsActive) return;	/* we are busy scrolling */

    DrawExposedLines (w);
}

static void HandleNonmaskableEvent(Widget gW, XtPointer closure, 
  XEvent *eventP, Boolean *continue_to_dispatch)
{
    VListWidget w = (VListWidget) gW;

    int type = eventP->xany.type;

    if (type == ClientMessage) {	/* update sweep complete */
	VListEndBatchUpdate (w);
	return;
    }

    if (w->batchUpdate) return;

    if (type == GraphicsExpose)
	SaveExposeRegion (w,
	    eventP->xgraphicsexpose.x + w->requestedXAdjust,
	    eventP->xgraphicsexpose.y + w->requestedYAdjust,
	    eventP->xgraphicsexpose.width,
	    eventP->xgraphicsexpose.height);

    /* Handle completion of the scroll operation. */

    if ((type == NoExpose) ||
      ((type == GraphicsExpose) && (!eventP->xgraphicsexpose.count))) {
	w->scrollIsActive = 0;
	w->externalXAdjust = w->requestedXAdjust;
	w->externalYAdjust = w->requestedYAdjust;

	DrawExposedLines (w);
	AdjustPosition (w);
	HandlePendingDeletes (w);
    }
}

static void SelectLine(w, line, select)
    VListWidget w;
    int line, select;
{
    LineInfo *lineInfoP;
    int otherLine;

    lineInfoP = LineToLineInfo (w, line);

    if (lineInfoP->vLine.select == select) return;
    if (!lineInfoP->vLine.sensitive) return;

    if ((lineInfoP->vLine.select = select)) w->selectionCnt++;
    else w->selectionCnt--;
    
    if (w->selectUnit == VListSelectUnitField) Flip (w, line);
    else for (otherLine=line; otherLine<(line + w->fieldCnt); otherLine++)
	Flip (w, otherLine);
}

static void DeselectAllLines(w)
    VListWidget w;
{
    int line, increment;

    if (!w->selectionCnt) return;		/* quick check */

    if (w->selectUnit == VListSelectUnitField) increment = 1;
    else increment = w->fieldCnt;

    for (line=0; w->selectionCnt; line += increment) SelectLine (w, line, 0);
}

static void SelectAllLines(w)
    VListWidget w;
{
    int line, increment;

    if (w->selectUnit == VListSelectUnitField) increment = 1;
    else increment = w->fieldCnt;

    for (line=0; line<w->lineCnt; line += increment) SelectLine (w, line, 1);
}

static void CallSelectCallbacks(w, eventP, confirm)
    VListWidget w;
    XButtonEvent *eventP;
    int confirm;
{
    VListSelectCallbackStruct cbData;
    int line;
    LineInfo *lineInfoP;
	
    cbData.reason = (confirm ? VListCRSelectConfirm : VListCRSelect);
    cbData.event = (XEvent *) eventP;

    ColumnTierToFieldRow (w, w->upColumn, w->upTier, &cbData.field,
	&cbData.row);

    if ((line = ColumnTierToLine (w, w->upColumn, w->upTier)) != -1) {
	lineInfoP = LineToLineInfo (w, line);
	cbData.vLine = lineInfoP->vLine;
    } else cbData.vLine.closure = 0;
	
    XtCallCallbacks ((Widget) w,
        (confirm ? VListNselectConfirmCallback : VListNselectCallback),
	(XtPointer) &cbData);
}

static void NewSelectColumnTier(w, newColumn, newTier)
    VListWidget w;
    int newColumn, newTier;
{
    int newLine, mouseLine, field, row, line, fieldIncrement;
    int downField, downRow, mouseField, mouseRow, newField, newRow;
    int oldFirstField, oldLastField, oldFirstRow, oldLastRow;
    int newFirstField, newLastField, newFirstRow, newLastRow;
    LineInfo *lineInfoP;

    if ((newColumn == w->mouseColumn) && (newTier == w->mouseTier)) return;

    if (w->selectStyle == VListSelectStyleSingle) {
        mouseLine = ColumnTierToLine (w, w->mouseColumn, w->mouseTier);
	newLine = ColumnTierToLine (w, newColumn, newTier);

	if (mouseLine != newLine) {
	    if (mouseLine != -1) SelectLine (w, mouseLine, 0);
	    if (newLine != -1) SelectLine (w, newLine, 1);
	}
    } else {
	ColumnTierToFieldRow (w, w->downColumn, w->downTier,
	    &downField, &downRow);

	ColumnTierToFieldRow (w, w->mouseColumn, w->mouseTier,
	    &mouseField, &mouseRow);

	ColumnTierToFieldRow (w, newColumn, newTier, &newField, &newRow);

	MinMax (downField, mouseField, &oldFirstField, &oldLastField);
	MinMax (downRow, mouseRow, &oldFirstRow, &oldLastRow);
	MinMax (downField, newField, &newFirstField, &newLastField);
	MinMax (downRow, newRow, &newFirstRow, &newLastRow);

	/* Go through the old select range, resetting any lines that are
	 * not included in the new select range. */

	if (w->selectUnit == VListSelectUnitField) fieldIncrement = 1;
    	else fieldIncrement = w->fieldCnt;

 	if (oldFirstField == -1) oldFirstField = 0;
	if (newFirstField == -1) newFirstField = 0;

	for (row = oldFirstRow; row <= oldLastRow; row++)
	    for (field = oldFirstField; field <= oldLastField;
	      field += fieldIncrement)
		if ((field < newFirstField) || (field > newLastField)
		  || (row < newFirstRow) || (row > newLastRow)) {
		    line = FieldRowToLine (w, field, row);
		    if (line != -1) {
			lineInfoP = LineToLineInfo (w, line);
			SelectLine (w, line, lineInfoP->undragSelect);
		    }
		}

	/* Go through the new select range, setting any lines that are not
	 * included in the old select range. */

	for (row = newFirstRow; row <= newLastRow; row++)
	    for (field = newFirstField; field <= newLastField;
	      field += fieldIncrement)
		if ((field < oldFirstField) || (field > oldLastField)
		  || (row < oldFirstRow) || (row > oldLastRow)) {
		    line = FieldRowToLine (w, field, row);
		    if (line != -1) SelectLine (w, line, w->selectParity);
		}
    }	

    w->mouseColumn = newColumn;
    w->mouseTier = newTier;
}

static void ButtonPressHandler(Widget gW, XtPointer closure, 
  XEvent *gEventP, Boolean *continue_to_dispatch)
{
    VListWidget w = (VListWidget) gW;
    XButtonEvent *eventP = (XButtonEvent *) gEventP;

    int line, field, row;
    LineInfo *lineInfoP;

    /* Chorded cancel. */

    if (w->listIsGrabbed) {
	w->listIsGrabbed = w->upTime = 0;

	for (line=0, lineInfoP=w->lineInfosP; line<w->lineCnt;
	  line++, lineInfoP++) {
	    lineInfoP->delete = 0;
	    if (lineInfoP->vLine.select != lineInfoP->undoSelect)
		SelectLine (w, line, lineInfoP->undoSelect);
	}

	SetInternalXYAdjust (w, w->undoXAdjust, w->undoYAdjust);
	AdjustPosition (w);
	return;
    }

    /* If this is not a simple un-chorded Button1 event, ignore it. */

    if ((eventP->button != Button1) || (eventP->state & (Button1Mask
      | Button2Mask | Button3Mask | Button4Mask | Button5Mask))) return;

    w->listIsGrabbed = 1;

    XYToColumnTier (w, eventP->x, eventP->y, &w->downColumn, &w->downTier);

    /* If the ButtonPress came soon enough after the last ButtonRelease, and
     * we're still over the same cell, and the widget does have at least one
     * selectConfirm callback declared, then prime the doubleClick action. */

    if ((eventP->time <= (w->upTime + w->doubleClickDelay))
      && (w->downColumn == w->upColumn) && (w->downTier == w->upTier)
      && (XtHasCallbacks ((Widget) w, VListNselectConfirmCallback)
      == XtCallbackHasSome)) {
	w->doubleClickIsPending = 1;
	return;
    }

    w->doubleClickIsPending = 0;

    /* Save state for chorded cancel. */

    for (line=0, lineInfoP=w->lineInfosP; line<w->lineCnt; line++, lineInfoP++)
	lineInfoP->undoSelect = lineInfoP->vLine.select;

    w->undoXAdjust = w->internalXAdjust;
    w->undoYAdjust = w->internalYAdjust;

    /* If the select style dictates, clear the selection. */

    if ((w->selectStyle == VListSelectStyleSingle) ||
      ((w->selectStyle == VListSelectStyleExtend) &&
      (!(eventP->state & ShiftMask)))) DeselectAllLines (w);

    /* If range select is possible, make a snapshot of the selection state
     * so we can backtrack. */

    if (w->selectStyle != VListSelectStyleSingle)
        for (line=0, lineInfoP=w->lineInfosP; line<w->lineCnt;
	  line++, lineInfoP++)
	    lineInfoP->undragSelect = lineInfoP->vLine.select;

    /* Determine the select parity, and flip the target line's selection. */

    if (w->selectStyle != VListSelectStyleSingle) {
	ColumnTierToFieldRow ( w, w->downColumn, w->downTier, &field, &row);
	line = FieldRowToLine (w, field, row);
    } else line = ColumnTierToLine (w, w->downColumn, w->downTier);

    if (line == -1) w->selectParity = 1;
    else {
	lineInfoP = LineToLineInfo (w, line);
	w->selectParity = (1 - lineInfoP->vLine.select);
	SelectLine (w, line, w->selectParity);
    }

    w->mouseColumn = w->downColumn;
    w->mouseTier = w->downTier;
}

static void PointerMotionHandler(Widget gW, XtPointer closure, 
  XEvent *gEventP, Boolean *continue_to_dispatch)
{
    VListWidget w = (VListWidget) gW;
    XMotionEvent *eventP = (XMotionEvent *) gEventP;

    int s, x, y, newColumn, newTier;

    if (!w->listIsGrabbed) return;
    if (w->doubleClickIsPending) return;

    x = eventP->x;
    y = eventP->y;

    XYToColumnTier (w, x, y, &newColumn, &newTier);
    NewSelectColumnTier (w, newColumn, newTier);

    /* Compute autoscroll strengths. */

    if (x < 0) s = x;
    else if (x >= w->core.width) s = x - w->core.width;
    else s = 0;
    w->xScrollStrength = s * w->autoScrollRate / 100;

    if (y < 0) s = y;
    else if (y >= w->core.height) s = y - w->core.height;
    else s = 0;
    w->yScrollStrength = s * w->autoScrollRate / 100;

    AdjustPosition (w);
}

static void ButtonReleaseHandler(Widget gW, XtPointer closure, 
  XEvent *gEventP, Boolean *continue_to_dispatch)
{
    VListWidget w = (VListWidget) gW;
    XButtonEvent *eventP = (XButtonEvent *) gEventP;

    int x, y;

    if (!w->listIsGrabbed) return;

    w->listIsGrabbed = 0;			/* done with list grab */

    /* If the select style supports drag select, and we're outside the window,
     * treat the upclick as though it were just inside the window to prevent
     * unseen lines from being selected. */

    x = eventP->x;
    y = eventP->y;

    if ((w->selectStyle != VListSelectStyleSingle)
      && (!w->doubleClickIsPending)) {
	if (x < 0) x = 0;
	else if (x >= w->core.width) x = w->core.width - 1;
    
	if (y < 0) y = 0;
	else if (y >= w->core.height) y = w->core.height - 1;
    }

    XYToColumnTier (w, x, y, &w->upColumn, &w->upTier);

    if (w->doubleClickIsPending) {
	w->upTime = 0;			/* don't want tripleClick problem */

	/* If the user didn't drag off the entry and didn't do a chorded cancel,
	 * then call the SelectConfirm callbacks. */

	if ((w->upColumn == w->downColumn) && (w->upTier == w->downTier)
	  && (eventP->type == ButtonRelease))
	    CallSelectCallbacks (w, eventP, 1);
    } else {
	w->upTime = eventP->time;	/* to test against next Down time */

	NewSelectColumnTier (w, w->upColumn, w->upTier);
	CallSelectCallbacks (w, eventP, 0);
    }

    HandlePendingDeletes (w);
}

static void DoInitialize(Widget gRequest, Widget gW, 
  ArgList args, Cardinal *num_args)
{
    VListWidget w       = (VListWidget) gW;

    {char *cP;
    for (cP = (char *)(&w->beginZeroInit); cP != (char *)(&w->endZeroInit); )
      *(cP++) = 0;
    }

    w->currentColoridx = w->currentFontidx = -1;

    CopyColors (w);
    CopyFonts (w);
    CopyFields (w);
    CopyLabels (w);
}

static void RealizeHandlersAndCallbacks(w)
    VListWidget w;
{
    Widget hScrollW, vScrollW;

    if ((hScrollW = w->hScrollW)) {
	XtAddCallback (hScrollW, XmNpageIncrementCallback, HPageIncCallback, w);
	XtAddCallback (hScrollW, XmNpageDecrementCallback, HPageDecCallback, w);
	XtAddCallback (hScrollW, XmNdragCallback, HValueChangedCallback, w);
	XtAddCallback (hScrollW, XmNvalueChangedCallback,
	    HValueChangedCallback, w);

        /* XmNpageIncrement was 0 - MSG 11/22/91 */
        XtVaSetValues (hScrollW, XmNminimum, 0, XmNincrement, w->charWidth, 
          XmNpageIncrement, 1, NULL);
    } else w->hScrollPolicy = VListScrollBarPolicyNever;

    if ((vScrollW = w->vScrollW)) {
	XtAddCallback (vScrollW, XmNpageIncrementCallback, VPageIncCallback, w);
	XtAddCallback (vScrollW, XmNpageDecrementCallback, VPageDecCallback, w);
	XtAddCallback (vScrollW, XmNdragCallback, VValueChangedCallback, w);
	XtAddCallback (vScrollW, XmNvalueChangedCallback,
	    VValueChangedCallback, w);
    
        /* XmNpageIncrement was 0 - MSG 11/22/91 */
	XtVaSetValues (vScrollW, XmNminimum, 0, XmNpageIncrement, 1, NULL);
    } else w->vScrollPolicy = VListScrollBarPolicyNever;

    /* Trap resize events on parent widget. */

#ifdef DRAWINGA_VLIST_PARENT
    XtAddCallback (w->core.parent, XmNresizeCallback,     ResizeCallback, 
      (XtPointer) w);
#else
    XtAddCallback (w->core.parent, VFrameNresizeCallback, ResizeCallback, 
      (XtPointer) w);
#endif

    /* Register an event handler for nonmaskable events. */

    XtAddRawEventHandler ((Widget) w, (EventMask) 0, (Boolean) 1, 
      HandleNonmaskableEvent, (XtPointer) 0);

    /* Register raw event handlers for the events that we will receive
     * as a result of our passive grab on Button1. */

    XtAddRawEventHandler ((Widget) w, ButtonPressMask, (Boolean) 0, 
      ButtonPressHandler, (XtPointer) 0);
    XtAddRawEventHandler ((Widget) w, PointerMotionMask, (Boolean) 0, 
      PointerMotionHandler, (XtPointer) 0);
    XtAddRawEventHandler ((Widget) w, ButtonReleaseMask, (Boolean) 0, 
      ButtonReleaseHandler, (XtPointer) 0);
}

static void RealizeGCs(w)
    VListWidget w;
{
    /* The GCs must be private (allocated with XCreateGC) rather
     * than shared (allocated with XtGetGC) because they are not read-only.
     * Their colors and fonts are changed dynamically. */

    {XGCValues values;
    values.background = w->core.background_pixel;
    values.function = GXcopy;
    w->normgc = XCreateGC (XtDisplay (w), XtWindow (w),
	GCBackground | GCFunction, &values);}

    {XGCValues values;
    values.foreground = w->core.background_pixel;
    values.function = GXcopy;
    w->invgc = XCreateGC (XtDisplay (w), XtWindow (w),
	GCForeground | GCFunction, &values);}

    {XGCValues values;
    values.function = GXinvert;
    w->flipgc = XCreateGC (XtDisplay (w), XtWindow (w),
	GCFunction, &values);}
}

static void RealizeGrabs(w)
    VListWidget w;
{
    /* Establish a passive grab on Button1Press. */

    XGrabButton (
	XtDisplay (w),					/* display */
	1,						/* button_grab */
	AnyModifier,					/* modifiers */
	XtWindow (w),					/* window */
	0,						/* owner_events */
	(ButtonPressMask | ButtonReleaseMask | Button1MotionMask),
							/* event_mask */
	GrabModeAsync,					/* pointer_mode */
	GrabModeAsync,					/* keyboard_mode */
	None,						/* confine_to */
	None);						/* cursor */
}

static void DoRealize(w, maskP, attributesP)
    VListWidget w;
    Mask *maskP;
    XSetWindowAttributes *attributesP;
{
    RealizeHandlersAndCallbacks (w);
   
    ComputeCellHeight (w);
    ComputeLabelInfo (w);
    ComputeLayout (w);

    XtCreateWindow ((Widget) w, InputOutput, CopyFromParent, *maskP, 
      attributesP);

    RealizeGCs (w);
    RealizeGrabs (w);

    StartUpdateSweep (w);

    if (w->visibleClosure) {
	VListMakeLineVisible (w, (Opaque) ((long) w->visibleClosure), 
            w->visiblePosition);
	w->visibleClosure = 0;
    }
}

#define Changed(f) (w->f != oldW->f)

static Boolean DoSetValues(Widget gOldW, Widget gRefW, Widget gW, 
    ArgList args, Cardinal *num_args)
{
    VListWidget oldW = (VListWidget) gOldW;
    VListWidget w    = (VListWidget) gW;

    int recomputeLayout = 0;

    if (Changed (fieldsP)) CopyFields (w);

    if (Changed (labelsP)) {
	FreeLabels (oldW);
	CopyLabels (w);
	if (XtIsRealized ((Widget) w)) ComputeLabelInfo (w);
    }

    if (Changed (selectStyle) || Changed (selectUnit)) {
	DeselectAllLines (oldW);
	w->selectionCnt = 0;
    }

    if (Changed (vScrollPosition) || Changed (vScrollPolicy)
      || Changed (hScrollPolicy) || Changed (columnStyle)) recomputeLayout = 1;

    if (Changed (rowSpacingHeight)) {
	ComputeCellHeight (w);
	recomputeLayout = 1;
    }

    if (recomputeLayout) {
	w->layoutIsValid = 0;
	if (XtIsRealized ((Widget) w)) StartUpdateSweep (w);
    }

    return (0);
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

  /* The VList widget must be a descendent of either a Motif manager
     widget or a topLevel or dialog shell widget. Managers are subclasses
     of the Bulletin Board and topLevel and dialog shells are subclasses
     of the Vendor shell                                                  */

  if (w == (Widget) NULL) XtAppErrorMsg(XtWidgetToApplicationContext(w),
    "Internal Error", "wrongParentage", "VListWidget",
    "This widget is not descended from a Bulletin Board or Vendor Shell.",
    (String *) NULL, (Cardinal *) NULL);

  value->addr = (XtPointer) &defaultFontList;
}

#define Offset(x) XtOffsetOf(VListRec, x)

static XtResource resources[] = {
 {VListNalignment, XtCValue, XtRInt, sizeof(int),
  Offset(alignment), XtRImmediate, (XtPointer) VListAlignmentBeginning},
 {VListNautoScrollRate, XtCValue, XtRInt, sizeof(int),
  Offset(autoScrollRate), XtRString, "15"},
 {VListNcolorList, XtCValue, XtRPixmap, sizeof(Pixmap),
  Offset(colorList), XtRImmediate, NULL},
 {VListNcolumnStyle, XtCValue, XtRInt, sizeof(int),
  Offset(columnStyle), XtRImmediate, (XtPointer) VListColumnStyleBestFit},
 {VListNdoubleClickDelay, XtCValue, XtRInt, sizeof(int),
  Offset(doubleClickDelay), XtRString, "250"},
 {VListNfieldCount, XtCValue, XtRInt, sizeof(int),
  Offset(fieldCnt), XtRString, "1"},
 {VListNfieldSpacingWidth, XtCValue, XtRInt, sizeof(int),
  Offset(fieldSpacingWidth), XtRString, "4"},
 {VListNfields, XtCValue, XtRPointer, sizeof(VListField *),
  Offset(fieldsP), XtRImmediate, NULL},
 {VListNfontList, XmCFontList, XmRFontList, sizeof(XmFontList),
  Offset(fontListP), XmRCallProc, (XtPointer) getDefaultFontList},
 {VListNforeground, XtCForeground, XtRPixel, sizeof(Pixel),
  Offset(foreground), XtRString, XtDefaultForeground},
 {VListNhScrollBarPolicy, XtCValue, XtRInt, sizeof(int),
  Offset(hScrollPolicy), XtRImmediate, 
  (XtPointer) VListScrollBarPolicyAsNeeded},
 {VListNhScrollBarWidget, XtCValue, XtRWindow, sizeof(Widget),
  Offset(hScrollW), XtRString, "0"},
 {VListNheaderWidget, XtCValue, XtRWindow, sizeof(Widget),
  Offset(vHeaderW), XtRString, "0"},
 {VListNlabelCount, XtCValue, XtRInt, sizeof(int),
  Offset(labelCnt), XtRString, "0"},
 {VListNlabels, XtCValue, XtRPointer, sizeof(VListLabel *),
  Offset(labelsP), XtRImmediate, NULL},
 {VListNmarginHeight, XtCValue, XtRInt, sizeof(int),
  Offset(marginHeight), XtRString, "6"},
 {VListNmarginWidth, XtCValue, XtRInt, sizeof(int),
  Offset(marginWidth), XtRString, "8"},
 {VListNrowSpacingHeight, XtCValue, XtRInt, sizeof(int),
  Offset(rowSpacingHeight), XtRString, "0"},
 {VListNselectCallback, XtCValue, XtRCallback, sizeof(XtCallbackList),
  Offset(selectCallback), XtRCallback, 0},
 {VListNselectConfirmCallback, XtCValue, XtRCallback, sizeof(XtCallbackList),
  Offset(selectConfirmCallback), XtRCallback, 0},
 {VListNselectStyle, XtCValue, XtRInt, sizeof(int),
  Offset(selectStyle), XtRImmediate, (XtPointer) VListSelectStyleSingle},
 {VListNselectUnit, XtCValue, XtRInt, sizeof(int),
  Offset(selectUnit), XtRImmediate, (XtPointer) VListSelectUnitRow},
 {VListNtextMarginWidth, XtCValue, XtRInt, sizeof(int),
  Offset(textMarginWidth), XtRString, "4"},
 {VListNvScrollBarPolicy, XtCValue, XtRInt, sizeof(int),
  Offset(vScrollPolicy), XtRImmediate, 
  (XtPointer) VListScrollBarPolicyAsNeeded},
 {VListNvScrollBarPosition, XtCValue, XtRInt, sizeof(int),
  Offset(vScrollPosition), XtRImmediate, 
  (XtPointer) VListScrollBarPositionRight},
 {VListNvScrollBarWidget, XtCValue, XtRWindow, sizeof(Widget),
  Offset(vScrollW), XtRString, "0"},
};

VListClassRec vlistClassRec = {
    {/* core_class fields	*/
	/* superclass		*/	(WidgetClass) &widgetClassRec,
	/* class_name	  	*/	"VList",
	/* widget_size	  	*/	sizeof(VListRec),
	/* class_initialize   	*/    	0,
	/* class_part_initialize */	0,
	/* class_inited       	*/	0,
	/* initialize	  	*/	DoInitialize,
	/* initialize_hook	*/	0,
	/* realize		*/	DoRealize,
	/* actions		*/    	0,
	/* num_actions	  	*/	0,
	/* resources	  	*/	resources,
	/* num_resources	*/	XtNumber(resources),
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

WidgetClass vlistWidgetClass = (WidgetClass) &vlistClassRec;

Widget VListCreate(pW, nameP, argsP, argCnt)
    Widget pW;
    char *nameP;
    Arg	argsP;
    int	argCnt;
{
    return (XtCreateWidget (nameP, vlistWidgetClass, pW, &argsP, argCnt));
}

void VListSelectAll(w, select)
    VListWidget w;
    int select;
{
    if (select) SelectAllLines (w);
    else DeselectAllLines (w);
}

Opaque VListGetFirstSelectedLine(w)
    VListWidget w;
{
    int line;
    LineInfo *lineInfoP;

    for (line=0, lineInfoP=w->lineInfosP; line<w->lineCnt; line++, lineInfoP++)
	if (lineInfoP->vLine.select) return (lineInfoP->vLine.closure);

    return (0);
}

int VListGetAllSelectedLines(w, closurePP)
    VListWidget w;
    Opaque **closurePP;
{
    Opaque *closureP;
    int remCnt;
    LineInfo *lineInfoP;

    if (!w->selectionCnt) closureP = (Opaque *) XtMalloc (1);
    else closureP = (Opaque *) XtMalloc (w->selectionCnt * sizeof (Opaque));

    *closurePP = closureP;

    for (remCnt=w->selectionCnt, lineInfoP=w->lineInfosP; remCnt; lineInfoP++)
	if (lineInfoP->vLine.select) {
	    *(closureP++) = lineInfoP->vLine.closure;
	    remCnt--;
	}

    return (w->selectionCnt);
}

int VListGetLineInfo(w, closure, vLineP, fieldP, rowP)
    VListWidget w;
    Opaque closure;
    VListLine *vLineP;
    int *fieldP, *rowP;
{
    int line, field, row;
    LineInfo *lineInfoP;

    if ((line = ClosureToLine (w, closure)) == -1) return (0);

    if (vLineP) {
	lineInfoP = LineToLineInfo (w, line);
    	*vLineP = lineInfoP->vLine;
    }

    if (fieldP || rowP) {
	LineToFieldRow (w, line, &field, &row);
	if (fieldP) *fieldP = field;
	if (rowP) *rowP = row;
    }

    return (1);
}

Opaque VListFieldRowToLine(w, field, row)
    VListWidget w;
    int field, row;
{
    int line;
    LineInfo *lineInfoP;

    if ((line = FieldRowToLine (w, field, row)) == -1) return (0);
    lineInfoP = LineToLineInfo (w, line);
    return (lineInfoP->vLine.closure);    
}

Opaque VListXYToLine(w, x, y)
    VListWidget w;
    int x, y;
{
    int line, column, tier;
    LineInfo *lineInfoP;

    XYToColumnTier (w, x, y, &column, &tier);
    if ((line = ColumnTierToLine (w, column, tier)) == -1) return (0);
    lineInfoP = LineToLineInfo (w, line);
    return (lineInfoP->vLine.closure);
}

Opaque VListAddLine(w, vLinesP, row)
    VListWidget w;
    VListLine *vLinesP;
    int row;
{
    VListLine *vLineP;
    LineInfo *firstNewLineInfoP, *lineInfoP;
    int firstNewLine, field, line, insertAtEnd, newLineCnt, selectCnt;
    int firstVY, lastVYP1, x, fromY, width, height, toY;

    /* Determine how many of the new items are selected. */

    selectCnt = 0;
    for (field = 0, vLineP = vLinesP; field < w->fieldCnt; field++, vLineP++)
	if ((vLineP->mask & VListLineSelectMask) && vLineP->select) selectCnt++;

    /* If any of the new lines are selected and we're doing single select style,
     * then clear the previous selection. */

    if (selectCnt && (w->selectStyle == VListSelectStyleSingle))
	DeselectAllLines (w);

    /* Extend the LineInfo array if necessary. */

    newLineCnt = w->lineCnt + w->fieldCnt;

    if (newLineCnt > w->maxLineCnt) {
	w->maxLineCnt = (newLineCnt * 3 / 2 + 8);	/* somewhat arbitrary */
	w->lineInfosP = (LineInfo *) XtRealloc ((char *) w->lineInfosP,
	    w->maxLineCnt * sizeof (LineInfo));
    }

    /* Find the insertion point, shuffle and initialize. */

    if ((row < 0) || ((firstNewLine = (row * w->fieldCnt)) >= w->lineCnt)) {
	firstNewLine = w->lineCnt;
	insertAtEnd = 1;
    } else insertAtEnd = 0;

    w->lineCnt += w->fieldCnt;
    w->rowCnt++;
    w->selectionCnt += selectCnt;

    for (line = (w->lineCnt - 1); line >= (firstNewLine + w->fieldCnt); line--)
	w->lineInfosP[line] = w->lineInfosP[line - w->fieldCnt];

    firstNewLineInfoP = LineToLineInfo (w, firstNewLine);

    for (field = 0, vLineP = vLinesP, lineInfoP = firstNewLineInfoP;
      field < w->fieldCnt; field++, vLineP++, lineInfoP++) {
	lineInfoP->vLine = *vLineP;

	/* If the user supplied a zero closure value, replace it. */

	if ((!(vLineP->mask & VListLineClosureMask)) || (!vLineP->closure))
	    lineInfoP->vLine.closure = (Opaque) ((long)(++w->lastUsedClosure));
    
	if (!(vLineP->mask & VListLineTextMask))
	    lineInfoP->vLine.textP = 0;

	if (!(vLineP->mask & VListLineFontidxMask))
	    lineInfoP->vLine.fontidx = 0;
    
	if (!(vLineP->mask & VListLineColoridxMask))
	    lineInfoP->vLine.coloridx = 0;

	if (!(vLineP->mask & VListLineSelectMask))
	    lineInfoP->vLine.select = 0;
    
	if (!(vLineP->mask & VListLineSensitiveMask))
	    lineInfoP->vLine.sensitive = 1;
 
	lineInfoP->segmentInfosP = 0;

	if (vLineP->mask & VListLineSegmentsMask) {
	    CopySegments (w, lineInfoP);
	} else {
	    lineInfoP->vLine.segmentsP = 0;
	    lineInfoP->vLine.segmentCount = 0;
	}

        if (lineInfoP->vLine.textP) {
	    lineInfoP->vLine.textP = XtNewString (lineInfoP->vLine.textP);
	    lineInfoP->textStrlen = strlen (lineInfoP->vLine.textP);
	    ComputeSegmentDefaults (w, lineInfoP);
	    ComputeTextInfo (w, lineInfoP);
	} else {
	    lineInfoP->vLine.textP = 0;
	    lineInfoP->textStrlen = 0;
	    lineInfoP->textWidth = 0;
	}

	lineInfoP->expose = lineInfoP->delete = 0;
    }

    if ((!XtIsRealized ((Widget) w)) || w->batchUpdate) {
	w->layoutIsValid = 0;
	return (firstNewLineInfoP->vLine.closure);
    }

    /* If there is only one group and we are not changing any column widths,
     * then preserve the layout. */

    if (w->layoutIsValid) {
	if (w->groupCnt != 1) w->layoutIsValid = 0;
	else {
	    for (field = 0, lineInfoP = LineToLineInfo (w, firstNewLine); field < w->fieldCnt; field++, lineInfoP++)
		if (AddWidthContribution (w, field,
		  lineInfoP->textWidth + 2 * w->textMarginWidth)) {
		    w->layoutIsValid = 0;
		    break;
		}
	}
    }

    if (!w->layoutIsValid) {
	StartUpdateSweep (w);
	return (firstNewLineInfoP->vLine.closure);
    }

    w->tierCnt = w->rowCnt;
    w->logicalHeight = w->tierCnt * w->cellHeight + 2 * w->marginHeight
	- w->rowSpacingHeight;

    ArrangeWidgets (w);

    if (!insertAtEnd) {
	if (w->scrollIsActive) {
	    StartUpdateSweep (w);
	    return (firstNewLineInfoP->vLine.closure);
	}

	firstVY = w->marginHeight + row * w->cellHeight;
	lastVYP1 = firstVY + w->cellHeight;
	x = 0;
	fromY = firstVY - w->requestedYAdjust;
	width = w->core.width;
	height = (w->rowCnt - row - 1) * w->cellHeight + w->marginHeight;
	toY = lastVYP1 - w->requestedYAdjust;

	XCopyArea (XtDisplay (w), XtWindow (w), XtWindow (w), w->normgc,
	    x, fromY, width, height, x, toY);

	w->scrollIsActive = 1;
    }

    for (line = firstNewLine; line < (firstNewLine + w->fieldCnt); line++)
	Draw (w, line, 1, 1);

    return (firstNewLineInfoP->vLine.closure);
}

void VListChangeLine(w, closure, vLineP)
    VListWidget w;
    Opaque closure;
    VListLine *vLineP;
{
    int line, selectLine = 0, oldTextWidth = 0, column, tier;
    int redraw = 0, recomputeTextInfo = 0, flipSelect = 0;
    int recomputeLayout = 0, recomputeSegmentDefaults = 0;
    LineInfo *lineInfoP, *selectLineInfoP;

    if ((line = ClosureToLine (w, closure)) == -1) return;

    lineInfoP = LineToLineInfo (w, line);

    if ((vLineP->mask & VListLineClosureMask) && vLineP->closure)
	lineInfoP->vLine.closure = vLineP->closure;

    if ((vLineP->mask & VListLineTextMask)
      && ((!lineInfoP->vLine.textP)
      || strcmp (vLineP->textP, lineInfoP->vLine.textP))) {
	XtFree (lineInfoP->vLine.textP);
        lineInfoP->vLine.textP = XtNewString (vLineP->textP);
	lineInfoP->textStrlen = strlen (lineInfoP->vLine.textP);
	recomputeTextInfo = redraw = 1;
    }

    if (vLineP->mask & VListLineSegmentsMask) {
	lineInfoP->vLine.segmentsP = vLineP->segmentsP;
	lineInfoP->vLine.segmentCount = vLineP->segmentCount;
        CopySegments (w, lineInfoP);
	recomputeSegmentDefaults = recomputeTextInfo = redraw = 1;
    }

    if ((vLineP->mask & VListLineFontidxMask)
      && (vLineP->fontidx != lineInfoP->vLine.fontidx)) {
	lineInfoP->vLine.fontidx = vLineP->fontidx;
	recomputeSegmentDefaults = recomputeTextInfo = redraw = 1;
    }

    if ((vLineP->mask & VListLineColoridxMask)
      && (vLineP->coloridx != lineInfoP->vLine.coloridx)) {
	lineInfoP->vLine.coloridx = vLineP->coloridx;
	recomputeSegmentDefaults = redraw = 1;
    }

    if (vLineP->mask & VListLineSelectMask) {
	if (w->selectUnit == VListSelectUnitField) {
	    selectLine = line;
	    selectLineInfoP = lineInfoP;
	} else {
	    selectLine = LineToFirstLineInRow (w, line);
            selectLineInfoP = LineToLineInfo (w, selectLine);
	}

        if (vLineP->select != selectLineInfoP->vLine.select) {
	    if (vLineP->select && (w->selectStyle == VListSelectStyleSingle))
		DeselectAllLines (w);
    
	    if ((selectLineInfoP->vLine.select = vLineP->select))
		w->selectionCnt++;
	    else w->selectionCnt--;
    
	    flipSelect = 1;
        }
    }

    if ((vLineP->mask & VListLineSensitiveMask)
      && (vLineP->sensitive != lineInfoP->vLine.sensitive))
	lineInfoP->vLine.sensitive = vLineP->sensitive;

    if (recomputeSegmentDefaults) ComputeSegmentDefaults (w, lineInfoP);

    if (recomputeTextInfo) {
	oldTextWidth = lineInfoP->textWidth;
	ComputeTextInfo (w, lineInfoP);
	if (oldTextWidth != lineInfoP->textWidth) recomputeLayout = 1;
    }

    if ((!XtIsRealized ((Widget) w)) || w->batchUpdate) {
	if (recomputeLayout) w->layoutIsValid = 0;
	return;
    }

    /* See if the change really changes the column width. */

    if (recomputeLayout) {
	LineToColumnTier (w, line, &column, &tier);

	if (!ChangeWidthContribution (w, column,
	  oldTextWidth + 2 * w->textMarginWidth,
	  lineInfoP->textWidth + 2 * w->textMarginWidth)) recomputeLayout = 0;
    }

    if (!recomputeLayout) {
	if (redraw) Draw (w, line, 1, 1);
	else if (flipSelect) Flip (w, line);
    
	if (flipSelect && (w->selectUnit == VListSelectUnitRow)) {
	    int lastLineP1 = selectLine + w->fieldCnt;
    
	    for (; selectLine < lastLineP1; selectLine++)
		if (selectLine != line) Flip (w, selectLine);
	}

	return;
    }

    /*****/
    w->layoutIsValid = 0;
    StartUpdateSweep (w);
}

void VListChangeLineClosure(w, closure, newClosure)
    VListWidget w;
    Opaque closure, newClosure;
{
    VListLine vLine;
    vLine.mask = VListLineClosureMask;
    vLine.closure = newClosure;
    VListChangeLine (w, closure, &vLine);
}

void VListChangeLineText(w, closure, newTextP)
    VListWidget w;
    Opaque closure;
    char *newTextP;
{
    VListLine vLine;
    vLine.mask = VListLineTextMask;
    vLine.textP = newTextP;
    VListChangeLine (w, closure, &vLine);
}

void VListChangeLineFontidx(w, closure, newFontidx)
    VListWidget w;
    Opaque closure;
    int newFontidx;
{
    VListLine vLine;
    vLine.mask = VListLineFontidxMask;
    vLine.fontidx = newFontidx;
    VListChangeLine (w, closure, &vLine);
}

void VListChangeLineColoridx(w, closure, newColoridx)
    VListWidget w;
    Opaque closure;
    int newColoridx;
{
    VListLine vLine;
    vLine.mask = VListLineColoridxMask;
    vLine.coloridx = newColoridx;
    VListChangeLine (w, closure, &vLine);
}

void VListChangeLineSelect(w, closure, newSelect)
    VListWidget w;
    Opaque closure;
    int newSelect;
{
    VListLine vLine;
    vLine.mask = VListLineSelectMask;
    vLine.select = newSelect;
    VListChangeLine (w, closure, &vLine);
}

void VListChangeLineSensitive(w, closure, newSensitive)
    VListWidget w;
    Opaque closure;
    int newSensitive;
{
    VListLine vLine;
    vLine.mask = VListLineSensitiveMask;
    vLine.sensitive = newSensitive;
    VListChangeLine (w, closure, &vLine);
}

void VListChangeLineSegments(w, closure, newSegmentsP, newSegmentCount)
    VListWidget w;
    Opaque closure;
    VListSegment *newSegmentsP;
    int newSegmentCount;
{
    VListLine vLine;
    vLine.mask = VListLineSegmentsMask;
    vLine.segmentsP = (long) newSegmentsP;
    vLine.segmentCount = newSegmentCount;
    VListChangeLine (w, closure, &vLine);
}

void VListMoveLine(w, closure, up)
    VListWidget w;
    Opaque closure;
    int up;
{
    LineInfo lineInfo, *lineInfoP, *otherLineInfoP;
    int field, firstLine, otherFirstLine, line;

    if ((line = ClosureToLine (w, closure)) == -1) return;
    firstLine = LineToFirstLineInRow (w, line);

    if (up) otherFirstLine = firstLine - w->fieldCnt;
    else otherFirstLine = firstLine + w->fieldCnt;

    if (otherFirstLine < 0) return;		/* already at top */
    if (otherFirstLine >= w->lineCnt) return;	/* already at bottom */

    for (field = 0,
      lineInfoP = LineToLineInfo (w, firstLine),
      otherLineInfoP = LineToLineInfo (w, otherFirstLine);
      field < w->fieldCnt; field++, lineInfoP++, otherLineInfoP++) {
        lineInfo = *lineInfoP;			/* copy to temp */
        *lineInfoP = *otherLineInfoP;		/* copy other */
        *otherLineInfoP = lineInfo;		/* and restore */
    }

    /* If the row is changing groups, invalidate the layout. */

    if ((firstLine / w->fieldCnt / w->tierCnt)
      != (otherFirstLine / w->fieldCnt / w->tierCnt)) w->layoutIsValid = 0;

    if ((!XtIsRealized ((Widget) w)) || w->batchUpdate) return;

    if (w->layoutIsValid) {
	for (field = 0, line = firstLine; field < w->fieldCnt;
          field++, line++) Draw (w, line, 1, 1);

	for (field = 0, line = otherFirstLine; field < w->fieldCnt;
	  field++, line++) Draw (w, line, 1, 1);

	return;
    }

    /*****/
    StartUpdateSweep (w);
}	

void VListRemoveLine(w, closure)
    VListWidget w;
    Opaque closure;
{
    int field, line, firstLine;
    LineInfo *firstLineInfoP, *lineInfoP;

    if ((line = ClosureToLine (w, closure)) == -1) return;

    firstLine = LineToFirstLineInRow (w, line);
    firstLineInfoP = LineToLineInfo (w, firstLine);

    /* Fix up the selection count, deselect the line, and keep it from
     * being selected again by making it not sensitive. */

    for (field=0, lineInfoP=firstLineInfoP; field<w->fieldCnt;
      field++, lineInfoP++) {
	if (lineInfoP->vLine.select) w->selectionCnt--;
	lineInfoP->vLine.select = lineInfoP->vLine.sensitive = 0;
    }

    firstLineInfoP->delete = w->anyAreDeleted = 1;
    HandlePendingDeletes (w);
}

void VListRemoveAllLines(w)
    VListWidget w;
{
    int line;
    LineInfo *lineInfoP;

    for (line = 0, lineInfoP = w->lineInfosP; line < w->lineCnt;
      line++, lineInfoP++) {
	XtFree (lineInfoP->vLine.textP);
	XtFree ((char *) lineInfoP->segmentInfosP);
    }

    w->anyAreDeleted = w->anyAreExposed = w->lineCnt = w->rowCnt = 0;
    w->selectionCnt = w->layoutIsValid = 0;

    SetInternalXYAdjust (w, 0, 0);
    SetPosition (w);

    if ((!XtIsRealized ((Widget) w)) || w->batchUpdate) return;

    StartUpdateSweep (w);
}

int VListComputePreferredWidth(w)
    VListWidget w;
{
    int width, height;

    /* If we are not in single column style, or we always want the
     * horizontal scrollbar anyway, just return the current size. */

    if ((w->columnStyle != VListColumnStyleSingle) 
      || (w->hScrollPolicy == VListScrollBarPolicyAlways))
	return (w->core.parent->core.width);

    DoColumnLayout (w);

    width = w->logicalWidth;
    height = w->core.parent->core.height;

    if (w->headerHeight)
	height -= (w->headerHeight + w->core.border_width);

    if (w->vScrollW && ((w->vScrollPolicy == VListScrollBarPolicyAlways)
      || ((w->vScrollPolicy == VListScrollBarPolicyAsNeeded)
      && (w->logicalHeight > height))))
	width += (w->vScrollW->core.width + w->vScrollW->core.border_width);

    return (width);
}

/* end of file VLIST.C */
