/* Copyright (C) 2003 Aladdin Enterprises.  All rights reserved.

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

/* $Id: ttfmemd.h,v 1.3 2005/12/13 16:57:28 jemarch Exp $ */
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
