/* Copyright (C) 2001-2006 Artifex Software, Inc.
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

/*$Id: zcolor3.c,v 1.1 2009/04/23 23:31:34 Arabidopsis Exp $*/
/* Level 3 color operators */
#include "ghost.h"
#include "oper.h"
#include "igstate.h"
#include "store.h"


/*
 *  <bool>   .setuseciecolor  -
 *
 * Set the use_cie_color parameter for the interpreter state, which
 * corresponds to the UseCIEColor page device parameter. This parameter
 * may be read at all language levels, but it may be set only for
 * language level 3. The parameter is handled separately from the page
 * device dictionary primarily for performance reasons (it may need to
 * be checked frequently), but also to ensure proper language level
 * specific behavior.
 *
 * This operator is accessible only during initialization and is called
 * only under controlled conditions. Hence, it does not do any operand
 * checking.
 */
static int
zsetuseciecolor(i_ctx_t * i_ctx_p)
{
    os_ptr  op = osp;

    istate->use_cie_color = *op;
    pop(1);
    return 0;
}

/* - .currentrenderingintent <int> */
static int
zcurrentrenderingintent(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    push(1);
    make_int(op, gs_currentrenderingintent(igs));
    return 0;
}

/* <int> .setrenderingintent - 
 * See the comment in gsstate.c about the argumet interepretation.
 */
static int
zsetrenderingintent(i_ctx_t * i_ctx_p)
{
    os_ptr op = osp;
    int param;
    int code = int_param(op, max_int, &param);

    if (code < 0 || (code = gs_setrenderingintent(igs, param)) < 0)
	return code;
    pop(1);
    return 0;
}

/*
 * Initialization procedure
 */

const op_def    zcolor3_l3_op_defs[] = {
    op_def_begin_ll3(),
    { "0.setuseciecolor", zsetuseciecolor },
    { "0.currentrenderintent", zcurrentrenderingintent },
    { "1.setrenderingintent", zsetrenderingintent },
    op_def_end(0)
};