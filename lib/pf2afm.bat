@echo off 
@rem $Id: pf2afm.bat,v 1.2 2004/02/14 22:20:04 atai Exp $
@rem Make an AFM file from PFB / PFA and (optionally) PFM files.

if %1/==/ goto usage
if not %2/==/ goto usage
call gssetgs.bat

%GSC% -q -dNODISPLAY -dSAFER -dDELAYSAFER -- pf2afm.ps %1
goto end

:usage
echo "Usage: pf2afm disk_font_name"

:end


