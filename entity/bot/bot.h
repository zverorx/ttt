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

#ifndef BOT_H_SENTRY
#define BOT_H_SENTRY

#include "../console_ui/console_ui.h"
#include "../player/player.h"
#include "../player_i.h"

class Bot : public Player {
private:
    /**
     * @enum stat_size 
     * @brief One of the sizes for Bot::move_stat
     * 
     * 3 rows + 3 columns + 2 diagonals = 8
     */
    enum stat_size { direction_count = 8 };

    /**
     * @enum stat_i
     * @brief Indexes for Bot::move_stat
     * @see enum stat_size
     */
    enum stat_i {
        row0, row1, row2,
        col0, col1, col2,
        d0, d1
    };

    const ConsoleUI *ui;
    int move_stat[direction_count][player_count];

public:
    Bot(const char *nickname, char mark);
    void Move(const ConsoleUI &ui, int &rowi, int &coli);

private:
    void StatDeterm(); 
    bool NeedRandomMove() const;
    void RandomMove(int &rowi, int &coli) const;
};

#endif /* BOT_H_SENTRY */
