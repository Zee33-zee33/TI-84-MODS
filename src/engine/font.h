#ifndef FONT_H
#define FONT_H

#include "render.h"

/* Font sizes */
typedef enum {
    FONT_SMALL = 8,
    FONT_MEDIUM = 12,
    FONT_LARGE = 16,
    FONT_XLARGE = 24
} font_size_t;

/* Initialize the font system */
void font_init(void);

/* Draw text at position with specified color and size */
void font_draw_text(const char *text, int x, int y, color_t color, font_size_t size);

/* Draw a number at position with specified color and size */
void font_draw_number(int number, int x, int y, color_t color, font_size_t size);

/* Get the width of text in pixels */
int font_get_text_width(const char *text, font_size_t size);

/* Shutdown the font system */
void font_shutdown(void);

#endif /* FONT_H */
