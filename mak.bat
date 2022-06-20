@rem <mak.bat> -*- coding: cp932-dos -*-
@echo off
rem Time-stamp: <2022-06-20 23:01:02 neige>
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

rem ------------------------------------------------------------
rem build
if not exist build mkdir build
pushd build
if not exist ALL_BUILD.vcxproj set @exec_cmake=t
if not "%@exec_cmake%"=="" cmake -A Win32 ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Debug /m
echo INFO: mak.bat: msbuild Debug Done.
if errorlevel 1 goto err_pop2
msbuild ALL_BUILD.vcxproj /p:Configuration=Release /m
echo INFO: mak.bat: msbuild Release Done.
if errorlevel 1 goto err_pop2
popd

rem ------------------------------------------------------------
rem buildu
if not exist buildu mkdir buildu
pushd buildu
if not exist ALL_BUILD.vcxproj set @exec_cmake=t
if not "%@exec_cmake%"=="" cmake -A Win32 -D UNICODE=1 ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Debug /m
echo INFO: mak.bat: msbuild Debug Done.
if errorlevel 1 goto err_pop2
msbuild ALL_BUILD.vcxproj /p:Configuration=Release /m
echo INFO: mak.bat: msbuild Release Done.
if errorlevel 1 goto err_pop2
popd

rem ------------------------------------------------------------
rem build64
if not exist build64 mkdir build64
pushd build64
if not exist ALL_BUILD.vcxproj set @exec_cmake=t
if not "%@exec_cmake%"=="" cmake -A x64 ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Debug /m
echo INFO: mak.bat: msbuild Debug Done.
if errorlevel 1 goto err_pop2
msbuild ALL_BUILD.vcxproj /p:Configuration=Release /m
echo INFO: mak.bat: msbuild Release Done.
if errorlevel 1 goto err_pop2
popd

rem ------------------------------------------------------------
rem build64u
if not exist build64u mkdir build64u
pushd build64u
if not exist ALL_BUILD.vcxproj set @exec_cmake=t
if not "%@exec_cmake%"=="" cmake -A x64 -D UNICODE=1 ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Debug /m
echo INFO: mak.bat: msbuild Debug Done.
if errorlevel 1 goto err_pop2
msbuild ALL_BUILD.vcxproj /p:Configuration=Release /m
echo INFO: mak.bat: msbuild Release Done.
if errorlevel 1 goto err_pop2
popd

rem ------------------------------------------------------------
:err_pop2
popd
:err_pop1
popd
if errorlevel 1 echo エラーがあります.
if errorlevel 1 exit /b 1
rem end of mak.bat
