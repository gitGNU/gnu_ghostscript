#    Copyright (C) 1995 Aladdin Enterprises.  All rights reserved.
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

# wctail.mak
# Last part of Watcom C/C++ makefile common to MS-DOS and MS Windows.

# Define the name of this makefile.
WCTAIL_MAK=wctail.mak

# Include the generic makefiles, except for devs.mak and int.mak.
!include version.mak
!include gs.mak
!include lib.mak
!include jpeg.mak
!include libpng.mak
!include zlib.mak

# -------------------------- Auxiliary programs --------------------------- #

$(ECHOGS_XE): echogs.$(OBJ)
	echo OPTION STUB=$(STUB) >_temp_.tr
	echo $LIBPATHS >>_temp_.tr
	$(LINK) @_temp_.tr FILE echogs

echogs.$(OBJ): echogs.c
	$(CCAUX) echogs.c

$(GENARCH_XE): genarch.$(OBJ)
	echo $LIBPATHS >_temp_.tr
	$(LINK) @_temp_.tr FILE genarch

genarch.$(OBJ): genarch.c $(stdpre_h)
	$(CCAUX) genarch.c

$(GENCONF_XE): genconf.$(OBJ)
	echo OPTION STUB=$(STUB) >_temp_.tr
	echo OPTION STACK=8k >>_temp_.tr
	echo $LIBPATHS >>_temp_.tr
	$(LINK) @_temp_.tr FILE genconf

genconf.$(OBJ): genconf.c $(stdpre_h)
	$(CCAUX) genconf.c

$(GENINIT_XE): geninit.$(OBJ)
	echo OPTION STUB=$(STUB) >_temp_.tr
	echo OPTION STACK=8k >>_temp_.tr
	echo $LIBPATHS >>_temp_.tr
	$(LINK) @_temp_.tr FILE geninit

geninit.$(OBJ): geninit.c $(stdio__h) $(string__h)
	$(CCAUX) geninit.c

# No special gconfig_.h is needed.
# Watcom `make' supports output redirection.
gconfig_.h: $(WCTAIL_MAK)
	echo /* This file deliberately left blank. */ >gconfig_.h

gconfigv.h: $(WCTAIL_MAK) $(MAKEFILE) $(ECHOGS_XE)
	$(EXP)echogs -w gconfigv.h -x 23 define USE_ASM -x 2028 -q $(USE_ASM)-0 -x 29
	$(EXP)echogs -a gconfigv.h -x 23 define USE_FPU -x 2028 -q $(FPU_TYPE)-0 -x 29
	$(EXP)echogs -a gconfigv.h -x 23 define EXTEND_NAMES 0$(EXTEND_NAMES)
