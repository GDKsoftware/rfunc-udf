:      rfunc UDF library
:      Compile script for Windows OS

:      Copyright 2009 PoleSoft Technologies Group
:      http://www.polesoft.ru/project/rfunc
:      mailto:support@polesoft.ru

:      This library is free software; you can redistribute it and/or
:      modify it under the terms of the GNU Lesser General Public
:      License as published by the Free Software Foundation; either
:      version 2.1 of the License, or (at your option) any later version.
:      See license.txt for more details.

@echo off
set makecmd=C:\CBuilderX\free\Bin\make.exe

: clear old files
%makecmd% -f makefile.bc clean
if errorlevel 1 goto error

: compile new version
%makecmd% -f makefile.bc
if errorlevel 1 goto error
goto ok

:error
pause

:ok