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

/*$Id: gdevmrun.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Definition of run-length encoded memory device */

#ifndef gdevmrun_INCLUDED
#  define gdevmrun_INCLUDED

/*
 * This memory device stores full-size pixels with run-length
 * encoding if possible, switching to the standard uncompressed
 * representation if necessary.
 */

#include "gxdevmem.h"

/*
 * Define the device, built on a memory device.
 */
typedef struct gx_device_run_s {
    gx_device_memory md;	/* must be first */
    uint runs_per_line;
    int umin, umax1;		/* some range of uninitialized lines */
    int smin, smax1;		/* some range in standard (not run) form */
    /*
     * Save memory device procedures that we replace with run-oriented
     * ones, for use with the uncompressed representation.
     */
    struct sp_ {
	dev_proc_copy_mono((*copy_mono));
	dev_proc_copy_color((*copy_color));
	dev_proc_fill_rectangle((*fill_rectangle));
	dev_proc_copy_alpha((*copy_alpha));
	dev_proc_strip_tile_rectangle((*strip_tile_rectangle));
	dev_proc_strip_copy_rop((*strip_copy_rop));
	dev_proc_get_bits_rectangle((*get_bits_rectangle));
    } save_procs;
} gx_device_run;

/*
 * Convert a memory device to run-length form.  The mdev argument should be
 * const, but it isn't because we need to call gx_device_white.
 */
int gdev_run_from_mem(P2(gx_device_run *rdev, gx_device_memory *mdev));

#endif /* gdevmrun_INCLUDED */
