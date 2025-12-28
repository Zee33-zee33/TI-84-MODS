#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include <stdbool.h>

/* Display dimensions for TI-84 CE */
#define LCD_WIDTH  320
#define LCD_HEIGHT 240

/* Tile sizes */
#define TILE_SIZE_8   8
#define TILE_SIZE_16  16

/* Color type (16-bit RGB565) */
typedef uint16_t color_t;

/* Common colors */
#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_YELLOW  0xFFE0
#define COLOR_CYAN    0x07FF
#define COLOR_MAGENTA 0xF81F

/* Sprite structure */
typedef struct {
    uint16_t width;
    uint16_t height;
    const uint16_t *data;
} sprite_t;

/* Tilemap structure */
typedef struct {
    uint16_t tile_size;
    uint16_t width;
    uint16_t height;
    const uint8_t *map_data;
    const sprite_t *tileset;
} tilemap_t;

/**
 * Initialize the rendering system
 * @return 0 on success, -1 on failure
 */
int render_init(void);

/**
 * Clear the screen with a solid color
 * @param color The color to clear with
 */
void render_clear_screen(color_t color);

/**
 * Draw a pixel at the specified position
 * @param x X coordinate
 * @param y Y coordinate
 * @param color Pixel color
 */
void render_draw_pixel(uint16_t x, uint16_t y, color_t color);

/**
 * Draw a filled rectangle
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Rectangle width
 * @param height Rectangle height
 * @param color Fill color
 */
void render_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, color_t color);

/**
 * Draw a sprite at the specified position
 * @param x X coordinate
 * @param y Y coordinate
 * @param sprite Pointer to sprite data
 */
void render_draw_sprite(uint16_t x, uint16_t y, const sprite_t *sprite);

/**
 * Draw a tile from a tileset
 * @param x X coordinate
 * @param y Y coordinate
 * @param tile_index Tile index in tileset
 * @param tile_size Size of tiles (8 or 16)
 * @param tileset Pointer to tileset sprite
 */
void render_draw_tile(uint16_t x, uint16_t y, uint8_t tile_index, uint16_t tile_size, const sprite_t *tileset);

/**
 * Draw a tilemap
 * @param x X coordinate offset
 * @param y Y coordinate offset
 * @param tilemap Pointer to tilemap structure
 */
void render_draw_tilemap(uint16_t x, uint16_t y, const tilemap_t *tilemap);

/**
 * Present the back buffer to the screen
 */
void render_present(void);

/**
 * Shutdown the rendering system
 */
void render_shutdown(void);

#endif /* RENDER_H */
