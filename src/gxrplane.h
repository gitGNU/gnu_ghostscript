/* Copyright (C) 1998 Aladdin Enterprises.  All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 2
  as published by the Free Software Foundation.


  This software is provided AS-IS with no warranty, either express or
  implied. That is, this program is distributed in the hope that it will 
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.
  
  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gxrplane.h,v 1.2 2004/02/14 22:20:18 atai Exp $ */
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
