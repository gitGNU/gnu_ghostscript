/* Copyright (C) 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gxclipsr.h,v 1.2 2004/02/14 22:20:18 atai Exp $ */
/* Internals of clipsave/cliprestore */

#ifndef gxclipsr_INCLUDED
#  define gxclipsr_INCLUDED

#include "gsrefct.h"

/*
 * Unlike the graphics state stack, which is threaded through the actual
 * gstate objects, the clipping path stack is implemented with separate,
 * small objects.  These are reference-counted, because they may be
 * shared by off-stack graphics states.
 */

#ifndef gx_clip_path_DEFINED
#  define gx_clip_path_DEFINED
typedef struct gx_clip_path_s gx_clip_path;
#endif
#ifndef gx_clip_stack_DEFINED
#  define gx_clip_stack_DEFINED
typedef struct gx_clip_stack_s gx_clip_stack_t;
#endif

struct gx_clip_stack_s {
    rc_header rc;
    gx_clip_path *clip_path;
    gx_clip_stack_t *next;
};

#define private_st_clip_stack()	/* in gsclipsr.c */\
  gs_private_st_ptrs2(st_clip_stack, gx_clip_stack_t,\
    "gx_clip_stack_t", clip_stack_enum_ptrs, clip_stack_reloc_ptrs,\
    clip_path, next)

#endif /* gxclipsr_INCLUDED */
