// <hello.cpp> -*- coding: utf-8 -*-
//
// Time-stamp: <2022-06-18 16:41:24 neige>
//
// Project try-cpp-winlin
// Copyright (C) 2022 neige
//
// Note: hello
//
// Compiler: gcc 8.3
//

// std c++
#include <iostream>
#include <locale>

using namespace std;

//------------------------------------------------------------

int main(int argc, char** argv)
{
    locale::global(locale(""));
    cout << "Hello, world." << endl;
    cout << "みなさんこんにちは。" << endl;
    return 0;
}

//------------------------------------------------------------

// end of <hello.cpp>
