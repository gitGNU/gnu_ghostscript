/* Copyright (C) 1992, 1993, 1997 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxdcconv.h,v 1.1 2004/01/14 16:59:51 atai Exp $ */
/* Internal device color conversion interfaces */

#ifndef gxdcconv_INCLUDED
#  define gxdcconv_INCLUDED

#include "gxfrac.h"

/* Color space conversion routines */
frac color_rgb_to_gray(P4(frac r, frac g, frac b,
			  const gs_imager_state * pis));
void color_rgb_to_cmyk(P5(frac r, frac g, frac b,
			  const gs_imager_state * pis, frac cmyk[4]));
frac color_cmyk_to_gray(P5(frac c, frac m, frac y, frac k,
			   const gs_imager_state * pis));
void color_cmyk_to_rgb(P6(frac c, frac m, frac y, frac k,
			  const gs_imager_state * pis, frac rgb[3]));

#endif /* gxdcconv_INCLUDED */
