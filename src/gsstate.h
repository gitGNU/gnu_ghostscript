/* Copyright (C) 1989, 1995, 1996, 1997, 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsstate.h,v 1.1 2004/01/14 16:59:50 atai Exp $ */
/* Public graphics state API */

#ifndef gsstate_INCLUDED
#  define gsstate_INCLUDED

/* Opaque type for a graphics state */
#ifndef gs_state_DEFINED
#  define gs_state_DEFINED
typedef struct gs_state_s gs_state;
#endif

/* Initial allocation and freeing */
gs_state *gs_state_alloc(P1(gs_memory_t *));	/* 0 if fails */
int gs_state_free(P1(gs_state *));

/* Initialization, saving, restoring, and copying */
int gs_gsave(P1(gs_state *)), gs_grestore(P1(gs_state *)), gs_grestoreall(P1(gs_state *));
int gs_grestore_only(P1(gs_state *));
int gs_gsave_for_save(P2(gs_state *, gs_state **)), gs_grestoreall_for_restore(P2(gs_state *, gs_state *));
gs_state *gs_gstate(P1(gs_state *));
gs_state *gs_state_copy(P2(gs_state *, gs_memory_t *));
int gs_copygstate(P2(gs_state * /*to */ , const gs_state * /*from */ )),
      gs_currentgstate(P2(gs_state * /*to */ , const gs_state * /*from */ )),
      gs_setgstate(P2(gs_state * /*to */ , const gs_state * /*from */ ));
int gs_initgraphics(P1(gs_state *));

/* Device control */
#include "gsdevice.h"

/* Line parameters and quality */
#include "gsline.h"

/* Color and gray */
#include "gscolor.h"

/* Halftone screen */
#include "gsht.h"
#include "gscsel.h"
int gs_setscreenphase(P4(gs_state *, int, int, gs_color_select_t));
int gs_currentscreenphase(P3(const gs_state *, gs_int_point *,
			     gs_color_select_t));

#define gs_sethalftonephase(pgs, px, py)\
  gs_setscreenphase(pgs, px, py, gs_color_select_all)
#define gs_currenthalftonephase(pgs, ppt)\
  gs_currentscreenphase(pgs, ppt, 0)
int gx_imager_setscreenphase(P4(gs_imager_state *, int, int,
				gs_color_select_t));

/* Miscellaneous */
int gs_setfilladjust(P3(gs_state *, floatp, floatp));
int gs_currentfilladjust(P2(const gs_state *, gs_point *));
void gs_setlimitclamp(P2(gs_state *, bool));
bool gs_currentlimitclamp(P1(const gs_state *));
#include "gscpm.h"
gs_in_cache_device_t gs_incachedevice(P1(const gs_state *));

#endif /* gsstate_INCLUDED */
