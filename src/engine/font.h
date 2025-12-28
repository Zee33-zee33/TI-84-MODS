/**
 * font.h - Font rendering system for TI-84 Pixel Games Engine
 * 
 * Provides bitmap font rendering for text and numbers
 */

#ifndef ENGINE_FONT_H
#define ENGINE_FONT_H

#include <stdint.h>

/**
 * Initialize font system with embedded bitmap font
 * 
 * @return 0 on success, non-zero on failure
 */
int font_init(void);

/**
 * Load a font from a binary blob
 * Font format: 8x8 bitmap, 1 bit per pixel, 8 bytes per character
 * 
 * @param data Pointer to font data (2048 bytes for 256 chars)
 * @return 0 on success, non-zero on failure
 */
int font_load_from_blob(const uint8_t *data);

/**
 * Draw text at specified position
 * 
 * @param x X coordinate in pixels
 * @param y Y coordinate in pixels
 * @param text Null-terminated string to draw
 * @param color Color index for text
 */
void draw_text(int x, int y, const char *text, uint8_t color);

/**
 * Draw a number at specified position
 * 
 * @param x X coordinate in pixels
 * @param y Y coordinate in pixels
 * @param number Number to draw
 * @param color Color index for text
 */
void draw_number(int x, int y, int number, uint8_t color);

/**
 * Get the width of a text string in pixels
 * 
 * @param text String to measure
 * @return Width in pixels
 */
int text_width(const char *text);

#endif /* ENGINE_FONT_H */
