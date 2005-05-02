/* Copyright (C) 1995, 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gscpm.h,v 1.3 2005/05/02 00:03:21 Arabidopsis Exp $ */
/* Charpath mode and cache device status definitions */

#ifndef gscpm_INCLUDED
#  define gscpm_INCLUDED

typedef enum {
    cpm_show,			/* *show (default, must be 0) */
    cpm_charwidth,		/* stringwidth rmoveto (not standard PS) */
    cpm_false_charpath,		/* false charpath */
    cpm_true_charpath,		/* true charpath */
    cpm_false_charboxpath,	/* false charboxpath (not standard PS) */
    cpm_true_charboxpath	/* true charboxpath (ditto) */
} gs_char_path_mode;

typedef enum {
    CACHE_DEVICE_NONE = 0,	/* default, must be 0 */
    CACHE_DEVICE_NOT_CACHING,	/* setcachedevice done but not caching */
    CACHE_DEVICE_CACHING	/* setcachedevice done and caching */
} gs_in_cache_device_t;

#endif /* gscpm_INCLUDED */
