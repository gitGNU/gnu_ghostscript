/* Copyright (C) 1992, 1993, 1996 artofcode LLC.  All rights reserved.
  
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

/*$Id: gp_mswin.h,v 1.1 2004/01/14 16:59:48 atai Exp $ */
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
