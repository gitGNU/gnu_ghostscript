/* Copyright (C) 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: gpgetenv.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Interface to platform-specific getenv routine */

#ifndef gpgetenv_INCLUDED
#  define gpgetenv_INCLUDED

/*
 * Get a value from the environment (getenv).
 *
 * If the key is missing, set *ptr = 0 (if *plen > 0), set *plen = 1,
 * and return 1.
 *
 * If the key is present and the length len of the value (not counting
 * the terminating \0) is less than *plen, copy the value to ptr, set
 * *plen = len + 1, and return 0.
 *
 * If the key is present and len >= *plen, set *plen = len + 1,
 * don't store anything at ptr, and return -1.
 *
 * Note that *plen is the size of the buffer, not the length of the string:
 * because of the terminating \0, the maximum string length is 1 less than
 * the size of the buffer.
 */
int gp_getenv(P3(const char *key, char *ptr, int *plen));

#endif /* gpgetenv_INCLUDED */
