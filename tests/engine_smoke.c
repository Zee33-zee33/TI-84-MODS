#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "input.h"
#include "render.h"
#include "font.h"
#include "save.h"
#include "ui.h"
#include "palette.h"
#include "assets.h"

int main(void) {
    printf("=== TI-84 Engine Smoke Test ===\n\n");
    
    // Test engine initialization
    printf("Testing engine_init... ");
    if (engine_init() != 0) {
        printf("FAILED\n");
        return 1;
    }
    printf("OK\n");
    
    // Test input system
    printf("Testing input_init... ");
    if (input_init() != 0) {
        printf("FAILED\n");
        return 1;
    }
    printf("OK\n");
    
    // Test renderer
    printf("Testing render_init... ");
    if (render_init() != 0) {
        printf("FAILED\n");
        return 1;
    }
    printf("OK\n");
    
    // Test font system
    printf("Testing font_init... ");
    if (font_init() != 0) {
        printf("FAILED\n");
        return 1;
    }
    printf("OK\n");
    
    // Test save system
    printf("Testing save_init... ");
    if (save_init() != 0) {
        printf("FAILED\n");
        return 1;
    }
    printf("OK\n");
    
    // Test UI system
    printf("Testing ui_init... ");
    if (ui_init() != 0) {
        printf("FAILED\n");
        return 1;
    }
    printf("OK\n");
    
    // Test palette system
    printf("Testing palette_init... ");
    if (palette_init() != 0) {
        printf("FAILED\n");
        return 1;
    }
    printf("OK\n");
    
    // Test assets system
    printf("Testing assets_init... ");
    if (assets_init() != 0) {
        printf("FAILED\n");
        return 1;
    }
    printf("OK\n");
    
    // Test basic functionality
    printf("\nTesting basic functionality...\n");
    
    // Test time
    uint32_t time1 = engine_time_ms();
    engine_tick();
    uint32_t time2 = engine_time_ms();
    printf("  Time tracking: %u ms -> %u ms... ", time1, time2);
    if (time2 >= time1) {
        printf("OK\n");
    } else {
        printf("FAILED\n");
    }
    
    // Test input update
    printf("  Input update... ");
    input_update();
    printf("OK\n");
    
    // Test render clear
    printf("  Render clear... ");
    render_clear(0);
    printf("OK\n");
    
    // Test font width calculation
    printf("  Font text width... ");
    int width = font_text_width("Test");
    if (width > 0) {
        printf("OK (width=%d)\n", width);
    } else {
        printf("FAILED\n");
    }
    
    // Cleanup
    printf("\nCleaning up...\n");
    assets_shutdown();
    palette_shutdown();
    ui_shutdown();
    save_shutdown();
    font_shutdown();
    render_shutdown();
    input_shutdown();
    engine_shutdown();
    
    printf("\n=== ENGINE OK ===\n");
    return 0;
}
