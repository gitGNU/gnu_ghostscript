/* Copyright (C) 1994, 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: sdctc.c,v 1.1 2004/01/14 16:59:53 atai Exp $ */
/* Code common to DCT encoding and decoding streams */
#include "stdio_.h"
#include "jpeglib_.h"
#include "gsmemory.h"
#include "gsmalloc.h"
#include "strimpl.h"
#include "sdct.h"

public_st_DCT_state();

/* Set the defaults for the DCT filters. */
void
s_DCT_set_defaults(stream_state * st)
{
    stream_DCT_state *const ss = (stream_DCT_state *) st;

    ss->jpeg_memory = &gs_memory_default;
    ss->data.common = 0;
	/****************
	  ss->data.common->Picky = 0;
	  ss->data.common->Relax = 0;
	 ****************/
    ss->ColorTransform = -1;
    ss->QFactor = 1.0;
    /* Clear pointers */
    ss->Markers.data = 0;
    ss->Markers.size = 0;
}
