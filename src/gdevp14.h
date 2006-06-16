/* Copyright (C) 2001 artofcode LLC.  All rights reserved.
  
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

/* $Id: gdevp14.h,v 1.5 2006/06/16 16:03:35 Arabidopsis Exp $ */
/* Definitions and interface for PDF 1.4 rendering device */

#ifndef gdevp14_INCLUDED
#  define gdevp14_INCLUDED

typedef enum {
    DeviceGray = 0,
    DeviceRGB = 1,
    DeviceCMYK = 2
} pdf14_default_colorspace_t;

typedef struct pdf14_buf_s pdf14_buf;
typedef struct pdf14_ctx_s pdf14_ctx;

struct pdf14_buf_s {
    pdf14_buf *saved;

    bool isolated;
    bool knockout;
    byte alpha;
    byte shape;
    gs_blend_mode_t blend_mode;

    bool has_alpha_g;
    bool has_shape;

    gs_int_rect rect;
    /* Note: the traditional GS name for rowstride is "raster" */

    /* Data is stored in planar format. Order of planes is: pixel values,
       alpha, shape if present, alpha_g if present. */

    int rowstride;
    int planestride;
    int n_chan; /* number of pixel planes including alpha */
    int n_planes; /* total number of planes including alpha, shape, alpha_g */
    byte *data;

    byte *transfer_fn;

    gs_int_rect bbox;
};

struct pdf14_ctx_s {
    pdf14_buf *stack;
    pdf14_buf *maskbuf;
    gs_memory_t *memory;
    gs_int_rect rect;
    bool additive;
    int n_chan;
};

typedef struct pdf14_device_s {
    gx_device_forward_common;

    pdf14_ctx *ctx;
    float opacity;
    float shape;
    float alpha; /* alpha = opacity * shape */
    gs_blend_mode_t blend_mode;
    const gx_color_map_procs *(*save_get_cmap_procs)(const gs_imager_state *,
						     const gx_device *);
    gx_device_color_info saved_clist_color_info;
} pdf14_device;

int gs_pdf14_device_push(gs_memory_t *mem, gs_imager_state * pis,
		gx_device * * pdev, gx_device * target);

int send_pdf14trans(gs_imager_state * pis, gx_device * dev,
    gx_device * * pcdev, gs_pdf14trans_params_t * pparams, gs_memory_t * mem);

#endif /* gdevp14_INCLUDED */
