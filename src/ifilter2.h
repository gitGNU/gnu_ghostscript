/* Copyright (C) 1999 Aladdin Enterprises.  All rights reserved.
  
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

  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: ifilter2.h,v 1.3 2005/05/02 00:03:27 Arabidopsis Exp $ */
/* Utilities for Level 2 filters */

#ifndef ifilter2_INCLUDED
#  define ifilter2_INCLUDED

/* Import setup code from zfdecode.c */
int zcf_setup(os_ptr op, stream_CF_state * pcfs, gs_ref_memory_t *imem);
int zlz_setup(os_ptr op, stream_LZW_state * plzs);
int zpd_setup(os_ptr op, stream_PDiff_state * ppds);
int zpp_setup(os_ptr op, stream_PNGP_state * ppps);

#endif /* ifilter2_INCLUDED */
