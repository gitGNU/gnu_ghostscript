#    Copyright (C) 1997 Aladdin Enterprises.  All rights reserved.
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

# Common interpreter makefile section for 32-bit MS Windows.

# This makefile must be acceptable to Microsoft Visual C++, Watcom C++,
# and Borland C++.  For this reason, the only conditional directives
# allowed are !if[n]def, !else, and !endif.


# Include the generic makefile.
!include int.mak

# ----------------------------- Main program ------------------------------ #

CCBEGIN=$(CCC) *.c

ICONS=gsgraph.ico gstext.ico

GS_ALL=$(INT_ALL) $(INTASM)\
  $(LIB_ALL) $(LIBCTR) lib.tr $(ld_tr) $(GSDLL).res $(GSDLL).def $(ICONS)

# Make the icons from their text form.

gsgraph.ico: gsgraph.icx echogs$(XE)
        echogs -wb gsgraph.ico -n -X -r gsgraph.icx

gstext.ico: gstext.icx echogs$(XE)
        echogs -wb gstext.ico -n -X -r gstext.icx

# resources for short EXE loader (no dialogs)
$(GS).res: dwmain.rc dwmain.h $(ICONS)
	$(RCOMP) -i$(INCDIR) -r -fo$(GS).res dwmain.rc

# resources for main program (includes dialogs)
$(GSDLL).res: gsdll32.rc gp_mswin.h $(ICONS)
	$(RCOMP) -i$(INCDIR) -r -fo$(GSDLL).res gsdll32.rc


# Modules for small EXE loader.

DWOBJ=dwdll.obj dwimg.obj dwmain.obj dwtext.obj gscdefs.obj

dwdll.obj: dwdll.cpp $(AK) dwdll.h gsdll.h
	$(CPP) $(COMPILE_FOR_EXE) -c dwdll.cpp

dwimg.obj: dwimg.cpp $(AK) dwmain.h dwdll.h dwtext.h dwimg.h gscdefs.h gsdll.h
	$(CPP) $(COMPILE_FOR_EXE) -c dwimg.cpp

dwmain.obj: dwmain.cpp $(AK) dwdll.h gscdefs.h gsdll.h
	$(CPP) $(COMPILE_FOR_EXE) -c dwmain.cpp

dwtext.obj: dwtext.cpp $(AK) dwtext.h
	$(CPP) $(COMPILE_FOR_EXE) -c dwtext.cpp

# Modules for big EXE

DWOBJNO = dwnodll.obj dwimg.obj dwmain.obj dwtext.obj

dwnodll.obj: dwnodll.cpp $(AK) dwdll.h gsdll.h
	$(CPP) $(COMPILE_FOR_EXE) -c dwnodll.cpp

# Compile gsdll.c, the main program of the DLL.

gsdll.obj: gsdll.c $(AK) gsdll.h $(ghost_h)

# Modules for console mode EXEs

OBJC=dwmainc.obj dwdllc.obj gscdefs.obj
OBJCNO=dwmainc.obj dwnodllc.obj

dwmainc.obj: dwmainc.cpp $(AK) dwmain.h dwdll.h gscdefs.h gsdll.h
	$(CPP) $(COMPILE_FOR_CONSOLE_EXE) -c dwmainc.cpp

dwdllc.obj: dwdll.cpp $(AK) dwdll.h gsdll.h
	$(CPP) $(COMPILE_FOR_CONSOLE_EXE) -c $(CCOBJNAME)dwdllc.obj dwdll.cpp

dwnodllc.obj: dwnodll.cpp $(AK) dwdll.h gsdll.h
	$(CPP) $(COMPILE_FOR_CONSOLE_EXE) -c $(CCOBJNAME)dwnodllc.obj dwnodll.cpp

# end of winint.mak
