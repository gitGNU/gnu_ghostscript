/* Copyright (C) 1997 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxcomp.h,v 1.1 2004/01/14 16:59:51 atai Exp $ */
/* Definitions for implementing compositing functions */

#ifndef gxcomp_INCLUDED
#  define gxcomp_INCLUDED

#include "gscompt.h"
#include "gsrefct.h"
#include "gxbitfmt.h"

/*
 * Define the abstract superclass for all compositing function types.
 */
						   /*typedef struct gs_composite_s gs_composite_t; *//* in gscompt.h */

#ifndef gs_imager_state_DEFINED
#  define gs_imager_state_DEFINED
typedef struct gs_imager_state_s gs_imager_state;

#endif

#ifndef gx_device_DEFINED
#  define gx_device_DEFINED
typedef struct gx_device_s gx_device;

#endif

typedef struct gs_composite_type_procs_s {

    /*
     * Create the default compositor for a compositing function.
     */
#define composite_create_default_compositor_proc(proc)\
  int proc(P5(const gs_composite_t *pcte, gx_device **pcdev,\
    gx_device *dev, const gs_imager_state *pis, gs_memory_t *mem))
    composite_create_default_compositor_proc((*create_default_compositor));

    /*
     * Test whether this function is equal to another one.
     */
#define composite_equal_proc(proc)\
  bool proc(P2(const gs_composite_t *pcte, const gs_composite_t *pcte2))
    composite_equal_proc((*equal));

    /*
     * Convert the representation of this function to a string
     * for writing in a command list.  *psize is the amount of space
     * available.  If it is large enough, the procedure sets *psize
     * to the amount used and returns 0; if it is not large enough,
     * the procedure sets *psize to the amount needed and returns a
     * rangecheck error; in the case of any other error, *psize is
     * not changed.
     */
#define composite_write_proc(proc)\
  int proc(P3(const gs_composite_t *pcte, byte *data, uint *psize))
    composite_write_proc((*write));

    /*
     * Convert the string representation of a function back to
     * a structure, allocating the structure.
     */
#define composite_read_proc(proc)\
  int proc(P4(gs_composite_t **ppcte, const byte *data, uint size,\
    gs_memory_t *mem))
    composite_read_proc((*read));

} gs_composite_type_procs_t;
typedef struct gs_composite_type_s {
    gs_composite_type_procs_t procs;
} gs_composite_type_t;

/*
 * Compositing objects are reference-counted, because graphics states will
 * eventually reference them.  Note that the common part has no
 * garbage-collectible pointers and is never actually instantiated, so no
 * structure type is needed for it.
 */
#define gs_composite_common\
	const gs_composite_type_t *type;\
	gs_id id;		/* see gscompt.h */\
	rc_header rc
struct gs_composite_s {
    gs_composite_common;
};

/* Replace a procedure with a macro. */
#define gs_composite_id(pcte) ((pcte)->id)

#endif /* gxcomp_INCLUDED */
