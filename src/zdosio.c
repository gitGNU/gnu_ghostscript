/* Copyright (C) 1992, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: zdosio.c,v 1.3 2005/05/02 00:03:33 Arabidopsis Exp $ */
/* MS-DOS direct I/O operators. */
/* These should NEVER be included in a released configuration! */
#include "dos_.h"
#include "ghost.h"
#include "oper.h"
#include "store.h"

/* <port> .inport <word> */
private int
zinport(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_integer);
    make_int(op, inport((int)op->value.intval));
    return 0;
}

/* <port> .inportb <byte> */
private int
zinportb(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_integer);
    make_int(op, inportb((int)op->value.intval));
    return 0;
}

/* <port> <word> .outport - */
private int
zoutport(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_integer);
    check_type(op[-1], t_integer);
    outport((int)op[-1].value.intval, (int)op->value.intval);
    pop(1);
    return 0;
}

/* <port> <byte> .outportb - */
private int
zoutportb(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_integer);
    check_int_leu(op[-1], 0xff);
    outportb((int)op[-1].value.intval, (byte) op->value.intval);
    pop(1);
    return 0;
}

/* <loc> .peek <byte> */
private int
zpeek(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_integer);
    make_int(op, *(byte *) (op->value.intval));
    return 0;
}

/* <loc> <byte> .poke - */
private int
zpoke(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_integer);
    check_int_leu(op[-1], 0xff);
    *(byte *) (op[-1].value.intval) = (byte) op->value.intval;
    pop(1);
    return 0;
}

/* ------ Operator initialization ------ */

const op_def zdosio_op_defs[] =
{
    {"1.inport", zinport},
    {"1.inportb", zinportb},
    {"2.outport", zoutport},
    {"2.outportb", zoutportb},
    {"1.peek", zpeek},
    {"2.poke", zpoke},
    op_def_end(0)
};
