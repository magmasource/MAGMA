#ifndef _vList_h
#define _vList_h

/*
MELTS Source Code: RCS $Log: vlist.h,v $
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
 * Revision 3.6  1997/06/21  22:49:17  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:22:56  ghiorso
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
 * Revision 3.1  1995/08/18  19:21:43  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  19:21:43  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include file for vList widget (file: VLIST.H)
**
**      This module contains C-language declarations needed to use the VList 
**      widget. Include this file into any C module that directly uses a 
**      VList widget.
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Original Version
**              COPYRIGHT (c) 1988, 1989  BY
**              DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASSACHUSETTS.
**              ALL RIGHTS RESERVED.
**              11-Jan-1990 (sjk) Add segmented string support.
**              03-Jan-1990 (sjk) Add VListAlignmentLeft and ~Right, and 
**                remove column and tier fields from VListSelectCallbackStruct.
**              28-Dec-1989 (sjk) Version X2.0 update.
**              15-Nov-1988 (sjk) Initial entry.
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  November 25, 1991
**              Converted VListNfonTable -> VListNfontList
**      V2.0-3  Mark S. Ghiorso  February 18, 1992
**              Added function declarations for ANSI compliance
**
**--
*/

typedef struct _VListClassRec *VListWidgetClass;
typedef struct _VListRec      *VListWidget;

extern WidgetClass vlistWidgetClass;

#define VListNalignment			"alignment"
#define VListNautoScrollRate		"autoScrollRate"
#define VListNcolorList			"colorList"
#define VListNcolumnStyle		"columnStyle"
#define VListNdoubleClickDelay		"doubleClickDelay"
#define VListNfieldCount		"fieldCount"
#define VListNfieldSpacingWidth		"fieldSpacingWidth"
#define VListNfields			"fields"
#define VListNfontList			"fontList"
#define VListNforeground		"foreground"
#define VListNhScrollBarPolicy		"hScrollBarPolicy"
#define VListNhScrollBarWidget		"hScrollBarWidget"
#define VListNheaderWidget		"headerWidget"
#define VListNlabelCount		"labelCount"
#define VListNlabels			"labels"
#define VListNmarginHeight		"marginHeight"
#define VListNmarginWidth		"marginWidth"
#define VListNrowSpacingHeight		"rowSpacingHeight"
#define VListNselectCallback		"selectCallback"
#define VListNselectConfirmCallback	"selectConfirmCallback"
#define VListNselectStyle		"selectStyle"
#define VListNselectUnit		"selectUnit"
#define VListNtextMarginWidth		"textMarginWidth"
#define VListNvScrollBarPolicy		"vScrollBarPolicy"
#define VListNvScrollBarPosition	"vScrollBarPosition"
#define VListNvScrollBarWidget		"vScrollBarWidget"

#define VListScrollBarPolicyNever	1
#define VListScrollBarPolicyAlways	2
#define VListScrollBarPolicyAsNeeded	3

#define VListScrollBarPositionLeft	1
#define VListScrollBarPositionRight	2

#define VListColumnStyleSingle		1
#define VListColumnStyleMultiple	2
#define VListColumnStyleBestFit		3

#define VListSelectStyleSingle		1
#define VListSelectStyleMultiple	2
#define VListSelectStyleExtend		3

#define VListSelectUnitField		1
#define VListSelectUnitRow		2

typedef struct {
    int		mask;		/* mask flags */
    int		width;		/* field's width in pixels */
    int		alignment;	/* alignment */
} VListField;

#define VListFieldWidthMask		(1<<0)
#define VListFieldAlignmentMask		(1<<1)

typedef struct {
    int		mask;		/* mask flags */
    char	*textP;		/* pointer to label's ASCIZ text */
    int		row;		/* zero-based row within header area */
    int		alignment;	/* label alignment */
    int		firstField;	/* first field */
    int		lastField;	/* last field */
} VListLabel;

#define VListLabelTextMask		(1<<0)
#define VListLabelRowMask		(1<<1)
#define VListLabelAlignmentMask		(1<<2)
#define VListLabelFirstFieldMask	(1<<3)
#define VListLabelLastFieldMask		(1<<4)

#define VListAlignmentCenter		1
#define VListAlignmentBeginning		2
#define VListAlignmentEnd		3
#define VListAlignmentLeft		4
#define VListAlignmentRight		5

typedef struct {
    int		textPosition;	/* zero-based offset into VListLine.textP */
    int		textStrlen;	/* number of bytes in text segment */
    int		mask;		/* mask flags */
    int		fontidx;	/* segment's font index */
    int		coloridx;	/* segment's color index */
} VListSegment;

#define VListSegmentFontidxMask		(1<<0)
#define VListSegmentColoridxMask	(1<<1)

typedef struct {
    int		mask;		/* mask flags */
    Opaque	closure;	/* line's Opaque closure (ID number) */
    char	*textP;		/* pointer to line's ASCIZ text */
    int         fontidx;        /* line's font index */
    int         coloridx;       /* line's color index */
    int		select;		/* line is selected (1/0) */
    int		sensitive;	/* line can be selected (1/0) */
    long	segmentsP;	/* array of VListSegment structures */
    int		segmentCount;	/* count of VListSegment entries */
} VListLine;

#define VListLineClosureMask		(1<<0)
#define VListLineTextMask		(1<<1)
#define VListLineFontidxMask		(1<<2)
#define VListLineColoridxMask		(1<<3)
#define VListLineSelectMask		(1<<4)
#define VListLineSensitiveMask		(1<<5)
#define VListLineSegmentsMask		(1<<6)

#define VListVisibleInWindow		1
#define VListVisibleAtTop		2
#define VListVisibleAtBottom		3
#define VListVisibleAtLeft		4
#define VListVisibleAtRight		5
#define VListVisibleAtTopLeft		6
#define VListVisibleAtTopRight		7
#define VListVisibleAtBottomLeft	8
#define VListVisibleAtBottomRight	9

#define VListAddAtTop			0
#define VListAddAtBottom		-1

#define VListMoveLineDown		0
#define VListMoveLineUp			1

#define VListCRSelect			1
#define VListCRSelectConfirm		2

typedef struct {
    int		reason;		/* VListCRSelect or VListCRSelectConfirm */
    XEvent	*event;		/* event which caused callback (may be zero) */
    int		field;		/* upclick logical field number */
    int		row;		/* upclick logical row number */
    VListLine	vLine;		/* line information (closure may be zero) */
} VListSelectCallbackStruct;

Widget VListCreate(Widget w, char *name, Arg args, int argCnt);
void VListMakeLineVisible(VListWidget w, Opaque closure, int visible);
void VListStartBatchUpdate(VListWidget w);
void VListEndBatchUpdate(VListWidget w);
void VListSelectAll(VListWidget w, int select);
Opaque VListGetFirstSelectedLine(VListWidget w);
int VListGetAllSelectedLines(VListWidget w, Opaque **closurePP);
int VListGetLineInfo(VListWidget w, Opaque closure, VListLine *vLineP,
  int *fieldP, int *rowP);
Opaque VListFieldRowToLine(VListWidget w, int field, int row);
Opaque VListXYToLine(VListWidget w, int x, int y);
Opaque VListAddLine(VListWidget w, VListLine *vLinesP, int row);
void VListChangeLine(VListWidget w, Opaque closure, VListLine *vLineP);
void VListChangeLineClosure(VListWidget w, Opaque closure, Opaque newClosure);
void VListChangeLineText(VListWidget w, Opaque closure, char *newTextP);
void VListChangeLineFontidx(VListWidget w, Opaque closure, int newFontidx);
void VListChangeLineColoridx(VListWidget w, Opaque closure, int newColoridx);
void VListChangeLineSelect(VListWidget w, Opaque closure, int newSelect);
void VListChangeLineSensitive(VListWidget w, Opaque closure, int newSensitive);
void VListChangeLineSegments(VListWidget w, Opaque closure, 
   VListSegment *newSegmentsP, int newSegmentCount);
void VListMoveLine(VListWidget w, Opaque closure, int up);
void VListRemoveLine(VListWidget w, Opaque closure);
void VListRemoveAllLines(VListWidget w);
int VListComputePreferredWidth(VListWidget w);

#endif /* _vList_h */
