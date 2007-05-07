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

/* $Id: ztrap.c,v 1.5 2007/05/07 11:21:44 Arabidopsis Exp $ */
/* Operators for setting trapping parameters and zones */
#include "ghost.h"
#include "oper.h"
#include "ialloc.h"
#include "iparam.h"
#include "gstrap.h"

/* Define the current trap parameters. */
/****** THIS IS BOGUS ******/
gs_trap_params_t i_trap_params;

/* <dict> .settrapparams - */
private int
zsettrapparams(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    dict_param_list list;
    int code;

    check_type(*op, t_dictionary);
    code = dict_param_list_read(&list, op, NULL, false, iimemory);
    if (code < 0)
	return code;
    code = gs_settrapparams(&i_trap_params, (gs_param_list *) & list);
    iparam_list_release(&list);
    if (code < 0)
	return code;
    pop(1);
    return 0;
}

/* - settrapzone - */
private int
zsettrapzone(i_ctx_t *i_ctx_p)
{
/****** NYI ******/
    return_error(e_undefined);
}

/* ------ Initialization procedure ------ */

const op_def ztrap_op_defs[] =
{
    op_def_begin_ll3(),
    {"1.settrapparams", zsettrapparams},
    {"0settrapzone", zsettrapzone},
    op_def_end(0)
};
