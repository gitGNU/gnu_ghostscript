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

/*$Id: iconf.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Collected imports for interpreter configuration and initialization */

#ifndef iconf_INCLUDED
#define iconf_INCLUDED
/* ------ Imported data ------ */

/* Configuration information imported from iccinit[01].c */
extern const byte gs_init_string[];
extern const uint gs_init_string_sizeof;

/* Configuration information imported from iconf.c */
extern const ref gs_init_file_array[];
extern const ref gs_emulator_name_array[];

#endif /* iconf_INCLUDED */
