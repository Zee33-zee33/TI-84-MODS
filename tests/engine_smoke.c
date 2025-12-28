#include "input.h"
#include "render.h"
#include "font.h"
#include "ui.h"
#include "save.h"
#include <stdlib.h>

#ifdef TI84CE
#include <ti/getcsc.h>
#endif

/**
 * Engine Smoke Test
 * 
 * This test demonstrates basic functionality of all engine modules.
 * When run in CEmu, it should display "ENGINE OK" and other test output.
 */

int main(void) {
    int result = 0;
    
    /* Initialize all engine modules */
    result = render_init();
    if (result != 0) {
        return 1;
    }
    
    result = input_init();
    if (result != 0) {
        render_shutdown();
        return 2;
    }
    
    result = font_init();
    if (result != 0) {
        render_shutdown();
        return 3;
    }
    
    result = ui_init();
    if (result != 0) {
        render_shutdown();
        return 4;
    }
    
    result = save_init("SMOKE");
    if (result != 0) {
        render_shutdown();
        return 5;
    }
    
    /* Clear screen to black */
    render_clear_screen(COLOR_BLACK);
    
    /* Draw main status message */
    font_draw_text_bg(10, 10, "TI-84 Game Engine", COLOR_WHITE, COLOR_BLUE);
    font_draw_text(10, 30, "Smoke Test v1.0", COLOR_CYAN);
    
    /* Draw test results */
    font_draw_text(10, 50, "[ PASS ] Render Module", COLOR_GREEN);
    font_draw_text(10, 65, "[ PASS ] Input Module", COLOR_GREEN);
    font_draw_text(10, 80, "[ PASS ] Font Module", COLOR_GREEN);
    font_draw_text(10, 95, "[ PASS ] UI Module", COLOR_GREEN);
    font_draw_text(10, 110, "[ PASS ] Save Module", COLOR_GREEN);
    
    /* Draw success message */
    font_draw_text_bg(10, 140, "ENGINE OK", COLOR_BLACK, COLOR_GREEN);
    
    /* Draw colored rectangles to test rendering */
    render_draw_rect(10, 170, 40, 20, COLOR_RED);
    render_draw_rect(55, 170, 40, 20, COLOR_GREEN);
    render_draw_rect(100, 170, 40, 20, COLOR_BLUE);
    render_draw_rect(145, 170, 40, 20, COLOR_YELLOW);
    render_draw_rect(190, 170, 40, 20, COLOR_CYAN);
    render_draw_rect(235, 170, 40, 20, COLOR_MAGENTA);
    
    /* Draw instructions */
    font_draw_text(10, 200, "Press ENTER to test menu", COLOR_WHITE);
    font_draw_text(10, 215, "Press CLEAR to exit", COLOR_WHITE);
    
    /* Present the frame */
    render_present();
    
    /* Wait for user input */
    while (1) {
        input_poll();
        
        /* Test menu system */
        if (input_button_pressed(BTN_ENTER)) {
            /* Create and show a test menu */
            menu_t *menu = ui_menu_create("Test Menu");
            ui_menu_add_item(menu, "Option 1", true);
            ui_menu_add_item(menu, "Option 2", true);
            ui_menu_add_item(menu, "Disabled", false);
            ui_menu_add_item(menu, "Exit Menu", true);
            
            int selection = -2;
            while (selection == -2) {
                ui_menu_draw(menu);
                render_present();
                selection = ui_menu_update(menu);
            }
            
            /* Clean up and return to main screen */
            free(menu);
            
            /* Redraw main screen */
            render_clear_screen(COLOR_BLACK);
            font_draw_text_bg(10, 10, "TI-84 Game Engine", COLOR_WHITE, COLOR_BLUE);
            font_draw_text(10, 30, "Smoke Test v1.0", COLOR_CYAN);
            font_draw_text(10, 50, "[ PASS ] Render Module", COLOR_GREEN);
            font_draw_text(10, 65, "[ PASS ] Input Module", COLOR_GREEN);
            font_draw_text(10, 80, "[ PASS ] Font Module", COLOR_GREEN);
            font_draw_text(10, 95, "[ PASS ] UI Module", COLOR_GREEN);
            font_draw_text(10, 110, "[ PASS ] Save Module", COLOR_GREEN);
            font_draw_text_bg(10, 140, "ENGINE OK", COLOR_BLACK, COLOR_GREEN);
            render_draw_rect(10, 170, 40, 20, COLOR_RED);
            render_draw_rect(55, 170, 40, 20, COLOR_GREEN);
            render_draw_rect(100, 170, 40, 20, COLOR_BLUE);
            render_draw_rect(145, 170, 40, 20, COLOR_YELLOW);
            render_draw_rect(190, 170, 40, 20, COLOR_CYAN);
            render_draw_rect(235, 170, 40, 20, COLOR_MAGENTA);
            font_draw_text(10, 200, "Menu test complete!", COLOR_YELLOW);
            font_draw_text(10, 215, "Press CLEAR to exit", COLOR_WHITE);
            render_present();
        }
        
        /* Exit on clear */
        if (input_button_pressed(BTN_CLEAR)) {
            break;
        }
    }
    
    /* Cleanup */
    render_shutdown();
    
    return 0;
}
