/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsalpha.c,v 1.2 2004/02/14 22:20:16 atai Exp $ */
/* Graphics state alpha value access */
#include "gx.h"
#include "gsalpha.h"
#include "gxdcolor.h"
#include "gzstate.h"

/* setalpha */
int
gs_setalpha(gs_state * pgs, floatp alpha)
{
    pgs->alpha =
	(gx_color_value) (alpha < 0 ? 0 : alpha > 1 ? gx_max_color_value :
			  alpha * gx_max_color_value);
    gx_unset_dev_color(pgs);
    return 0;
}

/* currentalpha */
float
gs_currentalpha(const gs_state * pgs)
{
    return (float)pgs->alpha / gx_max_color_value;
}
