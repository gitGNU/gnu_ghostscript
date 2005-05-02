/* Copyright (C) 1994-2001, Ghostgum Software Pty Ltd.  All rights reserved.
  
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

/* $Id: gsdllwin.h,v 1.3 2005/05/02 00:03:33 Arabidopsis Exp $ */
/* gsdll extension for Microsoft Windows platforms */

#ifndef gsdllwin_INCLUDED
#  define gsdllwin_INCLUDED

/* DLL exported functions */
/* for load time dynamic linking */
GSDLLEXPORT HGLOBAL GSDLLAPI gsdll_copy_dib(unsigned char * device);
GSDLLEXPORT HPALETTE GSDLLAPI gsdll_copy_palette(unsigned char * device);
GSDLLEXPORT void GSDLLAPI gsdll_draw(unsigned char * device, HDC hdc, LPRECT dest,
			 LPRECT src);
GSDLLEXPORT int GSDLLAPI gsdll_get_bitmap_row(unsigned char *device,
				  LPBITMAPINFOHEADER pbmih,
				  LPRGBQUAD prgbquad, LPBYTE * ppbyte,
				  unsigned int row);

/* Function pointer typedefs */
/* for run time dynamic linking */
typedef HGLOBAL (GSDLLAPI * PFN_gsdll_copy_dib)(unsigned char *);
typedef HPALETTE (GSDLLAPI * PFN_gsdll_copy_palette)(unsigned char *);
typedef void (GSDLLAPI * PFN_gsdll_draw) (unsigned char *, HDC, LPRECT,
					  LPRECT);
typedef int (GSDLLAPI * PFN_gsdll_get_bitmap_row)
     (unsigned char *device, LPBITMAPINFOHEADER pbmih, LPRGBQUAD prgbquad,
      LPBYTE * ppbyte, unsigned int row);

#endif /* gsdllwin_INCLUDED */
