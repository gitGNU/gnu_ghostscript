/* Copyright (C) 1997 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxcllzw.c,v 1.1 2004/01/14 16:59:51 atai Exp $ */
/* LZW filter initialization for RAM-based band lists */
#include "std.h"
#include "gstypes.h"
#include "gsmemory.h"
#include "gxclmem.h"
#include "slzwx.h"

private stream_LZW_state cl_LZWE_state;
private stream_LZW_state cl_LZWD_state;

/* Initialize the states to be copied. */
void
gs_cl_lzw_init(gs_memory_t * mem)
{
    s_LZW_set_defaults((stream_state *) & cl_LZWE_state);
    cl_LZWE_state.template = &s_LZWE_template;
    s_LZW_set_defaults((stream_state *) & cl_LZWD_state);
    cl_LZWD_state.template = &s_LZWD_template;
}

/* Return the prototypes for compressing/decompressing the band list. */
const stream_state *
clist_compressor_state(void *client_data)
{
    return (const stream_state *)&cl_LZWE_state;
}
const stream_state *
clist_decompressor_state(void *client_data)
{
    return (const stream_state *)&cl_LZWD_state;
}
