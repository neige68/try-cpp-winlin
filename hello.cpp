// <hello.cpp> -*- coding: utf-8 -*-
//
// Time-stamp: <2022-06-19 14:05:46 neige>
//
// Project try-cpp-winlin
// Copyright (C) 2022 neige
//
// Note: hello
//
// Compiler: gcc 8.3, VC 14.2
//

// std c++
#include <iomanip>
#include <iostream>
#include <locale>

#ifdef _WINDOWS
#include <tchar.h>
#endif

using namespace std;

//------------------------------------------------------------

void dump(const char* str)
{
    while (*str) 
        wcout << L' ' << setw(2) << setfill(L'0') << hex
              << (unsigned int)(unsigned char)(*str++);
}

#ifdef _WINDOWS
int _tmain(int argc, TCHAR** argv)
#else
int main(int argc, char** argv)
#endif
{
    try {
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
        if (typeid(argv) == typeid(char**)) {
            for (int i = 0; i < argc; i++) {
                wcout << L"argv[" << i << L"]:";
                dump(argv[i]);
                wcout << endl;
            }
        }
    }
    catch (const exception& x) {
        cerr << x.what() << endl;
    }
    return 0;
}

//------------------------------------------------------------

// end of <hello.cpp>
