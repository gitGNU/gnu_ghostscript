/* Copyright (C) 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: gdevbmp.h,v 1.1 2004/01/14 16:59:47 atai Exp $ */
/* .BMP file format definitions and utility interfaces */

#ifndef gdevbmp_INCLUDED
#  define gdevbmp_INCLUDED

/* Define the default X and Y resolution. */
#define X_DPI 72
#define Y_DPI 72

/* Write the BMP file header.  This procedure is used for all formats. */
int write_bmp_header(P2(gx_device_printer *pdev, FILE *file));

/* Write a BMP header for separated CMYK output. */
int write_bmp_separated_header(P2(gx_device_printer *pdev, FILE *file));

/* 24-bit color mappers */
dev_proc_map_rgb_color(bmp_map_16m_rgb_color);
dev_proc_map_color_rgb(bmp_map_16m_color_rgb);

#endif				/* gdevbmp_INCLUDED */
