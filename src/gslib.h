/* Copyright (C) 1995, 1996 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gslib.h,v 1.3 2005/05/02 00:03:35 Arabidopsis Exp $ */
/* Library initialization and finalization interface */
/* Requires stdio.h, gsmemory.h */

#ifndef gslib_INCLUDED
#  define gslib_INCLUDED

/*
 * Initialize the library.  gs_lib_init does all of the initialization,
 * using the C heap for initial allocation; if a client wants the library to
 * use a different default allocator during initialization, it should call
 * gs_lib_init0 and then gs_lib_init1.
 */
int gs_lib_init(FILE * debug_out);
gs_memory_t *gs_lib_init0(FILE * debug_out);
int gs_lib_init1(gs_memory_t *);

/* Clean up after execution. */
void gs_lib_finit(int exit_status, int code);

#endif /* gslib_INCLUDED */
