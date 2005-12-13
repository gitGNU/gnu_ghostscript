/* Copyright (C) 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: zfmd5.c,v 1.4 2005/12/13 16:57:28 jemarch Exp $ */
/* MD5Encode filter creation */
#include "memory_.h"
#include "ghost.h"
#include "oper.h"
#include "gsstruct.h"
#include "ialloc.h"
#include "stream.h"
#include "strimpl.h"
#include "smd5.h"
#include "ifilter.h"

/* <source> MD5Encode/filter <file> */
/* <source> <dict> MD5Encode/filter <file> */
private int
zMD5E(i_ctx_t *i_ctx_p)
{
    return filter_write_simple(i_ctx_p, &s_MD5E_template);
}

/* ------ Initialization procedure ------ */

const op_def zfmd5_op_defs[] =
{
    op_def_begin_filter(),
    {"1MD5Encode", zMD5E},
    op_def_end(0)
};
