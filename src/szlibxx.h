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

/*$Id: szlibxx.h,v 1.1 2004/01/14 16:59:53 atai Exp $ */
/* Implementation definitions for zlib interface */
/* Must be compiled with -I$(ZSRCDIR) */

#ifndef szlibxx_INCLUDED
#  define szlibxx_INCLUDED

#include "szlibx.h"
#include "zlib.h"

/*
 * We don't want to allocate zlib's private data directly from
 * the C heap, but we must allocate it as immovable; and to avoid
 * garbage collection issues, we must keep GC-traceable pointers
 * to every block allocated.  Since the stream state itself is movable,
 * we have to allocate an immovable block for the z_stream state as well.
 */
typedef struct zlib_block_s zlib_block_t;
struct zlib_block_s {
    void *data;
    zlib_block_t *next;
    zlib_block_t *prev;
};
#define private_st_zlib_block()	/* in szlibc.c */\
  gs_private_st_ptrs3(st_zlib_block, zlib_block_t, "zlib_block_t",\
    zlib_block_enum_ptrs, zlib_block_reloc_ptrs, next, prev, data)
/* The typedef is in szlibx.h */
/*typedef*/ struct zlib_dynamic_state_s {
    gs_memory_t *memory;
    zlib_block_t *blocks;
    z_stream zstate;
} /*zlib_dynamic_state_t*/;
#define private_st_zlib_dynamic_state()	/* in szlibc.c */\
  gs_private_st_ptrs1(st_zlib_dynamic_state, zlib_dynamic_state_t,\
    "zlib_dynamic_state_t", zlib_dynamic_enum_ptrs, zlib_dynamic_reloc_ptrs,\
    blocks)

/*
 * Provide zlib-compatible allocation and freeing functions.
 * The mem pointer actually points to the dynamic state.
 */
void *s_zlib_alloc(P3(void *mem, uint items, uint size));
void s_zlib_free(P2(void *mem, void *address));

/* Internal procedure to allocate and free the dynamic state. */
int s_zlib_alloc_dynamic_state(P1(stream_zlib_state *ss));
void s_zlib_free_dynamic_state(P1(stream_zlib_state *ss));

#endif /* szlibxx_INCLUDED */
