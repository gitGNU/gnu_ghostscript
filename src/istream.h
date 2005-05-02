/* Copyright (C) 1994, 1995, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: istream.h,v 1.3 2005/05/02 00:03:24 Arabidopsis Exp $ */
/* Interpreter support procedures for streams */
/* Requires scommon.h */

#ifndef istream_INCLUDED
#  define istream_INCLUDED

/* Procedures exported by zfproc.c */

	/* for zfilter.c - procedure stream initialization */
int sread_proc(ref *, stream **, gs_ref_memory_t *);
int swrite_proc(ref *, stream **, gs_ref_memory_t *);

	/* for interp.c, zfileio.c, zpaint.c - handle a procedure */
	/* callback or an interrupt */
int s_handle_read_exception(i_ctx_t *, int, const ref *, const ref *,
			    int, op_proc_t);
int s_handle_write_exception(i_ctx_t *, int, const ref *, const ref *,
			     int, op_proc_t);

#endif /* istream_INCLUDED */
