/* Copyright (C) 1989, 1995, 1996, 1997, 1999, 2000, 2002 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: zchar42.h,v 1.2 2005/05/02 00:03:33 Arabidopsis Exp $ */

#ifndef zchar42_INCLUDED
#  define zchar42_INCLUDED

/* Get a Type 42 character metrics and set the cache device. */
int zchar42_set_cache(i_ctx_t *i_ctx_p, gs_font_base *pbfont, ref *cnref, 
	    uint glyph_index, op_proc_t cont, op_proc_t *exec_cont, bool put_lsb);

#endif /* zchar42_INCLUDED */
