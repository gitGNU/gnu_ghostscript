/* Copyright (C) 1995, 1996, 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gxpaint.c,v 1.3 2005/05/02 00:03:35 Arabidopsis Exp $ */
/* Graphics-state-aware fill and stroke procedures */
#include "gx.h"
#include "gzstate.h"
#include "gxdevice.h"
#include "gxhttile.h"
#include "gxpaint.h"
#include "gxpath.h"

/* Fill a path. */
int
gx_fill_path(gx_path * ppath, gx_device_color * pdevc, gs_state * pgs,
	     int rule, fixed adjust_x, fixed adjust_y)
{
    gx_device *dev = gs_currentdevice_inline(pgs);
    gx_clip_path *pcpath;
    int code = gx_effective_clip_path(pgs, &pcpath);
    gx_fill_params params;

    if (code < 0)
	return code;
    params.rule = rule;
    params.adjust.x = adjust_x;
    params.adjust.y = adjust_y;
    params.flatness = (pgs->in_cachedevice > 1 ? 0.0 : pgs->flatness);
    params.fill_zero_width = (adjust_x | adjust_y) != 0;
    return (*dev_proc(dev, fill_path))
	(dev, (const gs_imager_state *)pgs, ppath, &params, pdevc, pcpath);
}

/* Stroke a path for drawing or saving. */
int
gx_stroke_fill(gx_path * ppath, gs_state * pgs)
{
    gx_device *dev = gs_currentdevice_inline(pgs);
    gx_clip_path *pcpath;
    int code = gx_effective_clip_path(pgs, &pcpath);
    gx_stroke_params params;

    if (code < 0)
	return code;
    params.flatness = (pgs->in_cachedevice > 1 ? 0.0 : pgs->flatness);
    return (*dev_proc(dev, stroke_path))
	(dev, (const gs_imager_state *)pgs, ppath, &params,
	 pgs->dev_color, pcpath);
}

int
gx_stroke_add(gx_path * ppath, gx_path * to_path,
	      const gs_state * pgs)
{
    gx_stroke_params params;

    params.flatness = (pgs->in_cachedevice > 1 ? 0.0 : pgs->flatness);
    return gx_stroke_path_only(ppath, to_path, pgs->device,
			       (const gs_imager_state *)pgs,
			       &params, NULL, NULL);
}

int
gx_imager_stroke_add(gx_path *ppath, gx_path *to_path,
		     gx_device *dev, const gs_imager_state *pis)
{
    gx_stroke_params params;

    params.flatness = pis->flatness;
    return gx_stroke_path_only(ppath, to_path, dev, pis,
			       &params, NULL, NULL);
}
