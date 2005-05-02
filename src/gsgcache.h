/* Copyright (C) 1996, 2000, 2001 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsgcache.h,v 1.2 2005/05/02 00:03:26 Arabidopsis Exp $ */
/* Glyph data cache definition. */

#ifndef gxgcache_INCLUDED
#  define gxgcache_INCLUDED

/* Using : */

#ifndef gs_font_type42_DEFINED
#  define gs_font_type42_DEFINED
typedef struct gs_font_type42_s gs_font_type42;
#endif

#ifndef gs_glyph_data_DEFINED
#   define gs_glyph_data_DEFINED
typedef struct gs_glyph_data_s gs_glyph_data_t;
#endif

#ifndef stream_DEFINED
#  define stream_DEFINED
typedef struct stream_s stream;
#endif

/* Data type definition : */

#ifndef gs_glyph_cache_DEFINED
#  define gs_glyph_cache_DEFINED
typedef struct gs_glyph_cache_s gs_glyph_cache;
#endif

typedef int (*get_glyph_data_from_file)(gs_font_type42 *pfont, stream *s, uint glyph_index,
		gs_glyph_data_t *pgd);


/* Methods : */

gs_glyph_cache *gs_glyph_cache__alloc(gs_font_type42 *pfont, stream *s,
			get_glyph_data_from_file read_data);
void gs_glyph_cache__release(gs_glyph_cache *this);
int gs_get_glyph_data_cached(gs_font_type42 *pfont, uint glyph_index, gs_glyph_data_t *pgd);

#endif /* gxgcache_INCLUDED */
