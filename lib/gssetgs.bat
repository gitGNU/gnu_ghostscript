@echo off
@rem $Id: gssetgs.bat,v 1.4 2010/07/10 22:02:36 Arabidopsis Exp $

rem Set default values for GS (gs with graphics window) and GSC
rem (console mode gs) if the user hasn't set them.

if %GS%/==/ set GS=gswin32
if %GSC%/==/ set GSC=gswin32c
