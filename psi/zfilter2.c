/* Copyright (C) 2001-2006 Artifex Software, Inc.
   All Rights Reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or
  modify it under the terms of the version 2 of the GNU General Public
  License as published by the Free Software Foundation.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

/* $Id: zfilter2.c,v 1.1 2009/04/23 23:31:42 Arabidopsis Exp $ */
/* Additional filter creation */
#include "memory_.h"
#include "ghost.h"
#include "oper.h"
#include "gsstruct.h"
#include "ialloc.h"
#include "idict.h"
#include "idparam.h"
#include "store.h"
#include "strimpl.h"
#include "sfilter.h"
#include "scfx.h"
#include "slzwx.h"
#include "spdiffx.h"
#include "spngpx.h"
#include "ifilter.h"
#include "ifilter2.h"
#include "ifwpred.h"

/* ------ CCITTFaxEncode filter ------ */

/* <target> <dict> CCITTFaxEncode/filter <file> */
static int
zCFE(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    stream_CFE_state cfs;
    int code;

    check_type(*op, t_dictionary);
    check_dict_read(*op);
    code = zcf_setup(op, (stream_CF_state *)&cfs, iimemory);
    if (code < 0)
	return code;
    return filter_write(i_ctx_p, 0, &s_CFE_template, (stream_state *)&cfs, 0);
}

/* ------ Common setup for possibly pixel-oriented encoding filters ------ */

int
filter_write_predictor(i_ctx_t *i_ctx_p, int npop,
		       const stream_template * template, stream_state * st)
{
    os_ptr op = osp;
    int predictor, code;
    stream_PDiff_state pds;
    stream_PNGP_state pps;

    if (r_has_type(op, t_dictionary)) {
	if ((code = dict_int_param(op, "Predictor", 0, 15, 1, &predictor)) < 0)
	    return code;
	switch (predictor) {
	    case 0:		/* identity */
		predictor = 1;
	    case 1:		/* identity */
		break;
	    case 2:		/* componentwise horizontal differencing */
		code = zpd_setup(op, &pds);
		break;
	    case 10:
	    case 11:
	    case 12:
	    case 13:
	    case 14:
	    case 15:
		/* PNG prediction */
		code = zpp_setup(op, &pps);
		break;
	    default:
		return_error(e_rangecheck);
	}
	if (code < 0)
	    return code;
    } else
	predictor = 1;
    if (predictor == 1)
	return filter_write(i_ctx_p, npop, template, st, 0);
    {
	/* We need to cascade filters. */
	ref rtarget, rdict;
	int code;

	/* Save the operands, just in case. */
	ref_assign(&rtarget, op - 1);
	ref_assign(&rdict, op);
	code = filter_write(i_ctx_p, npop, template, st, 0);
	if (code < 0)
	    return code;
	/* filter_write changed osp.... */
	op = osp;
	code =
	    (predictor == 2 ?
	     filter_write(i_ctx_p, 0, &s_PDiffE_template, (stream_state *)&pds, 0) :
	     filter_write(i_ctx_p, 0, &s_PNGPE_template, (stream_state *)&pps, 0));
	if (code < 0) {
	    /* Restore the operands.  Don't bother trying to clean up */
	    /* the first stream. */
	    osp = ++op;
	    ref_assign(op - 1, &rtarget);
	    ref_assign(op, &rdict);
	    return code;
	}
	/*
	 * Mark the compression stream as temporary, and propagate
	 * CloseTarget from it to the predictor stream.
	 */
	filter_mark_strm_temp(op, 2);
	return code;
    }
}

/* ------ LZW encoding filter ------ */

/* <target> LZWEncode/filter <file> */
/* <target> <dict> LZWEncode/filter <file> */
static int
zLZWE(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    stream_LZW_state lzs;
    int code = zlz_setup(op, &lzs);

    if (code < 0)
	return code;
    return filter_write_predictor(i_ctx_p, 0, &s_LZWE_template,
				  (stream_state *) & lzs);
}

/* ================ Initialization procedure ================ */

const op_def zfilter2_op_defs[] =
{
    op_def_begin_filter(),
    {"2CCITTFaxEncode", zCFE},
    {"1LZWEncode", zLZWE},
    op_def_end(0)
};