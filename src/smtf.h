/* Copyright (C) 1995 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: smtf.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
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
