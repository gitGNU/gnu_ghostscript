#!/usr/bin/tclsh
# Copyright (C) 1997, 1998 Aladdin Enterprises, Menlo Park, CA.
# All rights reserved.

# makedist.tcl

# This file does nearly all the work in making a GNU- or Aladdin-licensed
# DGS distribution, or a GNU-licensed GS distribution, from an Aladdin
# Ghostscript distribution.  Usage:
#	makedist (gs|dgs) [--aladdin] <fromdir>
# creates /tmp/[d]gsN.NN.tar.gz, using the current directory as scratch.
#	
# The actual steps involved in making a distribution are:
#
#	- Unpack the Aladdin distribution (including the GNU files if
#	appropriate) into some directory A (e.g., /gs/master/temp).
#
#	- Pick a scratch directory B (e.g., /gs/master/staging).
#		rm -f B/*
#		cd B
#		makedist ... A
#
#	- FTP /tmp/gsN.NN.tar.gz to an appropriate server.
#
#	- rm -f A/* B/* /tmp/gs*.tar.gz
#
# This involves the following:
#	+ If GNU:
#		+ Change the copyright/license notices
#		+ Move COPYLEFT to COPYING.
#		+ Change the mention of PUBLIC in gs_init.ps to COPYLEFT
#	+ Change the default product name in gscdef.c.
#	+ Change the release date information in whichever of the following
#	exist: gs.1, version.mak, gs-vms.hlp, NEWS, gscdef.c, gconf.c.
#	+ (Do special things for DGS if necessary: see below.)
#	+ Run tar_cat if necessary.
#	+ Make the actual archive.
#
# For DGS distributions, the following additional steps are needed:
#	+ Delete the following from the makefiles:
#		+ PDF, LanguageLevel 3, and page device sections of int.mak
#		and lib.mak.
#		+ BAND_LIST_* definitions from *.mak.
#		+ DEVICE_DEVS* definitions from *.mak, except x11 and
#		MS Windows devices.
#		+ PDF, LL3, and other non-standard FEATUREs.
#		+ Banding section of lib.mak.
#		+ All gdev* definitions from devs.mak, except x11 and
#		MS Windows devices.
#		+ All utilities.
#		+ Installation of documentation and scripts for deleted
#		features.
#	+ Delete the following files:
#		+ All files referenced in the PDF, LL3, page device,
#		banding, and non-standard sections above.
#		+ Drivers other than x11 and MS Windows.
#		+ .ppd and .upp files.
#		+ Documentation for removed features.

# ---------------- Parameters ---------------- #

set COPYRITE /gs/master/copyrite
set NOTICE /home/lamp/artifex/contract/gnu.not
set SCRIPT makedist.tcl
set TMP _.tmp

# Define the formats for the output file name.
# Parameters are major & minor version #.
set GSNAME_FORMAT "ghostscript-%s.%s"
set GSDIR_FORMAT "gs%s.%s"
set DGSNAME_FORMAT "dgs-%s.%s"
set DGSDIR_FORMAT "dgs%s.%s"

# Parameters set from the command line:
#set FROMDIR <dir>
#set GNU <0|1>
#set DGS <0|1>

# ---------------- Utilities ---------------- #

# Process a file line-by-line by copying it to a temporary file first.
proc for_lines {linevar fname outvar body} {
    global TMP
    upvar $linevar line $outvar out

    exec cp -p $fname $TMP
    set in [open $TMP]
    set out [open $fname w]
    while {[gets $in line] >= 0} {
	uplevel $body
    }
    close $out
    close $in
}

# Test whether a line in a makefile defines a header or a code file.
# If so, set defvar to the .h or .c file name and return 1 or 2,
# otherwise return 0;
proc defines {defvar l} {
    upvar $defvar def
    if {[regexp {^([a-z0-9]+)_h=} $l skip base]} {
	set def $base.h
	return 1
    }
    if {[regexp {: (\$\([A-Za-z0-9]+\)|)([a-z0-9]+\.c) } $l skip skip2 tail]} {
	set def $tail
	return 2
    }
    return 0
}

# Copy (a) file(s) to the current directory, optionally changing the notice(s).
proc copy_here {files {print 0}} {
    if {[llength $files] > 0} {
	global COPYRITE GNU NOTICE FILES

	if {$GNU} {
	    eval exec $COPYRITE -n $NOTICE -w $files
	    # copyrite doesn't preserve access attributes.
	    # Fix this now (awkwardly).
	    foreach f $files {
		set attrs [exec ls -l $f]
		set mask 0444
		for {set i 1} {$i < 10} {incr i} {
		    if {[string index $attrs $i] != "-"} {
			set mask [expr {$mask | (01000 >> $i)}]
		    }
		}
		exec chmod [format %03o $mask] [file tail $f]
	    }
	} else {
	    eval exec cp -p $files .
	}
	foreach f $files {
	    unset FILES($f)
	    if {$print} {puts "Copied $f"}
	}
    }
}

foreach m {Jan January Feb February Mar March Apr April May Jun June Jul July Aug August Sep September Oct October Nov November Dec December} {
    set MONTHNAME($m) ""
}
# Replace date fields with the current date.
proc subst_date {lvar} {
    global MONTHNAME

    upvar $lvar line
    if {[regexp {^(.*)([0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9])(.*)$} $line skip pre date post]} {
	# yyyymmdd
	set date [exec date +%Y%m%d]
    } elseif {[regexp {^(.*)([0-9]+/[0-9]+/[0-9]+)(.*)$} $line skip pre date post]} {
	# [m]m/[d]d/[yy]yy
	set date [exec date +%m/%d/%Y]
    } elseif {[regexp {^(.*)([0-9]+ ([A-Z][a-z]+) [0-9]+)(.*)$} $line skip pre date month post] && [info exists monthname($month)]} {
	# dd monthname [yy]yy
	set date [exec date +%d %B %Y]
    } else {
	return 0
    }
    set line "$pre$date$post"
    return 1
}

# Skip copying a set of files.
proc skip_files {files {print 1}} {
    global FILES FROMDIR

    foreach f $files {
	set ff $FROMDIR/$f
	if {[info exists FILES($ff)]} {
	    if {$print} {puts "Skipping $ff"}
	    unset FILES($ff)
	}
    }
}

# ---------------- Main program ---------------- #

### Check arguments and environment.
proc usage {} {
    puts stderr {Usage: makedist (gs|dgs) [--aladdin] <fromdir>}
    exit 1
}
proc check_arguments {argv} {
    global FROMDIR GNU DGS

    set args $argv
    switch [lindex $args 0] {
	gs {set DGS 0}
	dgs {set DGS 1}
	default {usage}
    }
    set args [lreplace $args 0 0]
    if {[llength $args] >= 1 && [lindex $args 0] == "--aladdin"} {
	set GNU 0
	set args [lreplace $args 0 0]
    } else {
	set GNU 1
    }
    if {[llength $args] != 1 || ![file isdirectory [lindex $args 0]]} {
	usage
    }
    set FROMDIR [lindex $args 0]
    # Check to make sure that we're working in a clean directory.
    if {[glob -nocomplain *] != ""} {
	puts stderr "\n\n\t****** This directory ([exec pwd])"
	puts stderr "\t****** is not a clean or DGS directory.\n\n"
	exit 1
    }
}

### Acquire the list of files to be copied.
proc acquire_files {} {
    global FILES FROMDIR

    catch {unset FILES}
    set files [glob $FROMDIR/*]
    foreach f $files {
	if {![file isfile $f]} {
	    if {![file isdirectory $f]} {
		puts "Skipping [file type $f] $f"
	    }
	} elseif {[regexp {(~|\.orig|\.o|\.dev)$} $f]} {
	} elseif {![file readable $f]} {
	    puts stderr "****** Unable to read $f."
	} else {
	    set FILES($f) [file tail $f]
	}
    }
    puts "Found [array size FILES] files."
}

### Process files requiring special handling.
proc make_changes {} {
    global FILES GNU FROMDIR DGS VMINOR VMAJOR

    # If this is a GNU re-release of Aladdin Ghostscript, fix up the dates.
    set update [expr $GNU && !$DGS]
    if {$GNU} {
	# Substitute the GNU license for the Aladdin license.
	if {[file exists $FROMDIR/COPYLEFT]} {
	    puts "Copying $FROMDIR/COPYLEFT to COPYING"
	    exec cp -p $FROMDIR/COPYLEFT COPYING
	}
	skip_files {COPYLEFT} 0
	skip_files {COPYING PUBLIC} 1
	# Change the mention of PUBLIC in gs_init.ps to COPYING.
	copy_here $FROMDIR/gs_init.ps 1
	for_lines l gs_init.ps out {
	    regsub PUBLIC $l COPYING l
	    puts $out $l
	}
	set product GNU
    } else {
	set product Aladdin
    }
    append product [lindex {{ Ghostscript} { DGS}} $DGS]
    if {[file exists $FROMDIR/gscdef.c]} {
	# Change the default product name.
	copy_here $FROMDIR/gscdef.c 1
	set found 0
	for_lines l gscdef.c out {
	    if {[regsub {Aladdin Ghostscript} $l $product l]} {set found 1}
 	    if {$update} {subst_date l}
	    puts $out $l
	}
	if {!$found} {
	    puts stderr "****** \"Aladdin Ghostscript\" not found in gscdef.c"
	}
    }
    if {$update} {
	foreach f {gs.1 version.mak gs-vms.hlp NEWS} {
	    if {[file exists $FROMDIR/$f]} {
		copy_here $FROMDIR/$f 1
		set found 0
		for_lines l $f out {
		    if {!$found && [subst_date l]} {set found 1}
		    puts $out $l
		}
	    }
	}
    } else {
	copy_here $FROMDIR/NEWS 1
    }
    # Get the release number from the NEWS file.
    if {[catch {set versions [exec grep ^Version NEWS]}] ||
      ![regexp {^Version ([0-9]+).([0-9]+)(\[[^)]*\)|) \([0-9]+/[0-9]+/[0-9]+\)} $versions skip VMAJOR VMINOR]} {
	puts stderr "****** Unable to find version # in NEWS"
	exit 1
    }
    puts "Version # in NEWS is $VMAJOR.$VMINOR"
    # Don't copy executables or makefile.  Make makefile a link.
    skip_files {ansi2knr echogs genarch genconf gendev makefile}
    if {[file exists $FROMDIR/unix-gcc.mak]} {
	exec ln -s unix-gcc.mak makefile
    }
}

### Copy the makefiles so we can edit them.
proc copy_makefiles {} {
    global FILES FROMDIR

    set mak [glob -nocomplain $FROMDIR/*.mak]
    copy_here $mak
    puts "Copied [llength $mak] makefiles."
}

### Remove PDF, LanguageLevel 3, setpagedevice, banding-related, and other
### non-standard sections of the makefiles, and any files that they reference.
proc delete_sections {} {
    global FILES FROMDIR

    set skippers(lib.mak) {PDF|Level.3|Command.list|setpagedevice|Page.device|Vector.device|Command.list|Double-precision|Functions|zlib}
    set skippers(int.mak) "$skippers(lib.mak)|RasterOp"
    foreach mf {lib.mak int.mak} {
	puts "Deleting sections from $mf."
	set skip 0
	set skipper $skippers($mf)
	for_lines l $mf out {
	    if {[string first {# ======} $l] == 0} {
		set skip [expr [regexp $skipper $l] * 2]
		if {$skip} {
		    puts "Skipping $l"
		}
	    } elseif {$skip != 2 && [string first {# ------} $l] == 0} {
		set skip [regexp $skipper $l]
		if {$skip} {
		    puts "Skipping $l"
		}
	    }
	    if {!$skip} {
		if {[regsub { pagedev(\.dev|)} $l {} l1]} {
		    puts "Deleting pagedev reference:"
		    puts $l
		    set l $l1
		}
		puts $out $l
	    } elseif {[defines def $l]} {
		unset FILES($FROMDIR/$def)
	    }
	}
    }
    foreach f [glob -nocomplain $FROMDIR/pdf_*.ps $FROMDIR/pdf2*] {
	unset FILES($f)
    }
}

### Remove definitions of BAND_LIST_ parameters.
proc delete_band_list {} {
    set mak [split [eval exec grep -l ^BAND_LIST_ [glob *.mak]] "\n"]
    puts "Deleting BAND_LIST_ definitions from [llength $mak] makefiles."
    foreach f $mak {
	for_lines l $f out {
	    if {[regexp {^BAND_LIST} $l]} {
		puts $out "\#****** Banding is not supported."
		puts $out "\#$l"
	    } else {
		puts $out $l
	    }
	}
    }
}

### Remove PDF and LL3 FEATUREs.
proc delete_features {} {
    set mak [split [eval exec grep -l ^FEATURE_DEVS [glob *.mak]] "\n"]
    puts "Deleting FEATUREs from [llength $mak] makefiles."
    foreach f $mak {
	puts "$f:"
	for_lines l $f out {
	    if {[regexp {^(FEATURE_DEVS=)(.*)$} $l skip lhs rhs]} {
		set features {}
		foreach d [split $rhs { }] {
		    switch $d {
			pdf.dev {}
			psl3.dev {}
			default {lappend features $d}
		    }
		}
		set nl "$lhs$features"
		if {$nl != $l} {puts $nl; set l $nl}
	    }
	    puts $out $l
	}
    }
}

### Remove DEVICE_DEVS definitions, except for x11 devices.
proc delete_devices {} {
    set mak [split [eval exec grep -l ^DEVICE_DEVS [glob *.mak]] "\n"]
    puts "Deleting non-display devices from [llength $mak] makefiles."
    foreach f $mak {
	puts "$f:"
	for_lines l $f out {
	    if {![regexp {^#DEVICE_DEVS[0-9]*} $l]} {
		if {[regexp {^(DEVICE_DEVS[0-9]*=)(.*)$} $l skip lhs rhs]} {
		    set devs {}
		    foreach d [split $rhs { }] {
			if {[regexp {^(x11|mswindll)} $d]} {lappend devs $d}
		    }
		    set l "$lhs$devs"
		    if {$l != $lhs} {puts $l}
		}
		puts $out $l
	    }
	}
    }
}

### Remove devices other than X11 devices.
proc delete_devs {} {
    global FILES FROMDIR

    puts "Keeping only display devices:"
    set keep 1
    set scan_first {[a-z$].*:}
    set scan_more {}
    set scan $scan_first
    for_lines l devs.mak out {
	set this $scan
	set scan $scan_first
	if {[string first {--------} $l] > 0} {
	    set keep [regexp -nocase {support|the x(11| windows)|ms.windows(.*)dll} $l]
	}
	if {$keep} {
	    # Keep files mentioned in kept sections.
	    if {[regexp "^${this}(.*)\$" $l skip rhs]} {
		puts $l
		foreach d [split rhs { }] {
		    if {[regexp {\$\(([a-z0-9_]+)\)_h$} $d skip h]} {
			set x($h.h) 1
		    } elseif {[regexp {([a-z0-9_]+\.c)$} $d skip c]} {
			set x($c) 1
		    }
		}
		if {[regexp {\\$} $l]} {
		    set scan $scan_more
		}
	    }
	    puts $out $l
	} elseif {[defines def $l]} {
	    lappend delete $def
	}
    }
    set count 0
    foreach def $delete {
	if {![info exists x$(def)]} {
	    # Ghostscript makefiles sometimes refer to nonexistent files....
	    incr count
	    catch {unset FILES($FROMDIR/$def)}
	}
    }
    puts "Skipped $count device-related files."
    set delete [concat [array names FILES *.upp] [array names FILES *.ppd]]
    puts "Skipping [llength $delete] .ppd and .upp files."
    foreach f $delete {
	unset FILES($f)
    }
}

### Remove utilities, and documentation for deleted features.
proc delete_others {} {
    global FILES FROMDIR

    foreach f [glob $FROMDIR/p*2* $FROMDIR/view*] {
	catch {unset FILES($f)}
    }
    foreach f [glob $FROMDIR/*.ps] {
	if {![regexp {(^|/)gs_} $f]} {
	    catch {unset FILES($f)}
	}
    }
    foreach f {devices.txt unix-lpr.txt} {
	catch {unset FILES($FROMDIR/$f)}
    }
    # Remove deleted files from the installation list.
    puts "Deleting files from installation list:"
    set deleted {}
    set kept 0
    for_lines l unixinst.mak out {
	if {[regexp {^[a-zA-Z].*\\$} $l]} {
	    # This is a list of files to be installed.
	    set keep {}
	    while {[regexp {^([a-zA-Z0-9_.]+) (.*)$} $l skip f l]} {
		if {[info exists FILES($FROMDIR/$f)] || [file exists $f]} {
		    append keep "$f "
		    incr kept
		} else {
		    lappend deleted $f
		}
	    }
	    puts $out "$keep $l"
	} else {
	    puts $out $l
	}
    }
    puts $deleted
    puts "[llength $deleted] files deleted, $kept kept."
}

### Copy the remaining files, changing the copyright/license notices.
proc copy_files {} {
    global FILES SCRIPT argv0

    set files {}
    set skipped 0
    foreach f [array names FILES] {
	if {[file exists [file tail $f]] || [regexp {\.(o|dev)$} $f]} {
	    incr skipped
	} else {
	    lappend files $f
	}
    }
    copy_here $files
    puts "Copied [llength $files] files, skipped $skipped."
    # Copy the script file itself into the output.
    if {[file readable $argv0]} {
	set script $argv0
    } else {
	set script [exec which $argv0]
    }
    exec cp -p $script $SCRIPT
}

### Construct the concatenated makefiles.
proc run_tar_cat {} {
    if {[file exists tar_cat]} {
	exec sh tar_cat
    }
}

### Make the actual archive.
proc make_archive {} {
    global DGS VMAJOR VMINOR

    if {$DGS} {
	global DGSNAME_FORMAT DGSDIR_FORMAT

	set nf $DGSNAME_FORMAT
	set df $DGSDIR_FORMAT
    } else {
	global GSNAME_FORMAT GSDIR_FORMAT

	set nf $GSNAME_FORMAT
	set df $GSDIR_FORMAT
    }
    set fname [format $nf $VMAJOR $VMINOR]
    set dir [format $df $VMAJOR $VMINOR]
    exec sh -c "rm -f /tmp/$dir; ln -s `pwd` /tmp/$dir; cd /tmp; tar cvzf $fname.tar.gz $dir/*; rm -f /tmp/$dir"
    exec ls -l /tmp/$fname.tar.gz >@ stdout
}

### Do the work.
proc doit {argv} {
    global FROMDIR DGS TMP

    check_arguments $argv
    regsub {/+$} $FROMDIR {} FROMDIR
    # Clear the destination directory.
    exec sh -c {rm -f *}
    acquire_files
    make_changes
    if {$DGS} {
	copy_makefiles
	delete_sections
	delete_band_list
	delete_features
	delete_devices
	delete_devs
	delete_others
    }
    copy_files
    run_tar_cat
    exec rm -f $TMP
    make_archive
    puts "Done."
    exit
}
if {!$tcl_interactive} {
    doit $argv
}
