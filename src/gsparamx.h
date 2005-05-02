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

/* $Id: gsparamx.h,v 1.3 2005/05/02 00:03:33 Arabidopsis Exp $ */
/* Interface to extended parameter dictionary utilities */

#ifndef gsparamx_INCLUDED
#  define gsparamx_INCLUDED

/* Test whether a parameter's string value is equal to a C string. */
bool gs_param_string_eq(const gs_param_string *pcs, const char *str);

/*
 * Put parameters of various types.  These propagate ecode, presumably
 * the previous accumulated error code.
 */
int param_put_enum(gs_param_list * plist, gs_param_name param_name,
		   int *pvalue, const char *const pnames[], int ecode);
int param_put_bool(gs_param_list * plist, gs_param_name param_name,
		   bool * pval, int ecode);
int param_put_int(gs_param_list * plist, gs_param_name param_name,
		  int * pval, int ecode);
int param_put_long(gs_param_list * plist, gs_param_name param_name,
		   long * pval, int ecode);

/* Copy one parameter list to another, recursively if necessary. */
int param_list_copy(gs_param_list *plto, gs_param_list *plfrom);

#endif /* gsparamx_INCLUDED */
