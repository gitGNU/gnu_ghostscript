/* Copyright (C) 1995, 1997 Aladdin Enterprises.  All rights reserved.
  
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

/* szlibc.c */
/* Code common to zlib encoding and decoding streams */
#include "std.h"
#include "gstypes.h"
#include "gsmemory.h"
#include "gsstruct.h"
#include "strimpl.h"
#include "szlibx.h"
#include "zconf.h"

public_st_zlib_state();

#define ss ((stream_zlib_state *)st)

/* Set defaults for stream parameters. */
void
s_zlib_set_defaults(stream_state *st)
{	ss->windowBits = MAX_WBITS;
	ss->no_wrapper = false;
	ss->level = Z_DEFAULT_COMPRESSION;
	ss->method = Z_DEFLATED;
	/* DEF_MEM_LEVEL should be in zlib.h or zconf.h, but it isn't. */
	ss->memLevel = min(MAX_MEM_LEVEL, 8);
	ss->strategy = Z_DEFAULT_STRATEGY;
}

#undef ss

/* Provide zlib-compatible allocation and freeing functions. */
void *
s_zlib_alloc(void *mem, uint items, uint size)
{	void *address =
	  gs_alloc_byte_array((gs_memory_t *)mem, items, size, "zlib");
	return (address == 0 ? Z_NULL : address);
}
void
s_zlib_free(void *mem, void *address)
{	gs_free_object((gs_memory_t *)mem, address, "zlib");
}
