// <hello.cpp> -*- coding: utf-8 -*-
//
// Time-stamp: <2022-06-18 20:15:54 neige>
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

using namespace std;

//------------------------------------------------------------

int main(int argc, char** argv)
{
    locale::global(locale(""));
    wcout << L"Hello, world." << endl;
    wcout << L"みなさんこんにちは。" << endl;
    return 0;
}

//------------------------------------------------------------

// end of <hello.cpp>
