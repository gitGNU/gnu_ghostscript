/* Copyright (C) 1995, 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: icfontab.c,v 1.2 2004/02/14 22:20:19 atai Exp $ */
/* Table of compiled fonts */
#include "ccfont.h"

/*
 * This is compiled separately and linked with the fonts themselves,
 * in a shared library when applicable.
 */

#undef font_
#define font_(fname, fproc, zfproc) extern ccfont_proc(fproc);
#ifndef GCONFIGF_H
# include "gconfigf.h"
#else
# include GCONFIGF_H
#endif

private const ccfont_fproc fprocs[] = {
#undef font_
#define font_(fname, fproc, zfproc) fproc,  /* fname, zfproc are not needed */
#ifndef GCONFIGF_H
# include "gconfigf.h"
#else
# include GCONFIGF_H
#endif
    0
};

int
ccfont_fprocs(int *pnum_fprocs, const ccfont_fproc ** pfprocs)
{
    *pnum_fprocs = countof(fprocs) - 1;
    *pfprocs = &fprocs[0];
    return ccfont_version;	/* for compatibility checking */
}
