/* Copyright (C) 1996 artofcode LLC.  All rights reserved.
  
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

/*$Id: gscsel.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
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
