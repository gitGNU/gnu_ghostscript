/* Copyright (C) 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: icremap.h,v 1.3 2005/05/02 00:03:33 Arabidopsis Exp $ */
/* Interpreter color remapping structure */

#ifndef icremap_INCLUDED
#  define icremap_INCLUDED

#include "gsccolor.h"

/*
 * Define the structure used to communicate information back to the
 * interpreter for color remapping.  Pattern remapping doesn't use the
 * tint values, DeviceN remapping does.
 */
#ifndef int_remap_color_info_DEFINED
#  define int_remap_color_info_DEFINED
typedef struct int_remap_color_info_s int_remap_color_info_t;
#endif
struct int_remap_color_info_s {
    op_proc_t proc;		/* remapping procedure */
    float tint[GS_CLIENT_COLOR_MAX_COMPONENTS];
};

#define private_st_int_remap_color_info() /* in zgstate.c */\
  gs_private_st_simple(st_int_remap_color_info, int_remap_color_info_t,\
    "int_remap_color_info_t")

#endif /* icremap_INCLUDED */
