/* Copyright (C) 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: icid.h,v 1.3 2005/04/18 12:06:03 Arabidopsis Exp $ */
/* Interface to zcid.c, zfcid0.c */

#ifndef icid_INCLUDED
#  define icid_INCLUDED

#ifndef gs_cid_system_info_DEFINED
#  define gs_cid_system_info_DEFINED
typedef struct gs_cid_system_info_s gs_cid_system_info_t;
#endif

/* Get the information from a CIDSystemInfo dictionary. */
int cid_system_info_param(gs_cid_system_info_t *, const ref *);

/* Convert a CID into TT char code or to TT glyph index, using SubstNWP. */
/* Returns 1 if a glyph presents, 0 if not, <0 if error. */
int cid_to_TT_charcode(const ref *Decoding, const ref *TT_cmap,  const ref *SubstNWP, 
                       uint nCID, uint *c, ref *src_type, ref *dst_type);

/* Create a CIDMap from a True Type cmap array, Decoding and SubstNWP. */
int cid_fill_CIDMap(const ref *Decoding, const ref *TT_cmap, const ref *SubstNWP, 
                    int GDBytes, ref *CIDMap);

/* <cid9font> <cid> .type9mapcid <charstring> <font_index> */
int ztype9mapcid(i_ctx_t *i_ctx_p);

#endif /* icid_INCLUDED */
