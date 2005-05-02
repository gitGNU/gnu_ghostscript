/* Copyright (C) 1992, 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gscolor2.h,v 1.4 2005/05/02 00:03:23 Arabidopsis Exp $ */
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
const gs_color_space *gs_currentcolorspace(const gs_state *);
int gs_setcolorspace(gs_state *, const gs_color_space *);
const gs_client_color *gs_currentcolor(const gs_state *);
int gs_setcolor(gs_state *, const gs_client_color *);


/* CIE-specific routines */
#ifndef gs_cie_render_DEFINED
#  define gs_cie_render_DEFINED
typedef struct gs_cie_render_s gs_cie_render;
#endif
const gs_cie_render *gs_currentcolorrendering(const gs_state *);
int gs_setcolorrendering(gs_state *, gs_cie_render *);

/* High level device support */
int gs_includecolorspace(gs_state * pgs, const byte *res_name, int name_length);

#endif /* gscolor2_INCLUDED */
