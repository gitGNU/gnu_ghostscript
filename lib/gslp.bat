@echo off
@rem $Id: gslp.bat,v 1.4 2010/07/10 22:02:36 Arabidopsis Exp $

call gssetgs.bat
%GSC% -q -sDEVICE=epson -r180 -P- -dSAFER -dNOPAUSE -sPROGNAME=gslp -- gslp.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
