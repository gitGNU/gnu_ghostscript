/* Copyright (C) 2001-2006 Artifex Software, Inc.
   All Rights Reserved.
  
   This software is provided AS-IS with no warranty, either express or
   implied.

   This software is distributed under license and may not be copied, modified
   or distributed except as expressly authorized under the terms of that
   license.  Refer to licensing information at http://www.artifex.com/
   or contact Artifex Software, Inc.,  7 Mt. Lassen Drive - Suite A-134,
   San Rafael, CA  94903, U.S.A., +1(415)492-9861, for further information.
*/

/* $Id: gdevsco.c,v 1.2 2010/07/10 22:02:19 Arabidopsis Exp $ */
/* 17Jul91 - wb - based on gdevpcfb.c */
/* 31Jul91 - Rick Calder rick@rick.att.com - ifdefs for AT&T UNIX 4.0 2.1 */
/* 13Sep91 - wb - modify for gs24b2 */
/*  9Mar92 - wb - modify for gs24b4 */
/* generate SCO Xenix/Unix style memory mapped ioctl output */
#include "memory_.h"
#include "gx.h"
#include "gserrors.h"
#include "gxdevice.h"
#include "gdevpcfb.h"
#include <signal.h>

#ifdef M_XENIX
#include <sys/console.h>	/* SCO Xenix and SCO UNIX */
#ifndef CONSIO
#include <sys/machdep.h>	/* Xenix needs this also */
#endif
#else
#include <sys/kd.h>		/* AT&T SVR4 */
#endif

#if defined(__STDC__)
#include <stdlib.h>
#else
extern char *getenv(const char *);
#endif

#if defined(M_XENIX)
#include <prototypes.h>
#include <fcntl.h>
#else
extern int ioctl(int, int,...);
extern int open(const char *, int,...);
#endif

static int console_fd = -1;	/* file descriptor of console */
fb_ptr fb_addr;			/* address of frame buffer for unix */
static int cur_mode = -1;	/* current video mode */

/* open the console */
/* possible files to open:
 * /dev/console = current system console
 * /dev/vga = vga monitor
 * /dev/tty = current terminal
 */

static void open_console(void);

static void
open_console()
{
    const char *dev;

    if (console_fd != -1)
	return;
    dev = getenv("GSDEVICE");
    if (dev == NULL || *dev == '\0')
	dev = "/dev/tty";
    console_fd = open(dev, 0);
    if (console_fd == -1) {
	ega_close((gx_device *) NULL);
	eprintf1("unable to map display '%s'\n", dev);
	perror("open_console");
	exit(1);
    }
}

#if defined(__GNUC__)
	/* Done with inline assembly in gdevpcfb.h */
#else
/* Output to a port */
void
outportb(uint port, byte data)
{
    int i;
    struct port_io_arg pio;

    if (console_fd == -1)
	open_console();
    pio.args[0].dir = OUT_ON_PORT;
    pio.args[0].port = port;
    pio.args[0].data = data;
    pio.args[1].port = 0;
    pio.args[2].port = 0;
    pio.args[3].port = 0;
    i = ioctl(console_fd, CONSIO, (long)(&pio));
    if (i == -1) {
	ega_close((gx_device *) NULL);
	eprintf("error setting device register\n");
	perror("outportb");
	exit(1);
    }
}

/* Output to 2 consecutive ports */
void
outport2(uint port, byte index, byte data)
{
    int i;
    struct port_io_arg pio;

    if (console_fd == -1)
	open_console();
    pio.args[0].dir = OUT_ON_PORT;
    pio.args[0].port = port;
    pio.args[0].data = index;
    pio.args[1].dir = OUT_ON_PORT;
    pio.args[1].port = port + 1;
    pio.args[1].data = data;
    pio.args[2].port = 0;
    pio.args[3].port = 0;
    i = ioctl(console_fd, CONSIO, (long)(&pio));
    if (i == -1) {
	ega_close((gx_device *) NULL);
	eprintf("error setting device register\n");
	perror("outport2");
	exit(1);
    }
}
#endif

/* interrupt signal handler */
/*  restore the video mode and exit */
static void
ega_int_handler(int sig)
{
    ega_close((gx_device *) NULL);
    eprintf("GS exiting...\n");
    exit(1);
}

/*
 * FIXME to make this work, the SIGCONT handler must restore the
 * the video state, including all the registers.
 * For now, I made the SIGSTOP handler exit just call the SIGINT handler
 */

#ifdef	SIGTSTP
/* user tried to stop us.  restore video and stop */
static void
ega_tstp_handler(int sig)
{
#if 1
    ega_int_handler(sig);
#else
    /* Preferable, but sco does not restore the monitor corretly */
    signal(SIGTSTP, ega_tstp_handler);
    ega_close((gx_device *) NULL);
    eprintf("GS stopping...\n");
    signal(SIGSTOP, SIG_DFL);
    kill(getpid(), SIGSTOP);
#endif
}
#endif /* SIGTSTP */

#ifdef	SIGCONT
/* we were unstopped.  reopen video */
static void
ega_cont_handler(int sig)
{
#if 1
    ega_int_handler(sig);
#else
    signal(SIGCONT, ega_cont_handler);
    ega_set_mode(cur_mode);
#endif
}
#endif /* SIGCONT */

/* ------ Internal routines ------ */

/* Catch signals so we can restore the video mode on exit. */
void
pcfb_set_signals(gx_device * dev)
{
    signal(SIGINT, ega_int_handler);
    signal(SIGTERM, ega_int_handler);
#ifdef	SIGTSTP
    signal(SIGTSTP, ega_tstp_handler);
#endif
#ifdef	SIGCONT
    signal(SIGCONT, ega_cont_handler);
#endif
}

/* Read the device mode */
void
pcfb_get_state(pcfb_bios_state * pbs)
{
    int mode;

    open_console();
    mode = ioctl(console_fd, CONS_CURRENT, 0L);
    if (mode == -1) {
#ifdef __linux__
	mode = M_ENH_C80x25;
#else
	ega_close((gx_device *) NULL);
	eprintf("unable to get current console mode\n");
	perror("pcfb_get_state");
	exit(1);
#endif
    }
    pbs->display_mode =
	(mode == M_ENH_CG640 || mode == M_CG640x350 ? 0x10 :
#ifdef M_VGA12
	 mode == M_VGA12 ? 0x12 :
#endif
	 0x03);
}

/* Set the device mode */
void
pcfb_set_mode(int mode)
{
    int i, mode1;

    open_console();
    cur_mode = mode;
    mode1 = -1;
    if (mode == 0x10)
	mode = SW_ENH_CG640;
#ifdef SW_VGA12
    else if (mode == 0x12)
	mode = SW_VGA12;
#endif
    else if (mode == 0x03) {
#ifdef SW_VGA80x25
	mode = SW_VGA80x25;
	mode1 = SW_ENHC80x25;
#else
	mode = SW_ENHC80x25;
#endif
    } else {
	eprintf1("can not set to video mode %d\n", mode);
	exit(1);
    }
    i = ioctl(console_fd, mode, 0L);
    if (i == -1 && mode1 != -1)
	i = ioctl(console_fd, mode1, 0L);
    if (i == -1) {
	ega_close((gx_device *) NULL);
	eprintf("unable to set console mode\n");
	perror("pcfb_set_mode");
	exit(1);
    }
#ifdef VGA_IOPRIVL
    if (ioctl(console_fd, VGA_IOPRIVL, 1) == -1) {
	ega_close((gx_device *) NULL);
	eprintf("unable to get I/O privilege\n");
	perror("pcfb_set_mode");
	exit(1);
    }
#endif
    i = ioctl(console_fd, MAPCONS, 0L);
    if (i == -1) {
	ega_close((gx_device *) NULL);
	eprintf("unable to map console adaptor's display memory\n");
	perror("pcfb_set_mode");
	exit(1);
    }
    fb_addr = (fb_ptr) (i);
}

/* Restore the device state */
void
pcfb_set_state(const pcfb_bios_state * pbs)
{
    pcfb_set_mode(pbs->display_mode);
}
