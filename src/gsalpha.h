/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsalpha.h,v 1.4 2005/12/13 16:57:20 jemarch Exp $ */
/* API for alpha value in graphics state */

#ifndef gsalpha_INCLUDED
#  define gsalpha_INCLUDED

/*
 * This tiny little file is separate so that it can be included by
 * gsstate.c for initializing the alpha value, even in configurations
 * that don't have full alpha support.
 */

/* Set/read alpha value. */
int gs_setalpha(gs_state *, floatp);
float gs_currentalpha(const gs_state *);

#endif /* gsalpha_INCLUDED */
