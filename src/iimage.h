/* Copyright (C) 1996, 1997, 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: iimage.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* Image operator entry points */
/* Requires gscspace.h, gxiparam.h */

#ifndef iimage_INCLUDED
#  define iimage_INCLUDED

/* These procedures are exported by zimage.c for other modules. */

/*
 * Define a structure for image parameters other than those defined
 * in the gs_*image*_t structure.
 */
typedef struct image_params_s {
    bool MultipleDataSources;
    ref DataSource[gs_image_max_components];
    const float *pDecode;
} image_params;

/* Extract and check parameters for an image. */
int data_image_params(const ref *op, gs_data_image_t *pim,
                      image_params *pip, bool require_DataSource,
                      int num_components, int max_bits_per_component,
                      bool has_alpha);
int pixel_image_params(i_ctx_t *i_ctx_p, const ref *op,
                       gs_pixel_image_t *pim, image_params * pip,
                       int max_bits_per_component, bool has_alpha);

/* Exported for zimage3.c and ztrans.c */
int zimage_setup(i_ctx_t *i_ctx_p, const gs_pixel_image_t * pim,
                 const ref * sources, bool uses_color, int npop);

/* Exported for zdpnext.c */
int image1_setup(i_ctx_t * i_ctx_p, bool has_alpha);

#endif /* iimage_INCLUDED */
