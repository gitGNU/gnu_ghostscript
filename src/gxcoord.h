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

/*$Id: gxcoord.h,v 1.1 2004/01/14 16:59:51 atai Exp $ */
/* Internal graphics state CTM procedures */
/* Requires gxmatrix.h and gzstate.h */

#ifndef gxcoord_INCLUDED
#  define gxcoord_INCLUDED

#include "gscoord.h"

/* Set the translation to a fixed value, and translate any existing path. */
/* Used by gschar.c to prepare for a BuildChar or BuildGlyph procedure. */
int gx_translate_to_fixed(P3(gs_state *, fixed, fixed));

/* Scale the CTM and character matrix for oversampling. */
int gx_scale_char_matrix(P3(gs_state *, int, int));

/* Compute the coefficients for fast fixed-point distance transformations */
/* from a transformation matrix. */
int gx_matrix_to_fixed_coeff(P3(const gs_matrix *, fixed_coeff *, int));

#endif /* gxcoord_INCLUDED */
