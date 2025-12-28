#include "ui.h"
#include "input.h"
#include "font.h"
#include <string.h>
#include <stdlib.h>

static bool initialized = false;

int ui_init(void) {
    initialized = true;
    return 0;
}

menu_t *ui_menu_create(const char *title) {
    if (!title) {
        return NULL;
    }
    
    menu_t *menu = (menu_t *)malloc(sizeof(menu_t));
    if (!menu) {
        return NULL;
    }
    
    memset(menu, 0, sizeof(menu_t));
    menu->title = title;
    menu->item_count = 0;
    menu->selected_index = 0;
    
    return menu;
}

int ui_menu_add_item(menu_t *menu, const char *text, bool enabled) {
    if (!menu || !text || menu->item_count >= MAX_MENU_ITEMS) {
        return -1;
    }
    
    strncpy(menu->items[menu->item_count].text, text, MAX_MENU_TEXT_LEN - 1);
    menu->items[menu->item_count].text[MAX_MENU_TEXT_LEN - 1] = '\0';
    menu->items[menu->item_count].enabled = enabled ? 1 : 0;
    menu->item_count++;
    
    return 0;
}

void ui_menu_draw(const menu_t *menu) {
    if (!initialized || !menu) {
        return;
    }
    
    /* Clear screen */
    render_clear_screen(COLOR_BLACK);
    
    /* Draw title */
    if (menu->title) {
        font_draw_text_aligned(LCD_WIDTH / 2, 20, menu->title, COLOR_WHITE, TEXT_ALIGN_CENTER);
    }
    
    /* Draw menu items */
    uint16_t item_y = 60;
    uint16_t item_height = font_get_height() + 10;
    
    for (uint8_t i = 0; i < menu->item_count; i++) {
        bool selected = (i == menu->selected_index);
        color_t text_color = menu->items[i].enabled ? COLOR_WHITE : COLOR_BLUE;
        
        /* Draw selection indicator */
        if (selected) {
            render_draw_rect(30, item_y - 2, LCD_WIDTH - 60, item_height, COLOR_BLUE);
            font_draw_text(40, item_y + 2, menu->items[i].text, COLOR_YELLOW);
        } else {
            font_draw_text(40, item_y + 2, menu->items[i].text, text_color);
        }
        
        item_y += item_height;
    }
}

int ui_menu_update(menu_t *menu) {
    if (!initialized || !menu || menu->item_count == 0) {
        return -1;
    }
    
    input_poll();
    
    /* Handle up/down navigation */
    if (input_button_pressed(BTN_UP)) {
        if (menu->selected_index > 0) {
            menu->selected_index--;
        } else {
            menu->selected_index = menu->item_count - 1;
        }
    }
    
    if (input_button_pressed(BTN_DOWN)) {
        if (menu->selected_index < menu->item_count - 1) {
            menu->selected_index++;
        } else {
            menu->selected_index = 0;
        }
    }
    
    /* Handle selection */
    if (input_button_pressed(BTN_ENTER)) {
        if (menu->items[menu->selected_index].enabled) {
            return menu->selected_index;
        }
    }
    
    /* Handle cancel */
    if (input_button_pressed(BTN_CLEAR)) {
        return -1;
    }
    
    return -2; /* No selection made */
}

dialog_result_t ui_dialog_yes_no(const char *title, const char *message) {
    if (!initialized || !title || !message) {
        return DIALOG_CANCEL;
    }
    
    const uint16_t dialog_width = 240;
    const uint16_t dialog_height = 120;
    const uint16_t dialog_x = (LCD_WIDTH - dialog_width) / 2;
    const uint16_t dialog_y = (LCD_HEIGHT - dialog_height) / 2;
    
    uint8_t selected = 0; /* 0 = Yes, 1 = No */
    
    while (1) {
        /* Draw dialog box */
        ui_draw_dialog_box(dialog_x, dialog_y, dialog_width, dialog_height, title);
        
        /* Draw message */
        font_draw_text_aligned(LCD_WIDTH / 2, dialog_y + 40, message, COLOR_WHITE, TEXT_ALIGN_CENTER);
        
        /* Draw buttons */
        ui_draw_button(dialog_x + 30, dialog_y + 80, 80, "Yes", selected == 0);
        ui_draw_button(dialog_x + 130, dialog_y + 80, 80, "No", selected == 1);
        
        render_present();
        
        /* Handle input */
        input_poll();
        
        if (input_button_pressed(BTN_LEFT) || input_button_pressed(BTN_RIGHT)) {
            selected = 1 - selected;
        }
        
        if (input_button_pressed(BTN_ENTER)) {
            return selected == 0 ? DIALOG_YES : DIALOG_NO;
        }
        
        if (input_button_pressed(BTN_CLEAR)) {
            return DIALOG_CANCEL;
        }
    }
}

void ui_dialog_ok(const char *title, const char *message) {
    if (!initialized || !title || !message) {
        return;
    }
    
    const uint16_t dialog_width = 240;
    const uint16_t dialog_height = 120;
    const uint16_t dialog_x = (LCD_WIDTH - dialog_width) / 2;
    const uint16_t dialog_y = (LCD_HEIGHT - dialog_height) / 2;
    
    while (1) {
        /* Draw dialog box */
        ui_draw_dialog_box(dialog_x, dialog_y, dialog_width, dialog_height, title);
        
        /* Draw message */
        font_draw_text_aligned(LCD_WIDTH / 2, dialog_y + 40, message, COLOR_WHITE, TEXT_ALIGN_CENTER);
        
        /* Draw OK button */
        ui_draw_button(dialog_x + 80, dialog_y + 80, 80, "OK", true);
        
        render_present();
        
        /* Handle input */
        input_poll();
        
        if (input_button_pressed(BTN_ENTER) || input_button_pressed(BTN_CLEAR)) {
            return;
        }
    }
}

void ui_draw_dialog_box(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const char *title) {
    /* Draw background */
    render_draw_rect(x, y, width, height, COLOR_BLACK);
    
    /* Draw border */
    render_draw_rect(x, y, width, 2, COLOR_WHITE);
    render_draw_rect(x, y, 2, height, COLOR_WHITE);
    render_draw_rect(x + width - 2, y, 2, height, COLOR_WHITE);
    render_draw_rect(x, y + height - 2, width, 2, COLOR_WHITE);
    
    /* Draw title bar */
    if (title) {
        render_draw_rect(x + 2, y + 2, width - 4, 20, COLOR_BLUE);
        font_draw_text_aligned(x + width / 2, y + 8, title, COLOR_WHITE, TEXT_ALIGN_CENTER);
    }
}

void ui_draw_button(uint16_t x, uint16_t y, uint16_t width, const char *text, bool selected) {
    color_t bg_color = selected ? COLOR_GREEN : COLOR_BLUE;
    color_t text_color = COLOR_WHITE;
    
    /* Draw button background */
    render_draw_rect(x, y, width, 24, bg_color);
    
    /* Draw button border */
    render_draw_rect(x, y, width, 2, COLOR_WHITE);
    render_draw_rect(x, y, 2, 24, COLOR_WHITE);
    render_draw_rect(x + width - 2, y, 2, 24, COLOR_WHITE);
    render_draw_rect(x, y + 22, width, 2, COLOR_WHITE);
    
    /* Draw text centered */
    if (text) {
        font_draw_text_aligned(x + width / 2, y + 8, text, text_color, TEXT_ALIGN_CENTER);
    }
}
