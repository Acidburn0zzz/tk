/*
 * tkSDLPort.h --
 *
 *	This file is included by all of the Tk C files.  It contains
 *	information that may be configuration-dependent, such as
 *	#includes for system include files and a few other things.
 *
 * Copyright (c) 1991-1993 The Regents of the University of California.
 * Copyright (c) 1994-1996 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 */

#ifndef _TKSDLPORT
#define _TKSDLPORT

#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#ifndef _WIN32
#include <pwd.h>
#endif
#ifdef NO_STDLIB_H
#   include "../compat/stdlib.h"
#else
#   include <stdlib.h>
#endif
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>
#ifdef HAVE_SYS_SELECT_H
#   include <sys/select.h>
#endif
#include <sys/stat.h>
#ifndef _TCL
#   include <tcl.h>
#endif
#if TIME_WITH_SYS_TIME
#   include <sys/time.h>
#   include <time.h>
#else
#   if HAVE_SYS_TIME_H
#       include <sys/time.h>
#   else
#       include <time.h>
#   endif
#endif
#if HAVE_INTTYPES_H
#    include <inttypes.h>
#endif
#ifndef NO_UNISTD_H
#   include <unistd.h>
#else
#   include "../compat/unistd.h"
#endif
#ifdef TK_USE_POLL
#   include <poll.h>
#endif
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

/*
 * The following macro defines the type of the mask arguments to
 * select:
 */

#ifndef NO_FD_SET
#   define SELECT_MASK fd_set
#   ifdef ANDROID
	typedef long fd_mask;
#   endif
#else
#   ifndef _AIX
	typedef long fd_mask;
#   endif
#   if defined(_IBMR2)
#	define SELECT_MASK void
#   else
#	define SELECT_MASK int
#   endif
#endif

/*
 * The following macro defines the number of fd_masks in an fd_set:
 */

#ifndef FD_SETSIZE
#   ifdef OPEN_MAX
#	define FD_SETSIZE OPEN_MAX
#   else
#	define FD_SETSIZE 256
#   endif
#endif
#if !defined(howmany)
#   define howmany(x, y) (((x)+((y)-1))/(y))
#endif
#ifndef NFDBITS
#   define NFDBITS NBBY*sizeof(fd_mask)
#endif
#define MASK_SIZE howmany(FD_SETSIZE, NFDBITS)

/*
 * Define "NBBY" (number of bits per byte) if it's not already defined.
 */

#ifndef NBBY
#   define NBBY 8
#endif

#ifdef __CYGWIN__
#   include "tkIntXlibDecls.h"
#   define UINT unsigned int
#   define HWND void *
#   define HDC void *
#   define HINSTANCE void *
#   define COLORREF void *
#   define HMENU void *
#   define TkWinDCState void
#   define HPALETTE void *
#   define WNDPROC void *
#   define WPARAM void *
#   define LPARAM void *
#   define LRESULT void *
#endif /* __CYGWIN__ */

/*
 * Supply macros for seek offsets, if they're not already provided by
 * an include file.
 */

#ifndef SEEK_SET
#   define SEEK_SET 0
#endif

#ifndef SEEK_CUR
#   define SEEK_CUR 1
#endif

#ifndef SEEK_END
#   define SEEK_END 2
#endif

/*
 * Declarations for various library procedures that may not be declared
 * in any other header file.
 */


/*
 * These functions do nothing under Unix, so we just eliminate calls to them.
 */

#define TkpButtonSetDefaults() {}
#define TkpDestroyButton(butPtr) {}
#ifndef __CYGWIN__
#define TkSetPixmapColormap(p,c) {}
#endif

/*
 * These calls implement native bitmaps which are not supported under
 * UNIX.  The macros eliminate the calls.
 */

#define TkpDefineNativeBitmaps()
#define TkpCreateNativeBitmap(display, source) None
#define TkpGetNativeAppBitmap(display, name, w, h) None

/*
 * Get keysyms like Windows does
 */
#define REDO_KEYSYM_LOOKUP

/*
 * This macro stores a representation of the window handle in a string.
 * This should perhaps use the real size of an XID.
 */

#ifndef __CYGWIN__
#define TkpPrintWindowId(buf,w) \
	sprintf((buf), "%#08lx", (unsigned long) (w))
#endif

extern unsigned long TkpGetPixel(XColor *);

#endif /* _TKSDLPORT */