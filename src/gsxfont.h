/* Copyright (C) 1993 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsxfont.h,v 1.2 2004/02/14 22:20:18 atai Exp $ */
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
