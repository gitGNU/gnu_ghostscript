/* Copyright (C) 1997, 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gsdsrc.c,v 1.3 2005/05/02 00:03:21 Arabidopsis Exp $ */
/* DataSource procedures */

#include "memory_.h"
#include "gx.h"
#include "gsdsrc.h"
#include "gserrors.h"
#include "stream.h"

/* GC descriptor */
public_st_data_source();
private 
ENUM_PTRS_WITH(data_source_enum_ptrs, gs_data_source_t *psrc)
{
    if (psrc->type == data_source_type_string)
	ENUM_RETURN_CONST_STRING_PTR(gs_data_source_t, data.str);
    else if (psrc->type == data_source_type_stream)
	ENUM_RETURN_PTR(gs_data_source_t, data.strm);
    else			/* bytes or floats */
	ENUM_RETURN_PTR(gs_data_source_t, data.str.data);
}
ENUM_PTRS_END
private RELOC_PTRS_WITH(data_source_reloc_ptrs, gs_data_source_t *psrc)
{
    if (psrc->type == data_source_type_string)
	RELOC_CONST_STRING_PTR(gs_data_source_t, data.str);
    else if (psrc->type == data_source_type_stream)
	RELOC_PTR(gs_data_source_t, data.strm);
    else			/* bytes or floats */
	RELOC_PTR(gs_data_source_t, data.str.data);
}
RELOC_PTRS_END

/* Access data from a string or a byte object. */
/* Does *not* check bounds. */
int
data_source_access_string(const gs_data_source_t * psrc, ulong start,
			  uint length, byte * buf, const byte ** ptr)
{
    const byte *p = psrc->data.str.data + start;

    if (ptr)
	*ptr = p;
    else
	memcpy(buf, p, length);
    return 0;
}
/* access_bytes is identical to access_string, but has a different */
/* GC procedure. */
int
data_source_access_bytes(const gs_data_source_t * psrc, ulong start,
			 uint length, byte * buf, const byte ** ptr)
{
    const byte *p = psrc->data.str.data + start;

    if (ptr)
	*ptr = p;
    else
	memcpy(buf, p, length);
    return 0;
}

/* Access data from a stream. */
/* Returns gs_error_rangecheck if out of bounds. */
int
data_source_access_stream(const gs_data_source_t * psrc, ulong start,
			  uint length, byte * buf, const byte ** ptr)
{
    stream *s = psrc->data.strm;
    const byte *p;

    if (start >= s->position &&
	(p = start - s->position + s->cbuf) + length <=
	s->cursor.r.limit + 1
	) {
	if (ptr)
	    *ptr = p;
	else
	    memcpy(buf, p, length);
    } else {
	uint nread;
	int code = sseek(s, start);

	if (code < 0)
	    return_error(gs_error_rangecheck);
	code = sgets(s, buf, length, &nread);
	if (code < 0)
	    return_error(gs_error_rangecheck);
	if (nread != length)
	    return_error(gs_error_rangecheck);
	if (ptr)
	    *ptr = buf;
    }
    return 0;
}
