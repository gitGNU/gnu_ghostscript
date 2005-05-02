/* Copyright (C) 1989, 1995, 1996, 1997 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsinit.c,v 1.3 2005/05/02 00:03:23 Arabidopsis Exp $ */
/* Initialization for the imager */
#include "stdio_.h"
#include "memory_.h"
#include "gdebug.h"
#include "gscdefs.h"
#include "gsmemory.h"
#include "gsmalloc.h"
#include "gp.h"
#include "gslib.h"		/* interface definition */

/* Imported from gsmisc.c */
extern FILE *gs_debug_out;

/* Configuration information from gconfig.c. */
extern_gx_init_table();

/* Initialization to be done before anything else. */
int
gs_lib_init(FILE * debug_out)
{
    return gs_lib_init1(gs_lib_init0(debug_out));
}
gs_memory_t *
gs_lib_init0(FILE * debug_out)
{
    gs_memory_t *mem;

    gs_debug_out = debug_out;
    mem = (gs_memory_t *) gs_malloc_init();
    /* Reset debugging flags */
    memset(gs_debug, 0, 128);
    gs_log_errors = 0;
    return mem;
}
int
gs_lib_init1(gs_memory_t * mem)
{
    /* Run configuration-specific initialization procedures. */
    init_proc((*const *ipp));
    int code;

    for (ipp = gx_init_table; *ipp != 0; ++ipp)
	if ((code = (**ipp)(mem)) < 0)
	    return code;
    return 0;
}

/* Clean up after execution. */
void
gs_lib_finit(int exit_status, int code)
{
    /* Do platform-specific cleanup. */
    gp_exit(exit_status, code);
    gs_malloc_release();
}
