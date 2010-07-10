/* Copyright (C) 2001-2006 Artifex Software, Inc.
   All Rights Reserved.
  
   This software is provided AS-IS with no warranty, either express or
   implied.

   This software is distributed under license and may not be copied, modified
   or distributed except as expressly authorized under the terms of that
   license.  Refer to licensing information at http://www.artifex.com/
   or contact Artifex Software, Inc.,  7 Mt. Lassen Drive - Suite A-134,
   San Rafael, CA  94903, U.S.A., +1(415)492-9861, for further information.
*/

/* $Id: gscolor1.h,v 1.2 2010/07/10 22:02:25 Arabidopsis Exp $ */
/* Client interface to Level 1 extended color facilities */
/* Requires gscolor.h */

#ifndef gscolor1_INCLUDED
#  define gscolor1_INCLUDED

/* Color and gray interface */
int gs_setcmykcolor(gs_state *, floatp, floatp, floatp, floatp),
    gs_currentcmykcolor(const gs_state *, float[4]),
    gs_setblackgeneration(gs_state *, gs_mapping_proc),
    gs_setblackgeneration_remap(gs_state *, gs_mapping_proc, bool);
gs_mapping_proc gs_currentblackgeneration(const gs_state *);
int gs_setundercolorremoval(gs_state *, gs_mapping_proc),
    gs_setundercolorremoval_remap(gs_state *, gs_mapping_proc, bool);
gs_mapping_proc gs_currentundercolorremoval(const gs_state *);

/* Transfer function */
int gs_setcolortransfer(gs_state *, gs_mapping_proc /*red */ ,
			gs_mapping_proc /*green */ ,
			gs_mapping_proc /*blue */ ,
			gs_mapping_proc /*gray */ ),
    gs_setcolortransfer_remap(gs_state *, gs_mapping_proc /*red */ ,
			      gs_mapping_proc /*green */ ,
			      gs_mapping_proc /*blue */ ,
			      gs_mapping_proc /*gray */ , bool);
void gs_currentcolortransfer(const gs_state *, gs_mapping_proc[4]);

#endif /* gscolor1_INCLUDED */
