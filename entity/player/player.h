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

#ifndef PLAYER_H_SENTRY
#define PLAYER_H_SENTRY

/**
 * @class Player
 * @brief The participant of the game. 
 */
class Player {
private:
    char nickname[33];
    char mark; /* [33;126] (printable ASCII) */

public:
    /**
     * @param nickname Must not be NULL.
     * @param mark Any other than control characters.
     *             Use code [33;126] (printable ASCII).
     * 
     * @throws const char * on invalid arguments.
     */
    Player(const char *nickname, char mark);

    const char *GetNickname() const;
    char GetMark() const;
    bool SetNickname(const char *nickname);
    bool SetMark(char mark);
};

#endif /* PLAYER_H_SENTRY */
