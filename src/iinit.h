/* Copyright (C) 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: iinit.h,v 1.3 2005/05/02 00:03:24 Arabidopsis Exp $ */
/* (Internal) interface to iinit.c */

#ifndef iinit_INCLUDED
#  define iinit_INCLUDED

/*
 * Declare initialization procedures exported by iinit.c for imain.c.
 * These must be executed in the order they are declared below.
 */
int obj_init(i_ctx_t **, gs_dual_memory_t *);
int zop_init(i_ctx_t *);
int op_init(i_ctx_t *);

/*
 * Test whether there are any Level 2 operators in the executable.
 * (This is different from the language level in which the interpreter is
 * actually running: it is only tested during initialization.)
 */
bool gs_have_level2(void);

#endif /* iinit_INCLUDED */
