/* Copyright (C) 1994 artofcode LLC.  All rights reserved.
  
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

/*$Id: gspath2.h,v 1.1 2004/01/14 16:59:50 atai Exp $ */
/* Level 2 graphics state path procedures */
/* Requires gsmatrix.h */

#ifndef gspath2_INCLUDED
#  define gspath2_INCLUDED

/* Miscellaneous */
int gs_setbbox(P5(gs_state *, floatp, floatp, floatp, floatp));

/* Rectangles */
int gs_rectappend(P3(gs_state *, const gs_rect *, uint));
int gs_rectclip(P3(gs_state *, const gs_rect *, uint));
int gs_rectfill(P3(gs_state *, const gs_rect *, uint));
int gs_rectstroke(P4(gs_state *, const gs_rect *, uint, const gs_matrix *));

#endif /* gspath2_INCLUDED */
