/* Copyright (C) 1998 artofcode LLC.  All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.

*/

/*$Id: gxsync.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Interface to synchronization primitives */

/* Initial version 2/1/98 by John Desrosiers (soho@crl.com) */

#if !defined(gxsync_INCLUDED)
#  define gxsync_INCLUDED

#include "gpsync.h"
#include "gsmemory.h"

/* This module abstracts the platform-specific synchronization primitives. */
/* Since these routines will see heavy use, performance is important. */

/* ----- Semaphore interface ----- */
/* These have the usual queued, counting semaphore semantics: at init time, */
/* the event count is set to 0 ('wait' will wait until 1st signal). */
typedef struct gx_semaphore_s {
    gs_memory_t *memory;	/* allocator to free memory */
    gp_semaphore native;	/* MUST BE LAST last since length is undef'd */
    /*  platform-dep impl, len is gp_semaphore_sizeof() */
} gx_semaphore_t;

gx_semaphore_t *		/* returns a new semaphore, 0 if error */
    gx_semaphore_alloc(P1(
			  gs_memory_t * memory	/* memory allocator to use */
			  ));
void
    gx_semaphore_free(P1(
			 gx_semaphore_t * sema	/* semaphore to delete */
			 ));

#define gx_semaphore_wait(sema)  gp_semaphore_wait(&(sema)->native)
#define gx_semaphore_signal(sema)  gp_semaphore_signal(&(sema)->native)


/* ----- Monitor interface ----- */
/* These have the usual monitor semantics: at init time, */
/* the event count is set to 1 (1st 'enter' succeeds immediately). */
typedef struct gx_monitor_s {
    gs_memory_t *memory;	/* allocator to free memory */
    gp_monitor native;		/* platform-dep impl, len is gp_monitor_sizeof() */
} gx_monitor_t;

gx_monitor_t *			/* returns a new monitor, 0 if error */
    gx_monitor_alloc(P1(
			gs_memory_t * memory	/* memory allocator to use */
			));
void
    gx_monitor_free(P1(
		       gx_monitor_t * mon	/* monitor to delete */
		       ));

#define gx_monitor_enter(sema)  gp_monitor_enter(&(sema)->native)
#define gx_monitor_leave(sema)  gp_monitor_leave(&(sema)->native)

#endif /* !defined(gxsync_INCLUDED) */
