/* Copyright (C) 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: sdcparam.h,v 1.3 2005/05/02 00:03:34 Arabidopsis Exp $ */
/* DCT filter parameter setting and reading interface */

#ifndef sdcparam_INCLUDED
#  define sdcparam_INCLUDED

/*
 * All of these procedures are defined in sdcparam.c and are only for
 * internal use (by sddparam.c and sdeparam.c), so they are not
 * documented here.
 */

int s_DCT_get_params(gs_param_list * plist, const stream_DCT_state * ss,
		     const stream_DCT_state * defaults);
int s_DCT_get_quantization_tables(gs_param_list * plist,
				  const stream_DCT_state * pdct,
				  const stream_DCT_state * defaults,
				  bool is_encode);
int s_DCT_get_huffman_tables(gs_param_list * plist,
			     const stream_DCT_state * pdct,
			     const stream_DCT_state * defaults,
			     bool is_encode);

int s_DCT_byte_params(gs_param_list * plist, gs_param_name key, int start,
		      int count, UINT8 * pvals);
int s_DCT_put_params(gs_param_list * plist, stream_DCT_state * pdct);
int s_DCT_put_quantization_tables(gs_param_list * plist,
				  stream_DCT_state * pdct,
				  bool is_encode);
int s_DCT_put_huffman_tables(gs_param_list * plist, stream_DCT_state * pdct,
			     bool is_encode);

#endif /* sdcparam_INCLUDED */
