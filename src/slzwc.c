/* Copyright (C) 1995, 1996, 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: slzwc.c,v 1.3 2005/05/02 00:03:26 Arabidopsis Exp $ */
/* Code common to LZW encoding and decoding streams */
#include "std.h"
#include "strimpl.h"
#include "slzwx.h"

/* Define the structure for the GC. */
public_st_LZW_state();

/* Set defaults */
void
s_LZW_set_defaults(stream_state * st)
{
    stream_LZW_state *const ss = (stream_LZW_state *) st;

    s_LZW_set_defaults_inline(ss);
}

/* Release a LZW filter. */
void
s_LZW_release(stream_state * st)
{
    stream_LZW_state *const ss = (stream_LZW_state *) st;

    gs_free_object(st->memory, ss->table.decode, "LZW(close)");
}
