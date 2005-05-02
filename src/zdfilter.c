/*
  Copyright (C) 2001 artofcode LLC.
  
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

  Author: Raph Levien <raph@artofcode.com>
*/
/* $Id: zdfilter.c,v 1.3 2005/05/02 00:03:26 Arabidopsis Exp $ */
/* PostScript operators for managing the device filter stack */

/* We probably don't need all of these, they were copied from zdevice.c. */
#include "string_.h"
#include "ghost.h"
#include "oper.h"
#include "ialloc.h"
#include "idict.h"
#include "igstate.h"
#include "iname.h"
#include "interp.h"
#include "iparam.h"
#include "ivmspace.h"
#include "gsmatrix.h"
#include "gsstate.h"
#include "gxdevice.h"
#include "store.h"
#include "gsdfilt.h"

/* pushpdf14devicefilter is defined in ztrans.c */

/* - .popdevicefilter - */
private int
zpopdevicefilter(i_ctx_t *i_ctx_p)
{
    gs_memory_t *mem = gs_memory_stable(imemory);

    return gs_pop_device_filter(mem, igs);
}

const op_def zdfilter_op_defs[] =
{
    {"0.popdevicefilter", zpopdevicefilter},
    op_def_end(0)
};
