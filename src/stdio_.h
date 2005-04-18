/* Copyright (C) 1992, 1993, 1994, 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: stdio_.h,v 1.3 2005/04/18 12:06:04 Arabidopsis Exp $ */
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
int unlink(const char *);
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

#if defined(_MSC_VER)
#  define fdopen(handle,mode) _fdopen(handle,mode)
#  define fileno(file) _fileno(file)
#endif

#endif /* stdio__INCLUDED */
