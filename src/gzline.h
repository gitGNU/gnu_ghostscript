/* Copyright (C) 1989, 1995, 1996 Aladdin Enterprises.  All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 2
  as published by the Free Software Foundation.


  This software is provided AS-IS with no warranty, either express or
  implied. That is, this program is distributed in the hope that it will 
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.
  
  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gzline.h,v 1.2 2004/02/14 22:20:18 atai Exp $ */
/* Line parameter implementation */

#ifndef gzline_INCLUDED
#  define gzline_INCLUDED

#include "gxline.h"

/*
 * The GC procedures are complex because we must not attempt to follow
 * the pattern pointer iff the pattern size is 0.
 */
#define private_st_line_params() /* in gsistate.c */\
  gs_private_st_complex_only(st_line_params, gx_line_params, "line_params",\
    0, line_params_enum_ptrs, line_params_reloc_ptrs, 0)
#define st_line_params_num_ptrs 1

/* Internal accessor for line parameters in graphics state */
const gx_line_params *gs_currentlineparams(const gs_imager_state *);

#endif /* gzline_INCLUDED */
