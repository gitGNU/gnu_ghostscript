/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gp_getnv.c,v 1.2 2004/02/14 22:20:16 atai Exp $ */
/* Standard implementation of gp_getenv */
#include "stdio_.h"
#include "string_.h"
#include "gsmemory.h"
#include "gstypes.h"
#include "gp.h"

/* Import the C getenv function. */
extern char *getenv(const char *);

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
