/* Copyright (C) 1997, 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsiparm2.h,v 1.2 2004/02/14 22:20:17 atai Exp $ */
/* ImageType 2 image parameter definition */

#ifndef gsiparm2_INCLUDED
#  define gsiparm2_INCLUDED

#include "gsiparam.h"

/* Opaque type for a path */
#ifndef gx_path_DEFINED
#  define gx_path_DEFINED
typedef struct gx_path_s gx_path;
#endif

/*
 * See Section 7.1 of the Adobe PostScript Version 3010 Supplement
 * for a definition of ImageType 2 images.
 */

typedef struct gs_image2_s {
    gs_image_common;
    gs_state *DataSource;
    float XOrigin, YOrigin;
    float Width, Height;
    /*
     * If UnpaintedPath is not 0, any unpainted path will be appended to it.
     */
    gx_path *UnpaintedPath;
    bool PixelCopy;
} gs_image2_t;
#define private_st_gs_image2()	/* in gximage2.c */\
  extern_st(st_gs_image_common);\
  gs_private_st_suffix_add2(st_gs_image2, gs_image2_t, "gs_image2_t",\
    image2_enum_ptrs, image2_reloc_ptrs, st_gs_image_common,\
    DataSource, UnpaintedPath)

/*
 * Initialize an ImageType 2 image.  Defaults:
 *      UnpaintedPath = 0
 *      PixelCopy = false
 */
void gs_image2_t_init(gs_image2_t * pim);

#endif /* gsiparm2_INCLUDED */
