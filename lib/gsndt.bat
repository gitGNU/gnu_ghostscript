@echo off
@rem $Id: gsndt.bat,v 1.1 2004/01/14 16:59:47 atai Exp $

call gssetgs.bat
%GSC% -DNODISPLAY %1 %2 %3 %4 %5 %6 %7 %8 %9 >t
