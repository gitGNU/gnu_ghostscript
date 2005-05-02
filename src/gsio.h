/* Copyright (C) 1989, 1990, 1993, 1996, 1999, 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsio.h,v 1.3 2005/05/02 00:03:35 Arabidopsis Exp $ */
/* stdio redirection */

#ifndef gsio_INCLUDED
#  define gsio_INCLUDED

/*
 * Define substitutes for stdin/out/err.  Eventually these will always be
 * referenced through an instance structure.
 */
extern FILE *gs_stdio[3];
#define gs_stdin (gs_stdio[0])
#define gs_stdout (gs_stdio[1])
#define gs_stderr (gs_stdio[2])

/*
 * The library and interpreter must never use stdin/out/err directly.
 * Make references to them illegal.
 */
#undef stdin
#define stdin stdin_not_available
#undef stdout
#define stdout stdout_not_available
#undef stderr
#define stderr stderr_not_available

/*
 * Redefine all the relevant stdio functions to reference stdin/out/err
 * explicitly, or to be illegal.
 */
#undef fgetchar
#define fgetchar() Function._fgetchar_.unavailable
#undef fputchar
#define fputchar(c) Function._fputchar_.unavailable
#undef getchar
#define getchar() Function._getchar_.unavailable
#undef gets
#define gets Function._gets_.unavailable
/* We should do something about perror, but since many Unix systems */
/* don't provide the strerror function, we can't.  (No Aladdin-maintained */
/* code uses perror.) */
#undef printf
#define printf Function._printf_.unavailable
#undef putchar
#define putchar(c) Function._putchar_.unavailable
#undef puts
#define puts(s) Function._putchar_.unavailable
#undef scanf
#define scanf Function._scanf_.unavailable
#undef vprintf
#define vprintf Function._vprintf_.unavailable
#undef vscanf
#define vscanf Function._vscanf_.unavailable

#endif /* gsio_INCLUDED */
