/* Copyright (C) 1997, 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gxhttype.h,v 1.2 2004/02/14 22:20:18 atai Exp $ */
/* Client halftone type enumeration */

#ifndef gxhttype_INCLUDED
#  define gxhttype_INCLUDED

/* Halftone types */
typedef enum {
    ht_type_none,		/* is this needed? */
    ht_type_screen,		/* set by setscreen */
    ht_type_colorscreen,	/* set by setcolorscreen */
    ht_type_spot,		/* Type 1 halftone dictionary */
    ht_type_threshold,		/* Type 3 halftone dictionary */
    ht_type_threshold2,		/* Extended Type 3 halftone dictionary */
				/* (Type 3 with either 8- or 16-bit */
				/* samples, bytestring instead of string */
				/* thresholds, and 1 or 2 rectangles) */
    ht_type_multiple,		/* Type 5 halftone dictionary */
    ht_type_multiple_colorscreen,  /* Type 5 halftone dictionary */
				/* created from Type 2 or Type 4 */
				/* halftone dictionary  */
    ht_type_client_order	/* client-defined, creating a gx_ht_order */
} gs_halftone_type;

#endif /* gxhttype_INCLUDED */
