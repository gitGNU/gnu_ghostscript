/* Copyright (C) 1992, 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: zimage2.c,v 1.2 2004/02/14 22:20:20 atai Exp $ */
/* image operator extensions for Level 2 PostScript */
#include "memory_.h"
#include "ghost.h"
#include "gsimage.h"
#include "gxiparam.h"
#include "icstate.h"
#include "iimage2.h"
#include "igstate.h"		/* for igs */


/*
 * Process an image that has no explicit source data.  This isn't used by
 * standard Level 2, but it's a very small procedure and is needed by
 * both zdps.c and zdpnext.c.
 */
int
process_non_source_image(i_ctx_t *i_ctx_p, const gs_image_common_t * pic,
			 client_name_t cname)
{
    gx_image_enum_common_t *pie;
    int code = gs_image_begin_typed(pic, igs, false /****** WRONG ******/ ,
				    &pie);

    /* We didn't pass any data, so there's nothing to clean up. */
    return code;
}
