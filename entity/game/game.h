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

class Game {
private:
    Player *p1, *p2, *curr_p;
    ConsoleUI *ui;
    Terminal *terminal;
    const char prompt;

public:
    Game();
    ~Game();

    void Start();
private:
    Game(Game &g);
    void operator=(Game &g);

    void Intro() const;
    bool PromptHandle(int move_count, int &rowi, 
                      int &coli, int color_code) const;
};

#endif /* GAME_H_SENTRY */
