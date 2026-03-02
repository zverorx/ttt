/* 
 * This file is part of ttt.
 * ttt - Tic-tac-toe in a terminal.
 *
 * Copyright (C) 2026 Egorov Konstantin
 *
 * ttt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ttt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ttt. If not, see <https://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <string.h>

#include "terminal.h"

Terminal::Terminal()
{
    tcgetattr(STDIN_FILENO, &origin);
    memcpy(&modify, &origin, sizeof(termios));
}

Terminal::~Terminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &origin);
}

termios Terminal::GetOrigin() const
{
    return origin;
}

termios Terminal::GetModify() const
{
    return modify;
}

void Terminal::DisableICanon(int vtime, int vmin)
{
    modify.c_lflag &= ~ICANON;

    modify.c_cc[VTIME] = vtime;
    modify.c_cc[VMIN] = vmin;

    tcsetattr(STDIN_FILENO, TCSANOW, &modify);
}

void Terminal::EnableICanon()
{
    modify.c_lflag |= ICANON;

    tcsetattr(STDIN_FILENO, TCSANOW, &modify);
}

void Terminal::DisableEcho()
{
    modify.c_lflag &= ~ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &modify);
}

void Terminal::EnableEcho()
{
    modify.c_lflag |= ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &modify);
}
