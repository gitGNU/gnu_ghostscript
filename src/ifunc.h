/* Copyright (C) 1997, 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: ifunc.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Internal interpreter interfaces for Functions */

#ifndef ifunc_INCLUDED
#  define ifunc_INCLUDED

#include "gsfunc.h"

/* Define build procedures for the various function types. */
#define build_function_proc(proc)\
  int proc(P6(i_ctx_t *i_ctx_p, const ref *op, const gs_function_params_t *params, int depth,\
	      gs_function_t **ppfn, gs_memory_t *mem))
typedef build_function_proc((*build_function_proc_t));

/* Define the table of build procedures, indexed by FunctionType. */
typedef struct build_function_type_s {
    int type;
    build_function_proc_t proc;
} build_function_type_t;
extern const build_function_type_t build_function_type_table[];
extern const uint build_function_type_table_count;

/* Build a function structure from a PostScript dictionary. */
int fn_build_function(P4(i_ctx_t *i_ctx_p, const ref * op, gs_function_t ** ppfn,
			 gs_memory_t *mem));
int fn_build_sub_function(P5(i_ctx_t *i_ctx_p, const ref * op, gs_function_t ** ppfn,
			     int depth, gs_memory_t *mem));

/* Allocate an array of function objects. */
int alloc_function_array(P3(uint count, gs_function_t *** pFunctions,
			    gs_memory_t *mem));

/*
 * Collect a heap-allocated array of floats.  If the key is missing, set
 * *pparray = 0 and return 0; otherwise set *pparray and return the number
 * of elements.  Note that 0-length arrays are acceptable, so if the value
 * returned is 0, the caller must check whether *pparray == 0.
 */
int fn_build_float_array(P6(const ref * op, const char *kstr, bool required,
			    bool even, const float **pparray,
			    gs_memory_t *mem));

/*
 * If a PostScript object is a Function procedure, return the function
 * object, otherwise return 0.
 */
gs_function_t *ref_function(P1(const ref *op));

/*
 * Operator to execute a function.
 * <in1> ... <function_struct> %execfunction <out1> ...
 */
int zexecfunction(P1(i_ctx_t *));

#endif /* ifunc_INCLUDED */
