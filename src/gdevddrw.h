/* Copyright (C) 2002 artofcode LLC. All rights reserved.
  
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

/* $Id: gdevddrw.h,v 1.5 2006/03/08 12:30:24 Arabidopsis Exp $ */
/* Prototypes of some polygon and image drawing procedures */

#ifndef gdevddrw_INCLUDED
#  define gdevddrw_INCLUDED

enum fill_trap_flags {
    ftf_peak0 = 1,
    ftf_peak1 = 2,
    ftf_pseudo_rasterization = 4
};

int gx_fill_trapezoid_cf_fd(gx_device * dev, const gs_fixed_edge * left,
    const gs_fixed_edge * right, fixed ybot, fixed ytop, int flags,
    const gx_device_color * pdevc, gs_logical_operation_t lop);
int gx_fill_trapezoid_cf_nd(gx_device * dev, const gs_fixed_edge * left,
    const gs_fixed_edge * right, fixed ybot, fixed ytop, int flags,
    const gx_device_color * pdevc, gs_logical_operation_t lop);

#endif /* gdevddrw_INCLUDED */

