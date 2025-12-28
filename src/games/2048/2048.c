#include "2048.h"
#include "../../engine/save.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Internal helper functions */
static void spawn_tile(board_t *board);
static int move_tiles(board_t *board, direction_t dir);
static void save_for_undo(board_t *board);
static void update_game_state(board_t *board);

void game_init(board_t *board) {
    if (!board) return;
    
    /* Initialize random seed */
    srand((unsigned int)time(NULL));
    
    /* Clear the board */
    memset(board->tiles, 0, sizeof(board->tiles));
    board->score = 0;
    board->high_score = 0;
    board->state = GAME_PLAYING;
    board->moves = 0;
    board->can_undo = 0;
    memset(board->prev_tiles, 0, sizeof(board->prev_tiles));
    board->prev_score = 0;
    
    /* Try to load saved high score */
    board_t saved;
    if (game_load(&saved) == 0) {
        board->high_score = saved.high_score;
    }
}

void game_reset(board_t *board) {
    if (!board) return;
    
    int high_score = board->high_score;
    
    /* Clear the board */
    memset(board->tiles, 0, sizeof(board->tiles));
    board->score = 0;
    board->high_score = high_score;
    board->state = GAME_PLAYING;
    board->moves = 0;
    board->can_undo = 0;
    memset(board->prev_tiles, 0, sizeof(board->prev_tiles));
    board->prev_score = 0;
    
    /* Spawn two initial tiles */
    spawn_tile(board);
    spawn_tile(board);
}

int game_move(board_t *board, direction_t dir) {
    if (!board || board->state != GAME_PLAYING) return 0;
    
    /* Save state for undo */
    save_for_undo(board);
    
    /* Try to move tiles */
    int moved = move_tiles(board, dir);
    
    if (moved) {
        /* Spawn a new tile */
        spawn_tile(board);
        
        /* Update game state */
        board->moves++;
        update_game_state(board);
        board->can_undo = 1;
    } else {
        /* Move didn't change anything, don't count as valid undo state */
        board->can_undo = 0;
    }
    
    return moved;
}

int game_undo(board_t *board) {
    if (!board || !board->can_undo) return 0;
    
    /* Restore previous state */
    memcpy(board->tiles, board->prev_tiles, sizeof(board->tiles));
    board->score = board->prev_score;
    board->can_undo = 0;
    board->state = GAME_PLAYING; /* Reset to playing state */
    
    return 1;
}

int game_can_move(const board_t *board) {
    if (!board) return 0;
    
    /* Check for empty cells */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->tiles[i][j] == 0) return 1;
        }
    }
    
    /* Check for adjacent matching tiles */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int current = board->tiles[i][j];
            /* Check right neighbor */
            if (j < BOARD_SIZE - 1 && board->tiles[i][j + 1] == current) return 1;
            /* Check down neighbor */
            if (i < BOARD_SIZE - 1 && board->tiles[i + 1][j] == current) return 1;
        }
    }
    
    return 0;
}

game_state_t game_get_state(const board_t *board) {
    if (!board) return GAME_LOST;
    return board->state;
}

int game_save(const board_t *board) {
    if (!board) return -1;
    return save_write(SAVE_FILE, board, sizeof(board_t));
}

int game_load(board_t *board) {
    if (!board) return -1;
    return save_read(SAVE_FILE, board, sizeof(board_t));
}

/* Internal helper functions */

static void spawn_tile(board_t *board) {
    if (!board) return;
    
    /* Find empty cells */
    int empty_cells[BOARD_SIZE * BOARD_SIZE][2];
    int count = 0;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->tiles[i][j] == 0) {
                empty_cells[count][0] = i;
                empty_cells[count][1] = j;
                count++;
            }
        }
    }
    
    if (count == 0) return;
    
    /* Choose random empty cell */
    int index = rand() % count;
    int row = empty_cells[index][0];
    int col = empty_cells[index][1];
    
    /* 90% chance of 2, 10% chance of 4 */
    board->tiles[row][col] = (rand() % 10 == 0) ? 4 : 2;
}

static int move_tiles(board_t *board, direction_t dir) {
    if (!board) return 0;
    
    int moved = 0;
    int i, j;
    
    if (dir == DIR_LEFT) {
        for (i = 0; i < BOARD_SIZE; i++) {
            int target = 0;
            int last_merge = -1;
            for (j = 0; j < BOARD_SIZE; j++) {
                if (board->tiles[i][j] != 0) {
                    if (target > 0 && board->tiles[i][target - 1] == board->tiles[i][j] 
                        && last_merge != target - 1) {
                        /* Merge tiles */
                        board->tiles[i][target - 1] *= 2;
                        board->score += board->tiles[i][target - 1];
                        board->tiles[i][j] = 0;
                        last_merge = target - 1;
                        moved = 1;
                    } else {
                        /* Move tile */
                        if (target != j) {
                            board->tiles[i][target] = board->tiles[i][j];
                            board->tiles[i][j] = 0;
                            moved = 1;
                        }
                        target++;
                    }
                }
            }
        }
    } else if (dir == DIR_RIGHT) {
        for (i = 0; i < BOARD_SIZE; i++) {
            int target = BOARD_SIZE - 1;
            int last_merge = -1;
            for (j = BOARD_SIZE - 1; j >= 0; j--) {
                if (board->tiles[i][j] != 0) {
                    if (target < BOARD_SIZE - 1 && board->tiles[i][target + 1] == board->tiles[i][j] 
                        && last_merge != target + 1) {
                        /* Merge tiles */
                        board->tiles[i][target + 1] *= 2;
                        board->score += board->tiles[i][target + 1];
                        board->tiles[i][j] = 0;
                        last_merge = target + 1;
                        moved = 1;
                    } else {
                        /* Move tile */
                        if (target != j) {
                            board->tiles[i][target] = board->tiles[i][j];
                            board->tiles[i][j] = 0;
                            moved = 1;
                        }
                        target--;
                    }
                }
            }
        }
    } else if (dir == DIR_UP) {
        for (j = 0; j < BOARD_SIZE; j++) {
            int target = 0;
            int last_merge = -1;
            for (i = 0; i < BOARD_SIZE; i++) {
                if (board->tiles[i][j] != 0) {
                    if (target > 0 && board->tiles[target - 1][j] == board->tiles[i][j] 
                        && last_merge != target - 1) {
                        /* Merge tiles */
                        board->tiles[target - 1][j] *= 2;
                        board->score += board->tiles[target - 1][j];
                        board->tiles[i][j] = 0;
                        last_merge = target - 1;
                        moved = 1;
                    } else {
                        /* Move tile */
                        if (target != i) {
                            board->tiles[target][j] = board->tiles[i][j];
                            board->tiles[i][j] = 0;
                            moved = 1;
                        }
                        target++;
                    }
                }
            }
        }
    } else if (dir == DIR_DOWN) {
        for (j = 0; j < BOARD_SIZE; j++) {
            int target = BOARD_SIZE - 1;
            int last_merge = -1;
            for (i = BOARD_SIZE - 1; i >= 0; i--) {
                if (board->tiles[i][j] != 0) {
                    if (target < BOARD_SIZE - 1 && board->tiles[target + 1][j] == board->tiles[i][j] 
                        && last_merge != target + 1) {
                        /* Merge tiles */
                        board->tiles[target + 1][j] *= 2;
                        board->score += board->tiles[target + 1][j];
                        board->tiles[i][j] = 0;
                        last_merge = target + 1;
                        moved = 1;
                    } else {
                        /* Move tile */
                        if (target != i) {
                            board->tiles[target][j] = board->tiles[i][j];
                            board->tiles[i][j] = 0;
                            moved = 1;
                        }
                        target--;
                    }
                }
            }
        }
    }
    
    return moved;
}

static void save_for_undo(board_t *board) {
    if (!board) return;
    memcpy(board->prev_tiles, board->tiles, sizeof(board->tiles));
    board->prev_score = board->score;
}

static void update_game_state(board_t *board) {
    if (!board) return;
    
    /* Check for 2048 tile (win condition) */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->tiles[i][j] == 2048) {
                board->state = GAME_WON;
                /* Note: player can continue playing */
            }
        }
    }
    
    /* Check if no moves possible (lose condition) */
    if (!game_can_move(board)) {
        board->state = GAME_LOST;
    }
    
    /* Update high score */
    if (board->score > board->high_score) {
        board->high_score = board->score;
    }
}
