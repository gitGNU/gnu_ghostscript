/* Copyright (C) 1994, 1995, 1996, 1997, 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxdither.h,v 1.1 2004/01/14 16:59:51 atai Exp $ */
/* Interface to gxdither.c */

#ifndef gxdither_INCLUDED
#  define gxdither_INCLUDED

#include "gxfrac.h"

#ifndef gx_device_halftone_DEFINED
#  define gx_device_halftone_DEFINED
typedef struct gx_device_halftone_s gx_device_halftone;
#endif

/*
 * Note that in the procedures below, the colors are specified by fracs,
 * but the alpha value is a gx_color_value.  This is a design flaw that
 * we might be able to fix eventually.
 */

/* Render a gray, possibly by halftoning. */
/* Return 0 if complete, 1 if caller must do gx_color_load, <0 on error. */
int gx_render_device_gray(P6(frac gray, gx_color_value alpha,
			     gx_device_color * pdevc, gx_device * dev,
			     gx_device_halftone * dev_ht,
			     const gs_int_point * ht_phase));

#define gx_render_gray_alpha(gray, alpha, pdevc, pis, dev, select)\
  gx_render_device_gray(gray, alpha, pdevc, dev, pis->dev_ht,\
			&pis->screen_phase[select])
#define gx_render_gray(gray, pdevc, pis, dev, select)\
  gx_render_gray_alpha(gray, pis->alpha, pdevc, pis, dev, select)

/* Render a color, possibly by halftoning. */
/* Return as for gx_render_[device_]gray. */
int gx_render_device_color(P10(frac red, frac green, frac blue, frac white,
			       bool cmyk, gx_color_value alpha,
			       gx_device_color * pdevc, gx_device * dev,
			       gx_device_halftone * pdht,
			       const gs_int_point * ht_phase));

#define gx_render_color_alpha(r, g, b, w, a, cmyk, pdevc, pis, dev, select)\
  gx_render_device_color(r, g, b, w, cmyk, a, pdevc, dev,\
			 pis->dev_ht, &pis->screen_phase[select])
#define gx_render_color(r, g, b, w, cmyk, pdevc, pis, dev, select)\
  gx_render_color_alpha(r, g, b, w, pis->alpha, cmyk, pdevc, pis, dev, select)
#define gx_render_rgb(r, g, b, pdevc, pis, dev, select)\
  gx_render_color(r, g, b, frac_0, false, pdevc, pis, dev, select)
#define gx_render_cmyk(c, m, y, k, pdevc, pis, dev, select)\
  gx_render_color(c, m, y, k, true, pdevc, pis, dev, select)
#define gx_render_rgb_alpha(r, g, b, a, pdevc, pis, dev, select)\
  gx_render_color_alpha(r, g, b, frac_0, a, false, pdevc, pis, dev, select)

/*
 * Reduce a colored halftone with 0 or 1 varying plane(s) to a pure color
 * or a binary halftone.
 */
int gx_reduce_colored_halftone(P3(gx_device_color *pdevc, gx_device *dev,
				  bool cmyk));

#endif /* gxdither_INCLUDED */
