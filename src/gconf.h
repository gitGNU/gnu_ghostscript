/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
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
/* $Id: gconf.h,v 1.5 2007/05/07 11:21:45 Arabidopsis Exp $ */
/* Wrapper for gconfig.h or a substitute. */

/*
 * NOTA BENE: This file, unlike all other header files, must *not* have
 * double-inclusion protection, since it is used in peculiar ways.
 */

/*
 * Since not all C preprocessors implement #include with a non-quoted
 * argument, we arrange things so that we can still compile with such
 * compilers as long as GCONFIG_H isn't defined.
 */

#ifndef GCONFIG_H
#  include "gconfig.h"
#else
#  include GCONFIG_H
#endif
