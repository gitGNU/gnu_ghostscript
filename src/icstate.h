/* Copyright (C) 1998, 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: icstate.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Externally visible context state */

#ifndef icstate_INCLUDED
#  define icstate_INCLUDED

#include "imemory.h"
#include "iref.h"
#include "idsdata.h"
#include "iesdata.h"
#include "iosdata.h"

/*
 * Define the externally visible state of an interpreter context.
 * If we aren't supporting Display PostScript features, there is only
 * a single context.
 */
#ifndef gs_context_state_t_DEFINED
#  define gs_context_state_t_DEFINED
typedef struct gs_context_state_s gs_context_state_t;
#endif
struct gs_context_state_s {
    gs_state *pgs;
    gs_dual_memory_t memory;
    int language_level;
    ref array_packing;		/* t_boolean */
    ref binary_object_format;	/* t_integer */
    long rand_state;		/* (not in Red Book) */
    long usertime_total;	/* total accumulated usertime, */
				/* not counting current time if running */
    bool keep_usertime;		/* true if context ever executed usertime */
    int in_superexec;		/* # of levels of superexec */
    /* View clipping is handled in the graphics state. */
    ref userparams;		/* t_dictionary */
    int scanner_options;	/* derived from userparams */
    bool LockFilePermissions;	/* accessed from userparams */
    byte *filearg;		/* null terminated string of file being run */
    ref stdio[3];		/* t_file */
    /* Put the stacks at the end to minimize other offsets. */
    dict_stack_t dict_stack;
    exec_stack_t exec_stack;
    op_stack_t op_stack;
};
extern const long rand_state_initial; /* in zmath.c */

/*
 * We make st_context_state public because zcontext.c must subclass it.
 */
/*extern_st(st_context_state); *//* in icontext.h */
#define public_st_context_state()	/* in icontext.c */\
  gs_public_st_complex_only(st_context_state, gs_context_state_t,\
    "gs_context_state_t", context_state_clear_marks,\
    context_state_enum_ptrs, context_state_reloc_ptrs, 0)

#endif /* icstate_INCLUDED */
