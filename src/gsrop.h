/* Copyright (C) 1995, 1996, 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gsrop.h,v 1.2 2004/02/14 22:20:17 atai Exp $ */
/* RasterOp / transparency procedure interface */

#ifndef gsrop_INCLUDED
#  define gsrop_INCLUDED

#include "gsropt.h"

/* Procedural interface */

int gs_setrasterop(gs_state *, gs_rop3_t);
gs_rop3_t gs_currentrasterop(const gs_state *);
int gs_setsourcetransparent(gs_state *, bool);
bool gs_currentsourcetransparent(const gs_state *);
int gs_settexturetransparent(gs_state *, bool);
bool gs_currenttexturetransparent(const gs_state *);

/* Save/restore the combined logical operation. */
gs_logical_operation_t gs_current_logical_op(const gs_state *);
int gs_set_logical_op(gs_state *, gs_logical_operation_t);

#endif /* gsrop_INCLUDED */
