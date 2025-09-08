/**
 * @file main.c
 * @author Zveror
 * @data September 2025
 */

/* Includes */
#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "func.h"

/**
 * @brief Error check with cleanup.
 * @param OBJECT	Object to check.
 * @param GAME		Game structure to destroy on error. May be NULL.
 * @param ERROR		Return value on error.
 * 
 * Calls destroy_game(GAME) and returns ERROR if check fails.
 */
#define CHECK_POINTER(OBJECT, GAME, ERROR)\
	do {\
		if(!(OBJECT)){\
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

int main(int argc, char **argv)
{
	char buff[64];
	int row, col, res_input;
	struct used_cell *curr_uc_ptr = NULL;
	struct player *curr_player = NULL;
	struct game *game_ptr = NULL;

create_game:

	game_ptr = init_game();
	CHECK_POINTER(game_ptr, game_ptr,  MEMORY_ALLOC_ERR);

	curr_uc_ptr = game_ptr->used_cell_head;
	curr_player = game_ptr->player_1;

	/* TODO: Completing the cycle */
	while(game_ptr->game_is_not_over) {
		print_game_field(game_ptr);

		res_input = input_processing(buff, sizeof(buff), &row, &col, curr_player->nickname);
		switch(res_input) {
			case COORDINATES:
				if(game_ptr->field[row][col] != '_') {
					clean_output(NUM_OF_LINES);
					continue;
				}

				curr_uc_ptr = remember_used_cell(curr_uc_ptr, row, col);
				CHECK_POINTER(curr_uc_ptr, game_ptr, MEMORY_ALLOC_ERR);

				game_ptr->field[row][col] = curr_player->mark;
				curr_player = (curr_player == game_ptr->player_1) ? game_ptr->player_2 : game_ptr->player_1;

				clean_output(NUM_OF_LINES);
				break;
			case ERROR: 
				clean_output(NUM_OF_LINES);
				continue;
			case QUIT: 
				return SUCCESS;
			case RESTART:
				destroy_game(game_ptr);
				clean_output(NUM_OF_LINES);
				goto create_game;
			case RENAME:
				handle_rename(curr_player);
				break;
		}

	}

	destroy_game(game_ptr);
	return SUCCESS;
}
