@echo off
@rem $Id: gsdj.bat,v 1.4 2010/07/10 22:02:35 Arabidopsis Exp $

call gssetgs.bat
%GSC% -q -sDEVICE=deskjet -r300 -P- -dSAFER -dNOPAUSE -sPROGNAME=gsdj -- gslp.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
