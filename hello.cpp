// <hello.cpp> -*- coding: utf-8 -*-
//
// Time-stamp: <2022-06-22 03:31:59 neige>
//
// Project try-cpp-winlin
// Copyright (C) 2022 neige
//
// Note: hello
//
// Compiler: gcc 8.3, VC 14.2
//

// mine
#include "termcols.h"

// std c++
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <locale>
#include <map>
#include <string>
#include <vector>

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

void dump(const wchar_t* str)
{
    while (*str) 
        wcout << L' ' << setw(sizeof(wchar_t) * 2) << setfill(L'0') << hex
              << (unsigned int)(wchar_t)(*str++);
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

#ifdef _WINDOWS
int _tmain(int argc, TCHAR** argv)
#else
int main(int argc, char** argv)
#endif
{
    try {
        locale::global(locale(locale::classic(), "", locale::ctype));
        wcout.imbue(locale());
        wcout << L"Hello, world." << endl;
        wcout << L"みなさんこんにちは。" << endl;
        wcout << L"ターミナルの行の長さ: " << GetTerminalCols() << endl;
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
        for (int i = 0; i < argc; i++) {
            wcout << L"----------" << endl;
            wcout << L"argv[" << i << L"]:\t";
            dump(argv[i]);
            wcout << endl;
            wstring arg = to_wstring(argv[i]);
            wcout << L"wchar_t:\t";
            dump(arg.c_str());
            wcout << endl;
            //
            vector<pair<string, wstring>> localeAndHeaders = {
                { "ja_JP.utf8", L"UTF-8:\t\t" },
#ifdef _WINDOWS
                { ".932", L"SJIS(CP932):\t" },
                { ".20932", L"EUC(CP20932):\t" },
#else
                { "ja_JP.eucjp", L"EUC-JP:\t\t" },
#endif
            };
            for (const auto& iLocaleAndHeaders: localeAndHeaders) {
                wcout << iLocaleAndHeaders.second;
                try {
                    locale::global(locale(iLocaleAndHeaders.first));
                    string arg_mb = to_string(arg);
                    locale::global(locale(""));
                    dump(arg_mb.c_str());
                }
                catch (const exception& x) {
                    wcout << L"Exception: " << x.what();
                }
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
