/* Copyright (C) 1996-2004 artofcode LLC. All rights reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free Software
  Foundation; either version 2, or (at your option) any later version.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

/* $Id: gscdef.c,v 1.7 2006/06/16 12:55:03 Arabidopsis Exp $ */
/* Configuration scalars */

#include "std.h"
#include "gscdefs.h"		/* interface */
#include "gconfigd.h"		/* for #defines */

/* ---------------- Miscellaneous system parameters ---------------- */

/* All of these can be set in the makefile. */
/* Normally they are all const; see gscdefs.h for more information. */

#ifndef GS_BUILDTIME
#  define GS_BUILDTIME\
	0			/* should be set in the makefile */
#endif
CONFIG_CONST long gs_buildtime = GS_BUILDTIME;

#ifndef GS_COPYRIGHT
#  define GS_COPYRIGHT\
	"Copyright (C) 2006 artofcode LLC, Benicia, CA.  All rights reserved."
#endif
const char *CONFIG_CONST gs_copyright = GS_COPYRIGHT;

#ifndef GS_PRODUCTFAMILY
#  define GS_PRODUCTFAMILY\
	"GNU Ghostscript"
#endif
const char *CONFIG_CONST gs_productfamily = GS_PRODUCTFAMILY;

#ifndef GS_PRODUCT
#  define GS_PRODUCT\
	GS_PRODUCTFAMILY
#endif
const char *CONFIG_CONST gs_product = GS_PRODUCT;

const char *
gs_program_name(void)
{
    return gs_product;
}

/* GS_REVISION must be defined in the makefile. */
CONFIG_CONST long gs_revision = GS_REVISION;

long
gs_revision_number(void)
{
    return gs_revision;
}

/* GS_REVISIONDATE must be defined in the makefile. */
CONFIG_CONST long gs_revisiondate = GS_REVISIONDATE;

#ifndef GS_SERIALNUMBER
#  define GS_SERIALNUMBER\
	42			/* a famous number */
#endif
CONFIG_CONST long gs_serialnumber = GS_SERIALNUMBER;

/* ---------------- Installation directories and files ---------------- */

/* Here is where the library search path, the name of the */
/* initialization file, and the doc directory are defined. */
/* Define the documentation directory (only used in help messages). */
const char *const gs_doc_directory = GS_DOCDIR;

/* Define the default library search path. */
const char *const gs_lib_default_path = GS_LIB_DEFAULT;

/* Define the interpreter initialization file. */
const char *const gs_init_file = GS_INIT;
