/* Copyright (C) 1992, 1993, 1994, 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: stdio_.h,v 1.1 2004/01/14 16:59:53 atai Exp $ */
/* Generic substitute for stdio.h */

#ifndef stdio__INCLUDED
#  define stdio__INCLUDED

/*
 * This is here primarily because we must include std.h before
 * any file that includes sys/types.h.
 */
#include "std.h"
#include <stdio.h>

#ifdef VMS
/* VMS prior to 7.0 doesn't have the unlink system call.  Use delete instead. */
#  ifdef __DECC
#    include <unixio.h>
#  endif
#  if ( __VMS_VER < 70000000 )
#    define unlink(fname) delete(fname)
#  endif
#else
#if !defined(const)
/*
 * Other systems may or may not declare unlink in stdio.h;
 * if they do, the declaration will be compatible with this one, as long
 * as const has not been disabled by defining it to be the empty string.
 */
int unlink(P1(const char *));
#endif

#endif

/*
 * Plan 9 has a system function called sclose, which interferes with the
 * procedure defined in stream.h.  The following makes the system sclose
 * inaccessible, but avoids the name clash.
 */
#ifdef Plan9
#  undef sclose
#  define sclose(s) Sclose(s)
#endif

/* Patch a couple of things possibly missing from stdio.h. */
#ifndef SEEK_SET
#  define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#  define SEEK_CUR 1
#endif
#ifndef SEEK_END
#  define SEEK_END 2
#endif

#endif /* stdio__INCLUDED */
