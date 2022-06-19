// <termcols.cpp> -*- coding: utf-8 -*-
//
// Time-stamp: <2022-06-20 00:45:05 neige>
//
// Project try-cpp-winlin
// Copyright (C) 2022 neige
//
// Note: termcols
//
// Compiler: gcc 8.3, VC 14.2
// Library:  ncurses (Linux)
//

#include "termcols.h"

// lib
#if defined(_MSC_VER)
# include <windows.h>
#else
#include <curses.h>
#endif

// std c++
#if defined(_MSC_VER)
# include <string>
# include <vector>
using namespace std;
#endif

//------------------------------------------------------------
#if defined(_MSC_VER)
static
vector<string> split(const string& str, char c)
{
    vector<string> result;
    size_t start = 0;
    for (;;) {
        size_t pos = str.find(c, start);
        if (pos == string::npos) break;
        result.push_back(str.substr(start, pos - 1));
        start = pos + 1;
    }
    return result;
}
#endif

int GetTerminalCols()
{
#if defined(_MSC_VER)
    CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleScreenBufferInfo))
        return ConsoleScreenBufferInfo.dwSize.X;
    else {
        // Emacs の shell ではエラー: ハンドルが無効です。
#pragma warning(disable:4996) // getenv の結果は string にすぐコピーするので安全だと思う
        if (string(getenv("TERM")) == "emacs") { // Windows の Emacs の shell では環境変数 TERM=emacs になっている
            string cap = getenv("TERMCAP"); // "emacs:co#115:tc=unknown:" のように起動時の幅が記憶されている
            vector<string> scap = split(cap, ':');
            auto iscap = find_if(scap.begin(), scap.end(),
                                 [] (const string& s) { return s.substr(0, 3) == "co#"; });
            if (iscap != scap.end())
                return atoi(iscap->substr(3).c_str());
        }
#pragma warning(default:4996)
    }
    return 80;
#else // !defined(_MSC_VER)
    initscr();
    return COLS;
#endif // !defined(_MSC_VER)
}

//------------------------------------------------------------

// end of <termcols.cpp>
