/* Copyright (C) 1989, 1992, 1993, 1994, 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: string_.h,v 1.3 2005/05/02 00:03:33 Arabidopsis Exp $ */
/* Generic substitute for Unix string.h */

#ifndef string__INCLUDED
#  define string__INCLUDED

/* We must include std.h before any file that includes sys/types.h. */
#include "std.h"

#ifdef BSD4_2
#  include <strings.h>
#  define strchr index
#else
#  ifdef MEMORY__NEED_MEMMOVE
#    undef memmove		/* This is disgusting, but so is GCC */
#  endif
#  include <string.h>
#  if defined(THINK_C)
	/* Patch strlen to return a uint rather than a size_t. */
#    define strlen (uint)strlen
#  endif
#  ifdef MEMORY__NEED_MEMMOVE
#    define memmove(dest,src,len) gs_memmove(dest,src,len)
#  endif
#endif

#endif /* string__INCLUDED */
