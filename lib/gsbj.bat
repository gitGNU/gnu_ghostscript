@echo off
@rem $Id: gsbj.bat,v 1.2 2004/02/14 22:20:04 atai Exp $

call gssetgs.bat
%GSC% -q -sDEVICE=bj10e -r180 -dNOPAUSE -sPROGNAME=gsbj -- gslp.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
