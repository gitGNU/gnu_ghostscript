#!/usr/bin/env python

#    Copyright (C) 2001-2004 Artifex Software Inc.
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


# $Id: gscheck_pdfwrite.py,v 1.5 2006/03/06 11:16:03 Arabidopsis Exp $

#
# gscheck_pdfwrite.py
#
# compares Ghostscript against a baseline made from file->pdf->raster->md5sum.
# this test tries to detect Ghostscript changes that affect the pdfwrite driver.

import os, stat
import calendar, string, time
import gstestutils
import gsconf, gstestgs, gsparamsets, gssum, gsutil


class GSPDFWriteCompareTestCase(gstestgs.GhostscriptTestCase):
    def shortDescription(self):
        file = "%s.pdf.%s.%d.%d" % (self.file[string.rindex(self.file, '/') + 1:], self.device, self.dpi, self.band)
	rasterfilename = gsconf.rasterdbdir + file + ".gz"
	if not os.access(rasterfilename, os.F_OK):
		os.system(gsconf.codedir + "update_pdfbaseline '%s'" %
                          (os.path.basename(self.file),))	
	ct = time.localtime(os.stat(rasterfilename)[stat.ST_MTIME])
	baseline_date = "%s %d, %4d %02d:%02d" % ( calendar.month_abbr[ct[1]], ct[2], ct[0], ct[3], ct[4] )

	if self.band:
	    return "Checking pdfwrite of %s (%s/%ddpi/banded) against baseline set on %s" % (os.path.basename(self.file), self.device, self.dpi, baseline_date)
        else:
	    return "Checking pdfwrite of %s (%s/%ddpi/noband) against baseline set on %s" % (os.path.basename(self.file), self.device, self.dpi, baseline_date)

	
    def runTest(self):
        file1 = '%s.%s.%d.%d.pdf' % (self.file[string.rindex(self.file, '/') + 1:], 'pdf', self.dpi, self.band)
	file2 = '%s.pdf.%s.%d.%d' % (self.file[string.rindex(self.file, '/') + 1:], self.device, self.dpi, self.band)

	gs = gstestgs.Ghostscript()
	gs.command = self.gs
	gs.dpi = self.dpi
	gs.band = self.band
	gs.infile = self.file
	if self.log_stdout:
	    gs.log_stdout = self.log_stdout
	if self.log_stderr:
	    gs.log_stderr = self.log_stderr

	# do file->PDF conversion

	gs.device = 'pdfwrite'
        gs.dpi = None
	gs.outfile = file1
	if not gs.process():
	    self.fail("non-zero exit code trying to create pdf file from " + self.file)

	# do PDF->device (pbmraw, pgmraw, ppmraw, pkmraw)
		
	gs.device = self.device
        gs.dpi = self.dpi
	gs.infile = file1
	gs.outfile = file2
	if not gs.process():
	    self.fail("non-zero exit code trying to"\
		      " rasterize " + file1)

	# compare baseline
		
	sum = gssum.make_sum(file2)
	os.unlink(file1)
	os.unlink(file2)
	
	# add test result to daily database
	if self.track_daily:
	    gssum.add_file(file2, dbname=gsconf.get_dailydb_name(), sum=sum)

	self.assertEqual(sum, gssum.get_sum(file2), "md5sum did not match baseline (" + file2 + ") for file: " + self.file)

# Add the tests defined in this file to a suite

def add_compare_test(suite, f, device, dpi, band, track):
    suite.addTest(GSPDFWriteCompareTestCase(gs=gsconf.comparegs,
					    file=gsconf.comparefiledir + f,
					    device=device, dpi=dpi,
					    band=band, track_daily=track,
					    log_stdout=gsconf.log_stdout,
					    log_stderr=gsconf.log_stderr))

def addTests(suite, gsroot, **args):
    if args.has_key('track'):
        track = args['track']
    else:
        track = 0
    
    # get a list of test files
    comparefiles = os.listdir(gsconf.comparefiledir)

    for f in comparefiles:
        if gsutil.check_extension(f):
	    for params in gsparamsets.pdftestparamsets:
	        add_compare_test(suite, f, params.device,
				 params.resolution,
				 params.banding, track)

if __name__ == "__main__":
    gstestutils.gsRunTestsMain(addTests)
