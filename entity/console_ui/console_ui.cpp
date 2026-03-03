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
#include <stdlib.h>

#include "console_ui.h"

ConsoleUI::ConsoleUI() 
    : default_fill('_')
    , output_lines(0)
    , panel_lines(13)
    , field_lines(5)
    , separator_lines(2)
{
    memset(gameplay, 0, sizeof(gameplay));
    ClearField();
}

ConsoleUI::~ConsoleUI()
{
    DeleteAllMove();
}

void ConsoleUI::Print(panel_version v, const Player *p)
{
    PrintPanel(v, p);
    PrintSeparator();
    PrintField();
    PrintGameplay();
}

void ConsoleUI::Clear()
{
    for (int i = 0; i < output_lines; i++) {
        fputs("\033[2K", stdout);
        if (i < output_lines - 1) { fputs("\033[1A", stdout); }
    }

    output_lines = 0;

    fputc('\r', stdout);
    fflush(stdout);
}

bool ConsoleUI::AddMove(const char *str, size_t len)
{
    if (!str || len <= 0) { return false; }

    for (int i = 0; i < GAMEPLAY_SIZE; i++) {
        if (gameplay[i] != 0) { continue; }

        gameplay[i] = static_cast<char *>(calloc(len + 1, sizeof(char)));
        if (!gameplay[i]) { return false; }

        strncpy(gameplay[i], str, len);
        gameplay[i][len] = '\0';
        return true;
    }

    return false;
}

bool ConsoleUI::DeleteMove(int index)
{
    if (index < 0 || index > GAMEPLAY_SIZE - 1) { return false; }

    free(gameplay[index]);

    gameplay[index] = static_cast<char *>(0);

    return true;
}
    
void ConsoleUI::DeleteAllMove()
{
    for (int i = 0; i < GAMEPLAY_SIZE; i++) {
        free(gameplay[i]);
        gameplay[i] = static_cast<char *>(0);
    }
}

bool ConsoleUI::IsBusy(int rowi, int coli, char &mark) const
{
    if ((rowi > row_count - 1 || rowi < 0 ) ||
        (coli > col_count - 1 || coli < 0 )) { 
        mark = '\0';
        return true;
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

void ConsoleUI::PrintPanel(panel_version v, const Player *p)
{
    char nickname[28];
    size_t nick_size = sizeof(nickname);
    memset(nickname, 0, sizeof(nickname));

    if (p) {
        size_t nick_len = p->GetLengthNickname();
        strncpy(nickname, p->GetNickname(), 
                nick_size - 1 > nick_len ? nick_len : nick_size - 1);
    }
    else {
        strncpy(nickname, "  No one, just no one ...", nick_size - 1);
    }

    switch (v) {
        case info:
            printf(" _____________________________\n");
            printf("|         Tic Tac Toe         |\n");
            printf("|         INFORMATION         |\n");
            printf("| To move, enter the row and  |\n");
            printf("| column separated by a space.|\n");
            printf("|                             |\n");
            printf("|   The first move is for:    |\n");
            printf("|                             |\n");
            printf("| %-27s |\n"                      , nickname);
            printf("|                             |\n");
            printf("|                             |\n");
            printf("|       Enjoy the game!       |\n");
            printf("|_____________________________|");
            break;

        case game_time:
            printf(" _____________________________\n");
            printf("|         Tic Tac Toe         |\n");
            printf("|          GAME TIME          |\n");
            printf("|   Player's expected move:   |\n");
            printf("|                             |\n");
            printf("| %-27s |\n"                      , nickname);
            printf("|                             |\n");
            printf("| Commands:                   |\n");
            printf("| q - quit                    |\n");
            printf("| r - restart                 |\n");
            printf("|                             |\n");
            printf("|                             |\n");
            printf("|_____________________________|");
            break;
        
        case input_error:
            printf(" _____________________________\n");
            printf("|         Tic Tac Toe         |\n");
            printf("|          GAME TIME          |\n");
            printf("|   Player's expected move:   |\n");
            printf("|                             |\n");
            printf("| %-27s |\n"                      , nickname);
            printf("|                             |\n");
            printf("| Commands:                   |\n");
            printf("| q - quit                    |\n");
            printf("| r - restart                 |\n");
            printf("|                             |\n");
            printf("|  Invalid input. Try again!  |\n");
            printf("|_____________________________|");
            break;

        case busy_error:
            printf(" _____________________________\n");
            printf("|         Tic Tac Toe         |\n");
            printf("|          GAME TIME          |\n");
            printf("|   Player's expected move:   |\n");
            printf("|                             |\n");
            printf("| %-27s |\n"                      , nickname);
            printf("|                             |\n");
            printf("| Commands:                   |\n");
            printf("| q - quit                    |\n");
            printf("| r - restart                 |\n");
            printf("|                             |\n");
            printf("|  Cell is busy.  Try again!  |\n");
            printf("|_____________________________|");
            break;

        case game_over:
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
            printf("|       Come back again!      |\n");
            printf("|_____________________________|");
            break;
    }

    output_lines += panel_lines;
    fflush(stdout);
}

void ConsoleUI::PrintSeparator()
{
    printf("\n\n[=============================]");

    fflush(stdout);
    output_lines += separator_lines;
}

void ConsoleUI::PrintField()
{
	printf("\n\t    0   1   2\n");
	printf("\t   ___ ___ ___\n");
	printf("\t0 |_%c_|_%c_|_%c_|\n", field[0][0], field[0][1], field[0][2]);
	printf("\t1 |_%c_|_%c_|_%c_|\n", field[1][0], field[1][1], field[1][2]);
	printf("\t2 |_%c_|_%c_|_%c_|", field[2][0], field[2][1], field[2][2]);

    fflush(stdout);
    output_lines += field_lines;
}

void ConsoleUI::PrintGameplay()
{
    putc('\n', stdout);
    output_lines++;

    putc('\n', stdout);
    output_lines++;

    for (int i = 0; i < GAMEPLAY_SIZE; i++) {
        if (gameplay[i]) {
            printf("%s\n", gameplay[i]);
            output_lines++;
        }
    }
    
    fflush(stdout);
}
