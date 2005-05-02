/* Copyright (C) 1992, 1995 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: shc.c,v 1.3 2005/05/02 00:03:35 Arabidopsis Exp $ */
/* Support code for shc.h */
#include "std.h"
#include "scommon.h"
#include "shc.h"

/* ------ Encoding ------ */

/* Empty the 1-word buffer onto the output stream. */
/* q has already been incremented. */
void
hc_put_code_proc(bool reverse_bits, byte * q, uint cw)
{
#define cb(n) ((byte)(cw >> (n * 8)))
    if (reverse_bits) {
#if hc_bits_size > 16
	q[-3] = byte_reverse_bits[cb(3)];
	q[-2] = byte_reverse_bits[cb(2)];
#endif
	q[-1] = byte_reverse_bits[cb(1)];
	q[0] = byte_reverse_bits[cb(0)];
    } else {
#if hc_bits_size > 16
	q[-3] = cb(3);
	q[-2] = cb(2);
#endif
	q[-1] = cb(1);
	q[0] = cb(0);
    }
#undef cb
}

/* Put out any final bytes. */
/* Note that this does a store_state, but not a load_state. */
byte *
hc_put_last_bits_proc(stream_hc_state * ss, byte * q, uint bits, int bits_left)
{
    while (bits_left < hc_bits_size) {
	byte c = (byte) (bits >> (hc_bits_size - 8));

	if (ss->FirstBitLowOrder)
	    c = byte_reverse_bits[c];
	*++q = c;
	bits <<= 8;
	bits_left += 8;
    }
    ss->bits = bits;
    ss->bits_left = bits_left;
    return q;
}
