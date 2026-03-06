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

#ifndef PLAYER_I_H
#define PLAYER_I_H

/**
 * @enum player_i
 * @brief Indexes for the array of players.
 * 
 * @see Game::plr
 * @see Bot::move_stat
 */
enum player_i { man = 0, bot = 1, player_count = 2 };

#endif /* PLAYER_I_H */
