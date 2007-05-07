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

/* $Id: dwreg.h,v 1.5 2007/05/07 11:21:46 Arabidopsis Exp $ */

#ifndef dwreg_INCLUDED
#  define dwreg_INCLUDED

/* Get and set named registry values for Ghostscript application. */
int win_get_reg_value(const char *name, char *ptr, int *plen);
int win_set_reg_value(const char *name, const char *value);

#endif /* dwreg_INCLUDED */
