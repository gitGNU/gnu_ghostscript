@echo off
@rem $Id: ps2pdf13.bat,v 1.4 2010/07/10 22:02:37 Arabidopsis Exp $

rem Convert PostScript to PDF 1.3 (Acrobat 4-and-later compatible).

echo -dCompatibilityLevel#1.3 >_.at
goto bot

rem Pass arguments through a file to avoid overflowing the command line.
:top
echo %1 >>_.at
shift
:bot
if not %3/==/ goto top
call ps2pdfxx %1 %2
