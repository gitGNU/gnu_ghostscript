/* Copyright (C) 1998, 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: ichar1.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Type 1 / Type 2 character rendering operator procedures */

#ifndef ichar1_INCLUDED
#  define ichar1_INCLUDED

/* ---------------- Public ---------------- */

/* Render a Type 1 or Type 2 outline. */
/* This is the entire implementation of the .type1/2execchar operators. */
int charstring_execchar(P2(i_ctx_t *i_ctx_p, int font_type_mask));

/* ---------------- Internal ---------------- */

/*
 * Get a Type 1 or Type 2 glyph outline.  This is the glyph_outline
 * procedure for the font.
 */
font_proc_glyph_outline(zchar1_glyph_outline);

/*
 * Get a glyph outline given a CharString.  The glyph_outline procedure
 * for CIDFontType 0 fonts uses this.
 */
int zcharstring_outline(P5(gs_font_type1 *pfont, const ref *pgref,
			   const gs_const_string *pgstr,
			   const gs_matrix *pmat, gx_path *ppath));

#endif /* ichar1_INCLUDED */
