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

/* $Id: gspenum.h,v 1.5 2007/05/07 11:21:45 Arabidopsis Exp $ */
/* Common definitions for client interface to path enumeration */

#ifndef gspenum_INCLUDED
#  define gspenum_INCLUDED

/* Define the path element types. */
#define gs_pe_moveto 1
#define gs_pe_lineto 2
#define gs_pe_curveto 3
#define gs_pe_closepath 4

/* Define an abstract type for the path enumerator. */
typedef struct gs_path_enum_s gs_path_enum;

#endif /* gspenum_INCLUDED */
