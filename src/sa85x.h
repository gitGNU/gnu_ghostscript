/* Copyright (C) 1996, 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: sa85x.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* ASCII85 filter interface */
/* Requires scommon.h; strimpl.h if any templates are referenced */

#ifndef sa85x_INCLUDED
#  define sa85x_INCLUDED

#include "sa85d.h"

/* ASCII85Encode */
typedef struct stream_A85E_state_s {
    stream_state_common;
    /* The following change dynamically. */
    int count;			/* # of digits since last EOL */
    int last_char;		/* last character written */
} stream_A85E_state;

#define private_st_A85E_state()	/* in sfilter2.c */\
  gs_private_st_simple(st_A85E_state, stream_A85E_state,\
    "ASCII85Encode state")
#define s_A85E_init_inline(ss)\
  ((ss)->count = 0, (ss)->last_char = '\n')
extern const stream_template s_A85E_template;

#endif /* sa85x_INCLUDED */
