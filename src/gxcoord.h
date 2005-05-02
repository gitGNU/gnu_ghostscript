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

  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gxcoord.h,v 1.3 2005/05/02 00:03:34 Arabidopsis Exp $ */
/* Internal graphics state CTM procedures */
/* Requires gxmatrix.h and gzstate.h */

#ifndef gxcoord_INCLUDED
#  define gxcoord_INCLUDED

#include "gscoord.h"

/* Set the translation to a fixed value, and translate any existing path. */
/* Used by gschar.c to prepare for a BuildChar or BuildGlyph procedure. */
int gx_translate_to_fixed(gs_state *, fixed, fixed);

/* Scale the CTM and character matrix for oversampling. */
int gx_scale_char_matrix(gs_state *, int, int);

/* Compute the coefficients for fast fixed-point distance transformations */
/* from a transformation matrix. */
int gx_matrix_to_fixed_coeff(const gs_matrix *, fixed_coeff *, int);

#endif /* gxcoord_INCLUDED */
