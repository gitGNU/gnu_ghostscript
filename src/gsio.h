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

*/

/* $Id: gsio.h,v 1.5 2006/03/08 12:30:26 Arabidopsis Exp $ */
/* stdio redirection */

#ifndef gsio_INCLUDED
#  define gsio_INCLUDED

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
