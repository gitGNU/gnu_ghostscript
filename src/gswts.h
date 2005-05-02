/* Copyright (C) 2002 artofcode LLC.  All rights reserved.
  
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
/*$Id: gswts.h,v 1.2 2005/05/02 00:03:33 Arabidopsis Exp $ */
#ifndef gswts_INCLUDED
#  define gswts_INCLUDED

#ifndef gs_wts_screen_enum_t_DEFINED
#  define gs_wts_screen_enum_t_DEFINED
typedef struct gs_wts_screen_enum_s gs_wts_screen_enum_t;
#endif

typedef struct gx_wts_cell_params_s gx_wts_cell_params_t;

/* Note: this corresponds roughly to the SP structure in the WTS code. */
struct gx_wts_cell_params_s {
    wts_screen_type t;
    int width;
    int height;
    double ufast;
    double vfast;
    double uslow;
    double vslow;
};

gx_wts_cell_params_t *
wts_pick_cell_size(gs_screen_halftone *ph, const gs_matrix *pmat);

gs_wts_screen_enum_t *
gs_wts_screen_enum_new(gx_wts_cell_params_t *wcp);

int
gs_wts_screen_enum_currentpoint(gs_wts_screen_enum_t *wse, gs_point *ppt);

int
gs_wts_screen_enum_next(gs_wts_screen_enum_t *wse, floatp value);

int
wts_sort_blue(gs_wts_screen_enum_t *wse);

int
wts_sort_cell(gs_wts_screen_enum_t *wse);

wts_screen_t *
wts_screen_from_enum(const gs_wts_screen_enum_t *wse);

void
gs_wts_free_enum(gs_wts_screen_enum_t *wse);

void
gs_wts_free_screen(wts_screen_t *wts);

#endif



