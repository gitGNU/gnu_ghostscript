/* Copyright (C) 2003 artofcode LLC.  All rights reserved.
  
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

/* $Id: sjbig2.h,v 1.1 2004/02/14 22:32:08 atai Exp $ */
/* Definitions for jbig2decode filter */
/* Requires scommon.h; strimpl.h if any templates are referenced */

#ifndef sjbig2_INCLUDED
#  define sjbig2_INCLUDED

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
