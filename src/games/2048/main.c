#include "2048.h"
#include "2048_ui.h"
#include <stdio.h>

int main(void) {
    board_t board;
    ui_context_t ui_ctx;
    
    /* Initialize game */
    game_init(&board);
    ui_init(&ui_ctx, &board);
    
    printf("2048 Game Starting...\n");
    
    /* Main game loop */
    while (ui_run(&ui_ctx)) {
        /* Game runs in ui_run() */
    }
    
    /* Cleanup */
    ui_cleanup(&ui_ctx);
    
    printf("2048 Game Ended.\n");
    return 0;
}
