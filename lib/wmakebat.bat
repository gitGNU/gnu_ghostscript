@rem Execute this script with echo on, so we can see what's happening.
@rem $Id: wmakebat.bat,v 1.2 2004/02/14 22:20:04 atai Exp $
wmakel -u -n -h %1 %2 %3 %4 %5 %6 %7 %8 %9 >_wm_temp.bat
_wm_temp.bat
