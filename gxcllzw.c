/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
  This file is part of GNU Ghostscript.
  
  GNU Ghostscript is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY.  No author or distributor accepts responsibility to
  anyone for the consequences of using it or for whether it serves any
  particular purpose or works at all, unless he says so in writing.  Refer to
  the GNU General Public License for full details.
  
  Everyone is granted permission to copy, modify and redistribute GNU
  Ghostscript, but only under the conditions described in the GNU General
  Public License.  A copy of this license is supposed to have been given to
  you along with GNU Ghostscript so you can know your rights and
  responsibilities.  It should be in a file named COPYING.  Among other
  things, the copyright notice and this notice must be preserved on all
  copies.
  
  Aladdin Enterprises is not affiliated with the Free Software Foundation or
  the GNU Project.  GNU Ghostscript, as distributed by Aladdin Enterprises,
  does not depend on any other GNU software.
*/

/* gxcllzw.c */
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
gs_cl_lzw_init(gs_memory_t *mem)
{	s_LZW_set_defaults((stream_state *)&cl_LZWE_state);
	cl_LZWE_state.template = &s_LZWE_template;
	s_LZW_set_defaults((stream_state *)&cl_LZWD_state);
	cl_LZWD_state.template = &s_LZWD_template;
}

/* Return the prototypes for compressing/decompressing the band list. */
const stream_state *
clist_compressor_state(void *client_data)
{	return (const stream_state *)&cl_LZWE_state;
}
const stream_state *
clist_decompressor_state(void *client_data)
{	return (const stream_state *)&cl_LZWD_state;
}
