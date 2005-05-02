#!/bin/sh
# hack to restart using tclsh \
exec tclsh "$0" "$@"

#    Copyright (C) 2000 Aladdin Enterprises.  All rights reserved.
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

# $Id: errlist.tcl,v 1.3 2005/05/02 00:03:35 Arabidopsis Exp $

# Usage:
#	errlist < compiler-output-log > interleaved-listing

set inname ""
while {[gets stdin line] >= 0} {
    if {![regexp {^([./0-9a-zA-Z_]+):([0-9]+):} $line skip fname lno]} {continue}
    if {$fname != $inname} {
	if {$inname != ""} {close $infile}
	set infile [open $fname]
	set inname $fname
	set inlno 1
    }
    puts $line
    while {$inlno < $lno} {
	gets $infile
	incr inlno
    }
    while {$inlno <= $lno} {
	if {[gets $infile inline] >= 0} {
	    puts $inline
	}
	incr inlno
    }
    puts ""
}
if {$inname != ""} {
    close $infile
}
