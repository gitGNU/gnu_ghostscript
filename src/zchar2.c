/* Copyright (C) 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: zchar2.c,v 1.3 2005/05/02 00:03:27 Arabidopsis Exp $ */
/* Type 2 character display operator */
#include "ghost.h"
#include "oper.h"
#include "gxfixed.h"
#include "gxmatrix.h"
#include "gxfont.h"
#include "gxfont1.h"
#include "gxtype1.h"
#include "ichar1.h"

/* <font> <code|name> <name> <charstring> .type2execchar - */
private int
ztype2execchar(i_ctx_t *i_ctx_p)
{
    return charstring_execchar(i_ctx_p, (1 << (int)ft_encrypted2));
}

/* ------ Initialization procedure ------ */

const op_def zchar2_op_defs[] =
{
    {"4.type2execchar", ztype2execchar},
    op_def_end(0)
};
