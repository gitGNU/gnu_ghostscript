/* Copyright (C) 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: gpmisc.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Miscellaneous support for platform facilities */

#ifndef gpmisc_INCLUDED
#  define gpmisc_INCLUDED

/*
 * The facilities defined in this file and implemented in gpmisc.c are
 * generic utilities shared among multiple gp_ platform files.
 */

/*
 * Get the name of the directory for temporary files, if any.  Currently
 * this checks the TMPDIR and TEMP environment variables, in that order.
 * The return value and the setting of *ptr and *plen are as for gp_getenv.
 */
int gp_gettmpdir(P2(char *ptr, int *plen));

/*
 * Open a temporary file, using O_EXCL and S_IRWXU to prevent race
 * conditions and symlink attacks.
 */
FILE *gp_fopentemp(P2(const char *fname, const char *mode));

#endif /* gpmisc_INCLUDED */
