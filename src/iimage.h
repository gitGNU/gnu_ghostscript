/* Copyright (C) 1996, 1997, 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: iimage.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Image operator entry points */
/* Requires gscspace.h, gxiparam.h */

#ifndef iimage_INCLUDED
#  define iimage_INCLUDED

/* These procedures are exported by zimage.c for other modules. */

/* Exported for zcolor1.c */
int zimage_opaque_setup(P6(i_ctx_t *i_ctx_p, os_ptr op, bool multi,
			   gs_image_alpha_t alpha, const gs_color_space * pcs,
			   int npop));

/* Exported for zimage2.c */
int zimage_setup(P5(i_ctx_t *i_ctx_p, const gs_pixel_image_t * pim,
		    const ref * sources, bool uses_color, int npop));

/* Exported for zcolor3.c */
int zimage_data_setup(P5(i_ctx_t *i_ctx_p, const gs_pixel_image_t * pim,
			 gx_image_enum_common_t * pie,
			 const ref * sources, int npop));

/* Exported for zcolor1.c and zdpnext.c. */
int zimage_multiple(P2(i_ctx_t *i_ctx_p, bool has_alpha));

#endif /* iimage_INCLUDED */
