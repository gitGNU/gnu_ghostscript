/* Copyright (C) 2002 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gscencs.c,v 1.1 2004/02/14 22:32:08 atai Exp $ */
/* Compact C representation of built-in encodings */

#include "memory_.h"
#include "gscedata.h"
#include "gscencs.h"
#include "gserror.h"
#include "gserrors.h"

/*
 * The actual encoding data tables in gscedata.c, and the internal
 * interface definitions in gscedata.h, are generated by toolbin/encs2c.ps,
 * q.v.
 *
 * In the encoding tables in gscedata.c, each glyph is represented by a
 * ushort (16-bit) value.  A bias of gs_c_min_std_encoding_glyph is added
 * or subtracted to form a gs_glyph value.
 */

/*
 * gscedata.[hc] defines the following tables:
 *	const char gs_c_known_encoding_chars[NUM_CHARS] --
 *	  the character table.
 *	const int gs_c_known_encoding_offsets[NUM_INDIRECT_LEN] --
 *	  the starting offsets of the names of a given length in the
 *	  character table.
 *	const ushort *const gs_c_known_encodings[] --
 *	  pointers to the encodings per se.
 *	const ushort gs_c_known_encoding_lengths[] --
 *	  lengths of the encodings.
 */

const gs_glyph gs_c_min_std_encoding_glyph = gs_min_cid_glyph - 0x10000;

/*
 * Encode a character in a known encoding.  The only use for glyph numbers
 * returned by this procedure is to pass them to gs_c_glyph_name.
 */
gs_glyph
gs_c_known_encode(gs_char ch, int ei)
{
    if (ei < 0 || ei >= gs_c_known_encoding_count ||
	ch >= gs_c_known_encoding_lengths[ei]
	)
	return gs_no_glyph;
    return gs_c_min_std_encoding_glyph + gs_c_known_encodings[ei][ch];
}

/*
 * Convert a glyph number returned by gs_c_known_encode to a string.
 */
int
gs_c_glyph_name(gs_glyph glyph, gs_const_string *pstr)
{
    uint n = (uint)(glyph - gs_c_min_std_encoding_glyph);
    uint len = N_LEN(n);
    uint off = N_OFFSET(n);

#ifdef DEBUG
    if (len == 0 || len > gs_c_known_encoding_max_length ||
	off >= gs_c_known_encoding_offsets[len + 1] -
	  gs_c_known_encoding_offsets[len] ||
	off % len != 0
	)
	return_error(gs_error_rangecheck);
#endif
    pstr->data = (const byte *)
	&gs_c_known_encoding_chars[gs_c_known_encoding_offsets[len] + off];
    pstr->size = len;
    return 0;
}

/*
 * Test whether a string is one that was returned by gs_c_glyph_name.
 */
bool
gs_is_c_glyph_name(const byte *str, uint len)
{
    return (str >= (const byte *)gs_c_known_encoding_chars &&
	    (str - (const byte *)gs_c_known_encoding_chars) <
	      gs_c_known_encoding_total_chars);
}

/*
 * Return the glyph number corresponding to a string (the inverse of
 * gs_c_glyph_name), or gs_no_glyph if the glyph name is not known.
 */
gs_glyph
gs_c_name_glyph(const byte *str, uint len)
{
    if (len == 0 || len > gs_c_known_encoding_max_length)
	return gs_no_glyph;
    /* Binary search the character table. */
    {
	uint base = gs_c_known_encoding_offsets[len];
	const byte *bot = (const byte *)&gs_c_known_encoding_chars[base];
	uint count = (gs_c_known_encoding_offsets[len + 1] - base) / len;
	uint a = 0, b = count;	/* know b > 0 */
	const byte *probe;

	while (a < b) {		/* know will execute at least once */
	    uint m = (a + b) >> 1;
	    int cmp;

	    probe = bot + m * len;
	    cmp = memcmp(str, probe, len);
	    if (cmp == 0)
		return gs_c_min_std_encoding_glyph + N(len, probe - bot);
	    else if (cmp > 0)
		a = m + 1;
	    else
		b = m;
	}
    }

    return gs_no_glyph;
}

#ifdef TEST

/* NOTE: test values will have to be updated if representation changes. */
#define I_caron N(5,85)
#define I_carriagereturn N(14,154)
#define I_circlemultiply N(14,168)
#define I_numbersign N(10,270)
#define I_copyright N(9,180)

/* Test */
#include <stdio.h>
main()
{
    gs_glyph g;
    gs_const_string str;

    /* Test with a short name. */
    g = gs_c_known_encode((gs_char)0237, 1); /* caron */
    printf("caron is %u, should be %u\n",
	   g - gs_c_min_std_encoding_glyph, I_caron);
    gs_c_glyph_name(g, &str);
    fwrite(str.data, 1, str.size, stdout);
    printf(" should be caron\n");

    /* Test with a long name. */
    g = gs_c_known_encode((gs_char)0277, 2); /* carriagereturn */
    printf("carriagereturn is %u, should be %u\n",
	   g - gs_c_min_std_encoding_glyph, I_carriagereturn);
    gs_c_glyph_name(g, &str);
    fwrite(str.data, 1, str.size, stdout);
    printf(" should be carriagereturn\n");

    /* Test lookup with 3 kinds of names. */
    g = gs_c_name_glyph((const byte *)"circlemultiply", 14);
    printf("circlemultiply is %u, should be %u\n",
	   g - gs_c_min_std_encoding_glyph, I_circlemultiply);
    g = gs_c_name_glyph((const byte *)"numbersign", 10);
    printf("numbersign is %u, should be %u\n",
	   g - gs_c_min_std_encoding_glyph, I_numbersign);
    g = gs_c_name_glyph((const byte *)"copyright", 9);
    printf("copyright is %u, should be %u\n",
	   g - gs_c_min_std_encoding_glyph, I_copyright);

    exit(0);
}

#endif /* TEST */
