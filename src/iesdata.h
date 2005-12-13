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

  
*/

/* $Id: iesdata.h,v 1.4 2005/12/13 16:57:25 jemarch Exp $ */
/* Generic execution stack structure definition */

#ifndef iesdata_INCLUDED
#  define iesdata_INCLUDED

#include "isdata.h"

/* Define the execution stack structure. */
typedef struct exec_stack_s {

    ref_stack_t stack;		/* the actual execution stack */

/*
 * To improve performance, we cache the currentfile pointer
 * (i.e., `shallow-bind' it in Lisp terminology).  The invariant is as
 * follows: either esfile points to the currentfile slot on the estack
 * (i.e., the topmost slot with an executable file), or it is 0.
 * To maintain the invariant, it is sufficient that whenever a routine
 * pushes or pops anything on the estack, if the object *might* be
 * an executable file, invoke esfile_clear_cache(); alternatively,
 * immediately after pushing an object, invoke esfile_check_cache().
 */
    ref *current_file;

} exec_stack_t;

/*
 * current_file is cleared by garbage collection, so we don't declare it
 * as a pointer.
 */
#define public_st_exec_stack()	/* in interp.c */\
  gs_public_st_suffix_add0(st_exec_stack, exec_stack_t, "exec_stack_t",\
    exec_stack_enum_ptrs, exec_stack_reloc_ptrs, st_ref_stack)
#define st_exec_stack_num_ptrs st_ref_stack_num_ptrs

#endif /* iesdata_INCLUDED */
