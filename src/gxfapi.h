/* Copyright (C) 1991, 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gxfapi.h,v 1.1 2004/02/14 22:32:08 atai Exp $ */
/* Font API support */

#ifndef gxfapi_INCLUDED
#  define gxfapi_INCLUDED

void gx_set_UFST_Callbacks(LPUB8 (*p_PCLEO_charptr)(LPUB8 pfont_hdr, UW16  sym_code),
			   LPUB8 (*p_PCLchId2ptr)(IF_STATE *pIFS, UW16 chId),
			   LPUB8 (*p_PCLglyphID2Ptr)(IF_STATE *pIFS, UW16 glyphID));

void gx_reset_UFST_Callbacks(void);

#endif /* gxfapi_INCLUDED */
