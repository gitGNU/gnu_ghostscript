/* Copyright (C) 1999 artofcode LLC.  All rights reserved.
  
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

/*$Id: gsnotify.h,v 1.1 2004/01/14 16:59:50 atai Exp $ */
/* Notification machinery */

#ifndef gsnotify_INCLUDED
#  define gsnotify_INCLUDED

#include "gsstype.h"		/* for extern_st */

/*
 * An arbitrary number of clients may register themselves to be notified
 * when an event occurs.  Duplicate registrations are not detected.  Clients
 * must unregister themselves when they are being freed (finalized), if not
 * before.  Objects that provide notification must notify clients when the
 * object is being freed (finalized): in this event, and only in this event,
 * event_data = NULL.
 */

/* Define the structure used to keep track of registrations. */
#define GS_NOTIFY_PROC(proc)\
    int proc(P2(void *proc_data, void *event_data))
typedef GS_NOTIFY_PROC((*gs_notify_proc_t));
typedef struct gs_notify_registration_s gs_notify_registration_t;
struct gs_notify_registration_s {
    gs_notify_proc_t proc;
    void *proc_data;
    gs_notify_registration_t *next;
};
#define private_st_gs_notify_registration() /* in gsnotify.c */\
  gs_private_st_ptrs2(st_gs_notify_registration, gs_notify_registration_t,\
    "gs_notify_registration_t", notify_registration_enum_ptrs,\
    notify_registration_reloc_ptrs, proc_data, next)

/* Define a notification list. */
typedef struct gs_notify_list_s {
    gs_memory_t *memory;	/* for allocating registrations */
    gs_notify_registration_t *first;
} gs_notify_list_t;
/* The descriptor is public for GC of embedded instances. */
extern_st(st_gs_notify_list);
#define public_st_gs_notify_list() /* in gsnotify.c */\
  gs_public_st_ptrs1(st_gs_notify_list, gs_notify_list_t,\
    "gs_notify_list_t", notify_list_enum_ptrs, notify_list_reloc_ptrs,\
    first)
#define st_gs_notify_list_max_ptrs 1

/* Initialize a notification list. */
void gs_notify_init(P2(gs_notify_list_t *nlist, gs_memory_t *mem));

/* Register a client. */
int gs_notify_register(P3(gs_notify_list_t *nlist, gs_notify_proc_t proc,
			  void *proc_data));

/*
 * Unregister a client.  Return 1 if the client was registered, 0 if not.
 * If proc_data is 0, unregister all registrations of that proc; otherwise,
 * unregister only the registration of that procedure with that proc_data.
 */
int gs_notify_unregister(P3(gs_notify_list_t *nlist, gs_notify_proc_t proc,
			    void *proc_data));

/* Unregister a client, calling a procedure for each unregistration. */
int gs_notify_unregister_calling(P4(gs_notify_list_t *nlist,
				    gs_notify_proc_t proc, void *proc_data,
				    void (*unreg_proc)(P1(void *pdata))));

/*
 * Notify the clients on a list.  If an error occurs, return the first
 * error code, but notify all clients regardless.
 */
int gs_notify_all(P2(gs_notify_list_t *nlist, void *event_data));

/* Release a notification list. */
void gs_notify_release(P1(gs_notify_list_t *nlist));

#endif /* gsnotify_INCLUDED */
