/* Copyright (C) 1994 artofcode LLC.  All rights reserved.
  
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

/*$Id: shcgen.h,v 1.1 2004/01/14 16:59:53 atai Exp $ */
/* Interface for Huffman code generation */
/* Requires shc.h */

#ifndef shcgen_INCLUDED
#  define shcgen_INCLUDED

/* Compute an optimal Huffman code from an input data set. */
/* The client must have set all the elements of *def. */
/* The definition is guaranteed to be well-behaved. */
int hc_compute(P3(hc_definition * def, const long *freqs, gs_memory_t * mem));

/* Convert a definition to a byte string. */
/* The caller must provide the byte string, of length def->num_values. */
/* Assume (do not check) that the definition is well-behaved. */
/* Return the actual length of the string. */
int hc_bytes_from_definition(P2(byte * dbytes, const hc_definition * def));

/* Extract num_counts and num_values from a byte string. */
void hc_sizes_from_bytes(P3(hc_definition * def, const byte * dbytes, int num_bytes));

/* Convert a byte string back to a definition. */
/* The caller must initialize *def, including allocating counts and values. */
void hc_definition_from_bytes(P2(hc_definition * def, const byte * dbytes));

/* Generate the encoding table from the definition. */
/* The size of the encode array is def->num_values. */
void hc_make_encoding(P2(hce_code * encode, const hc_definition * def));

/* Calculate the size of the decoding table. */
uint hc_sizeof_decoding(P2(const hc_definition * def, int initial_bits));

/* Generate the decoding tables. */
void hc_make_decoding(P3(hcd_code * decode, const hc_definition * def,
			 int initial_bits));

#endif /* shcgen_INCLUDED */
