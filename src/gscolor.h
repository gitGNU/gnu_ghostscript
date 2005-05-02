/* Copyright (C) 1991, 2000 Aladdin Enterprises.  All rights reserved.
  
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

  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gscolor.h,v 1.3 2005/05/02 00:03:21 Arabidopsis Exp $ */
/* Client interface to color routines */

#ifndef gscolor_INCLUDED
#  define gscolor_INCLUDED

#include "gxtmap.h"

/* Color and gray interface */
int gs_setgray(gs_state *, floatp);
int gs_currentgray(const gs_state *, float *);
int gs_setrgbcolor(gs_state *, floatp, floatp, floatp);
int gs_currentrgbcolor(const gs_state *, float[3]);
int gs_setnullcolor(gs_state *);

/* Transfer function */
int gs_settransfer(gs_state *, gs_mapping_proc);
int gs_settransfer_remap(gs_state *, gs_mapping_proc, bool);
gs_mapping_proc gs_currenttransfer(const gs_state *);

#endif /* gscolor_INCLUDED */
