/* Copyright (C) 1994, 1995, 1996, 1997, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsline.h,v 1.1 2004/01/14 16:59:50 atai Exp $ */
/* Line parameter and quality definitions */

#ifndef gsline_INCLUDED
#  define gsline_INCLUDED

#include "gslparam.h"

/* Procedures */
int gs_setlinewidth(P2(gs_state *, floatp));
float gs_currentlinewidth(P1(const gs_state *));
int gs_setlinecap(P2(gs_state *, gs_line_cap));
gs_line_cap gs_currentlinecap(P1(const gs_state *));
int gs_setlinejoin(P2(gs_state *, gs_line_join));
gs_line_join gs_currentlinejoin(P1(const gs_state *));
int gs_setmiterlimit(P2(gs_state *, floatp));
float gs_currentmiterlimit(P1(const gs_state *));
int gs_setdash(P4(gs_state *, const float *, uint, floatp));
uint gs_currentdash_length(P1(const gs_state *));
const float *gs_currentdash_pattern(P1(const gs_state *));
float gs_currentdash_offset(P1(const gs_state *));
int gs_setflat(P2(gs_state *, floatp));
float gs_currentflat(P1(const gs_state *));
int gs_setstrokeadjust(P2(gs_state *, bool));
bool gs_currentstrokeadjust(P1(const gs_state *));

/* Extensions - device-independent */
void gs_setdashadapt(P2(gs_state *, bool));
bool gs_currentdashadapt(P1(const gs_state *));
int gs_setcurvejoin(P2(gs_state *, int));
int gs_currentcurvejoin(P1(const gs_state *));

/* Extensions - device-dependent */
void gs_setaccuratecurves(P2(gs_state *, bool));
bool gs_currentaccuratecurves(P1(const gs_state *));
int gs_setdotlength(P3(gs_state *, floatp, bool));
float gs_currentdotlength(P1(const gs_state *));
bool gs_currentdotlength_absolute(P1(const gs_state *));
int gs_setdotorientation(P1(gs_state *));
int gs_dotorientation(P1(gs_state *));

/* Imager-level procedures */
#ifndef gs_imager_state_DEFINED
#  define gs_imager_state_DEFINED
typedef struct gs_imager_state_s gs_imager_state;
#endif
int gs_imager_setflat(P2(gs_imager_state *, floatp));
bool gs_imager_currentdashadapt(P1(const gs_imager_state *));
bool gs_imager_currentaccuratecurves(P1(const gs_imager_state *));

#endif /* gsline_INCLUDED */
