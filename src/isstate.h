/* Copyright (C) 1993, 1995, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: isstate.h,v 1.4 2005/12/13 16:57:26 jemarch Exp $ */
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
