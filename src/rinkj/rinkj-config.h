/* Copyright (C) 2000-2004 artofcode LLC.  All rights reserved.
  
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

/*$Id: rinkj-config.h,v 1.1 2006/03/08 12:30:41 Arabidopsis Exp $ */
/* Support for reading Rinkj config files. */

char *
rinkj_strdup_size (const char *src, int size);

char *
rinkj_config_get (const char *config, const char *key);

char *
rinkj_config_keyval (const char *config, char **p_val, const char **p_next);
