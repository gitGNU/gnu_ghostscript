/* Copyright (C) 1994, 2000 Aladdin Enterprises.  All rights reserved.
  
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
*/

/* $Id: zfbcp.c,v 1.2 2004/02/14 22:20:20 atai Exp $ */
/* (T)BCP filter creation */
#include "memory_.h"
#include "ghost.h"
#include "oper.h"
#include "gsstruct.h"
#include "ialloc.h"
#include "stream.h"
#include "strimpl.h"
#include "sbcp.h"
#include "ifilter.h"

/* Define null handlers for the BCP out-of-band signals. */
private int
no_bcp_signal_interrupt(stream_state * st)
{
    return 0;
}
private int
no_bcp_request_status(stream_state * st)
{
    return 0;
}

/* <source> BCPEncode/filter <file> */
/* <source> <dict> BCPEncode/filter <file> */
private int
zBCPE(i_ctx_t *i_ctx_p)
{
    return filter_write_simple(i_ctx_p, &s_BCPE_template);
}

/* <target> BCPDecode/filter <file> */
/* <target> <dict> BCPDecode/filter <file> */
private int
zBCPD(i_ctx_t *i_ctx_p)
{
    stream_BCPD_state state;

    state.signal_interrupt = no_bcp_signal_interrupt;
    state.request_status = no_bcp_request_status;
    return filter_read(i_ctx_p, 0, &s_BCPD_template, (stream_state *)&state, 0);
}

/* <source> TBCPEncode/filter <file> */
/* <source> <dict> TBCPEncode/filter <file> */
private int
zTBCPE(i_ctx_t *i_ctx_p)
{
    return filter_write_simple(i_ctx_p, &s_TBCPE_template);
}

/* <target> TBCPDecode/filter <file> */
/* <target> <dict> TBCPDecode/filter <file> */
private int
zTBCPD(i_ctx_t *i_ctx_p)
{
    stream_BCPD_state state;

    state.signal_interrupt = no_bcp_signal_interrupt;
    state.request_status = no_bcp_request_status;
    return filter_read(i_ctx_p, 0, &s_TBCPD_template, (stream_state *)&state, 0);
}

/* ------ Initialization procedure ------ */

const op_def zfbcp_op_defs[] =
{
    op_def_begin_filter(),
    {"1BCPEncode", zBCPE},
    {"1BCPDecode", zBCPD},
    {"1TBCPEncode", zTBCPE},
    {"1TBCPDecode", zTBCPD},
    op_def_end(0)
};
