// <locale.cpp> -*- coding: utf-8 -*-
//
// Time-stamp: <2022-06-23 20:04:32 neige>
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
#include <vector>

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

wstring to_wstring(const char* str)
{
    vector<wchar_t> buf(strlen(str) + 1);
#ifdef _MSC_VER
    size_t returnValue;
    mbstowcs_s(&returnValue, &buf.at(0), buf.size(), str, _TRUNCATE);
#else   
    mbstowcs(&buf.at(0), str, buf.size());
#endif   
    return wstring(&buf.at(0));
}

wstring to_wstring(const string& str)
{
    return to_wstring(str.c_str());
}

wstring to_wstring(const wchar_t* str)
{
    return wstring(str);
}

string to_string(const wstring& wcs)
{
    vector<char> mbs(wcs.size() * MB_CUR_MAX + 1);
#ifdef _MSC_VER
    size_t returnValue;
    wcstombs_s(&returnValue, &mbs.at(0), mbs.size(), wcs.c_str(), _TRUNCATE);
#else
    wcstombs(&mbs.at(0), wcs.c_str(), mbs.size());
#endif    
    return &mbs.at(0);
}

int main(int argc, char** argv)
{
    try {
        wcout << L"locale" << endl;
        //wcout << L"グローバルロケール変更前に出力すると何も出力されなくなる" << endl;
        locale::global(locale(""));
        output(L"imbue する前の wcout は クラシックロケール のまま");
        wcout.imbue(locale(""));
        output(L"ネイティブロケール");
        wcout.imbue(locale(locale::classic(), "ja_JP.UTF-8", locale::ctype));
        output(L"クラシックロケールで ctype は utf-8");
        wcout.imbue(locale(locale::classic(), "", locale::ctype));
        output(L"クラシックロケールで ctype はネイティブロケールのもの");
    }
    catch (const exception& x) {
        cerr << x.what() << endl;
    }
    return 0;
}

//------------------------------------------------------------

// end of <locale.cpp>
