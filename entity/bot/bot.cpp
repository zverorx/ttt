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

#include "bot.h"

Bot::Bot(const char *nickname, char mark) 
    : Player(nickname, mark) {}

void Bot::Move(const ConsoleUI &ui, int &rowi, int &coli) const
{
    char mark;

    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < col_count; j++) {
            if (!ui.IsBusy(i, j, mark)) {
                rowi = i;
                coli = j;
            }
        }
    }
}
