/* Copyright (C) 2001, Ghostgum Software Pty Ltd.  All rights reserved.
  
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

/*$Id: dwreg.h,v 1.1 2004/01/14 16:59:47 atai Exp $ */

#ifndef dwreg_INCLUDED
#  define dwreg_INCLUDED

/* Get and set named registry values for Ghostscript application. */
int win_get_reg_value(const char *name, char *ptr, int *plen);
int win_set_reg_value(const char *name, const char *value);

#endif /* dwreg_INCLUDED */
