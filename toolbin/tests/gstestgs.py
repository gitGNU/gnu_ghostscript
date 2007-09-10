#!/usr/bin/env python
# -*- Mode: python -*-

#    Copyright (C) 2001 Artifex Software Inc.
# 
# This file is part of GNU ghostscript
#
# GNU ghostscript is free software; you can redistribute it and/or
# modify it under the terms of the version 2 of the GNU General Public
# License as published by the Free Software Foundation.
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


# $Id: gstestgs.py,v 1.9 2007/09/10 14:08:48 Arabidopsis Exp $

# gstestgs.py
#
# base classes for regression testing

import os, time
import string
import gsconf
from gstestutils import GSTestCase

myself="gstestgs.py"

class Ghostscript:
	def __init__(self):
		self.device = ''
		self.dpi = 72
		self.band = 0
		self.infile = 'input'
		if os.name == 'nt':
			self.nullfile = 'nul'
		else:
			self.nullfile = '/dev/null'
		self.outfile = self.nullfile

		# log file options
		# NOTE: we always append to the log.  if it is desired to start a new
		# log, it is the responsibility of the caller to clear/erase the old one.

		self.log_stdout = self.nullfile
		self.log_stderr = self.nullfile

	def log_message(self,message):
		try:
			log = open(self.log_stdout, "a")
			log.write(message+"\n")
			log.close()
		except:
			pass

	def process(self):
		bandsize = 30000000
		if (self.band): bandsize = 10000
		
		gsroot=self.gsroot
		execpath = gsroot+'bin/gs'

		arguments = ' -sOutputFile=\'%s\' ' % (self.outfile,)

		if gsconf.fontdir:
			FontPath=gsconf.fontdir
		else:
			FontPath = ''
		ResourcePath=gsroot+'lib/'
		IPath = ResourcePath+':'+FontPath
		if IPath:
			arguments+= ' -I' + IPath


		arguments += ' -sDEVICE=%s ' % (self.device,)
		if self.dpi:
			arguments += '-r%d ' % (self.dpi,)

		arguments += ' -dNOPAUSE -dBATCH -K1000000'
		arguments += ' -dMaxBitmap=%d' % (bandsize,)
		arguments += ' -dNOOUTERSAVE -dJOBSERVER -c false 0 startjob pop -f'

		if string.lower(self.infile[-4:]) == ".pdf" or string.lower(self.infile[-3:]) == ".ai":
			arguments += ' -dFirstPage=1 -dLastPage=1 '
			infile = self.infile
		else:
			# for some tests, input from stdin is required - use it all the time
			infile = ' - < '+self.infile

		if self.log_stdout and self.log_stderr:
			capture=' >> %s 2>> %s' % (self.log_stdout, self.log_stderr)
		else:
			capture=''

		fullcommand=execpath+arguments+" "+infile+" "+capture
		
		# before we execute the command which appends to the log
		# we output a message to record the commandline that generates the log entry.

		infilename=os.path.basename(self.infile)
		comment=' '.join((infilename,"to",self.outfile))

		if len(self.log_stdout) > 0 and self.log_stdout != self.nullfile:
			try:
				log = open(self.log_stdout, "a")
				log.write("=== "+comment+"\n")
				log.write(fullcommand+"\n")
				log.write("---\n")
				log.close()
			except:
				pass
		if len(self.log_stderr) > 0 and self.log_stderr != self.nullfile:
			try:
				log = open(self.log_stderr, "a")
				log.write("==="+comment+"\n")
				log.write(fullcommand+"\n")
				log.write("---\n")
				log.close()
			except:
				pass

		if self.__dict__.has_key("verbose") and self.verbose:
			print fullcommand

		gs_return=os.system(fullcommand)

		if gs_return == 0:
			return 1
		else:
			return 0

		
class GhostscriptTestCase(GSTestCase):
	def __init__(self,
		     gsroot='gsroot',
		     dpi=72, band=0, file='test.ps', device='pdfwrite', log_stdout='', log_stderr='', track_daily=0,now=None):

		self.gsroot = gsroot

		self.file = file
		self.device = device
		self.dpi = dpi
		self.band = band
		self.log_stdout = log_stdout
		self.log_stderr = log_stderr
		self.track_daily = track_daily
		self.now = now
		GSTestCase.__init__(self)

class GSCrashTestCase(GhostscriptTestCase):
	def runTest(self):
		gs = Ghostscript()
		gs.gsroot = self.gsroot
		gs.device = self.device
		gs.dpi = self.dpi
		gs.band = self.band
		gs.infile = self.file
		self.assert_(gs.process(), 'ghostscript failed to render file: ' + self.file)
