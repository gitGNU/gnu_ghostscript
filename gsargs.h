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

/* gsargs.h */
/* Command line argument list management */

#ifndef gsargs_INCLUDED
#  define gsargs_INCLUDED

/*
 * We need to handle recursion into @-files.
 * The following structures keep track of the state.
 * Defining a maximum argument length and a maximum nesting depth
 * decreases generality, but eliminates the need for dynamic allocation.
 */
#define arg_str_max 512
#define arg_depth_max 10
typedef struct arg_source_s {
	bool is_file;
	union _u {
	  const char *str;
	  FILE *file;
	} u;
} arg_source;
typedef struct arg_list_s {
	bool expand_ats;	/* if true, expand @-files */
	FILE *(*arg_fopen)(P2(const char *fname, void *fopen_data));
	void *fopen_data;
	const char **argp;
	int argn;
	int depth;		/* depth of @-files */
	char cstr[arg_str_max + 1];
	arg_source sources[arg_depth_max];
} arg_list;

/* Initialize an arg list. */
void arg_init(P5(arg_list *pal, const char **argv, int argc,
		 FILE *(*arg_fopen)(P2(const char *fname, void *fopen_data)),
		 void *fopen_data));

/* Push a string onto an arg list. */
/* This may also be used (once) to "unread" the last argument. */
void arg_push_string(P2(arg_list *pal, const char *str));

/* Clean up an arg list before exiting. */
void arg_finit(P1(arg_list *pal));

/* Get the next arg from a list. */
/* Note that these are not copied to the heap. */
const char *arg_next(P1(arg_list *pal));

/* Copy an argument string to the heap. */
char *arg_copy(P2(const char *str, gs_memory_t *mem));

#endif					/* gsargs_INCLUDED */
