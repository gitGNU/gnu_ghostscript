/* Copyright (C) 1995, 1996, 1998 artofcode LLC.  All rights reserved.
  
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

*/

/*$Id: gsrop.c,v 1.1 2004/01/14 16:59:50 atai Exp $ */
/* RasterOp / transparency accessing for library */
#include "gx.h"
#include "gserrors.h"
#include "gzstate.h"
#include "gsrop.h"

/* setrasterop */
int
gs_setrasterop(gs_state * pgs, gs_rop3_t rop)
{
    if (pgs->in_cachedevice)
	return_error(gs_error_undefined);
    pgs->log_op = (rop & rop3_1) | (pgs->log_op & ~rop3_1);
    return 0;
}

/* currentrasterop */
gs_rop3_t
gs_currentrasterop(const gs_state * pgs)
{
    return lop_rop(pgs->log_op);
}

/* setsourcetransparent */
int
gs_setsourcetransparent(gs_state * pgs, bool transparent)
{
    if (pgs->in_cachedevice)
	return_error(gs_error_undefined);
    pgs->log_op =
	(transparent ? pgs->log_op | lop_S_transparent :
	 pgs->log_op & ~lop_S_transparent);
    return 0;
}

/* currentsourcetransparent */
bool
gs_currentsourcetransparent(const gs_state * pgs)
{
    return (pgs->log_op & lop_S_transparent) != 0;
}

/* settexturetransparent */
int
gs_settexturetransparent(gs_state * pgs, bool transparent)
{
    if (pgs->in_cachedevice)
	return_error(gs_error_undefined);
    pgs->log_op =
	(transparent ? pgs->log_op | lop_T_transparent :
	 pgs->log_op & ~lop_T_transparent);
    return 0;
}

/* currenttexturetransparent */
bool
gs_currenttexturetransparent(const gs_state * pgs)
{
    return (pgs->log_op & lop_T_transparent) != 0;
}

/* Save/restore logical operation.  (For internal use only.) */
int
gs_set_logical_op(gs_state * pgs, gs_logical_operation_t lop)
{
    pgs->log_op = lop;
    return 0;
}
gs_logical_operation_t
gs_current_logical_op(const gs_state * pgs)
{
    return pgs->log_op;
}
