/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or
  modify it under the terms of the version 2 of the GNU General Public
  License as published by the Free Software Foundation.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

/* $Id: zpaint.c,v 1.6 2007/08/01 14:26:53 jemarch Exp $ */
/* Painting operators */
#include "ghost.h"
#include "oper.h"
#include "gspaint.h"
#include "igstate.h"

/* - fill - */
private int
zfill(i_ctx_t *i_ctx_p)
{
    return gs_fill(igs);
}

/* - eofill - */
private int
zeofill(i_ctx_t *i_ctx_p)
{
    return gs_eofill(igs);
}

/* - stroke - */
private int
zstroke(i_ctx_t *i_ctx_p)
{
    return gs_stroke(igs);
}

/* ------ Non-standard operators ------ */

/* - .fillpage - */
private int
zfillpage(i_ctx_t *i_ctx_p)
{
    return gs_fillpage(igs);
}

/* <width> <height> <data> .imagepath - */
private int
zimagepath(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    int code;

    check_type(op[-2], t_integer);
    check_type(op[-1], t_integer);
    check_read_type(*op, t_string);
    if (r_size(op) < ((op[-2].value.intval + 7) >> 3) * op[-1].value.intval)
	return_error(e_rangecheck);
    code = gs_imagepath(igs,
			(int)op[-2].value.intval, (int)op[-1].value.intval,
			op->value.const_bytes);
    if (code >= 0)
	pop(3);
    return code;
}

/* ------ Initialization procedure ------ */

const op_def zpaint_op_defs[] =
{
    {"0eofill", zeofill},
    {"0fill", zfill},
    {"0stroke", zstroke},
		/* Non-standard operators */
    {"0.fillpage", zfillpage},
    {"3.imagepath", zimagepath},
    op_def_end(0)
};
