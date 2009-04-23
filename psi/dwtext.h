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

/* $Id: dwtext.h,v 1.1 2009/04/23 23:31:49 Arabidopsis Exp $ */
/* Text Window class */

#ifndef dwtext_INCLUDED
#  define dwtext_INCLUDED


#ifdef _WINDOWS
#define _Windows
#endif


typedef struct TEXTWINDOW_S {
    const char *Title;		/* required */
    HICON hIcon;		/* optional */
    BYTE *ScreenBuffer;
    POINT ScreenSize;		/* optional */
    char *DragPre;		/* optional */
    char *DragPost;		/* optional */
    int nCmdShow;		/* optional */

    HWND hwnd;

    BYTE *KeyBuf;
    BYTE *KeyBufIn;
    BYTE *KeyBufOut;
    unsigned int KeyBufSize;
    BOOL quitnow;

    char line_buf[256];
    int line_end;
    int line_start;
    BOOL line_complete;
    BOOL line_eof;

    BOOL bFocus;
    BOOL bGetCh;

    char *fontname;	/* font name */
    int fontsize;	/* font size in pts */

    HFONT hfont;
    int CharAscent;

    int CaretHeight;
    int CursorFlag;
    POINT CursorPos;
    POINT ClientSize;
    POINT CharSize;
    POINT ScrollPos;
    POINT ScrollMax;

    int x, y, cx, cy;	/* window position */
} TW;


/* Create new TW structure */
TW *text_new(void);

/* Destroy window and TW structure */
void text_destroy(TW *tw);

/* test if a key has been pressed
 * return TRUE if key hit
 * return FALSE if no key
 */
int text_kbhit(TW *tw);

/* Get a character from the keyboard, waiting if necessary */
int getch(void);

/* Get a line from the keyboard
 * store line in buf, with no more than len characters
 * including null character
 * return number of characters read
 */
int text_gets(TW *tw, char *buf, int len);

/* Get a line from the keyboard
 * store line in buf, with no more than len characters
 * line is not null terminated
 * return number of characters read
 */
int text_read_line(TW *tw, char *buf, int len);

/* Put a character to the window */
int text_putch(TW *tw, int ch);

/* Write cnt character from buf to the window */
void text_write_buf(TW *tw, const char *buf, int cnt);

/* Put a string to the window */
void text_puts(TW *tw, const char *str);

/* Scroll window to make cursor visible */
void text_to_cursor(TW *tw);

/* register window class */
int text_register_class(TW *tw, HICON hicon);

/* Create and show window with given name and min/max/normal state */
/* return 0 on success, non-zero on error */
int text_create(TW *tw, const char *title, int cmdShow);

/* Set window font and size */
/* a must choose monospaced */
void text_font(TW *tw, const char *fontname, int fontsize);

/* Set screen size in characters */
void text_size(TW *tw, int width, int height);

/* Set and get the window position and size */
void text_setpos(TW *tw, int x, int y, int cx, int cy);
int text_getpos(TW *tw, int *px, int *py, int *pcx, int *pcy);

/* Set pre drag and post drag strings
 * If a file is dropped on the window, the following will
 * be poked into the keyboard buffer: 
 *   the pre_drag string
 *   the file name
 *   the post_drag string
 */
void text_drag(TW *tw, const char *pre_drag, const char *post_drag);

/* provide access to window handle */
HWND text_get_handle(TW *tw);

/* ================================== */


#endif /* dwtext_INCLUDED */