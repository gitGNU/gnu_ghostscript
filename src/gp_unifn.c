/* Copyright (C) 1994, 1996 artofcode LLC.  All rights reserved.
  
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

/*$Id: gp_unifn.c,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Unix-like file name syntax platform routines for Ghostscript */
#include "gx.h"
#include "gp.h"
#include "gsutil.h"

/* Define the character used for separating file names in a list. */
const char gp_file_name_list_separator = ':';

/* Define the string to be concatenated with the file mode */
/* for opening files without end-of-line conversion. */
const char gp_fmode_binary_suffix[] = "";

/* Define the file modes for binary reading or writing. */
const char gp_fmode_rb[] = "r";
const char gp_fmode_wb[] = "w";

/* Answer whether a path_string can meaningfully have a prefix applied */
bool
gp_pathstring_not_bare(const char *fname, unsigned len)
{			
    /* A file name is not bare if it starts with a '/' or a '.' or	*/
    /* it contains "/../"						*/
    if (len && (*fname == '.' || *fname == '/'))
	return true;
    while (len-- > 3) {
        int c = *fname++;

	if ((c == '/') &&
	    ((len >= 3) && (bytes_compare(fname, 2, "..", 2) == 0) &&
			(fname[2] == '/')))
	    return true;
    }
    return false;
}

/* Answer whether the file_name references the directory	*/
/* containing the specified path (parent). 			*/
bool
gp_file_name_references_parent(const char *fname, unsigned len)
{
    int i = 0, last_sep_pos = -1;

    /* A file name references its parent directory if it starts */
    /* with ../ or if ../ follows a / */
    while (i < len) {
	if (fname[i] == '/') {
	    last_sep_pos = i++;
	    continue;
	}
	if (fname[i++] != '.')
	    continue;
        if (i > last_sep_pos + 2 || (i < len && fname[i] != '.'))
	    continue;
	i++;
	/* have separator followed by .. */
	if (i < len && fname[i] == '/')
	    return true;
    }
    return false;
}


/* Answer the string to be used for combining a directory/device prefix */
/* with a base file name. The prefix directory/device is examined to	*/
/* determine if a separator is needed and may return an empty string	*/
const char *
gp_file_name_concat_string(const char *prefix, unsigned plen)
{
    if (plen > 0 && prefix[plen - 1] == '/')
	return "";
    return "/";
}
