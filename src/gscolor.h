/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
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

/* $Id: gscolor.h,v 1.5 2007/05/07 11:21:46 Arabidopsis Exp $ */
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
