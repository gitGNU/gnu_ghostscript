@echo off
@rem $Id: gssetgs.bat,v 1.1 2004/01/14 16:59:47 atai Exp $

rem Set default values for GS (gs with graphics window) and GSC
rem (console mode gs) if the user hasn't set them.

if %GS%/==/ set GS=gswin32
if %GSC%/==/ set GSC=gswin32c
