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

/* $Id: sjbig2.h,v 1.4 2005/12/13 16:57:28 jemarch Exp $ */
/* Definitions for jbig2decode filter */
/* Requires scommon.h; strimpl.h if any templates are referenced */

#ifndef sjbig2_INCLUDED
#  define sjbig2_INCLUDED

#include "stdint_.h"
#include "scommon.h"
#include <jbig2.h>

/* Arcfour is a symmetric cipher whose state is maintained
 * in two indices into an accompanying 8x8 S box. this will
 * typically be allocated on the stack, and so has no memory
 * management associated.
 */
typedef struct stream_jbig2decode_state_s
{
    stream_state_common;	/* a define from scommon.h */
    Jbig2GlobalCtx *global_ctx;
    Jbig2Ctx *decode_ctx;
    Jbig2Image *image;
    long offset; /* offset into the image bitmap of the next byte to be returned */
}
stream_jbig2decode_state;

/* call in to process the JBIG2Globals parameter */
public int
s_jbig2decode_make_global_ctx(byte *data, uint length, Jbig2GlobalCtx **global_ctx);
public int
s_jbig2decode_set_global_ctx(stream_state *ss, Jbig2GlobalCtx *global_ctx);

#define private_st_jbig2decode_state()	\
  gs_private_st_simple(st_jbig2decode_state, stream_jbig2decode_state,\
    "jbig2decode filter state")
extern const stream_template s_jbig2decode_template;

#endif /* sjbig2_INCLUDED */
