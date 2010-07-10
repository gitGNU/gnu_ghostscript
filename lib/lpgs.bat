@echo off
@rem $Id: lpgs.bat,v 1.4 2010/07/10 22:02:37 Arabidopsis Exp $

call gssetgs.bat
%GSC% -sDEVICE#djet500 -P- -dSAFER -dNOPAUSE -sPROGNAME=lpgs -- gslp.ps -fCourier9 %1 %2 %3 %4 %5 %6 %7 %8 %9
