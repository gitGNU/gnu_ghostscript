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

/* $Id: gxshade4.h,v 1.7 2007/05/07 11:21:44 Arabidopsis Exp $ */
/* Internal definitions for triangle shading rendering */

#ifndef gxshade4_INCLUDED
#  define gxshade4_INCLUDED

/* Configuration flags for development needs only. Users should not modify them. */
#define USE_LINEAR_COLOR_PROCS 1 /* Old code = 0, new code = 1. */

#define QUADRANGLES 0 /* 0 = decompose by triangles, 1 = by quadrangles. */
/* The code QUADRANGLES 1 appears unuseful.
   We keep it because it stores a valuable code for constant_color_quadrangle,
   which decomposes a random quadrangle into 3 or 4 trapezoids.
   The color approximation looks worse than with triangles, and works some slower.
 */
#define INTERPATCH_PADDING (fixed_1 / 2) /* Emulate a trapping for poorly designed documents. */
/* When INTERPATCH_PADDING > 0, it generates paddings between patches,
   i.e. performs a patch expansion, being similar
   to the path adjustment in the filling algorithm.
   The expansion is an emulation of Adobe's trapping.
   The value specifies the width of paddings.
   We did some testing of Adobe RIP, and it looks as applying 
   same logicks as for clipping - any part of pixel inside.
   Therefore the expansion should be half pixel size.
 */
#define COLOR_CONTIGUITY 1 /* A smothness divisor for triangulation. */
/* This is a coefficient used to rich
   a better color contiguity. The value 1 corresponds to PLRM,
   bigger values mean more contiguity. The speed decreases as
   a square of COLOR_CONTIGUITY.
 */
#define LAZY_WEDGES 1 /* 0 = fill immediately, 1 = fill lazy. */
/* This mode delays creating wedges for a boundary until
   both neoghbour areas are painted. At that moment we can know
   all subdivision points for both right and left areas,
   and skip wedges for common points. Therefore the number of wadges 
   dramatically reduces, causing a significant speedup.
   The LAZY_WEDGES 0 mode was not systematically tested.
 */
#define VD_TRACE_DOWN 1 /* Developer's needs, not important for production. */
#define NOFILL_TEST 0 /* Developer's needs, must be off for production. */
#define SKIP_TEST 0 /* Developer's needs, must be off for production. */
/* End of configuration flags (we don't mean that users should modify the rest). */

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
  gs_fixed_rect rect
typedef struct mesh_fill_state_s {
    mesh_fill_state_common;
} mesh_fill_state_t;
/****** NEED GC DESCRIPTOR ******/

typedef struct wedge_vertex_list_elem_s wedge_vertex_list_elem_t;
struct wedge_vertex_list_elem_s {
    gs_fixed_point p;
    int level;
    bool divide_count;
    wedge_vertex_list_elem_t *next, *prev;
};
typedef struct {
    bool last_side;
    wedge_vertex_list_elem_t *beg, *end;    
} wedge_vertex_list_t;

#define LAZY_WEDGES_MAX_LEVEL 9 /* memory consumption is 
    sizeof(wedge_vertex_list_elem_t) * LAZY_WEDGES_MAX_LEVEL * (1 << LAZY_WEDGES_MAX_LEVEL) */

#define SHADING_COLOR_STACK_SIZE 200; /* Should be enough for max 64 decomposition levels. */

/* Define a color to be used in curve rendering. */
/* This may be a real client color, or a parametric function argument. */
struct patch_color_s {
    float t[2];			/* parametric value */
    gs_client_color cc;
    /* NOTE : The structure gs_client_color ends with a big array, but only few elements
       are used in most cases. Therefore sometimes we allocate a shorter area,
       so that ending elements are not allocated and must not be accessed/modified.
       The number of allocated elements are known from the shading color space
       and from patch_fill_state_s::num_components. */
};

#ifndef patch_color_t_DEFINED
#  define patch_color_t_DEFINED
typedef struct patch_color_s patch_color_t;
#endif



/* Define the common state for rendering Coons and tensor patches. */
typedef struct patch_fill_state_s {
    mesh_fill_state_common;
    const gs_function_t *Function;
    bool vectorization;
    int n_color_args;
    fixed max_small_coord; /* Length restriction for intersection_of_small_bars. */
    wedge_vertex_list_elem_t *wedge_vertex_list_elem_buffer;
    wedge_vertex_list_elem_t *free_wedge_vertex;
    int wedge_vertex_list_elem_count;
    int wedge_vertex_list_elem_count_max;
    gs_client_color color_domain;
    fixed fixed_flat;
    double smoothness;
    bool maybe_self_intersecting;
    bool monotonic_color;
    bool linear_color;
    bool unlinear;
    bool inside;
    int color_stack_size;
    int color_stack_step;
    byte *color_stack_ptr;
    byte *color_stack; /* A storage for shortened patch_color_t structures. */
    byte *color_stack_limit;
    gs_memory_t *memory; /* Where color_buffer is allocated. */
} patch_fill_state_t;

/* Define a structure for mesh or patch vertex. */
struct shading_vertex_s {
    gs_fixed_point p;
    const patch_color_t *c;
};

/* Define one segment (vertex and next control points) of a curve. */
typedef struct patch_curve_s {
    mesh_vertex_t vertex;
    gs_fixed_point control[2];
    bool straight;
} patch_curve_t;

/* Initialize the fill state for triangle shading. */
int mesh_init_fill_state(mesh_fill_state_t * pfs,
			  const gs_shading_mesh_t * psh,
			  const gs_fixed_rect * rect_clip,
			  gx_device * dev, gs_imager_state * pis);

int init_patch_fill_state(patch_fill_state_t *pfs);
bool term_patch_fill_state(patch_fill_state_t *pfs);

int mesh_triangle(patch_fill_state_t *pfs, 
    const shading_vertex_t *p0, const shading_vertex_t *p1, const shading_vertex_t *p2);

int mesh_padding(patch_fill_state_t *pfs, const gs_fixed_point *p0, const gs_fixed_point *p1, 
	    const patch_color_t *c0, const patch_color_t *c1);

int patch_fill(patch_fill_state_t * pfs, const patch_curve_t curve[4],
	   const gs_fixed_point interior[4],
	   void (*transform) (gs_fixed_point *, const patch_curve_t[4],
			      const gs_fixed_point[4], floatp, floatp));

int wedge_vertex_list_elem_buffer_alloc(patch_fill_state_t *pfs);
void wedge_vertex_list_elem_buffer_free(patch_fill_state_t *pfs);

void patch_resolve_color(patch_color_t * ppcr, const patch_fill_state_t *pfs);

int gx_shade_background(gx_device *pdev, const gs_fixed_rect *rect, 
	const gx_device_color *pdevc, gs_logical_operation_t log_op);

byte *reserve_colors(patch_fill_state_t *pfs, patch_color_t *c0[], int n);
void release_colors(patch_fill_state_t *pfs, byte *ptr, int n);

#endif /* gxshade4_INCLUDED */
