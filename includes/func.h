/**
 * @file func.h
 * @brief Constants and function headers for the game tic-tac-toe.
 * 
 * @author Zveror
 * @data September 2025
 */

#ifndef FUNC_H_SENTRY
#define FUNC_H_SENTRY

/* ========================================================================== */
/*                                Enums                                       */
/* ========================================================================== */

/* @brief Represents the result of user input processing.
 *
 * Used by input_processing() to indicate whether the user entered:
 * - Game coordinates (COORDINATES),
 * - A control command (QUIT, RENAME, RESTART),
 * - Or invalid/unreadable input (ERROR).
 */
typedef enum {
	COORDINATES,
	ERROR,
	QUIT			= 'q',
	RENAME			= 'n',
	RESTART			= 'r'
} input_data;

/* ========================================================================== */
/*                                Includes                                    */
/* ========================================================================== */
#include "structs.h"

/* ========================================================================== */
/*                                Constants                                   */
/* ========================================================================== */

/* The number of lines that the program's stdout occupies */
#define NUM_OF_LINES		20

/* ========================================================================== */
/*                                Headers                                     */
/* ========================================================================== */

/**
 * @brief Print game field to stdout.
 * @param game_ptr Pointer to the game structure.
 * @return void.
 */
void print_game_field(struct game *game_ptr);

/**
 * @brief Initializes a new game instance with default settings.
 *
 * Allocates and initializes the main game structure, two players,
 * an empty game field, and a head node for the list of used cells.
 *
 * @return Pointer to the initialized game structure on success, NULL on memory allocation failure.
 */
struct game *init_game();

/**
 * @brief Frees all memory associated with the game.
 * @param game_ptr Pointer to the game structure (may be NULL).
 */
void destroy_game(struct game *game_ptr);

/**
 * @brief Reads and parses user input: either coordinates (row col) or a single-letter command.
 *        On success with coordinates, writes them to `row` and `col`.
 *        On command input ('q', 'n', 'r'), returns corresponding enum value.
 *        If input is invalid or unreadable, returns ERROR.
 *
 * @return COORDINATES — valid row/col parsed.
 *         ERROR       — failed to read or parse input.
 *         QUIT        — user typed 'q'.
 *         RENAME      — user typed 'n'.
 *         RESTART     — user typed 'r'.
 */
input_data input_processing(char *buff, size_t buff_size, int *row, int *col, const char *nickname);

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

/**
 * @brief Fills current cell and appends a new one to the used cell list.
 *
 * Stores row and col in curr_uc_ptr, allocates a new node, links it, and returns the new node.
 * Returns NULL on allocation failure or if curr_uc_ptr is NULL.
 *
 * @param curr_uc_ptr Pointer to current used cell (must be valid).
 * @param row         Row index to record.
 * @param col         Column index to record.
 * @return            Pointer to new node, or NULL on error.
 */
struct used_cell *remember_used_cell(struct used_cell *curr_uc_ptr, int row, int col);

/**
 * @brief Prompts the user to enter a new nickname and updates the player's name.
 *
 * Reads input from stdin, trims the trailing newline, and safely copies
 * the result into the player's nickname field. Cleans console after input.
 * Does nothing if fgets fails.
 *
 * @param curr_player Pointer to the player structure to update (must not be NULL).
 */
void handle_rename(struct player *curr_player);

#endif /* FUNC_H_SENTRY */
