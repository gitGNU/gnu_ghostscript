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

/* $Id: gx.h,v 1.7 2007/05/07 11:21:44 Arabidopsis Exp $ */
/* Common internal definitions for Ghostscript library */

#ifndef gx_INCLUDED
#  define gx_INCLUDED

#include "stdio_.h"		/* includes std.h */
#include "gserror.h"
#include "gsio.h"
#include "gstypes.h"
#include "gsmemory.h"
#include "gdebug.h"

/* Define opaque types for the graphics state. */
/* This is used so pervasively that we define it here, */
/* rather than at a higher level as perhaps would be more appropriate. */
#ifndef gs_imager_state_DEFINED
#  define gs_imager_state_DEFINED
typedef struct gs_imager_state_s gs_imager_state;

#endif
#ifndef gs_state_DEFINED
#  define gs_state_DEFINED
typedef struct gs_state_s gs_state;

#endif

#endif /* gx_INCLUDED */
