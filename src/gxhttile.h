/* Copyright (C) 1995, 1996 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gxhttile.h,v 1.2 2004/02/14 22:20:18 atai Exp $ */
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
