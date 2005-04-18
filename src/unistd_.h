/* Copyright (C) 2000, 2001 Artifex Software, Inc. All rights reserved.
  
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

/* $Id: unistd_.h,v 1.3 2005/04/18 12:05:59 Arabidopsis Exp $ */
/* Generic substitute for Unix unistd.h */

#ifndef unistd__INCLUDED
#  define unistd__INCLUDED

/* We must include std.h before any file that includes sys/types.h. */
#include "std.h"

/*
 * It's likely that you will have to edit the next lines on some Unix
 * and most non-Unix platforms, since there is no standard (ANSI or
 * otherwise) for where to find these definitions.
 */

#ifdef __OS2__
#  include <io.h>
#endif
#ifdef __WIN32__
#  include <io.h>
#endif

#if defined(_MSC_VER) 
#  define fsync(handle) _commit(handle)
#  define read(fd, buf, len) _read(fd, buf, len)
#  define isatty(fd) _isatty(fd)
#  define setmode(fd, mode) _setmode(fd, mode)
#  define fstat(fd, buf) _fstat(fd, buf)
#  define dup(fd) _dup(fd)
#  define open(fname, flags, mode) _open(fname, flags, mode)
#  define close(fd) _close(fd)
#elif defined(__BORLANDC__) && defined(__WIN32__) 
#  define fsync(handle) _commit(handle)
#  define read(fd, buf, len) _read(fd, buf, len)
#  define isatty(fd) _isatty(fd)
#  define setmode(fd, mode) _setmode(fd, mode)
#else
#  include <unistd.h>
#endif

#endif   /* unistd__INCLUDED */

