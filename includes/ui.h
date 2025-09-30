/**
 * @file ui.h
 * @brief Function headers for user interface.
 *
 * @author zverorx
 * @data September
 */

#ifndef UI_H_SENTRY
#define UI_H_SENTRY

/* ========================================================================== */
/*                                Includes                                    */
/* ========================================================================== */

#include "types.h"

/* ========================================================================== */
/*                                Headers                                     */
/* ========================================================================== */

/**
 * @brief Prints the game result message (win or draw).
 *
 * @param status    Game result: RGO_WIN or RGO_DRAW.
 * @param plr       Pointer to the winning player (ignored for draw).
 */
void print_game_over(ret_game_over status, struct player *plr);

/**
 * @brief Print game field to stdout.
 * @param game_ptr Pointer to the game structure.
 * @return void.
 */
void print_game_field(struct game *game_ptr);

/**
 * @brief Clears the previous N lines in the terminal.
 *
 * Moves the cursor up line by line, starting from the current position,
 * and erases each line's content using ANSI escape sequences.
 * 
 * @param rows Number of lines to clear in terminal.
 * @note This function uses ANSI escape codes:
 *       \r      – Carriage return (to start of line)
 *       \033[2K – Clear entire line
 *       \033[A  – Move cursor up one line
 */
void clean_output(int rows);

#endif /* UI_H_SENTRY */
