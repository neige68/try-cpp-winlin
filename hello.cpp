// <hello.cpp> -*- coding: utf-8 -*-
//
// Time-stamp: <2022-06-18 22:05:26 neige>
//
// Project try-cpp-winlin
// Copyright (C) 2022 neige
//
// Note: hello
//
// Compiler: gcc 8.3, VC 14.2
//

// std c++
#include <iostream>
#include <locale>

#ifdef _WINDOWS
#include <tchar.h>
#endif

using namespace std;

//------------------------------------------------------------

#ifdef _WINDOWS
int _tmain(int argc, TCHAR** argv)
#else
int main(int argc, char** argv)
#endif
{
    locale::global(locale(""));
    wcout << L"Hello, world." << endl;
    wcout << L"みなさんこんにちは。" << endl;
#if defined(_WIN64)
    wcout << L"_WIN64 が定義されています。" << endl;
#endif
    wcout << L"sizeof(void*)=" << sizeof(void*) << endl;
#if defined(UNICODE)
    wcout << L"UNICODE が定義されています。" << endl;
#endif
#if defined(_UNICODE)
    wcout << L"_UNICODE が定義されています。" << endl;
#endif
    wcout << L"typename(argv)=" << typeid(argv).name() << endl;
    return 0;
}

//------------------------------------------------------------

// end of <hello.cpp>
