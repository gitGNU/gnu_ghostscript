/* Copyright (C) 1994, 1997 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsht1.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Extended public interface to halftones */

#ifndef gsht1_INCLUDED
#  define gsht1_INCLUDED

#include "gsht.h"

/* Procedural interface */
int gs_setcolorscreen(P2(gs_state *, gs_colorscreen_halftone *));
int gs_currentcolorscreen(P2(gs_state *, gs_colorscreen_halftone *));

/*
 * We include sethalftone here, even though it is a Level 2 feature,
 * because it turns out to be convenient to define setcolorscreen
 * using sethalftone.
 */
#ifndef gs_halftone_DEFINED
#  define gs_halftone_DEFINED
typedef struct gs_halftone_s gs_halftone;

#endif
/*
 * gs_halftone structures may have complex substructures.  We provide two
 * procedures for setting them.  gs_halftone assumes that the gs_halftone
 * structure and all its substructures was allocated with the same allocator
 * as the gs_state; gs_halftone_allocated looks in the structure itself (the
 * rc.memory member) to find the allocator that was used.  Both procedures
 * copy the top-level structure (using the appropriate allocator), but take
 * ownership of the substructures.
 */
int gs_sethalftone(P2(gs_state *, gs_halftone *));
int gs_sethalftone_allocated(P2(gs_state *, gs_halftone *));
int gs_currenthalftone(P2(gs_state *, gs_halftone *));

#endif /* gsht1_INCLUDED */
