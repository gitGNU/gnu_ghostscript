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

/*$Id: icid.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Interface to zcid.c */

#ifndef icid_INCLUDED
#  define icid_INCLUDED

/* Get the information from a CIDSystemInfo dictionary. */
int cid_system_info_param(P2(gs_cid_system_info_t *, const ref *));

#endif /* icid_INCLUDED */
