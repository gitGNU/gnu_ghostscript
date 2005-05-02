/* Copyright (C) 1995, 1996, 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: zrop.c,v 1.3 2005/05/02 00:03:34 Arabidopsis Exp $ */
/* RasterOp control operators */
#include "memory_.h"
#include "ghost.h"
#include "oper.h"
#include "gsrop.h"
#include "gsutil.h"
#include "gxdevice.h"
#include "idict.h"
#include "idparam.h"
#include "igstate.h"
#include "store.h"

/* <int8> .setrasterop - */
private int
zsetrasterop(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    int param;
    int code = int_param(op, 0xff, &param);

    if (code < 0)
	return code;
    gs_setrasterop(igs, (gs_rop3_t)param);
    pop(1);
    return 0;
}

/* - .currentrasterop <int8> */
private int
zcurrentrasterop(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    push(1);
    make_int(op, (int)gs_currentrasterop(igs));
    return 0;
}

/* <bool> .setsourcetransparent - */
private int
zsetsourcetransparent(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_boolean);
    gs_setsourcetransparent(igs, op->value.boolval);
    pop(1);
    return 0;
}

/* - .currentsourcetransparent <bool> */
private int
zcurrentsourcetransparent(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    push(1);
    make_bool(op, gs_currentsourcetransparent(igs));
    return 0;
}

/* <bool> .settexturetransparent - */
private int
zsettexturetransparent(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_boolean);
    gs_settexturetransparent(igs, op->value.boolval);
    pop(1);
    return 0;
}

/* - .currenttexturetransparent <bool> */
private int
zcurrenttexturetransparent(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    push(1);
    make_bool(op, gs_currenttexturetransparent(igs));
    return 0;
}

/* ------ Initialization procedure ------ */

const op_def zrop_op_defs[] =
{
    {"0.currentrasterop", zcurrentrasterop},
    {"0.currentsourcetransparent", zcurrentsourcetransparent},
    {"0.currenttexturetransparent", zcurrenttexturetransparent},
    {"1.setrasterop", zsetrasterop},
    {"1.setsourcetransparent", zsetsourcetransparent},
    {"1.settexturetransparent", zsettexturetransparent},
    op_def_end(0)
};
