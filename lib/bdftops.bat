@echo off
@rem $Id: bdftops.bat,v 1.1 2004/01/14 16:59:46 atai Exp $

call gssetgs.bat
%GSC% -q -dBATCH -dNODISPLAY -- bdftops.ps %1 %2 %3 %4 %5 %6 %7 %8 %9
