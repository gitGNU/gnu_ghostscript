/* Copyright (C) 2001, Ghostgum Software Pty Ltd.  All rights reserved.
  
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

/* $Id: dwreg.h,v 1.2 2004/02/14 22:20:05 atai Exp $ */

#ifndef dwreg_INCLUDED
#  define dwreg_INCLUDED

/* Get and set named registry values for Ghostscript application. */
int win_get_reg_value(const char *name, char *ptr, int *plen);
int win_set_reg_value(const char *name, const char *value);

#endif /* dwreg_INCLUDED */
