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

/**
 * @file func.c
 * @brief Contains function definitions for main.c.
 */

/* Includes */
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "ui.h"
#include "func.h"

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
				 struct player **curr_player, int row, int col) {
	int res_game_over;

	if(game_ptr->field[row][col] != '_') {
		clean_output(NUM_OF_LINES);
		return;
	}
	*curr_uc_ptr = remember_used_cell(*curr_uc_ptr, row, col);
	if(!*curr_uc_ptr){
		destroy_game(game_ptr);
		exit(MEMORY_ALLOC_ERR);
	}

	game_ptr->field[row][col] = (*curr_player)->mark;

	res_game_over = check_game_over(game_ptr, *curr_player);
	switch(res_game_over) {
		case RGO_WIN:
			game_ptr->game_is_not_over = 0;
			clean_output(NUM_OF_LINES);
			print_game_field(game_ptr);
			print_game_over(RGO_WIN, *curr_player);
			return;
		case RGO_DRAW:
			game_ptr->game_is_not_over = 0;
			clean_output(NUM_OF_LINES);
			print_game_field(game_ptr);
			print_game_over(RGO_DRAW, *curr_player);
			return;
	}
	*curr_player = (*curr_player == game_ptr->player_1) ? game_ptr->player_2 : game_ptr->player_1;
	clean_output(NUM_OF_LINES);
	return;
}

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
ret_game_over check_game_over(struct game *game_ptr, struct player *curr_player)
{
	int count, has_free_cells = 0;
	char mark = curr_player->mark;

	if(!game_ptr || !curr_player) {
		return RGO_ERROR;
	}

	/* Check by rows */
	for(int i = 0; i < MAX_ROW; i++) {
		count = 0;
		for(int j = 0; j < MAX_COLUMN; j++) {
			if(game_ptr->field[i][j] == mark) {
				count++;
			}
			if(count == 3) {
				goto winner;
			}
			if(game_ptr->field[i][j] == '_') {
				has_free_cells = 1;
			} 
		}
	}

	/* Check by columns */
	for(int j = 0; j < MAX_ROW; j++) {
		count = 0;
		for(int i = 0; i < MAX_COLUMN; i++) {
			if(game_ptr->field[i][j] == mark) {
				count++;
			}
			if(count == 3) {
				goto winner;
			}
			if(game_ptr->field[i][j] == '_') {
				has_free_cells = 1;
			} 
		}
	}

	/* Main diagonal */
	count = 0;
	for(int i = 0; i < MAX_ROW; i++) {
		if(game_ptr->field[i][i] == mark) {
			count++;
		}
		if(count == 3) {
			goto winner;
		}
		if(game_ptr->field[i][i] == '_') {
			has_free_cells = 1;
		} 
	}

	/* Secondary diagonal */
	count = 0;
	for(int i = 0; i < MAX_ROW; i++) {
		if(game_ptr->field[i][2 - i] == mark) {
			count++;
		}
		if(count == 3) {
			goto winner;
		}
		if(game_ptr->field[i][2 - i] == '_') {
			has_free_cells = 1;
		} 
	}

	/* Checking a draw */
	if(!has_free_cells) {
		goto draw;
	}

	return 0; 

winner:
	return RGO_WIN;

draw:
	return RGO_DRAW;

}

/**
 * @brief Initializes a new game instance with default settings.
 *
 * Allocates and initializes the main game structure, two players,
 * an empty game field, and a head node for the list of used cells.
 *
 * @return Pointer to the initialized game structure on success, NULL on memory allocation failure.
 */
struct game *init_game()
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
void destroy_game(struct game *game_ptr)
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
input_data input_processing(char *buff, size_t buff_size, int *row, int *col, const char *nickname)
{
	int res_sscanf;
	char *res_fgets, trash, cmd;

	printf("> %s: ", nickname ? nickname : "Unknown");
	res_fgets = fgets(buff, buff_size, stdin);
	if(!res_fgets) {
		return INP_D_ERROR;
	}

	res_sscanf = sscanf(buff, "%d %d %c", row, col, &trash);
	if(res_sscanf != 2 ||
		*(row) < 0 || *(row) >= MAX_ROW ||
		*(col) < 0 || *(col) >= MAX_COLUMN) {

		res_sscanf = sscanf(buff, "%c %c", &cmd, &trash);
		if(res_sscanf != 1) {
			return INP_D_ERROR;
		}

		switch(cmd) {
			case 'q': return INP_D_QUIT;
			case 'n': return INP_D_RENAME;
			case 'r': return INP_D_RESTART;
			default: return INP_D_ERROR;
		}
	}

	return INP_D_COORDINATES;
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
struct used_cell *remember_used_cell(struct used_cell *curr_uc_ptr, int row, int col)
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

/**
 * @brief Prompts the user to enter a new nickname and updates the player's name.
 *
 * Reads input from stdin, trims the trailing newline, and safely copies
 * the result into the player's nickname field. Cleans console after input.
 * Does nothing if fgets fails.
 *
 * @param curr_player Pointer to the player structure to update (must not be NULL).
 */
void handle_rename(struct player *curr_player)
{
	char buff[64], *res_fgets;
	
	printf("\r\033[A\033[2K");
	fputs("> ", stdout);
	res_fgets = fgets(buff, sizeof(buff), stdin);
	if(!res_fgets) {
		clean_output(NUM_OF_LINES);
		return;
	}
	for(int i = 0; i < sizeof(buff); i++) {
		if(buff[i] == '\n') {
			buff[i] = '\0';
			break;
		}
	}
	snprintf(curr_player->nickname, sizeof(curr_player->nickname), "%s", buff);
	clean_output(NUM_OF_LINES);
	return;
}
