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

/* $Id: iccinit1.c */
/* Initialization string for compiled initialization */
#include "stdpre.h"

/* The following PostScript is a prefix to the "real" gs_init.ps which is in the %rom%	
 * as gs_init.ps. This sequence must start with an integer token. We don't bother to
 * make it match the current version since it is discarded.
 * Care must be taken to only use basic operators since ones like '[' and ']' are
 * defined later in gs_init.ps.
 */
const byte gs_init_string[] = 
	"0 pop "			/* required integer token. DO NOT REMOVE.            */
	"systemdict /GenericResourceDir known not { " 		/* if GenericResourceDir was */
	"systemdict /GenericResourceDir (%rom%Resource/) put "	/* not set on command line,  */
	"} if "							/* set to %rom%Resource/     */
	"(gs_init.ps) .libfile not { "
	"(Can't find initialization file gs_init.ps.\\n) print flush quit "	/* OOPS! */
	"} if cvx exec "					/* now run the init file       */
;
const uint gs_init_string_sizeof = sizeof(gs_init_string);
