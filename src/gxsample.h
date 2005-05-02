/* Copyright (C) 1997, 1999 Aladdin Enterprises.  All rights reserved.
  
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

  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gxsample.h,v 1.3 2005/05/02 00:03:22 Arabidopsis Exp $ */
/* Sample lookup and expansion */

#ifndef gxsample_INCLUDED
#  define gxsample_INCLUDED

/*
 * The following union implements the expansion of sample
 * values from N bits to 8, and a possible linear transformation.
 */
typedef union sample_lookup_s {
    bits32 lookup4x1to32[16];	/* 1 bit/sample, not spreading */
    bits16 lookup2x2to16[16];	/* 2 bits/sample, not spreading */
    byte lookup8[256];		/* 1 bit/sample, spreading [2] */
    /* 2 bits/sample, spreading [4] */
    /* 4 bits/sample [16] */
    /* 8 bits/sample [256] */
} sample_lookup_t;

/*
 * Define identity and inverted expansion lookups for 1-bit input values.
 * These can be cast to a const sample_lookup_t.
 */
extern const bits32 lookup4x1to32_identity[16];
extern const bits32 lookup4x1to32_inverted[16];

/*
 * Define procedures to unpack and shuffle image data samples.  The Unix C
 * compiler can't handle typedefs for procedure (as opposed to
 * pointer-to-procedure) types, so we have to do it with macros instead.
 *
 * The original data start at sample data_x relative to data.
 * bptr points to the buffer normally used to deliver the unpacked data.
 * The unpacked data are at sample *pdata_x relative to the return value.
 *
 * Note that this procedure may return either a pointer to the buffer, or
 * a pointer to the original data.
 */
#define SAMPLE_UNPACK_PROC(proc)\
  const byte *proc(byte *bptr, int *pdata_x, const byte *data, int data_x,\
		   uint dsize, const sample_lookup_t *ptab, int spread)
typedef SAMPLE_UNPACK_PROC((*sample_unpack_proc_t));

/*
 * Declare the 1-for-1 unpacking procedure.
 */
SAMPLE_UNPACK_PROC(sample_unpack_copy);
/*
 * Declare unpacking procedures for 1, 2, 4, and 8 bits per pixel,
 * with optional spreading of the result.
 */
SAMPLE_UNPACK_PROC(sample_unpack_1);
SAMPLE_UNPACK_PROC(sample_unpack_2);
SAMPLE_UNPACK_PROC(sample_unpack_4);
SAMPLE_UNPACK_PROC(sample_unpack_8);

#endif /* gxsample_INCLUDED */
