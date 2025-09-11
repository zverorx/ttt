/**
 * @file types.h
 * @brief Game data structures, constants and enums for Tic-Tac-Toe implementation.
 *
 * Defines the core data structures used in the game:
 * - Game state (board, players, control flags)
 * - Player information (nickname, mark)
 * - Linked list node for tracking used cells
 * - Constants for board dimensions.
 *
 * @author zveror
 * @date September 2025
 */

#ifndef STRUCTS_H_SENTRY
#define STRUCTS_H_SENTRY

/* ========================================================================== */
/*                                Includes                                    */
/* ========================================================================== */

#include <stdint.h>

/* ========================================================================== */
/*                                Constants                                   */
/* ========================================================================== */

/**
 * @def MAX_ROW
 * @brief Number of rows in the game field.
 * @note Currently set to 3 for a standard 3x3 Tic-Tac-Toe board.
 */
#define MAX_ROW     3

/**
 * @def MAX_COLUMN
 * @brief Number of columns in the game field.
 * @note Currently set to 3 for a standard 3x3 Tic-Tac-Toe board.
 */
#define MAX_COLUMN  3

/**
 * @def NUM_OF_LINES
 * @brief The number of lines that the program's stdout occupies.
 * @note Used when clearing output as a parameter to clean_output(int rows).
 *
 */ 
#define NUM_OF_LINES		20

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
/*                                Structures                                  */
/* ========================================================================== */

/**
 * @struct used_cell
 * @brief Represents a single used cell in the game grid.
 *
 * This structure is used to form a linked list of all moves made during the game.
 * The list starts at game->used_cell_head and grows with each move.
 *
 * @var used_cell::row
 *      Row index of the used cell (0-based).
 * @var used_cell::col
 *      Column index of the used cell (0-based).
 * @var used_cell::next
 *      Pointer to the next used cell in the list, or NULL if last.
 */
struct used_cell {
    uint8_t row;              /**< Row index (0 to MAX_ROW-1) */
    uint8_t col;              /**< Column index (0 to MAX_COLUMN-1) */
    struct used_cell *next;   /**< Next node in the linked list */
};

/**
 * @struct player
 * @brief Represents a player in the game.
 *
 * Contains player-specific data such as nickname and assigned mark ('X' or 'O').
 *
 * @var player::nickname
 *      Player's name, used for prompts and display (max 63 chars + null terminator).
 * @var player::mark
 *      Symbol used by the player on the board: typically 'X' or 'O'.
 */
struct player {
    char nickname[64];         /**< Player's nickname (null-terminated string) */
    char mark;                 /**< Player's symbol on the board ('X' or 'O') */
};

/**
 * @struct game
 * @brief Central structure representing the entire game state.
 *
 * Holds all data necessary for the current game session:
 * - Game control flag (running or over)
 * - Game board (2D array of marks)
 * - Linked list head for tracking moves
 * - Pointers to both players
 *
 * @var game::game_is_not_over
 *      Boolean flag: 1 if game is active, 0 if game has ended.
 * @var game::field
 *      2D array representing the game board. Empty cells contain '_'.
 * @var game::used_cell_head
 *      Pointer to the first node in the linked list of used cells.
 *      The list is used to track move history.
 * @var game::player_1
 *      Pointer to the first player (typically 'X').
 * @var game::player_2
 *      Pointer to the second player (typically 'O').
 *
 * @note Memory for this structure and all substructures must be managed
 *       via init_game() and destroy_game().
 */
struct game {
    uint8_t game_is_not_over;           /**< Game running flag (1 = active) */
    char field[MAX_ROW][MAX_COLUMN];    /**< Game board: '_' = empty, 'X'/'O' = occupied */
    struct used_cell *used_cell_head;   /**< Head of used cells list */
    struct player *player_1;            /**< First player */
    struct player *player_2;            /**< Second player */
};

#endif /* STRUCTS_H_SENTRY */
