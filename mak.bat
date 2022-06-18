@rem <mak.bat> -*- coding: cp932-dos -*-
@echo off
rem Time-stamp: <2022-06-18 17:11:56 neige>
rem
rem Project try-cpp-winlin
rem Copyright (C) 2022 neige68
rem
rem Note: build
rem
rem Windows:   XP and lator
rem

setlocal
pushd %~dp0
set @exec_cmake=

rem VC の vcvarsall.bat のあるディレクトリを指定
set VC=%VC142%

:optloop
if "%1"=="" goto optend
if "%1"=="cm" set @exec_cmake=t
if "%1"=="cm" goto optnext
echo WARN: mak.bat: オプション %1 が無効です.
:optnext
shift
goto optloop
:optend

if "%VCToolsVersion%"=="" call "%VC%\vcvarsall.bat" x86
if not exist build mkdir build
pushd build
if not exist ALL_BUILD.vcxproj set @exec_cmake=t
if not "%@exec_cmake%"=="" cmake -A Win32 ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Debug /m
echo INFO: mak.bat: msbuild Debug Done.
if errorlevel 1 goto err
msbuild ALL_BUILD.vcxproj /p:Configuration=Release /m
echo INFO: mak.bat: msbuild Release Done.
:err
popd
:err_pop1
popd
if errorlevel 1 echo エラーがあります.
if errorlevel 1 exit /b 1
rem end of mak.bat
