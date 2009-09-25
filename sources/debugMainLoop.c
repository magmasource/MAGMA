const char *debugMainLoop_ver(void) { return "$Id: debugMainLoop.c,v 1.2 2006/08/17 16:47:18 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: debugMainLoop.c,v $
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
 * Revision 3.6  1997/06/21  22:49:59  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:23:37  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:41  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:33:43  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  17:29:26  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  17:29:26  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Debug version of XtMainLoop (file: DEBUGMAINLOOP.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  August 31, 1990   Original Version
**      V2.0-1  Mark S. Ghiorso  November 14, 1991
**              Conversion to OSF Motif V1.1.1/X11 Release 4
**      V2.0-2  Mark S. Ghiorso  February 18, 1992
**              Corrected some minor non-ANSI type casting errors
**      V3.0-1  Mark S. Ghiorso March 12, 1994
**              Reorganized code for alpha vms errors
**--
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Xm/Xm.h> 
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xproto.h>

#include "interface.h"

const char *Yes = "YES";
const char *No = "NO";
const char *Unknown = "unknown";

Display *dpy;

static void prologue (eventp, event_name)
    XEvent *eventp;
    char *event_name;
{
    XAnyEvent *e = (XAnyEvent *) eventp;

    printf ("\n%s event, serial %ld, synthetic %s, window 0x%lx,\n",
	    event_name, e->serial, e->send_event ? Yes : No, e->window);
    return;
}


static void do_KeyPress (eventp)
    XEvent *eventp;
{
    XKeyEvent *e = (XKeyEvent *) eventp;
    KeySym ks;
    char *ksname;
    int nbytes;
    char str[256+1];

    nbytes = XLookupString ((XKeyEvent *) eventp, str, 256, &ks, NULL);
    if (ks == NoSymbol)
	ksname = "NoSymbol";
    else if (!(ksname = XKeysymToString (ks)))
	ksname = "(no name)";
    printf ("    root 0x%lx, subw 0x%lx, time %lu, (%d,%d), root:(%d,%d),\n",
	    e->root, e->subwindow, e->time, e->x, e->y, e->x_root, e->y_root);
    printf ("    state 0x%x, keycode %u (keysym 0x%x, %s), same_screen %s,\n",
	    e->state, e->keycode, (unsigned int) ks, ksname, 
	    e->same_screen ? Yes : No);
    if (nbytes < 0) nbytes = 0;
    if (nbytes > 256) nbytes = 256;
    str[nbytes] = '\0';
    printf ("    XLookupString gives %d characters:  \"%s\"\n", nbytes, str);

    return;
}

static void do_KeyRelease (eventp)
    XEvent *eventp;
{
    do_KeyPress (eventp);		/* since it has the same info */
    return;
}

static void do_ButtonPress (eventp)
    XEvent *eventp;
{
    XButtonEvent *e = (XButtonEvent *) eventp;

    printf ("    root 0x%lx, subw 0x%lx, time %lu, (%d,%d), root:(%d,%d),\n",
	    e->root, e->subwindow, e->time, e->x, e->y, e->x_root, e->y_root);
    printf ("    state 0x%x, button %u, same_screen %s\n",
	    e->state, e->button, e->same_screen ? Yes : No);

    return;
}

static void do_ButtonRelease (eventp)
    XEvent *eventp;
{
    do_ButtonPress (eventp);		/* since it has the same info */
    return;
}

static void do_MotionNotify (eventp)
    XEvent *eventp;
{
    XMotionEvent *e = (XMotionEvent *) eventp;

    printf ("    root 0x%lx, subw 0x%lx, time %lu, (%d,%d), root:(%d,%d),\n",
	    e->root, e->subwindow, e->time, e->x, e->y, e->x_root, e->y_root);
    printf ("    state 0x%x, is_hint %u, same_screen %s\n",
	    e->state, e->is_hint, e->same_screen ? Yes : No);

    return;
}

static void do_EnterNotify (eventp)
    XEvent *eventp;
{
    XCrossingEvent *e = (XCrossingEvent *) eventp;
    char *mode, *detail;
    char dmode[10], ddetail[10];

    switch (e->mode) {
      case NotifyNormal:  mode = "NotifyNormal"; break;
      case NotifyGrab:  mode = "NotifyGrab"; break;
      case NotifyUngrab:  mode = "NotifyUngrab"; break;
      case NotifyWhileGrabbed:  mode = "NotifyWhileGrabbed"; break;
      default:  mode = dmode, sprintf (dmode, "%u", e->mode); break;
    }

    switch (e->detail) {
      case NotifyAncestor:  detail = "NotifyAncestor"; break;
      case NotifyVirtual:  detail = "NotifyVirtual"; break;
      case NotifyInferior:  detail = "NotifyInferior"; break;
      case NotifyNonlinear:  detail = "NotifyNonlinear"; break;
      case NotifyNonlinearVirtual:  detail = "NotifyNonlinearVirtual"; break;
      case NotifyPointer:  detail = "NotifyPointer"; break;
      case NotifyPointerRoot:  detail = "NotifyPointerRoot"; break;
      case NotifyDetailNone:  detail = "NotifyDetailNone"; break;
      default:  detail = ddetail; sprintf (ddetail, "%u", e->detail); break;
    }

    printf ("    root 0x%lx, subw 0x%lx, time %lu, (%d,%d), root:(%d,%d),\n",
	    e->root, e->subwindow, e->time, e->x, e->y, e->x_root, e->y_root);
    printf ("    mode %s, detail %s, same_screen %s,\n",
	    mode, detail, e->same_screen ? Yes : No);
    printf ("    focus %s, state %u\n", e->focus ? Yes : No, e->state);

    return;
}

static void do_LeaveNotify (eventp)
    XEvent *eventp;
{
    do_EnterNotify (eventp);		/* since it has same information */
    return;
}

static void do_FocusIn (eventp)
    XEvent *eventp;
{
    XFocusChangeEvent *e = (XFocusChangeEvent *) eventp;
    char *mode, *detail;
    char dmode[10], ddetail[10];

    switch (e->mode) {
      case NotifyNormal:  mode = "NotifyNormal"; break;
      case NotifyGrab:  mode = "NotifyGrab"; break;
      case NotifyUngrab:  mode = "NotifyUngrab"; break;
      case NotifyWhileGrabbed:  mode = "NotifyWhileGrabbed"; break;
      default:  mode = dmode, sprintf (dmode, "%u", e->mode); break;
    }

    switch (e->detail) {
      case NotifyAncestor:  detail = "NotifyAncestor"; break;
      case NotifyVirtual:  detail = "NotifyVirtual"; break;
      case NotifyInferior:  detail = "NotifyInferior"; break;
      case NotifyNonlinear:  detail = "NotifyNonlinear"; break;
      case NotifyNonlinearVirtual:  detail = "NotifyNonlinearVirtual"; break;
      case NotifyPointer:  detail = "NotifyPointer"; break;
      case NotifyPointerRoot:  detail = "NotifyPointerRoot"; break;
      case NotifyDetailNone:  detail = "NotifyDetailNone"; break;
      default:  detail = ddetail; sprintf (ddetail, "%u", e->detail); break;
    }

    printf ("    mode %s, detail %s\n", mode, detail);
    return;
}

static void do_FocusOut (eventp)
    XEvent *eventp;
{
    do_FocusIn (eventp);		/* since it has same information */
    return;
}

static void do_KeymapNotify (eventp)
    XEvent *eventp;
{
    XKeymapEvent *e = (XKeymapEvent *) eventp;
    int i;

    printf ("    keys:  ");
    for (i = 0; i < 32; i++) {
	if (i == 16) printf ("\n           ");
	printf ("%-3u ", (unsigned int) e->key_vector[i]);
    }
    printf ("\n");
    return;
}

static void do_Expose (eventp)
    XEvent *eventp;
{
    XExposeEvent *e = (XExposeEvent *) eventp;

    printf ("    (%d,%d), width %d, height %d, count %d\n",
	    e->x, e->y, e->width, e->height, e->count);
    return;
}

static void do_GraphicsExpose (eventp)
    XEvent *eventp;
{
    XGraphicsExposeEvent *e = (XGraphicsExposeEvent *) eventp;
    char *m;
    char mdummy[10];

    switch (e->major_code) {
      case X_CopyArea:  m = "CopyArea";  break;
      case X_CopyPlane:  m = "CopyPlane";  break;
      default:  m = mdummy; sprintf (mdummy, "%d", e->major_code); break;
    }

    printf ("    (%d,%d), width %d, height %d, count %d,\n",
	    e->x, e->y, e->width, e->height, e->count);
    printf ("    major %s, minor %d\n", m, e->minor_code);
    return;
}

static void do_NoExpose (eventp)
    XEvent *eventp;
{
    XNoExposeEvent *e = (XNoExposeEvent *) eventp;
    char *m;
    char mdummy[10];

    switch (e->major_code) {
      case X_CopyArea:  m = "CopyArea";  break;
      case X_CopyPlane:  m = "CopyPlane";  break;
      default:  m = mdummy; sprintf (mdummy, "%d", e->major_code); break;
    }

    printf ("    major %s, minor %d\n", m, e->minor_code);
    return;
}

static void do_VisibilityNotify (eventp)
    XEvent *eventp;
{
    XVisibilityEvent *e = (XVisibilityEvent *) eventp;
    char *v;
    char vdummy[10];

    switch (e->state) {
      case VisibilityUnobscured:  v = "VisibilityUnobscured"; break;
      case VisibilityPartiallyObscured: v = "VisibilityPartiallyObscured";break;
      case VisibilityFullyObscured:  v = "VisibilityFullyObscured"; break;
      default:  v = vdummy; sprintf (vdummy, "%d", e->state); break;
    }

    printf ("    state %s\n", v);
    return;
}

static void do_CreateNotify (eventp)
    XEvent *eventp;
{
    XCreateWindowEvent *e = (XCreateWindowEvent *) eventp;

    printf ("    parent 0x%lx, window 0x%lx, (%d,%d), width %d, height %d\n",
	    e->parent, e->window, e->x, e->y, e->width, e->height);
    printf ("border_width %d, override %s\n",
	    e->border_width, e->override_redirect ? Yes : No);
    return;
}

static void do_DestroyNotify (eventp)
    XEvent *eventp;
{
    XDestroyWindowEvent *e = (XDestroyWindowEvent *) eventp;

    printf ("    event 0x%lx, window 0x%lx\n", e->event, e->window);
    return;
}

static void do_UnmapNotify (eventp)
    XEvent *eventp;
{
    XUnmapEvent *e = (XUnmapEvent *) eventp;

    printf ("    event 0x%lx, window 0x%lx, from_configure %s\n",
	    e->event, e->window, e->from_configure ? Yes : No);
    return;
}

static void do_MapNotify (eventp)
    XEvent *eventp;
{
    XMapEvent *e = (XMapEvent *) eventp;

    printf ("    event 0x%lx, window 0x%lx, override %s\n",
	    e->event, e->window, e->override_redirect ? Yes : No);
    return;
}

static void do_MapRequest (eventp)
    XEvent *eventp;
{
    XMapRequestEvent *e = (XMapRequestEvent *) eventp;

    printf ("    parent 0x%lx, window 0x%lx\n", e->parent, e->window);
    return;
}

static void do_ReparentNotify (eventp)
    XEvent *eventp;
{
    XReparentEvent *e = (XReparentEvent *) eventp;

    printf ("    event 0x%lx, window 0x%lx, parent 0x%lx,\n",
	    e->event, e->window, e->parent);
    printf ("    (%d,%d), override %s\n", e->x, e->y, 
	    e->override_redirect ? Yes : No);
    return;
}

static void do_ConfigureNotify (eventp)
    XEvent *eventp;
{
    XConfigureEvent *e = (XConfigureEvent *) eventp;

    printf ("    event 0x%lx, window 0x%lx, (%d,%d), width %d, height %d,\n",
	    e->event, e->window, e->x, e->y, e->width, e->height);
    printf ("    border_width %d, above 0x%lx, override %s\n",
	    e->border_width, e->above, e->override_redirect ? Yes : No);
    return;
}

static void do_ConfigureRequest (eventp)
    XEvent *eventp;
{
    XConfigureRequestEvent *e = (XConfigureRequestEvent *) eventp;
    char *detail;
    char ddummy[10];

    switch (e->detail) {
      case Above:  detail = "Above";  break;
      case Below:  detail = "Below";  break;
      case TopIf:  detail = "TopIf";  break;
      case BottomIf:  detail = "BottomIf"; break;
      case Opposite:  detail = "Opposite"; break;
      default:  detail = ddummy; sprintf (ddummy, "%d", e->detail); break;
    }

    printf ("    parent 0x%lx, window 0x%lx, (%d,%d), width %d, height %d,\n",
	    e->parent, e->window, e->x, e->y, e->width, e->height);
    printf ("    border_width %d, above 0x%lx, detail %s, value 0x%lx\n",
	    e->border_width, e->above, detail, e->value_mask);
    return;
}

static void do_GravityNotify (eventp)
    XEvent *eventp;
{
    XGravityEvent *e = (XGravityEvent *) eventp;

    printf ("    event 0x%lx, window 0x%lx, (%d,%d)\n",
	    e->event, e->window, e->x, e->y);
    return;
}

static void do_ResizeRequest (eventp)
    XEvent *eventp;
{
    XResizeRequestEvent *e = (XResizeRequestEvent *) eventp;

    printf ("    width %d, height %d\n", e->width, e->height);
    return;
}

static void do_CirculateNotify (eventp)
    XEvent *eventp;
{
    XCirculateEvent *e = (XCirculateEvent *) eventp;
    char *p;
    char pdummy[10];

    switch (e->place) {
      case PlaceOnTop:  p = "PlaceOnTop"; break;
      case PlaceOnBottom:  p = "PlaceOnBottom"; break;
      default:  p = pdummy; sprintf (pdummy, "%d", e->place); break;
    }

    printf ("    event 0x%lx, window 0x%lx, place %s\n",
	    e->event, e->window, p);
    return;
}

static void do_CirculateRequest (eventp)
    XEvent *eventp;
{
    XCirculateRequestEvent *e = (XCirculateRequestEvent *) eventp;
    char *p;
    char pdummy[10];

    switch (e->place) {
      case PlaceOnTop:  p = "PlaceOnTop"; break;
      case PlaceOnBottom:  p = "PlaceOnBottom"; break;
      default:  p = pdummy; sprintf (pdummy, "%d", e->place); break;
    }

    printf ("    parent 0x%lx, window 0x%lx, place %s\n",
	    e->parent, e->window, p);
    return;
}

static void do_PropertyNotify (eventp)
    XEvent *eventp;
{
    XPropertyEvent *e = (XPropertyEvent *) eventp;
    char *aname = XGetAtomName (dpy, e->atom);
    char *s;
    char sdummy[10];

    switch (e->state) {
      case PropertyNewValue:  s = "PropertyNewValue"; break;
      case PropertyDelete:  s = "PropertyDelete"; break;
      default:  s = sdummy; sprintf (sdummy, "%d", e->state); break;
    }

    printf ("    atom 0x%lx (%s), time %lu, state %s\n",
	   e->atom, aname ? aname : Unknown, e->time,  s);

    if (aname) XFree (aname);
    return;
}

static void do_SelectionClear (eventp)
    XEvent *eventp;
{
    XSelectionClearEvent *e = (XSelectionClearEvent *) eventp;
    char *sname = XGetAtomName (dpy, e->selection);

    printf ("    selection 0x%lx (%s), time %lu\n",
	    e->selection, sname ? sname : Unknown, e->time);

    if (sname) XFree (sname);
    return;
}

static void do_SelectionRequest (eventp)
    XEvent *eventp;
{
    XSelectionRequestEvent *e = (XSelectionRequestEvent *) eventp;
    char *sname = XGetAtomName (dpy, e->selection);
    char *tname = XGetAtomName (dpy, e->target);
    char *pname = XGetAtomName (dpy, e->property);

    printf ("    owner 0x%lx, requestor 0x%lx, selection 0x%lx (%s),\n",
	    e->owner, e->requestor, e->selection, sname ? sname : Unknown);
    printf ("    target 0x%lx (%s), property 0x%lx (%s), time %lu\n",
	    e->target, tname ? tname : Unknown, e->property,
	    pname ? pname : Unknown, e->time);

    if (sname) XFree (sname);
    if (tname) XFree (tname);
    if (pname) XFree (pname);

    return;
}

static void do_SelectionNotify (eventp)
    XEvent *eventp;
{
    XSelectionEvent *e = (XSelectionEvent *) eventp;
    char *sname = XGetAtomName (dpy, e->selection);
    char *tname = XGetAtomName (dpy, e->target);
    char *pname = XGetAtomName (dpy, e->property);

    printf ("    selection 0x%lx (%s), target 0x%lx (%s),\n",
	    e->selection, sname ? sname : Unknown, e->target,
	    tname ? tname : Unknown);
    printf ("    property 0x%lx (%s), time %lu\n",
	    e->property, pname ? pname : Unknown, e->time);

    if (sname) XFree (sname);
    if (tname) XFree (tname);
    if (pname) XFree (pname);

    return;
}

static void do_ColormapNotify (eventp)
    XEvent *eventp;
{
    XColormapEvent *e = (XColormapEvent *) eventp;
    char *s;
    char sdummy[10];

    switch (e->state) {
      case ColormapInstalled:  s = "ColormapInstalled"; break;
      case ColormapUninstalled:  s = "ColormapUninstalled"; break;
      default:  s = sdummy; sprintf (sdummy, "%d", e->state); break;
    }

    printf ("    colormap 0x%lx, new %s, state %s\n",
	    e->colormap, e->new ? Yes : No, s);
    return;
}

static void do_ClientMessage (eventp)
    XEvent *eventp;
{
    XClientMessageEvent *e = (XClientMessageEvent *) eventp;
    char *mname = XGetAtomName (dpy, e->message_type);

    printf ("    message_type 0x%lx (%s), format %d\n",
	    e->message_type, mname ? mname : Unknown, e->format);

    if (mname) XFree (mname);
    return;
}

static void do_MappingNotify (eventp)
    XEvent *eventp;
{
    XMappingEvent *e = (XMappingEvent *) eventp;
    char *r;
    char rdummy[10];

    switch (e->request) {
      case MappingModifier:  r = "MappingModifier"; break;
      case MappingKeyboard:  r = "MappingKeyboard"; break;
      case MappingPointer:  r = "MappingPointer"; break;
      default:  r = rdummy; sprintf (rdummy, "%d", e->request); break;
    }

    printf ("    request %s, first_keycode %d, count %d\n",
	    r, e->first_keycode, e->count);
    return;
}

void debugMainLoop(XtAppContext app_context)
{
  XEvent event;

  dpy = XtDisplay(topLevel);
  (void *) XSynchronize(XtDisplay(topLevel), TRUE); 

  for (;;) {
    XtAppNextEvent(app_context, &event);

    switch (event.type) {
    case KeyPress:
      prologue (&event, "KeyPress");
      do_KeyPress (&event);
      break;
    case KeyRelease:
      prologue (&event, "KeyRelease");
      do_KeyRelease (&event);
      break;
    case ButtonPress:
      prologue (&event, "ButtonPress");
      do_ButtonPress (&event);
      break;
    case ButtonRelease:
      prologue (&event, "ButtonRelease");
      do_ButtonRelease (&event);
      break;
    case MotionNotify:
      prologue (&event, "MotionNotify");
      do_MotionNotify (&event);
      break;
    case EnterNotify:
      prologue (&event, "EnterNotify");
      do_EnterNotify (&event);
      break;
    case LeaveNotify:
      prologue (&event, "LeaveNotify");
      do_LeaveNotify (&event);
      break;
    case FocusIn:
      prologue (&event, "FocusIn");
      do_FocusIn (&event);
      break;
    case FocusOut:
      prologue (&event, "FocusOut");
      do_FocusOut (&event);
      break;
    case KeymapNotify:
      prologue (&event, "KeymapNotify");
      do_KeymapNotify (&event);
      break;
    case Expose:
      prologue (&event, "Expose");
      do_Expose (&event);
      break;
    case GraphicsExpose:
      prologue (&event, "GraphicsExpose");
      do_GraphicsExpose (&event);
      break;
    case NoExpose:
      prologue (&event, "NoExpose");
      do_NoExpose (&event);
      break;
    case VisibilityNotify:
      prologue (&event, "VisibilityNotify");
      do_VisibilityNotify (&event);
      break;
    case CreateNotify:
      prologue (&event, "CreateNotify");
      do_CreateNotify (&event);
      break;
    case DestroyNotify:
      prologue (&event, "DestroyNotify");
      do_DestroyNotify (&event);
      break;
    case UnmapNotify:
      prologue (&event, "UnmapNotify");
      do_UnmapNotify (&event);
      break;
    case MapNotify:
      prologue (&event, "MapNotify");
      do_MapNotify (&event);
      break;
    case MapRequest:
      prologue (&event, "MapRequest");
      do_MapRequest (&event);
      break;
    case ReparentNotify:
      prologue (&event, "ReparentNotify");
      do_ReparentNotify (&event);
      break;
    case ConfigureNotify:
      prologue (&event, "ConfigureNotify");
      do_ConfigureNotify (&event);
      break;
    case ConfigureRequest:
      prologue (&event, "ConfigureRequest");
      do_ConfigureRequest (&event);
      break;
    case GravityNotify:
      prologue (&event, "GravityNotify");
      do_GravityNotify (&event);
      break;
    case ResizeRequest:
      prologue (&event, "ResizeRequest");
      do_ResizeRequest (&event);
      break;
    case CirculateNotify:
      prologue (&event, "CirculateNotify");
      do_CirculateNotify (&event);
      break;
    case CirculateRequest:
      prologue (&event, "CirculateRequest");
      do_CirculateRequest (&event);
      break;
    case PropertyNotify:
      prologue (&event, "PropertyNotify");
      do_PropertyNotify (&event);
      break;
    case SelectionClear:
      prologue (&event, "SelectionClear");
      do_SelectionClear (&event);
      break;
    case SelectionRequest:
      prologue (&event, "SelectionRequest");
      do_SelectionRequest (&event);
      break;
    case SelectionNotify:
      prologue (&event, "SelectionNotify");
      do_SelectionNotify (&event);
      break;
    case ColormapNotify:
      prologue (&event, "ColormapNotify");
      do_ColormapNotify (&event);
      break;
    case ClientMessage:
      prologue (&event, "ClientMessage");
      do_ClientMessage (&event);
      break;
    case MappingNotify:
      prologue (&event, "MappingNotify");
      do_MappingNotify (&event);
      break;
    default:
      printf ("Unknown event type %d\n", event.type);
      break;
    }

    XtDispatchEvent(&event);
  }
}

/* end of file DEBUGMAINLOOP.C */
