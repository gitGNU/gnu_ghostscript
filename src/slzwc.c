/* Copyright (C) 1995, 1996, 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: slzwc.c,v 1.1 2004/01/14 16:59:53 atai Exp $ */
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
