/* Copyright (C) 1989, 1996 Aladdin Enterprises.  All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 2
  as published by the Free Software Foundation.


  This software is provided AS-IS with no warranty, either express or
  implied. That is, this program is distributed in the hope that it will 
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.
  
  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gscoord.h,v 1.2 2004/02/14 22:20:17 atai Exp $ */
/* Interface to graphics state CTM procedures */
/* Requires gsmatrix.h and gsstate.h */

#ifndef gscoord_INCLUDED
#  define gscoord_INCLUDED

/* Coordinate system modification */
int gs_initmatrix(gs_state *),
    gs_defaultmatrix(const gs_state *, gs_matrix *),
    gs_currentmatrix(const gs_state *, gs_matrix *),
    gs_setmatrix(gs_state *, const gs_matrix *),
    gs_translate(gs_state *, floatp, floatp),
    gs_scale(gs_state *, floatp, floatp),
    gs_rotate(gs_state *, floatp),
    gs_concat(gs_state *, const gs_matrix *);

/* Extensions */
int gs_setdefaultmatrix(gs_state *, const gs_matrix *),
    gs_currentcharmatrix(gs_state *, gs_matrix *, bool),
    gs_setcharmatrix(gs_state *, const gs_matrix *),
    gs_settocharmatrix(gs_state *);

/* Coordinate transformation */
int gs_transform(gs_state *, floatp, floatp, gs_point *),
    gs_dtransform(gs_state *, floatp, floatp, gs_point *),
    gs_itransform(gs_state *, floatp, floatp, gs_point *),
    gs_idtransform(gs_state *, floatp, floatp, gs_point *);

#ifndef gs_imager_state_DEFINED
#  define gs_imager_state_DEFINED
typedef struct gs_imager_state_s gs_imager_state;
#endif

int gs_imager_setmatrix(gs_imager_state *, const gs_matrix *);
int gs_imager_idtransform(const gs_imager_state *, floatp, floatp, gs_point *);

#endif /* gscoord_INCLUDED */
