/* Copyright (C) 2000 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: itoken.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* Interface to exported procedures in ztoken.c */

#ifndef itoken_INCLUDED
#  define itoken_INCLUDED

/*
 * Continue after handling a procedure stream refill or other callout
 * while reading tokens in the interpreter.
 */
int ztokenexec_continue(i_ctx_t *i_ctx_p);

/*
 * Handle a scan_Comment or scan_DSC_Comment return from scan_token.
 */
#ifndef scanner_state_DEFINED
#  define scanner_state_DEFINED
typedef struct scanner_state_s scanner_state;
#endif
int ztoken_handle_comment(i_ctx_t *i_ctx_p, const ref *fop,
			  scanner_state *sstate, const ref *ptoken,
			  int scan_code, bool save, bool push_file,
			  op_proc_t cont);

/*
 * Update the cached scanner_options in the context state after doing a
 * setuserparams.  (We might move this procedure somewhere else eventually.)
 */
int ztoken_scanner_options(const ref *upref, int old_options);

#endif /* itoken_INCLUDED */
