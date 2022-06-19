// <termcols.cpp>
//
// Time-stamp: <2022-06-20 00:25:37 neige>
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

#if !defined(_MSC_VER)
#include <curses.h>
#endif

//------------------------------------------------------------

int GetTerminalCols()
{
#if defined(_MSC_VER)
    return 80;
#else // !defined(_MSC_VER)
    initscr();
    return COLS;
#endif // !defined(_MSC_VER)
}

//------------------------------------------------------------

// end of <termcols.cpp>
