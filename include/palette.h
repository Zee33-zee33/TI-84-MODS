#ifndef PALETTE_H
#define PALETTE_H

#include <stdint.h>

// RGB color structure
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;

// Palette with 256 colors
#define PALETTE_SIZE 256

typedef struct {
    rgb_color_t colors[PALETTE_SIZE];
} palette_t;

// Initialize palette system
int palette_init(void);
void palette_shutdown(void);

// Load palette from file
int palette_load(const char* filename);

// Get RGB color from palette index
rgb_color_t palette_get_color(uint8_t index);

// Set palette color
void palette_set_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b);

#endif // PALETTE_H
