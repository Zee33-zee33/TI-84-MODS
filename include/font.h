#ifndef FONT_H
#define FONT_H

#include <stdint.h>
#include "render.h"

/* Font structure */
typedef struct {
    uint8_t char_width;
    uint8_t char_height;
    uint8_t first_char;
    uint8_t last_char;
    const uint8_t *bitmap_data;
} font_t;

/* Text alignment options */
typedef enum {
    TEXT_ALIGN_LEFT = 0,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT
} text_align_t;

/**
 * Initialize the font system with a default font
 * @return 0 on success, -1 on failure
 */
int font_init(void);

/**
 * Load a custom font
 * @param font Pointer to font structure
 * @return 0 on success, -1 on failure
 */
int font_load(const font_t *font);

/**
 * Get the default built-in font
 * @return Pointer to default font
 */
const font_t *font_get_default(void);

/**
 * Draw text at the specified position
 * @param x X coordinate
 * @param y Y coordinate
 * @param text Text string to draw
 * @param color Text color
 */
void font_draw_text(uint16_t x, uint16_t y, const char *text, color_t color);

/**
 * Draw text with background
 * @param x X coordinate
 * @param y Y coordinate
 * @param text Text string to draw
 * @param fg_color Foreground color
 * @param bg_color Background color
 */
void font_draw_text_bg(uint16_t x, uint16_t y, const char *text, color_t fg_color, color_t bg_color);

/**
 * Draw aligned text
 * @param x X coordinate (left edge for LEFT, center for CENTER, right edge for RIGHT)
 * @param y Y coordinate
 * @param text Text string to draw
 * @param color Text color
 * @param align Text alignment
 */
void font_draw_text_aligned(uint16_t x, uint16_t y, const char *text, color_t color, text_align_t align);

/**
 * Get the width of a text string in pixels
 * @param text Text string to measure
 * @return Width in pixels
 */
uint16_t font_get_text_width(const char *text);

/**
 * Get the height of the current font
 * @return Height in pixels
 */
uint8_t font_get_height(void);

#endif /* FONT_H */
