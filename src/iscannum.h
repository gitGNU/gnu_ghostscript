/* Copyright (C) 1994, 1995, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: iscannum.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Interface to Ghostscript number scanner */

#ifndef iscannum_INCLUDED
#  define iscannum_INCLUDED

/*
 * Scan a number.  If the number consumes the entire string, return 0;
 * if not, set *psp to the first character beyond the number and return 1.
 * Note that scan_number does not mark the result ref as "new".
 */
int scan_number(P5(const byte * sp, const byte * end, int sign, ref * pref,
		   const byte ** psp));

#endif /* iscannum_INCLUDED */
