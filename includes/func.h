/**
 * @file func.h
 * @brief Constants and function headers for the game tic-tac-toe.
 * 
 * @author Zveror
 * @data September 2025
 */

#ifndef FUNC_H_SENTRY
#define FUNC_H_SENTRY

/* Includes */
#include "structs.h"

/* ========================================================================== */
/*                                Constants                                   */
/* ========================================================================== */

/* The number of lines that the program's stdout occupies */
#define NUM_OF_LINES	11

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
 * @brief Processes data received on stdin.
 *
 * Calls fgets, then parses the resulting data using sscanf. 
 * Expects two numbers in the range [0,2] (row, column).
 *
 * @param buff		The buffer into which the line from stdin is written.
 * @param buff_size	Size of buffer from first parameter. 
 * @param row		Pointer to which the line number will be written upon successful input.
 * @param col		Pointer to which the column number will be written upon successful input.
 * @param nickname 	Nickname of the player from whom the input is received.
 * @return 0 if success, 1 if error fgets, 2 if error sscanf. 
 */
int input_processing(char *buff, size_t buff_size, int *row, int *col, char *nickname);

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
#endif
