/* Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
  
  This file is part of GNU Ghostscript.
  
  GNU Ghostscript is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY.  No author or distributor accepts responsibility to
  anyone for the consequences of using it or for whether it serves any
  particular purpose or works at all, unless he says so in writing.  Refer to
  the GNU General Public License for full details.
  
  Everyone is granted permission to copy, modify and redistribute GNU
  Ghostscript, but only under the conditions described in the GNU General
  Public License.  A copy of this license is supposed to have been given to
  you along with GNU Ghostscript so you can know your rights and
  responsibilities.  It should be in a file named COPYING.  Among other
  things, the copyright notice and this notice must be preserved on all
  copies.
  
  Aladdin Enterprises is not affiliated with the Free Software Foundation or
  the GNU Project.  GNU Ghostscript, as distributed by Aladdin Enterprises,
  does not depend on any other GNU software.
*/

/* gsdps.c */
/* Display PostScript extensions */
#include "gx.h"
#include "gsdps.h"
#include "gspath.h"		/* for newpath */
#include "gxdevice.h"		/* for gxcpath.h */
#include "gzpath.h"		/* for gzcpath.h */
#include "gzstate.h"
#include "gzcpath.h"

#ifdef DPNEXT

/* Forward references */
private int common_viewclip(P2(gs_state *, int));

int
gs_initviewclip(gs_state *pgs)
{	const gx_clip_path *pcpath = pgs->view_clip->path;

	if ( pcpath->rule != 0 ) {
	  gx_cpath_release(pcpath);
	  gx_cpath_init(pcpath, pcpath->path.memory);
	  pcpath->rule = 0;
	}
	return 0;
}

int
gs_viewclip(gs_state *pgs)
{	return common_viewclip(pgs, gx_rule_winding_number);
}

int
gs_eoviewclip(gs_state *pgs)
{	return common_viewclip(pgs, gx_rule_even_odd);
}

private int
common_viewclip(gs_state *pgs, int rule)
{	/*
	 * Temporarily substitute the view clip path for the clip path
	 * so we can use gx_clip_to_path.
	 */
	gx_clip_path *save_cpath = pgs->clip_path;
	int code;

	pgs->clip_path = pgs->view_clip->path;
	code = gx_clip_to_path(pgs);
	pgs->clip_path = save_cpath;
	if ( code >= 0 )
	  gs_newpath(pgs);
	return code;
}

int
gs_viewclippath(gs_state *pgs)
{	gx_path cpath;
	const gx_clip_path *pcpath = pgs->view_clip->path;
	int code;

	if ( pcpath->rule == 0 ) {
	  /*
	   * No view clip path is active: fabricate one.
	   ****** SHOULD USE IMAGEABLE AREA, NOT ENTIRE PAGE ******
	   */
	  const gx_device *dev = pgs->device;

	  gx_path_init(&cpath, pgs->memory);
	  code = gx_path_add_rectangle(&cpath, fixed_0, fixed_0,
				       int2fixed(dev->width),
				       int2fixed(dev->height));
	} else {
	  gx_path path;

	  code = gx_cpath_path(pcpath, &path);
	  if ( code < 0 )
	    return code;
	  code = gx_path_copy(&path, &cpath, 1);
	}
	if ( code < 0 )
	  return code;
	gx_path_release(pgs->path);
	*pgs->path = cpath;
	return 0;
}

#else				/* !DPNEXT */

/* Provide dummy definitions, since gs_state.view_clip doesn't exist. */

int
gs_initviewclip(gs_state *pgs)
{	return 0;
}

int
gs_viewclip(gs_state *pgs)
{	return gs_newpath(pgs);
}

int
gs_eoviewclip(gs_state *pgs)
{	return gs_newpath(pgs);
}

int
gs_viewclippath(gs_state *pgs)
{	return gs_initclip(pgs);
}

#endif
