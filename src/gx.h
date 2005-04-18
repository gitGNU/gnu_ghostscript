/* Copyright (C) 1989, 1991, 1994 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gx.h,v 1.3 2005/04/18 12:06:05 Arabidopsis Exp $ */
/* Common internal definitions for Ghostscript library */

#ifndef gx_INCLUDED
#  define gx_INCLUDED

#include "stdio_.h"		/* includes std.h */
#include "gserror.h"
#include "gsio.h"
#include "gstypes.h"
#include "gsmemory.h"
#include "gdebug.h"

#define NEW_TT_INTERPRETER 1
#define TT_GRID_FITTING (NEW_TT_INTERPRETER && 0) /* old code = 0, new code = 1. */
#define FLATTENED_CURVE_ITERATOR 1 /* Old code = 0, new code = 1. */
#define FLATTENED_CURVE_ITERATOR0_COMPATIBLE 1 /* Temporarily used for a backward compatibility. */
#define CURVED_TRAPEZOID_FILL (FLATTENED_CURVE_ITERATOR & 0) /* old code = 0, new code = 1. */

/* Define opaque types for the graphics state. */
/* This is used so pervasively that we define it here, */
/* rather than at a higher level as perhaps would be more appropriate. */
#ifndef gs_imager_state_DEFINED
#  define gs_imager_state_DEFINED
typedef struct gs_imager_state_s gs_imager_state;

#endif
#ifndef gs_state_DEFINED
#  define gs_state_DEFINED
typedef struct gs_state_s gs_state;

#endif

#endif /* gx_INCLUDED */
