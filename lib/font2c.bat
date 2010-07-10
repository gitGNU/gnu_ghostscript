@echo off
@rem $Id: font2c.bat,v 1.4 2010/07/10 22:02:36 Arabidopsis Exp $

call gssetgs.bat
%GSC% -P- -dSAFER -q -dNODISPLAY -dWRITESYSTEMDICT -- font2c.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
