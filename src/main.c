/**
 * Developer: Zveror
 * September 2025
 */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "structs.h"

/**
 * @brief Error check with cleanup.
 * @param OBJECT Object to check (pointer or int).
 * @param TYPE   'p' for pointer (non-NULL expected), 'i' for int (0 expected).
 * @param ERROR  Return value on error.
 * 
 * Calls destroy_game(game_ptr) and returns ERROR if check fails.
 * Requires 'game_ptr' to be in scope.
 */
#define CHECK_ERROR(OBJECT, TYPE, ERROR)\
	do {\
		if((TYPE == 'p' && !(OBJECT)) ||\
		   (TYPE == 'i' && (OBJECT))) {\
			destroy_game(game_ptr);\
			return ERROR;\
		}\
	} while(0)

/**
 * @enum errors
 * @brief Error codes returned by the program.
 */
enum errors {
	SUCCESS				= 0, /*< No error. */
	MEMORY_ALLOC_ERR	= 1, /*< Memory allocation error */
	INPUT_ERR			= 2  /*< Data entry error */
};

/* Local headers */
static void print_game_field(struct game *game_ptr);
static struct game *init_game();
static void destroy_game(struct game *game_ptr);
static int8_t input_processing(char *buff, int8_t *row, int8_t *col, char *nickname);
static void clean_output();

int main(int argc, char **argv)
{
	char buff[64];
	int8_t row, col, res_input;

	struct game *game_ptr = init_game();
	CHECK_ERROR(game_ptr, 'p', MEMORY_ALLOC_ERR);

	/* TODO: Completing the cycle, accounting for used cells */
	while(game_is_not_over) {
		print_game_field(game_ptr);
		res_input = input_processing(buff, &row, &col, game_ptr->player_1->nickname);
		CHECK_ERROR(res_input, 'i', INPUT_ERR);

		game_ptr->field[row][col] = game_ptr->player_1->mark;
		clean_output();
	}

	destroy_game(game_ptr);
	return SUCCESS;
}

/**
 * @brief Print game field to stdout.
 * @param game_ptr Pointer to the game structure.
 * @return void.
 */
static void print_game_field(struct game *game_ptr)
{
	printf("    0   1   2\n");
	printf("   ___ ___ ___\n");
	printf("0 |_%c_|_%c_|_%c_|\n", game_ptr->field[0][0], game_ptr->field[0][1], game_ptr->field[0][2]);
	printf("1 |_%c_|_%c_|_%c_|\n", game_ptr->field[1][0], game_ptr->field[1][1], game_ptr->field[1][2]);
	printf("2 |_%c_|_%c_|_%c_|\n", game_ptr->field[2][0], game_ptr->field[2][1], game_ptr->field[2][2]);
	putc('\n', stdout);
}

/**
 * @brief Initializes a new game instance with default settings.
 *
 * Allocates and initializes the main game structure, two players,
 * an empty game field, and a head node for the list of used cells.
 *
 * @return Pointer to the initialized game structure on success, NULL on memory allocation failure.
 */
static struct game *init_game()
{
	struct player *p1_ptr = NULL, *p2_ptr = NULL;
	struct used_cell *us_ptr = NULL;
	struct game *game_ptr = NULL;

	/* Create main structure */
	game_ptr = calloc(1, sizeof(struct game));
	if(!game_ptr) {
		goto exit;
	}

	/* Create players and list of used cells */
	p1_ptr = calloc(1, sizeof(struct player));
	if(!p1_ptr) {
		goto exit;
	}
	p2_ptr = calloc(1, sizeof(struct player));
	if(!p2_ptr) {
		goto exit;
	}
	us_ptr = calloc(1, sizeof(struct used_cell));
	if(!us_ptr) {
		goto exit;
	}

	/* Define default nicknames and marks for players */
	snprintf(p1_ptr->nickname, sizeof(p1_ptr->nickname), "Player_1");
	p1_ptr->mark = 'X';
	snprintf(p2_ptr->nickname, sizeof(p2_ptr->nickname), "Player_2");
	p2_ptr->mark = 'O';

	/* Assigning fields to the used_cell structure */
	us_ptr->next = NULL;

	/* Assigning fields to the game structure */
	game_is_not_over = 1;
	game_ptr->used_cells_head = us_ptr;
	game_ptr->player_1 = p1_ptr;
	game_ptr->player_2 = p2_ptr;
	for(int i = 0; i < MAX_ROW; i++) {
		for(int j = 0; j < MAX_COLUMN; j++) {
			game_ptr->field[i][j] = '_';
		}
	}

	return game_ptr;

exit:
	free(game_ptr);
	free(p1_ptr);
	free(p2_ptr);
	free(us_ptr);
	return NULL;
}

/**
 * @brief Frees all memory associated with the game.
 * @param game_ptr Pointer to the game structure (may be NULL).
 */
static void destroy_game(struct game *game_ptr)
{
	struct used_cell *current = NULL;

	if(!game_ptr) {
		return;
	}

	current = game_ptr->used_cells_head;
	while(current) {
		struct used_cell *next = current->next;
		free(current);
		current = next;
	}

	free(game_ptr->player_1);
	free(game_ptr->player_2);

	free(game_ptr);

	return;
}

/**
 * @brief Processes data received on stdin.
 *
 * Calls fgets, then parses the resulting data using sscanf. 
 * Expects two numbers in the range [0,2] (row, collumn).
 *
 * @param buff The buffer into which the line from stdin is written.
 * @param row Pointer to which the line number will be written upon successful input.
 * @param col Pointer to which the column number will be written upon successful input.
 * @param nickname Nickname of the player from whom the input is received.
 * @return 0 if success, 1 if error fgets, 2 if error sscanf. 
 */
static int8_t input_processing(char *buff, int8_t *row, int8_t *col, char *nickname)
{
	int res_sscanf;
	char *res_fgets;

	printf("%s: ", nickname);
	res_fgets = fgets(buff, sizeof(buff), stdin);
	if(!res_fgets) {
		return 1;
	}

	res_sscanf = sscanf(buff, "%hhd %hhd", row, col);
	if (res_sscanf != 2 ||
		*(row) < 0 || *(row) >= MAX_ROW ||
		*(col) < 0 || *(col) >= MAX_COLUMN) {
		return 2;
	}

	return 0;
}

/**
 * @brief Clears the previous 7 lines in the terminal.
 *
 * Moves the cursor up line by line, starting from the current position,
 * and erases each line's content using ANSI escape sequences.
 * Assumes that at least 7 lines were previously printed.
 *
 * @note This function uses ANSI escape codes:
 *       \r      – Carriage return (to start of line)
 *       \033[2K – Clear entire line
 *       \033[A  – Move cursor up one line
 *
 * @warning Behavior is undefined if fewer than 7 lines were printed.
 * 
 */
static void clean_output()
{
	printf("\r\033[2K\033[A");
	for (int i = 0; i < 6; i++) {
		printf("\033[2K\033[A");
	}
	fflush(stdout);
}
