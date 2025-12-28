/**
 * render.c - Rendering system implementation
 * 
 * Framebuffer-based rendering with tile and sprite support
 */

#include "render.h"
#include <string.h>
#include <stdlib.h>

/* Platform detection */
#ifdef __TI84PCE__
    #define PLATFORM_CE 1
    /* CE-specific graphics includes would go here */
    /* #include <graphx.h> */
#else
    #define PLATFORM_HOST 1
#endif

/* Framebuffer (8-bit indexed color) */
static uint8_t *framebuffer = NULL;
static uint16_t palette[256];

/* Stub tileset (16x16 tiles, 8x8 pattern for testing) */
#define MAX_TILES 256
static uint8_t tileset[MAX_TILES * TILE_WIDTH * TILE_HEIGHT];

int render_init(void) {
#ifdef PLATFORM_CE
    /* Initialize CE graphics library */
    /* gfx_Begin(); */
    /* gfx_SetDrawBuffer(); */
    
    /* Use CE framebuffer */
    /* framebuffer = gfx_vbuffer; */
    framebuffer = NULL; /* Stub for now */
    
#else
    /* Allocate framebuffer on host */
    framebuffer = (uint8_t*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT);
    if (!framebuffer) {
        return -1;
    }
#endif
    
    /* Initialize default palette (grayscale) */
    for (int i = 0; i < 256; i++) {
        /* RGB565: 5 bits red, 6 bits green, 5 bits blue */
        uint8_t gray = i;
        uint16_t r = (gray >> 3) & 0x1F;
        uint16_t g = (gray >> 2) & 0x3F;
        uint16_t b = (gray >> 3) & 0x1F;
        palette[i] = (r << 11) | (g << 5) | b;
    }
    
    /* Initialize stub tileset with simple patterns */
    memset(tileset, 0, sizeof(tileset));
    
    return 0;
}

void render_clear(uint8_t color) {
    /* Stub implementation: Silent no-op when framebuffer not initialized.
     * In production, framebuffer will always be valid after render_init(). */
    if (!framebuffer) return;
    
#ifdef PLATFORM_CE
    /* Use CE graphics library clear */
    /* gfx_FillScreen(color); */
    
    /* Stub: fill framebuffer */
    /* memset(framebuffer, color, SCREEN_WIDTH * SCREEN_HEIGHT); */
#else
    memset(framebuffer, color, SCREEN_WIDTH * SCREEN_HEIGHT);
#endif
}

void render_present(void) {
#ifdef PLATFORM_CE
    /* Swap buffers on CE */
    /* gfx_SwapDraw(); */
    /* Or copy to screen: gfx_Blit(gfx_buffer); */
#else
    /* On host: no-op (framebuffer is already "displayed" in memory) */
    /* In a real implementation, could output to terminal or SDL window */
#endif
}

void draw_tile(int x, int y, uint8_t tile_id) {
    if (!framebuffer) return;
    
    /* Bounds check */
    if (x < 0 || y < 0 || x + TILE_WIDTH > SCREEN_WIDTH || y + TILE_HEIGHT > SCREEN_HEIGHT) {
        return;
    }
    
    /* Draw tile from tileset */
    const uint8_t *tile_data = &tileset[tile_id * TILE_WIDTH * TILE_HEIGHT];
    
    for (int ty = 0; ty < TILE_HEIGHT; ty++) {
        for (int tx = 0; tx < TILE_WIDTH; tx++) {
            uint8_t pixel = tile_data[ty * TILE_WIDTH + tx];
            if (pixel != 0) { /* 0 = transparent */
                int px = x + tx;
                int py = y + ty;
                if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
                    framebuffer[py * SCREEN_WIDTH + px] = pixel;
                }
            }
        }
    }
}

void draw_sprite(int x, int y, int w, int h, const uint8_t *data) {
    if (!framebuffer || !data) return;
    
    /* Bounds check and clipping */
    for (int sy = 0; sy < h; sy++) {
        for (int sx = 0; sx < w; sx++) {
            int px = x + sx;
            int py = y + sy;
            
            if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
                uint8_t pixel = data[sy * w + sx];
                if (pixel != 0) { /* 0 = transparent */
                    framebuffer[py * SCREEN_WIDTH + px] = pixel;
                }
            }
        }
    }
}

void set_palette(const uint16_t *pal) {
    if (pal) {
        memcpy(palette, pal, sizeof(palette));
    }
    
#ifdef PLATFORM_CE
    /* Apply palette to CE hardware */
    /* gfx_SetPalette(pal, sizeof(palette), 0); */
#endif
}

void draw_pixel(int x, int y, uint8_t color) {
    if (!framebuffer) return;
    
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        framebuffer[y * SCREEN_WIDTH + x] = color;
    }
}

void render_cleanup(void) {
#ifdef PLATFORM_CE
    /* Cleanup CE graphics */
    /* gfx_End(); */
#else
    if (framebuffer) {
        free(framebuffer);
        framebuffer = NULL;
    }
#endif
}
