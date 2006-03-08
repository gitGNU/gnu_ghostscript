/* Copyright (C) 2004 Artifex Software Inc., artofcode LLC.  All rights reserved.

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

/*$Id: gsequivc.h,v 1.1 2006/03/08 12:30:24 Arabidopsis Exp $ */
/* Header for routines for determining equivalent color for spot colors */

/* For more information, see comment at the start of src/gsequivc.c */

#ifndef gsequivc_INCLUDED
# define gsequivc_INCLUDED

/*
 * Structure for holding a CMYK color.
 */
typedef struct cmyk_color_s {
    bool color_info_valid;
    frac c;
    frac m;
    frac y;
    frac k;
} cmyk_color;

/*
 * Structure for holding parameters for collecting the equivalent CMYK
 * for a spot colorant.
 */
typedef struct equivalent_cmyk_color_params_s {
    bool all_color_info_valid;
    cmyk_color color[GX_DEVICE_MAX_SEPARATIONS];
} equivalent_cmyk_color_params;

/* If possible, update the equivalent CMYK color for a spot color */
void update_spot_equivalent_cmyk_colors(gx_device * pdev,
		const gs_state * pgs, gs_devn_params * pdevn_params,
		equivalent_cmyk_color_params * pparams);

#endif		/* define gsequivc_INCLUDED */
