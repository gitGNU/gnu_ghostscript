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

# msvc32.mak
# makefile for 32-bit Microsoft Visual C++, Windows NT or Windows 95 platform.
#
# Optimization /O2 seems OK with MSVC++ 4.1 & 5.0.
# Created 1997-01-24 by Russell Lang from MSVC++ 2.0 makefile.
# Enhanced 97-05-15 by JD
# Common code factored out 1997-05-22 by L. Peter Deutsch.

# ------------------------------- Options ------------------------------- #

###### This section is the only part of the file you should need to edit.

# ------ Generic options ------ #

# Define the directory that will hold documentation at runtime.

GS_DOCDIR=c:/gs

# Define the default directory/ies for the runtime initialization and
# font files.  Separate multiple directories with ';'.
# Use / to indicate directories, not \.
# MSVC will not allow \'s here because it sees '\;' CPP-style as an
# illegal escape.

GS_LIB_DEFAULT=.;c:/gs/lib;c:/gs/fonts

# Define whether or not searching for initialization files should always
# look in the current directory first.  This leads to well-known security
# and confusion problems, but users insist on it.
# NOTE: this also affects searching for files named on the command line:
# see the "File searching" section of use.txt for full details.
# Because of this, setting SEARCH_HERE_FIRST to 0 is not recommended.

SEARCH_HERE_FIRST=1

# Define the name of the interpreter initialization file.
# (There is no reason to change this.)

GS_INIT=gs_init.ps

# Choose generic configuration options.

# Setting DEBUG=1 includes debugging features (-Z switch) in the code.
# Code runs substantially slower even if no debugging switches are set,
# and also takes about another 25K of memory.

DEBUG=0

# Setting TDEBUG=1 includes symbol table information for the debugger,
# and also enables stack checking.  Code is substantially slower and larger.

TDEBUG=0

# Setting NOPRIVATE=1 makes private (static) procedures and variables public,
# so they are visible to the debugger and profiler.
# No execution time or space penalty, just larger .OBJ and .EXE files.

NOPRIVATE=0

# Define the name of the executable file.

GS=gswin32
GSCONSOLE=gswin32c
GSDLL=gsdll32

# To build two small executables and a large DLL use MAKEDLL=1
# To build two large executables use MAKEDLL=0

MAKEDLL=1

# Define the directory where the IJG JPEG library sources are stored,
# and the major version of the library that is stored there.
# You may need to change this if the IJG library version changes.
# See jpeg.mak for more information.

JSRCDIR=jpeg-6a
JVERSION=6

# Define the directory where the PNG library sources are stored,
# and the version of the library that is stored there.
# You may need to change this if the libpng version changes.
# See libpng.mak for more information.

PSRCDIR=libpng
PVERSION=96

# Define the directory where the zlib sources are stored.
# See zlib.mak for more information.

ZSRCDIR=zlib

# Define the configuration ID.  Read gs.mak carefully before changing this.

CONFIG=

# Define any other compilation flags.

CFLAGS=

# ------ Platform-specific options ------ #

# Define which major version of MSVC is being used (currently, 4 & 5 supported)

MSVC_VERSION = 5

# Define the drive, directory, and compiler name for the Microsoft C files.
# COMPDIR contains the compiler and linker (normally \msdev\bin).
# INCDIR contains the include files (normally \msdev\include).
# LIBDIR contains the library files (normally \msdev\lib).
# COMP is the full C compiler path name (normally \msdev\bin\cl).
# COMPCPP is the full C++ compiler path name (normally \msdev\bin\cl).
# COMPAUX is the compiler name for DOS utilities (normally \msdev\bin\cl).
# RCOMP is the resource compiler name (normallly \msdev\bin\rc).
# LINK is the full linker path name (normally \msdev\bin\link).
# Note that when INCDIR and LIBDIR are used, they always get a '\' appended,
#   so if you want to use the current directory, use an explicit '.'.

!if $(MSVC_VERSION) == 4
DEVSTUDIO=c:\msdev
COMPBASE=$(DEVSTUDIO)
SHAREDBASE=$(DEVSTUDIO)
!else
DEVSTUDIO=c:\devstudio
COMPBASE=$(DEVSTUDIO)\VC
SHAREDBASE=$(DEVSTUDIO)\SharedIDE
!endif
COMPDIR=$(COMPBASE)\bin
LINKDIR=$(COMPBASE)\bin
RCDIR=$(SHAREDBASE)\bin
INCDIR=$(COMPBASE)\include
LIBDIR=$(COMPBASE)\lib
COMP=$(COMPDIR)\cl
COMPCPP=$(COMP)
COMPAUX=$(COMPDIR)\cl
RCOMP=$(RCDIR)\rc
LINK=$(LINKDIR)\link

# Define the processor architecture. (i386, ppc, alpha)

CPU_FAMILY=i386
#CPU_FAMILY=ppc
#CPU_FAMILY=alpha  # not supported yet - we need someone to tweak

# Define the processor (CPU) type. Allowable values depend on the family:
#   i386: 386, 486, 586
#   ppc: 601, 604, 620
#   alpha: not currently used.

CPU_TYPE=486
#CPU_TYPE=601

!if "$(CPU_FAMILY)"=="i386"

# Intel(-compatible) processors are the only ones for which the CPU type
# doesn't indicate whether a math coprocessor is present.
# For Intel processors only, define the math coprocessor (FPU) type.
# Options are -1 (optimize for no FPU), 0 (optimize for FPU present,
# but do not require a FPU), 87, 287, or 387.
# If you have a 486 or Pentium CPU, you should normally set FPU_TYPE to 387,
# since most of these CPUs include the equivalent of an 80387 on-chip;
# however, the 486SX and the Cyrix 486SLC do not have an on-chip FPU, so if
# you have one of these CPUs and no external FPU, set FPU_TYPE to -1 or 0.
# An xx87 option means that the executable will run only if a FPU
# of that type (or higher) is available: this is NOT currently checked
# at runtime.

FPU_TYPE=0

!endif

# ------ Devices and features ------ #

# Choose the language feature(s) to include.  See gs.mak for details.

FEATURE_DEVS=level2.dev pdf.dev ttfont.dev

# Choose whether to compile the .ps initialization files into the executable.
# See gs.mak for details.

COMPILE_INITS=0

# Choose whether to store band lists on files or in memory.
# The choices are 'file' or 'memory'.

BAND_LIST_STORAGE=file

# Choose which compression method to use when storing band lists in memory.
# The choices are 'lzw' or 'zlib'.  lzw is not recommended, because the
# LZW-compatible code in Ghostscript doesn't actually compress its input.

BAND_LIST_COMPRESSOR=zlib

# Choose the implementation of file I/O: 'stdio', 'fd', or 'both'.
# See gs.mak and sfxfd.c for more details.

FILE_IMPLEMENTATION=stdio

# Choose the device(s) to include.  See devs.mak for details.

DEVICE_DEVS=mswindll.dev mswinprn.dev mswinpr2.dev
DEVICE_DEVS2=epson.dev eps9high.dev eps9mid.dev epsonc.dev ibmpro.dev
DEVICE_DEVS3=deskjet.dev djet500.dev laserjet.dev ljetplus.dev ljet2p.dev ljet3.dev ljet4.dev
DEVICE_DEVS4=cdeskjet.dev cdjcolor.dev cdjmono.dev cdj550.dev pj.dev pjxl.dev pjxl300.dev
DEVICE_DEVS5=djet500c.dev declj250.dev lj250.dev jetp3852.dev r4081.dev lbp8.dev uniprint.dev
DEVICE_DEVS6=st800.dev stcolor.dev bj10e.dev bj200.dev m8510.dev necp6.dev bjc600.dev bjc800.dev
DEVICE_DEVS7=t4693d2.dev t4693d4.dev t4693d8.dev tek4696.dev
DEVICE_DEVS8=pcxmono.dev pcxgray.dev pcx16.dev pcx256.dev pcx24b.dev pcxcmyk.dev
DEVICE_DEVS9=pbm.dev pbmraw.dev pgm.dev pgmraw.dev pgnm.dev pgnmraw.dev pnm.dev pnmraw.dev ppm.dev ppmraw.dev
DEVICE_DEVS10=tiffcrle.dev tiffg3.dev tiffg32d.dev tiffg4.dev tifflzw.dev tiffpack.dev
DEVICE_DEVS11=bmpmono.dev bmp16.dev bmp256.dev bmp16m.dev tiff12nc.dev tiff24nc.dev
DEVICE_DEVS12=psmono.dev bit.dev bitrgb.dev bitcmyk.dev
DEVICE_DEVS13=pngmono.dev pnggray.dev png16.dev png256.dev png16m.dev
DEVICE_DEVS14=jpeg.dev jpeggray.dev
DEVICE_DEVS15=pdfwrite.dev pswrite.dev epswrite.dev pxlmono.dev pxlcolor.dev

# ---------------------------- End of options ---------------------------- #

# Derive values for FPU_TYPE for non-Intel processors.

!if "$(CPU_FAMILY)"=="ppc"
!if $(CPU_TYPE)>601
FPU_TYPE=2
!else
FPU_TYPE=1
!endif
!endif

!if "$(CPU_FAMILY)"=="alpha"
# *** alpha *** This needs fixing
FPU_TYPE=1
!endif

# Define the name of the makefile -- used in dependencies.

MAKEFILE=msvc32.mak msvccom.mak winlib.mak winint.mak

# Define the files to be removed by `make clean'.
# nmake expands macros when encountered, not when used,
# so this must precede the !include statements.

BEGINFILES2=gsdll32.exp gsdll32.ilk gsdll32.pdb gsdll32.lib\
   gswin32.exp gswin32.ilk gswin32.pdb gswin32.lib\
   gswin32c.exp gswin32c.ilk gswin32c.pdb gswin32c.lib


!include msvccom.mak
!include winint.mak

# ----------------------------- Main program ------------------------------ #

!if $(MAKEDLL)
# The graphical small EXE loader
$(GS_XE): $(GSDLL).dll  $(DWOBJ) $(GSCONSOLE).exe
	echo /SUBSYSTEM:WINDOWS > gswin32.rsp
	echo /DEF:dwmain32.def /OUT:$(GS_XE) >> gswin32.rsp
        $(LINK) $(LCT) @gswin32.rsp $(DWOBJ) @$(LIBCTR) $(GS).res
	-del gswin32.rsp

# The console mode small EXE loader
$(GSCONSOLE).exe: $(OBJC) $(GS).res dw32c.def
	echo /SUBSYSTEM:CONSOLE > gswin32.rsp
	echo  /DEF:dw32c.def /OUT:$(GSCONSOLE).exe >> gswin32.rsp
	$(LINK_SETUP)
        $(LINK) $(LCT) @gswin32.rsp $(OBJC) @$(LIBCTR) $(GS).res
	-del gswin32.rsp

# The big DLL
$(GSDLL).dll: $(GS_ALL) $(DEVS_ALL) gsdll.$(OBJ) $(GSDLL).res
	echo /DLL /DEF:gsdll32.def /OUT:$(GSDLL).dll > gswin32.rsp
	$(LINK_SETUP)
        $(LINK) $(LCT) @gswin32.rsp gsdll @$(ld_tr) $(INTASM) @lib.tr @$(LIBCTR) $(GSDLL).res
	-del gswin32.rsp

!else
# The big graphical EXE
$(GS_XE):   $(GSCONSOLE).exe $(GS_ALL) $(DEVS_ALL) gsdll.$(OBJ) $(DWOBJNO) $(GS).res dwmain32.def
	copy $(ld_tr) gswin32.tr
	echo dwnodll.obj >> gswin32.tr
	echo dwimg.obj >> gswin32.tr
	echo dwmain.obj >> gswin32.tr
	echo dwtext.obj >> gswin32.tr
	echo /DEF:dwmain32.def /OUT:$(GS_XE) > gswin32.rsp
	$(LINK_SETUP)
        $(LINK) $(LCT) @gswin32.rsp gsdll @gswin32.tr @$(LIBCTR) $(INTASM) @lib.tr $(GSDLL).res
	-del gswin32.tr
	-del gswin32.rsp

# The big console mode EXE
$(GSCONSOLE).exe:  $(GS_ALL) $(DEVS_ALL) gsdll.$(OBJ) $(OBJCNO) $(GS).res dw32c.def
	copy $(ld_tr) gswin32c.tr
	echo dwnodllc.obj >> gswin32c.tr
	echo dwmainc.obj >> gswin32c.tr
	echo  /SUBSYSTEM:CONSOLE > gswin32.rsp
	echo  /DEF:dw32c.def /OUT:$(GSCONSOLE).exe  >> gswin32.rsp
	$(LINK_SETUP)
        $(LINK) $(LCT) @gswin32.rsp gsdll @gswin32c.tr @$(LIBCTR) $(INTASM) @lib.tr $(GS).res
	-del gswin32.rsp
	-del gswin32c.tr
!endif

# end of makefile
