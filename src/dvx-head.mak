#    Copyright (C) 1994, 1996, 1997, 1998, 1999 artofcode LLC.  All rights reserved.
# 
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
# Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA, 02111-1307.


# $Id: dvx-head.mak,v 1.1 2004/01/14 16:59:47 atai Exp $
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
