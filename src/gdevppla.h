/* Copyright (C) 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: gdevppla.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Support for printer devices with planar buffering. */
/* Requires gdevprn.h */

#ifndef gdevppla_INCLUDED
#  define gdevppla_INCLUDED

/* Set the buf_procs in a printer device to planar mode. */
int gdev_prn_set_procs_planar(P1(gx_device *pdev));

/* Open a printer device, conditionally setting it to be planar. */
int gdev_prn_open_planar(P2(gx_device *pdev, bool upb));

/* Augment get/put_params to add UsePlanarBuffer. */
int gdev_prn_get_params_planar(P3(gx_device * pdev, gs_param_list * plist,
				  bool *pupb));
int gdev_prn_put_params_planar(P3(gx_device * pdev, gs_param_list * plist,
				  bool *pupb));

/* Create a planar buffer device. */
/* Use this instead of the default if UsePlanarBuffer is true. */
int gdev_prn_create_buf_planar(P5(gx_device **pbdev, gx_device *target,
				  const gx_render_plane_t *render_plane,
				  gs_memory_t *mem, bool for_band));

/* Determine the space needed by a planar buffer device. */
/* Use this instead of the default if UsePlanarBuffer is true. */
int gdev_prn_size_buf_planar(P5(gx_device_buf_space_t *space,
				gx_device *target,
				const gx_render_plane_t *render_plane,
				int height, bool for_band));

#endif /* gdevppla_INCLUDED */
