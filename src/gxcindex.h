/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
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

/* $Id: gxcindex.h,v 1.6 2007/05/07 11:21:44 Arabidopsis Exp $ */
/* Define the device color index type and macros */

#ifndef gxcindex_INCLUDED
#  define gxcindex_INCLUDED

#include "gsbitops.h"		/* for sample_store macros */

/*
 * Define the maximum number of components in a device color.
 * The minimum value is 4, to handle CMYK; the maximum value is
 * arch_sizeof_color_index * 8, since for larger values, there aren't enough
 * bits in a gx_color_index to have even 1 bit per component.
 */
#define GX_DEVICE_COLOR_MAX_COMPONENTS (ARCH_SIZEOF_GX_COLOR_INDEX * 8)

/*
 * We might change gx_color_index to a pointer or a structure in the
 * future.  These disabled options help us assess how much disruption
 * such a change might cause.
 */
/*#define TEST_CINDEX_POINTER*/
/*#define TEST_CINDEX_STRUCT*/

/*
 * Internally, a (pure) device color is represented by opaque values of
 * type gx_color_index, which are tied to the specific device.  The driver
 * maps between these values and RGB[alpha] or CMYK values.  In this way,
 * the driver can convert RGB values to its most natural color representation,
 * and have the graphics library cache the result.
 */

#ifdef TEST_CINDEX_STRUCT

/* Define the type for device color index (pixel value) data. */
typedef struct { ulong value[2]; } gx_color_index_data;

#else  /* !TEST_CINDEX_STRUCT */

/* Define the type for device color index (pixel value) data. */
#ifdef GX_COLOR_INDEX_TYPE
typedef GX_COLOR_INDEX_TYPE gx_color_index_data;
#else
/* this default must be kept in sync with the one in genarch.c
   or ARCH_SIZEOF_GX_COLOR_INDEX will be incorrect */
typedef ulong gx_color_index_data;
#endif

#endif /* (!)TEST_CINDEX_STRUCT */

#ifdef TEST_CINDEX_POINTER

/* Define the type for device color indices (pixel values). */
typedef gx_color_index_data * gx_color_index;
#define arch_sizeof_color_index arch_sizeof_ptr

extern const gx_color_index_data gx_no_color_index_data;
#define gx_no_color_index_values (&gx_no_color_index_data)
#define gx_no_color_index (&gx_no_color_index_data)

#else  /* !TEST_CINDEX_POINTER */

#define arch_sizeof_color_index sizeof(gx_color_index_data)

/* Define the type for device color indices (pixel values). */
typedef gx_color_index_data gx_color_index;

/*
 * Define the 'transparent' or 'undefined' color index.
 */
#define gx_no_color_index_value (~0)	/* no cast -> can be used in #if */
/*
 * There was a comment here about the SGI C compiler provided with Irix 5.2
 * giving error messages.  I hope that was fixed when the value of gx_no_color_index
 * was changed from (-1) to (~0).  If not then let us know.
 */
#define gx_no_color_index ((gx_color_index)gx_no_color_index_value)

#endif /* (!)TEST_CINDEX_POINTER */

/*
 * Define macros for accumulating a scan line of a colored image.
 * The usage is as follows:
 *	DECLARE_LINE_ACCUM(line, bpp, xo);
 *	for ( x = xo; x < xe; ++x ) {
 *	    << compute color at x >>
 *          LINE_ACCUM(color, bpp);
 *      }
 * This code must be enclosed in { }, since DECLARE_LINE_ACCUM declares
 * variables.  Supported values of bpp are 1, 2, 4, or n * 8, where n <= 8.
 *
 * Note that DECLARE_LINE_ACCUM declares the variables l_dptr, l_dbyte, and
 * l_dbit.  Other code in the loop may use these variables.
 */
#define DECLARE_LINE_ACCUM(line, bpp, xo)\
	sample_store_declare_setup(l_dptr, l_dbit, l_dbyte, line, 0, bpp)
#define LINE_ACCUM(color, bpp)\
	sample_store_next_any(color, l_dptr, l_dbit, bpp, l_dbyte)
#define LINE_ACCUM_SKIP(bpp)\
	sample_store_skip_next(l_dptr, l_dbit, bpp, l_dbyte)
#define LINE_ACCUM_STORE(bpp)\
	sample_store_flush(l_dptr, l_dbit, bpp, l_dbyte)
/*
 * Declare additional macros for accumulating a scan line with copying
 * to a device.  Note that DECLARE_LINE_ACCUM_COPY also declares l_xprev.
 * LINE_ACCUM_COPY is called after the accumulation loop.
 */
#define DECLARE_LINE_ACCUM_COPY(line, bpp, xo)\
	DECLARE_LINE_ACCUM(line, bpp, xo);\
	int l_xprev = (xo)
#define LINE_ACCUM_COPY(dev, line, bpp, xo, xe, raster, y)\
	if ( (xe) > l_xprev ) {\
	    int code;\
	    LINE_ACCUM_STORE(bpp);\
	    code = (*dev_proc(dev, copy_color))\
	      (dev, line, l_xprev - (xo), raster,\
	       gx_no_bitmap_id, l_xprev, y, (xe) - l_xprev, 1);\
	    if ( code < 0 )\
	      return code;\
	}

#endif /* gxcindex_INCLUDED */
