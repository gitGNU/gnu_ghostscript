@rem $Id: rm.bat,v 1.1 2009/04/23 23:27:25 Arabidopsis Exp $
@echo off
:next
if '%1'=='' goto exit
if '%1'=='-f' goto sh
if exist %1 erase %1
:sh
shift
goto next
:exit
