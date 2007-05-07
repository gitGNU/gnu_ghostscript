/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
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

/* $Id: gscsel.h,v 1.5 2007/05/07 11:21:45 Arabidopsis Exp $ */
/* Definitions for color operand selection */

#ifndef gscsel_INCLUDED
#  define gscsel_INCLUDED

/*
 * Define whether we are mapping a "source" or a "texture" color for
 * RasterOp.  Right the source and texture only have separate halftone
 * phases in the graphics state, but someday they might have more.
 */
typedef enum {
    gs_color_select_all = -1,	/* for setting only, not for reading */
    gs_color_select_texture = 0,	/* 0 is the one is used for currenthtphase */
    gs_color_select_source = 1
} gs_color_select_t;

#define gs_color_select_count 2

#endif /* gscsel_INCLUDED */
