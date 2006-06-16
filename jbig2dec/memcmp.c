/*
    jbig2dec
    
    Copyright (C) 2001-2005 artofcode LLC.
    
    This software is distributed under license and may not
    be copied, modified or distributed except as expressly
    authorized under the terms of the license contained in
    the file LICENSE in this distribution.
                                                                                
    $Id: memcmp.c,v 1.3 2006/06/16 12:55:32 Arabidopsis Exp $
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stddef.h>

/* replacement for broken memcmp() */

/*
 * compares two byte strings 'a' and 'b', both assumed to be 'len' bytes long
 * returns zero if the two strings are identical, otherwise returns -1 or 1
 * depending on the relative magnitude of the first differing elements,
 * considered as unsigned chars
 */

int memcmp(const void *b1, const void *b2, size_t len)
{
	unsigned char *a, *b;
	size_t i;

	a = (unsigned char *)b1;
	b = (unsigned char *)b2;
	for(i = 0; i < len; i++) {
		if (*a != *b) {
			 /* strings differ */
			return (*a < *b) ? -1 : 1;
		}
		a++;
		b++;
	}

	/* strings match */
	return 0;
}
