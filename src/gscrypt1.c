/* Copyright (C) 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gscrypt1.c,v 1.2 2004/02/14 22:20:17 atai Exp $ */
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
