/* Copyright (C) 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: ifont2.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Type 2 font utilities 2 */

#ifndef ifont2_INCLUDED
#  define ifont2_INCLUDED

/* Declare the Type 2 interpreter. */
extern charstring_interpret_proc(gs_type2_interpret);

/* Default value of lenIV */
#define DEFAULT_LENIV_2 (-1)

/*
 * Get the additional parameters for a Type 2 font (or FontType 2 FDArray
 * entry in a CIDFontType 0 font), beyond those common to Type 1 and Type 2
 * fonts.
 */
int type2_font_params(P3(const_os_ptr op, charstring_font_refs_t *pfr,
			 gs_type1_data *pdata1));

#endif /* ifont2_INCLUDED */
