/* Copyright (C) 1991, 1995, 1997, 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: time_.h,v 1.1 2004/01/14 16:59:53 atai Exp $ */
/* Generic substitute for Unix sys/time.h */

#ifndef time__INCLUDED
#  define time__INCLUDED

/* We must include std.h before any file that includes sys/types.h. */
#include "std.h"

/*
 * The location (or existence) of certain system headers is
 * environment-dependent. We detect this in the makefile
 * and conditionally define switches in gconfig_.h.
 */
#include "gconfig_.h"

/*
 * Some System V environments don't include sys/time.h.
 * The HAVE_SYS_TIME_H switch in gconfig_.h reflects this.
 */
#ifdef HAVE_SYS_TIME_H
#  include <sys/time.h>
#  if defined(Plan9) || defined(M_UNIX) || defined(_IBMR2) || defined(_SEQUENT_) || defined(__GNUC__)
     /* Plan 9, SCO, AIX and Sequent's DYNIX/ptx need both time.h and
        sys/time.h! As of version 2.2, at least some glibc
        installations also require both files. */
#    include <time.h>
#  endif
#else
#  include <time.h>
#  if !defined(__DECC) && !defined(__MWERKS__)
struct timeval {
    long tv_sec, tv_usec;
};
#  endif
struct timezone {
    int tz_minuteswest, tz_dsttime;
};

#endif

#if defined(ultrix) && defined(mips)
/*
 * Apparently some versions of Ultrix for the DECstation include
 * time_t in sys/time.h, and some don't.  If you get errors
 * compiling gp_unix.c, uncomment the next line.
 */
/*      typedef int     time_t; */
#endif

/*
 * In SVR4.0 (but not other System V implementations),
 * gettimeofday doesn't take a timezone argument.
 */
#ifdef SVR4_0
#  define gettimeofday_no_timezone 1
#else
#  define gettimeofday_no_timezone 0
#endif

/* Some System V environments, and Posix environments, need <sys/times.h>. */
#ifdef HAVE_SYS_TIMES_H
#  include <sys/times.h>
#  define use_times_for_usertime 1
		/* Posix 1003.1b-1993 section 4.8.1.5 says that
		   CLK_TCK is obsolescent and that sysconf(_SC_CLK_TCK)
		   should be used instead, but this requires including
		   <unistd.h>, which is too painful to configure.  */
#  ifndef CLK_TCK
#    define CLK_TCK 100		/* guess for older hosts */
#  endif
#else
#  define use_times_for_usertime 0
#endif

#endif /* time__INCLUDED */
