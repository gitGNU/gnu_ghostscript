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

/* $Id: zchar2.c,v 1.5 2007/05/07 11:21:46 Arabidopsis Exp $ */
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
