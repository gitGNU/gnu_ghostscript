
/* 
 * International Color Consortium Format Library (icclib)
 * File dump utility.
 *
 * Author:  Graeme W. Gill
 * Date:    99/11/29
 * Version: 2.00
 *
 * Copyright 1997, 1998, 1999, 2000, 2001 Graeme W. Gill
 * Please refer to Licence.txt file for details.
 */

/*
 * TTBD:
 * 		Add support for command line offset (or auto signature search ?)
 * 		to cope with dumping embeded profiles.
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <string.h>
#include "icc.h"

void error(char *fmt, ...), warning(char *fmt, ...);

void usage(void) {
	fprintf(stderr,"Dump an ICC file in human readable form, V2.00\n");
	fprintf(stderr,"Author: Graeme W. Gill\n");
	fprintf(stderr,"usage: iccdump [-v level] [-t tagname] infile\n");
	fprintf(stderr," -v level                 Verbose level 1-3\n");
	fprintf(stderr," -t tag                   Dump this tag only\n");
	exit(1);
}

int
main(int argc, char *argv[]) {
	int fa,nfa;				/* argument we're looking at */
	char in_name[100];
	char tag_name[40] = { '\000' };
	int verb = 2;
	icmFile *fp;
	icc *icco;
	int rv = 0;
	
	if (argc < 2)
		usage();

	/* Process the arguments */
	for(fa = 1;fa < argc;fa++) {
		nfa = fa;					/* skip to nfa if next argument is used */
		if (argv[fa][0] == '-')	{	/* Look for any flags */
			char *na = NULL;		/* next argument after flag, null if none */

			if (argv[fa][2] != '\000')
				na = &argv[fa][2];		/* next is directly after flag */
			else {
				if ((fa+1) < argc) {
					if (argv[fa+1][0] != '-') {
						nfa = fa + 1;
						na = argv[nfa];		/* next is seperate non-flag argument */
					}
				}
			}

			if (argv[fa][1] == '?')
				usage();

			/* Verbosity */
			else if (argv[fa][1] == 'v' || argv[fa][1] == 'V') {
				fa = nfa;
				if (na == NULL) usage();
				verb = atoi(na);
			}
			/* Tag name */
			else if (argv[fa][1] == 't' || argv[fa][1] == 'T') {
				fa = nfa;
				if (na == NULL) usage();
				strcpy(tag_name,na);
			}

			else 
				usage();
		}
		else
			break;
	}

	if (fa >= argc || argv[fa][0] == '-') usage();
	strcpy(in_name,argv[fa]);

	/* Open up the file for reading */
	if ((fp = new_icmFileStd_name(in_name,"r")) == NULL)
		error ("Can't open file '%s'",in_name);

	if ((icco = new_icc()) == NULL)
		error ("Creation of ICC object failed");

	if ((rv = icco->read(icco,fp,0)) != 0)
		error ("%d, %s",rv,icco->err);

	if (tag_name[0] != '\000') {
		icTagSignature sig = str2tag(tag_name);

		/* Try and locate that particular tag */
		if ((rv = icco->find_tag(icco,sig)) != 0) {
			if (rv == 1)
				warning ("icc->find_tag() tag '%s' found but unknown", tag_name);
			else
				warning ("icc->find_tag() can't find tag '%s' in file", tag2str(sig));
		} else {
			icmBase *ob;

			if ((ob = icco->read_tag(icco, sig)) == NULL) {
				warning("Failed to read tag '%s': %d, %s",tag_name, icco->errc,icco->err);
			} else {
				ob->dump(ob, stdout, verb-1);
			}
		}
	} else {
		icco->dump(icco, stdout, verb);
	}

	icco->del(icco);
	fp->del(fp);

	return 0;
}


/* Basic printf type error() and warning() routines */

void
error(char *fmt, ...)
{
	va_list args;

	fprintf(stderr,"iccdump: Error - ");
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
	exit (-1);
}

void
warning(char *fmt, ...)
{
	va_list args;

	fprintf(stderr,"iccdump: Warning - ");
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
}
