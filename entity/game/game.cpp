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
#include <unistd.h>
#include <string.h>

#include "game.h"

#define RED     31
#define BLUE    34 

Game::Game()
    : curr_p(0)
    , prompt('>')
{
    p1 = new Player("Player1", 'X');
    p2 = new Player("         ><[O_O]><", 'O');

    ui = new ConsoleUI();
}

Game::~Game()
{
    delete p1;
    delete p2;
    delete curr_p;
    delete ui;
}

void Game::Start()
{
    int res_ph, rowi, coli;
    char swtch = 0;

    Intro();

    for (int i = 0, move = 0; ; i++) {
        curr_p = i % 2 ? p1 : p2;
        ui->Print(game_time, curr_p);

        if (i == 0) { printf("\n0%c START\n", prompt); }
        else { fprintf(stdout, "\033[%dB", 2 + i); }

        swtch = !swtch;
        if (swtch) { move++; }
        for (;;) {
            res_ph = PromptHandle(move, rowi, coli, i % 2 ? BLUE : RED);
            if (res_ph) {
                ui->SetMark(rowi, coli, *curr_p);
                break; 
            }
            else {
                fputs("\033[2K\033[1A\033[2K", stdout);
                fprintf(stdout, "\033[2K\033[%dA", 2 + i);
                ui->Clear();
                ui->Print(game_time_error, curr_p);
                fprintf(stdout, "\033[%dB", 2 + i);
                fflush(stdout);
            }
        }

        fprintf(stdout, "\033[%dA", 3 + i);
        ui->Clear();
    }
}

void Game::Intro() const
{
    int symbol;

    ui->Print(info, p2);

    for(;;) {
        printf("\n%c PRESS ENTER TO START", prompt);

        symbol = fgetc(stdin);

        fputs("\033[2K\033[A", stdout);
        fflush(stdout);

        if (symbol == '\n') { 
            fputs("\033[2K\033[1A", stdout);
            break; 
        }

        if (symbol == EOF) { clearerr(stdin); }
    }

    ui->Clear();
}

bool Game::PromptHandle(int move_count, int &rowi, 
                        int &coli, int color_code) const
{
    char buff[8];
    int res_sscanf;
    char mark;

    memset(buff, 0, sizeof(buff));

    printf("\033[%dm%d%c\033[0m ", color_code, move_count, prompt);

    fgets(buff, sizeof(buff), stdin);
    res_sscanf = sscanf(buff, "%d %d\n", &rowi, &coli);
    if (res_sscanf != 2) { return false; }
    if (ui->IsBusy(rowi, coli, mark)) { return false; }

    return true;
}
