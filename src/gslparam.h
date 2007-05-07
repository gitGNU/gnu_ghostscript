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

/* $Id: gslparam.h,v 1.6 2007/05/07 11:21:45 Arabidopsis Exp $ */
/* Line parameter definitions */

#ifndef gslparam_INCLUDED
#  define gslparam_INCLUDED

/* Line cap values */
typedef enum {
    gs_cap_butt = 0,
    gs_cap_round = 1,
    gs_cap_square = 2,
    gs_cap_triangle = 3,		/* not supported by PostScript */
    gs_cap_unknown = 4
} gs_line_cap;

#define gs_line_cap_max 3

/* Line join values */
typedef enum {
    gs_join_miter = 0,
    gs_join_round = 1,
    gs_join_bevel = 2,
    gs_join_none = 3,		/* not supported by PostScript */
    gs_join_triangle = 4,	/* not supported by PostScript */
    gs_join_unknown = 5
} gs_line_join;

#define gs_line_join_max 4

#endif /* gslparam_INCLUDED */
