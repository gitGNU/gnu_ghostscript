/* Copyright (C) 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: gp_strdl.c,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Default, stream-based readline implementation */
#include "std.h"
#include "gstypes.h"
#include "gsmemory.h"
#include "gp.h"

int
gp_readline_init(void **preadline_data, gs_memory_t * mem)
{
    return 0;
}

int
gp_readline(stream *s_in, stream *s_out, void *readline_data,
	    gs_const_string *prompt, gs_string * buf,
	    gs_memory_t * bufmem, uint * pcount, bool *pin_eol,
	    bool (*is_stdin)(P1(const stream *)))
{
    return sreadline(s_in, s_out, readline_data, prompt, buf, bufmem, pcount,
		     pin_eol, is_stdin);
}

void
gp_readline_finit(void *readline_data)
{
}
