@echo off
@rem $Id: gslj.bat,v 1.4 2010/07/10 22:02:38 Arabidopsis Exp $

call gssetgs.bat
%GSC% -q -sDEVICE=laserjet -r300 -P- -dSAFER -dNOPAUSE -sPROGNAME=gslj -- gslp.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
