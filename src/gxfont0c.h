/* Copyright (C) 2002 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gxfont0c.h,v 1.1 2004/02/14 22:32:08 atai Exp $ */
/* Interface to gsfont0c.c */

#ifndef gxfont0c_INCLUDED
#  define gxfont0c_INCLUDED

#include "gxfont0.h"
#include "gxfcid.h"

/* Exported by gsfont0c.c */

/*
 * Create a Type 0 font wrapper for a CIDFont.
 * psmat == NULL means use the identity matrix.
 */
int gs_font_type0_from_cidfont(gs_font_type0 **ppfont0, gs_font *font,
			       int wmode, const gs_matrix *psmat,
			       gs_memory_t *mem);

/*
 * Create a Type 0 font wrapper for a Type 42 font (converted to a Type 2
 * CIDFont), optionally using the TrueType cmap as the CMap.
 * See gs_cmap_from_type42_cmap below for details.
 */
int gs_font_type0_from_type42(gs_font_type0 **ppfont0, gs_font_type42 *pfont42,
			      int wmode, bool use_cmap, gs_memory_t *mem);

/* Exported by gsfcid2.c */

/*
 * Create a Type 2 CIDFont from a Type 42 font.
 */
int gs_font_cid2_from_type42(gs_font_cid2 **ppfcid, gs_font_type42 *pfont42,
			     int wmode, gs_memory_t *mem);

/*
 * Create a CMap from a TrueType cmap (Platform 3, Encoding 1, Format 4 only).
 * The resulting CMap is marked as being Unicode-based.
 */
int gs_cmap_from_type42_cmap(gs_cmap_t **ppcmap, gs_font_type42 *pfont42,
			     int wmode, gs_memory_t *mem);

#endif /* gxfont0c_INCLUDED */
