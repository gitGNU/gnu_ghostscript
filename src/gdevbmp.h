/* Copyright (C) 1998 Aladdin Enterprises.  All rights reserved.
  
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

  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gdevbmp.h,v 1.3 2005/05/02 00:03:27 Arabidopsis Exp $ */
/* .BMP file format definitions and utility interfaces */

#ifndef gdevbmp_INCLUDED
#  define gdevbmp_INCLUDED

/* Define the default X and Y resolution. */
#define X_DPI 72
#define Y_DPI 72

/* Write the BMP file header.  This procedure is used for all formats. */
int write_bmp_header(gx_device_printer *pdev, FILE *file);

/* Write a BMP header for separated CMYK output. */
int write_bmp_separated_header(gx_device_printer *pdev, FILE *file);

/* 24-bit color mappers */
dev_proc_map_rgb_color(bmp_map_16m_rgb_color);
dev_proc_map_color_rgb(bmp_map_16m_color_rgb);

#endif				/* gdevbmp_INCLUDED */
