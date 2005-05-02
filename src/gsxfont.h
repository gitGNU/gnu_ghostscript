/* Copyright (C) 1993 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsxfont.h,v 1.3 2005/05/02 00:03:33 Arabidopsis Exp $ */
/* External font client definitions for Ghostscript library */

#ifndef gsxfont_INCLUDED
#  define gsxfont_INCLUDED

/* Define a character glyph identifier.  This is opaque, probably an index */
/* into the font.  Glyph identifiers are font-specific. */
typedef ulong gx_xglyph;

#define gx_no_xglyph ((gx_xglyph)~0L)

/* Structure for xfont procedures. */
struct gx_xfont_procs_s;
typedef struct gx_xfont_procs_s gx_xfont_procs;

/* A generic xfont. */
struct gx_xfont_s;
typedef struct gx_xfont_s gx_xfont;

#endif /* gsxfont_INCLUDED */
