/* Copyright (C) 1994-1996, Russell Lang.  All rights reserved.
  
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

/*$Id: gsdllos2.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* gsdll extension for OS/2 platforms */

#ifndef gsdllos2_INCLUDED
#  define gsdllos2_INCLUDED

/* DLL exported functions */
/* for load time dynamic linking */
unsigned long gsdll_get_bitmap(unsigned char *device, unsigned char **pbitmap);

/* Function pointer typedefs */
/* for run time dynamic linking */
typedef long (*GSDLLAPI PFN_gsdll_get_bitmap) (unsigned char *, unsigned char **);

#endif /* gsdllos2_INCLUDED */
