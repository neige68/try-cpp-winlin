// <po.cpp> -*- coding: utf-8 -*-
//
// Time-stamp: <2022-06-22 19:47:25 neige>
//
// Project try-cpp-winlin
// Copyright (C) 2022 neige68
//
// Note: po
//
// Compiler: gcc 8.3, VC 14.2
//

// boost
#include <boost/program_options.hpp>
#include <boost/scope_exit.hpp>

// std c++
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WINDOWS
# include <tchar.h>
# ifdef _UNICODE
#  define VALUE wvalue
#  define STRING wstring
#  define COUT wcout
# else
#  define VALUE value
#  define STRING string
#  define COUT cout
# endif
# define TEXT(s) _T(s)
# define MAIN _tmain
#else
# define TCHAR char
# define VALUE value
# define STRING string
# define COUT cout
# define TEXT(s) s
# define MAIN main
#endif

using namespace std;

//------------------------------------------------------------
//
// to_wstring
//

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

wstring to_wstring(const wstring& str)
{
    return str;
}

wstring utf8_to_wstring(const string& str)
{
    auto org = locale();
    BOOST_SCOPE_EXIT(org) {
        locale::global(org);
    } BOOST_SCOPE_EXIT_END;
    locale::global(locale(org, "ja_JP.UTF-8", locale::ctype));
    return to_wstring(str);
}

//------------------------------------------------------------

#ifdef _WINDOWS
# if 0 // どっちでもいい
typedef TCHAR argv_char_t;
int _tmain(int argc, TCHAR* argv[])
# else
typedef wchar_t argv_char_t;
int wmain(int argc, wchar_t* argv[])
# endif
#else
typedef char argv_char_t;
int main(int argc, char* argv[])
#endif
{
    try {
        locale::global(locale(locale::classic(), "", locale::ctype));
        wcout.imbue(locale());
        wcout << L"po" << endl;
        namespace po = boost::program_options;
        po::positional_options_description pod;
        pod.add("infile", -1); // 位置パラメータ
        po::options_description od("option");
        od.add_options()
            ("help,?", "この表示")
            ("string,S", po::wvalue<wstring>()->default_value(L"hoge", "hoge"), "文字列オプション")
            ("integer,I", po::value<int>()->default_value(0), "整数オプション")
            ;
        po::options_description od_all = od;
        od_all.add_options()
            ("infile", po::wvalue<vector<wstring>>(), "hidden")
            ;
        po::variables_map vm;
        store(po::basic_command_line_parser<argv_char_t>(argc, argv).options(od_all).positional(pod).run(), vm);
        po::notify(vm);
        if (vm.count("help")) {
            cout << od;
            return 0;
        }
        wcout << L"string=" << to_wstring(vm["string"].as<wstring>()) << endl;
        wcout << L"integer=" << vm["integer"].as<int>() << endl;
        if (vm.count("infile"))
            for (const auto& infile : vm["infile"].as<vector<wstring>>())
                wcout << L"infile: " << infile << endl;
    }
    catch (const exception& x) {
        cerr << x.what() << endl;
    }
    return 0;
}

//------------------------------------------------------------

// end of <po.cpp>
