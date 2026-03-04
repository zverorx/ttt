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

#ifndef GAME_H_SENTRY
#define GAME_H_SENTRY

#include "../player/player.h"
#include "../console_ui/console_ui.h"
#include "../terminal/terminal.h"

enum player_i { man = 0, bot = 1, count = 2 };

typedef enum player_move {
    success         = 0,
    invalid_input   = 1,
    cell_is_busy    = 2,
    quit            = 3,
    restart         = 4
} pmove_t;

class Game {
private:
    Player *plr[count];
    ConsoleUI *ui;
    Terminal *terminal;
    const char prompt;

public:
    Game();
    ~Game();

    pmove_t Start();
    void Reset();

private:
    Game(Game &g);
    void operator=(Game &g);

    player_i Intro() const;
    pmove_t ProcessPlayerMove(int move_count, int &rowi, 
                              int &coli, int color_code) const;
};

#endif /* GAME_H_SENTRY */
