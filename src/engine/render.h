#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

/* Color type for TI-84 Plus CE (RGB565 format) */
typedef uint16_t color_t;

/* RGB565 color helper */
#define RGB(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

/* Common colors */
#define COLOR_BLACK     RGB(0, 0, 0)
#define COLOR_WHITE     RGB(255, 255, 255)
#define COLOR_RED       RGB(255, 0, 0)
#define COLOR_GREEN     RGB(0, 255, 0)
#define COLOR_BLUE      RGB(0, 0, 255)
#define COLOR_YELLOW    RGB(255, 255, 0)
#define COLOR_ORANGE    RGB(255, 165, 0)
#define COLOR_GRAY      RGB(128, 128, 128)

/* Screen dimensions */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

/* Initialize the rendering system */
void render_init(void);

/* Clear the screen with a color */
void render_clear(color_t color);

/* Draw a filled rectangle */
void render_fill_rect(int x, int y, int width, int height, color_t color);

/* Draw a rectangle outline */
void render_rect(int x, int y, int width, int height, color_t color);

/* Swap front and back buffers (for double buffering) */
void render_flip(void);

/* Shutdown the rendering system */
void render_shutdown(void);

#endif /* RENDER_H */
