@rem $Id: rm.bat,v 1.2 2004/02/14 22:20:19 atai Exp $
@echo off
:next
if '%1'=='' goto exit
if '%1'=='-f' goto sh
if exist %1 erase %1
:sh
shift
goto next
:exit
