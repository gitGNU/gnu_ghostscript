/* Copyright (C) 1997, 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxfunc.h,v 1.1 2004/01/14 16:59:51 atai Exp $ */
/* Internal definitions for Functions */

#ifndef gxfunc_INCLUDED
#  define gxfunc_INCLUDED

#include "gsfunc.h"
#include "gsstruct.h"

/* ---------------- Types and structures ---------------- */

/* Define the generic Function structure type.  This is never instantiated. */
extern_st(st_function);
#define public_st_function()	/* in gsfunc.c */\
  gs_public_st_ptrs2(st_function, gs_function_t, "gs_function_t",\
    function_enum_ptrs, function_reloc_ptrs, params.Domain, params.Range)

/* ---------------- Internal procedures ---------------- */

/* Generic free_params implementation. */
void fn_common_free_params(P2(gs_function_params_t * params, gs_memory_t * mem));

/* Generic free implementation. */
void fn_common_free(P3(gs_function_t * pfn, bool free_params, gs_memory_t * mem));

/* Check the values of m, n, Domain, and (if supplied) Range. */
int fn_check_mnDR(P3(const gs_function_params_t * params, int m, int n));

/* Get the monotonicity of a function over its Domain. */
int fn_domain_is_monotonic(P2(const gs_function_t *pfn,
			      gs_function_effort_t effort));

/* Generic get_info implementation (no Functions or DataSource). */
FN_GET_INFO_PROC(gs_function_get_info_default);

/* Write generic parameters (FunctionType, Domain, Range) on a parameter list. */
int fn_common_get_params(P2(const gs_function_t *pfn, gs_param_list *plist));

#endif /* gxfunc_INCLUDED */
