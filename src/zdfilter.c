/*
  Copyright (C) 2001 artofcode LLC.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.


  Author: Raph Levien <raph@artofcode.com>
*/
/*$Id: zdfilter.c,v 1.1 2004/01/14 16:59:53 atai Exp $ */
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

#ifdef DFILTER_TEST
private int
/* - .pushtestdevicefilter - */
zpushtestdevicefilter(i_ctx_t *i_ctx_p)
{
    gs_device_filter_t *df;
    int code;
    gs_memory_t *mem = gs_memory_stable(imemory);

    code = gs_test_device_filter(&df, mem);
    if (code < 0)
	return code;
    code = gs_push_device_filter(mem, igs, df);
    return code;
}
#endif

/* pushpdf14devicefilter is defined in zdtrans.c */

/* - .popdevicefilter - */
private int
zpopdevicefilter(i_ctx_t *i_ctx_p)
{
    gs_memory_t *mem = gs_memory_stable(imemory);

    return gs_pop_device_filter(mem, igs);
}

const op_def zdfilter_op_defs[] =
{
#ifdef DFILTER_TEST
    {"0.pushtestdevicefilter", zpushtestdevicefilter},
#endif
    {"0.popdevicefilter", zpopdevicefilter},
    op_def_end(0)
};
