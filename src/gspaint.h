/* Copyright (C) 1989, 1992, 1993 artofcode LLC.  All rights reserved.
  
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

/*$Id: gspaint.h,v 1.1 2004/01/14 16:59:50 atai Exp $ */
/* Erase/fill/stroke procedures */
/* Requires gsstate.h */

#ifndef gspaint_INCLUDED
#  define gspaint_INCLUDED

/* Painting */
int gs_erasepage(P1(gs_state *)),
    gs_fillpage(P1(gs_state *)),
    gs_fill(P1(gs_state *)),
    gs_eofill(P1(gs_state *)),
    gs_stroke(P1(gs_state *));

/* Image tracing */
int gs_imagepath(P4(gs_state *, int, int, const byte *));

#endif /* gspaint_INCLUDED */
