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

/*$Id: gscolor2.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Client interface to Level 2 color facilities */
/* (requires gscspace.h, gsmatrix.h) */

#ifndef gscolor2_INCLUDED
#  define gscolor2_INCLUDED

#include "gscindex.h"
#include "gsptype1.h"

/* ---------------- Graphics state ---------------- */

/*
 * Note that setcolorspace and setcolor copy the (top level of) their
 * structure argument, so if the client allocated it on the heap, the
 * client should free it after setting it in the graphics state.
 */

/* General color routines */
const gs_color_space *gs_currentcolorspace(P1(const gs_state *));
int gs_setcolorspace(P2(gs_state *, const gs_color_space *));
const gs_client_color *gs_currentcolor(P1(const gs_state *));
int gs_setcolor(P2(gs_state *, const gs_client_color *));

/*
 * gs_currentcolorspace_index returns the index of the current color space
 * *before* any substitution.
 */
gs_color_space_index gs_currentcolorspace_index(P1(const gs_state *));

/* CIE-specific routines */
#ifndef gs_cie_render_DEFINED
#  define gs_cie_render_DEFINED
typedef struct gs_cie_render_s gs_cie_render;
#endif
const gs_cie_render *gs_currentcolorrendering(P1(const gs_state *));
int gs_setcolorrendering(P2(gs_state *, gs_cie_render *));

#endif /* gscolor2_INCLUDED */
