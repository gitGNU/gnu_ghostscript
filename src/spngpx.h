/* Copyright (C) 1996, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: spngpx.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* Definitions for PNGPredictor filters */
/* Requires strimpl.h */

#ifndef spngpx_INCLUDED
#  define spngpx_INCLUDED

/* PNGPredictorDecode / PNGPredictorEncode */
typedef struct stream_PNGP_state_s {
    stream_state_common;
    /* The client sets the following before initialization. */
    int Colors;			/* # of colors, 1..16 */
    int BitsPerComponent;	/* 1, 2, 4, 8, 16 */
    uint Columns;		/* >0 */
    int Predictor;		/* 10-15, only relevant for Encode */
    /* The init procedure computes the following. */
    uint row_count;		/* # of bytes per row */
    byte end_mask;		/* mask for left-over bits in last byte */
    int bpp;			/* bytes per pixel */
    byte *prev_row;		/* previous row */
    int case_index;		/* switch index for case dispatch, */
				/* set dynamically when decoding */
    /* The following are updated dynamically. */
    long row_left;		/* # of bytes left in row */
    byte prev[32];		/* previous samples */
} stream_PNGP_state;

#define private_st_PNGP_state()	/* in sPNGP.c */\
  gs_private_st_ptrs1(st_PNGP_state, stream_PNGP_state,\
    "PNGPredictorEncode/Decode state", pngp_enum_ptrs, pngp_reloc_ptrs,\
    prev_row)
#define s_PNGP_set_defaults_inline(ss)\
  ((ss)->Colors = 1, (ss)->BitsPerComponent = 8, (ss)->Columns = 1,\
   (ss)->Predictor = 15,\
		/* Clear pointers */\
   (ss)->prev_row = 0)
extern const stream_template s_PNGPD_template;
extern const stream_template s_PNGPE_template;

#endif /* spngpx_INCLUDED */
