@echo off
if "%2"=="" goto noparams
if not exist %1 goto notfound
if not exist %2 goto notfound

fc %1 %2 >nul

IF "%errorlevel%"=="0" goto ok
echo ScriptRes:Bad:%ERRORLEVEL%
exit

:ok
echo ScriptRes:Ok:%ERRORLEVEL%
exit

:notfound
echo ScriptRes:Unknown:file not found
exit

:noparams
echo ScriptRes:Unknown:not enough parameters
exit
