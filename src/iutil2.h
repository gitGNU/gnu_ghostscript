/* Copyright (C) 1993, 1994, 1998 artofcode LLC.  All rights reserved.
  
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

/*$Id: iutil2.h,v 1.1 2004/01/14 16:59:52 atai Exp $ */
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
int param_read_password(P3(gs_param_list *, const char *, password *));
int param_write_password(P3(gs_param_list *, const char *, const password *));

/* Check a password from a parameter list. */
/* Return 0 if OK, 1 if not OK, or an error code. */
int param_check_password(P2(gs_param_list *, const password *));

/* Read a password from, or write a password into, a dictionary */
/* (presumably systemdict). */
int dict_read_password(P3(password *, const ref *, const char *));
int dict_write_password(P4(const password *, ref *, const char *, bool));

#endif /* iutil2_INCLUDED */
