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
#include <pwd.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

enum color { red = 31, blue = 34};

Game::Game()
    : prompt('>')
{
    passwd *pw = getpwuid(geteuid());
    plr[man] = pw ? new Player(pw->pw_name, 'X') : new Player("Player", 'X');

    plr[bot] = new Player("><[O_O]><", 'O');
    ui = new ConsoleUI();
    terminal = new Terminal();
}

Game::~Game()
{
    delete plr[man];
    delete plr[bot];
    delete ui;
    delete terminal;
}

pmove_t Game::Start()
{
    int rowi, coli, curr_plr_i;
    pmove_t res_move;

    terminal->DisableICanon(0, 1);
    terminal->DisableEcho();

    curr_plr_i = Intro();

    terminal->DisableICanon(0, 4);
    terminal->EnableEcho();

    for (int i = 0, move = 0, swtch = 0; ; i++, curr_plr_i = !curr_plr_i) {
        ui->Print(game_time, plr[curr_plr_i]);

        swtch = !swtch;
        if (swtch) { move++; }

        for (bool run = true; run;) {
            res_move = ProcessPlayerMove(move, rowi, coli, curr_plr_i ? red : blue);
            switch (res_move) {
                case success:
                    ui->SetMark(rowi, coli, *plr[curr_plr_i]);
                    run = false;
                    break;
                case quit: return quit;
                case restart: 
                    ui->Clear(); 
                    return restart;
                case invalid_input:
                    ui->Clear(); 
                    ui->Print(input_error, plr[curr_plr_i]);
                    break;
                case cell_is_busy:
                    ui->Clear(); 
                    ui->Print(busy_error, plr[curr_plr_i]);
                    break;
                case out_of_range:
                    ui->Clear(); 
                    ui->Print(range_error, plr[curr_plr_i]);
                    break;
            }
        }

        ui->Clear();
    }

    return quit;
}

void Game::Reset()
{
    delete plr[man];
    delete plr[bot];
    delete ui;
    delete terminal;

    passwd *pw = getpwuid(geteuid());
    plr[man] = pw ? new Player(pw->pw_name, 'X') : new Player("Player", 'X');

    plr[bot] = new Player("><[O_O]><", 'O');
    ui = new ConsoleUI();
    terminal = new Terminal();
}

player_i Game::Intro() const
{
    char buff[80];
    player_i first_plr_indx;
    int rnd;

    srand(time(0));
    rnd = rand();
    first_plr_indx = rnd % 2 ? man : bot;

    ui->Print(info, plr[first_plr_indx]);

    printf("%c PRESS ANY TO START...", prompt);
    getc(stdin);
    fputs("\r\033[2K", stdout);
    fflush(stdout);

    snprintf(buff, sizeof(buff), "0%c START", prompt);
    ui->AddMove(buff, sizeof(buff));

    ui->Clear();

    return first_plr_indx;
}

pmove_t Game::ProcessPlayerMove(int move_count, int &rowi, 
                                int &coli, int color_code) const
{
    char line_buff[80];
    char input_buff[5];

    memset(line_buff, 0, sizeof(line_buff));
    memset(input_buff, 0, sizeof(input_buff));

    size_t size_input_buff = sizeof(input_buff);
    size_t len_input_buff = size_input_buff - 1; /* minus '\0' */

    printf("\033[%dm%d%c\033[0m ", color_code, move_count, prompt);

    for (size_t i = 0; i < len_input_buff; i++) {
        input_buff[i] = fgetc(stdin);
        if (input_buff[i] == '\n') { break; }
        if (i == len_input_buff - 1) {
            fputc('\n', stdout); 

            if (strcmp("quit", input_buff) == 0) { return quit; }
            if (strcmp("rest", input_buff) == 0) { 
                fputs("\033[1A", stdout);
                return restart;
            }

            input_buff[i] = '\n';
        }
    }

    fputs("\r\033[2K\033[1A", stdout);
    fflush(stdout);

    int res_sscanf = sscanf(input_buff, "%d %d", &rowi, &coli);
    if (res_sscanf != 2) { return invalid_input; }
    char mark;
    if (ui->IsBusy(rowi, coli, mark)) {
        if (mark != '\0') { return cell_is_busy; }
        else { return out_of_range; }
    }

    snprintf(line_buff, sizeof(line_buff), "\033[%dm%d%c\033[0m %d %d",
             color_code, move_count, prompt, rowi, coli);
    ui->AddMove(line_buff, sizeof(line_buff));

    return success;
}
