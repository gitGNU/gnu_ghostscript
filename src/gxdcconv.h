/* Copyright (C) 1992, 1993, 1997 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gxdcconv.h,v 1.4 2005/12/13 16:57:24 jemarch Exp $ */
/* Internal device color conversion interfaces */

#ifndef gxdcconv_INCLUDED
#  define gxdcconv_INCLUDED

#include "gxfrac.h"

/* Color space conversion routines */
frac color_rgb_to_gray(frac r, frac g, frac b,
		       const gs_imager_state * pis);
void color_rgb_to_cmyk(frac r, frac g, frac b,
		       const gs_imager_state * pis, frac cmyk[4]);
frac color_cmyk_to_gray(frac c, frac m, frac y, frac k,
			const gs_imager_state * pis);
void color_cmyk_to_rgb(frac c, frac m, frac y, frac k,
		       const gs_imager_state * pis, frac rgb[3]);

#endif /* gxdcconv_INCLUDED */
