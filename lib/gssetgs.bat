@echo off
@rem $Id: gssetgs.bat,v 1.2 2004/02/14 22:20:04 atai Exp $

rem Set default values for GS (gs with graphics window) and GSC
rem (console mode gs) if the user hasn't set them.

if %GS%/==/ set GS=gswin32
if %GSC%/==/ set GSC=gswin32c
