/* Copyright (C) 1996, 1997, 1998, 1999, 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: zfcid.c,v 1.2 2004/02/14 22:20:20 atai Exp $ */
/* CID-keyed font utilities */
#include "ghost.h"
#include "oper.h"
#include "gsmatrix.h"
#include "gxfcid.h"
#include "bfont.h"
#include "icid.h"
#include "idict.h"
#include "idparam.h"
#include "ifcid.h"
#include "store.h"

/* Get the CIDSystemInfo of a CIDFont. */
int
cid_font_system_info_param(gs_cid_system_info_t *pcidsi, const ref *prfont)
{
    ref *prcidsi;

    if (dict_find_string(prfont, "CIDSystemInfo", &prcidsi) <= 0)
	return_error(e_rangecheck);
    return cid_system_info_param(pcidsi, prcidsi);
}

/* Get the additional information for a CIDFontType 0 or 2 CIDFont. */
int
cid_font_data_param(os_ptr op, gs_font_cid_data *pdata, ref *pGlyphDirectory)
{
    int code;
    ref *pgdir;

    check_type(*op, t_dictionary);
    if ((code = cid_font_system_info_param(&pdata->CIDSystemInfo, op)) < 0 ||
	(code = dict_int_param(op, "CIDCount", 0, max_int, -1,
			       &pdata->CIDCount)) < 0
	)
	return code;
    /*
     * If the font doesn't have a GlyphDirectory, GDBytes is required.
     * If it does have a GlyphDirectory, GDBytes may still be needed for
     * CIDMap: it's up to the client to check this.
     */
    if (dict_find_string(op, "GlyphDirectory", &pgdir) <= 0) {
	/* Standard CIDFont, require GDBytes. */
	make_null(pGlyphDirectory);
	return dict_int_param(op, "GDBytes", 1, MAX_GDBytes, 0,
			      &pdata->GDBytes);
    }
    if (r_has_type(pgdir, t_dictionary) || r_is_array(pgdir)) {
	/* GlyphDirectory, GDBytes is optional. */
	*pGlyphDirectory = *pgdir;
	code = dict_int_param(op, "GDBytes", 1, MAX_GDBytes, 1,
			      &pdata->GDBytes);
	if (code == 1) {
	    pdata->GDBytes = 0;
	    code = 0;
	}
	return code;
    } else {
	return_error(e_typecheck);
    }
}
