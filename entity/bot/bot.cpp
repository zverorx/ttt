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

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "bot.h"

Bot::Bot(const char *nickname, char mark) 
    : Player(nickname, mark)
    , ui(0) 
{
    memset(move_stat, 0, sizeof(move_stat));
    srand(time(NULL));
}

void Bot::Move(const ConsoleUI &ui, int &rowi, int &coli)
{
    field_line line;
    char mark;

    this->ui = &ui;
    StatDeterm();

    if (IsFirstMove()) {
        if (rand() % 4 < 2 && !ui.IsBusy(1, 1, mark)) {
            rowi = 1;
            coli = 1;
        }
        else { RandomMove(rowi, coli);}

        return;
    }

    if (IsCurrentMoveWin(line)) {
        FillLine(rowi, coli, line);
        return;
    }

    if (IsNextMoveLoss(line)) {
        FillLine(rowi, coli, line);
        return;
    }

    RandomMove(rowi, coli);

    return;
}

void Bot::StatDeterm()
{
	char own_mark = GetMark();
    char mark;

    memset(move_stat, 0, sizeof(move_stat));

	for(int i = 0; i < ConsoleUI::row_count; i++) {
		for(int j = 0; j < ConsoleUI::col_count; j++) {
			if(ui->IsBusy(i, j, mark)) {
                if (mark == own_mark) {
                    if (i == 0) { move_stat[bot][row0]++; }
                    if (i == 1) { move_stat[bot][row1]++; }
                    if (i == 2) { move_stat[bot][row2]++; }

                    if (j == 0) { move_stat[bot][col0]++; }
                    if (j == 1) { move_stat[bot][col1]++; }
                    if (j == 2) { move_stat[bot][col2]++; }
                }
                else {
                    if (i == 0) { move_stat[man][row0]++; }
                    if (i == 1) { move_stat[man][row1]++; }
                    if (i == 2) { move_stat[man][row2]++; }

                    if (j == 0) { move_stat[man][col0]++; }
                    if (j == 1) { move_stat[man][col1]++; }
                    if (j == 2) { move_stat[man][col2]++; }
                }
            }
		}
	}

	/* Main diagonal */
	for(int i = 0; i < ConsoleUI::row_count; i++) {
        if(ui->IsBusy(i, i, mark)) {
            if (mark == own_mark) { move_stat[bot][d0]++; }
            else { move_stat[man][d0]++; }
        }
	}

	/* Secondary diagonal */
	for(int i = 0; i < ConsoleUI::row_count; i++) {
        if(ui->IsBusy(i, 2 - i, mark)) {
            if (mark == own_mark) { move_stat[bot][d1]++; }
            else { move_stat[man][d1]++; }
        }
	}
}

bool Bot::IsFirstMove() const
{
    for (int j = 0; j < line_count; j++) {
        if (move_stat[bot][j] != 0) { return false; }
    }

    return true;
}

bool Bot::IsCurrentMoveWin(field_line &line) const
{
    for (int j = 0; j < line_count; j++) {
        if (move_stat[bot][j] == 2 && !move_stat[man][j]) {
            line = static_cast<field_line>(j);
            return true; 
        }
    }

    return false;
}

bool Bot::IsNextMoveLoss(field_line &line) const
{
    for (int j = 0; j < line_count; j++) {
        if (move_stat[man][j] == 2 && !move_stat[bot][j]) {
            line = static_cast<field_line>(j);
            return true; 
        }
    }

    return false;
}

void Bot::RandomMove(int &rowi, int &coli) const
{
    int rnd_row, rnd_col;
    char mark;

    for (;;) {
        rnd_row = rand() % ConsoleUI::row_count;
        rnd_col = rand() % ConsoleUI::col_count;

        if (!ui->IsBusy(rnd_row, rnd_col, mark)) {
            rowi = rnd_row;
            coli = rnd_col;
            break;
        }
    }
}

void Bot::FillLine(int &rowi, int &coli, field_line line)
{
    char mark;
    int i, j;

    if (line >= row0 && line <= row2) {
        if (line == row0) { i = 0; }
        if (line == row1) { i = 1; }
        if (line == row2) { i = 2; }

        for (j = 0; j < ConsoleUI::col_count; j++) {
            if (!ui->IsBusy(i, j, mark)) {
                rowi = i;
                coli = j;
                break;
            }
        }

        return;
    }

    if (line >= col0 && line <= col2) {
        if (line == col0) { j = 0; }
        if (line == col1) { j = 1; }
        if (line == col2) { j = 2; }

        for (i = 0; i < ConsoleUI::row_count; i++) {
            if (!ui->IsBusy(i, j, mark)) {
                rowi = i;
                coli = j;
                break;
            }
        }

        return;
    }

    if (line == d0) {
        for (i = 0; i < ConsoleUI::row_count; i++) {
            if (!ui->IsBusy(i, i, mark)) {
                rowi = i;
                coli = i;
                break;
            }
        }

        return;
    }

    if (line == d1) {
        for (i = 0; i < ConsoleUI::row_count; i++) {
            if (!ui->IsBusy(i, 2 - i, mark)) {
                rowi = i;
                coli = 2 - i;
                break;
            }
        }

        return;
    }
}
