/* Copyright (C) 2002 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: gdevpdti.h,v 1.3 2005/05/02 00:03:24 Arabidopsis Exp $ */
/* Bitmap font interface for pdfwrite */

#ifndef gdevpdti_INCLUDED
#  define gdevpdti_INCLUDED

#include "gdevpdt.h"

/*
 * Bitmap fonts are Type 3 fonts created internally by pdfwrite.  Their
 * CharProc consists of a single bitmap image at "device" resolution.
 */

/* ================ Types and structures ================ */

#ifndef pdf_bitmap_fonts_DEFINED
#  define pdf_bitmap_fonts_DEFINED
typedef struct pdf_bitmap_fonts_s pdf_bitmap_fonts_t;
#endif

/* ================ Procedures ================ */

/* Exported for gdevpdf.c */

/*
 * Update text state at the end of a page.
 */
void pdf_close_text_page(gx_device_pdf *pdev);

/* Exported for gdevpdfb.c */

/* Return the Y offset for a bitmap character image. */
int pdf_char_image_y_offset(const gx_device_pdf *pdev, int x, int y, int h);

/* Begin a CharProc for an embedded (bitmap) font. */
int pdf_begin_char_proc(gx_device_pdf * pdev, int w, int h, int x_width,
			int y_offset, gs_id id, pdf_char_proc_t **ppcp,
			pdf_stream_position_t * ppos);

/* End a CharProc. */
int pdf_end_char_proc(gx_device_pdf * pdev, pdf_stream_position_t * ppos);

/* Put out a reference to an image as a character in an embedded font. */
int pdf_do_char_image(gx_device_pdf * pdev, const pdf_char_proc_t * pcp,
		      const gs_matrix * pimat);

/* Only used within text code */

/*
 * Allocate and initialize bookkeeping for bitmap fonts.
 */
pdf_bitmap_fonts_t *pdf_bitmap_fonts_alloc(gs_memory_t *mem);

/*
 * Write the Encoding for bitmap fonts, if needed.
 */
int pdf_write_bitmap_fonts_Encoding(gx_device_pdf *pdev);

/* Write the contents of a Type 3 bitmap font resource. */
int pdf_write_contents_bitmap(gx_device_pdf *pdev, pdf_font_resource_t *pdfont);

#endif /* gdevpdti_INCLUDED */
