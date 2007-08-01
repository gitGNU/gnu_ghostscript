/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or
  modify it under the terms of the version 2 of the GNU General Public
  License as published by the Free Software Foundation.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

/*$Id: rinkj-dither.h,v 1.3 2007/08/01 14:26:55 jemarch Exp $ */
/* The dither object abstraction within the Rinkj driver. */

typedef struct _RinkjDither RinkjDither;

struct _RinkjDither {
  void (*dither_line) (RinkjDither *self, unsigned char *dst, const unsigned char *src);
  void (*close) (RinkjDither *self);
};

void
rinkj_dither_line (RinkjDither *self, unsigned char *dst, const unsigned char *src);

void
rinkj_dither_close (RinkjDither *self);

