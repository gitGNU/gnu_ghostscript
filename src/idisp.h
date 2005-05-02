/* Copyright (C) 2001, Ghostgum Software Pty Ltd.  All rights reserved.

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

/* $Id: idisp.h,v 1.3 2005/05/02 00:03:34 Arabidopsis Exp $ */

#ifndef idisp_INCLUDED
#  define idisp_INCLUDED

#ifndef display_callback_DEFINED
# define display_callback_DEFINED
typedef struct display_callback_s display_callback;
#endif

/* Called from imain.c to set the display callback in the device instance. */
int display_set_callback(gs_main_instance *minst, display_callback *callback);


#endif /* idisp_INCLUDED */
