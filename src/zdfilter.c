/*
  Copyright (C) 2001 artofcode LLC.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 2
  as published by the Free Software Foundation.


  This software is provided AS-IS with no warranty, either express or
  implied. That is, this program is distributed in the hope that it will 
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.
  
  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.

  Author: Raph Levien <raph@artofcode.com>
*/
/* $Id: zdfilter.c,v 1.2 2004/02/14 22:20:20 atai Exp $ */
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
