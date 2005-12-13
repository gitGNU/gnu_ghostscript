/* Copyright (C) 1997, 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: pipe_.h,v 1.4 2005/12/13 16:57:27 jemarch Exp $ */
/* Declaration of popen and pclose */

#ifndef pipe__INCLUDED
#  define pipe__INCLUDED

#include "stdio_.h"

#ifdef __WIN32__
/*
 * MS Windows has popen and pclose in stdio.h, but under different names.
 * Unfortunately MSVC5 and 6 have a broken implementation of _popen, 
 * so we use own.  Our implementation only supports mode "wb".
 */
extern FILE *mswin_popen(const char *cmd, const char *mode);
#  define popen(cmd, mode) mswin_popen(cmd, mode)
/* #  define popen(cmd, mode) _popen(cmd, mode) */
#  define pclose(file) _pclose(file)
#else  /* !__WIN32__ */
/*
 * popen isn't POSIX-standard, so we declare it here.
 * Because of inconsistent (and sometimes incorrect) header files,
 * we must omit the argument list.  Unfortunately, this sometimes causes
 * more trouble than it cures.
 */
extern FILE *popen( /* const char *, const char * */ );
extern int pclose(FILE *);
#endif /* !__WIN32__ */

#endif /* pipe__INCLUDED */
