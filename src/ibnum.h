/* Copyright (C) 1990, 1996, 1997 artofcode LLC.  All rights reserved.
  
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

/*$Id: ibnum.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Encoded number definitions and support */
/* Requires stream.h */

#ifndef ibnum_INCLUDED
#  define ibnum_INCLUDED

/* Define the byte that begins an encoded number string. */
/* (This is the same as the value of bt_num_array in btoken.h.) */
#define bt_num_array_value 149

/* Homogenous number array formats. */
/* The default for numbers is big-endian. */
#define num_int32 0		/* [0..31] */
#define num_int16 32		/* [32..47] */
#define num_float 48
#define num_float_IEEE num_float
#define num_float_native (num_float + 1)
#define num_msb 0
#define num_lsb 128
#define num_is_lsb(format) ((format) >= num_lsb)
#define num_is_valid(format) (((format) & 127) <= 49)
/* Special "format" for reading from an array. */
/* num_msb/lsb is not used in this case. */
#define num_array 256
/* Define the number of bytes for a given format of encoded number. */
extern const byte enc_num_bytes[];	/* in ibnum.c */

#define enc_num_bytes_values\
  4, 4, 2, 4, 0, 0, 0, 0,\
  4, 4, 2, 4, 0, 0, 0, 0,\
  sizeof(ref)
#define encoded_number_bytes(format)\
  (enc_num_bytes[(format) >> 4])

/* Read from an array or encoded number string. */
int num_array_format(P1(const ref *));	/* returns format or error */
uint num_array_size(P2(const ref *, int));
int num_array_get(P4(const ref *, int, uint, ref *));

/* Decode a number from a string with appropriate byte swapping. */
int sdecode_number(P3(const byte *, int, ref *));
int sdecodeshort(P2(const byte *, int));
uint sdecodeushort(P2(const byte *, int));
long sdecodelong(P2(const byte *, int));
float sdecodefloat(P2(const byte *, int));

#endif /* ibnum_INCLUDED */
