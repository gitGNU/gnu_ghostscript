/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
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

/* $Id: gscedata.h,v 1.3 2007/05/07 11:21:43 Arabidopsis Exp $ */

#ifndef gscedata_INCLUDED
#  define gscedata_INCLUDED

#define NUM_LEN_BITS 5

#define N(len,offset) (((offset) << NUM_LEN_BITS) + (len))
#define N_LEN(e) ((e) & ((1 << NUM_LEN_BITS) - 1))
#define N_OFFSET(e) ((e) >> NUM_LEN_BITS)

extern const char gs_c_known_encoding_chars[];
extern const int gs_c_known_encoding_total_chars;
extern const int gs_c_known_encoding_max_length;
extern const ushort gs_c_known_encoding_offsets[];
extern const int gs_c_known_encoding_count;
extern const ushort *const gs_c_known_encodings[];
extern const ushort *const gs_c_known_encodings_reverse[];
extern const ushort gs_c_known_encoding_lengths[];
extern const ushort gs_c_known_encoding_reverse_lengths[];

#endif /* gscedata_INCLUDED */
