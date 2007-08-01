#  Copyright (C) 2001-2006 artofcode LLC.
#  All Rights Reserved.
#
#  This file is part of GNU ghostscript
#
#  GNU ghostscript is free software; you can redistribute it and/or
#  modify it under the terms of the version 2 of the GNU General
#  Public License as published by the Free Software Foundation.
#
#  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
#  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along with
#  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
#  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# $Id: dvx-head.mak,v 1.6 2007/08/01 14:25:43 jemarch Exp $
# Partial makefile, common to all Desqview/X configurations.

# This part of the makefile gets inserted after the compiler-specific part
# (xxx-head.mak) and before gs.mak, devs.mak, and contrib.mak.

# ----------------------------- Generic stuff ----------------------------- #

# Define the platform name.

PLATFORM=dvx_

# Define the syntax for command, object, and executable files.

# Work around the fact that some `make' programs drop trailing spaces
# or interpret == as a special definition operator.
NULL=

CMD=.bat
D_=-D
_D_=$(NULL)=
_D=
I_=-I
II=-I
_I=
NO_OP=@:
O_=-o $(NULL)
OBJ=o
Q=
XE=.exe
XEAUX=.exe

# Define the current directory prefix and command invocations.

CAT=type
D=\\
EXP=
SHELL=
SH=

# Define generic commands.

CP_=cp
RM_=rm -f

# Define the arguments for genconf.

CONFILES=-p -pl &-l%%s
CONFLDTR=-ol

# Define the compilation rules and flags.

CC_D=$(CC_)
CC_INT=$(CC_)

# Patch a couple of PC-specific things that aren't relevant to DV/X builds,
# but that cause `make' to produce warnings.

PCFBASM=
