@echo off
@rem $Id: font2c.bat,v 1.1 2004/01/14 16:59:46 atai Exp $

call gssetgs.bat
%GSC% -q -dNODISPLAY -dWRITESYSTEMDICT -- font2c.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
