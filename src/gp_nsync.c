/* Copyright (C) 1998, 1999 Aladdin Enterprises.  All rights reserved.
  
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

*/

/* $Id: gp_nsync.c,v 1.4 2005/12/13 16:57:20 jemarch Exp $ */
/* Dummy thread / semaphore / monitor implementation */
#include "std.h"
#include "gserror.h"
#include "gserrors.h"
#include "gpsync.h"

/* ------- Synchronization primitives -------- */

/* Semaphores */

uint
gp_semaphore_sizeof(void)
{
    return sizeof(gp_semaphore);
}

int
gp_semaphore_open(gp_semaphore * sema)
{
    if (sema)
	*(int *)sema = 0;
    return 0;
}

int
gp_semaphore_close(gp_semaphore * sema)
{
    return 0;
}

int
gp_semaphore_wait(gp_semaphore * sema)
{
    if (*(int *)sema == 0)
	return_error(gs_error_unknownerror); /* no real waiting */
    --(*(int *)sema);
    return 0;
}

int
gp_semaphore_signal(gp_semaphore * sema)
{
    ++(*(int *)sema);
    return 0;
}

/* Monitors */

uint
gp_monitor_sizeof(void)
{
    return sizeof(gp_monitor);
}

int
gp_monitor_open(gp_monitor * mon)
{
    if (mon)
	mon->dummy_ = 0;
    return 0;
}

int
gp_monitor_close(gp_monitor * mon)
{
    return 0;
}

int
gp_monitor_enter(gp_monitor * mon)
{
    if (mon->dummy_ != 0)
	return_error(gs_error_unknownerror);
    mon->dummy_ = mon;
    return 0;
}

int
gp_monitor_leave(gp_monitor * mon)
{
    if (mon->dummy_ != mon)
	return_error(gs_error_unknownerror);
    mon->dummy_ = 0;
    return 0;
}

/* Thread creation */

int
gp_create_thread(gp_thread_creation_callback_t proc, void *proc_data)
{
    return_error(gs_error_unknownerror);
}
