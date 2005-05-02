/* Copyright (C) 1995, 1996 Aladdin Enterprises.  All rights reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free Software
  Foundation; either version 2, or (at your option) any later version.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gzacpath.h,v 1.4 2005/05/02 00:03:35 Arabidopsis Exp $ */
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
void gx_cpath_accum_begin(gx_device_cpath_accum * padev, gs_memory_t * mem);

/* Set the accumulator's clipping box. */
void gx_cpath_accum_set_cbox(gx_device_cpath_accum * padev,
			     const gs_fixed_rect * pbox);

/* Finish accumulating a clipping path. */
/* Note that this releases the old contents of the clipping path. */
int gx_cpath_accum_end(const gx_device_cpath_accum * padev,
		       gx_clip_path * pcpath);

/* Discard an accumulator in case of error. */
void gx_cpath_accum_discard(gx_device_cpath_accum * padev);

/* Intersect two clipping paths using an accumulator. */
int gx_cpath_intersect_path_slow(gx_clip_path *, gx_path *, int,
					gs_imager_state *);

#endif /* gzacpath_INCLUDED */
