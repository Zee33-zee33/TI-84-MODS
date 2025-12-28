#ifndef GAME_2048_UI_H
#define GAME_2048_UI_H

#include "2048.h"
#include "../../engine/render.h"
#include "../../engine/input.h"
#include "../../engine/font.h"
#include "../../engine/save.h"

/* UI state */
typedef enum {
    UI_STATE_MENU,
    UI_STATE_PLAYING,
    UI_STATE_PAUSED,
    UI_STATE_GAME_OVER,
    UI_STATE_GAME_WON,
    UI_STATE_QUIT
} ui_state_t;

/* UI context */
typedef struct {
    board_t *board;
    ui_state_t state;
    int animation_frame;
} ui_context_t;

/* Initialize the UI */
void ui_init(ui_context_t *ctx, board_t *board);

/* Run the main game loop */
/* Returns 0 when user quits, 1 to continue */
int ui_run(ui_context_t *ctx);

/* Render the current frame */
void ui_render(ui_context_t *ctx);

/* Handle input for current state */
void ui_handle_input(ui_context_t *ctx, key_t key);

/* Cleanup UI resources */
void ui_cleanup(ui_context_t *ctx);

#endif /* GAME_2048_UI_H */
