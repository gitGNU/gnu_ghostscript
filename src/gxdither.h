/* Copyright (C) 1994, 1995, 1996, 1997, 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gxdither.h,v 1.2 2004/02/14 22:20:18 atai Exp $ */
/* Interface to gxdither.c */

#ifndef gxdither_INCLUDED
#  define gxdither_INCLUDED

#include "gxfrac.h"

#ifndef gx_device_halftone_DEFINED
#  define gx_device_halftone_DEFINED
typedef struct gx_device_halftone_s gx_device_halftone;
#endif

/*
 * Render DeviceN possibly by halftoning.
 *  pcolors = pointer to an array color values (as fracs)
 *  pdevc - pointer to device color structure
 *  dev = pointer to device data structure
 *  pht = pointer to halftone data structure
 *  ht_phase  = halftone phase
 *  gray_colorspace = true -> current color space is DeviceGray.
 *  This is part of a kludge to minimize differences in the
 *  regression testing.
 */
int gx_render_device_DeviceN(frac * pcolor, gx_device_color * pdevc,
	gx_device * dev, gx_device_halftone * pdht,
	const gs_int_point * ht_phase, bool gray_colorspace);
/*
 * Reduce a colored halftone with 0 or 1 varying plane(s) to a pure color
 * or a binary halftone.
 */
int gx_devn_reduce_colored_halftone(gx_device_color *pdevc, gx_device *dev);

#endif /* gxdither_INCLUDED */
