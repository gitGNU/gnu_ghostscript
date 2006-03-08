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

/* $Id: gsiodevs.c,v 1.5 2006/03/08 12:30:24 Arabidopsis Exp $ */
/* %stdxxx IODevice implementation for non-PostScript configurations */
#include "gx.h"
#include "gserrors.h"
#include "gxiodev.h"
#include "stream.h"
#include "strimpl.h"

const char iodev_dtype_stdio[] = "Special";
#define iodev_stdio(dname, open) {\
    dname, iodev_dtype_stdio,\
	{ iodev_no_init, open, iodev_no_open_file,\
	  iodev_no_fopen, iodev_no_fclose,\
	  iodev_no_delete_file, iodev_no_rename_file, iodev_no_file_status,\
	  iodev_no_enumerate_files, NULL, NULL,\
	  iodev_no_get_params, iodev_no_put_params\
	}\
}

#define STDIO_BUF_SIZE 128
private int
stdio_close_file(stream *s)
{
    /* Don't close stdio files, but do free the buffer. */
    gs_memory_t *mem = s->memory;

    s->file = 0;
    gs_free_object(mem, s->cbuf, "stdio_close_file(buffer)");
    return 0;
}
private int
stdio_open(gx_io_device * iodev, const char *access, stream ** ps,
	   gs_memory_t * mem, char rw, FILE *file,
	   void (*srw_file)(stream *, FILE *, byte *, uint))
{
    stream *s;
    byte *buf;

    if (!streq1(access, rw))
	return_error(gs_error_invalidfileaccess);
    s = s_alloc(mem, "stdio_open(stream)");
    buf = gs_alloc_bytes(mem, STDIO_BUF_SIZE, "stdio_open(buffer)");
    if (s == 0 || buf == 0) {
	gs_free_object(mem, buf, "stdio_open(buffer)");
	gs_free_object(mem, s, "stdio_open(stream)");
	return_error(gs_error_VMerror);
    }
    srw_file(s, file, buf, STDIO_BUF_SIZE);
    s->procs.close = stdio_close_file;
    *ps = s;
    return 0;
}

private int
stdin_open(gx_io_device * iodev, const char *access, stream ** ps,
	   gs_memory_t * mem)
{
    return stdio_open(iodev, access, ps, mem, 'r', 
		      mem->gs_lib_ctx->fstdin, sread_file);
}
const gx_io_device gs_iodev_stdin = iodev_stdio("%stdin%", stdin_open);

private int
stdout_open(gx_io_device * iodev, const char *access, stream ** ps,
	    gs_memory_t * mem)
{
    return stdio_open(iodev, access, ps, mem, 'w', 
		      mem->gs_lib_ctx->fstdout, swrite_file);
}
const gx_io_device gs_iodev_stdout = iodev_stdio("%stdout%", stdout_open);

private int
stderr_open(gx_io_device * iodev, const char *access, stream ** ps,
	    gs_memory_t * mem)
{
    return stdio_open(iodev, access, ps, mem, 'w', 
		      mem->gs_lib_ctx->fstderr, swrite_file);
}
const gx_io_device gs_iodev_stderr = iodev_stdio("%stderr%", stderr_open);
