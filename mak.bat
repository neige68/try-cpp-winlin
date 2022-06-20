@rem <mak.bat> -*- coding: cp932-dos -*-
@echo off
rem Time-stamp: <2022-06-20 23:07:48 neige>
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
set @build=build
set @cmake_opt=-A Win32

if not exist %@build% mkdir %@build%
pushd %@build%
if not exist ALL_BUILD.vcxproj set @exec_cmake=t
if not "%@exec_cmake%"=="" cmake %@cmake_opt% ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Debug /m
echo INFO: mak.bat: msbuild Debug Done.
if errorlevel 1 goto err_pop2
msbuild ALL_BUILD.vcxproj /p:Configuration=Release /m
echo INFO: mak.bat: msbuild Release Done.
if errorlevel 1 goto err_pop2
popd

rem ------------------------------------------------------------
rem buildu
set @build=buildu
set @cmake_opt=-A Win32 -D UNICODE=1

if not exist %@build% mkdir %@build%
pushd %@build%
if not exist ALL_BUILD.vcxproj set @exec_cmake=t
if not "%@exec_cmake%"=="" cmake %@cmake_opt% ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Debug /m
echo INFO: mak.bat: msbuild Debug Done.
if errorlevel 1 goto err_pop2
msbuild ALL_BUILD.vcxproj /p:Configuration=Release /m
echo INFO: mak.bat: msbuild Release Done.
if errorlevel 1 goto err_pop2
popd

rem ------------------------------------------------------------
rem build64
set @build=build64
set @cmake_opt=-A x64

if not exist %@build% mkdir %@build%
pushd %@build%
if not exist ALL_BUILD.vcxproj set @exec_cmake=t
if not "%@exec_cmake%"=="" cmake %@cmake_opt% ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Debug /m
echo INFO: mak.bat: msbuild Debug Done.
if errorlevel 1 goto err_pop2
msbuild ALL_BUILD.vcxproj /p:Configuration=Release /m
echo INFO: mak.bat: msbuild Release Done.
if errorlevel 1 goto err_pop2
popd

rem ------------------------------------------------------------
rem build64u
set @build=build64u
set @cmake_opt=-A x64 -D UNICODE=1

if not exist %@build% mkdir %@build%
pushd %@build%
if not exist ALL_BUILD.vcxproj set @exec_cmake=t
if not "%@exec_cmake%"=="" cmake %@cmake_opt% ..
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
