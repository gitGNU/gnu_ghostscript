#    Copyright (C) 1997-2004 artofcode LLC. All rights reserved.
# 
# This file is part of GNU ghostscript
#
# GNU ghostscript is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2, or (at your option) any later version.
#
# This software is provided AS-IS with no warranty, either express or
# implied. That is, this program is distributed in the hope that it will 
# be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA, 02110-1301.
# 
# For more information about licensing, please refer to
# http://www.ghostscript.com/licensing/. For information on
# commercial licensing, go to http://www.artifex.com/licensing/ or
# contact Artifex Software, Inc., 101 Lucas Valley Road #110,
# San Rafael, CA  94903, U.S.A., +1(415)492-9861.

# $Id: version.mak,v 1.4 2005/05/02 00:03:35 Arabidopsis Exp $
# Makefile fragment containing the current revision identification.

# Major and minor version numbers.
# MINOR0 is different from MINOR only if MINOR is a single digit.
GS_VERSION_MAJOR=8
GS_VERSION_MINOR=15
GS_VERSION_MINOR0=15
# Revision date: year x 10000 + month x 100 + day.
GS_REVISIONDATE=20040922
# Derived values
GS_VERSION=$(GS_VERSION_MAJOR)$(GS_VERSION_MINOR0)
GS_DOT_VERSION=$(GS_VERSION_MAJOR).$(GS_VERSION_MINOR0)
GS_REVISION=$(GS_VERSION)
