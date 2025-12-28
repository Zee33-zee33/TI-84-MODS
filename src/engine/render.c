#include "render.h"
#include <stdlib.h>
#include <string.h>

static uint16_t W, H;
static Color *framebuffer;

void render_init(uint16_t width, uint16_t height) {
    W = width;
    H = height;
    framebuffer = calloc(W * H, sizeof(Color));
}

void render_clear(Color c) {
    for (int i = 0; i < W * H; ++i)
        framebuffer[i] = c;
}

void draw_pixel(int x, int y, Color c) {
    if (x < 0 || y < 0 || x >= W || y >= H) return;
    framebuffer[y * W + x] = c;
}

void draw_rect(int x, int y, int w, int h, Color c) {
    for (int iy = 0; iy < h; ++iy)
        for (int ix = 0; ix < w; ++ix)
            draw_pixel(x + ix, y + iy, c);
}

void draw_sprite(int x, int y, const uint8_t *sprite, int w, int h) {
    for (int iy = 0; iy < h; ++iy) {
        for (int ix = 0; ix < w; ++ix) {
            uint8_t v = sprite[iy * w + ix];
            if (v) draw_pixel(x + ix, y + iy, (Color){v, v, v});
        }
    }
}

void render_present(void) {
    /* HOST STUB
       On CE / SDL / framebuffer, flush here */
}

uint16_t render_width(void) { return W; }
uint16_t render_height(void) { return H; }
