/* Copyright (C) 1992, 2000, 2001 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: zcolor2.c,v 1.4 2005/12/13 16:57:28 jemarch Exp $ */
/* Level 2 color operators */
#include "ghost.h"
#include "string_.h"
#include "oper.h"
#include "gsmatrix.h"
#include "gsstruct.h"
#include "gxcspace.h"
#include "gscolor2.h"
#include "igstate.h"
#include "store.h"


/*
 *  -   .useralternate   <bool>
 *
 * Push true if the current color space contains a base or alternate
 * color space and makes use of that color space (e.g.: a Separation
 * color space for a component not supported by the process color model.
 */
private int
zusealternate(i_ctx_t * i_ctx_p)
{
    os_ptr                  op = osp;
    const gs_color_space *  pcs = gs_currentcolorspace(igs);

    push(1);
    make_bool(op, cs_base_space(pcs) != 0);
    return 0;
}


/* ------ Initialization procedure ------ */

const op_def    zcolor2_l2_op_defs[] = {
    op_def_begin_level2(),
    { "0.usealternate", zusealternate },
    op_def_end(0)
};
