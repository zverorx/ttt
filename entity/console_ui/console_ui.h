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

#ifndef CONSOLE_UI_H_SENTRY
#define CONSOLE_UI_H_SENTRY

#include "../player/player.h"

/**
 * @def GAMEPALY_SIZE
 * @brief ConsoleUI::gameplay size
 */
#define GAMEPLAY_SIZE   10

/**
 * @enum field_size
 * @brief The size of the playing field.
 */
enum field_size { row_count = 3, col_count = 3 };

/**
 * @enum panel_version
 * 
 * @brief Available panel display modes.
 * 
 * @var info Initial information panel.
 * @var game_time Active game panel expecting move.
 * @var input_error Game panel with input error message.
 * @var busy_error Game panel with busy cell message.
 * @var game_over Final panel showing winner.
 * 
 * @see Console::Print
 */
enum panel_version { info, game_time, input_error, busy_error, game_over };

/**
 * @class ConsoleUI
 * @brief Rendering of info panels, playing field, and player moves.
 */
class ConsoleUI {
private:
    char field[row_count][col_count];   /**< Playing field          */
    const char default_fill;            /**< Default cell content   */
    char *gameplay[GAMEPLAY_SIZE];      /**< Description of each move */

    int output_lines;                   /**< Lines printed to stdout*/
    const int panel_lines;              /**< Lines in info panel    */
    const int field_lines;              /**< Lines in playing field */
    const int separator_lines;          /**< Lines in separator     */
public:
    ConsoleUI();
    ~ConsoleUI();

    /**
     * @brief Prints the complete game interface.
     * @param v Panel version to display.
     * @param p Pointer to player (can be NULL for default message).
     * 
     * Combines panel, separator and field into single output.
     * Updates output line counter.
     */
    void Print(panel_version v, const Player *p = 0);

    /**
     * @brief Clears all previously printed interface lines from console.
     * 
     * Moves cursor up and clears each line that was printed in previous output.
     * Resets output line counter to zero after clearing.
     * 
     * @note This function uses ANSI escape codes:
     *       \033[2K – Clear entire line
     *       \033[1A – Move cursor up one line
     */
    void Clear();

    /**
     * @brief Adds a move description to history.
     * @param str Source string (null-terminated).
     * @param len Number of characters to copy.
     * @return true if added successfully, false otherwise.
     */
    bool AddMove(const char *str, size_t len);

    /**
     * @brief Deletes a move from history by index.
     * @param index Position in gameplay array.
     * @return true if deleted successfully, false otherwise.
     */
    bool DeleteMove(int index);

    /**
     * @brief Deletes all moves from history.
     */
    void DeleteAllMove();

    /**
     * @brief Checks if the cell is occupied and returns its mark.
     * @param rowi Row index (0 to row_count-1).
     * @param coli Column index (0 to col_count-1).
     * @param[out] mark Reference to store the cell's mark.
     *                  If coordinates are invalid, mark = '\0'.
     * @return true If cell is occupied or coordinates are invalid.
     * @return false If cell is free.
     */
    bool IsBusy(int rowi, int coli, char &mark) const;

    /**
     * @brief Sets player's mark at specified cell.
     * @param rowi Row index (0 to row_count-1).
     * @param coli Column index (0 to col_count-1).
     * @param p Player whose mark will be placed.
     * @return true If coordinates valid and mark set.
     * @return false If coordinates out of range.
     */
    bool SetMark(int rowi, int coli, const Player &p);

    /**
     * @brief Clears player's mark at specified cell.
     * @param rowi Row index (0 to row_count-1).
     * @param coli Column index (0 to col_count-1).
     * @return true If coordinates valid and mark cleared.
     * @return false If coordinates out of range.
     */
    bool ClearMark(int rowi, int coli);

    /**
     * @brief Resets all field cells to default fill character.
     */
    void ClearField();

private:
    ConsoleUI(ConsoleUI &ui);
    void operator=(ConsoleUI &ui);

    /**
     * @brief Prints the info panel according to specified version.
     * @param v Panel version to display.
     * @param p Pointer to player whose nickname will be shown.
     * 
     * Available panels:
     * - info: Initial screen with first player info
     * - game_time: Active game screen expecting player's move
     * - game_time_error: Same as game_time but with error message
     * - game_over: Final screen with winner info
     * 
     * If p is NULL, displays default message.
     * Updates output line counter.
     */
    void PrintPanel(panel_version v, const Player *p = 0);

    /**
     * @brief Prints a separator line between panel and field.
     * 
     * Updates output line counter.
     */
    void PrintSeparator();

    /**
     * @brief Prints the playing field with current marks.
     * 
     * Updates output line counter.
     */
    void PrintField();

    /**
     * @brief Prints the gameplay history.
     * 
     * Updates output line counter.
     */
    void PrintGameplay();
};

#endif /* CONSOLE_UI_H_SENTRY */
