/* Copyright (C) 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gscdevn.h,v 1.2 2004/02/14 22:20:17 atai Exp $ */
/* Client interface to DeviceN color */

#ifndef gscdevn_INCLUDED
#  define gscdevn_INCLUDED

#include "gscspace.h"

/*
 * Fill in a DeviceN color space.  Does not include allocation
 * and initialization of the color space.
 * Note that the client is responsible for memory management of the
 * tint transform Function.
 */
int gs_build_DeviceN(
			gs_color_space *pcspace,
			uint num_components,
			const gs_color_space *palt_cspace,
			gs_memory_t *pmem
			);
/*
 * Allocate and fill in a DeviceN color space.
 * Note that the client is responsible for memory management of the
 * tint transform Function.
 */
int gs_cspace_build_DeviceN(
			       gs_color_space **ppcspace,
			       gs_separation_name *psnames,
			       uint num_components,
			       const gs_color_space *palt_cspace,
			       gs_memory_t *pmem
			       );

/* Set the tint transformation procedure for a DeviceN color space. */
/* VMS limits procedure names to 31 characters, and some systems only */
/* compare the first 23 characters. */
extern int gs_cspace_set_devn_proc(
				      gs_color_space * pcspace,
			int (*proc)(const float *,
				       float *,
				       const gs_imager_state *,
				       void *
				      ),
				      void *proc_data
				      );

/* Set the DeviceN tint transformation procedure to a Function. */
#ifndef gs_function_DEFINED
typedef struct gs_function_s gs_function_t;
#  define gs_function_DEFINED
#endif
int gs_cspace_set_devn_function(gs_color_space *pcspace,
				   gs_function_t *pfn);

/*
 * If the DeviceN tint transformation procedure is a Function,
 * return the function object, otherwise return 0.
 */
gs_function_t *gs_cspace_get_devn_function(const gs_color_space *pcspace);

/* Map a DeviceN color using a Function. */
int map_devn_using_function(const float *in, float *out,
			const gs_imager_state *pis, void *data);

#endif /* gscdevn_INCLUDED */
