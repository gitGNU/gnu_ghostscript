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

/*$Id: sbcp.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Interface to [T]BCP streams */

#ifndef sbcp_INCLUDED
#  define sbcp_INCLUDED

/* (T)BCPEncode */
/* (no state) */
extern const stream_template s_BCPE_template;
extern const stream_template s_TBCPE_template;

/* (T)BCPDecode */
typedef struct stream_BCPD_state_s {
    stream_state_common;
    /* The client sets the following before initialization. */
    int (*signal_interrupt) (P1(stream_state *));
    int (*request_status) (P1(stream_state *));
    /* The following are updated dynamically. */
    bool escaped;
    int matched;		/* TBCP only */
    int copy_count;		/* TBCP only */
    const byte *copy_ptr;	/* TBCP only */
} stream_BCPD_state;

#define private_st_BCPD_state()	/* in sbcp.c */\
  gs_private_st_simple(st_BCPD_state, stream_BCPD_state, "(T)BCPDecode state")
extern const stream_template s_BCPD_template;
extern const stream_template s_TBCPD_template;

#endif /* sbcp_INCLUDED */
