/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gxpcache.h,v 1.2 2004/02/14 22:20:18 atai Exp $ */
/* Definition of Pattern cache */

#ifndef gxpcache_INCLUDED
#  define gxpcache_INCLUDED

/*
 * Define a cache for rendered Patterns.  This is currently an open
 * hash table with single probing (no reprobing) and round-robin
 * replacement.  Obviously, we can do better in both areas.
 */
#ifndef gx_pattern_cache_DEFINED
#  define gx_pattern_cache_DEFINED
typedef struct gx_pattern_cache_s gx_pattern_cache;

#endif
#ifndef gx_color_tile_DEFINED
#  define gx_color_tile_DEFINED
typedef struct gx_color_tile_s gx_color_tile;

#endif
struct gx_pattern_cache_s {
    gs_memory_t *memory;
    gx_color_tile *tiles;
    uint num_tiles;
    uint tiles_used;
    uint next;			/* round-robin index */
    ulong bits_used;
    ulong max_bits;
    void (*free_all) (gx_pattern_cache *);
};

#define private_st_pattern_cache() /* in gxpcmap.c */\
  gs_private_st_ptrs1(st_pattern_cache, gx_pattern_cache,\
    "gx_pattern_cache", pattern_cache_enum, pattern_cache_reloc, tiles)

#endif /* gxpcache_INCLUDED */
