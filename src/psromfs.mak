#  Copyright (C) 2001-2006 Artifex Software, Inc.
#  All Rights Reserved.
#
#  This file is part of GNU ghostscript
#
#  GNU ghostscript is free software; you can redistribute it and/or modify it under
#  the terms of the version 2 of the GNU General Public License as published by the Free Software
#  Foundation.
#
#  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
#  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along with
#  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
#  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# $Id: psromfs.mak,v 1.1 2008/05/04 14:34:47 Arabidopsis Exp $
# mkromfs macros for PostScript %rom% when COMPILE_INITS=1

# The following list of files needed by the interpreter is maintained here.
# This changes infrequently, but is a potential point of bitrot, but since
# unix-inst.mak uses this macro, problems should surface when testing installed
# versions.

#	The init files are put in the lib/ directory (gs_init.ps + EXTRA_INIT_FILES)
#	Resource files go into Resource/...

RESOURCE_LIST=ColorSpace$(D) Decoding$(D) Encoding$(D) Font$(D) ProcSet$(D) IdiomSet$(D) CIDFont$(D) CMap$(D)

#	Note: gs_cet.ps is only needed to match Adobe CPSI defaults
PS_ROMFS_ARGS=-c -P $(PSRESDIR)$(D) -d Resource/ $(RESOURCE_LIST) \
   -d lib/ -P $(PSGENDIR)$(D) $(GS_INIT) \
   -P $(PSLIBDIR)$(D) Fontmap cidfmap xlatmap FAPI FCOfontmap-PCLPS2 gs_cet.ps

PS_ROMFS_DEPS=$(PSGENDIR)$(D)$(GS_INIT)
