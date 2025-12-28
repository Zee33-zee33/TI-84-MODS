#include "2048_ui.h"
#include "../../engine/font.h"
#include <stdio.h>
#include <string.h>

/* UI Layout constants */
#define BOARD_X 60
#define BOARD_Y 60
#define TILE_SIZE 50
#define TILE_MARGIN 5
#define HEADER_Y 10
#define FOOTER_Y 220

/* Tile colors based on value */
static color_t get_tile_color(int value) {
    switch (value) {
        case 0:    return RGB(205, 193, 180);
        case 2:    return RGB(238, 228, 218);
        case 4:    return RGB(237, 224, 200);
        case 8:    return RGB(242, 177, 121);
        case 16:   return RGB(245, 149, 99);
        case 32:   return RGB(246, 124, 95);
        case 64:   return RGB(246, 94, 59);
        case 128:  return RGB(237, 207, 114);
        case 256:  return RGB(237, 204, 97);
        case 512:  return RGB(237, 200, 80);
        case 1024: return RGB(237, 197, 63);
        case 2048: return RGB(237, 194, 46);
        default:   return RGB(60, 58, 50);
    }
}

static color_t get_text_color(int value) {
    return (value <= 4) ? RGB(119, 110, 101) : COLOR_WHITE;
}

static void render_tile(int value, int row, int col) {
    int x = BOARD_X + col * (TILE_SIZE + TILE_MARGIN);
    int y = BOARD_Y + row * (TILE_SIZE + TILE_MARGIN);
    
    color_t tile_color = get_tile_color(value);
    render_fill_rect(x, y, TILE_SIZE, TILE_SIZE, tile_color);
    
    if (value > 0) {
        char text[16];
        snprintf(text, sizeof(text), "%d", value);
        
        /* Center text */
        font_size_t size = (value >= 1000) ? FONT_MEDIUM : FONT_LARGE;
        int text_width = font_get_text_width(text, size);
        int text_x = x + (TILE_SIZE - text_width) / 2;
        int text_y = y + (TILE_SIZE - size) / 2;
        
        color_t text_color = get_text_color(value);
        font_draw_text(text, text_x, text_y, text_color, size);
    }
}

static void render_board(board_t *board) {
    /* Draw background */
    render_fill_rect(BOARD_X - 5, BOARD_Y - 5, 
                     BOARD_SIZE * (TILE_SIZE + TILE_MARGIN) + 5,
                     BOARD_SIZE * (TILE_SIZE + TILE_MARGIN) + 5,
                     RGB(187, 173, 160));
    
    /* Draw tiles */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            render_tile(board->tiles[i][j], i, j);
        }
    }
}

static void render_header(board_t *board) {
    /* Draw title */
    font_draw_text("2048", 10, HEADER_Y, RGB(119, 110, 101), FONT_XLARGE);
    
    /* Draw score */
    char score_text[32];
    snprintf(score_text, sizeof(score_text), "Score: %d", board->score);
    font_draw_text(score_text, 120, HEADER_Y, RGB(119, 110, 101), FONT_MEDIUM);
    
    /* Draw high score */
    char high_score_text[32];
    snprintf(high_score_text, sizeof(high_score_text), "Best: %d", board->high_score);
    font_draw_text(high_score_text, 120, HEADER_Y + 15, RGB(119, 110, 101), FONT_MEDIUM);
}

static void render_menu(void) {
    render_clear(RGB(250, 248, 239));
    
    font_draw_text("2048 - Menu", 100, 50, RGB(119, 110, 101), FONT_XLARGE);
    font_draw_text("Arrow Keys: Move", 80, 100, RGB(119, 110, 101), FONT_MEDIUM);
    font_draw_text("Enter: Undo", 80, 120, RGB(119, 110, 101), FONT_MEDIUM);
    font_draw_text("2nd: Pause", 80, 140, RGB(119, 110, 101), FONT_MEDIUM);
    font_draw_text("Clear: Quit", 80, 160, RGB(119, 110, 101), FONT_MEDIUM);
    font_draw_text("Press any key to start", 60, 200, RGB(119, 110, 101), FONT_MEDIUM);
}

static void render_pause_menu(board_t *board) {
    /* Render game in background */
    render_clear(RGB(250, 248, 239));
    render_header(board);
    render_board(board);
    
    /* Draw pause overlay */
    render_fill_rect(60, 80, 200, 80, RGB(237, 194, 46));
    font_draw_text("PAUSED", 120, 95, COLOR_WHITE, FONT_LARGE);
    font_draw_text("2nd: Resume", 90, 120, COLOR_WHITE, FONT_SMALL);
    font_draw_text("Clear: Quit", 90, 135, COLOR_WHITE, FONT_SMALL);
}

static void render_game_over(board_t *board) {
    render_clear(RGB(250, 248, 239));
    render_header(board);
    render_board(board);
    
    /* Draw game over overlay */
    render_fill_rect(60, 80, 200, 80, RGB(237, 194, 46));
    font_draw_text("GAME OVER", 100, 95, COLOR_WHITE, FONT_LARGE);
    font_draw_text("Enter: New Game", 80, 120, COLOR_WHITE, FONT_SMALL);
    font_draw_text("Clear: Quit", 90, 135, COLOR_WHITE, FONT_SMALL);
}

static void render_game_won(board_t *board) {
    render_clear(RGB(250, 248, 239));
    render_header(board);
    render_board(board);
    
    /* Draw win overlay */
    render_fill_rect(60, 80, 200, 80, RGB(237, 194, 46));
    font_draw_text("YOU WIN!", 110, 95, COLOR_WHITE, FONT_LARGE);
    font_draw_text("Enter: Continue", 80, 120, COLOR_WHITE, FONT_SMALL);
    font_draw_text("Clear: Quit", 90, 135, COLOR_WHITE, FONT_SMALL);
}

void ui_init(ui_context_t *ctx, board_t *board) {
    if (!ctx || !board) return;
    
    ctx->board = board;
    ctx->state = UI_STATE_MENU;
    ctx->animation_frame = 0;
    
    render_init();
    input_init();
    font_init();
    save_init();
}

int ui_run(ui_context_t *ctx) {
    if (!ctx) return 0;
    
    key_t key = input_get_key();
    
    if (key != KEY_NONE) {
        ui_handle_input(ctx, key);
    }
    
    ui_render(ctx);
    
    return (ctx->state != UI_STATE_QUIT);
}

void ui_render(ui_context_t *ctx) {
    if (!ctx || !ctx->board) return;
    
    switch (ctx->state) {
        case UI_STATE_MENU:
            render_menu();
            break;
            
        case UI_STATE_PLAYING:
            render_clear(RGB(250, 248, 239));
            render_header(ctx->board);
            render_board(ctx->board);
            break;
            
        case UI_STATE_PAUSED:
            render_pause_menu(ctx->board);
            break;
            
        case UI_STATE_GAME_OVER:
            render_game_over(ctx->board);
            break;
            
        case UI_STATE_GAME_WON:
            render_game_won(ctx->board);
            break;
            
        default:
            break;
    }
    
    render_flip();
}

void ui_handle_input(ui_context_t *ctx, key_t key) {
    if (!ctx || !ctx->board) return;
    
    switch (ctx->state) {
        case UI_STATE_MENU:
            /* Any key starts the game */
            if (key != KEY_NONE) {
                game_reset(ctx->board);
                ctx->state = UI_STATE_PLAYING;
            }
            break;
            
        case UI_STATE_PLAYING:
            if (key == KEY_CLEAR) {
                ctx->state = UI_STATE_QUIT;
            } else if (key == KEY_2ND) {
                ctx->state = UI_STATE_PAUSED;
            } else if (key == KEY_ENTER) {
                game_undo(ctx->board);
            } else {
                /* Handle movement */
                direction_t dir;
                int valid_move = 1;
                
                switch (key) {
                    case KEY_UP:    dir = DIR_UP; break;
                    case KEY_DOWN:  dir = DIR_DOWN; break;
                    case KEY_LEFT:  dir = DIR_LEFT; break;
                    case KEY_RIGHT: dir = DIR_RIGHT; break;
                    default: valid_move = 0; break;
                }
                
                if (valid_move) {
                    game_move(ctx->board, dir);
                    
                    /* Check game state */
                    game_state_t state = game_get_state(ctx->board);
                    if (state == GAME_WON) {
                        ctx->state = UI_STATE_GAME_WON;
                    } else if (state == GAME_LOST) {
                        ctx->state = UI_STATE_GAME_OVER;
                    }
                }
            }
            break;
            
        case UI_STATE_PAUSED:
            if (key == KEY_2ND) {
                ctx->state = UI_STATE_PLAYING;
            } else if (key == KEY_CLEAR) {
                ctx->state = UI_STATE_QUIT;
            }
            break;
            
        case UI_STATE_GAME_OVER:
            if (key == KEY_ENTER) {
                game_reset(ctx->board);
                ctx->state = UI_STATE_PLAYING;
            } else if (key == KEY_CLEAR) {
                ctx->state = UI_STATE_QUIT;
            }
            break;
            
        case UI_STATE_GAME_WON:
            if (key == KEY_ENTER) {
                /* Continue playing */
                ctx->state = UI_STATE_PLAYING;
            } else if (key == KEY_CLEAR) {
                ctx->state = UI_STATE_QUIT;
            }
            break;
            
        default:
            break;
    }
}

void ui_cleanup(ui_context_t *ctx) {
    if (!ctx) return;
    
    /* Save game state if playing */
    if (ctx->state == UI_STATE_PLAYING && ctx->board) {
        game_save(ctx->board);
    }
    
    save_shutdown();
    font_shutdown();
    input_shutdown();
    render_shutdown();
}
