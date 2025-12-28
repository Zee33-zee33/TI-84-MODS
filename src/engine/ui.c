#include "ui.h"
#include "font.h"
#include "render.h"
#include "input.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int ui_init(void) {
    return 0;
}

void ui_shutdown(void) {
}

void ui_draw_dialog(int x, int y, int w, int h, const char* title) {
    // Draw border
    render_rect(x, y, w, h, 15);  // White background
    render_rect(x, y, w, 2, 1);   // Black title bar
    
    // Draw title
    if (title) {
        font_draw_text(x + 4, y + 2, title, 15, 1);
    }
}

int ui_menu(const char* title, const menu_item_t* items, int num_items) {
    if (num_items == 0) {
        return -1;
    }
    
    int selected = 0;
    
    while (1) {
        // Clear and draw menu
        render_clear(0);
        
        int menu_x = 40;
        int menu_y = 40;
        int menu_w = 240;
        int menu_h = 20 + num_items * 12;
        
        ui_draw_dialog(menu_x, menu_y, menu_w, menu_h, title);
        
        // Draw menu items
        for (int i = 0; i < num_items; i++) {
            int item_y = menu_y + 20 + i * 12;
            color_t fg = (i == selected) ? 0 : 8;
            color_t bg = (i == selected) ? 14 : 15;
            
            char text[64];
            snprintf(text, sizeof(text), "%s %s", 
                    (i == selected) ? ">" : " ", 
                    items[i].text);
            
            font_draw_text(menu_x + 4, item_y, text, fg, bg);
        }
        
        render_present();
        
        // Handle input
        input_update();
        
        if (input_key_pressed(KEY_UP) || input_key_pressed('w')) {
            selected = (selected - 1 + num_items) % num_items;
        }
        if (input_key_pressed(KEY_DOWN) || input_key_pressed('s')) {
            selected = (selected + 1) % num_items;
        }
        if (input_key_pressed(KEY_ENTER) || input_key_pressed(' ')) {
            if (items[selected].callback) {
                items[selected].callback();
            }
            return selected;
        }
        if (input_key_pressed(KEY_ESC) || input_key_pressed('q')) {
            return -1;
        }
        
        // Simple delay to prevent spinning
        usleep(50000);
    }
}

void ui_message(const char* title, const char* message) {
    render_clear(0);
    
    int msg_x = 60;
    int msg_y = 80;
    int msg_w = 200;
    int msg_h = 80;
    
    ui_draw_dialog(msg_x, msg_y, msg_w, msg_h, title);
    
    // Draw message
    font_draw_text(msg_x + 8, msg_y + 24, message, 0, 15);
    font_draw_text(msg_x + 8, msg_y + 56, "Press any key...", 8, 15);
    
    render_present();
    
    // Wait for key press
    while (1) {
        input_update();
        
        // Check for any key
        for (int i = 0; i < 256; i++) {
            if (input_key_pressed(i)) {
                return;
            }
        }
        
        usleep(50000);
    }
}
