/* Copyright (C) 2001-2006 Artifex Software, Inc.
   All Rights Reserved.
  
   This software is provided AS-IS with no warranty, either express or
   implied.

   This software is distributed under license and may not be copied, modified
   or distributed except as expressly authorized under the terms of that
   license.  Refer to licensing information at http://www.artifex.com/
   or contact Artifex Software, Inc.,  7 Mt. Lassen Drive - Suite A-134,
   San Rafael, CA  94903, U.S.A., +1(415)492-9861, for further information.
*/
/* $Id: gscedata.h,v 1.2 2010/07/10 22:02:19 Arabidopsis Exp $ */
/*
 * This file contains substantial parts of toolbin/encs2c.ps,
 * which generated the remainder of the file mechanically from
 *   gs_std_e.ps  gs_il1_e.ps  gs_sym_e.ps  gs_dbt_e.ps
 *   gs_wan_e.ps  gs_mro_e.ps  gs_mex_e.ps  gs_mgl_e.ps
 *   gs_lgo_e.ps  gs_lgx_e.ps  gs_css_e.ps
 *
 * This source file is maintained manually under source code control,
 * however its content should be regenerated by using encs2c.ps
 * if changes are required.
 */

#ifndef gscedata_INCLUDED
#  define gscedata_INCLUDED

#define NUM_LEN_BITS 5

#define N(len,offset) (((offset) << NUM_LEN_BITS) + (len))
#define N_LEN(e) ((e) & ((1 << NUM_LEN_BITS) - 1))
#define N_OFFSET(e) ((e) >> NUM_LEN_BITS)

extern const char gs_c_known_encoding_chars[];
extern const int gs_c_known_encoding_total_chars;
extern const int gs_c_known_encoding_max_length;
extern const ushort gs_c_known_encoding_offsets[];
extern const int gs_c_known_encoding_count;
extern const ushort *const gs_c_known_encodings[];
extern const ushort *const gs_c_known_encodings_reverse[];
extern const ushort gs_c_known_encoding_lengths[];
extern const ushort gs_c_known_encoding_reverse_lengths[];

#endif /* gscedata_INCLUDED */
