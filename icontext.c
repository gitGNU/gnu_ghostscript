/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
  This file is part of GNU Ghostscript.
  
  GNU Ghostscript is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY.  No author or distributor accepts responsibility to
  anyone for the consequences of using it or for whether it serves any
  particular purpose or works at all, unless he says so in writing.  Refer to
  the GNU General Public License for full details.
  
  Everyone is granted permission to copy, modify and redistribute GNU
  Ghostscript, but only under the conditions described in the GNU General
  Public License.  A copy of this license is supposed to have been given to
  you along with GNU Ghostscript so you can know your rights and
  responsibilities.  It should be in a file named COPYING.  Among other
  things, the copyright notice and this notice must be preserved on all
  copies.
  
  Aladdin Enterprises is not affiliated with the Free Software Foundation or
  the GNU Project.  GNU Ghostscript, as distributed by Aladdin Enterprises,
  does not depend on any other GNU software.
*/

/* icontext.c */
/* Context state operations */
#include "ghost.h"
#include "gsstruct.h"		/* for gxalloc.h */
#include "gxalloc.h"
#include "errors.h"
#include "igstate.h"
#include "icontext.h"
#include "interp.h"
#include "dstack.h"
#include "estack.h"
#include "ostack.h"
#include "store.h"

/* Define the initial stack sizes. */
#define DSTACK_INITIAL 20
#define ESTACK_INITIAL 250
#define OSTACK_INITIAL 200

/* Per-context state stored in statics */
extern ref ref_array_packing;
extern ref ref_binary_object_format;
extern ref user_names;
extern long zrand_state;

/* Initialization procedures */
void zrand_state_init(P1(long *));

/* Allocate the state of a context. */
/* The client is responsible for the 'memory' member. */
int
context_state_alloc(gs_context_state_t *pcst, gs_ref_memory_t *mem)
{	int code = gs_interp_create_stacks(mem, &pcst->dstack, &pcst->estack,
					   &pcst->ostack);

	if ( code < 0 )
	  return code;
	pcst->pgs = int_gstate_alloc(mem);
	if ( pcst->pgs == 0 )
	  return_error(e_VMerror);
	make_false(&pcst->array_packing);
	make_int(&pcst->binary_object_format, 0);
	zrand_state_init(&pcst->rand_state);
	pcst->usertime_total = 0;
	pcst->keep_usertime = false;
	/****** user parameters ******/
	/****** %stdin, %stdout ******/
	return 0;
}

/* Load the interpreter state from a context. */
void
context_state_load(const gs_context_state_t *pcst)
{	d_stack = *r_ptr(&pcst->dstack, ref_stack);
	e_stack = *r_ptr(&pcst->estack, ref_stack);
	o_stack = *r_ptr(&pcst->ostack, ref_stack);
	igs = pcst->pgs;
	gs_imemory = pcst->memory;
	ref_array_packing = pcst->array_packing;
	ref_binary_object_format = pcst->binary_object_format;
	zrand_state = pcst->rand_state;
	/****** user parameters ******/
	/****** %stdin, %stdout ******/
}

/* Store the interpreter state in a context. */
void
context_state_store(gs_context_state_t *pcst)
{	*r_ptr(&pcst->dstack, ref_stack) = d_stack;
	*r_ptr(&pcst->estack, ref_stack) = e_stack;
	*r_ptr(&pcst->ostack, ref_stack) = o_stack;
	pcst->pgs = igs;
	pcst->memory = gs_imemory;
	pcst->array_packing = ref_array_packing;
	pcst->binary_object_format = ref_binary_object_format;
	pcst->rand_state = zrand_state;
	/****** user parameters ******/
	/****** %stdin, %stdout ******/
}

/* Free the state of a context. */
void
context_state_free(gs_context_state_t *pcst, gs_ref_memory_t *mem)
{	/****** SEE alloc ABOVE ******/
	int i;

	/*
	 * If this context is the last one referencing a particular VM
	 * (local, or local and global), free the entire VM space;
	 * otherwise, just free the context-related structures.
	 */
	for ( i = countof(pcst->memory.spaces.indexed); --i >= 0; ) {
	  if ( pcst->memory.spaces.indexed[i] != 0 &&
	       !--(pcst->memory.spaces.indexed[i]->num_contexts)
	     ) {
	    /****** FREE THE ENTIRE SPACE ******/
	  }
	}
}
