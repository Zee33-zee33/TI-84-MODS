#ifndef FONT_H
#define FONT_H

#include <stdint.h>
#include "render.h"

// Font glyph dimensions
#define GLYPH_WIDTH  8
#define GLYPH_HEIGHT 8

// Initialize font system
int font_init(void);
void font_shutdown(void);

// Draw text at pixel coordinates
void font_draw_text(int x, int y, const char* text, color_t fg, color_t bg);

// Draw single character
void font_draw_char(int x, int y, char c, color_t fg, color_t bg);

// Get text width in pixels
int font_text_width(const char* text);

#endif // FONT_H
