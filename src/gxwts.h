/* Copyright (C) 2002 artofcode LLC.  All rights reserved.
  
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

  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/
/*$Id: gxwts.h,v 1.2 2005/05/02 00:03:22 Arabidopsis Exp $ */
#ifndef gxwts_INCLUDED
#  define gxwts_INCLUDED

typedef bits16 wts_screen_sample_t;

#ifndef wts_screen_t_DEFINED
#  define wts_screen_t_DEFINED
typedef struct wts_screen_s wts_screen_t;
#endif

typedef enum {
    WTS_SCREEN_RAT,
    WTS_SCREEN_J,
    WTS_SCREEN_H
} wts_screen_type;

struct wts_screen_s {
    wts_screen_type type;
    int cell_width;
    int cell_height;
    int cell_shift;
    wts_screen_sample_t *samples;
};

typedef struct {
    wts_screen_t base;

    /* Probabilities of "jumps". A and B jumps can happen when moving
       one pixel to the right. C and D can happen when moving one pixel
       down. */
    int pa; /* change to double? */
    int pb;
    int pc;
    int pd;

    int XA;
    int YA;
    int XB;
    int YB;
    int XC;
    int YC;
    int XD;
    int YD;
} wts_screen_j_t;

typedef struct {
    wts_screen_t base;

    /* This is the exact value that x1 and (width-x1) approximates. */
    double px;
    /* Ditto y1 and (height-y1). */
    double py;

    int x1;
    int y1;
} wts_screen_h_t;

int
wts_get_samples(const wts_screen_t *ws, int x, int y,
		wts_screen_sample_t **samples, int *p_nsamples);

#endif
