/* Copyright (C) 1994, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: iparray.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Packed array constructor for Ghostscript */
/* Requires ipacked.h, istack.h */

#ifndef iparray_INCLUDED
#  define iparray_INCLUDED

/*
 * The only reason to put this in a separate header is that it requires
 * both ipacked.h and istack.h; putting it in either one would make it
 * depend on the other one.  There must be a better way....
 */

/* Procedures implemented in zpacked.c */

/* Make a packed array from the top N elements of a stack. */
int make_packed_array(P5(ref *, ref_stack_t *, uint, gs_dual_memory_t *,
			 client_name_t));

#endif /* iparray_INCLUDED */
