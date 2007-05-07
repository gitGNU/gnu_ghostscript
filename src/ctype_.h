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
/* $Id: ctype_.h,v 1.5 2007/05/07 11:21:45 Arabidopsis Exp $ */
/* Wrapper for ctype.h */

#ifndef ctype__INCLUDED
#  define ctype__INCLUDED

/* We must include std.h before any file that includes sys/types.h. */
#include "std.h"

/* ... and that's the only reason for having this file at all. */
#include <ctype.h>

#endif /* ctype__INCLUDED */
