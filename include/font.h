#ifndef FONT_H
#define FONT_H

#include <stdint.h>
#include "render.h"

typedef struct {
    const uint8_t *bitmap;
    uint8_t char_w;
    uint8_t char_h;
} BitmapFont;

void font_set(const BitmapFont *font);
void font_draw_text(int x, int y, const char *text, Color color);

#endif
