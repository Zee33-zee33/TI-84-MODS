#include "render.h"
#include <string.h>
#include <stdlib.h>

#ifdef TI84CE
#include <graphx.h>
#endif

static bool initialized = false;

int render_init(void) {
#ifdef TI84CE
    gfx_Begin();
    gfx_SetDrawBuffer();
#endif
    initialized = true;
    return 0;
}

void render_clear_screen(color_t color) {
    if (!initialized) {
        return;
    }
#ifdef TI84CE
    gfx_FillScreen(color);
#else
    (void)color;
#endif
}

void render_draw_pixel(uint16_t x, uint16_t y, color_t color) {
    if (!initialized || x >= LCD_WIDTH || y >= LCD_HEIGHT) {
        return;
    }
#ifdef TI84CE
    gfx_SetPixel(x, y);
    gfx_SetColor(color);
#else
    (void)color;
#endif
}

void render_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, color_t color) {
    if (!initialized) {
        return;
    }
#ifdef TI84CE
    gfx_SetColor(color);
    gfx_FillRectangle(x, y, width, height);
#else
    (void)x;
    (void)y;
    (void)width;
    (void)height;
    (void)color;
#endif
}

void render_draw_sprite(uint16_t x, uint16_t y, const sprite_t *sprite) {
    if (!initialized || !sprite || !sprite->data) {
        return;
    }
    
#ifdef TI84CE
    /* Draw sprite using GraphX */
    gfx_sprite_t *gfx_sprite = (gfx_sprite_t*)sprite->data;
    gfx_TransparentSprite(gfx_sprite, x, y);
#else
    /* Stub implementation - just draw a rectangle */
    render_draw_rect(x, y, sprite->width, sprite->height, COLOR_MAGENTA);
#endif
}

void render_draw_tile(uint16_t x, uint16_t y, uint8_t tile_index, uint16_t tile_size, const sprite_t *tileset) {
    if (!initialized || !tileset) {
        return;
    }
    
    /* Calculate tile position in tileset */
    uint16_t tiles_per_row = tileset->width / tile_size;
    uint16_t tile_x = (tile_index % tiles_per_row) * tile_size;
    uint16_t tile_y = (tile_index / tiles_per_row) * tile_size;
    
#ifdef TI84CE
    /* Draw tile region from tileset */
    gfx_sprite_t *gfx_sprite = (gfx_sprite_t*)tileset->data;
    gfx_TransparentSprite_NoClip(gfx_sprite, x - tile_x, y - tile_y);
#else
    /* Stub implementation */
    render_draw_rect(x, y, tile_size, tile_size, COLOR_GREEN);
    (void)tile_x;
    (void)tile_y;
#endif
}

void render_draw_tilemap(uint16_t x, uint16_t y, const tilemap_t *tilemap) {
    if (!initialized || !tilemap || !tilemap->map_data || !tilemap->tileset) {
        return;
    }
    
    for (uint16_t row = 0; row < tilemap->height; row++) {
        for (uint16_t col = 0; col < tilemap->width; col++) {
            uint8_t tile_index = tilemap->map_data[row * tilemap->width + col];
            uint16_t tile_x = x + col * tilemap->tile_size;
            uint16_t tile_y = y + row * tilemap->tile_size;
            render_draw_tile(tile_x, tile_y, tile_index, tilemap->tile_size, tilemap->tileset);
        }
    }
}

void render_present(void) {
    if (!initialized) {
        return;
    }
#ifdef TI84CE
    gfx_SwapDraw();
#endif
}

void render_shutdown(void) {
    if (!initialized) {
        return;
    }
#ifdef TI84CE
    gfx_End();
#endif
    initialized = false;
}
