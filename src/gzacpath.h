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

/* $Id: gzacpath.h,v 1.2 2004/02/14 22:20:18 atai Exp $ */
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

#endif /* gzacpath_INCLUDED */
