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


# $Id: gssum.py,v 1.4 2005/12/13 17:58:03 jemarch Exp $

# gssum.py
#
# this module contains routines for calculating sums and managing
# the sum database
import anydbm
import gsconf
import os, string, md5
from stat import *

def exists(file, dbname=gsconf.testdatadb):
    db = anydbm.open(dbname)
    exists = db.has_key(file)
    db.close()

    return exists

def add_file(file, dbname=gsconf.testdatadb, sum=''):
    db = anydbm.open(dbname, 'w')
    if len(sum) > 0:
        db[file] = sum
    else:
        db[file] = make_sum(file)
    db.close()

def get_sum(file, dbname=gsconf.testdatadb):
    db = anydbm.open(dbname)
    sum = db[file]
    db.close()

    return sum

def make_sum(file):
    try:
	mode = os.stat(file)[ST_MODE]
    except OSError:
	return None
    if S_ISREG(mode):
	sum = md5.new()
	f = open(file, "r")
	data = f.read(1024)
	while data:
		sum.update(data)
		data = f.read(1024)
	f.close()

        return sum.hexdigest()
    
    return None
