/* Copyright (C) 1992, 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: ilevel.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Interpreter language level interface */

#ifndef ilevel_INCLUDED
#  define ilevel_INCLUDED

/* The current interpreter language level */
#define LANGUAGE_LEVEL (i_ctx_p->language_level)
#define LL2_ENABLED (LANGUAGE_LEVEL >= 2)
#define LL3_ENABLED (LANGUAGE_LEVEL >= 3)
#define level2_enabled LL2_ENABLED	/* backward compatibility */

#endif /* ilevel_INCLUDED */
