/* Copyright (C) 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsmemret.h,v 1.2 2004/02/14 22:20:17 atai Exp $ */
/* Interface to retrying memory allocator */

#if !defined(gsmemret_INCLUDED)
#  define gsmemret_INCLUDED

#include "gsmemory.h"

/*
 * This allocator encapsulates another allocator with a closure that is
 * called to attempt to free up memory if an allocation fails.
 * Note that it does not keep track of memory that it acquires:
 * thus free_all with FREE_ALL_DATA is a no-op.
 */
typedef struct gs_memory_retrying_s gs_memory_retrying_t;

/*
 * Define the procedure type for the recovery closure.
 */
typedef enum {
    RECOVER_STATUS_NO_RETRY,
    RECOVER_STATUS_RETRY_OK
} gs_memory_recover_status_t;
typedef gs_memory_recover_status_t (*gs_memory_recover_proc_t)
     (gs_memory_retrying_t *rmem, void *proc_data);

struct gs_memory_retrying_s {
    gs_memory_common;		/* interface outside world sees */
    gs_memory_t *target;	/* allocator to front */
    gs_memory_recover_proc_t recover_proc;
    void *recover_proc_data;
};

/* ---------- Public constructors/destructors ---------- */

/* Initialize a retrying memory manager. */
int gs_memory_retrying_init(
			    gs_memory_retrying_t * rmem, /* allocator to init */
			    gs_memory_t * target	/* allocator to wrap */
			    );

/* Release a retrying memory manager. */
/* Note that this has no effect on the target. */
void gs_memory_retrying_release(gs_memory_retrying_t *rmem);

/* Set the recovery closure of a retrying memory manager. */
void gs_memory_retrying_set_recover(gs_memory_retrying_t *rmem,
				    gs_memory_recover_proc_t recover_proc,
				    void *recover_proc_data);

/* Get the target of a retrying memory manager. */
gs_memory_t * gs_memory_retrying_target(const gs_memory_retrying_t *rmem);

#endif /*!defined(gsmemret_INCLUDED) */
