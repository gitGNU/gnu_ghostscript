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

/*$Id: smtf.h,v 1.1 2004/01/14 16:59:53 atai Exp $ */
/* Definitions for MoveToFront filters */
/* Requires scommon.h; strimpl.h if any templates are referenced */

#ifndef smtf_INCLUDED
#  define smtf_INCLUDED

/* MoveToFrontEncode/Decode */
typedef struct stream_MTF_state_s {
    stream_state_common;
    /* The following change dynamically. */
    union _p {
	ulong l[256 / sizeof(long)];
	byte b[256];
    } prev;
} stream_MTF_state;
typedef stream_MTF_state stream_MTFE_state;
typedef stream_MTF_state stream_MTFD_state;

#define private_st_MTF_state()	/* in sbwbs.c */\
  gs_private_st_simple(st_MTF_state, stream_MTF_state,\
    "MoveToFrontEncode/Decode state")
extern const stream_template s_MTFE_template;
extern const stream_template s_MTFD_template;

#endif /* smtf_INCLUDED */
