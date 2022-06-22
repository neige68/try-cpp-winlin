# <CMakeLists.txt> -*- coding: utf-8 -*-
# Time-stamp: <2022-06-22 23:39:14 neige>
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
find_package(Boost 1.74 REQUIRED COMPONENTS program_options)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#------------------------------------------------------------

if (CMAKE_GENERATOR MATCHES "Visual Studio")
    # /source-charset: ソースコードの優先する文字集合の指定
    # /MP: マルチプロセスでコンパイル
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:UTF-8 /MP")
endif()

if (${UNICODE})
    add_compile_definitions(UNICODE;_UNICODE)
endif()

add_executable(hello hello.cpp termcols.cpp)

if (UNIX)
    target_link_libraries(hello ncurses)
endif()

add_executable(locale locale.cpp)

add_executable(po po.cpp)
if (UNIX)
    target_link_libraries(po boost_program_options)
endif()

# end of <CMakeLists.txt>
