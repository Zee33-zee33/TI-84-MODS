#ifndef GAME_2048_H
#define GAME_2048_H

#include <stdint.h>

#define BOARD_SIZE 4
#define SAVE_FILE "2048.sav"

/* Direction for moves */
typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} direction_t;

/* Game state */
typedef enum {
    GAME_PLAYING,
    GAME_WON,
    GAME_LOST
} game_state_t;

/* Board state structure */
typedef struct {
    int tiles[BOARD_SIZE][BOARD_SIZE];
    int score;
    int high_score;
    game_state_t state;
    int moves;
    /* Undo support - store previous state */
    int prev_tiles[BOARD_SIZE][BOARD_SIZE];
    int prev_score;
    int can_undo;
} board_t;

/* Initialize the game board */
void game_init(board_t *board);

/* Reset the board for a new game */
void game_reset(board_t *board);

/* Make a move in the specified direction */
/* Returns 1 if the move changed the board, 0 otherwise */
int game_move(board_t *board, direction_t dir);

/* Undo the last move (one-step undo) */
/* Returns 1 if undo was successful, 0 if no undo available */
int game_undo(board_t *board);

/* Check if any moves are possible */
int game_can_move(const board_t *board);

/* Get the current game state */
game_state_t game_get_state(const board_t *board);

/* Save the game state */
int game_save(const board_t *board);

/* Load the game state */
int game_load(board_t *board);

#endif /* GAME_2048_H */
