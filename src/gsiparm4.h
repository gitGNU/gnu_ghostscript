/* Copyright (C) 1997, 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsiparm4.h,v 1.2 2004/02/14 22:20:17 atai Exp $ */
/* ImageType 4 image parameter definition */

#ifndef gsiparm4_INCLUDED
#  define gsiparm4_INCLUDED

#include "gsiparam.h"

/*
 * See Section 4.3 of the Adobe PostScript Version 3010 Supplement
 * for a definition of ImageType 4 images.
 */

typedef struct gs_image4_s {
    gs_pixel_image_common;
    /*
     * If MaskColor_is_range is false, the first N elements of
     * MaskColor are sample values; if MaskColor_is_range is true,
     * the first 2*N elements are ranges of sample values.
     *
     * Currently, the largest sample values supported by the library are 12
     * bits, but eventually we want to support DevicePixel images with
     * samples up to 32 bits as well.
     */
    bool MaskColor_is_range;
    uint MaskColor[GS_IMAGE_MAX_COMPONENTS * 2];
} gs_image4_t;

#define private_st_gs_image4()	/* in gximage4.c */\
  extern_st(st_gs_pixel_image);\
  gs_private_st_suffix_add0(st_gs_image4, gs_image4_t, "gs_image4_t",\
    image4_enum_ptrs, image4_reloc_ptrs, st_gs_pixel_image)

/*
 * Initialize an ImageType 4 image.  Defaults:
 *      MaskColor_is_range = false
 */
void gs_image4_t_init(gs_image4_t * pim, const gs_color_space * color_space);

#endif /* gsiparm4_INCLUDED */
