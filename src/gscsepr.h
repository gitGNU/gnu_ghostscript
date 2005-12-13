/* Copyright (C) 1992, 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gscsepr.h,v 1.4 2005/12/13 16:57:21 jemarch Exp $ */
/* Client interface to Separation color */

#ifndef gscsepr_INCLUDED
#  define gscsepr_INCLUDED

#include "gscspace.h"


/*
 * Separation color spaces.
 *
 * With the implementation of full DeviceN support, the API for creating
 * A Separation color space object has changed.  Separation color spaces
 * are treated as a single component version of a DeviceN color space.
 * The /All separation and the /None separation are the only exceptions.
 * The /All separation and the /None separation is each treated as its own
 * case and thus forms the majority of the remaining Separation color space
 * code.
 *
 * The earlier API which had a multi element cache has been removed.
 * The tint transform procedure now is executed as required and must
 * be executable without doing a call out.
 */
extern int gs_cspace_build_Separation(
					 gs_color_space ** ppcspace,
					 gs_separation_name sname,
					 const gs_color_space * palt_cspace,
					 int cache_size,
					 gs_memory_t * pmem
					 );
/*
 * This routine builds the central part of the Separation color space.
 * It does not allocate a structure for the color space or initialize it.
 */
extern int gs_build_Separation(
				  gs_color_space * pcspace,
				  const gs_color_space * palt_cspace,
				  gs_memory_t * pmem
				  );

/* Set the Separation tint transformation procedure to a Function. */
#ifndef gs_function_DEFINED
typedef struct gs_function_s gs_function_t;
#  define gs_function_DEFINED
#endif
int gs_cspace_set_sepr_proc(gs_color_space * pcspace,
			int (*proc)(const float *,
				    float *,
				    const gs_imager_state *,
				    void *
				    ),
			void *proc_data
			);
/*
 * Set the Separation tint transformation procedure to a Function.
 */
int gs_cspace_set_sepr_function(const gs_color_space *pcspace,
				    gs_function_t *pfn);
/*
 * If the Separation tint transformation procedure is a Function,
 * return the function object, otherwise return 0.
 */
gs_function_t *gs_cspace_get_sepr_function(const gs_color_space *pcspace);

#endif /* gscsepr_INCLUDED */
