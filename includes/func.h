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

/**
 * @enum errors
 * @brief Error codes returned by the program.
 */
enum errors {
	SUCCESS				= 0, /*< No error. */
	MEMORY_ALLOC_ERR	= 1, /*< Memory allocation error */
	INPUT_ERR			= 2  /*< Data entry error */
};

/**
 * @brief Return codes for game-over status.
 */
typedef enum {
	RGO_ERROR		= -1,
	RGO_WIN			= 1,
	RGO_DRAW		= 2
} ret_game_over;

/* @brief Represents the result of user input processing.
 *
 * Used by input_processing() to indicate whether the user entered:
 * - Game coordinates (COORDINATES),
 * - A control command (QUIT, RENAME, RESTART),
 * - Or invalid/unreadable input (ERROR).
 */
typedef enum {
	INP_D_COORDINATES,
	INP_D_ERROR,
	INP_D_QUIT			= 'q',
	INP_D_RENAME		= 'n',
	INP_D_RESTART		= 'r'
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
 * @brief Prints the game result message (win or draw).
 *
 * @param status    Game result: RGO_WIN or RGO_DRAW.
 * @param plr       Pointer to the winning player (ignored for draw).
 */
void print_game_over(ret_game_over status, struct player *plr);

/**
 * @brief Checks if the current player has won or if the game is a draw.
 *
 * Scans rows, columns, and diagonals for 3 matching marks.
 * Also checks if any free cells remain to determine a draw.
 *
 * @param game_ptr      Pointer to the game state (must not be NULL).
 * @param curr_player   Pointer to the current player (must not be NULL).
 *
 * @return RGO_WIN if current player won, RGO_DRAW if no moves left, 0 otherwise.
 */
ret_game_over check_game_over(struct game *game_ptr, struct player *curr_player);

/**
 * @brief Handles a player's move on the game board.
 *
 * Places the current player's mark if the cell is empty.
 * Records the move, checks for win/draw, and switches player.
 * Exits on memory allocation failure.
 *
 * @param game_ptr      Pointer to the game state (must not be NULL).
 * @param curr_uc_ptr   Pointer to the current used cell pointer (updated after move).
 * @param curr_player   Pointer to the current player pointer (switched after move).
 * @param row           Target row (0-based).
 * @param col           Target column (0-based).
 */
void handle_move(struct game *game_ptr, 
				 struct used_cell **curr_uc_ptr, 
				 struct player **curr_player, int row, int col);

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
