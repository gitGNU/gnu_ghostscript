/* Copyright (C) 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: sdcparam.h,v 1.1 2004/01/14 16:59:53 atai Exp $ */
/* DCT filter parameter setting and reading interface */

#ifndef sdcparam_INCLUDED
#  define sdcparam_INCLUDED

/*
 * All of these procedures are defined in sdcparam.c and are only for
 * internal use (by sddparam.c and sdeparam.c), so they are not
 * documented here.
 */

int s_DCT_get_params(P3(gs_param_list * plist, const stream_DCT_state * ss,
			const stream_DCT_state * defaults));
int s_DCT_get_quantization_tables(P4(gs_param_list * plist,
				     const stream_DCT_state * pdct,
				     const stream_DCT_state * defaults,
				     bool is_encode));
int s_DCT_get_huffman_tables(P4(gs_param_list * plist,
				const stream_DCT_state * pdct,
				const stream_DCT_state * defaults,
				bool is_encode));

int s_DCT_byte_params(P5(gs_param_list * plist, gs_param_name key, int start,
			 int count, UINT8 * pvals));
int s_DCT_put_params(P2(gs_param_list * plist, stream_DCT_state * pdct));
int s_DCT_put_quantization_tables(P3(gs_param_list * plist,
				     stream_DCT_state * pdct,
				     bool is_encode));
int s_DCT_put_huffman_tables(P3(gs_param_list * plist, stream_DCT_state * pdct,
				bool is_encode));

#endif /* sdcparam_INCLUDED */
