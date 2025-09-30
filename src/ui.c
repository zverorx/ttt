/**
 * @file ui.c
 * @brief Contains function definitions for main.c.
 *
 * Functions are responsible for the user interface.
 *
 * @author zverorx
 * @data September 2025
 */

/* Includes */
#include <stdio.h>
#include "types.h"

/**
 * @brief Print game field to stdout.
 * @param game_ptr Pointer to the game structure.
 * @return void.
 */
void print_game_field(struct game *game_ptr)
{
	printf(" _____________________________\n");
	printf("|         Tic Tac Toe         |\n");
	printf("| To move, enter the row and  |\n");
	printf("| column separated by a space.|\n");
	printf("|                             |\n");
	printf("| Commands:                   |\n");
	printf("| q - exit                    |\n");
	printf("| r - restart                 |\n");
	printf("| n - rename                  |\n");
	printf("|                             |\n");
	printf("| Enjoy the game!             |\n");
	printf("|_____________________________|\n\n");
	printf("\t    0   1   2\n");
	printf("\t   ___ ___ ___\n");
	printf("\t0 |_%c_|_%c_|_%c_|\n", game_ptr->field[0][0], game_ptr->field[0][1], game_ptr->field[0][2]);
	printf("\t1 |_%c_|_%c_|_%c_|\n", game_ptr->field[1][0], game_ptr->field[1][1], game_ptr->field[1][2]);
	printf("\t2 |_%c_|_%c_|_%c_|\n", game_ptr->field[2][0], game_ptr->field[2][1], game_ptr->field[2][2]);
	putchar('\n');
}

/**
 * @brief Prints the game result message (win or draw).
 *
 * @param status    Game result: RGO_WIN or RGO_DRAW.
 * @param plr       Pointer to the winning player (ignored for draw).
 */
void print_game_over(ret_game_over status, struct player *plr) {
	switch(status) {
		case RGO_WIN:
			printf(" _____________________________\n");
			printf("|                             |\n");
			printf("|  %s is a winner!            \n", plr->nickname);
			printf("|_____________________________|\n");
			break;
		case RGO_DRAW:
			printf(" _____________________________\n");
			printf("|                             |\n");
			printf("| This game ended in a draw!  |\n");
			printf("|_____________________________|\n");
			break;
		case RGO_ERROR: break;
	}
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
void clean_output(int rows)
{
	for (int i = 0; i < rows; i++) {
		if (i < rows - 1) {
			printf("\033[K");
		}
		printf("\r\033[2K\033[A");
	}
	fflush(stdout);
}
