/* Copyright (C) 1989, 1995, 1997, 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsmatrix.h,v 1.1 2004/01/14 16:59:50 atai Exp $ */
/* Definition of matrices and client interface to matrix routines */

#ifndef gsmatrix_INCLUDED
#  define gsmatrix_INCLUDED

/* See p. 65 of the PostScript manual for the semantics of */
/* transformation matrices. */

/* Structure for a transformation matrix. */
#define _matrix_body\
  float xx, xy, yx, yy, tx, ty
struct gs_matrix_s {
    _matrix_body;
};

#ifndef gs_matrix_DEFINED
#  define gs_matrix_DEFINED
typedef struct gs_matrix_s gs_matrix;
#endif

/* Macro for initializing constant matrices */
#define constant_matrix_body(xx, xy, yx, yy, tx, ty)\
  (float)(xx), (float)(xy), (float)(yx),\
  (float)(yy), (float)(tx), (float)(ty)

/* Macros for testing whether matrix coefficients are zero, */
/* for shortcuts when the matrix is simple. */
#define is_xxyy(pmat) is_fzero2((pmat)->xy, (pmat)->yx)
#define is_xyyx(pmat) is_fzero2((pmat)->xx, (pmat)->yy)

/* The identity matrix (for structure initialization) */
#define identity_matrix_body\
  constant_matrix_body(1, 0, 0, 1, 0, 0)

/* Matrix creation */
void gs_make_identity(P1(gs_matrix *));
int gs_make_translation(P3(floatp, floatp, gs_matrix *)),
    gs_make_scaling(P3(floatp, floatp, gs_matrix *)),
    gs_make_rotation(P2(floatp, gs_matrix *));

/* Matrix arithmetic */
int gs_matrix_multiply(P3(const gs_matrix *, const gs_matrix *, gs_matrix *)),
    gs_matrix_invert(P2(const gs_matrix *, gs_matrix *)),
    gs_matrix_translate(P4(const gs_matrix *, floatp, floatp, gs_matrix *)),
    gs_matrix_scale(P4(const gs_matrix *, floatp, floatp, gs_matrix *)),
    gs_matrix_rotate(P3(const gs_matrix *, floatp, gs_matrix *));

/* Coordinate transformation */
int gs_point_transform(P4(floatp, floatp, const gs_matrix *, gs_point *)),
    gs_point_transform_inverse(P4(floatp, floatp, const gs_matrix *, gs_point *)),
    gs_distance_transform(P4(floatp, floatp, const gs_matrix *, gs_point *)),
    gs_distance_transform_inverse(P4(floatp, floatp, const gs_matrix *, gs_point *)),
    gs_points_bbox(P2(const gs_point[4], gs_rect *)), gs_bbox_transform_only(P3(const gs_rect *, const gs_matrix *, gs_point[4])),
    gs_bbox_transform(P3(const gs_rect *, const gs_matrix *, gs_rect *)),
    gs_bbox_transform_inverse(P3(const gs_rect *, const gs_matrix *, gs_rect *));

/* Serialization */
#ifndef stream_DEFINED
#  define stream_DEFINED
typedef struct stream_s stream;
#endif
int sget_matrix(P2(stream *, gs_matrix *));
int sput_matrix(P2(stream *, const gs_matrix *));

#endif /* gsmatrix_INCLUDED */
