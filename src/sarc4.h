/* Copyright (C) 2001 artofcode LLC.  All rights reserved.
  
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

/*$Id: sarc4.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Definitions for Arcfour cipher and filter */
/* Requires scommon.h; strimpl.h if any templates are referenced */

#ifndef sarc4_INCLUDED
#  define sarc4_INCLUDED

#include "scommon.h"

/* Arcfour is a symmetric cipher whose state is maintained
 * in two indices into an accompanying 8x8 S box. this will
 * typically be allocated on the stack, and so has no memory
 * management associated.
 */
typedef struct stream_arcfour_state_s
{
    stream_state_common;	/* a define from scommon.h */
    unsigned int x, y;
    unsigned char S[256];
}
stream_arcfour_state;

int s_arcfour_set_key(stream_arcfour_state * state, const unsigned char *key,
		      int keylength);

#define private_st_arcfour_state()	/* used in sarc4.c */\
  gs_private_st_simple(st_arcfour_state, stream_arcfour_state,\
    "Arcfour filter state")
extern const stream_template s_arcfour_template;

#endif /* sarc4_INCLUDED */
