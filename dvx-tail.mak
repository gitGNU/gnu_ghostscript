#    Copyright (C) 1994, 1995, 1997 Aladdin Enterprises.  All rights reserved.
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

# This is the last part of the makefile for Desqview/X configurations.
# Since Unix make doesn't have an 'include' facility, we concatenate
# the various parts of the makefile together by brute force (in tar_cat).

# The following prevents GNU make from constructing argument lists that
# include all environment variables, which can easily be longer than
# brain-damaged system V allows.

.NOEXPORT:

# -------------------------------- Library -------------------------------- #

## The Desqview/X platform

dvx__=gp_nofb.$(OBJ) gp_dvx.$(OBJ) gp_unifs.$(OBJ) gp_dosfs.$(OBJ)
dvx_.dev: $(dvx__)
	$(SETMOD) dvx_ $(dvx__)

gp_dvx.$(OBJ): gp_dvx.c $(AK) $(string__h) $(gx_h) $(gsexit_h) $(gp_h) \
  $(time__h) $(dos__h)
	$(CCC) -D__DVX__ gp_dvx.c

# -------------------------- Auxiliary programs --------------------------- #

$(ANSI2KNR_XE): ansi2knr.c $(stdio__h) $(string__h) $(malloc__h)
	$(CC) -o ansi2knr $(CFLAGS) ansi2knr.c

$(ECHOGS_XE): echogs.c
	$(CC) -o echogs $(CFLAGS) echogs.c
	strip echogs
	coff2exe echogs
	del echogs

$(GENARCH_XE): genarch.c $(stdpre_h)
	$(CC) -o genarch genarch.c
	strip genarch
	coff2exe genarch
	del genarch

$(GENCONF_XE): genconf.c $(stdpre_h)
	$(CC) -o genconf genconf.c
	strip genconf
	coff2exe genconf
	del genconf

$(GENINIT_XE): geninit.c $(stdio__h) $(string__h)
	$(CC) -o geninit geninit.c
	strip geninit
	coff2exe geninit
	del geninit

# Construct gconfig_.h to reflect the environment.
INCLUDE=/djgpp/include
gconfig_.h: dvx-tail.mak $(ECHOGS_XE)
	echogs -w gconfig_.h -x 2f2a -s This file was generated automatically. -s -x 2a2f
	echogs -a gconfig_.h -x 23 define HAVE_SYS_TIME_H
	echogs -a gconfig_.h -x 23 define HAVE_DIRENT_H

# ----------------------------- Main program ------------------------------ #

BEGINFILES=
CCBEGIN=$(CCC) *.c

# Interpreter main program

$(GS_XE): ld.tr gs.$(OBJ) $(INT_ALL) $(LIB_ALL) $(DEVS_ALL)
	$(CP_) ld.tr _temp_
	echo $(EXTRALIBS) -lm >>_temp_
	$(CC) $(LDFLAGS) $(XLIBDIRS) -o $(GS) gs.$(OBJ) @_temp_
	strip $(GS)
	coff2exe $(GS)  
	del $(GS)  
