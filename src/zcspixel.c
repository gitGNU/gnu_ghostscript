/* Copyright (C) 1997, 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: zcspixel.c,v 1.1 2004/01/14 16:59:53 atai Exp $ */
/* DevicePixel color space support */
#include "ghost.h"
#include "oper.h"
#include "igstate.h"
#include "gscspace.h"
#include "gsmatrix.h"		/* for gscolor2.h */
#include "gscolor2.h"
#include "gscpixel.h"

/* <array> .setdevicepixelspace - */
private int
zsetdevicepixelspace(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    ref depth;
    gs_color_space cs;
    int code;

    check_read_type(*op, t_array);
    if (r_size(op) != 2)
	return_error(e_rangecheck);
    array_get(op, 1L, &depth);
    check_type_only(depth, t_integer);
    code = gs_cspace_init_DevicePixel(&cs, (int)depth.value.intval);
    if (code < 0)
	return code;
    code = gs_setcolorspace(igs, &cs);
    if (code >= 0)
	pop(1);
    return code;
}

/* ------ Initialization procedure ------ */

const op_def zcspixel_op_defs[] =
{
    {"1.setdevicepixelspace", zsetdevicepixelspace},
    op_def_end(0)
};
