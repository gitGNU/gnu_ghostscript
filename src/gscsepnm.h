/* Copyright (C) 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: gscsepnm.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Standard color space separation names */

#ifndef gscsepnm_INCLUDED
#  define gscsepnm_INCLUDED

/*
 * Define enumeration indices for the standard separation names, and the
 * corresponding name strings. These are only used internally: in all
 * externally accessible APIs, separations are defined either by a string
 * name or by an opaque identifier.
 *
 * NB: the enumeration and the list of strings must be synchronized.  */
typedef enum {
    gs_ht_separation_Default,	/* must be first */
    gs_ht_separation_Gray,
    gs_ht_separation_Red,
    gs_ht_separation_Green,
    gs_ht_separation_Blue,
    gs_ht_separation_Cyan,
    gs_ht_separation_Magenta,
    gs_ht_separation_Yellow,
    gs_ht_separation_Black
} gs_ht_separation_name;

#define gs_ht_separation_name_strings            \
    "Default", "Gray", "Red", "Green", "Blue",   \
    "Cyan", "Magenta", "Yellow", "Black"

#endif /* gscsepnm_INCLUDED */
