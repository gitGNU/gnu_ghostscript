/* Copyright (C) 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: sddparam.c,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* DCTDecode filter parameter setting and reading */
#include "std.h"
#include "jpeglib_.h"
#include "gserror.h"
#include "gserrors.h"
#include "gstypes.h"
#include "gsmemory.h"
#include "gsparam.h"
#include "strimpl.h"		/* sdct.h requires this */
#include "sdct.h"
#include "sdcparam.h"
#include "sjpeg.h"

/* ================ Get parameters ================ */

stream_state_proc_get_params(s_DCTD_get_params, stream_DCT_state);	/* check */

int
s_DCTD_get_params(gs_param_list * plist, const stream_DCT_state * ss, bool all)
{
    stream_DCT_state dcts_defaults;
    const stream_DCT_state *defaults;

    if (all)
	defaults = 0;
    else {
	(*s_DCTE_template.set_defaults) ((stream_state *) & dcts_defaults);
	defaults = &dcts_defaults;
    }
/****** NYI ******/
    return s_DCT_get_params(plist, ss, defaults);
}

/* ================ Put parameters ================ */

stream_state_proc_put_params(s_DCTD_put_params, stream_DCT_state);	/* check */

int
s_DCTD_put_params(gs_param_list * plist, stream_DCT_state * pdct)
{
    int code;

    if ((code = s_DCT_put_params(plist, pdct)) < 0 ||
    /*
     * DCTDecode accepts quantization and huffman tables
     * in case these tables have been omitted from the datastream.
     */
	(code = s_DCT_put_huffman_tables(plist, pdct, false)) < 0 ||
	(code = s_DCT_put_quantization_tables(plist, pdct, false)) < 0
	)
	DO_NOTHING;
    return code;
}
