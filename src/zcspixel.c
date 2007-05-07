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

/* $Id: zcspixel.c,v 1.6 2007/05/07 11:21:43 Arabidopsis Exp $ */
/* DevicePixel color space support */
#include "ghost.h"
#include "oper.h"
#include "igstate.h"
#include "gscspace.h"
#include "gsmatrix.h"		/* for gscolor2.h */
#include "gscolor2.h"
#include "gscpixel.h"
#include "ialloc.h"

/* <array> .setdevicepixelspace - */
private int
zsetdevicepixelspace(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    ref depth;
    gs_color_space *pcs;
    int code;

    check_read_type(*op, t_array);
    if (r_size(op) != 2)
	return_error(e_rangecheck);
    array_get(imemory, op, 1L, &depth);
    check_type_only(depth, t_integer);
    code = gs_cspace_new_DevicePixel(imemory, &pcs, (int)depth.value.intval);
    if (code < 0)
	return code;
    code = gs_setcolorspace(igs, pcs);
    /* release reference from construction */
    rc_decrement_only(pcs, "zsetseparationspace");
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
