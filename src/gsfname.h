/* Copyright (C) 1993, 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsfname.h,v 1.2 2004/02/14 22:20:17 atai Exp $ */

#ifndef gsfname_INCLUDED
#  define gsfname_INCLUDED

/*
 * Structure and procedures for parsing file names.
 *
 * Define a structure for representing a parsed file name, consisting of
 * an IODevice name in %'s, a file name, or both.  Note that the file name
 * may be either a gs_string (no terminator) or a C string (null terminator).
 *
 * NOTE: You must use parse_[real_]file_name to construct parsed_file_names.
 * Do not simply allocate the structure and fill it in.
 */
#ifndef gx_io_device_DEFINED
#  define gx_io_device_DEFINED
typedef struct gx_io_device_s gx_io_device;
#endif

typedef struct gs_parsed_file_name_s {
    gs_memory_t *memory;	/* allocator for terminated name string */
    gx_io_device *iodev;
    const char *fname;
    uint len;
} gs_parsed_file_name_t;

/* Parse a file name into device and individual name. */
int gs_parse_file_name(gs_parsed_file_name_t *, const char *, uint);

/* Parse a real (non-device) file name and convert to a C string. */
int gs_parse_real_file_name(gs_parsed_file_name_t *, const char *, uint,
			    gs_memory_t *, client_name_t);

/* Convert a file name to a C string by adding a null terminator. */
int gs_terminate_file_name(gs_parsed_file_name_t *, gs_memory_t *,
			   client_name_t);

/* Free a file name that was copied to a C string. */
void gs_free_file_name(gs_parsed_file_name_t *, client_name_t);

#endif /* gsfname_INCLUDED */
