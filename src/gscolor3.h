/* Copyright (C) 1997 artofcode LLC.  All rights reserved.
  
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

/*$Id: gscolor3.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Client interface to LanguageLevel 3 color facilities */

#ifndef gscolor3_INCLUDED
#  define gscolor3_INCLUDED

/* Smooth shading */
#ifndef gs_shading_t_DEFINED
#  define gs_shading_t_DEFINED
typedef struct gs_shading_s gs_shading_t;
#endif

int gs_setsmoothness(P2(gs_state *, floatp));
float gs_currentsmoothness(P1(const gs_state *));
int gs_shfill(P2(gs_state *, const gs_shading_t *));

#endif /* gscolor3_INCLUDED */
