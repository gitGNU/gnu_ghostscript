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

/* gsargs.c */
/* Command line argument list management */
#include "ctype_.h"
#include "stdio_.h"
#include "string_.h"
#include "gsexit.h"
#include "gsmemory.h"
#include "gsargs.h"

/* Initialize an arg list. */
void
arg_init(arg_list *pal, const char **argv, int argc,
  FILE *(*arg_fopen)(P2(const char *fname, void *fopen_data)),
  void *fopen_data)
{	pal->expand_ats = true;
	pal->arg_fopen = arg_fopen;
	pal->fopen_data = fopen_data;
	pal->argp = argv + 1;
	pal->argn = argc - 1;
	pal->depth = 0;
}

/* Push a string onto an arg list. */
void
arg_push_string(arg_list *pal, const char *str)
{	arg_source *pas;

	if ( pal->depth == arg_depth_max )
	  { lprintf("Too much nesting of @-files.\n");
	    gs_exit(1);
	  }
	pas = &pal->sources[pal->depth];
	pas->is_file = false;
	pas->u.str = str;
	pal->depth++;
}

/* Clean up an arg list. */
void
arg_finit(arg_list *pal)
{	while ( pal->depth )
	  if ( pal->sources[--(pal->depth)].is_file )
	    fclose(pal->sources[pal->depth].u.file);
}

/* Get the next arg from a list. */
/* Note that these are not copied to the heap. */
const char *
arg_next(arg_list *pal)
{	arg_source *pas;
	FILE *f;
	const char *astr = 0;		/* initialized only to pacify gcc */
	char *cstr;
	const char *result;
	int endc;
	register int c;
	register int i;
	bool in_quote;

top:	pas = &pal->sources[pal->depth - 1];
	if ( pal->depth == 0 )
	{	if ( pal->argn <= 0 )		/* all done */
		  return 0;
		pal->argn--;
		result = *(pal->argp++);
		goto at;
	}
	if ( pas->is_file )
	  f = pas->u.file, endc = EOF;
	else
	  astr = pas->u.str, f = NULL, endc = 0;
	result = cstr = pal->cstr;
#define cfsgetc() (f == NULL ? (*astr ? *astr++ : 0) : fgetc(f))
	while ( isspace(c = cfsgetc()) ) ;
	if ( c == endc )
	{	if ( f != NULL )
		  fclose(f);
		pal->depth--;
		goto top;
	}
	in_quote = false;
	for ( i = 0; ; )
	{	if ( i == arg_str_max - 1 )
		{	cstr[i] = 0;
			fprintf(stdout, "Command too long: %s\n", cstr);
			gs_exit(1);
		}
		/* If input is coming from an @-file, allow quotes */
		/* to protect whitespace. */
		if ( c == '"' && f != NULL )
		  in_quote = !in_quote;
		else
		  cstr[i++] = c;
		c = cfsgetc();
		if ( c == endc )
		  {	if ( in_quote )
			  { cstr[i] = 0;
			    fprintf(stdout,
				    "Unterminated quote in @-file: %s\n",
				    cstr);
			    gs_exit(1);
			  }
			break;
		  }
		if ( isspace(c) && !in_quote )
		  break;
	}
	cstr[i] = 0;
	if ( f == NULL )
	  pas->u.str = astr;
at:	if ( pal->expand_ats && result[0] == '@' )
	{	if ( pal->depth == arg_depth_max )
		{	lprintf("Too much nesting of @-files.\n");
			gs_exit(1);
		}
		result++;		/* skip @ */
		f = (*pal->arg_fopen)(result, pal->fopen_data);
		if ( f == NULL )
		{	fprintf(stdout, "Unable to open command line file %s\n", result);
			gs_exit(1);
		}
		pal->depth++;
		pas++;
		pas->is_file = true;
		pas->u.file = f;
		goto top;
	}
	return result;
}

/* Copy an argument string to the heap. */
char *
arg_copy(const char *str, gs_memory_t *mem)
{	char *sstr = (char *)gs_alloc_bytes(mem, strlen(str) + 1, "arg_copy");
	if ( sstr == 0 )
	{	lprintf("Out of memory!\n");
		gs_exit(1);
	}
	strcpy(sstr, str);
	return sstr;
}
