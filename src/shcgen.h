/* Copyright (C) 1994 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: shcgen.h,v 1.3 2005/05/02 00:03:22 Arabidopsis Exp $ */
/* Interface for Huffman code generation */
/* Requires shc.h */

#ifndef shcgen_INCLUDED
#  define shcgen_INCLUDED

/* Compute an optimal Huffman code from an input data set. */
/* The client must have set all the elements of *def. */
/* The definition is guaranteed to be well-behaved. */
int hc_compute(hc_definition * def, const long *freqs, gs_memory_t * mem);

/* Convert a definition to a byte string. */
/* The caller must provide the byte string, of length def->num_values. */
/* Assume (do not check) that the definition is well-behaved. */
/* Return the actual length of the string. */
int hc_bytes_from_definition(byte * dbytes, const hc_definition * def);

/* Extract num_counts and num_values from a byte string. */
void hc_sizes_from_bytes(hc_definition * def, const byte * dbytes, int num_bytes);

/* Convert a byte string back to a definition. */
/* The caller must initialize *def, including allocating counts and values. */
void hc_definition_from_bytes(hc_definition * def, const byte * dbytes);

/* Generate the encoding table from the definition. */
/* The size of the encode array is def->num_values. */
void hc_make_encoding(hce_code * encode, const hc_definition * def);

/* Calculate the size of the decoding table. */
uint hc_sizeof_decoding(const hc_definition * def, int initial_bits);

/* Generate the decoding tables. */
void hc_make_decoding(hcd_code * decode, const hc_definition * def,
		      int initial_bits);

#endif /* shcgen_INCLUDED */
