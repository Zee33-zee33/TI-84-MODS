#ifndef UI_H
#define UI_H

#include <stdint.h>

typedef struct {
    const char *label;
    void (*on_select)(void);
} MenuItem;

void ui_menu(const char *title, MenuItem *items, int count);

#endif
