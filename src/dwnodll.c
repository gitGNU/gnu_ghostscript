/* Copyright (C) 1996-2000 Ghostgum Software Pty Ltd.  All rights reserved.
  
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

/* dwnodll.c */
/* $Id: dwnodll.c,v 1.1 2004/01/14 16:59:47 atai Exp $ */

#define STRICT
#include <windows.h>
#include <string.h>
#include <stdio.h>

#include "stdpre.h"
#include "gpgetenv.h"
#include "gscdefs.h"
#define GSREVISION gs_revision

#include "dwdll.h"

/* We are static linking, so just store the function addresses */
int load_dll(GSDLL *gsdll, char *last_error, int len)
{
    gsdll->new_instance = &gsapi_new_instance;
    gsdll->delete_instance = &gsapi_delete_instance;
    gsdll->set_stdio = &gsapi_set_stdio;
    gsdll->set_poll = &gsapi_set_poll;
    gsdll->set_display_callback = &gsapi_set_display_callback;
    gsdll->init_with_args = &gsapi_init_with_args;
    gsdll->run_string = &gsapi_run_string;
    gsdll->exit = &gsapi_exit;
    return 0;
}

void unload_dll(GSDLL *gsdll)
{
}
