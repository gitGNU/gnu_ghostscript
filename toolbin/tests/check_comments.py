#!/usr/bin/env python2.2

#    Copyright (C) 2003 artofcode LLC. All rights reserved.
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

# $Id: check_comments.py,v 1.1 2004/02/14 22:46:29 atai Exp $

# Check for C++ style comments

import os
import re
from glob import glob

import gsconf
from gstestutils import GSTestCase, gsRunTestsMain

class GSCheckForComments(GSTestCase):

    def __init__(self, root, dirName, extensions=['*'], skip=[]):
        self.root = root
        self.dirName = dirName
        self.extensions = extensions
        self.skip = skip
        GSTestCase.__init__(self)

    def shortDescription(self):
        return "All relevant files must not have C++ style comments"\
               " (checking %s)" % (self.dirName,)

    def runTest(self):
        d, extns, skip = self.root + self.dirName, self.extensions, self.skip
        skip = map((lambda o,d=d: d + os.sep + o), skip)
        incorrect = []
        for e in extns:
            for f in glob(d + os.sep + '*.' + e):
                if f in skip or os.path.isdir(f):
                    continue
                fp = open(f, 'r')
                text_code = fp.read()
                fp.close()

                pattern = re.compile("(\")|(/\*)|(\*/)|(//)")
                mi = pattern.finditer(text_code)
                try:
                    startComment = 0
                    inString = 0
                    while 1:
                        m = mi.next()
                        mstr = m.group()
                        if mstr == '"' and not startComment:
                            inString = not inString
                            continue
                        if not inString and mstr == '/*':
                            startComment = 1
                            continue
                        if startComment and mstr == '*/':
                            startComment = 0
                            continue
                        if not inString and not startComment and mstr == '//':
                            incorrect.append(f)
                            break
                except StopIteration:
                    continue
                    
        if incorrect:
            incorrect = ['These %d files have C++ style comments:' % (len(incorrect),)] + incorrect

        self.failIfMessages(incorrect)

## Main stuff

checkDirs = [
    ('src', ['c', 'h'],
     # list of exempt files
     ['dwdll.h',
      'dwimg.h',
      'dwinst.h',
      'dwsetup.h',
      'dwtext.h',
      'dwuninst.h',
      'gdevhpij.c',
      'dmmain.c',
      'gdevmac.c',
      'gdevmacxf.c',
      'gdevphex.c',
      'gdevwdib.c',
      'gp_mac.c',
      'gp_macio.c',
      'gp_msio.c',
      'gxchar.c',
      'macsysstat.h'
     ])
    ]

def addTests(suite, gsroot, **args):
    for dir, extns, skip in checkDirs:
        suite.addTest(GSCheckForComments(gsroot, dir, extns, skip))

if __name__ == "__main__":
    gsRunTestsMain(addTests)
