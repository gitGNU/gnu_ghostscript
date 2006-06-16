/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: iht.h,v 1.5 2006/06/16 12:55:05 Arabidopsis Exp $ */
/* Procedures exported by zht.c for zht1.c and zht2.c */

#ifndef iht_INCLUDED
#  define iht_INCLUDED

int zscreen_params(os_ptr op, gs_screen_halftone * phs);

int zscreen_enum_init(i_ctx_t *i_ctx_p, const gx_ht_order * porder,
		      gs_screen_halftone * phs, ref * pproc, int npop,
		      op_proc_t finish_proc, int space_index);

#endif /* iht_INCLUDED */
