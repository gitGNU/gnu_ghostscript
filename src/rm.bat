@rem $Id: rm.bat,v 1.1 2004/01/14 16:59:52 atai Exp $
@echo off
:next
if '%1'=='' goto exit
if '%1'=='-f' goto sh
if exist %1 erase %1
:sh
shift
goto next
:exit
