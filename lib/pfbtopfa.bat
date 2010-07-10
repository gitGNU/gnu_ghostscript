@echo off 
@rem $Id: pfbtopfa.bat,v 1.3 2010/07/10 22:02:39 Arabidopsis Exp $
@rem Convert .pfb fonts to .pfa format

if %1/==/ goto usage
if %2/==/ goto usage
if not %3/==/ goto usage
call gssetgs.bat

%GSC% -P- -dSAFER -q -dNODISPLAY -- pfbtopfa.ps %1 %2
goto end

:usage
echo "Usage: pfbtopfa input.pfb output.pfa"

:end
