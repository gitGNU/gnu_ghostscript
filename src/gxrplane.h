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

/* $Id: gxrplane.h,v 1.4 2005/12/13 16:57:24 jemarch Exp $ */
/* Definitions for planar rendering */

#ifndef gxrplane_INCLUDED
#  define gxrplane_INCLUDED

#ifndef gx_device_DEFINED
#  define gx_device_DEFINED
typedef struct gx_device_s gx_device;
#endif

/*
 * Define the parameters for extracting a single plane from chunky pixels.
 * This structure should be considered opaque, and should only be
 * initialized with the procedure.
 */
typedef struct gx_render_plane_s {
    int depth;
    int shift;			/* bit position of l.s.b. from low end */
    int index;			/* index within multi-screen halftone */
} gx_render_plane_t;

/*
 * Initialize a rendering plane specification for a device.  Note that it is
 * up to the device to decide which bits constitute a given plane identified
 * by index.  (Currently this is done with a fixed procedure, but eventually
 * it will be made a property of the device somehow, perhaps in the
 * color_info.)
 */
int gx_render_plane_init(gx_render_plane_t *render_plane,
			 const gx_device *dev, int index);

#endif /* gxrplane_INCLUDED */
