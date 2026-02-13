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

#include <string.h>

#include "player.h"

Player::Player(const char *nickname, char mark)
    : nickname()
    , mark(mark)
{
    if (!nickname) { throw "Bad nickname"; }
    if ((mark < 33 || mark > 126)) { throw "Bad mark"; }

    strncpy(this->nickname, nickname, sizeof(this->nickname));
    this->nickname[sizeof(this->nickname) - 1] = '\0';
}

const char *Player::GetNickname() const
{
    return nickname;
}

char Player::GetMark() const
{
    return mark;
}

bool Player::SetNickname(const char *nickname)
{
    if (!nickname) { return false; }

    memset(this->nickname, 0, sizeof(this->nickname));
    strncpy(this->nickname, nickname, sizeof(this->nickname));
    this->nickname[sizeof(this->nickname) - 1] = '\0';

    return true;
}

bool Player::SetMark(char mark)
{
    if ((mark < 33 || mark > 126)) { return false; }

    this->mark = mark;

    return true;
}
