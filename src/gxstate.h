/* Copyright (C) 1996 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxstate.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Internal graphics state API */

#ifndef gxstate_INCLUDED
#  define gxstate_INCLUDED

/* Opaque type for a graphics state */
#ifndef gs_state_DEFINED
#  define gs_state_DEFINED
typedef struct gs_state_s gs_state;

#endif

/*
 * The interfaces in this file are for internal use only, primarily by the
 * interpreter.  They are not guaranteed to remain stable from one release
 * to another.
 */

/* Memory and save/restore management */
gs_memory_t *gs_state_memory(P1(const gs_state *));
gs_state *gs_state_saved(P1(const gs_state *));
gs_state *gs_state_swap_saved(P2(gs_state *, gs_state *));
gs_memory_t *gs_state_swap_memory(P2(gs_state *, gs_memory_t *));

/*
 * "Client data" interface for graphics states.
 *
 * As of release 4.36, the copy procedure is superseded by copy_for
 * (although it will still be called if there is no copy_for procedure).
 */
typedef void *(*gs_state_alloc_proc_t) (P1(gs_memory_t * mem));
typedef int (*gs_state_copy_proc_t) (P2(void *to, const void *from));
typedef void (*gs_state_free_proc_t) (P2(void *old, gs_memory_t * mem));
typedef enum {
    copy_for_gsave,		/* from = current, to = new(saved) */
    copy_for_grestore,		/* from = saved, to = current */
    copy_for_gstate,		/* from = current, to = new(copy) */
    copy_for_setgstate,		/* from = stored, to = current */
    copy_for_copygstate,	/* from & to are specified explicitly */
    copy_for_currentgstate	/* from = current, to = stored */
} gs_state_copy_reason_t;

/* Note that the 'from' argument of copy_for is not const. */
/* This is deliberate -- some clients need this. */
typedef int (*gs_state_copy_for_proc_t) (P3(void *to, void *from,
					    gs_state_copy_reason_t reason));
typedef struct gs_state_client_procs_s {
    gs_state_alloc_proc_t alloc;
    gs_state_copy_proc_t copy;
    gs_state_free_proc_t free;
    gs_state_copy_for_proc_t copy_for;
} gs_state_client_procs;
void gs_state_set_client(P3(gs_state *, void *, const gs_state_client_procs *));

/* gzstate.h redefines the following: */
#ifndef gs_state_client_data
void *gs_state_client_data(P1(const gs_state *));

#endif

#endif /* gxstate_INCLUDED */
