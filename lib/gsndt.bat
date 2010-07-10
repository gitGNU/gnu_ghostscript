@echo off
@rem $Id: gsndt.bat,v 1.4 2010/07/10 22:02:36 Arabidopsis Exp $

call gssetgs.bat
%GSC% -P- -dSAFER -DNODISPLAY %1 %2 %3 %4 %5 %6 %7 %8 %9 >t
