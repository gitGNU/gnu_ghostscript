/* Copyright (C) 1994, 1995, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: spdiffx.h,v 1.1 2004/01/14 16:59:53 atai Exp $ */
/* Definitions for PixelDifference filters */
/* Requires strimpl.h */

#ifndef spdiffx_INCLUDED
#  define spdiffx_INCLUDED

/*
 * Define the maximum value for Colors.  This must be at least 4, but can
 * be arbitrarily large: the only cost is a larger stream state structure.
 */
#define s_PDiff_max_Colors 16

/* PixelDifferenceDecode / PixelDifferenceEncode */
typedef struct stream_PDiff_state_s {
    stream_state_common;
    /* The client sets the following before initialization. */
    int Colors;			/* # of colors, 1..s_PDiff_max_Colors */
    int BitsPerComponent;	/* 1, 2, 4, 8 */
    int Columns;
    /* The init procedure computes the following. */
    uint row_count;		/* # of bytes per row */
    byte end_mask;		/* mask for left-over bits in last byte */
    int case_index;		/* switch index for case dispatch */
    /* The following are updated dynamically. */
    uint row_left;		/* # of bytes left in row */
    byte prev[s_PDiff_max_Colors];	/* previous sample */
} stream_PDiff_state;

#define private_st_PDiff_state()	/* in spdiff.c */\
  gs_private_st_simple(st_PDiff_state, stream_PDiff_state,\
    "PixelDifferenceEncode/Decode state")
#define s_PDiff_set_defaults_inline(ss)\
  ((ss)->Colors = 1, (ss)->BitsPerComponent = 8, (ss)->Columns = 1)
extern const stream_template s_PDiffD_template;
extern const stream_template s_PDiffE_template;

#endif /* spdiffx_INCLUDED */
