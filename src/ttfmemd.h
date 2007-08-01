/* Copyright (C) 2001-2006 artofcode LLC.
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

/* $Id: ttfmemd.h,v 1.5 2007/08/01 14:26:46 jemarch Exp $ */
/* Memory structure descriptors for the TrueType instruction interpreter. */

#if !defined(ttfmemd_INCLUDED)
#  define ttfmemd_INCLUDED

#include "gsstype.h"

extern_st(st_TFace);
extern_st(st_TInstance);
extern_st(st_TExecution_Context);
extern_st(st_ttfFont);
extern_st(st_ttfInterpreter);

#endif /* !defined(ttfmemd_INCLUDED) */
