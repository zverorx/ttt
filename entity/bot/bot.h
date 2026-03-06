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

/**
 * @class Bot
 * @brief The computer-controlled participant of the game.
 */
class Bot : public Player {
private:
    /**
     * @enum field_line 
     * @brief All lines of the 3x3 field.
     * 
     * @see Bot::move_stat
     */
    enum field_line {
        row0, row1, row2,
        col0, col1, col2,
        d0, d1,
        line_count = 8
    };

    /**
     * @brief Used to generate Bot::move_stat based 
     *        on the current playing field.
     */
    const ConsoleUI *ui;

    /**
     * @brief Statistics of marks on the playing field.
     * 
     * First index: player (bot or man).
     * Second index: line (row, column or diagonal).
     * Value: number of marks in that line.
     * 
     * @see enum player_i (first index)
     * @see Bot::field_line (second index)
     */
    int move_stat[player_count][line_count];

public:
    Bot(const char *nickname, char mark);

    /**
     * @brief Generates the bot's next move based on current field state.
     * 
     * @param ui Game interface for field access.
     * @param[out] rowi Selected row.
     * @param[out] coli Selected column.
     */
    void Move(const ConsoleUI &ui, int &rowi, int &coli);

private:
    /**
     * @brief Determines move statistics by scanning the current field.
     * 
     * Counts marks for bot and opponent in each row, column and diagonal.
     * Results are stored in Bot::move_stat array.
     */
    void StatDeterm();

    /**
     * @brief Checks whether the current move is the first one.
     * 
     * @return true if no bot marks on the game field, false otherwise.
     */
    bool IsFirstMove() const;

    /**
     * @brief Checks whether the bot can win in the current move.
     * 
     * @param[out] line The line where winning move is possible.
     * @return true if winning move exists, false otherwise.
     * 
     * @note If return value is false, line contains invalid data.
     */
    bool IsCurrentMoveWin(field_line &line) const;

    /**
     * @brief Checks whether the opponent can win in the next move.
     * 
     * @param[out] line The line that needs to be blocked.
     * @return true if opponent has a winning threat, false otherwise.
     * 
     * @note If return value is false, line contains invalid data.
     */
    bool IsNextMoveLoss(field_line &line) const;

    /**
     * @brief Generates a random free cell on the field.
     * 
     * @param[out] rowi Selected row.
     * @param[out] coli Selected column.
     * 
     * @warning Randomly picks coordinates until an empty cell is found.
     */
    void RandomMove(int &rowi, int &coli) const;

    /**
     * @brief Finds a free cell in the specified line.
     * 
     * @param[out] rowi Selected row.
     * @param[out] coli Selected column.
     * @param line The line to search for a free cell.
     * 
     * @note If no free cell in the line, output values are undefined.
     */
    void FillLine(int &rowi, int &coli, field_line line);
};

#endif /* BOT_H_SENTRY */
