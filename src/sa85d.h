/* Copyright (C) 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: sa85d.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* ASCII85Decode filter interface */
/* Requires scommon.h; strimpl.h if any templates are referenced */

#ifndef sa85d_INCLUDED
#  define sa85d_INCLUDED

/* ASCII85Decode */
typedef struct stream_A85D_state_s {
    stream_state_common;
    int odd;			/* # of odd digits */
    ulong word;			/* word being accumulated */
} stream_A85D_state;

#define private_st_A85D_state()	/* in sfilter2.c */\
  gs_private_st_simple(st_A85D_state, stream_A85D_state,\
    "ASCII85Decode state")
/* We define the initialization procedure here, so that the scanner */
/* can avoid a procedure call. */
#define s_A85D_init_inline(ss)\
  ((ss)->min_left = 1, (ss)->word = 0, (ss)->odd = 0)
extern const stream_template s_A85D_template;

#endif /* sa85d_INCLUDED */
