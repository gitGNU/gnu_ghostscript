/* Copyright (C) 1995, 1998 artofcode LLC.  All rights reserved.
  
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

*/

/*$Id: gdevht.h,v 1.2 2005/05/02 00:03:33 Arabidopsis Exp $ */
/* Halftoning "device" definitions */
/* Requires gxdevice.h */

#ifndef gdevht_INCLUDED
#  define gdevht_INCLUDED

#include "gzht.h"

/*
 * A halftoning device converts between a non-halftoned device color space
 * (e.g., 8-bit gray) and a halftoned space (e.g., 1-bit black and white).
 * We represent colors by packing the two colors being halftoned and the
 * halftone level into a gx_color_index.
 */
typedef struct gx_device_ht_s {
    gx_device_forward_common;
    /* Following + target are set before opening. */
    const gx_device_halftone *dev_ht;
    gs_int_point ht_phase;	/* halftone phase from gstate */
    /* Following are computed when device is opened. */
    int color_shift;		/* # of bits of color */
    int level_shift;		/* = color_shift * 2 */
    gx_color_index color_mask;	/* (1 << color_shift) - 1 */
    gs_int_point phase;		/* halftone tile offset */
} gx_device_ht;

#endif /* gdevht_INCLUDED */
