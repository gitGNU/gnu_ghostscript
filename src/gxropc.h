/* Copyright (C) 2001-2006 Artifex Software, Inc.
   All Rights Reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or
  modify it under the terms of the version 2 of the GNU General Public
  License as published by the Free Software Foundation.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

/* $Id: gxropc.h,v 1.7 2007/09/11 15:24:10 Arabidopsis Exp $ */
/* Internals for RasterOp compositing */

#ifndef gxropc_INCLUDED
#  define gxropc_INCLUDED

#include "gsropc.h"
#include "gxcomp.h"

/* Define RasterOp-compositing objects. */
typedef struct gs_composite_rop_s {
    gs_composite_common;
    gs_composite_rop_params_t params;
} gs_composite_rop_t;

#define private_st_composite_rop() /* in gsropc.c */\
  gs_private_st_ptrs1(st_composite_rop, gs_composite_rop_t,\
    "gs_composite_rop_t", composite_rop_enum_ptrs, composite_rop_reloc_ptrs,\
    params.texture)

/*
 * Initialize a RasterOp compositing function from parameters.
 * We make this visible so that clients can allocate gs_composite_rop_t
 * objects on the stack, to reduce memory manager overhead.
 */
void gx_init_composite_rop(gs_composite_rop_t * pcte,
			   const gs_composite_rop_params_t * params);

#endif /* gxropc_INCLUDED */
