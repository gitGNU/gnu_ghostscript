/* Copyright (C) 1998, 2000, 2001 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: ichar1.h,v 1.4 2005/05/02 00:03:33 Arabidopsis Exp $ */
/* Type 1 / Type 2 character rendering operator procedures */

#ifndef ichar1_INCLUDED
#  define ichar1_INCLUDED

/* ---------------- Public ---------------- */

/* Render a Type 1 or Type 2 outline. */
/* This is the entire implementation of the .type1/2execchar operators. */
int charstring_execchar(i_ctx_t *i_ctx_p, int font_type_mask);

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
int zcharstring_outline(gs_font_type1 *pfont, int WMode, const ref *pgref,
			const gs_glyph_data_t *pgd,
			const gs_matrix *pmat, gx_path *ppath);

int
z1_glyph_info(gs_font *font, gs_glyph glyph, const gs_matrix *pmat,
	      int members, gs_glyph_info_t *info);

int z1_glyph_info_generic(gs_font *font, gs_glyph glyph, const gs_matrix *pmat,
	      int members, gs_glyph_info_t *info, font_proc_glyph_info((*proc)), 
	      int wmode);

#endif /* ichar1_INCLUDED */
