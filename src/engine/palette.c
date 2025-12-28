#include "palette.h"
#include <stdio.h>
#include <string.h>

static palette_t current_palette;

// Default grayscale palette
static void init_default_palette(void) {
    for (int i = 0; i < PALETTE_SIZE; i++) {
        current_palette.colors[i].r = i;
        current_palette.colors[i].g = i;
        current_palette.colors[i].b = i;
    }
}

int palette_init(void) {
    init_default_palette();
    return 0;
}

void palette_shutdown(void) {
}

int palette_load(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        return -1;
    }
    
    // Read palette data (expecting RGB triplets)
    for (int i = 0; i < PALETTE_SIZE; i++) {
        uint8_t rgb[3];
        if (fread(rgb, 1, 3, f) != 3) {
            fclose(f);
            return -1;
        }
        current_palette.colors[i].r = rgb[0];
        current_palette.colors[i].g = rgb[1];
        current_palette.colors[i].b = rgb[2];
    }
    
    fclose(f);
    return 0;
}

rgb_color_t palette_get_color(uint8_t index) {
    return current_palette.colors[index];
}

void palette_set_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
    current_palette.colors[index].r = r;
    current_palette.colors[index].g = g;
    current_palette.colors[index].b = b;
}
