@echo off
@rem $Id: gsdj500.bat,v 1.1 2004/01/14 16:59:47 atai Exp $

call gssetgs.bat
%GSC% -q -sDEVICE#djet500 -r300 -dNOPAUSE -sPROGNAME=gsdj500 -- gslp.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
