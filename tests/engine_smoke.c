/**
 * engine_smoke.c - Smoke test for TI-84 Pixel Games Engine
 * 
 * Tests basic engine initialization and displays "ENGINE OK" text
 */

#include "../src/engine/input.h"
#include "../src/engine/render.h"
#include "../src/engine/font.h"
#include "../src/engine/save.h"
#include "../src/engine/ui.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __TI84PCE__
    #define PLATFORM_CE 1
    /* CE-specific delay function */
    /* #include <ti/delay.h> */
#else
    #define PLATFORM_HOST 1
    #include <unistd.h>
#endif

int main(void) {
    int result = 0;
    
    printf("Engine Smoke Test Starting...\n");
    
    /* Initialize all engine systems */
    printf("Initializing input system...\n");
    if (input_init() != 0) {
        printf("ERROR: Failed to initialize input system\n");
        result = -1;
    }
    
    printf("Initializing render system...\n");
    if (render_init() != 0) {
        printf("ERROR: Failed to initialize render system\n");
        result = -1;
    }
    
    printf("Initializing font system...\n");
    if (font_init() != 0) {
        printf("ERROR: Failed to initialize font system\n");
        result = -1;
    }
    
    printf("Initializing save system...\n");
    if (save_init() != 0) {
        printf("ERROR: Failed to initialize save system\n");
        result = -1;
    }
    
    if (result == 0) {
        printf("All systems initialized successfully!\n");
        
        /* Clear screen to black */
        printf("Clearing screen...\n");
        render_clear(0);
        
        /* Draw "ENGINE OK" text to screen */
        printf("Drawing 'ENGINE OK' text...\n");
        draw_text(120, 116, "ENGINE OK", 255);
        
        /* Present the framebuffer */
        printf("Presenting frame...\n");
        render_present();
        
        printf("\n=================================\n");
        printf("SMOKE TEST PASSED!\n");
        printf("'ENGINE OK' should be visible on screen\n");
        printf("=================================\n");
        
#ifdef PLATFORM_CE
        /* Wait for key press on CE */
        /* while (!os_GetCSC()); */
#else
        /* Brief delay on host to simulate display */
        sleep(1);
#endif
    } else {
        printf("\nSMOKE TEST FAILED!\n");
    }
    
    /* Cleanup */
    printf("Cleaning up...\n");
    render_cleanup();
    input_cleanup();
    save_cleanup();
    
    printf("Engine Smoke Test Complete.\n");
    
    return result;
}
