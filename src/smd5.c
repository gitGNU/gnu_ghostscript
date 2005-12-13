/* Copyright (C) 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: smd5.c,v 1.5 2005/12/13 16:57:28 jemarch Exp $ */
/* MD5Encode filter */
#include "memory_.h"
#include "strimpl.h"
#include "stream.h"
#include "smd5.h"

/* ------ MD5Encode ------ */

private_st_MD5E_state();

/* Initialize the state. */
private int
s_MD5E_init(stream_state * st)
{
    stream_MD5E_state *const ss = (stream_MD5E_state *) st;

    md5_init(&ss->md5);
    return 0;
}

/* Process a buffer. */
private int
s_MD5E_process(stream_state * st, stream_cursor_read * pr,
	       stream_cursor_write * pw, bool last)
{
    stream_MD5E_state *const ss = (stream_MD5E_state *) st;
    int status = 0;

    if (pr->ptr < pr->limit) {
	md5_append(&ss->md5, pr->ptr + 1, pr->limit - pr->ptr);
	pr->ptr = pr->limit;
    }
    if (last) {
	if (pw->limit - pw->ptr >= 16) {
	    md5_finish(&ss->md5, pw->ptr + 1);
	    pw->ptr += 16;
	    status = EOFC;
	} else
	    status = 1;
    }
    return status;
}

/* Stream template */
const stream_template s_MD5E_template = {
    &st_MD5E_state, s_MD5E_init, s_MD5E_process, 1, 16
};

stream *
s_MD5E_make_stream(gs_memory_t *mem, byte *digest, int digest_size)
{
    stream *s = s_alloc(mem, "s_MD5E_make_stream");
    stream_state *ss = s_alloc_state(mem, s_MD5E_template.stype, "s_MD5E_make_stream");

    if (ss == NULL || s == NULL)
	goto err;
    ss->template = &s_MD5E_template;
    if (s_init_filter(s, ss, digest, digest_size, NULL) < 0)
	goto err;
    s->strm = s;
    return s;
err:
    gs_free_object(mem, ss, "s_MD5E_make_stream");
    gs_free_object(mem, s, "s_MD5E_make_stream");
    return NULL;
}
