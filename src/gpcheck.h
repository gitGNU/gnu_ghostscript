/* Copyright (C) 1992, 1994 artofcode LLC.  All rights reserved.
  
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

/*$Id: gpcheck.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Interrupt check interface */

#ifndef gpcheck_INCLUDED
#  define gpcheck_INCLUDED

/*
 * On some platforms, the interpreter must check periodically for user-
 * initiated actions.  (Eventually, this may be extended to all platforms,
 * to handle multi-tasking through the 'context' facility.)  Routines that
 * run for a long time must periodically call gp_check_interrupts(), and
 * if it returns true, must clean up whatever they are doing and return an
 * e_interrupted (or gs_error_interrupted) exceptional condition.
 * The return_if_interrupt macro provides a convenient way to do this.
 *
 * On platforms that require an interrupt check, the makefile defines
 * a symbol CHECK_INTERRUPTS.  Currently this is only the Microsoft
 * Windows platform.
 */
int gs_return_check_interrupt(P1(int code));

#ifdef CHECK_INTERRUPTS
int gp_check_interrupts(P0());
#  define process_interrupts() discard(gp_check_interrupts())
#  define return_if_interrupt()\
    { int icode_ = gp_check_interrupts();\
      if ( icode_ )\
	return gs_note_error((icode_ > 0 ? gs_error_interrupt : icode_));\
    }
#  define return_check_interrupt(code)\
    return gs_return_check_interrupt(code)
#else
#  define gp_check_interrupts() 0
#  define process_interrupts() DO_NOTHING
#  define return_if_interrupt()	DO_NOTHING
#  define return_check_interrupt(code)\
    return (code)
#endif

#endif /* gpcheck_INCLUDED */
