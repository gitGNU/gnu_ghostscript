/* Copyright (C) 1994, 1997, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: zhsb.c,v 1.4 2005/12/13 16:57:28 jemarch Exp $ */
/* HSB color operators */
#include "ghost.h"
#include "oper.h"
#include "igstate.h"
#include "store.h"
#include "gshsb.h"

/* - currenthsbcolor <hue> <saturation> <brightness> */
private int
zcurrenthsbcolor(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    float par[3];

    gs_currenthsbcolor(igs, par);
    push(3);
    make_floats(op - 2, par, 3);
    return 0;
}

/* <hue> <saturation> <brightness> sethsbcolor - */
private int
zsethsbcolor(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    double par[3];
    int code;

    if ((code = num_params(op, 3, par)) < 0 ||
	(code = gs_sethsbcolor(igs, par[0], par[1], par[2])) < 0
	)
	return code;
    make_null(&istate->colorspace.array);
    pop(3);
    return 0;
}

/* ------ Initialization procedure ------ */

const op_def zhsb_op_defs[] =
{
    {"0currenthsbcolor", zcurrenthsbcolor},
    {"3sethsbcolor", zsethsbcolor},
    op_def_end(0)
};
