/**
 * ui.c - User Interface system implementation
 * 
 * Simple menu and dialog rendering using font system
 */

#include "ui.h"
#include "font.h"
#include "render.h"
#include <string.h>

#define UI_COLOR_BG      0
#define UI_COLOR_FG      255
#define UI_COLOR_SELECT  128

void menu_draw(int x, int y, const char *title, const char **items, int count, int selected) {
    if (!title || !items || count <= 0) {
        return;
    }
    
    int cursor_y = y;
    
    /* Draw title */
    draw_text(x, cursor_y, title, UI_COLOR_FG);
    cursor_y += 12; /* Skip a line */
    
    /* Draw menu items */
    for (int i = 0; i < count; i++) {
        if (!items[i]) continue;
        
        uint8_t color = (i == selected) ? UI_COLOR_SELECT : UI_COLOR_FG;
        
        /* Draw selection indicator */
        if (i == selected) {
            draw_text(x, cursor_y, ">", color);
        }
        
        /* Draw menu item */
        draw_text(x + 10, cursor_y, items[i], color);
        cursor_y += 10;
    }
}

void dialog_yes_no(int x, int y, const char *message, int selected) {
    if (!message) {
        return;
    }
    
    /* Draw message */
    draw_text(x, y, message, UI_COLOR_FG);
    
    /* Draw Yes/No options */
    int options_y = y + 20;
    
    uint8_t yes_color = (selected == 0) ? UI_COLOR_SELECT : UI_COLOR_FG;
    uint8_t no_color = (selected == 1) ? UI_COLOR_SELECT : UI_COLOR_FG;
    
    if (selected == 0) {
        draw_text(x, options_y, "> Yes", yes_color);
        draw_text(x + 50, options_y, "  No", no_color);
    } else {
        draw_text(x, options_y, "  Yes", yes_color);
        draw_text(x + 50, options_y, "> No", no_color);
    }
}

void message_box(int x, int y, const char *message) {
    if (!message) {
        return;
    }
    
    /* Draw border (simple implementation) */
    int msg_width = text_width(message);
    int box_width = msg_width + 16;
    int box_height = 24;
    
    /* Draw top border */
    for (int i = 0; i < box_width; i++) {
        draw_pixel(x + i, y, UI_COLOR_FG);
    }
    
    /* Draw bottom border */
    for (int i = 0; i < box_width; i++) {
        draw_pixel(x + i, y + box_height, UI_COLOR_FG);
    }
    
    /* Draw left border */
    for (int i = 0; i < box_height; i++) {
        draw_pixel(x, y + i, UI_COLOR_FG);
    }
    
    /* Draw right border */
    for (int i = 0; i < box_height; i++) {
        draw_pixel(x + box_width, y + i, UI_COLOR_FG);
    }
    
    /* Draw message centered in box */
    draw_text(x + 8, y + 8, message, UI_COLOR_FG);
}
