/* Copyright (C) 1994 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gspath2.h,v 1.4 2005/12/13 16:57:23 jemarch Exp $ */
/* Level 2 graphics state path procedures */
/* Requires gsmatrix.h */

#ifndef gspath2_INCLUDED
#  define gspath2_INCLUDED

/* Miscellaneous */
int gs_setbbox(gs_state *, floatp, floatp, floatp, floatp);

/* Rectangles */
int gs_rectappend(gs_state *, const gs_rect *, uint);
int gs_rectclip(gs_state *, const gs_rect *, uint);
int gs_rectfill(gs_state *, const gs_rect *, uint);
int gs_rectstroke(gs_state *, const gs_rect *, uint, const gs_matrix *);

#endif /* gspath2_INCLUDED */
