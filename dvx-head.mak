#    Copyright (C) 1994, 1996 Aladdin Enterprises.  All rights reserved.
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

# Partial makefile, common to all Desqview/X configurations.

# This part of the makefile gets inserted after the compiler-specific part
# (xxx-head.mak) and before gs.mak and devs.mak.

# ----------------------------- Generic stuff ----------------------------- #

# Define the platform name.

PLATFORM=dvx_

# Define the syntax for command, object, and executable files.

CMD=.bat
O=-o ./
OBJ=o
XE=.exe
XEAUX=.exe

# Define the current directory prefix and command invocations.

CAT=type
D=\\
EXP=
SHELL=
SH=
SHP=

# Define generic commands.

CP_=cp
RM_=rm -f

# Define the arguments for genconf.

CONFILES=-p -pl &-l%%s -ol ld.tr

# Define the compilation rules and flags.

CCFLAGS=$(GENOPT) $(CFLAGS)

.c.o: $(AK)
	$(CCC) $*.c

CCCF=$(CCC)
CCD=$(CCC)
CCINT=$(CCC)

# Patch a couple of PC-specific things that aren't relevant to DV/X builds,
# but that cause `make' to produce warnings.

BGIDIR=***UNUSED***
PCFBASM=
