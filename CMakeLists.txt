# <CMakeLists.txt> -*- coding: utf-8 -*-
# Time-stamp: <2022-06-18 16:40:16 neige>
#
# Project try-cpp-winlin
# Copyright (C) 2022 neige
#

cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE ON)
# MSVC でスタティックリンク
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(try-cpp-winlin CXX)

#------------------------------------------------------------
#
# boost
#

# BOOST を探す
# Windows で C: ドライブ以外から探すには 環境変数 CMAKE_PREFIX_PATH の設定が必要
find_package(Boost 1.74 REQUIRED COMPONENTS filesystem)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#------------------------------------------------------------

# C++17 使用
#set(CMAKE_CXX_STANDARD "17")

# /MP: マルチプロセス
# /wd4068: warning C4068: 不明なプラグマがありました。をオフに設定
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /wd4068")

# マップファイル生成
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MAP")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MAP")

#add_compile_definitions(_CRT_RAND_S)

add_executable(hello hello.cpp)

# end of <CMakeLists.txt>
