/* Copyright (C) 2003-2004 artofcode LLC.  All rights reserved.
  
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

/* $Id: sjpx.h,v 1.2 2006/06/16 12:55:04 Arabidopsis Exp $ */
/* Definitions for JPXDecode filter (JPEG 2000) */
/* we link to the JasPer library for the actual decoding */

#ifndef sjpx_INCLUDED
#  define sjpx_INCLUDED

/* Requires scommon.h; strimpl.h if any templates are referenced */

#include "scommon.h"
#include <jasper/jasper.h>

/* Our local state consists of pointers to the JasPer library's
 * stream and image structs for sending and retrieving the
 * image data. There's no way to feed a jasper stream with
 * incremental buffers, so we also must spool the entire
 * compressed stream into our own buffer before handing it
 * to the library. We also keep track of how much of the
 * decoded image we have returned.
 */
typedef struct stream_jpxd_state_s
{
    stream_state_common;	/* a define from scommon.h */
    jas_image_t *image;
    jas_stream_t *stream;
    long offset; /* offset into the image bitmap of the next
                    byte to be returned */
    const gs_memory_t *jpx_memory;
    unsigned char *buffer; /* temporary buffer for compressed data */
    long bufsize; /* total size of the buffer */
    long buffill; /* number of bytes written into the buffer */
}
stream_jpxd_state;

#define private_st_jpxd_state()	\
  gs_private_st_simple(st_jpxd_state, stream_jpxd_state,\
    "JPXDecode filter state")
extern const stream_template s_jpxd_template;

#endif /* sjpx_INCLUDED */
