/* Copyright (C) 2003 artofcode LLC.  All rights reserved.
  
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

  
*/

/* $Id: sjbig2.h,v 1.5 2006/06/16 12:55:05 Arabidopsis Exp $ */
/* Definitions for jbig2decode filter */
/* Requires scommon.h; strimpl.h if any templates are referenced */

#ifndef sjbig2_INCLUDED
#  define sjbig2_INCLUDED

#include "stdint_.h"
#include "scommon.h"
#include <jbig2.h>

/* JBIG2Decode internal stream state */
typedef struct stream_jbig2decode_state_s
{
    stream_state_common;	/* a define from scommon.h */
    Jbig2GlobalCtx *global_ctx;
    Jbig2Ctx *decode_ctx;
    Jbig2Image *image;
    long offset; /* offset into the image bitmap of the next byte to be returned */
    int error;
}
stream_jbig2decode_state;

#define private_st_jbig2decode_state()	\
  gs_private_st_simple(st_jbig2decode_state, stream_jbig2decode_state,\
    "jbig2decode filter state")
extern const stream_template s_jbig2decode_template;

/* call ins to process the JBIG2Globals parameter */
public int
s_jbig2decode_make_global_data(byte *data, uint length, void **result);
public int
s_jbig2decode_set_global_data(stream_state *ss, void *data);
public void
s_jbig2decode_free_global_data(void *data);
	
#endif /* sjbig2_INCLUDED */
