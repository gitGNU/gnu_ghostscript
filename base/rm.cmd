@echo off
@rem $Id: rm.cmd,v 1.1 2009/04/23 23:26:21 Arabidopsis Exp $
:next
if '%1'=='' goto exit
if '%1'=='-f' goto sh
erase %1
:sh
shift
goto next
:exit
