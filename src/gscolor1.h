/* Copyright (C) 1993 artofcode LLC.  All rights reserved.
  
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

/*$Id: gscolor1.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Client interface to Level 1 extended color facilities */
/* Requires gscolor.h */

#ifndef gscolor1_INCLUDED
#  define gscolor1_INCLUDED

/* Color and gray interface */
int gs_setcmykcolor(P5(gs_state *, floatp, floatp, floatp, floatp)), gs_currentcmykcolor(P2(const gs_state *, float[4])),
      gs_setblackgeneration(P2(gs_state *, gs_mapping_proc)), gs_setblackgeneration_remap(P3(gs_state *, gs_mapping_proc, bool));
gs_mapping_proc gs_currentblackgeneration(P1(const gs_state *));
int gs_setundercolorremoval(P2(gs_state *, gs_mapping_proc)), gs_setundercolorremoval_remap(P3(gs_state *, gs_mapping_proc, bool));
gs_mapping_proc gs_currentundercolorremoval(P1(const gs_state *));

/* Transfer function */
int gs_setcolortransfer(P5(gs_state *, gs_mapping_proc /*red */ ,
		    gs_mapping_proc /*green */ , gs_mapping_proc /*blue */ ,
			   gs_mapping_proc /*gray */ )), gs_setcolortransfer_remap(P6(gs_state *, gs_mapping_proc /*red */ ,
		    gs_mapping_proc /*green */ , gs_mapping_proc /*blue */ ,
					 gs_mapping_proc /*gray */ , bool));
void gs_currentcolortransfer(P2(const gs_state *, gs_mapping_proc[4]));

#endif /* gscolor1_INCLUDED */
