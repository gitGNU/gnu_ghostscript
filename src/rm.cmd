@echo off
@rem $Id: rm.cmd,v 1.1 2004/01/14 16:59:52 atai Exp $
:next
if '%1'=='' goto exit
if '%1'=='-f' goto sh
erase %1
:sh
shift
goto next
:exit
