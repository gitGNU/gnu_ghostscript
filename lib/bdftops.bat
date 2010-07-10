@echo off
@rem $Id: bdftops.bat,v 1.4 2010/07/10 22:02:37 Arabidopsis Exp $

call gssetgs.bat
%GSC% -P- -dSAFER -q -dBATCH -dNODISPLAY -- bdftops.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
