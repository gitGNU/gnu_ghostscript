/* Copyright (C) 2000 artofcode LLC.  All rights reserved.
  
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

/*$Id: gdevpsu.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
/* Interface to PostScript-writing utilities */

#ifndef gdevpsu_INCLUDED
#  define gdevpsu_INCLUDED

/* Define parameters and state for PostScript-writing drivers. */
typedef struct gx_device_pswrite_common_s {
    float LanguageLevel;
    bool ProduceEPS;
    int ProcSet_version;
    long bbox_position;		/* set when writing file header */
} gx_device_pswrite_common_t;
#define PSWRITE_COMMON_PROCSET_VERSION 1000 /* for definitions in gdevpsu.c */
#define PSWRITE_COMMON_VALUES(ll, eps, psv)\
  {ll, eps, PSWRITE_COMMON_PROCSET_VERSION + (psv)}

/* ---------------- Low level ---------------- */

/* Write a 0-terminated array of strings as lines. */
void psw_print_lines(P2(FILE *f, const char *const lines[]));

/* ---------------- File level ---------------- */

/*
 * Write the file header, up through the BeginProlog.  This must write to a
 * file, not a stream, because it may be called during finalization.
 */
void psw_begin_file_header(P5(FILE *f, const gx_device *dev,
			      const gs_rect *pbbox,
			      gx_device_pswrite_common_t *pdpc, bool ascii));

/* End the file header.*/
void psw_end_file_header(P1(FILE *f));

/* End the file. */
void psw_end_file(P5(FILE *f, const gx_device *dev,
		     const gx_device_pswrite_common_t *pdpc,
		     const gs_rect *pbbox, int page_count));

/* ---------------- Page level ---------------- */

/*
 * Write the page header.
 */
void psw_write_page_header(P5(stream *s, const gx_device *dev,
			      const gx_device_pswrite_common_t *pdpc,
			      bool do_scale, long page_ord));
/*
 * Write the page trailer.  We do this directly to the file, rather than to
 * the stream, because we may have to do it during finalization.
 */
void psw_write_page_trailer(P3(FILE *f, int num_copies, int flush));

#endif /* gdevpsu_INCLUDED */

