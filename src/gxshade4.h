/* Copyright (C) 1998, 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: gxshade4.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
/* Internal definitions for triangle shading rendering */

#ifndef gxshade4_INCLUDED
#  define gxshade4_INCLUDED

#define mesh_max_depth (16 * 3 + 1)	/* each recursion adds 3 entries */
typedef struct mesh_frame_s {	/* recursion frame */
    mesh_vertex_t va, vb, vc;	/* current vertices */
    bool check_clipping;
} mesh_frame_t;
/****** NEED GC DESCRIPTOR ******/

/*
 * Define the fill state structure for triangle shadings.  This is used
 * both for the Gouraud triangle shading types and for the Coons and
 * tensor patch types.
 *
 * The shading pointer is named pshm rather than psh in case subclasses
 * also want to store a pointer of a more specific type.
 */
#define mesh_fill_state_common\
  shading_fill_state_common;\
  const gs_shading_mesh_t *pshm;\
  gs_fixed_rect rect;\
  int depth;\
  mesh_frame_t frames[mesh_max_depth]
typedef struct mesh_fill_state_s {
    mesh_fill_state_common;
} mesh_fill_state_t;
/****** NEED GC DESCRIPTOR ******/

/* Initialize the fill state for triangle shading. */
void mesh_init_fill_state(P5(mesh_fill_state_t * pfs,
			     const gs_shading_mesh_t * psh,
			     const gs_rect * rect,
			     gx_device * dev, gs_imager_state * pis));

/* Fill one triangle in a mesh. */
void mesh_init_fill_triangle(P5(mesh_fill_state_t * pfs,
				const mesh_vertex_t *va,
				const mesh_vertex_t *vb,
				const mesh_vertex_t *vc, bool check_clipping));
int mesh_fill_triangle(P1(mesh_fill_state_t * pfs));

#endif /* gxshade4_INCLUDED */
