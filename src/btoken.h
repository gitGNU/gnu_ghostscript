/* Copyright (C) 1990, 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: btoken.h,v 1.1 2004/01/14 16:59:47 atai Exp $ */
/* Definitions for Level 2 binary tokens */

#ifndef btoken_INCLUDED
#  define btoken_INCLUDED

/*
 * Define accessors for pointers to the system and user name tables
 * (arrays).  Note that these refer implicitly to i_ctx_p.  Note also
 * that these pointers may be NULL: clients must check this.
 */
#define system_names_p (gs_imemory.space_global->names_array)
#define user_names_p (gs_imemory.space_local->names_array)

/* Create a system or user name table (in the stable memory of mem). */
int create_names_array(P3(ref **ppnames, gs_memory_t *mem,
			  client_name_t cname)); /* in zbseq.c */

/* Convert an object to its representation in a binary object sequence. */
int encode_binary_token(P5(i_ctx_t *i_ctx_p, const ref *obj, long *ref_offset,
			   long *char_offset, byte *str)); /* in iscanbin.c */

/* Define the current binary object format for operators. */
/* This is a ref so that it can be managed properly by save/restore. */
#define ref_binary_object_format_container i_ctx_p
#define ref_binary_object_format\
  (ref_binary_object_format_container->binary_object_format)

#endif /* btoken_INCLUDED */
