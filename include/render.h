#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t r, g, b;
} Color;

void render_init(uint16_t width, uint16_t height);
void render_clear(Color c);
void render_present(void);

void draw_pixel(int x, int y, Color c);
void draw_rect(int x, int y, int w, int h, Color c);
void draw_sprite(int x, int y, const uint8_t *sprite, int w, int h);

uint16_t render_width(void);
uint16_t render_height(void);

#endif
