/* Copyright (C) 1996, 2001, Ghostgum Software Pty Ltd.  All rights reserved.

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

/* $Id: dwimg.h,v 1.1 2004/01/14 16:59:47 atai Exp $ */

#ifndef dwimg_INCLUDED
#  define dwimg_INCLUDED

/* Windows Image Window structure */

typedef struct IMAGE_S IMAGE;
struct IMAGE_S {
    void *handle;
    void *device;
    HWND hwnd;
    HBRUSH hBrush;	/* background */
    int raster;
    unsigned int format;
    unsigned char *image;
    BITMAPINFOHEADER bmih;
    HPALETTE palette;
    int bytewidth;
    int sep;		/* CMYK separations to display */

    /* periodic redrawing */
    SYSTEMTIME update_time;
    int update_interval;

    /* Window scrolling stuff */
    int cxClient, cyClient;
    int cxAdjust, cyAdjust;
    int nVscrollPos, nVscrollMax;
    int nHscrollPos, nHscrollMax;

    /* thread synchronisation */
    HANDLE hmutex;

    IMAGE *next;

    HWND hwndtext;	/* handle to text window */

    int x, y, cx, cy;	/* window position */
};

extern IMAGE *first_image;

/* Main thread only */
IMAGE *image_find(void *handle, void *device);
IMAGE *image_new(void *handle, void *device);
void image_delete(IMAGE *img);
int image_size(IMAGE *img, int new_width, int new_height, int new_raster, 
   unsigned int new_format, void *pimage);

/* GUI thread only */
void image_open(IMAGE *img);
void image_close(IMAGE *img);
void image_sync(IMAGE *img);
void image_page(IMAGE *img);
void image_presize(IMAGE *img, int new_width, int new_height, int new_raster, 
   unsigned int new_format);
void image_poll(IMAGE *img);

#endif /* dwimg_INCLUDED */
