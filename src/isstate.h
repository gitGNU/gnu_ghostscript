/* Copyright (C) 1993, 1995, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: isstate.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* Definition of 'save' structure */
/* Requires isave.h */

#ifndef isstate_INCLUDED
#  define isstate_INCLUDED

/* Saved state of allocator and other things as needed. */
/*typedef struct alloc_save_s alloc_save_t; *//* in isave.h */
struct alloc_save_s {
    gs_ref_memory_t state;	/* must be first for subclassing */
    vm_spaces spaces;
    bool restore_names;
    bool is_current;
    ulong id;
    void *client_data;
};

#define private_st_alloc_save()	/* in isave.c */\
  gs_private_st_suffix_add1(st_alloc_save, alloc_save_t, "alloc_save",\
    save_enum_ptrs, save_reloc_ptrs, st_ref_memory, client_data)

#endif /* isstate_INCLUDED */
