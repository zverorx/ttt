/* 
 * This file is part of ttt.
 * ttt - Tic-tac-toe in a terminal with two players.
 *
 * Copyright (C) 2025 Egorov Konstantin
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

/* Includes */
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "func.h"
#include "ui.h"

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

	while(game_ptr->game_is_not_over) {
		print_game_field(game_ptr);

		res_input = input_processing(buff, sizeof(buff), &row, &col, curr_player->nickname);
		switch(res_input) {
			case INP_D_COORDINATES:
				handle_move(game_ptr, &curr_uc_ptr, &curr_player, row, col);
				break;
			case INP_D_ERROR: 
				clean_output(NUM_OF_LINES);
				continue;
			case INP_D_QUIT: 
				return SUCCESS;
			case INP_D_RESTART:
				destroy_game(game_ptr);
				curr_uc_ptr = NULL;
				curr_player = NULL;
				clean_output(NUM_OF_LINES);
				goto create_game;
			case INP_D_RENAME:
				handle_rename(curr_player);
				break;
		}
	}

	destroy_game(game_ptr);
	return SUCCESS;
}
