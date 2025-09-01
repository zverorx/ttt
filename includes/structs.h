#ifndef FUNC_H_SENTRY
#define FUNC_H_SENTRY

/* Defines */
#define MAX_ROW		3
#define MAX_COLUMN	3

struct game {
	uint8_t game_is_not_over; /* 0 or 1 */
	char field[MAX_ROW][MAX_COLUMN];
	struct used_cell *used_cells_head;
	struct player *player_1;
	struct player *player_2;
};

struct player {
	char nickname[64];
	char mark; //X or O
};

struct used_cell {
	uint8_t row;
	uint8_t col;
	struct used_cell *next;
};
#endif
