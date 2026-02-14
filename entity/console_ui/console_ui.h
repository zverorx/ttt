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
 * @enum field_size
 * @brief The size of the playing field.
 */
enum field_size { row_count = 3, col_count = 3 };

/**
 * @enum print_mode
 * @brief Print the active game or its finish.
 * @see ConsoleUI::PrintUI
 */
enum print_mode { active, finish };

/**
 * @class ConsoleUI
 * @brief Manages the display of the game panel and playing field.
 */
class ConsoleUI {
private:
    char field[row_count][col_count];   /**< Playing field          */
    const char default_fill;            /**< Default cell content   */

    int output_lines;                   /**< Lines printed to stdout*/
    const int panel_lines;              /**< Lines in info panel    */
    const int field_lines;              /**< Lines in playing field */
    const int separator_lines;          /**< Lines in separator     */
public:
    ConsoleUI();

    /**
     * @brief Prints the complete interface.
     * @param md Display mode (active game or finished game).
     * @param winner Pointer to the winner player (NULL for draw).
     */
    void PrintUI(print_mode md = active, const Player *winner = 0);

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
    void ClearUI();

    /**
     * @brief Checks if the cell is occupied and returns its mark.
     * @param rowi Row index (0 to row_count-1).
     * @param coli Column index (0 to col_count-1).
     * @param[out] mark Reference to store the cell's mark.
     * @return true If cell is occupied.
     * @return false If coordinates invalid (mark = '\0') or cell is free.
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
    /**
     * @brief Prints the start panel with game instructions and commands.
     * 
     * Displays title, movement instructions, and available commands.
     * Updates output line counter.
     */
    void PrintStartPanel();

    /**
     * @brief Prints the end panel with game results.
     * 
     * Displays game over message and winner information.
     * If winner is NULL, displays draw message.
     * Updates output line counter.
     * 
     * @param winner Pointer to the winning player (NULL for draw).
     */
    void PrintEndPanel(const Player *winner = 0);

    /**
     * @brief Prints the playing field with current marks.
     * 
     * Updates output line counter.
     */
    void PrintField();

    /**
     * @brief Prints a separator line between panel and field.
     * 
     * Updates output line counter.
     */
    void PrintSeparator();
};

#endif /* CONSOLE_UI_H_SENTRY */
