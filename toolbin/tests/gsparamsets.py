#!/usr/bin/env python
# -*- Mode: python -*-

#    Copyright (C) 2001 Artifex Software Inc.
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

# $Id: gsparamsets.py,v 1.3 2005/05/02 00:03:35 Arabidopsis Exp $

# gsparamsets.py
#
# Parameter sets for regression testing with gs

class _GSParamSet:

    def __init__(self, device, resolution, banding):
        self.device = device
        self.resolution = resolution
        self.banding = banding

testparamsets = [

    # mono
    _GSParamSet('pbmraw', 72, 0),
    _GSParamSet('pbmraw', 72, 1),
    _GSParamSet('pbmraw', 300, 0),
    _GSParamSet('pbmraw', 300, 1),
    #_GSParamSet('pbmraw', 600, 0),
    #_GSParamSet('pbmraw', 600, 1),

    # grayscale
    _GSParamSet('pgmraw', 72, 0),
    _GSParamSet('pgmraw', 72, 1),
    _GSParamSet('pgmraw', 300, 0),
    _GSParamSet('pgmraw', 300, 1),
    #_GSParamSet('pgmraw', 600, 0),
    #_GSParamSet('pgmraw', 600, 1),

    # color
    _GSParamSet('ppmraw', 72, 0),
    _GSParamSet('ppmraw', 72, 1),
    _GSParamSet('ppmraw', 300, 0),
    _GSParamSet('ppmraw', 300, 1),
    #_GSParamSet('ppmraw', 600, 0),
    #_GSParamSet('ppmraw', 600, 1),

    # 1-bit CMYK
    _GSParamSet('pkmraw', 72, 0),
    _GSParamSet('pkmraw', 72, 1),
    _GSParamSet('pkmraw', 300, 0),
    _GSParamSet('pkmraw', 300, 1),
    #_GSParamSet('pkmraw', 600, 0),
    #_GSParamSet('pkmraw', 600, 1)

]

pdftestparamsets = [
    # color
    _GSParamSet('ppmraw', 72, 0),
    _GSParamSet('ppmraw', 300, 0),
    
    # 1-bit CMYK
    _GSParamSet('pkmraw', 300, 0)
]
