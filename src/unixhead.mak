#    Copyright (C) 1990, 1993, 1996, 1997, 1999 artofcode LLC.  All rights reserved.
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


# $Id: unixhead.mak,v 1.1 2004/01/14 16:59:53 atai Exp $
# Partial makefile common to all Unix configurations.

# This part of the makefile gets inserted after the compiler-specific part
# (xxx-head.mak) and before gs.mak, devs.mak, and contrib.mak.

# ----------------------------- Generic stuff ----------------------------- #

# Define the platform name.  For a "stock" System V platform,
# use sysv_ instead of unix_.

PLATFORM=unix_

# Define the syntax for command, object, and executable files.

# Work around the fact that some `make' programs drop trailing spaces
# or interpret == as a special definition operator.
NULL=

CMD=
C_=-c
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
XE=
XEAUX=

# Define the current directory prefix and command invocations.

CAT=cat
D=/
EXP=
SHELL=/bin/sh
SH=$(SHELL)

# Define generic commands.

CP_=cp
RM_=rm -f
RMN_=rm -f

# Define the arguments for genconf.

CONFILES=-p "%s&s&&" -pl "&-l%s&s&&" -pL "&-L%s&s&&"
CONFLDTR=-ol

# Define the compilation rules and flags.

CC_D=$(CC_)
CC_INT=$(CC_)

BEGINFILES=

# Patch a couple of PC-specific things that aren't relevant to Unix builds,
# but that cause `make' to produce warnings.

PCFBASM=

# Define the default build rule, so the object directories get created
# automatically.

std: STDDIRS default
	$(NO_OP)
