/* Copyright (C) 1989, 1993, 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: gserrors.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Error code definitions */

#ifndef gserrors_INCLUDED
#  define gserrors_INCLUDED

/* A procedure that may return an error always returns */
/* a non-negative value (zero, unless otherwise noted) for success, */
/* or negative for failure. */
/* We use ints rather than an enum to avoid a lot of casting. */

#define gs_error_unknownerror (-1)	/* unknown error */
#ifdef gs_error_interrupt
#undef gs_error_interrupt
#endif
#define gs_error_interrupt (-6)
#define gs_error_invalidaccess (-7)
#define gs_error_invalidfileaccess (-9)
#define gs_error_invalidfont (-10)
#define gs_error_ioerror (-12)
#define gs_error_limitcheck (-13)
#define gs_error_nocurrentpoint (-14)
#define gs_error_rangecheck (-15)
#define gs_error_typecheck (-20)
#define gs_error_undefined (-21)
#define gs_error_undefinedfilename (-22)
#define gs_error_undefinedresult (-23)
#define gs_error_VMerror (-25)
#define gs_error_unregistered (-29)

#define gs_error_hit_detected (-99)

#define gs_error_Fatal (-100)

#endif /* gserrors_INCLUDED */
