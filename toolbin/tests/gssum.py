#!/usr/bin/env python
# -*- Mode: python -*-

#    Copyright (C) 2001 Artifex Software Inc.
# 
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License version 2
#  as published by the Free Software Foundation.
#
#
#  This software is provided AS-IS with no warranty, either express or
#  implied. That is, this program is distributed in the hope that it will 
#  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  General Public License for more details
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  59 Temple Place, Suite 330, Boston, MA, 02111-1307.
# 
# For more information about licensing, please refer to
# http://www.ghostscript.com/licensing/. For information on
# commercial licensing, go to http://www.artifex.com/licensing/ or
# contact Artifex Software, Inc., 101 Lucas Valley Road #110,
# San Rafael, CA  94903, U.S.A., +1(415)492-9861.

# $Id: gssum.py,v 1.2 2005/04/18 12:06:13 Arabidopsis Exp $

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
