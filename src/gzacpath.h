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

/*$Id: gzacpath.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* State and interface definitions for clipping path accumulator */
/* Requires gxdevice.h, gzcpath.h */

#ifndef gzacpath_INCLUDED
#  define gzacpath_INCLUDED

/*
 * Device for accumulating a rectangle list.  This device can clip
 * the list being accumulated with a clipping rectangle on the fly:
 * we use this to clip clipping paths to band boundaries when
 * rendering a band list.
 */
typedef struct gx_device_cpath_accum_s {
    gx_device_common;
    gs_memory_t *list_memory;
    gs_int_rect clip_box;
    gs_int_rect bbox;
    gx_clip_list list;
} gx_device_cpath_accum;

/* Start accumulating a clipping path. */
void gx_cpath_accum_begin(P2(gx_device_cpath_accum * padev, gs_memory_t * mem));

/* Set the accumulator's clipping box. */
void gx_cpath_accum_set_cbox(P2(gx_device_cpath_accum * padev,
				const gs_fixed_rect * pbox));

/* Finish accumulating a clipping path. */
/* Note that this releases the old contents of the clipping path. */
int gx_cpath_accum_end(P2(const gx_device_cpath_accum * padev,
			  gx_clip_path * pcpath));

/* Discard an accumulator in case of error. */
void gx_cpath_accum_discard(P1(gx_device_cpath_accum * padev));

#endif /* gzacpath_INCLUDED */
