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

/* $Id: zpcolor.c,v 1.7 2007/05/07 11:21:44 Arabidopsis Exp $ */
/* Pattern color */
#include "ghost.h"
#include "oper.h"
#include "gscolor.h"
#include "gsmatrix.h"
#include "gsstruct.h"
#include "gscoord.h"
#include "gxcspace.h"
#include "gxfixed.h"		/* for gxcolor2.h */
#include "gxcolor2.h"
#include "gxdcolor.h"		/* for gxpcolor.h */
#include "gxdevice.h"
#include "gxdevmem.h"		/* for gxpcolor.h */
#include "gxpcolor.h"
#include "gxpath.h"
#include "estack.h"
#include "ialloc.h"
#include "icremap.h"
#include "istruct.h"
#include "idict.h"
#include "idparam.h"
#include "igstate.h"
#include "ipcolor.h"
#include "store.h"
#include "gzstate.h"
#include "memory_.h"

/* Imported from gspcolor.c */
extern const gs_color_space_type gs_color_space_type_Pattern;

/* Forward references */
private int zPaintProc(const gs_client_color *, gs_state *);
private int pattern_paint_prepare(i_ctx_t *);
private int pattern_paint_finish(i_ctx_t *);

/* GC descriptors */
private_st_int_pattern();

/* Initialize the Pattern cache. */
private int
zpcolor_init(i_ctx_t *i_ctx_p)
{
    gstate_set_pattern_cache(igs,
			     gx_pattern_alloc_cache(imemory_system,
					       gx_pat_cache_default_tiles(),
					      gx_pat_cache_default_bits()));
    return 0;
}

/* Create an interpreter pattern structure. */
int
int_pattern_alloc(int_pattern **ppdata, const ref *op, gs_memory_t *mem)
{
    int_pattern *pdata =
	gs_alloc_struct(mem, int_pattern, &st_int_pattern, "int_pattern");

    if (pdata == 0)
	return_error(e_VMerror);
    pdata->dict = *op;
    *ppdata = pdata;
    return 0;
}

/* <pattern> <matrix> .buildpattern1 <pattern> <instance> */
private int
zbuildpattern1(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    os_ptr op1 = op - 1;
    int code;
    gs_matrix mat;
    float BBox[4];
    gs_client_pattern template;
    int_pattern *pdata;
    gs_client_color cc_instance;
    ref *pPaintProc;

    code = read_matrix(imemory, op, &mat);
    if (code < 0)
        return code;
    check_type(*op1, t_dictionary);
    check_dict_read(*op1);
    gs_pattern1_init(&template);

    code = dict_uid_param(op1, &template.uid, 1, imemory, i_ctx_p);
    if (code < 0)
        return code;
    if (code != 1)
        return_error(e_rangecheck);

    code = dict_int_param(op1, "PaintType", 1, 2, 0, &template.PaintType);
    if (code < 0)
        return code;

    code = dict_int_param(op1, "TilingType", 1, 3, 0, &template.TilingType);
    if (code < 0)
        return code;
    
    code = dict_floats_param(imemory, op1, "BBox", 4, BBox, NULL);
    if (code < 0)
        return code;
    if (code == 0)
       return_error(e_undefined); 

    code = dict_float_param(op1, "XStep", 0.0, &template.XStep);
    if (code < 0)
        return code;
    if (code == 1)
       return_error(e_undefined); 
    
    code = dict_float_param(op1, "YStep", 0.0, &template.YStep);
    if (code < 0)
        return code;
    if (code == 1)
       return_error(e_undefined); 
    
    code = dict_find_string(op1, "PaintProc", &pPaintProc);
    if (code < 0)
        return code;
    if (code == 0)
       return_error(e_undefined); 

    check_proc(*pPaintProc);

    if (mat.xx * mat.yy == mat.xy * mat.yx)
        return_error(e_undefinedresult);
    if (BBox[0] >= BBox[2] ||  BBox[1] >= BBox[3])
        return_error(e_rangecheck);

    template.BBox.p.x = BBox[0];
    template.BBox.p.y = BBox[1];
    template.BBox.q.x = BBox[2];
    template.BBox.q.y = BBox[3];
    template.PaintProc = zPaintProc;
    code = int_pattern_alloc(&pdata, op1, imemory);
    if (code < 0)
	return code;
    template.client_data = pdata;
    code = gs_makepattern(&cc_instance, &template, &mat, igs, imemory);
    if (code < 0) {
	ifree_object(pdata, "int_pattern");
	return code;
    }
    make_istruct(op, a_readonly, cc_instance.pattern);
    return code;
}

/* <array> .setpatternspace - */
/* In the case of uncolored patterns, the current color space is */
/* the base space for the pattern space. */
private int
zsetpatternspace(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    gs_color_space *pcs;
    gs_color_space *pcs_base;
    uint edepth = ref_stack_count(&e_stack);
    int code = 0;

    if (!r_is_array(op))
        return_error(e_typecheck);
    check_read(*op);
    switch (r_size(op)) {
	case 1:		/* no base space */
	    pcs_base = NULL;
	    break;
	default:
	    return_error(e_rangecheck);
	case 2:
	    pcs_base = gs_currentcolorspace(igs);
	    if (cs_num_components(pcs_base) < 0)       /* i.e., Pattern space */
		return_error(e_rangecheck);
    }
    pcs = gs_cspace_alloc(imemory, &gs_color_space_type_Pattern);
    pcs->base_space = pcs_base;
    pcs->params.pattern.has_base_space = (pcs_base != NULL);
    rc_increment(pcs_base);
    code = gs_setcolorspace(igs, pcs);
    /* release reference from construction */
    rc_decrement_only(pcs, "zsetpatternspace");
    if (code < 0) {
	ref_stack_pop_to(&e_stack, edepth);
	return code;
    }
    make_null(&istate->pattern); /* PLRM: initial color value is a null object */
    pop(1);
    return (ref_stack_count(&e_stack) == edepth ? 0 : o_push_estack);	/* installation will load the caches */
}

/* ------ Initialization procedure ------ */

const op_def zpcolor_l2_op_defs[] =
{
    op_def_begin_level2(),
    {"2.buildpattern1", zbuildpattern1},
    {"1.setpatternspace", zsetpatternspace},
		/* Internal operators */
    {"0%pattern_paint_prepare", pattern_paint_prepare},
    {"0%pattern_paint_finish", pattern_paint_finish},
    op_def_end(zpcolor_init)
};

/* ------ Internal procedures ------ */

/* Render the pattern by calling the PaintProc. */
private int pattern_paint_cleanup(i_ctx_t *);
private int
zPaintProc(const gs_client_color * pcc, gs_state * pgs)
{
    /* Just schedule a call on the real PaintProc. */
    r_ptr(&gs_int_gstate(pgs)->remap_color_info,
	  int_remap_color_info_t)->proc =
	pattern_paint_prepare;
    return_error(e_RemapColor);
}
/* Prepare to run the PaintProc. */
private int
pattern_paint_prepare(i_ctx_t *i_ctx_p)
{
    gs_state *pgs = igs;
    gs_pattern1_instance_t *pinst =
	(gs_pattern1_instance_t *)gs_currentcolor(pgs)->pattern;
    ref *pdict = &((int_pattern *) pinst->template.client_data)->dict;
    gx_device_pattern_accum *pdev = NULL;
    gx_device *cdev = gs_currentdevice_inline(igs);
    int code;
    ref *ppp;
    bool internal_accum = true;

    check_estack(6);
    if (pgs->have_pattern_streams) {
	code = dev_proc(cdev, pattern_manage)(cdev, pinst->id, pinst, 
				pattern_manage__can_accum);
	if (code < 0)
	    return code;
	internal_accum = (code == 0);
    }
    if (internal_accum) {
	pdev = gx_pattern_accum_alloc(imemory, "pattern_paint_prepare");
	if (pdev == 0)
	    return_error(e_VMerror);
	pdev->instance = pinst;
	pdev->bitmap_memory = gstate_pattern_cache(pgs)->memory;
	code = (*dev_proc(pdev, open_device)) ((gx_device *) pdev);
	if (code < 0) {
	    ifree_object(pdev, "pattern_paint_prepare");
	    return code;
	}
    } else {
	code = gx_pattern_cache_add_dummy_entry((gs_imager_state *)igs, 
		    pinst, cdev->color_info.depth);
	if (code < 0)
	    return code;
    }
    code = gs_gsave(pgs);
    if (code < 0)
	return code;
    code = gs_setgstate(pgs, pinst->saved);
    if (code < 0) {
	gs_grestore(pgs);
	return code;
    }
    /* gx_set_device_only(pgs, (gx_device *) pdev); */
    if (internal_accum)
	gs_setdevice_no_init(pgs, (gx_device *)pdev);
    else {
	gs_matrix m;
	gs_fixed_rect clip_box;

	gs_make_identity(&m);
	gs_setmatrix(igs, &m);
	clip_box.p.x = float2fixed(pinst->template.BBox.p.x);
	clip_box.p.y = float2fixed(pinst->template.BBox.p.y);
	clip_box.q.x = float2fixed(pinst->template.BBox.q.x);
	clip_box.q.y = float2fixed(pinst->template.BBox.q.y);
	code = gx_clip_to_rectangle(igs, &clip_box);
	if (code < 0) {
	    gs_grestore(pgs);
	    return code;
	}
	code = dev_proc(cdev, pattern_manage)(cdev, pinst->id, pinst, 
				pattern_manage__start_accum);
	if (code < 0) {
	    gs_grestore(pgs);
	    return code;
	}
    }
    push_mark_estack(es_other, pattern_paint_cleanup);
    ++esp;
    make_istruct(esp, 0, pdev);
    ++esp;
    /* Save operator stack depth in case PaintProc leaves junk on ostack. */
    make_int(esp, ref_stack_count(&o_stack));
    push_op_estack(pattern_paint_finish);
    dict_find_string(pdict, "PaintProc", &ppp);		/* can't fail */
    *++esp = *ppp;
    *++esp = *pdict;		/* (push on ostack) */
    return o_push_estack;
}
/* Save the rendered pattern. */
private int
pattern_paint_finish(i_ctx_t *i_ctx_p)
{
    int o_stack_adjust = ref_stack_count(&o_stack) - esp->value.intval;
    gx_device_pattern_accum *pdev = r_ptr(esp - 1, gx_device_pattern_accum);

    if (pdev != NULL) {
	gx_color_tile *ctile;
	int code = gx_pattern_cache_add_entry((gs_imager_state *)igs,
					  pdev, &ctile);
	if (code < 0)
	    return code;
    }
    if (o_stack_adjust > 0) {
#if 0
	dlprintf1("PaintProc left %d extra on operator stack!\n", o_stack_adjust);
#endif
	pop(o_stack_adjust);
    }
    esp -= 3;
    pattern_paint_cleanup(i_ctx_p);
    return o_pop_estack;
}
/* Clean up after rendering a pattern.  Note that iff the rendering */
/* succeeded, closing the accumulator won't free the bits. */
private int
pattern_paint_cleanup(i_ctx_t *i_ctx_p)
{
    gx_device_pattern_accum *const pdev = 
	r_ptr(esp + 2, gx_device_pattern_accum);
    int code;

    if (pdev != NULL) {
	/* grestore will free the device, so close it first. */
	(*dev_proc(pdev, close_device)) ((gx_device *) pdev);
    }
    code = gs_grestore(igs);
    if (pdev == NULL) {
	gx_device *cdev = gs_currentdevice_inline(igs);
	int code1 = dev_proc(cdev, pattern_manage)(cdev, gx_no_bitmap_id, NULL, 
				pattern_manage__finish_accum);
	
	if (code == 0 && code1 < 0)
	    code = code1;
    }
    return code;
}
