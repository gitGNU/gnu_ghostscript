/* Copyright (C) 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gp_strdl.c,v 1.2 2004/02/14 22:20:16 atai Exp $ */
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
	    bool (*is_stdin)(const stream *))
{
    return sreadline(s_in, s_out, readline_data, prompt, buf, bufmem, pcount,
		     pin_eol, is_stdin);
}

void
gp_readline_finit(void *readline_data)
{
}
