@echo off
@rem $Id: lpr2.bat,v 1.4 2010/07/10 22:02:35 Arabidopsis Exp $

call gssetgs.bat
%GSC% -sDEVICE#djet500 -P- -dSAFER -dNOPAUSE -sPROGNAME=lpr2 -- gslp.ps -2r %1 %2 %3 %4 %5 %6 %7 %8 %9
