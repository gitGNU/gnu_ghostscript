/* Copyright (C) 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsfuncv.c,v 1.2 2005/05/02 00:03:24 Arabidopsis Exp $ */
/* "Vanilla" Function support */
#include "gx.h"
#include "gserrors.h"
#include "gsfuncv.h"
#include "gsparam.h"
#include "gxfunc.h"

/* GC descriptor */
private_st_function_Va();

/*
 * Test whether a Vanilla function is monotonic.  (This information is
 * provided at function definition time.)
 */
private int
fn_Va_is_monotonic(const gs_function_t * pfn_common,
		   const float *lower, const float *upper,
		   gs_function_effort_t effort)
{
    const gs_function_Va_t *const pfn =
	(const gs_function_Va_t *)pfn_common;

    return pfn->params.is_monotonic;
}

/* Free the parameters of a Vanilla function. */
void
gs_function_Va_free_params(gs_function_Va_params_t * params,
			   gs_memory_t * mem)
{
    gs_free_object(mem, params->eval_data, "eval_data");
    fn_common_free_params((gs_function_params_t *) params, mem);
}

/* Allocate and initialize a Vanilla function. */
int
gs_function_Va_init(gs_function_t ** ppfn,
		    const gs_function_Va_params_t * params,
		    gs_memory_t * mem)
{
    static const gs_function_head_t function_Va_head = {
	function_type_Vanilla,
	{
	    NULL,			/* filled in from params */
	    (fn_is_monotonic_proc_t) fn_Va_is_monotonic,
	    gs_function_get_info_default,
	    fn_common_get_params,	/****** WHAT TO DO ABOUT THIS? ******/
	    (fn_free_params_proc_t) gs_function_Va_free_params,
	    fn_common_free
	}
    };
    int code;

    *ppfn = 0;			/* in case of error */
    code = fn_check_mnDR((const gs_function_params_t *)params, 1, params->n);
    if (code < 0)
	return code;
    {
	gs_function_Va_t *pfn =
	    gs_alloc_struct(mem, gs_function_Va_t, &st_function_Va,
			    "gs_function_Va_init");

	if (pfn == 0)
	    return_error(gs_error_VMerror);
	pfn->params = *params;
	pfn->head = function_Va_head;
	pfn->head.procs.evaluate = params->eval_proc;
	pfn->head.is_monotonic = params->is_monotonic;
	*ppfn = (gs_function_t *) pfn;
    }
    return 0;
}
