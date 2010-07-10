@rem $Id: rm.bat,v 1.2 2010/07/10 22:02:30 Arabidopsis Exp $
@echo off
:next
if '%1'=='' goto exit
if '%1'=='-f' goto sh
if exist %1 erase %1
:sh
shift
goto next
:exit
