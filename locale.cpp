// <locale.cpp> -*- coding: utf-8 -*-
//
// Time-stamp: <2022-06-22 04:11:20 neige>
//
// Project try-cpp-winlin
// Copyright (C) 2022 neige68
//
// Note: locale
//
// Compiler: gcc 8.3, VC 14.2
//

// std c++
#include <exception>
#include <iomanip>
#include <iostream>
#include <locale>

using namespace std;

//------------------------------------------------------------

void output(const wchar_t* msg)
{
    wcout << L"----------" << endl;
    wcout << msg << endl;
    wcout << setfill(L' ') << dec << setw(10) << 12345678 << endl;
    wcout << setfill(L' ') << dec << setw(10) << 1234.5678 << endl;
    wcout << setfill(L' ') << dec << setw(10) << 1.2345678 << endl;
    wcout << setfill(L'0') << hex << setw(10) << 0x1a2b3c4d << endl;
    wcout << setfill(L'0') << hex << setw(10) << 0x1a2b << endl;
}

int main(int argc, char** argv)
{
    try {
        locale::global(locale(""));
        output(L"imbue する前の wcout は クラシックロケール のまま");
        wcout.imbue(locale(""));
        output(L"デフォルトロケール");
        wcout.imbue(locale(locale::classic(), ".utf-8", locale::ctype));
        output(L"クラシックロケールで ctype は utf-8");
        wcout.imbue(locale(locale::classic(), "", locale::ctype));
        output(L"クラシックロケールで ctype はデフォルトロケールのもの");
    }
    catch (const exception& x) {
        cerr << x.what() << endl;
    }
    return 0;
}

//------------------------------------------------------------

// end of <locale.cpp>
