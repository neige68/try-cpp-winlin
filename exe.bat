@rem <exe.bat> -*- coding: cp932-dos -*-
@echo off
rem Time-stamp: <2022-06-18 22:14:04 neige>
rem
rem Project try-cpp-winlin
rem Copyright (C) 2022 neige68
rem
rem Note: exe
rem
rem Windows:   XP and lator
rem

setlocal
pushd %~dp0
set @config=debug
set @name=
set @verbose=
set @x64=
set @unicode=
:loop
if "%1"=="--" goto optbreak
if "%1"=="6" goto x64
if "%1"=="64" goto x64
if "%1"=="x64" goto x64
if "%1"=="u" goto unicode
if "%1"=="unicode" goto unicode
if "%1"=="r" goto rel
if "%1"=="-r" goto rel
if "%1"=="rel" goto rel
if "%1"=="d" goto deb
if "%1"=="-d" goto deb
if "%1"=="deb" goto deb
if "%1"=="v" goto verbose
if "%1"=="-v" goto verbose
if "%1"=="h" goto help
if "%1"=="-h" goto help
if "%1"=="--help" goto help
goto optend
:x64
set @x64=64
shift
goto loop
:unicode
set @unicode=u
shift
goto loop
:rel
set @config=release
shift
goto loop
:deb
set @config=debug
shift
goto loop
:verbose
set @verbose=t
shift
goto loop
:optbreak
shift
:optend
if not "%1"=="" set @name=%1
if "%@name%"=="" goto help
set @exe=build%@x64%%@unicode%\%@config%\%@name%.exe
if not exist %@exe% set @exe=build%@x64%%@unicode%\%@name%\%@config%\%@name%.exe
if not "%@verbose%"=="" echo INFO: %@exe%
shift
shift
%@exe% %0 %1 %2 %3 %4 %5 %6 %7 %8 %9
goto end
:help
echo usage: exe [x64] [unicode] [v] [deb/rel] [--] name
:end
popd
rem end of exe.bat
