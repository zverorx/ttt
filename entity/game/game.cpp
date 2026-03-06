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

Game::Game()
    : prompt('>')
{
    passwd *pw = getpwuid(geteuid());
    plr[man] = pw ? new Player(pw->pw_name, 'X') : new Player("Player", 'X');

    plr[bot] = new Bot("><[O_O]><", 'O');
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

Game::pmove_t Game::Start()
{
    int rowi, coli, curr_plr_i;
    pmove_t res_move;

    terminal->DisableICanon(0, 1);
    terminal->DisableEcho();

    curr_plr_i = Intro();

    terminal->DisableICanon(0, 4);
    terminal->EnableEcho();

    for (int i = 0, move = 0, swtch = 0; ; i++, curr_plr_i = !curr_plr_i) {
        ui->Print(ConsoleUI::game_time, plr[curr_plr_i]);

        swtch = !swtch;
        if (swtch) { move++; }

        for (bool run = true; run;) {
            res_move = ProcessPlayerMove(move, rowi, coli, 
                                         static_cast<player_i>(curr_plr_i));
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
                    ui->Print(ConsoleUI::input_error, plr[curr_plr_i]);
                    break;
                case cell_is_busy:
                    ui->Clear(); 
                    ui->Print(ConsoleUI::busy_error, plr[curr_plr_i]);
                    break;
                case out_of_range:
                    ui->Clear(); 
                    ui->Print(ConsoleUI::range_error, plr[curr_plr_i]);
                    break;
            }
        }

        ui->Clear();

        int cgo_res = CheckGameOver(static_cast<player_i>(curr_plr_i));
        if (cgo_res == win) {
            ui->Print(ConsoleUI::game_over, plr[curr_plr_i]);
            return quit;
        }
        else if (cgo_res == draw) {
            ui->Print(ConsoleUI::game_over);
            return quit;
        }
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

    plr[bot] = new Bot("><[O_O]><", 'O');
    ui = new ConsoleUI();
    terminal = new Terminal();
}

const ConsoleUI &Game::GetUI() const
{
    return *ui;
}

player_i Game::Intro() const
{
    char buff[80];
    player_i first_plr_indx;
    int rnd;

    srand(time(0));
    rnd = rand();
    first_plr_indx = rnd % 2 ? man : bot;

    ui->Print(ConsoleUI::info, plr[first_plr_indx]);

    printf("%c PRESS ANY TO START...", prompt);
    getc(stdin);
    fputs("\r\033[2K", stdout);
    fflush(stdout);

    snprintf(buff, sizeof(buff), "0%c START", prompt);
    ui->AddMove(buff, sizeof(buff));

    ui->Clear();

    return first_plr_indx;
}

Game::pmove_t Game::ProcessPlayerMove(int move_count, int &rowi, 
                                int &coli, player_i plr_i ) const
{
    enum color { red = 31, blue = 34};

    char line_buff[80];
    char input_buff[10];
    color clr = plr_i ? red : blue;

    memset(line_buff, 0, sizeof(line_buff));
    memset(input_buff, 0, sizeof(input_buff));

    printf("\033[%dm%d%c\033[0m ", clr, move_count, prompt);
    fflush(stdout);

    if (plr_i == bot) { BotHandle(rowi, coli, input_buff, sizeof(input_buff)); }
    else { read(STDIN_FILENO, input_buff, sizeof(input_buff)); }

    char *p = input_buff;
    while ((p = strchr(p, '\n')) != 0) {
        fputs("\033[2K\033[1A", stdout);
        p++;
    }
    fputc('\n', stdout);

    if (strcmp("quit", input_buff) == 0) { return quit; }
    if (strcmp("rest", input_buff) == 0) { 
        fputs("\033[1A", stdout);
        return restart;
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
             clr, move_count, prompt, rowi, coli);
    ui->AddMove(line_buff, sizeof(line_buff));

    return success;
}

Game::game_over_stat Game::CheckGameOver(player_i curr_plr_i)
{
	int count, has_free_cells = 0;
	char curr_mark = plr[curr_plr_i]->GetMark();
    char mark;

	/* Check by rows */
	for(int i = 0; i < ConsoleUI::row_count; i++) {
		count = 0;
		for(int j = 0; j < ConsoleUI::col_count; j++) {
			if(ui->IsBusy(i, j, mark)) {
                if (mark == curr_mark) { count++; }
            }
            else { has_free_cells = 1; }
			if(count == 3) { return win; }
		}
	}

	/* Check by columns */
	for(int i = 0; i < ConsoleUI::row_count; i++) {
		count = 0;
		for(int j = 0; j < ConsoleUI::col_count; j++) {
			if(ui->IsBusy(j, i, mark)) {
                if (mark == curr_mark) { count++; }
            }
            else { has_free_cells = 1; }
			if(count == 3) { return win; }
		}
	}

	/* Main diagonal */
	for(int i = 0, count = 0; i < ConsoleUI::row_count; i++) {
        if(ui->IsBusy(i, i, mark)) {
            if (mark == curr_mark) { count++; }
        }
        else { has_free_cells = 1; }
        if(count == 3) { return win; }
	}

	/* Secondary diagonal */
	for(int i = 0, count = 0; i < ConsoleUI::row_count; i++) {
        if(ui->IsBusy(i, 2 - i, mark)) {
            if (mark == curr_mark) { count++; }
        }
        else { has_free_cells = 1; }
        if(count == 3) { return win; }
	}

	/* Checking a draw */
	if(!has_free_cells) { return draw; }

	return absent; 
}

void Game::BotHandle(int &rowi, int &coli, char *buff, size_t size) const
{
    if (size < 4) { return; }

    static_cast<Bot *>(plr[bot])->Move(GetUI(), rowi, coli);

    terminal->DisableEcho();

    sleep(1);
    printf("%d", rowi);
    fflush(stdout);

    sleep(1);
    printf(" %d", coli);
    fflush(stdout);

    sleep(1);

    terminal->EnableEcho();

    tcflush(STDIN_FILENO, TCIFLUSH);

    buff[0] = 48 + rowi;
    buff[1] = ' ';
    buff[2] = 48 + coli;
    buff[3] = 0;
}
