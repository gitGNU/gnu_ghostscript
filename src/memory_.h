/* Copyright (C) 1989, 1992, 1993, 1994, 1997, 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: memory_.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Generic substitute for Unix memory.h */

#ifndef memory__INCLUDED
#  define memory__INCLUDED

/* We must include std.h before any file that includes sys/types.h. */
#include "std.h"

/******
 ****** Note: the System V bcmp routine only returns zero or non-zero,
 ****** unlike memcmp which returns -1, 0, or 1.
 ******/

#ifdef __TURBOC__
/* Define inline functions */
#  ifdef __WIN32__
#    define memcmp_inline(b1,b2,len) memcmp(b1,b2,len)
#  else
#    define memcmp_inline(b1,b2,len) __memcmp__(b1,b2,len)
#  endif
#  include <mem.h>
#else
	/* Not Turbo C, no inline functions */
#  define memcmp_inline(b1,b2,len) memcmp(b1,b2,len)
	/*
	 * Apparently the newer VMS compilers include prototypes
	 * for the mem... routines in <string.h>.  Unfortunately,
	 * gcc lies on Sun systems: it defines __STDC__ even if
	 * the header files in /usr/include are broken.
	 * However, Solaris systems, which define __svr4__, do have
	 * correct header files.
	 */
	/*
	 * The exceptions vastly outnumber the BSD4_2 "rule":
	 * these tests should be the other way around....
	 */
#  if defined(VMS) || defined(_POSIX_SOURCE) || (defined(__STDC__) && (!defined(sun) || defined(__svr4__))) || defined(_HPUX_SOURCE) || defined(__WATCOMC__) || defined(THINK_C) || defined(bsdi) || defined(__FreeBSD) || (defined(_MSC_VER) && _MSC_VER >= 1000)
#    include <string.h>
#  else
#    if defined(BSD4_2) || defined(UTEK)
extern bcopy(), bcmp(), bzero();

#	 define memcpy(dest,src,len) bcopy(src,dest,len)
#	 define memcmp(b1,b2,len) bcmp(b1,b2,len)
	 /* Define our own versions of missing routines (in gsmisc.c). */
#	 define MEMORY__NEED_MEMMOVE
#        include <sys/types.h>	/* for size_t */
#	 define MEMORY__NEED_MEMSET
#	 if defined(UTEK)
#          define MEMORY__NEED_MEMCHR
#        endif			/* UTEK */
#    else
#      include <memory.h>
#      if defined(__SVR3) || defined(sun)	/* Not sure this is right.... */
#	 define MEMORY__NEED_MEMMOVE
#        include <sys/types.h>	/* for size_t */
#      endif			/* __SVR3 or sun */
#    endif			/* BSD4_2 or UTEK */
#  endif			/* VMS, POSIX, ... */
#endif /* !__TURBOC__ */

/*
 * If we are profiling, substitute our own versions of memset, memcpy,
 * and memmove, in case profiling libraries aren't available.
 */
#ifdef PROFILE
#  define MEMORY__NEED_MEMCPY
#  define MEMORY__NEED_MEMMOVE
#  define MEMORY__NEED_MEMSET
#endif

/* Declare substitutes for library procedures we supply. */
#ifdef MEMORY__NEED_MEMMOVE
#  define memmove(dest,src,len) gs_memmove(dest,src,len)
void *gs_memmove(P3(void *, const void *, size_t));
#endif
#ifdef MEMORY__NEED_MEMCPY
#  define memcpy(dest,src,len) gs_memcpy(dest,src,len)
void *gs_memcpy(P3(void *, const void *, size_t));
#endif
#ifdef MEMORY__NEED_MEMSET
#  define memset(dest,ch,len) gs_memset(dest,ch,len)
void *gs_memset(P3(void *, int, size_t));
#endif
#ifdef MEMORY__NEED_MEMCHR
#  define memchr(ptr,ch,len) gs_memchr(ptr,ch,len)
void *gs_memchr(P3(const void *, int, size_t));
#endif



#endif /* memory__INCLUDED */
