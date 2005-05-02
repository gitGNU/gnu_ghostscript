/* Copyright (C) 1994-7 artofcode LLC.  All rights reserved.
  
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

/* $Id: macsystypes.h,v 1.4 2005/05/02 00:03:23 Arabidopsis Exp $ */

#ifndef __sys_types_h__
#define __sys_types_h__

#include <MacTypes.h>
#include <unix.h>
#define CHECK_INTERRUPTS

/* use a 64 bit type for color vectors. (from MacTypes.h)
   this is important for devicen support, but can be safely
   undef'd to fallback to a 32 bit representation  */
#define GX_COLOR_INDEX_TYPE UInt64

#define main gs_main

#if (0)
#define fprintf myfprintf
#define fputs myfputs
#define getenv mygetenv
int myfprintf(FILE *file, const char *fmt, ...);
int myfputs(const char *string, FILE *file);
#endif

/* Metrowerks CodeWarrior should define this */
#ifndef __MACOS__
#define __MACOS__
#endif

#endif /* __sys_types_h__ */
