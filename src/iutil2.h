/* Copyright (C) 1993, 1994, 1998 Aladdin Enterprises.  All rights reserved.
  
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

/* $Id: iutil2.h,v 1.3 2005/05/02 00:03:33 Arabidopsis Exp $ */
/* Interface to procedures in iutil2.c */

#ifndef iutil2_INCLUDED
#  define iutil2_INCLUDED

/* ------ Password utilities ------ */

/* Define the password structure. */
/* NOTE: MAX_PASSWORD must match the initial password lengths in gs_lev2.ps. */
#define MAX_PASSWORD 64		/* must be at least 11 */
typedef struct password_s {
    uint size;
    byte data[MAX_PASSWORD];
} password;

# define NULL_PASSWORD {0, {0}}

/* Transmit a password to or from a parameter list. */
int param_read_password(gs_param_list *, const char *, password *);
int param_write_password(gs_param_list *, const char *, const password *);

/* Check a password from a parameter list. */
/* Return 0 if OK, 1 if not OK, or an error code. */
int param_check_password(gs_param_list *, const password *);

/* Read a password from, or write a password into, a dictionary */
/* (presumably systemdict). */
int dict_read_password(password *, const ref *, const char *);
int dict_write_password(const password *, ref *, const char *, bool);

#endif /* iutil2_INCLUDED */
