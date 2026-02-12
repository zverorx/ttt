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
#include <stdlib.h>

#include "player.h"

Player::Player(char *nickname, char mark)
{
    this->nickname = nickname;
    this->mark = mark;
}

Player::Player(const Player &p)
{
    nickname = strdup(p.nickname);
    if (!nickname) { throw "Bad argument"; }

    mark = p.mark;
}

Player::~Player()
{
    if (nickname) { free(nickname); }
}

void Player::operator=(const Player &p)
{
    if (this == &p) { return; }

    if (nickname) { free(nickname); }

    nickname = strdup(p.nickname);
    if (!nickname) { throw "Bad argument"; }

    mark = p.mark;
}

Player *Player::Create(const char *nickname, const char mark)
{
    if (!nickname) { return 0; }

    if (mark < 'A' || mark > 'Z') { return 0; }

    char *nickname_dup = strdup(nickname);
    if (!nickname_dup) { return 0; }

    return new Player(nickname_dup, mark);
}

const char *Player::GetNickname() const
{
    const char *nickname = this->nickname;
    return nickname;
}

char Player::GetMark() const
{
    return mark;
}

bool Player::SetNickname(const char *nickname)
{
    if (!nickname) { return false; }
    free(this->nickname);

    this->nickname = strdup(nickname);
    if (!this->nickname) { return false; }

    return true;
}

bool Player::SetMark(const char mark)
{
    if (mark < 'A' || mark > 'Z') { return false; }

    this->mark = mark;

    return true;
}
