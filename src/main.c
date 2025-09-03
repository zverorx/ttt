/**
 * Developer: Zveror
 * September 2025
 */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

/* The number of lines that the program's stdout occupies */
#define NUM_OF_LINES	7

/**
 * @brief Error check with cleanup.
 * @param OBJECT	Object to check (pointer or int).
 * @param TYPE		'p' for pointer (non-NULL expected), 'i' for int (0 expected).
 * @param GAME		Game structure to destroy on error. May be NULL.
 * @param ERROR		Return value on error.
 * 
 * Calls destroy_game(GAME) and returns ERROR if check fails.
 */
#define CHECK_ERROR(OBJECT, TYPE, GAME, ERROR)\
	do {\
		if((TYPE == 'p' && !(OBJECT)) ||\
		   (TYPE == 'i' && (OBJECT))) {\
			destroy_game(GAME);\
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
static int input_processing(char *buff, size_t buff_size, int *row, int *col, char *nickname);
static void clean_output(int rows);
static struct used_cell *remember_used_cell(struct used_cell *curr_uc_ptr, int row, int col);

int main(int argc, char **argv)
{
	char buff[64];
	int row, col, res_input;
	struct used_cell *curr_uc_ptr = NULL;
	struct player *curr_player = NULL;

	struct game *game_ptr = init_game();
	CHECK_ERROR(game_ptr, 'p', game_ptr,  MEMORY_ALLOC_ERR);

	curr_uc_ptr = game_ptr->used_cell_head;
	curr_player = game_ptr->player_1;

	/* TODO: Completing the cycle, control of used cells */
	while(game_ptr->game_is_not_over) {
		print_game_field(game_ptr);

		res_input = input_processing(buff, sizeof(buff), &row, &col, curr_player->nickname);
		CHECK_ERROR(res_input, 'i', game_ptr, INPUT_ERR);

		curr_uc_ptr = remember_used_cell(curr_uc_ptr, row, col);
		CHECK_ERROR(curr_uc_ptr, 'p', game_ptr, MEMORY_ALLOC_ERR);

		game_ptr->field[row][col] = curr_player->mark;
		curr_player = (curr_player == game_ptr->player_1) ? game_ptr->player_2 : game_ptr->player_1;

		clean_output(NUM_OF_LINES);
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
	putchar('\n');
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
	struct used_cell *uc_ptr = NULL;
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
	uc_ptr = calloc(1, sizeof(struct used_cell));
	if(!uc_ptr) {
		goto exit;
	}

	/* Define default nicknames and marks for players */
	snprintf(p1_ptr->nickname, sizeof(p1_ptr->nickname), "Player_1");
	p1_ptr->mark = 'X';
	snprintf(p2_ptr->nickname, sizeof(p2_ptr->nickname), "Player_2");
	p2_ptr->mark = 'O';

	/* Assigning fields to the used_cell structure */
	uc_ptr->next = NULL;

	/* Assigning fields to the game structure */
	game_ptr->game_is_not_over = 1;
	game_ptr->used_cell_head = uc_ptr;
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
	free(uc_ptr);
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

	current = game_ptr->used_cell_head;
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
 * Expects two numbers in the range [0,2] (row, column).
 *
 * @param buff		The buffer into which the line from stdin is written.
 * @param buff_size	Size of buffer from first parameter. 
 * @param row		Pointer to which the line number will be written upon successful input.
 * @param col		Pointer to which the column number will be written upon successful input.
 * @param nickname 	Nickname of the player from whom the input is received.
 * @return 0 if success, 1 if error fgets, 2 if error sscanf. 
 */
static int input_processing(char *buff, size_t buff_size, int *row, int *col, char *nickname)
{
	int res_sscanf;
	char *res_fgets, trash;

	printf("%s: ", nickname ? nickname : "Unknown");
	res_fgets = fgets(buff, buff_size, stdin);
	if(!res_fgets) {
		return 1;
	}

	res_sscanf = sscanf(buff, "%d %d %c", row, col, &trash);
	if (res_sscanf != 2 ||
		*(row) < 0 || *(row) >= MAX_ROW ||
		*(col) < 0 || *(col) >= MAX_COLUMN) {
		return 2;
	}

	return 0;
}

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
static void clean_output(int rows)
{
	for (int i = 0; i < rows; i++) {
		if (i < rows - 1) {
			printf("\033[K");
		}
		printf("\r\033[2K\033[A");
	}
	fflush(stdout);
}

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
static struct used_cell *remember_used_cell(struct used_cell *curr_uc_ptr, int row, int col)
{
	struct used_cell *new_uc_ptr = NULL;

	if(!curr_uc_ptr) {
		return NULL;
	}

	curr_uc_ptr->row = row;
	curr_uc_ptr->col = col;
	new_uc_ptr = calloc(1, sizeof(struct used_cell));
	if(!new_uc_ptr) {
		return NULL;
	}

	new_uc_ptr->next = NULL;
	curr_uc_ptr->next = new_uc_ptr;

	return new_uc_ptr;
}

