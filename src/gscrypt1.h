/* Copyright (C) 1990, 1992, 1997 artofcode LLC.  All rights reserved.
  
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

/*$Id: gscrypt1.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Interface to Adobe Type 1 encryption/decryption. */

#ifndef gscrypt1_INCLUDED
#  define gscrypt1_INCLUDED

/* Normal public interface */
typedef ushort crypt_state;
int gs_type1_encrypt(P4(byte * dest, const byte * src, uint len,
			crypt_state * pstate));
int gs_type1_decrypt(P4(byte * dest, const byte * src, uint len,
			crypt_state * pstate));

/* Define the encryption parameters and procedures. */
#define crypt_c1 ((ushort)52845)
#define crypt_c2 ((ushort)22719)
/* c1 * c1' == 1 mod 2^16. */
#define crypt_c1_inverse ((ushort)27493)
#define encrypt_next(ch, state, chvar)\
  (chvar = ((ch) ^ (state >> 8)),\
   state = (chvar + state) * crypt_c1 + crypt_c2)
#define decrypt_this(ch, state)\
  ((ch) ^ (state >> 8))
#define decrypt_next(ch, state, chvar)\
  (chvar = decrypt_this(ch, state),\
   decrypt_skip_next(ch, state))
#define decrypt_skip_next(ch, state)\
  (state = ((ch) + state) * crypt_c1 + crypt_c2)
#define decrypt_skip_previous(ch, state)\
  (state = (state - crypt_c2) * crypt_c1_inverse - (ch))

#endif /* gscrypt1_INCLUDED */
