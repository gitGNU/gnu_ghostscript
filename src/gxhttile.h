/* Copyright (C) 1995, 1996 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxhttile.h,v 1.1 2004/01/14 16:59:51 atai Exp $ */
/* Halftone tile definition */
/* Requires gxbitmap.h */

#ifndef gxhttile_INCLUDED
#  define gxhttile_INCLUDED

/*
 * A halftone tile is just an ordinary bitmap tile, plus a couple of other
 * items associated with managing its existence in a tile cache.
 * (See gzht.h for details.)  We define this in its own file so that
 * clients of gx_device_color can access it.
 */

#ifndef gx_ht_tile_DEFINED
#  define gx_ht_tile_DEFINED
typedef struct gx_ht_tile_s gx_ht_tile;

#endif

struct gx_ht_tile_s {
    gx_strip_bitmap tiles;	/* the currently rendered tile */
    int level;			/* the cached gray level, i.e. */
    /* the number of spots whitened, */
    /* or -1 if the cache is empty */
    uint index;			/* the index of the tile within */
    /* the cache (for GC) */
};

#endif /* gxhttile_INCLUDED */
