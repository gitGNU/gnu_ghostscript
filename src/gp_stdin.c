/* Copyright (C) 2001 artofcode LLC.  All rights reserved.
  
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

/*$Id: gp_stdin.c,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Read stdin on platforms that do not support unbuffered read.
 * This is the most portable implementation, but it is very slow
 * when reading stdin because it will read one byte at a time.
 * Platforms that support unbuffered read should use gp_stdia.c
 * or provide their own implementation
 */

#include "stdio_.h"
#include "gx.h"
#include "gp.h"

/* Read bytes from stdin, using unbuffered if possible.
 * This implementation doesn't do unbuffered, so if 
 * interactive read one byte at a time.
 */
int gp_stdin_read(char *buf, int len, int interactive, FILE *f)
{
    return fread(buf, 1, interactive ? 1 : len, f);
}

