#ifndef UI_H
#define UI_H

#include <stdint.h>
#include "render.h"

// Menu item structure
typedef struct {
    const char* text;
    void (*callback)(void);
} menu_item_t;

// Initialize UI system
int ui_init(void);
void ui_shutdown(void);

// Show menu and return selected index (-1 if cancelled)
int ui_menu(const char* title, const menu_item_t* items, int num_items);

// Show message box
void ui_message(const char* title, const char* message);

// Draw simple dialog
void ui_draw_dialog(int x, int y, int w, int h, const char* title);

#endif // UI_H
