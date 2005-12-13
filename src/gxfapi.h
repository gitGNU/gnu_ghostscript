/* Copyright (C) 1991, 2000 Aladdin Enterprises.  All rights reserved.
  
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

  
*/

/* $Id: gxfapi.h,v 1.3 2005/12/13 16:57:24 jemarch Exp $ */
/* Font API support */

#ifndef gxfapi_INCLUDED
#  define gxfapi_INCLUDED

void gx_set_UFST_Callbacks(LPUB8 (*p_PCLEO_charptr)(LPUB8 pfont_hdr, UW16  sym_code),
			   LPUB8 (*p_PCLchId2ptr)(IF_STATE *pIFS, UW16 chId),
			   LPUB8 (*p_PCLglyphID2Ptr)(IF_STATE *pIFS, UW16 glyphID));

void gx_reset_UFST_Callbacks(void);

#endif /* gxfapi_INCLUDED */
