@echo off
@rem $Id: rm.cmd,v 1.2 2010/07/10 22:02:20 Arabidopsis Exp $
:next
if '%1'=='' goto exit
if '%1'=='-f' goto sh
erase %1
:sh
shift
goto next
:exit
