/* Copyright (C) 1994-2002 artofcode LLC.  All rights reserved.
  
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

/* $Id: gdevmacttf.h,v 1.5 2005/12/13 16:57:18 jemarch Exp $ */
/* Datatypes for simpler access to data structures in TrueType fonts */

#ifndef gdevmacttf_INCLUDED
#  define gdevmacttf_INCLUDED


/* Font Directory Component */

typedef struct {
	UInt32		tagName;
	UInt32		checkSum;
	UInt32		offset;
	UInt32		length;
} TTFontDirComponent;



/* Font Directory */

typedef struct {
	UInt32				version;
	UInt16				numTables;
	UInt16				searchRange;
	UInt16				entrySelector;
	UInt16				rangeShift;
	TTFontDirComponent	components[1];	/* an array of numTables components */
} TTFontDir;



/* Tag definitions */
#define		TTF_FONT_NAMING_TABLE	'name'



/* Font Naming Table */

typedef struct {
	UInt16				formatSelector;
	UInt16				numNames;
	UInt16				stringAreaOffset;
	UInt16				platformID;
	UInt16				platformSpecificID;
	UInt16				languageID;
	UInt16				nameID;
	UInt16				length;
	UInt16				offset;
} TTFontNamingTable;

#endif /* gdevmacttf_INCLUDED */
