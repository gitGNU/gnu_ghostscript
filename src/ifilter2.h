/* Copyright (C) 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: ifilter2.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Utilities for Level 2 filters */

#ifndef ifilter2_INCLUDED
#  define ifilter2_INCLUDED

/* Import setup code from zfdecode.c */
int zcf_setup(P3(os_ptr op, stream_CF_state * pcfs, gs_ref_memory_t *imem));
int zlz_setup(P2(os_ptr op, stream_LZW_state * plzs));
int zpd_setup(P2(os_ptr op, stream_PDiff_state * ppds));
int zpp_setup(P2(os_ptr op, stream_PNGP_state * ppps));

#endif /* ifilter2_INCLUDED */
