/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free Software
  Foundation; either version 2, or (at your option) any later version.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

/* $Id: iconf.h,v 1.5 2007/05/07 11:21:45 Arabidopsis Exp $ */
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
