/* Copyright (C) 1997 artofcode LLC.  All rights reserved.
  
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

/*$Id: gscompt.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Abstract types for compositing objects */

#ifndef gscompt_INCLUDED
#  define gscompt_INCLUDED

/*
 * Compositing is the next-to-last step in the rendering pipeline.
 * It occurs after color correction but before halftoning (if needed).
 *
 * gs_composite_t is the abstract superclass for compositing functions such
 * as RasterOp functions or alpha-based compositing.  Concrete subclasses
 * must provide a default implementation (presumably based on
 * get_bits_rectangle and copy_color) for devices that provide no optimized
 * implementation of their own.
 *
 * A client that wants to produce composited output asks the target device
 * to create an appropriate compositing device based on the target device
 * and the gs_composite_t (and possibly other elements of the imager state).
 * If the target device doesn't have its own implementation for the
 * requested function, format, and state, it passes the buck to the
 * gs_composite_t, which may make further tests for special cases before
 * creating and returning a compositing device that uses the default
 * implementation.
 */
typedef struct gs_composite_s gs_composite_t;

/*
 * To enable fast cache lookup and equality testing, compositing functions,
 * like halftones, black generation functions, etc., carry a unique ID (time
 * stamp).
 */
gs_id gs_composite_id(P1(const gs_composite_t * pcte));

#endif /* gscompt_INCLUDED */
