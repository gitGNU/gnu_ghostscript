@echo off
@rem $Id: rm.cmd,v 1.2 2004/02/14 22:20:19 atai Exp $
:next
if '%1'=='' goto exit
if '%1'=='-f' goto sh
erase %1
:sh
shift
goto next
:exit
