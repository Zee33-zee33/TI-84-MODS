#include "font.h"
#include <string.h>

static const BitmapFont *active_font = NULL;

void font_set(const BitmapFont *font) {
    active_font = font;
}

void font_draw_text(int x, int y, const char *text, Color color) {
    if (!active_font) return;

    int cx = x;
    while (*text) {
        char ch = *text++;
        const uint8_t *glyph =
            &active_font->bitmap[(ch - 32) *
             active_font->char_w *
             active_font->char_h];

        for (int gy = 0; gy < active_font->char_h; ++gy)
            for (int gx = 0; gx < active_font->char_w; ++gx)
                if (glyph[gy * active_font->char_w + gx])
                    draw_pixel(cx + gx, y + gy, color);

        cx += active_font->char_w;
    }
}
