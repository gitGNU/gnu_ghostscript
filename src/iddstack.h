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

/*$Id: iddstack.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Dictionary stack API subset needed by idict.h */

#ifndef iddstack_INCLUDED
#  define iddstack_INCLUDED

#ifndef dict_stack_DEFINED
#  define dict_stack_DEFINED
typedef struct dict_stack_s dict_stack_t;
#endif

/*
 * Reset the cached top values.  Every routine that alters the
 * dictionary stack (including changing the protection or size of the
 * top dictionary on the stack) must call this.
 */
void dstack_set_top(P1(dict_stack_t *));

/* Check whether a dictionary is one of the permanent ones on the d-stack. */
bool dstack_dict_is_permanent(P2(const dict_stack_t *, const ref *));

#endif /* iddstack_INCLUDED */
