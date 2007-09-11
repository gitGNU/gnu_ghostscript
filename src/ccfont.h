/* Copyright (C) 2001-2006 Artifex Software, Inc.
   All Rights Reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or
  modify it under the terms of the version 2 of the GNU General Public
  License as published by the Free Software Foundation.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

/* $Id: ccfont.h,v 1.7 2007/09/11 15:24:00 Arabidopsis Exp $ */
/* Header for fonts compiled into C. */

#ifndef ccfont_INCLUDED
#  define ccfont_INCLUDED

/* Include all the things a compiled font needs. */
#include "stdpre.h"
#include "gsmemory.h"
#include "iref.h"
#include "ivmspace.h"		/* for avm_foreign */
#include "store.h"

/* Define type-specific refs for initializing arrays. */
#define ref_(t) struct { struct tas_s tas; t value; }
#define boolean_v(b) { {t_boolean<<r_type_shift}, (ushort)(b) }
#define integer_v(i) { {t_integer<<r_type_shift}, (long)(i) }
#define null_v() { {t_null<<r_type_shift} }
#define real_v(v) { {t_real<<r_type_shift}, (float)(v) }

/* Define other initialization structures. */
typedef struct {
    byte encx, charx;
} charindex;

/*
 * We represent mostly-string arrays by byte strings.  Each element
 * starts with length bytes.  If the first length byte is not 255,
 * it and the following byte define a big-endian length of a string or name.
 * If the first two bytes are (255,255), this element is null.
 * Otherwise, the initial 255 is followed by a 2-byte big-endian length
 * of a string that must be scanned as a token.
 */
typedef const char *cfont_string_array;

/* Support routines in iccfont.c */
typedef struct {
    const charindex *enc_keys;	/* keys from encoding vectors */
    uint num_enc_keys;
    uint num_str_keys;
    uint extra_slots;		/* (need extra for fonts) */
    uint dict_attrs;		/* protection for dictionary */
    uint value_attrs;		/* protection for values */
    /* (only used for string dicts) */
} cfont_dict_keys;

/*
 * We pass a procedure vector to the font initialization routine
 * to avoid having externs, which compromise sharability.
 */
typedef struct cfont_procs_s {
    int (*ref_dict_create) (i_ctx_t *, ref *, const cfont_dict_keys *,
			    cfont_string_array, const ref *);
    int (*string_dict_create) (i_ctx_t *, ref *, const cfont_dict_keys *,
			       cfont_string_array, cfont_string_array);
    int (*num_dict_create) (i_ctx_t *, ref *, const cfont_dict_keys *,
			    cfont_string_array, const ref *, const char *);
    int (*name_array_create) (i_ctx_t *, ref *, cfont_string_array, int);
    int (*string_array_create) (i_ctx_t *, ref *, cfont_string_array,
				int /*size */ , uint /*protection */ );
    int (*scalar_array_create) (i_ctx_t *, ref *, const ref *,
				int /*size */ , uint /*protection */ );
    int (*name_create) (i_ctx_t *, ref *, const char *);
    int (*ref_from_string) (i_ctx_t *, ref *, const char *, uint);
} cfont_procs;

/*
 * In order to make it possible for third parties to compile fonts (into
 * a shared library, on systems that support such things), we define
 * a tiny procedural interface for getting access to the compiled font table.
 */
#define ccfont_proc(proc)\
  int proc(i_ctx_t *, const cfont_procs *, ref *)
typedef ccfont_proc((*ccfont_fproc));

/*
 * There should be some consts in the *** below, but a number of
 * C compilers don't handle const properly in such situations.
 */
extern int ccfont_fprocs(int *, const ccfont_fproc **);

#define ccfont_version 19	/* for checking against libraries */

#endif /* ccfont_INCLUDED */
