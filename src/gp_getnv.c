/* Copyright (C) 1997 artofcode LLC.  All rights reserved.
  
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

/*$Id: gp_getnv.c,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Standard implementation of gp_getenv */
#include "stdio_.h"
#include "string_.h"
#include "gsmemory.h"
#include "gstypes.h"
#include "gp.h"

/* Import the C getenv function. */
extern char *getenv(P1(const char *));

/* Get the value of an environment variable.  See gp.h for details. */
int
gp_getenv(const char *key, char *ptr, int *plen)
{
    const char *str = getenv(key);

    if (str) {
	int len = strlen(str);

	if (len < *plen) {
	    /* string fits */
	    strcpy(ptr, str);
	    *plen = len + 1;
	    return 0;
	}
	/* string doesn't fit */
	*plen = len + 1;
	return -1;
    }
    /* missing key */
    if (*plen > 0)
	*ptr = 0;
    *plen = 1;
    return 1;
}
