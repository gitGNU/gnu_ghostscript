/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
  This file is part of GNU Ghostscript.
  
  GNU Ghostscript is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY.  No author or distributor accepts responsibility to
  anyone for the consequences of using it or for whether it serves any
  particular purpose or works at all, unless he says so in writing.  Refer to
  the GNU General Public License for full details.
  
  Everyone is granted permission to copy, modify and redistribute GNU
  Ghostscript, but only under the conditions described in the GNU General
  Public License.  A copy of this license is supposed to have been given to
  you along with GNU Ghostscript so you can know your rights and
  responsibilities.  It should be in a file named COPYING.  Among other
  things, the copyright notice and this notice must be preserved on all
  copies.
  
  Aladdin Enterprises is not affiliated with the Free Software Foundation or
  the GNU Project.  GNU Ghostscript, as distributed by Aladdin Enterprises,
  does not depend on any other GNU software.
*/

/* gsfcmap.h */
/* CMap data definition */
/* Requires gsstruct.h */

#ifndef gsfcmap_INCLUDED
#  define gsfcmap_INCLUDED

#include "gsccode.h"

/* Define the abstract type for a CMap. */
#ifndef gs_cmap_DEFINED
#  define gs_cmap_DEFINED
typedef struct gs_cmap_s gs_cmap;
#endif

/* We only need the structure descriptor for testing. */
extern_st(st_cmap);

/* Define the structure for CIDSystemInfo. */
typedef struct gs_cid_system_info_s {
  gs_const_string Registry;
  gs_const_string Ordering;
  int Supplement;
} gs_cid_system_info;
#define gs_cid_system_info_max_ptrs 2
/* We only need the structure descriptor for embedding. */
extern_st(st_cid_system_info);

/* ---------------- Procedural interface ---------------- */

/*
 * Decode a character from a string using a CMap, updating the index.
 * Return 0 for a CID or name, N > 0 for a character code where N is the
 * number of bytes in the code, or an error.  For undefined characters,
 * we return CID 0.
 */
int gs_cmap_decode_next(P5(const gs_cmap *pcmap, const gs_const_string *str,
			   uint *pindex, uint *pfidx, gs_glyph *pglyph));

#endif				/* gsfcmap_INCLUDED */
