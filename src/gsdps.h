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

/*$Id: gsdps.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Client interface to Display PostScript facilities. */

#ifndef gsdps_INCLUDED
#  define gsdps_INCLUDED

/* Device-source images */
#include "gsiparm2.h"

/* View clipping */
int gs_initviewclip(P1(gs_state *));
int gs_eoviewclip(P1(gs_state *));
int gs_viewclip(P1(gs_state *));
int gs_viewclippath(P1(gs_state *));

#endif /* gsdps_INCLUDED */
