#    Copyright (C) 1991-1997 Aladdin Enterprises.  All rights reserved.
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

# Common makefile section for 32-bit MS Windows.

# This makefile must be acceptable to Microsoft Visual C++, Watcom C++,
# and Borland C++.  For this reason, the only conditional directives
# allowed are !if[n]def, !else, and !endif.


# Note that built-in libpng and zlib aren't available.

SHARE_LIBPNG=0
SHARE_ZLIB=0

# Define the platform name.

!ifndef PLATFORM
PLATFORM=mswin32_
!endif

# Define the ANSI-to-K&R dependency.  Borland C, Microsoft C and
# Watcom C all accept ANSI syntax, but we need to preconstruct ccf32.tr 
# to get around the limit on the maximum length of a command line.

AK=ccf32.tr

# Define the syntax for command, object, and executable files.

CMD=.bat
O=-o
OBJ=obj
XE=.exe
XEAUX=.exe

# Define generic commands.

# We have to use a batch file for the equivalent of cp,
# because the DOS COPY command copies the file write time, like cp -p.
CP_=call cp.bat
RM_=erase
RMN_=call rm.bat

# Define the generic compilation flags.

PLATOPT=

INTASM=
PCFBASM=

# Define the files to be removed by `make clean'.
# nmake expands macros when encountered, not when used,
# so this must precede the !include statements.

BEGINFILES=gs*.res gs*.ico ccf32.tr\
   $(GSDLL).dll $(GSCONSOLE).exe\
   $(BEGINFILES2)

# Include the generic makefiles.
!include version.mak
!include gs.mak
!include lib.mak
!include jpeg.mak
!include libpng.mak
!include zlib.mak
!include devs.mak

# -------------------------- Auxiliary programs --------------------------- #

$(ECHOGS_XE): echogs.c
	$(CCAUX_SETUP)
	$(CCAUX) echogs.c $(CCAUX_TAIL)

# $(GENARCH_XE) is in individual (compiler-specific) makefiles.

$(GENCONF_XE): genconf.c $(stdpre_h)
	$(CCAUX_SETUP)
	$(CCAUX) genconf.c $(CCAUX_TAIL)

$(GENINIT_XE): geninit.c $(stdio__h) $(string__h)
	$(CCAUX_SETUP)
	$(CCAUX) geninit.c $(CCAUX_TAIL)

# No special gconfig_.h is needed.
# Assume `make' supports output redirection.
gconfig_.h: $(MAKEFILE)
	echo /* This file deliberately left blank. */ >gconfig_.h

gconfigv.h: $(MAKEFILE) $(ECHOGS_XE)
	$(EXP)echogs -w gconfigv.h -x 23 define USE_ASM -x 2028 -q $(USE_ASM)-0 -x 29
	$(EXP)echogs -a gconfigv.h -x 23 define USE_FPU -x 2028 -q $(FPU_TYPE)-0 -x 29
	$(EXP)echogs -a gconfigv.h -x 23 define EXTEND_NAMES 0$(EXTEND_NAMES)


# -------------------------------- Library -------------------------------- #

# The Windows Win32 platform

mswin32__=gp_mswin.$(OBJ) gp_msio.$(OBJ) gp_win32.$(OBJ) gp_nofb.$(OBJ) gp_ntfs.$(OBJ)
mswin32_.dev: $(mswin32__)
        $(SETMOD) mswin32_ $(mswin32__)
        $(ADDMOD) mswin32_ -iodev wstdio

gp_mswin.$(OBJ): gp_mswin.c $(AK) gp_mswin.h \
 $(ctype__h) $(dos__h) $(malloc__h) $(memory__h) $(string__h) $(windows__h) \
 $(gx_h) $(gp_h) $(gpcheck_h) $(gserrors_h) $(gsexit_h)

gp_msio.$(OBJ): gp_msio.c $(AK) gp_mswin.h \
 $(gsdll_h) $(stdio__h) $(gxiodev_h) $(stream_h) $(gx_h) $(gp_h) $(windows__h)

# end of winlib.mak
