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

#include <stdio.h>
#include <string.h>

#include "console_ui.h"

ConsoleUI::ConsoleUI() 
    : default_fill('_')
    , output_lines(0)
    , panel_lines(14)
    , field_lines(6)
    , separator_lines(1)
{
    ClearField();
}

void ConsoleUI::PrintUI(print_mode md, const Player *winner)
{
    if (md == active) { PrintStartPanel(); }
    else { PrintEndPanel(winner); }

    PrintSeparator();
    PrintField();
}

void ConsoleUI::ClearUI()
{
    for (int i = 0; i < output_lines; i++) {
        fputs("\033[2K", stdout);
        if (i < output_lines - 1) { fputs("\033[1A", stdout); }
    }

    output_lines = 0;

    fputc('\r', stdout);
    fflush(stdout);
}

bool ConsoleUI::IsBusy(int rowi, int coli, char &mark) const
{
    if ((rowi > row_count - 1 || rowi < 0 ) ||
        (coli > col_count - 1 || coli < 0 )) { 
        mark = '\0';
        return false;
    }

    mark = field[rowi][coli];
    if (mark == default_fill) { return false; }

    return true;
}

bool ConsoleUI::SetMark(int rowi, int coli, const Player &p)
{
    if (rowi > row_count - 1 || rowi < 0 ) { return false; }
    if (coli > col_count - 1 || coli < 0 ) { return false; }

    field[rowi][coli] = p.GetMark();
    return true;
}

bool ConsoleUI::ClearMark(int rowi, int coli)
{
    if (rowi > row_count - 1 || rowi < 0 ) { return false; }
    if (coli > col_count - 1 || coli < 0 ) { return false; }

    field[rowi][coli] = default_fill;
    return true;
}

void ConsoleUI::ClearField()
{
    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < col_count; j++) {
            field[i][j] = default_fill;
        }
    }
}

void ConsoleUI::PrintStartPanel()
{
    printf(" _____________________________\n");
	printf("|         Tic Tac Toe         |\n");
	printf("| To move, enter the row and  |\n");
	printf("| column separated by a space.|\n");
	printf("|                             |\n");
	printf("| Commands:                   |\n");
	printf("| q - quit                    |\n");
	printf("| r - restart                 |\n");
	printf("| n - change nickname         |\n");
	printf("| m - change mark             |\n");
	printf("|                             |\n");
	printf("| Enjoy the game!             |\n");
	printf("|_____________________________|\n");

    fflush(stdout);
    output_lines += panel_lines;
}

void ConsoleUI::PrintEndPanel(const Player *winner)
{
    char nickname[28];
    size_t nick_size = sizeof(nickname);
    memset(nickname, 0, sizeof(nickname));

    if (winner == 0) {
        strncpy(nickname, "No one, just no one ...", nick_size - 1);
    }
    else {
        size_t nick_len = winner->GetLengthNickname();
        strncpy(nickname, winner->GetNickname(), 
                nick_size - 1 > nick_len ? nick_len : nick_size - 1);
    }

    printf(" _____________________________\n");
    printf("|         Tic Tac Toe         |\n");
    printf("|          GAME OVER          |\n");
    printf("|        The winner is        |\n");
    printf("|                             |\n");
    printf("| %-27s |\n"                      , nickname);
    printf("|                             |\n");
    printf("| Commands:                   |\n");
    printf("| q - quit                    |\n");
    printf("| r - restart                 |\n");
    printf("|                             |\n");
    printf("| Come back again!            |\n");
    printf("|_____________________________|\n");

    fflush(stdout);
    output_lines += panel_lines;
}

void ConsoleUI::PrintField()
{
	printf("\t    0   1   2\n");
	printf("\t   ___ ___ ___\n");
	printf("\t0 |_%c_|_%c_|_%c_|\n", field[0][0], field[0][1], field[0][2]);
	printf("\t1 |_%c_|_%c_|_%c_|\n", field[1][0], field[1][1], field[1][2]);
	printf("\t2 |_%c_|_%c_|_%c_|\n", field[2][0], field[2][1], field[2][2]);

    fflush(stdout);
    output_lines += field_lines;
}

void ConsoleUI::PrintSeparator()
{
    printf("\n[=============================]\n");
    output_lines += separator_lines;
}
