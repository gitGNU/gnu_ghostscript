@echo off 
@rem $Id: pf2afm.bat,v 1.4 2010/07/10 22:02:38 Arabidopsis Exp $
@rem Make an AFM file from PFB / PFA and (optionally) PFM files.

if %1/==/ goto usage
if not %2/==/ goto usage
call gssetgs.bat

%GSC% -q -dNODISPLAY -P- -dSAFER -dDELAYSAFER -- pf2afm.ps %1
goto end

:usage
echo "Usage: pf2afm disk_font_name"

:end


