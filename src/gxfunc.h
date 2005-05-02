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

/* $Id: gxfunc.h,v 1.4 2005/05/02 00:03:34 Arabidopsis Exp $ */
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
void fn_common_free_params(gs_function_params_t * params, gs_memory_t * mem);

/* Generic free implementation. */
void fn_common_free(gs_function_t * pfn, bool free_params, gs_memory_t * mem);

/* Check the values of m, n, Domain, and (if supplied) Range. */
int fn_check_mnDR(const gs_function_params_t * params, int m, int n);

/* Get the monotonicity of a function over its Domain. */
int fn_domain_is_monotonic(const gs_function_t *pfn,
			   gs_function_effort_t effort);

/* Generic get_info implementation (no Functions or DataSource). */
FN_GET_INFO_PROC(gs_function_get_info_default);

/*
 * Write generic parameters (FunctionType, Domain, Range) on a parameter list.
 */
int fn_common_get_params(const gs_function_t *pfn, gs_param_list *plist);

/*
 * Copy an array of numeric values when scaling a function.
 */
void *fn_copy_values(const void *pvalues, int count, int size,
		     gs_memory_t *mem);

/*
 * If necessary, scale the Range or Decode array for fn_make_scaled.
 * Note that we must always allocate a new array.
 */
int fn_scale_pairs(const float **ppvalues, const float *pvalues, int npairs,
		   const gs_range_t *pranges, gs_memory_t *mem);

/*
 * Scale the generic part of a function (Domain and Range).
 * The client must have copied the parameters already.
 */
int fn_common_scale(gs_function_t *psfn, const gs_function_t *pfn,
		    const gs_range_t *pranges, gs_memory_t *mem);

/* Serialize. */
int fn_common_serialize(const gs_function_t * pfn, stream *s);

#endif /* gxfunc_INCLUDED */
