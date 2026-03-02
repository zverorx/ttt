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

enum color { red = 31, blue = 34};

Game::Game()
    : curr_p(0)
    , prompt('>')
{
    p1 = new Player("Player1", 'X');
    p2 = new Player("         ><[O_O]><", 'O');

    ui = new ConsoleUI();
    terminal = new Terminal();
}

Game::~Game()
{
    delete p1;
    delete p2;
    delete ui;
    delete terminal;
}

void Game::Start()
{
    int res_move, rowi, coli;

    terminal->DisableICanon(0, 1);
    terminal->DisableEcho();

    Intro();

    terminal->DisableICanon(0, 4);
    terminal->EnableEcho();

    for (int i = 0, move = 0, swtch = 0; ; i++) {
        curr_p = i % 2 ? p1 : p2;
        ui->Print(game_time, curr_p);

        swtch = !swtch;
        if (swtch) { move++; }

        for (;;) {
            res_move = PromptHandle(move, rowi, coli, i % 2 ? blue : red);
            if (res_move) {
                ui->SetMark(rowi, coli, *curr_p);
                break;
            }
            else {
                ui->Clear();
                ui->Print(game_time_error, curr_p);
            }
        }

        ui->Clear();
    }
}

void Game::Intro() const
{
    char buff[80];

    ui->Print(info, p2);

    printf("%c PRESS ANY TO START...", prompt);
    getc(stdin);
    fputs("\r\033[2K", stdout);
    fflush(stdout);

    snprintf(buff, sizeof(buff), "0%c START", prompt);
    ui->AddMove(buff, sizeof(buff));

    ui->Clear();
}

bool Game::PromptHandle(int move_count, int &rowi, 
                        int &coli, int color_code) const
{
    char line_buff[80];
    char input_buff[5];

    memset(line_buff, 0, sizeof(line_buff));
    memset(input_buff, 0, sizeof(input_buff));

    size_t size_input_buff = sizeof(input_buff);
    size_t len_input_buff = size_input_buff - 1; /* minus '\0' */

    char mark;

    printf("\033[%dm%d%c\033[0m ", color_code, move_count, prompt);

    for (size_t i = 0; i < len_input_buff; i++) {
        input_buff[i] = fgetc(stdin);
        if (input_buff[i] == '\n') { break; }
        if (i == len_input_buff - 1) {
            input_buff[i] = '\n';
            fputc('\n', stdout);
        }
    }

    fputs("\r\033[2K\033[1A", stdout);
    fflush(stdout);

    int res_sscanf = sscanf(input_buff, "%d %d\n", &rowi, &coli);
    if (res_sscanf != 2) { return false; }
    if (ui->IsBusy(rowi, coli, mark)) { return false; }

    snprintf(line_buff, sizeof(line_buff), "\033[%dm%d%c\033[0m %d %d",
             color_code, move_count, prompt, rowi, coli);
    ui->AddMove(line_buff, sizeof(line_buff));

    return true;
}
