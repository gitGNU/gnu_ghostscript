/* Copyright (C) 1997, 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsargs.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Command line argument list management */

#ifndef gsargs_INCLUDED
#  define gsargs_INCLUDED

/*
 * We need to handle recursion into @-files.
 * The following structures keep track of the state.
 * Defining a maximum argument length and a maximum nesting depth
 * decreases generality, but eliminates the need for dynamic allocation.
 */
#define arg_str_max 2048
#define arg_depth_max 10
typedef struct arg_source_s {
    bool is_file;
    union _u {
	struct _su {
	    char *chars;	/* original string */
	    gs_memory_t *memory;  /* if non-0, free chars when done with it */
	    const char *str;	/* string being read */
	} s;
	FILE *file;
    } u;
} arg_source;
typedef struct arg_list_s {
    bool expand_ats;		/* if true, expand @-files */
    FILE *(*arg_fopen) (P2(const char *fname, void *fopen_data));
    void *fopen_data;
    const char **argp;
    int argn;
    int depth;			/* depth of @-files */
    char cstr[arg_str_max + 1];
    arg_source sources[arg_depth_max];
} arg_list;

/* Initialize an arg list. */
void arg_init(P5(arg_list * pal, const char **argv, int argc,
	      FILE * (*arg_fopen) (P2(const char *fname, void *fopen_data)),
		 void *fopen_data));

/*
 * Push a string onto an arg list.
 * This may also be used (once) to "unread" the last argument.
 * If mem != 0, it is used to free the string when we are done with it.
 * Return 0 on success, non-zero on failure
 */
int arg_push_memory_string(P3(arg_list * pal, char *str, gs_memory_t * mem));

#define arg_push_string(pal, str)\
  arg_push_memory_string(pal, str, (gs_memory_t *)0);

/* Clean up an arg list before exiting. */
void arg_finit(P1(arg_list * pal));

/*
 * Get the next arg from a list.
 * Note that these are not copied to the heap.
 */
const char *arg_next(P2(arg_list * pal, int *code));

/* Copy an argument string to the heap. */
char *arg_copy(P2(const char *str, gs_memory_t * mem));

#endif /* gsargs_INCLUDED */
