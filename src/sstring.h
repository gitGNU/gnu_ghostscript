/* Copyright (C) 1996, 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: sstring.h,v 1.4 2005/12/13 16:57:28 jemarch Exp $ */
/* String and hexstring streams (filters) */

#ifndef sstring_INCLUDED
#  define sstring_INCLUDED

/* ASCIIHexEncode */
typedef struct stream_AXE_state_s {
    stream_state_common;
    /* The following are set by the client. */
    bool EndOfData;		/* if true, write > at EOD (default) */
    /* The following change dynamically. */
    int count;			/* # of digits since last EOL */
} stream_AXE_state;

#define private_st_AXE_state()	/* in sstring.c */\
  gs_private_st_simple(st_AXE_state, stream_AXE_state,\
    "ASCIIHexEncode state")
#define s_AXE_init_inline(ss)\
  ((ss)->EndOfData = true, (ss)->count = 0)
extern const stream_template s_AXE_template;

/* ASCIIHexDecode */
typedef struct stream_AXD_state_s {
    stream_state_common;
    int odd;			/* odd digit */
} stream_AXD_state;

#define private_st_AXD_state()	/* in sstring.c */\
  gs_private_st_simple(st_AXD_state, stream_AXD_state,\
    "ASCIIHexDecode state")
#define s_AXD_init_inline(ss)\
  ((ss)->min_left = 1, (ss)->odd = -1, 0)
extern const stream_template s_AXD_template;

/* PSStringDecode */
typedef struct stream_PSSD_state_s {
    stream_state_common;
    /* The following are set by the client. */
    bool from_string;		/* true if using Level 1 \ convention */
    /* The following change dynamically. */
    int depth;
} stream_PSSD_state;

#define private_st_PSSD_state()	/* in sstring.c */\
  gs_private_st_simple(st_PSSD_state, stream_PSSD_state,\
    "PSStringDecode state")
/* We define the initialization procedure here, so that the scanner */
/* can avoid a procedure call. */
#define s_PSSD_init_inline(ss)\
  ((ss)->depth = 0)
extern const stream_template s_PSSD_template;

/* PSStringEncode */
/* (no state) */
extern const stream_template s_PSSE_template;

#endif /* sstring_INCLUDED */
