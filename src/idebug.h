/* Copyright (C) 1994, 1995, 1999 Aladdin Enterprises.  All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 2
  as published by the Free Software Foundation.


  This software is provided AS-IS with no warranty, either express or
  implied. That is, this program is distributed in the hope that it will 
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.
  
  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: idebug.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* Prototypes for debugging procedures in idebug.c */

#ifndef idebug_INCLUDED
#  define idebug_INCLUDED

/* Print individual values. */
void debug_print_name(const ref *);
void debug_print_name_index(uint /*name_index_t*/);
void debug_print_ref(const ref *);
void debug_print_ref_packed(const ref_packed *);

/* Dump regions of memory. */
void debug_dump_one_ref(const ref *);
void debug_dump_refs(const ref * from, uint size, const char *msg);
void debug_dump_array(const ref * array);

/* Dump a stack.  Using this requires istack.h. */
#ifndef ref_stack_DEFINED
typedef struct ref_stack_s ref_stack_t;	/* also defined in isdata.h */
#  define ref_stack_DEFINED
#endif
void debug_dump_stack(const ref_stack_t * pstack, const char *msg);

#endif /* idebug_INCLUDED */
