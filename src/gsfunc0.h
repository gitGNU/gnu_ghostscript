/* Copyright (C) 1997, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsfunc0.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Definitions for FunctionType 0 (Sampled) Functions */

#ifndef gsfunc0_INCLUDED
#  define gsfunc0_INCLUDED

#include "gsfunc.h"
#include "gsdsrc.h"

/* ---------------- Types and structures ---------------- */

/* Define the Function type. */
#define function_type_Sampled 0

/* Define Sampled functions. */
typedef struct gs_function_Sd_params_s {
    gs_function_params_common;
    int Order;			/* 1 or 3, optional */
    gs_data_source_t DataSource;
    int BitsPerSample;		/* 1, 2, 4, 8, 12, 16, 24, 32 */
    const float *Encode;	/* 2 x m, optional */
    const float *Decode;	/* 2 x n, optional */
    const int *Size;		/* m */
} gs_function_Sd_params_t;

#define private_st_function_Sd()	/* in gsfunc.c */\
  gs_private_st_composite(st_function_Sd, gs_function_Sd_t,\
    "gs_function_Sd_t", function_Sd_enum_ptrs, function_Sd_reloc_ptrs)

/* ---------------- Procedures ---------------- */

/* Allocate and initialize a Sampled function. */
int gs_function_Sd_init(P3(gs_function_t ** ppfn,
			   const gs_function_Sd_params_t * params,
			   gs_memory_t * mem));

/* Free the parameters of a Sampled function. */
void gs_function_Sd_free_params(P2(gs_function_Sd_params_t * params,
				   gs_memory_t * mem));

#endif /* gsfunc0_INCLUDED */
