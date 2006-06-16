/* Copyright (C) 1996, 2000 artofcode LLC.  All rights reserved.
/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
   This software is provided AS-IS with no warranty, either express or
   implied.

   This software is distributed under license and may not be copied, modified
   or distributed except as expressly authorized under the terms of that
   license.  Refer to licensing information at http://www.artifex.com/
   or contact Artifex Software, Inc.,  7 Mt. Lassen Drive - Suite A-134,
   San Rafael, CA  94903, U.S.A., +1(415)492-9861, for further information.
*/

/* $Id: gdevpdft.c,v 1.3 2006/06/16 12:55:05 Arabidopsis Exp $ */
/* transparency processing for PDF-writing driver */
#include "gx.h"
#include "string_.h"
#include "gserrors.h"
#include "gstrans.h"
#include "gscolor2.h"
#include "gzstate.h"
#include "gdevpdfx.h"
#include "gdevpdfg.h"
#include "gdevpdfo.h"

private int
pdf_make_soft_mask_dict(gx_device_pdf * pdev, const gs_pdf14trans_params_t * pparams)
{
    pdf_resource_t *pres_soft_mask_dict = 0;
    cos_dict_t *soft_mask_dict;
    int code;

    /* Fixme : merge redundant objects. */
    code = pdf_alloc_resource(pdev, resourceSoftMaskDict, gs_no_id, &pres_soft_mask_dict, -1);
    if (code < 0)
	return code;
    cos_become(pres_soft_mask_dict->object, cos_type_dict);
    pdev->pres_soft_mask_dict = pres_soft_mask_dict;
    soft_mask_dict = (cos_dict_t *)pres_soft_mask_dict->object;
    code = cos_dict_put_c_key_string(soft_mask_dict, "/S", 
	    pparams->subtype == TRANSPARENCY_MASK_Alpha ? (byte *)"/Alpha" : (byte *)"/Luminosity", 
	    pparams->subtype == TRANSPARENCY_MASK_Alpha ? 6 : 11);
    if (code < 0)
	return code;
    if (pparams->Background_components) {
	cos_array_t *Background;

	Background = cos_array_from_floats(pdev, pparams->Background, 
		    pparams->Background_components, "pdf_write_soft_mask_dict");
	if (Background == NULL)
	    return_error(gs_error_VMerror);
	code = cos_dict_put_c_key_object(soft_mask_dict, "/BC", (cos_object_t *)Background);
	if (code < 0)
	    return code;
    }
    if (pparams->transfer_function != NULL) {
	long id;
	char buf[20];
	
	code = pdf_write_function(pdev, pparams->transfer_function, &id);
	if (code < 0)
	    return code;
	sprintf(buf, " %ld 0 R", id);
	code = cos_dict_put_c_key_string(soft_mask_dict, "/TR", (const byte *)buf, strlen(buf));
	if (code < 0)
	    return code;
    }
    return 0;

}

private int
pdf_make_group_dict(gx_device_pdf * pdev, const gs_pdf14trans_params_t * pparams,
			    const gs_imager_state * pis, cos_dict_t **pdict)
{
    pdf_resource_t *pres_group;
    cos_dict_t *group_dict;
    int code;
    const gs_state *gstate = gx_hld_get_gstate_ptr(pis);
    cos_value_t cs_value;

    code = pdf_alloc_resource(pdev, resourceGroup, gs_no_id, &pres_group, -1);
    if (code < 0)
	return code;
    cos_become(pres_group->object, cos_type_dict);
    group_dict = (cos_dict_t *)pres_group->object;
    code = cos_dict_put_c_key_string(group_dict, "/Type", (const byte *)"/Group", 6);
    if (code < 0)
	return code;
    code = cos_dict_put_c_key_string(group_dict, "/S", (const byte *)"/Transparency", 13);
    if (code < 0)
	return code;
    if (pparams->Isolated) {
	code = cos_dict_put_c_key_bool(group_dict, "/I", true);
	if (code < 0)
	    return code;
    }
    if (pparams->Knockout) {
	code = cos_dict_put_c_key_bool(group_dict, "/K", true);
	if (code < 0)
	    return code;
    }
    if (gstate != NULL) {
	const gs_color_space *cs = gstate->color_space;

	code = pdf_color_space(pdev, &cs_value, NULL, cs,
		&pdf_color_space_names, false);
	if (code < 0)
	    return code;
	code = cos_dict_put_c_key(group_dict, "/CS", &cs_value);
	if (code < 0)
	    return code;
    }
    group_dict = NULL; /* The next line invalidates it. */
    code = pdf_substitute_resource(pdev, &pres_group, resourceGroup, NULL, false);
    if (code < 0)
	return code;
    *pdict = (cos_dict_t *)pres_group->object;
    return 0;
}

private int
pdf_make_form_dict(gx_device_pdf * pdev, const gs_pdf14trans_params_t * pparams,
			    const gs_imager_state * pis, 
			    const cos_dict_t *group_dict, cos_dict_t *form_dict)
{
    cos_array_t *bbox_array;
    float bbox[4];
    gs_rect bbox_rect;
    int code;


    code = gs_bbox_transform(&pparams->bbox, &ctm_only(pis), &bbox_rect);
    if (code < 0)
	return code;
    bbox[0] = bbox_rect.p.x;
    bbox[1] = bbox_rect.p.y;
    bbox[2] = bbox_rect.q.x;
    bbox[3] = bbox_rect.q.y;
    code = cos_dict_put_c_key_string(form_dict, "/Type", (const byte *)"/XObject", 8);
    if (code < 0)
	return code;
    code = cos_dict_put_c_key_string(form_dict, "/Subtype", (const byte *)"/Form", 5);
    if (code < 0)
	return code;
    code = cos_dict_put_c_key_int(form_dict, "/FormType", 1);
    if (code < 0)
	return code;
    code = cos_dict_put_c_key_string(form_dict, "/Matrix", (const byte *)"[1 0 0 1 0 0]", 13);
    if (code < 0)
	return code;
    bbox_array = cos_array_from_floats(pdev, bbox, 4, "pdf_begin_transparency_group");
    if (bbox_array == NULL)
	return_error(gs_error_VMerror);
    code = cos_dict_put_c_key_object(form_dict, "/BBox", (cos_object_t *)bbox_array);
    if (code < 0)
	return code;
    return cos_dict_put_c_key_object(form_dict, "/Group", (cos_object_t *)group_dict);
}

private int 
pdf_begin_transparency_group(gs_imager_state * pis, gx_device_pdf * pdev,
				const gs_pdf14trans_params_t * pparams)
{
    cos_dict_t *group_dict;
    bool in_page = is_in_page(pdev);
    const gs_state *gstate = gx_hld_get_gstate_ptr(pis);
    int code;

    if (gstate == NULL)
	return_error(gs_error_unregistered); /* Must not happen. */
    code = pdf_make_group_dict(pdev, pparams, pis, &group_dict);
    if (code < 0)
	return code;
    code = pdf_open_page(pdev, PDF_IN_STREAM);
    if (code < 0)
	return code;
    if (pdf_must_put_clip_path(pdev, gstate->clip_path)) {
	code = pdf_put_clip_path(pdev, gstate->clip_path);
	if (code < 0)
	    return code;
    }
    if (!in_page) 
	pdev->pages[pdev->next_page].group_id = group_dict->id;
    else {
	pdf_resource_t *pres, *pres_gstate = NULL;

	code = pdf_prepare_drawing(pdev, pis, &pres_gstate);
	if (code < 0)
	    return code;
	code = pdf_end_gstate(pdev, pres_gstate);
	if (code < 0)
	    return code;
	code = pdf_enter_substream(pdev, resourceXObject, 
		gs_no_id, &pres, false, pdev->params.CompressPages);
	if (code < 0)
	    return code;
	return pdf_make_form_dict(pdev, pparams, pis, group_dict, (cos_dict_t *)pres->object);
    }
    return 0;
}

private int 
pdf_end_transparency_group(gs_imager_state * pis, gx_device_pdf * pdev)
{
    int bottom = (pdev->ResourcesBeforeUsage ? 1 : 0);

    if (pdev->sbstack_depth == bottom) {
	/* We're closing the page group. */
	if (pdev->pages[pdev->next_page].group_id == 0)
	    return_error(gs_error_unregistered); /* Must not happen. */
	return 0;
    } else {
	pdf_resource_t *pres = pdev->accumulating_substream_resource;
	int code;
	uint ignore;

	code = pdf_exit_substream(pdev);
	if (code < 0)
	    return code;
	code = pdf_substitute_resource(pdev, &pres, resourceXObject, NULL, false);
	if (code < 0)
	    return code;
	sputc(pdev->strm,'/');
	sputs(pdev->strm, (const byte *)pres->rname, strlen(pres->rname), &ignore);
	sputs(pdev->strm, (const byte *)" Do\n", 4, &ignore);
	return 0;    
    }
}

private int 
pdf_begin_transparency_mask(gs_imager_state * pis, gx_device_pdf * pdev,
				const gs_pdf14trans_params_t * pparams)
{
    if (pparams->mask_is_image) {
	/* HACK : 
	    The control comes here when 
	    the PDF interpreter will make the PS interpreter 
	    to interprete the mask for filling the transparency buffer
    	    with an SMask image.
	    Since we handle Type 3 images as a high level objects, 
	    we don't install the transparency buffer here
	    and need to skip the image enumeration for the SMask.
	    However we have no right method for skipping
	    an image enumeration due to possible side effect 
	    of the image data proc in Postscript language.
	    Therefore we do enumerate the image mask and accumulate
	    it as a PDF stream, but don't create a reference to it.
	    Later it will be enumerated once again as a part of SMask-ed image,
	    and the pdfwrite image handler will recognize duplicated images 
	    and won't create the second stream for same image.

	    We could make a special workaround for 
	    skipping mask images either in the graphics library or 
	    in the PS code of the PDF interpreter,
	    but we don't want to complicate things now.
	    The performance leak for the second enumeration 
	    shouldn't be harmful.

	    So now just set a flag for pdf_end_and_do_image.
	*/
	pdev->image_mask_skip = true;
	return 0;
    } else {
	int code;
	
	code = pdf_make_soft_mask_dict(pdev, pparams);
	if (code < 0)
	    return code;
	code = pdf_open_page(pdev, PDF_IN_STREAM);
	if (code < 0)
	    return code;
	return pdf_begin_transparency_group(pis, pdev, pparams);
    }
}

private int 
pdf_end_transparency_mask(gs_imager_state * pis, gx_device_pdf * pdev,
				const gs_pdf14trans_params_t * pparams)
{
    if (pdev->image_mask_skip) 
	pdev->image_mask_skip = false;
    else {
	pdf_resource_t *pres = pdev->accumulating_substream_resource;
	int code;
	char buf[20];
	
	code = pdf_exit_substream(pdev);
	if (code < 0)
	    return code;
	code = pdf_substitute_resource(pdev, &pres, resourceXObject, NULL, false);
	if (code < 0)
	    return 0;
	sprintf(buf, "%ld 0 R", pdf_resource_id(pres));
	code = cos_dict_put_c_key_string((cos_dict_t *)pdev->pres_soft_mask_dict->object,
		"/G", (const byte *)buf, strlen(buf));
	if (code < 0)
	    return code;
	code = pdf_substitute_resource(pdev, &pdev->pres_soft_mask_dict, 
					resourceSoftMaskDict, NULL, false);
	if (code < 0)
	    return code;
	pis->soft_mask_id = pdev->pres_soft_mask_dict->object->id;
	pdev->pres_soft_mask_dict = NULL;
    }
    return 0;
}

private int
pdf_set_blend_params(gs_imager_state * pis, gx_device_pdf * dev,
				const gs_pdf14trans_params_t * pparams)
{
    return 0;
}

int 
gdev_pdf_create_compositor(gx_device *dev,
    gx_device **pcdev, const gs_composite_t *pct,
    gs_imager_state *pis, gs_memory_t *memory)
{
    gx_device_pdf *pdev = (gx_device_pdf *)dev;
    
    if (pdev->HaveTransparency && pdev->CompatibilityLevel >= 1.4 &&
	    pct->type->comp_id == GX_COMPOSITOR_PDF14_TRANS &&
	    !pdev->PDFA) {
	gs_pdf14trans_t *pcte = (gs_pdf14trans_t *)pct;
	gs_pdf14trans_params_t *params = &pcte->params;

	*pcdev = dev;
	switch(params->pdf14_op) {
	    case PDF14_PUSH_DEVICE:
		return 0;
	    case PDF14_POP_DEVICE:
		return 0;
	    case PDF14_BEGIN_TRANS_GROUP:
		return pdf_begin_transparency_group(pis, pdev, params);
	    case PDF14_END_TRANS_GROUP:
		return pdf_end_transparency_group(pis, pdev);
	    case PDF14_INIT_TRANS_MASK:
		return gx_init_transparency_mask(pis, params);
	    case PDF14_BEGIN_TRANS_MASK:
		return pdf_begin_transparency_mask(pis, pdev, params);
	    case PDF14_END_TRANS_MASK:
		return pdf_end_transparency_mask(pis, pdev, params);
	    case PDF14_SET_BLEND_PARAMS:
		return pdf_set_blend_params(pis, pdev, params);
	    default :
		return_error(gs_error_unregistered); /* Must not happen. */
	}
	return 0;
    }
    return psdf_create_compositor(dev, pcdev, pct, pis, memory);
}

/* We're not sure why the folllowing device methods are never called.
   Stub them for a while. */

int 
gdev_pdf_begin_transparency_group(gx_device *dev,
    const gs_transparency_group_params_t *ptgp,
    const gs_rect *pbbox,
    gs_imager_state *pis,
    gs_transparency_state_t **ppts,
    gs_memory_t *mem)
{
    return 0;
}

int
gdev_pdf_end_transparency_group(gx_device *dev,
    gs_imager_state *pis,
    gs_transparency_state_t **ppts)
{
    return 0;
}

int
gdev_pdf_begin_transparency_mask(gx_device *dev,
    const gx_transparency_mask_params_t *ptmp,
    const gs_rect *pbbox,
    gs_imager_state *pis,
    gs_transparency_state_t **ppts,
    gs_memory_t *mem)
{
    return 0;
}

int
gdev_pdf_end_transparency_mask(gx_device *dev,
    gs_transparency_mask_t **pptm)
{
    return 0;
}

int
gdev_pdf_discard_transparency_layer(gx_device *dev,
    gs_transparency_state_t **ppts)
{
    return 0;
}
  
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

/*$Id: gdevpdft.c,v 1.3 2006/06/16 12:55:05 Arabidopsis Exp $ */
/* Text handling for PDF-writing driver. */
#include "math_.h"
#include "memory_.h"
#include "string_.h"
#include "gx.h"
#include "gserrors.h"
#include "gxpath.h"		/* for getting current point */
#include "gdevpdfx.h"
#include "gdevpdff.h"
#include "gdevpdfg.h"
#include "scommon.h"

/* GC descriptors */
private_st_pdf_text_enum();

/* Define the auxiliary procedures for text processing. */
private int
pdf_text_resync(gs_text_enum_t *pte, const gs_text_enum_t *pfrom)
{
    pdf_text_enum_t *const penum = (pdf_text_enum_t *)pte;

    if ((pte->text.operation ^ pfrom->text.operation) & ~TEXT_FROM_ANY)
	return_error(gs_error_rangecheck);
    if (penum->pte_default) {
	int code = gs_text_resync(penum->pte_default, pfrom);

	if (code < 0)
	    return code;
    }
    pte->text = pfrom->text;
    gs_text_enum_copy_dynamic(pte, pfrom, false);
    return 0;
}
private bool
pdf_text_is_width_only(const gs_text_enum_t *pte)
{
    const pdf_text_enum_t *const penum = (const pdf_text_enum_t *)pte;

    if (penum->pte_default)
	return gs_text_is_width_only(penum->pte_default);
    return false;
}
private int
pdf_text_current_width(const gs_text_enum_t *pte, gs_point *pwidth)
{
    const pdf_text_enum_t *const penum = (const pdf_text_enum_t *)pte;

    if (penum->pte_default)
	return gs_text_current_width(penum->pte_default, pwidth);
    return_error(gs_error_rangecheck); /* can't happen */
}
private int
pdf_text_set_cache(gs_text_enum_t *pte, const double *pw,
		   gs_text_cache_control_t control)
{
    pdf_text_enum_t *const penum = (pdf_text_enum_t *)pte;

    if (penum->pte_default)
	return gs_text_set_cache(penum->pte_default, pw, control);
    return_error(gs_error_rangecheck); /* can't happen */
}
private int
pdf_text_retry(gs_text_enum_t *pte)
{
    pdf_text_enum_t *const penum = (pdf_text_enum_t *)pte;

    if (penum->pte_default)
	return gs_text_retry(penum->pte_default);
    return_error(gs_error_rangecheck); /* can't happen */
}
private void
pdf_text_release(gs_text_enum_t *pte, client_name_t cname)
{
    pdf_text_enum_t *const penum = (pdf_text_enum_t *)pte;

    if (penum->pte_default) {
	gs_text_release(penum->pte_default, cname);
	penum->pte_default = 0;
    }
    gx_default_text_release(pte, cname);
}

/* Begin processing text. */
extern text_enum_proc_process(pdf_text_process); /* in gdevpdfs.c */
private const gs_text_enum_procs_t pdf_text_procs = {
    pdf_text_resync, pdf_text_process,
    pdf_text_is_width_only, pdf_text_current_width,
    pdf_text_set_cache, pdf_text_retry,
    pdf_text_release
};
int
gdev_pdf_text_begin(gx_device * dev, gs_imager_state * pis,
		    const gs_text_params_t *text, gs_font * font,
		    gx_path * path, const gx_device_color * pdcolor,
		    const gx_clip_path * pcpath,
		    gs_memory_t * mem, gs_text_enum_t ** ppte)
{
    gx_device_pdf *const pdev = (gx_device_pdf *)dev;
    pdf_text_enum_t *penum;
    gs_fixed_point cpt;
    int code;

    /* Track the dominant text rotation. */
    {
	gs_matrix tmat;
	int i;

	gs_matrix_multiply(&font->FontMatrix, &ctm_only(pis), &tmat);
	if (is_xxyy(&tmat))
	    i = (tmat.xx >= 0 ? 0 : 2);
	else if (is_xyyx(&tmat))
	    i = (tmat.xy >= 0 ? 1 : 3);
	else
	    i = 4;
	pdf_current_page(pdev)->text_rotation.counts[i] += text->size;
    }

    if (!(text->operation & TEXT_DO_DRAW) || path == 0 ||
	gx_path_current_point(path, &cpt) < 0
	)
	return gx_default_text_begin(dev, pis, text, font, path, pdcolor,
				     pcpath, mem, ppte);

    code = pdf_prepare_fill(pdev, pis);
    if (code < 0)
	return code;

    if (text->operation & TEXT_DO_DRAW) {
	/*
	 * Set the clipping path and drawing color.  We set both the fill
	 * and stroke color, because we don't know whether the fonts will be
	 * filled or stroked, and we can't set a color while we are in text
	 * mode.  (This is a consequence of the implementation, not a
	 * limitation of PDF.)
	 */

	if (pdf_must_put_clip_path(pdev, pcpath)) {
	    int code = pdf_open_page(pdev, PDF_IN_STREAM);

	    if (code < 0)
		return code;
	    pdf_put_clip_path(pdev, pcpath);
	}

	if ((code =
	     pdf_set_drawing_color(pdev, pdcolor, &pdev->stroke_color,
				   &psdf_set_stroke_color_commands)) < 0 ||
	    (code =
	     pdf_set_drawing_color(pdev, pdcolor, &pdev->fill_color,
				   &psdf_set_fill_color_commands)) < 0
	    )
	    return code;
    }

    /* Allocate and initialize the enumerator. */

    rc_alloc_struct_1(penum, pdf_text_enum_t, &st_pdf_text_enum, mem,
		      return_error(gs_error_VMerror), "gdev_pdf_text_begin");
    penum->rc.free = rc_free_text_enum;
    penum->pte_default = 0; 
    code = gs_text_enum_init((gs_text_enum_t *)penum, &pdf_text_procs,
			     dev, pis, text, font, path, pdcolor, pcpath, mem);
    if (code < 0) {
	gs_free_object(mem, penum, "gdev_pdf_text_begin");
	return code;
    }

    *ppte = (gs_text_enum_t *)penum;

    return 0;
}

/* ---------------- Text and font utilities ---------------- */

/* Forward declarations */
private int assign_char_code(P1(gx_device_pdf * pdev));

/*
 * Set the current font and size, writing a Tf command if needed.
 */
int
pdf_set_font_and_size(gx_device_pdf * pdev, pdf_font_t * font, floatp size)
{
    if (font != pdev->text.font || size != pdev->text.size) {
	int code = pdf_open_page(pdev, PDF_IN_TEXT);
	stream *s = pdev->strm;

	if (code < 0)
	    return code;
	pprints1(s, "/%s ", font->rname);
	pprintg1(s, "%g Tf\n", size);
	pdev->text.font = font;
	pdev->text.size = size;
    }
    font->where_used |= pdev->used_mask;
    return 0;
}

/*
 * Set the text matrix for writing text.
 * The translation component of the matrix is the text origin.
 * If the non-translation components of the matrix differ from the
 * current ones, write a Tm command; if there is only a Y translation
 * and it matches the leading, set use_leading so the next text string
 * will be written with ' rather than Tj; otherwise, write either a TL
 * command or a Tj command using space pseudo-characters.
 */
private int
set_text_distance(gs_point *pdist, const gs_point *ppt, const gs_matrix *pmat)
{
    double rounded;
    int code;

    code = gs_distance_transform_inverse(pmat->tx - ppt->x, pmat->ty - ppt->y,
				  pmat, pdist);
    if (code < 0)
	return code;
    /* If the distance is very close to integers, round it. */
    if (fabs(pdist->x - (rounded = floor(pdist->x + 0.5))) < 0.0005)
	pdist->x = rounded;
    if (fabs(pdist->y - (rounded = floor(pdist->y + 0.5))) < 0.0005)
	pdist->y = rounded;
    return 0;
}
int
pdf_set_text_matrix(gx_device_pdf * pdev, const gs_matrix * pmat)
{
    stream *s = pdev->strm;
    double sx = 72.0 / pdev->HWResolution[0],
	sy = 72.0 / pdev->HWResolution[1];
    int code;

    if (pmat->xx == pdev->text.matrix.xx &&
	pmat->xy == pdev->text.matrix.xy &&
	pmat->yx == pdev->text.matrix.yx &&
	pmat->yy == pdev->text.matrix.yy &&
    /*
     * If we aren't already in text context, BT will reset
     * the text matrix.
     */
	(pdev->context == PDF_IN_TEXT || pdev->context == PDF_IN_STRING)
	) {
	/* Use leading, Td or a pseudo-character. */
	gs_point dist;

	code = set_text_distance(&dist, &pdev->text.current, pmat);
	if (code < 0)
	    return code;
	if (dist.y == 0 && dist.x >= X_SPACE_MIN &&
	    dist.x <= X_SPACE_MAX &&
	    pdev->text.font != 0 &&
	    PDF_FONT_IS_SYNTHESIZED(pdev->text.font)
	    ) {			/* Use a pseudo-character. */
	    int dx = (int)dist.x;
	    int dx_i = dx - X_SPACE_MIN;
	    byte space_char = pdev->text.font->spaces[dx_i];

	    if (space_char == 0) {
		if (pdev->text.font != pdev->open_font)
		    goto not_spaces;
		code = assign_char_code(pdev);
		if (code <= 0)
		    goto not_spaces;
		space_char = pdev->open_font->spaces[dx_i] = (byte)code;
		if (pdev->space_char_ids[dx_i] == 0) {
		    /* Create the space char_proc now. */
		    char spstr[3 + 14 + 1];
		    stream *s;

		    sprintf(spstr, "%d 0 0 0 0 0 d1\n", dx);
		    pdev->space_char_ids[dx_i] = pdf_begin_separate(pdev);
		    s = pdev->strm;
		    pprintd1(s, "<</Length %d>>\nstream\n", strlen(spstr));
		    pprints1(s, "%sendstream\n", spstr);
		    pdf_end_separate(pdev);
		}
	    }
	    pdf_append_chars(pdev, &space_char, 1);
	    pdev->text.current.x += dx * pmat->xx;
	    pdev->text.current.y += dx * pmat->xy;
	    /* Don't change use_leading -- it only affects Y placement. */
	    return 0;
	}
      not_spaces:
	code = pdf_open_page(pdev, PDF_IN_TEXT);
	if (code < 0)
	    return code;
	code = set_text_distance(&dist, &pdev->text.line_start, pmat);
	if (code < 0)
	    return code;
	if (pdev->text.use_leading) {
	    /* Leading was deferred: take it into account now. */
	    dist.y -= pdev->text.leading;
	}
	if (dist.x == 0 && dist.y < 0) {
	    /* Use TL, if needed, + '. */
	    float dist_y = (float)-dist.y;

	    if (fabs(pdev->text.leading - dist_y) > 0.0005) {
		pprintg1(s, "%g TL\n", dist_y);
		pdev->text.leading = dist_y;
	    }
	    pdev->text.use_leading = true;
	} else {
	    /* Use Td. */
	    pprintg2(s, "%g %g Td\n", dist.x, dist.y);
	    pdev->text.use_leading = false;
	}
    } else {			/* Use Tm. */
	code = pdf_open_page(pdev, PDF_IN_TEXT);
	if (code < 0)
	    return code;
	/*
	 * See stream_to_text in gdevpdf.c for why we need the following
	 * matrix adjustments.
	 */
	pprintg6(pdev->strm, "%g %g %g %g %g %g Tm\n",
		 pmat->xx * sx, pmat->xy * sy,
		 pmat->yx * sx, pmat->yy * sy,
		 pmat->tx * sx, pmat->ty * sy);
	pdev->text.matrix = *pmat;
	pdev->text.use_leading = false;
    }
    pdev->text.line_start.x = pmat->tx;
    pdev->text.line_start.y = pmat->ty;
    pdev->text.current.x = pmat->tx;
    pdev->text.current.y = pmat->ty;
    return 0;
}

/*
 * Append characters to a string being accumulated.
 */
int
pdf_append_chars(gx_device_pdf * pdev, const byte * str, uint size)
{
    const byte *p = str;
    uint left = size;

    while (left)
	if (pdev->text.buffer_count == max_text_buffer) {
	    int code = pdf_open_page(pdev, PDF_IN_TEXT);

	    if (code < 0)
		return code;
	} else {
	    int code = pdf_open_page(pdev, PDF_IN_STRING);
	    uint copy;

	    if (code < 0)
		return code;
	    copy = min(max_text_buffer - pdev->text.buffer_count, left);
	    memcpy(pdev->text.buffer + pdev->text.buffer_count, p, copy);
	    pdev->text.buffer_count += copy;
	    p += copy;
	    left -= copy;
	}
    return 0;
}

/* ---------------- Synthesized fonts ---------------- */

/* Assign a code for a char_proc. */
private int
assign_char_code(gx_device_pdf * pdev)
{
    pdf_font_t *font = pdev->open_font;
    int c;

    if (pdev->embedded_encoding_id == 0)
	pdev->embedded_encoding_id = pdf_obj_ref(pdev);
    if (font == 0 || font->num_chars == 256 || !pdev->use_open_font) {
	/* Start a new synthesized font. */
	int code = pdf_alloc_font(pdev, gs_no_id, &font, NULL, NULL);
	char *pc;

	if (code < 0)
	    return code;
	if (pdev->open_font == 0)
	    font->rname[0] = 0;
	else
	    strcpy(font->rname, pdev->open_font->rname);
	for (pc = font->rname; *pc == 'Z'; ++pc)
	    *pc = '@';
	if ((*pc)++ == 0)
	    *pc = 'A', pc[1] = 0;
	pdev->open_font = font;
	pdev->use_open_font = true;
    }
    c = font->num_chars++;
    if (c > pdev->max_embedded_code)
	pdev->max_embedded_code = c;
    return c;
}

/* Begin a CharProc for a synthesized (bitmap) font. */
int
pdf_begin_char_proc(gx_device_pdf * pdev, int w, int h, int x_width,
  int y_offset, gs_id id, pdf_char_proc_t ** ppcp, pdf_stream_position_t * ppos)
{
    pdf_resource_t *pres;
    pdf_char_proc_t *pcp;
    int char_code = assign_char_code(pdev);
    pdf_font_t *font = pdev->open_font;
    int code;

    if (char_code < 0)
	return char_code;
    code = pdf_begin_resource(pdev, resourceCharProc, id, &pres);
    if (code < 0)
	return code;
    pcp = (pdf_char_proc_t *) pres;
    pcp->font = font;
    pcp->char_next = font->char_procs;
    font->char_procs = pcp;
    pcp->char_code = char_code;
    pcp->width = w;
    pcp->height = h;
    pcp->x_width = x_width;
    pcp->y_offset = y_offset;
    font->max_y_offset = max(font->max_y_offset, h + (h >> 2));
    *ppcp = pcp;
    {
	stream *s = pdev->strm;

	/*
	 * The resource file is positionable, so rather than use an
	 * object reference for the length, we'll go back and fill it in
	 * at the end of the definition.  Take 1M as the longest
	 * definition we can handle.  (This used to be 10K, but there was
	 * a real file that exceeded this limit.)
	 */
	stream_puts(s, "<</Length       >>stream\n");
	ppos->start_pos = stell(s);
    }
    return 0;
}

/* End a CharProc. */
int
pdf_end_char_proc(gx_device_pdf * pdev, pdf_stream_position_t * ppos)
{
    stream *s = pdev->strm;
    long start_pos = ppos->start_pos;
    long end_pos = stell(s);
    long length = end_pos - start_pos;

    if (length > 999999)
	return_error(gs_error_limitcheck);
    sseek(s, start_pos - 15);
    pprintd1(s, "%d", length);
    sseek(s, end_pos);
    stream_puts(s, "endstream\n");
    pdf_end_separate(pdev);
    return 0;
}

/* Put out a reference to an image as a character in a synthesized font. */
int
pdf_do_char_image(gx_device_pdf * pdev, const pdf_char_proc_t * pcp,
		  const gs_matrix * pimat)
{
    pdf_set_font_and_size(pdev, pcp->font, 1.0);
    {
	gs_matrix tmat;
	int code;

	tmat = *pimat;
	tmat.ty -= pcp->y_offset;
	code = pdf_set_text_matrix(pdev, &tmat);
	if (code < 0)
	    return code;
    }
    pdf_append_chars(pdev, &pcp->char_code, 1);
    pdev->text.current.x += pcp->x_width * pdev->text.matrix.xx;
    return 0;
}
