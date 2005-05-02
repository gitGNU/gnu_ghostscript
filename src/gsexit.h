/* Copyright (C) 1994, 2001 Aladdin Enterprises.  All rights reserved.
  
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

  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gsexit.h,v 1.4 2005/05/02 00:03:34 Arabidopsis Exp $ */
/* Declarations for exits */

#ifndef gsexit_INCLUDED
#  define gsexit_INCLUDED


/** The client must provide this.
 *  normally they do exit cleanup and error messaging
 *  without calling system exit() returning to the caller.
 */
int gs_to_exit(int exit_status);

/** some clients prefer this to return the postscript error code
 * to the caller otherwise the same as gs_to_exit()
 */
int gs_to_exit_with_code(int exit_status, int code);

/** The client must provide this.  
 * After possible cleanup it may call gp_do_exit() which calls exit() in a platform
 * independent way.  This is a fatal error so returning is not a good idea.
 */
void gs_abort(void);

#endif /* gsexit_INCLUDED */
