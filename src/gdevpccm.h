/* Copyright (C) 1992, 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: gdevpccm.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* PC color mapping support */
/* Requires gxdevice.h */

#ifndef gdevpccm_INCLUDED
#  define gdevpccm_INCLUDED

/* Color mapping routines for EGA/VGA-style color. */
dev_proc_map_rgb_color(pc_4bit_map_rgb_color);
dev_proc_map_color_rgb(pc_4bit_map_color_rgb);
#define dci_pc_4bit dci_values(3, 4, 3, 2, 4, 3)

/* Color mapping routines for 8-bit color (with a fixed palette). */
dev_proc_map_rgb_color(pc_8bit_map_rgb_color);
dev_proc_map_color_rgb(pc_8bit_map_color_rgb);
#define dci_pc_8bit dci_values(3, 8, 6, 6, 7, 7)

/* Write the palette on a file. */
int pc_write_palette(P3(gx_device *, uint, FILE *));

#endif /* gdevpccm_INCLUDED */
