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
#include "../bot/bot.h"
#include "../console_ui/console_ui.h"
#include "../terminal/terminal.h"

/**
 * @enum player_i
 * @brief Indexes for the array of players. 
 * @see Game::plr
 */
enum player_i { man = 0, bot = 1, count = 2 };

/**
 * @enum player_move
 * @brief User input result.
 * 
 * @see Game::ProcessPlayerMove
 * @see Game::Start
 */
typedef enum player_move {
    success         = 0,
    invalid_input   = 1, 
    cell_is_busy    = 2,
    out_of_range    = 3,
    quit            = 4, /**< Useful for Game::Start */
    restart         = 5  /**< Useful for Game::Start */
} pmove_t;

/**
 * @enum game_over_stat
 * @brief Game over status codes
 * 
 * @var win    Game is won by current player.
 * @var draw   Game ended in a draw.
 * @var absent Game is still in progress.
 */
enum game_over_stat { win, draw, absent };

/**
 * @class Game
 * @brief The main class on gameplay management. 
 */
class Game {
private:
    Player *plr[count]; /**< The participants of the game */
    ConsoleUI *ui;      /**< Interface rendering */
    Terminal *terminal; /**< Setting up a terminal session */

    const char prompt;  /**< A symbol indicating an input prompt */

public:
    Game();
    ~Game();

    /**
     * @brief Starting the main game loop.
     * 
     * @return pmove_t::quit If the user decides to log out. 
     * @return pmove_t::restart If the user decides to restart 
     */
    pmove_t Start();

    /**
     * @brief Reset the internal state.
     * 
     * Called when Game::Start returns restart.
     */
    void Reset();

    const ConsoleUI &GetUI() const;

private:
    Game(Game &g);
    void operator=(Game &g);

    /**
     * @brief Displaying the information panel with the first player.
     * 
     * The first player is determined randomly with a 50% probability.
     * 
     * @return player_i Index of the first player.
     */
    player_i Intro() const;

    /**
     * @brief Processing player input.
     * 
     * Handles commands and various error cases. 
     * If the input is successful, the prompt string is saved in ConsoleUI.
     *
     * @param move_count Current move number (for display).
     * @param[out] rowi  Selected row (if input valid).
     * @param[out] coli  Selected column (if input valid).
     * @param plr_i Index of the current player.
     * 
     * @return pmove_t Input result: success, errors, or commands.
     */
    pmove_t ProcessPlayerMove(int move_count, int &rowi, 
                              int &coli, player_i plr_i) const;

    /**
     * @brief Checks if the game is over for current player
     * 
     * @param curr_plr_i Index of current player
     * @return game_over_stat Game status: win, draw, or absent
     */
    game_over_stat CheckGameOver(player_i curr_plr_i);

    /**
     * @brief Handles bot move generation and formats result into buffer.
     * 
     * @param rowi Reference to store bot's chosen row coordinate.
     * @param coli Reference to store bot's chosen column coordinate.
     * @param buff Output buffer for formatted move string "row col\0".
     * @param size Size of the output buffer (must be at least 4).
     * 
     * @note Terminal echo is temporarily disabled during coordinate display.
     * @note Input buffer is flushed after displaying coordinates.
     */  
    void BotHandle(int &rowi, int &coli, char *buff, size_t size) const;
};

#endif /* GAME_H_SENTRY */
