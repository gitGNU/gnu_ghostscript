#    Copyright (C) 1991, 1995, 1996, 1997 Aladdin Enterprises.  All rights reserved.
# 
# This file is part of GNU Ghostscript.
# 
# GNU Ghostscript is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY.  No author or distributor accepts responsibility to
# anyone for the consequences of using it or for whether it serves any
# particular purpose or works at all, unless he says so in writing.  Refer to
# the GNU General Public License for full details.
# 
# Everyone is granted permission to copy, modify and redistribute GNU
# Ghostscript, but only under the conditions described in the GNU General
# Public License.  A copy of this license is supposed to have been given to
# you along with GNU Ghostscript so you can know your rights and
# responsibilities.  It should be in a file named COPYING.  Among other
# things, the copyright notice and this notice must be preserved on all
# copies.
# 
# Aladdin Enterprises is not affiliated with the Free Software Foundation or
# the GNU Project.  GNU Ghostscript, as distributed by Aladdin Enterprises,
# does not depend on any other GNU software.

# makefile for MS-DOS / Watcom C/C++ library testing.

libdefault: gslib.exe
	%null

GS_DOCDIR=c:/gs
GS_LIB_DEFAULT=.;c:/gs\;c:/gs/fonts
SEARCH_HERE_FIRST=1
GS_INIT=gs_init.ps

DEBUG=1
TDEBUG=0
NOPRIVATE=1

GS=gslib
JSRCDIR=jpeg-6a
JVERSION=6

PSRCDIR=libpng
PVERSION=96
SHARE_LIBPNG=0
LIBPNG_NAME=png

ZSRCDIR=zlib
SHARE_ZLIB=0
ZLIB_NAME=z

CONFIG=
CFLAGS=

# Allow predefinition of WCVERSION
# when using this makefile from inside another one.
!ifndef WCVERSION
WCVERSION=10.0
!endif
LIBPATHS=LIBPATH $(%WATCOM)\lib386 LIBPATH $(%WATCOM)\lib386\dos
STUB=$(%WATCOM)\binb\wstub.exe

CPU_TYPE=386
FPU_TYPE=0

PLATFORM=watclib_
MAKEFILE=watclib.mak
PLATOPT=

!include wccommon.mak

# Allow predefinition of selectable options
# when using this makefile from inside another one.
!ifndef FEATURE_DEVS
FEATURE_DEVS=patlib.dev path1lib.dev hsblib.dev
!endif
!ifndef DEVICE_DEVS
DEVICE_DEVS=vga.dev
!endif
!ifndef COMPILE_INITS
COMPILE_INITS=0
!endif
!ifndef BAND_LIST_STORAGE
BAND_LIST_STORAGE=file
!endif
!ifndef BAND_LIST_COMPRESSOR
BAND_LIST_COMPRESSOR=zlib
!endif
!ifndef FILE_IMPLEMENTATION
FILE_IMPLEMENTATION=stdio
!endif

!include wctail.mak
!include devs.mak

watclib__=gp_iwatc.$(OBJ) gp_msdos.$(OBJ) gp_nofb.$(OBJ) gp_dosfs.$(OBJ) gp_dosfe.$(OBJ)
watclib_.dev: $(watclib__)
	$(SETMOD) watclib_ $(watclib__)

gp_iwatc.$(OBJ): gp_iwatc.c $(stat__h) $(string__h) $(gx_h) $(gp_h)

BEGINFILES=*.err
CCBEGIN=for %%f in (gs*.c gx*.c z*.c) do $(CCC) %%f

LIB_ONLY=gslib.obj gsnogc.obj gconfig.obj gscdefs.obj
ll_tr=ll$(CONFIG).tr
$(ll_tr): $(MAKEFILE)
	echo SYSTEM DOS4G >$(ll_tr)
	echo OPTION STUB=$(STUB) >>$(ll_tr)
	echo OPTION STACK=12k >>$(ll_tr)
	echo FILE gsnogc.obj >>$(ll_tr)
	echo FILE gconfig.obj >>$(ll_tr)
	echo FILE gscdefs.obj >>$(ll_tr)

gslib.exe: $(LIB_ALL) $(LIB_ONLY) $(ld_tr) $(ll_tr)
	$(LINK) $(LCT) NAME gslib OPTION MAP=gslib FILE gslib @$(ld_tr) @$(ll_tr)
