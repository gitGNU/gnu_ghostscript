/* Copyright (C) 2001-2006 Artifex Software, Inc.
   All Rights Reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or
  modify it under the terms of the version 2 of the GNU General Public
  License as published by the Free Software Foundation.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

/* $Id: scantab.c,v 1.1 2009/04/23 23:26:36 Arabidopsis Exp $ */
/* Scanner table for PostScript/PDF tokens */
#include "stdpre.h"
#include "scommon.h"
#include "scanchar.h"		/* defines interface */

/* Define the character scanning table (see scanchar.h). */
const byte scan_char_array[max_stream_exception + 256] =
{stream_exception_repeat(ctype_exception),
		/* Control characters 0-31. */
 ctype_space,			/* NULL - standard only in Level 2 */
 ctype_name, ctype_name, ctype_name,
 ctype_other,                 /* EOT == ctrl-d <04> */
 ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_space,			/* TAB (\t) */
 ctype_space,			/* LF (\n) */
 ctype_name,
 ctype_space,			/* FF (\f) */
 ctype_space,			/* CR (\r) */
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name,
		/* Printable characters 32-63 */
 ctype_space,			/* space (\s) */
 ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_other,			/* % */
 ctype_name, ctype_name,
 ctype_other,			/* ( */
 ctype_other,			/* ) */
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_other,			/* / */
 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	/* digits 0-9 */
 ctype_name, ctype_name,
 ctype_other,			/* < */
 ctype_name,
 ctype_other,			/* > */
 ctype_name,
		/* Printable characters 64-95 */
 ctype_name,
 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
 30, 31, 32, 33, 34, 35,
 ctype_other,			/* [ */
 ctype_name,
 ctype_other,			/* ] */
 ctype_name, ctype_name,
		/* Printable characters 96-126 and DEL */
 ctype_name,
 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
 30, 31, 32, 33, 34, 35,
 ctype_other,			/* { */
 ctype_name,
 ctype_other,			/* } */
 ctype_name, ctype_name,
		/* Characters 128-159, binary tokens */
 ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken,
 ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken,
 ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken,
 ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken,
 ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken,
 ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken, ctype_btoken,
 ctype_btoken, ctype_btoken,
		/* Characters 160-191, not defined */
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name,
		/* Characters 192-223, not defined */
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name,
		/* Characters 224-255, not defined */
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name, ctype_name, ctype_name, ctype_name,
 ctype_name, ctype_name
};