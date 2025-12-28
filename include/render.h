/**
 * render.h - Rendering system for TI-84 Pixel Games Engine
 * 
 * Provides framebuffer management, sprite/tile drawing, and palette control
 */

#ifndef ENGINE_RENDER_H
#define ENGINE_RENDER_H

#include <stdint.h>

/* Display dimensions for TI-84 CE (320x240) */
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

/* Tile dimensions */
#define TILE_WIDTH  16
#define TILE_HEIGHT 16

/**
 * Initialize the rendering system
 * Sets up framebuffer and display mode
 * 
 * @return 0 on success, non-zero on failure
 */
int render_init(void);

/**
 * Clear the framebuffer to a solid color
 * 
 * @param color Color index (0-255 for 8-bit palette mode)
 */
void render_clear(uint8_t color);

/**
 * Present the framebuffer to the screen
 * Swaps buffers or copies to display memory
 */
void render_present(void);

/**
 * Draw a tile from the tileset at specified position
 * 
 * @param x X coordinate in pixels
 * @param y Y coordinate in pixels
 * @param tile_id Tile index in tileset
 */
void draw_tile(int x, int y, uint8_t tile_id);

/**
 * Draw a sprite with raw pixel data
 * 
 * @param x X coordinate in pixels
 * @param y Y coordinate in pixels
 * @param w Width in pixels
 * @param h Height in pixels
 * @param data Pointer to pixel data (8-bit indexed color)
 */
void draw_sprite(int x, int y, int w, int h, const uint8_t *data);

/**
 * Set the color palette for indexed color mode
 * 
 * @param palette Pointer to 256 RGB565 color values (512 bytes)
 */
void set_palette(const uint16_t *palette);

/**
 * Draw a single pixel at the specified coordinates
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @param color Color index
 */
void draw_pixel(int x, int y, uint8_t color);

/**
 * Cleanup rendering system resources
 */
void render_cleanup(void);

#endif /* ENGINE_RENDER_H */
