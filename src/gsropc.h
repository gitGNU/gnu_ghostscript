/* Copyright (C) 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsropc.h,v 1.4 2005/12/13 16:57:23 jemarch Exp $ */
/* RasterOp-compositing interface */

#ifndef gsropc_INCLUDED
#  define gsropc_INCLUDED

#include "gscompt.h"
#include "gsropt.h"

/*
 * Define parameters for RasterOp-compositing.
 * There are two kinds of RasterOp compositing operations.
 * If texture == 0, the input data are the texture, and the source is
 * implicitly all 0 (black).  If texture != 0, it defines the texture,
 * and the input data are the source.  Note that in the latter case,
 * the client (the caller of gs_create_composite_rop) promises that
 * *texture will not change.
 */

#ifndef gx_device_color_DEFINED
#  define gx_device_color_DEFINED
typedef struct gx_device_color_s gx_device_color;

#endif

typedef struct gs_composite_rop_params_s {
    gs_logical_operation_t log_op;
    const gx_device_color *texture;
} gs_composite_rop_params_t;

/* Create a RasterOp-compositing object. */
int gs_create_composite_rop(gs_composite_t ** ppcte,
			    const gs_composite_rop_params_t * params,
			    gs_memory_t * mem);

#endif /* gsropc_INCLUDED */
