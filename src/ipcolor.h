/* Copyright (C) 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: ipcolor.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Interpreter definitions for Pattern color */

#ifndef ipcolor_INCLUDED
#  define ipcolor_INCLUDED

/*
 * Define the structure for remembering the pattern dictionary.
 * This is the "client data" in the template.
 * See zgstate.c (int_gstate) or zfont2.c (font_data) for information
 * as to why we define this as a structure rather than a ref array.
 */
typedef struct int_pattern_s {
    ref dict;
} int_pattern;

#define private_st_int_pattern()	/* in zpcolor.c */\
  gs_private_st_ref_struct(st_int_pattern, int_pattern, "int_pattern")

/* Create an interpreter pattern structure. */
int int_pattern_alloc(P3(int_pattern **ppdata, const ref *op,
			 gs_memory_t *mem));

#endif /* ipcolor_INCLUDED */
