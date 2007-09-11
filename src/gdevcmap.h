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
/* $Id: gdevcmap.h,v 1.7 2007/09/11 15:23:45 Arabidopsis Exp $ */
/* Interface to special color mapping device */

#ifndef gdevcmap_INCLUDED
#  define gdevcmap_INCLUDED

/* Define the color mapping algorithms. */
typedef enum {

    /* Don't change the color. */

    device_cmap_identity = 0,

    /* Snap each RGB primary component to 0 or 1 individually. */

    device_cmap_snap_to_primaries,

    /* Snap black to white, other colors to black. */

    device_cmap_color_to_black_over_white,

    /* Convert to a gray shade of the correct brightness. */

    device_cmap_monochrome

} gx_device_color_mapping_method_t;

#define device_cmap_max_method device_cmap_monochrome

/* Define the color mapping forwarding device. */
typedef struct gx_device_cmap_s {
    gx_device_forward_common;
    gx_device_color_mapping_method_t mapping_method;
} gx_device_cmap;

extern_st(st_device_cmap);
#define public_st_device_cmap()	/* in gdevcmap.c */\
  gs_public_st_suffix_add0_final(st_device_cmap, gx_device_cmap,\
    "gx_device_cmap", device_cmap_enum_ptrs, device_cmap_reloc_ptrs,\
    gx_device_finalize, st_device_forward)

/* Initialize a color mapping device.  Do this just once after allocation. */
int gdev_cmap_init(gx_device_cmap * dev, gx_device * target,
		   gx_device_color_mapping_method_t mapping_method);

/*
 * Clients can change the color mapping method at any time by setting
 * the ColorMappingMethod device parameter, but they must then call
 *	gs_setdevice_no_init(pgs, dev);
 * for each graphics state that may reference the device.
 */

#endif /* gdevcmap_INCLUDED */
