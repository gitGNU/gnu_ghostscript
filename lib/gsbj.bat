@echo off
@rem $Id: gsbj.bat,v 1.1 2004/01/14 16:59:47 atai Exp $

call gssetgs.bat
%GSC% -q -sDEVICE=bj10e -r180 -dNOPAUSE -sPROGNAME=gsbj -- gslp.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
