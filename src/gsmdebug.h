/* Copyright (C) 1995, 1996, 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsmdebug.h,v 1.1 2004/01/14 16:59:50 atai Exp $ */
/* Allocator debugging definitions and interface */
/* Requires gdebug.h (for gs_debug) */

#ifndef gsmdebug_INCLUDED
#  define gsmdebug_INCLUDED

/* Define the fill patterns used for debugging the allocator. */
extern const byte
       gs_alloc_fill_alloc,	/* allocated but not initialized */
       gs_alloc_fill_block,	/* locally allocated block */
       gs_alloc_fill_collected,	/* garbage collected */
       gs_alloc_fill_deleted,	/* locally deleted block */
       gs_alloc_fill_free;	/* freed */

/* Define an alias for a specialized debugging flag */
/* that used to be a separate variable. */
#define gs_alloc_debug gs_debug['@']

/* Conditionally fill unoccupied blocks with a pattern. */
extern void gs_alloc_memset(P3(void *, int /*byte */ , ulong));

#ifdef DEBUG
#  define gs_alloc_fill(ptr, fill, len)\
     BEGIN if ( gs_alloc_debug ) gs_alloc_memset(ptr, fill, (ulong)(len)); END
#else
#  define gs_alloc_fill(ptr, fill, len)\
     DO_NOTHING
#endif

#endif /* gsmdebug_INCLUDED */
