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

/* $Id: idosave.h,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* Supporting procedures for 'save' recording. */

#ifndef idosave_INCLUDED
#  define idosave_INCLUDED

/*
 * Save a change that must be undone by restore.  We have to pass the
 * pointer to the containing object to alloc_save_change for two reasons:
 *
 *      - We need to know which VM the containing object is in, so we can
 * know on which chain of saved changes to put the new change.
 *
 *      - We need to know whether the object is an array of refs (which
 * includes dictionaries) or a struct, so we can properly trace and
 * relocate the pointer to it from the change record during garbage
 * collection.
 */
int alloc_save_change(gs_dual_memory_t *dmem, const ref *pcont,
		      ref_packed *ptr, client_name_t cname);
int alloc_save_change_in(gs_ref_memory_t *mem, const ref *pcont,
			 ref_packed *ptr, client_name_t cname);

#endif /* idosave_INCLUDED */
