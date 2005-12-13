/* Copyright (C) 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gxp1impl.h,v 1.4 2005/12/13 16:57:24 jemarch Exp $ */
/* PatternType 1 implementation interface */
/* Requires gxpcolor.h */

#ifndef gxp1impl_INCLUDED
#  define gxp1impl_INCLUDED

/*
 * Declare the filling algorithms implemented in gxp1fill.c.
 * We use 'masked_fill_rect' instead of 'masked_fill_rectangle'
 * in order to limit identifier lengths to 32 characters.
 */
dev_color_proc_fill_rectangle(gx_dc_pattern_fill_rectangle);
dev_color_proc_fill_rectangle(gx_dc_pure_masked_fill_rect);
dev_color_proc_fill_rectangle(gx_dc_binary_masked_fill_rect);
dev_color_proc_fill_rectangle(gx_dc_colored_masked_fill_rect);

/*
 * Declare the Pattern color mapping procedures exported by gxpcmap.c.
 */
int gx_pattern_load(gx_device_color *, const gs_imager_state *,
		    gx_device *, gs_color_select_t);
pattern_proc_remap_color(gs_pattern1_remap_color);

#endif /* gxp1impl_INCLUDED */
