/* Copyright (C) 1994, 2001 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsexit.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Declarations for exits */

#ifndef gsexit_INCLUDED
#  define gsexit_INCLUDED

/* These do not call exit() */
/* You still need to return to the caller.*/
void gs_exit_with_code(P2(int exit_status, int code));
void gs_exit(P1(int exit_status));
void gs_abort(P0());

#endif /* gsexit_INCLUDED */
