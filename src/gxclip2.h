/* Copyright (C) 1993, 1996, 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxclip2.h,v 1.1 2004/01/14 16:59:51 atai Exp $ */
/* Tiled mask clipping device and interface */

#ifndef gxclip2_INCLUDED
#  define gxclip2_INCLUDED

#include "gxmclip.h"

/* The structure for tile clipping is the same as for simple mask clipping. */
typedef gx_device_mask_clip gx_device_tile_clip;
#define st_device_tile_clip st_device_mask_clip
/*
 * We can't just make this macro empty, since it is processed as a top-level
 * declaration and would lead to an extraneous semicolon.  The least damage
 * we can do is make it declare a constant (and not static, since static
 * would lead to a compiler warning about an unreferenced variable).
 */
#define private_st_device_tile_clip() /* in gxclip2.c */\
  const byte gxclip2_dummy = 0

/*
 * Initialize a tile clipping device from a mask.
 * We supply an explicit phase.
 */
int tile_clip_initialize(P6(gx_device_tile_clip * cdev,
			    const gx_strip_bitmap * tiles,
			    gx_device * tdev, int px, int py,
			    gs_memory_t *mem));

/*
 * Set the phase of the tile -- used in the tiling loop when
 * the tile doesn't simply fill the plane.
 */
void tile_clip_set_phase(P3(gx_device_tile_clip * cdev, int px, int py));

#endif /* gxclip2_INCLUDED */
