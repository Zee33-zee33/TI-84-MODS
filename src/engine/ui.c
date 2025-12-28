#include "ui.h"
#include "input.h"
#include "font.h"
#include "render.h"

void ui_menu(const char *title, MenuItem *items, int count) {
    static int index = 0;

    if (input_pressed() & BTN_UP)    index = (index - 1 + count) % count;
    if (input_pressed() & BTN_DOWN)  index = (index + 1) % count;
    if (input_pressed() & BTN_A)     items[index].on_select();

    render_clear((Color){0,0,0});
    font_draw_text(10, 5, title, (Color){255,255,255});

    for (int i = 0; i < count; ++i) {
        Color c = (i == index) ? (Color){255,255,0} : (Color){200,200,200};
        font_draw_text(10, 20 + i * 10, items[i].label, c);
    }

    render_present();
}
