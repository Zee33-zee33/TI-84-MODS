#include "../src/games/2048/2048.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

/* Test helpers */
static int test_count = 0;
static int test_passed = 0;

#define TEST(name) \
    printf("Testing %s...\n", name); \
    test_count++;

#define ASSERT(condition, message) \
    if (!(condition)) { \
        printf("  FAILED: %s\n", message); \
        return; \
    }

#define TEST_PASS() \
    printf("  PASSED\n"); \
    test_passed++;

/* Test initialization */
void test_init(void) {
    TEST("game_init");
    
    board_t board;
    game_init(&board);
    
    ASSERT(board.score == 0, "Initial score should be 0");
    ASSERT(board.state == GAME_PLAYING, "Initial state should be PLAYING");
    ASSERT(board.moves == 0, "Initial moves should be 0");
    ASSERT(board.can_undo == 0, "Should not be able to undo initially");
    
    TEST_PASS();
}

/* Test reset */
void test_reset(void) {
    TEST("game_reset");
    
    board_t board;
    game_init(&board);
    game_reset(&board);
    
    int tile_count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board.tiles[i][j] != 0) {
                tile_count++;
            }
        }
    }
    
    ASSERT(tile_count == 2, "Should have 2 tiles after reset");
    ASSERT(board.score == 0, "Score should be 0 after reset");
    
    TEST_PASS();
}

/* Test horizontal move left */
void test_move_left(void) {
    TEST("game_move LEFT");
    
    board_t board;
    game_init(&board);
    
    /* Set up test board: [2, 0, 2, 0] */
    memset(board.tiles, 0, sizeof(board.tiles));
    board.tiles[0][0] = 2;
    board.tiles[0][2] = 2;
    board.state = GAME_PLAYING;
    
    int moved = game_move(&board, DIR_LEFT);
    
    ASSERT(moved == 1, "Move should succeed");
    ASSERT(board.tiles[0][0] == 4, "Tiles should merge to 4");
    ASSERT(board.tiles[0][1] == 0 || board.tiles[0][1] == 2, "Position [0][1] should be 0 or have spawned tile");
    ASSERT(board.score == 4, "Score should increase by 4");
    
    TEST_PASS();
}

/* Test horizontal move right */
void test_move_right(void) {
    TEST("game_move RIGHT");
    
    board_t board;
    game_init(&board);
    
    /* Set up test board: [0, 2, 0, 2] */
    memset(board.tiles, 0, sizeof(board.tiles));
    board.tiles[0][1] = 2;
    board.tiles[0][3] = 2;
    board.state = GAME_PLAYING;
    
    int moved = game_move(&board, DIR_RIGHT);
    
    ASSERT(moved == 1, "Move should succeed");
    ASSERT(board.tiles[0][3] == 4, "Tiles should merge to 4 at rightmost position");
    ASSERT(board.score == 4, "Score should increase by 4");
    
    TEST_PASS();
}

/* Test vertical move up */
void test_move_up(void) {
    TEST("game_move UP");
    
    board_t board;
    game_init(&board);
    
    /* Set up test board: column with [2, 0, 2, 0] */
    memset(board.tiles, 0, sizeof(board.tiles));
    board.tiles[0][0] = 2;
    board.tiles[2][0] = 2;
    board.state = GAME_PLAYING;
    
    int moved = game_move(&board, DIR_UP);
    
    ASSERT(moved == 1, "Move should succeed");
    ASSERT(board.tiles[0][0] == 4, "Tiles should merge to 4 at top");
    ASSERT(board.score == 4, "Score should increase by 4");
    
    TEST_PASS();
}

/* Test vertical move down */
void test_move_down(void) {
    TEST("game_move DOWN");
    
    board_t board;
    game_init(&board);
    
    /* Set up test board: column with [2, 0, 2, 0] */
    memset(board.tiles, 0, sizeof(board.tiles));
    board.tiles[0][0] = 2;
    board.tiles[2][0] = 2;
    board.state = GAME_PLAYING;
    
    int moved = game_move(&board, DIR_DOWN);
    
    ASSERT(moved == 1, "Move should succeed");
    ASSERT(board.tiles[3][0] == 4, "Tiles should merge to 4 at bottom");
    ASSERT(board.score == 4, "Score should increase by 4");
    
    TEST_PASS();
}

/* Test merge behavior - should only merge once per move */
void test_merge_once(void) {
    TEST("merge once per move");
    
    board_t board;
    game_init(&board);
    
    /* Set up test board: [2, 2, 4, 0] */
    memset(board.tiles, 0, sizeof(board.tiles));
    board.tiles[0][0] = 2;
    board.tiles[0][1] = 2;
    board.tiles[0][2] = 4;
    board.state = GAME_PLAYING;
    
    int moved = game_move(&board, DIR_LEFT);
    
    ASSERT(moved == 1, "Move should succeed");
    ASSERT(board.tiles[0][0] == 4, "First merge: 2+2=4");
    ASSERT(board.tiles[0][1] == 4, "4 should not merge with result");
    
    TEST_PASS();
}

/* Test undo functionality */
void test_undo(void) {
    TEST("game_undo");
    
    board_t board;
    game_init(&board);
    
    /* Set up test board */
    memset(board.tiles, 0, sizeof(board.tiles));
    board.tiles[0][0] = 2;
    board.tiles[0][1] = 2;
    board.state = GAME_PLAYING;
    int original_score = board.score;
    
    /* Make a move */
    game_move(&board, DIR_LEFT);
    
    ASSERT(board.can_undo == 1, "Should be able to undo after move");
    
    /* Undo the move */
    int undone = game_undo(&board);
    
    ASSERT(undone == 1, "Undo should succeed");
    ASSERT(board.tiles[0][0] == 2, "Tile should be restored");
    ASSERT(board.tiles[0][1] == 2, "Tile should be restored");
    ASSERT(board.score == original_score, "Score should be restored");
    ASSERT(board.can_undo == 0, "Should not be able to undo again");
    
    TEST_PASS();
}

/* Test no move possible */
void test_no_move(void) {
    TEST("no move possible");
    
    board_t board;
    game_init(&board);
    
    /* Set up board where left move does nothing: [2, 0, 0, 0] */
    memset(board.tiles, 0, sizeof(board.tiles));
    board.tiles[0][0] = 2;
    board.state = GAME_PLAYING;
    
    int moved = game_move(&board, DIR_LEFT);
    
    ASSERT(moved == 0, "Move should not succeed (tile already at leftmost)");
    
    TEST_PASS();
}

/* Test can_move detection */
void test_can_move(void) {
    TEST("game_can_move");
    
    board_t board;
    game_init(&board);
    
    /* Empty board - can move (has empty cells) */
    memset(board.tiles, 0, sizeof(board.tiles));
    ASSERT(game_can_move(&board) == 1, "Empty board should allow moves");
    
    /* Full board with adjacent matches - can move */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.tiles[i][j] = 2;
        }
    }
    ASSERT(game_can_move(&board) == 1, "Board with matching tiles should allow moves");
    
    /* Full board with no matches - cannot move */
    int val = 2;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board.tiles[i][j] = val;
            val = (val == 2) ? 4 : 2;
        }
        val = (val == 2) ? 4 : 2; /* Alternate row start */
    }
    ASSERT(game_can_move(&board) == 0, "Checkerboard pattern should not allow moves");
    
    TEST_PASS();
}

/* Randomized test: multiple random moves */
void test_random_moves(void) {
    TEST("random moves (randomized)");
    
    board_t board;
    game_init(&board);
    game_reset(&board);
    
    /* Make 10 random valid moves */
    direction_t dirs[] = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
    int successful_moves = 0;
    
    for (int i = 0; i < 10 && game_can_move(&board); i++) {
        direction_t dir = dirs[rand() % 4];
        if (game_move(&board, dir)) {
            successful_moves++;
        }
    }
    
    ASSERT(successful_moves > 0, "Should have made at least one successful move");
    ASSERT(board.score >= 0, "Score should be non-negative");
    
    TEST_PASS();
}

int main(void) {
    printf("Running 2048 Game Logic Tests\n");
    printf("==============================\n\n");
    
    test_init();
    test_reset();
    test_move_left();
    test_move_right();
    test_move_up();
    test_move_down();
    test_merge_once();
    test_undo();
    test_no_move();
    test_can_move();
    test_random_moves();
    
    printf("\n==============================\n");
    printf("Tests: %d/%d passed\n", test_passed, test_count);
    
    return (test_passed == test_count) ? 0 : 1;
}
