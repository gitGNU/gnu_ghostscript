@echo off
@rem $Id: font2c.bat,v 1.2 2004/02/14 22:20:04 atai Exp $

call gssetgs.bat
%GSC% -q -dNODISPLAY -dWRITESYSTEMDICT -- font2c.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
