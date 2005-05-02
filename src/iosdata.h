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

/* $Id: iosdata.h,v 1.3 2005/05/02 00:03:35 Arabidopsis Exp $ */
/* Generic operand stack API */

#ifndef iosdata_INCLUDED
#  define iosdata_INCLUDED

#include "isdata.h"

/* Define the operand stack structure. */
/* Currently this is just a generic ref stack. */
typedef struct op_stack_s {

    ref_stack_t stack;		/* the actual operand stack */

} op_stack_t;

#define public_st_op_stack()	/* in interp.c */\
  gs_public_st_suffix_add0(st_op_stack, op_stack_t, "op_stack_t",\
    op_stack_enum_ptrs, op_stack_reloc_ptrs, st_ref_stack)
#define st_op_stack_num_ptrs st_ref_stack_num_ptrs

#endif /* iosdata_INCLUDED */
