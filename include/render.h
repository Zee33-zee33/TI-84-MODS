#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

// Screen dimensions for terminal rendering
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#define TILE_SIZE     16

// Color type (palette index)
typedef uint8_t color_t;

// Initialize renderer
int render_init(void);
void render_shutdown(void);

// Clear screen
void render_clear(color_t color);

// Draw tile at pixel coordinates
void draw_tile(int x, int y, const uint8_t* tile_data, color_t fg, color_t bg);

// Draw rectangle
void render_rect(int x, int y, int w, int h, color_t color);

// Present frame to screen
void render_present(void);

#endif // RENDER_H
