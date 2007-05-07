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

/* $Id: gdevpdtx.h,v 1.6 2007/05/07 11:21:47 Arabidopsis Exp $ */
/* Shared implementation definitions for pdfwrite text and fonts */

#ifndef gdevpdtx_INCLUDED
#  define gdevpdtx_INCLUDED

#include "gdevpdt.h"

/*
 * The pdfwrite text code is designed in layers.  Each layer uses only
 * facilities defined in that layer and those below it.  The layers and the
 * code files that define them are:
 *
 * Text processing
 *   gdevpdtt.c - main text processing and utilities
 *   gdevpdtc.c - processing for composite and CID-based fonts
 *   gdevpdte.c - processing for Encoding-based (i.e., all other) fonts
 *   gdevpdts.c - text state bookkeeping
 *   gdevpdt[st].h - definitions shared by the above
 * Font resources
 *   gdevpdtf.h - interface and public definitions
 *   gdevpdtf.c - implementation of font resources, except for writing
 *   gdevpdtw.[hc] - font resource writing
 * Font descriptors
 *   gdevpdtd.h - interface and public definitions
 *   gdevpdtd.c - implementation of font descriptors
 * Base fonts
 *   gdevpdtb.h - interface and public definitions
 *   gdevpdtb.c - implementation of base fonts
 *
 * There is also a module for bitmap font processing:
 *   gdevpdti.h - interface and public definitions
 *   gdevpdti.c - implementation of bitmap fonts
 * This handles both text processing and font resource management for
 * Type 3 bitmap fonts, which don't fit into the layer structure very well.
 */

/* ================ Types and structures ================ */

/*
 * Define the structure for managing the text and font state.  This is
 * made up of several individually opaque components.
 */

#ifndef pdf_bitmap_fonts_DEFINED
#  define pdf_bitmap_fonts_DEFINED
typedef struct pdf_bitmap_fonts_s pdf_bitmap_fonts_t;
#endif
#ifndef pdf_outline_fonts_DEFINED
#  define pdf_outline_fonts_DEFINED
typedef struct pdf_outline_fonts_s pdf_outline_fonts_t;
#endif
#ifndef pdf_text_state_DEFINED
#  define pdf_text_state_DEFINED
typedef struct pdf_text_state_s pdf_text_state_t;
#endif

/*typedef struct pdf_text_data_s pdf_text_data_t;*/  /* gdevpdfx.h */
struct pdf_text_data_s {
    pdf_outline_fonts_t *outline_fonts;	/* gdevpdtf.c */
    pdf_bitmap_fonts_t *bitmap_fonts; /* gdevpdti.c */
    pdf_text_state_t *text_state; /* gdevpdts.c */
};
#define private_st_pdf_text_data() /* gdevpdt.c */\
  gs_private_st_ptrs3(st_pdf_text_data, pdf_text_data_t, "pdf_text_data_t",\
    pdf_text_data_enum_ptrs, pdf_text_data_reloc_ptrs,\
    outline_fonts, bitmap_fonts, text_state)

/* ================ Procedures (internal utilities) ================ */

/* The typedef will eventually move to gdevpdfx.h. */
typedef struct pdf_font_resource_s pdf_font_resource_t;

/* ---------------- Font accessing ---------------- */

/* Get the object ID of a font resource. */
long pdf_font_id(const pdf_font_resource_t *pdfont);
/* Register charproc fonts with the page or substream. */
int pdf_used_charproc_resources(gx_device_pdf *pdev, pdf_font_resource_t *pdfont);

#endif /* gdevpdtx_INCLUDED */
