/* Copyright (C) 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gscrypt1.c,v 1.3 2005/05/02 00:03:33 Arabidopsis Exp $ */
/* Adobe Type 1 encryption/decryption. */
#include "stdpre.h"
#include "gstypes.h"
#include "gscrypt1.h"

/* Encrypt a string. */
int
gs_type1_encrypt(byte * dest, const byte * src, uint len, crypt_state * pstate)
{
    crypt_state state = *pstate;
    const byte *from = src;
    byte *to = dest;
    uint count = len;

    while (count) {
	encrypt_next(*from, state, *to);
	from++, to++, count--;
    }
    *pstate = state;
    return 0;
}
/* Decrypt a string. */
int
gs_type1_decrypt(byte * dest, const byte * src, uint len, crypt_state * pstate)
{
    crypt_state state = *pstate;
    const byte *from = src;
    byte *to = dest;
    uint count = len;

    while (count) {
	/* If from == to, we can't use the obvious */
	/*      decrypt_next(*from, state, *to);        */
	byte ch = *from++;

	decrypt_next(ch, state, *to);
	to++, count--;
    }
    *pstate = state;
    return 0;
}
