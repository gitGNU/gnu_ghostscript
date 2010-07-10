@rem Execute this script with echo on, so we can see what's happening.
@rem $Id: wmakebat.bat,v 1.4 2010/07/10 22:02:35 Arabidopsis Exp $
wmakel -u -n -h %1 %2 %3 %4 %5 %6 %7 %8 %9 >_wm_temp.bat
_wm_temp.bat
