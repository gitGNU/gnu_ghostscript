/* Copyright (C) 1989, 1992, 1993, 1994, 1996, 1997, 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: iestack.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* Generic execution stack API */

#ifndef iestack_INCLUDED
#  define iestack_INCLUDED

#include "iesdata.h"
#include "istack.h"

/* Define pointers into the execution stack. */
typedef s_ptr es_ptr;
typedef const_s_ptr const_es_ptr;

/* Manage the current_file cache. */
#define estack_clear_cache(pes) ((pes)->current_file = 0)
#define estack_set_cache(pes,pref) ((pes)->current_file = (pref))
#define estack_check_cache(pes)\
  BEGIN\
    if (r_has_type_attrs((pes)->stack.p, t_file, a_executable))\
      estack_set_cache(pes, (pes)->stack.p);\
  END

#endif /* iestack_INCLUDED */
