@echo off
@rem $Id: ps2ascii.bat,v 1.1 2004/01/14 16:59:47 atai Exp $

call gssetgs.bat
if '%1'=='' goto a0
if '%2'=='' goto a1
%GSC% -q -dNODISPLAY -dSAFER -dNOBIND -dWRITESYSTEMDICT -dSIMPLE ps2ascii.ps %1 -c quit >%2
goto x
:a0
%GSC% -q -dNODISPLAY -dSAFER -dNOBIND -dWRITESYSTEMDICT -dSIMPLE ps2ascii.ps - -c quit
goto x
:a1
%GSC% -q -dNODISPLAY -dSAFER -dNOBIND -dWRITESYSTEMDICT -dSIMPLE ps2ascii.ps %1 -c quit
goto x
:x
