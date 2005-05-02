/* Copyright (C) 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: fcntl_.h,v 1.3 2005/05/02 00:03:34 Arabidopsis Exp $ */
/* Declaration of the O_* flags for open */

#ifndef fcntl__INCLUDED
#  define fcntl__INCLUDED

/*
 * This absurd little file is needed because Microsoft C, in defiance
 * of multiple standards, does not define the O_ modes for 'open'.
 */

/*
 * We must include std.h before any file that includes (or might include)
 * sys/types.h.
 */
#include "std.h"
#include <fcntl.h>

#if !defined(O_APPEND) && defined(_O_APPEND)
#  define O_APPEND _O_APPEND
#endif
#if !defined(O_BINARY) && defined(_O_BINARY)
#  define O_BINARY _O_BINARY
#endif
#if !defined(O_CREAT) && defined(_O_CREAT)
#  define O_CREAT _O_CREAT
#endif
#if !defined(O_EXCL) && defined(_O_EXCL)
#  define O_EXCL _O_EXCL
#endif
#if !defined(O_RDONLY) && defined(_O_RDONLY)
#  define O_RDONLY _O_RDONLY
#endif
#if !defined(O_RDWR) && defined(_O_RDWR)
#  define O_RDWR _O_RDWR
#endif
#if !defined(O_TRUNC) && defined(_O_TRUNC)
#  define O_TRUNC _O_TRUNC
#endif
#if !defined(O_WRONLY) && defined(_O_WRONLY)
#  define O_WRONLY _O_WRONLY
#endif

#endif /* fcntl__INCLUDED */
