/* Copyright (C) 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxcid.h,v 1.1 2004/01/14 16:59:51 atai Exp $ */
/* Common data definitions for CMaps and CID-keyed fonts */

#ifndef gxcid_INCLUDED
#  define gxcid_INCLUDED

#include "gsstype.h"

/* Define the structure for CIDSystemInfo. */
typedef struct gs_cid_system_info_s {
    gs_const_string Registry;
    gs_const_string Ordering;
    int Supplement;
} gs_cid_system_info_t;
extern_st(st_cid_system_info);
extern_st(st_cid_system_info_element);
#define public_st_cid_system_info() /* in gsfcid.c */\
  gs_public_st_const_strings2(st_cid_system_info, gs_cid_system_info_t,\
    "gs_cid_system_info_t", cid_si_enum_ptrs, cid_si_reloc_ptrs,\
    Registry, Ordering)
#define st_cid_system_info_num_ptrs 2
#define public_st_cid_system_info_element() /* in gsfcid.c */\
  gs_public_st_element(st_cid_system_info_element, gs_cid_system_info_t,\
    "gs_cid_system_info_t[]", cid_si_elt_enum_ptrs, cid_si_elt_reloc_ptrs,\
    st_cid_system_info)

/*
 * The CIDSystemInfo of a CMap may be null.  We represent this by setting
 * Registry and Ordering to empty strings, and Supplement to 0.
 */
void cid_system_info_set_null(P1(gs_cid_system_info_t *));
bool cid_system_info_is_null(P1(const gs_cid_system_info_t *));

#endif /* gxcid_INCLUDED */
