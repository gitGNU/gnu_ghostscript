/* Copyright (C) 1992, 1993, 1996 Aladdin Enterprises.  All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License version 2
  as published by the Free Software Foundation.


  This software is provided AS-IS with no warranty, either express or
  implied. That is, this program is distributed in the hope that it will 
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA, 02111-1307.
  
  For more information about licensing, please refer to
  http://www.ghostscript.com/licensing/. For information on
  commercial licensing, go to http://www.artifex.com/licensing/ or
  contact Artifex Software, Inc., 101 Lucas Valley Road #110,
  San Rafael, CA  94903, U.S.A., +1(415)492-9861.
*/

/* $Id: gp_mswin.h,v 1.2 2004/02/14 22:20:16 atai Exp $ */
/* (used by both C code and Windows 'resource') */

#ifndef gp_mswin_INCLUDED
#  define gp_mswin_INCLUDED


#define GSTEXT_ICON	50
#define GSIMAGE_ICON	51
#define SPOOL_PORT	100
#define CANCEL_PCDONE	101
#define CANCEL_PRINTING	102

#ifndef RC_INVOKED		/* NOTA BENE */

/* system menu constants for image window */
#define M_COPY_CLIP 1

/* externals from gp_mswin.c */

/* Patch 26.10.94 :for Microsoft C/C++ 8.0 32-Bit       */
/* "_export" is Microsoft 16-Bit specific.              */
/* With MS-C/C++ 8.00 32 Bit "_export" causes an error. */
#if defined(_WIN32) && defined(_MSC_VER)
#define _export
#endif

/* 
extern HWND hwndtext;
extern HWND hDlgModeless;
*/
extern HINSTANCE phInstance;
extern const LPSTR szAppName;
extern BOOL is_win32s;
extern int is_spool(const char *queue);

#endif /* !defined(RC_INVOKED) */

#endif /* gp_mswin_INCLUDED */
