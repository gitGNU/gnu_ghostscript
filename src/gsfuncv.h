/* Copyright (C) 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsfuncv.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Definitions for "Vanilla" Functions */

#ifndef gsfuncv_INCLUDED
#  define gsfuncv_INCLUDED

#include "gsfunc.h"

/*
 * The simplest type of Function, "Vanilla" Functions just store closure
 * data.  The client provides the evaluation procedure.
 */

/* ---------------- Types and structures ---------------- */

#define function_type_Vanilla (-1)

typedef struct gs_function_Va_params_s {
    gs_function_params_common;
    fn_evaluate_proc_t eval_proc;
    void *eval_data;
    int is_monotonic;
} gs_function_Va_params_t;

typedef struct gs_function_Va_s {
    gs_function_head_t head;
    gs_function_Va_params_t params;
} gs_function_Va_t;

#define private_st_function_Va()	/* in gsfunc.c */\
  gs_private_st_suffix_add1(st_function_Va, gs_function_Va_t,\
    "gs_function_Va_t", function_Va_enum_ptrs, function_Va_reloc_ptrs,\
    st_function, params.eval_data)

/* ---------------- Procedures ---------------- */

/* Allocate and initialize a Vanilla function. */
int gs_function_Va_init(P3(gs_function_t ** ppfn,
			   const gs_function_Va_params_t * params,
			   gs_memory_t * mem));

/* Free the parameters of a Vanilla function. */
void gs_function_Va_free_params(P2(gs_function_Va_params_t * params,
				   gs_memory_t * mem));

#endif /* gsfuncv_INCLUDED */
