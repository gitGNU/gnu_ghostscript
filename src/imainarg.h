/* Copyright (C) 1996, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: imainarg.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* argv/argc interface to imainarg.c */

#ifndef imainarg_INCLUDED
#  define imainarg_INCLUDED

/* Define an opaque type for an interpreter instance.  See imain.h. */
#ifndef gs_main_instance_DEFINED
#  define gs_main_instance_DEFINED
typedef struct gs_main_instance_s gs_main_instance;
#endif

/*
 * As a shortcut for very high-level clients, we define a single call
 * that does the equivalent of command line invocation, passing argc
 * and argv.  This call includes calling init0 through init2.
 * argv should really be const char *[], but ANSI C requires writable
 * strings (which, however, it forbids the callee to modify!).
 */
int gs_main_init_with_args(gs_main_instance * minst, int argc, char *argv[]);

/*
 * Run the 'start' procedure (after processing the command line).
 */
int gs_main_run_start(gs_main_instance * minst);

#endif /* imainarg_INCLUDED */
