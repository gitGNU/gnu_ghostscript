/* Copyright (C) 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: ifcid.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Interface to zfcid.c */

#ifndef ifcid_INCLUDED
#  define ifcid_INCLUDED

/* Get the CIDSystemInfo of a CIDFont. */
int cid_font_system_info_param(P2(gs_cid_system_info_t *pcidsi,
				  const ref *prfont));

/* Get the additional information for a CIDFontType 0 or 2 CIDFont. */
int cid_font_data_param(P3(os_ptr op, gs_font_cid_data *pdata,
			   ref *pGlyphDirectory));

#endif /* ifcid_INCLUDED */
