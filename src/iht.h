/* Copyright (C) 1997 artofcode LLC.  All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.

*/

/*$Id: iht.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Procedures exported by zht.c for zht1.c and zht2.c */

#ifndef iht_INCLUDED
#  define iht_INCLUDED

int zscreen_params(P2(os_ptr op, gs_screen_halftone * phs));

int zscreen_enum_init(P7(i_ctx_t *i_ctx_p, const gx_ht_order * porder,
			 gs_screen_halftone * phs, ref * pproc, int npop,
			 op_proc_t finish_proc, gs_memory_t * mem));

#endif /* iht_INCLUDED */
