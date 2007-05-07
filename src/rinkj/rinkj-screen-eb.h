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

/*$Id: rinkj-screen-eb.h,v 1.2 2007/05/07 11:22:22 Arabidopsis Exp $ */
/* A Rinkj module encapsulating ETS screening. */

RinkjDevice *
rinkj_screen_eb_new (RinkjDevice *dev_out);

void
rinkj_screen_eb_set_scale (RinkjDevice *self, double xscale, double yscale);

void
rinkj_screen_eb_set_gamma (RinkjDevice *self, int plane, double gamma, double max);

void
rinkj_screen_eb_set_lut (RinkjDevice *self, int plane, const double *lut);
