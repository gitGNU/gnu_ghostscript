/* Copyright (C) 1995 artofcode LLC.  All rights reserved.
  
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

/*$Id: igcstr.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Internal interface to string garbage collector */

#ifndef igcstr_INCLUDED
#  define igcstr_INCLUDED

/* Exported by ilocate.c for igcstr.c */
chunk_t *gc_locate(P2(const void *, gc_state_t *));

/* Exported by igcstr.c for igc.c */
void gc_strings_set_marks(P2(chunk_t *, bool));
bool gc_string_mark(P4(const byte *, uint, bool, gc_state_t *));
void gc_strings_clear_reloc(P1(chunk_t *));
void gc_strings_set_reloc(P1(chunk_t *));
void gc_strings_compact(P1(chunk_t *));
string_proc_reloc(igc_reloc_string);
const_string_proc_reloc(igc_reloc_const_string);

#endif /* igcstr_INCLUDED */
