/* Copyright (C) 1995, 1996, 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsrop.h,v 1.1 2004/01/14 16:59:50 atai Exp $ */
/* RasterOp / transparency procedure interface */

#ifndef gsrop_INCLUDED
#  define gsrop_INCLUDED

#include "gsropt.h"

/* Procedural interface */

int gs_setrasterop(P2(gs_state *, gs_rop3_t));
gs_rop3_t gs_currentrasterop(P1(const gs_state *));
int gs_setsourcetransparent(P2(gs_state *, bool));
bool gs_currentsourcetransparent(P1(const gs_state *));
int gs_settexturetransparent(P2(gs_state *, bool));
bool gs_currenttexturetransparent(P1(const gs_state *));

/* Save/restore the combined logical operation. */
gs_logical_operation_t gs_current_logical_op(P1(const gs_state *));
int gs_set_logical_op(P2(gs_state *, gs_logical_operation_t));

#endif /* gsrop_INCLUDED */
