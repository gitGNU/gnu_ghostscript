/* Copyright (C) 1994, 1995, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: istream.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Interpreter support procedures for streams */
/* Requires scommon.h */

#ifndef istream_INCLUDED
#  define istream_INCLUDED

/* Procedures exported by zfproc.c */

	/* for zfilter.c - procedure stream initialization */
int sread_proc(P3(ref *, stream **, gs_ref_memory_t *));
int swrite_proc(P3(ref *, stream **, gs_ref_memory_t *));

	/* for interp.c, zfileio.c, zpaint.c - handle a procedure */
	/* callback or an interrupt */
int s_handle_read_exception(P6(i_ctx_t *, int, const ref *, const ref *,
			       int, op_proc_t));
int s_handle_write_exception(P6(i_ctx_t *, int, const ref *, const ref *,
				int, op_proc_t));

#endif /* istream_INCLUDED */
