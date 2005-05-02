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
 
# $Id: rasterdb.py,v 1.3 2005/05/02 00:03:35 Arabidopsis Exp $
 
# rasterdb.py
#
# methods to put and retrieve files to and from the raster database

import os, gzip
from stat import *
import gsconf

def exists(file, dbdir=gsconf.rasterdbdir):
    x = 0
    try:
        mode = os.stat(dbdir + file + '.gz')[ST_MODE]
        if S_ISREG(mode):
            x = 1
    except:
        pass
    
    return x

def get_file(file, dbdir=gsconf.rasterdbdir, output=None):
    if exists(file, dbdir):
        if output:
            ofile = output
        else:
            ofile = file
        zf = gzip.open(dbdir + file + '.gz')
        f = open(ofile, 'w')
        data = zf.read(1024)
        while data:
            f.write(data)
            data = zf.read(1024)
        zf.close()
        f.close()

def put_file(file, dbdir=gsconf.rasterdbdir):
    mode = os.stat(file)[ST_MODE]
    if S_ISREG(mode):
        f = open(file)
        zf = gzip.open(dbdir + file + '.gz', 'w')
        data = f.read(1024)
        while data:
            zf.write(data)
            data = f.read(1024)
        f.close()
        zf.close()
                       
