#!/bin/sh
# hack to restart using tclsh \
exec tclsh "$0" "$@"

#    Copyright (C) 2000 Aladdin Enterprises.  All rights reserved.
# 
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
# Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA, 02111-1307.

# $Id: errlist.tcl,v 1.1 2004/01/14 16:59:53 atai Exp $

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
