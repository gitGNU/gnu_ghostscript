/* Copyright (C) 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 2
  as published by the Free Software Foundation.


  This software is provided AS-IS with no warranty, either express or
  implied. That is, this program is distributed in the hope that it will 
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.
  
  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gsmemlok.h,v 1.2 2004/02/14 22:20:17 atai Exp $ */
/* Interface to monitor-locked heap memory allocator */

/* Initial version 2/1/98 by John Desrosiers (soho@crl.com) */

#if !defined(gsmemlok_INCLUDED)
#  define gsmemlok_INCLUDED

#include "gsmemory.h"
#include "gxsync.h"

/*
 * This allocator encapsulates another allocator with a mutex.
 * Note that it does not keep track of memory that it acquires:
 * thus free_all with FREE_ALL_DATA is a no-op.
 */

typedef struct gs_memory_locked_s {
    gs_memory_common;		/* interface outside world sees */
    gs_memory_t *target;	/* allocator to front */
    gx_monitor_t *monitor;	/* monitor to serialize access to functions */
} gs_memory_locked_t;

/* ---------- Public constructors/destructors ---------- */

/* Initialize a locked memory manager. */
int gs_memory_locked_init(
			  gs_memory_locked_t * lmem,	/* allocator to init */
			  gs_memory_t * target	/* allocator to monitor lock */
			  );

/* Release a locked memory manager. */
/* Note that this has no effect on the target. */
void gs_memory_locked_release(gs_memory_locked_t *lmem);

/* Get the target of a locked memory manager. */
gs_memory_t * gs_memory_locked_target(const gs_memory_locked_t *lmem);

#endif /*!defined(gsmemlok_INCLUDED) */
