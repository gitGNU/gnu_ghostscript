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

/*$Id: istkparm.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Parameter structure for expandable stacks of refs */

#ifndef istkparm_INCLUDED
#  define istkparm_INCLUDED

/*
 * Define the structure for stack parameters set at initialization.
 */
/*typedef struct ref_stack_params_s ref_stack_params_t;*/ /* in istack.h */
struct ref_stack_params_s {
    uint bot_guard;		/* # of guard elements below bot */
    uint top_guard;		/* # of guard elements above top */
    uint block_size;		/* size of each block */
    uint data_size;		/* # of data slots in each block */
    ref guard_value;		/* t__invalid or t_operator, */
				/* bottom guard value */
    int underflow_error;	/* error code for underflow */
    int overflow_error;		/* error code for overflow */
    bool allow_expansion;	/* if false, don't expand */
};
#define private_st_ref_stack_params() /* in istack.c */\
  gs_private_st_simple(st_ref_stack_params, ref_stack_params_t,\
    "ref_stack_params_t")

#endif /* istkparm_INCLUDED */
