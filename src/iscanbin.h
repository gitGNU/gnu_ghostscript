/* Copyright (C) 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: iscanbin.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* Interface to binary token scanner */

#ifndef iscanbin_INCLUDED
#  define iscanbin_INCLUDED

/*
 * Scan a binary token.  The main scanner calls this iff recognize_btokens()
 * is true.  Return e_unregistered if Level 2 features are not included.
 * Return 0 or scan_BOS on success, <0 on failure.
 *
 * This header file exists only because there are two implementations of
 * this procedure: a dummy one for Level 1 systems, and the real one.
 * The interface is entirely internal to the scanner.
 */
int scan_binary_token(i_ctx_t *i_ctx_p, stream *s, ref *pref,
		      scanner_state *pstate);

#endif /* iscanbin_INCLUDED */
