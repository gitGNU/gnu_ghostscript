@echo off
@rem $Id: lpgs.bat,v 1.2 2004/02/14 22:20:04 atai Exp $

call gssetgs.bat
%GSC% -sDEVICE#djet500 -dNOPAUSE -sPROGNAME=lpgs -- gslp.ps -fCourier9 %1 %2 %3 %4 %5 %6 %7 %8 %9
