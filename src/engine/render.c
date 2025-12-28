#include "render.h"
#include "palette.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Simple framebuffer for terminal rendering
static color_t framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

// ANSI color codes for 256-color terminal
static void set_color(uint8_t fg, uint8_t bg) {
    printf("\033[38;5;%dm\033[48;5;%dm", fg, bg);
}

static void reset_color(void) {
    printf("\033[0m");
}

int render_init(void) {
    // Clear screen and hide cursor
    printf("\033[2J\033[?25l");
    memset(framebuffer, 0, sizeof(framebuffer));
    return 0;
}

void render_shutdown(void) {
    // Show cursor and reset
    printf("\033[?25h");
    reset_color();
}

void render_clear(color_t color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            framebuffer[y][x] = color;
        }
    }
}

void draw_tile(int x, int y, const uint8_t* tile_data, color_t fg, color_t bg) {
    // Draw 8x8 tile from bitmap data
    for (int ty = 0; ty < 8; ty++) {
        for (int tx = 0; tx < 8; tx++) {
            int px = x + tx;
            int py = y + ty;
            
            if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
                // Check bit in tile data
                int byte_idx = ty;
                int bit_idx = 7 - tx;
                bool pixel_on = (tile_data[byte_idx] >> bit_idx) & 1;
                
                framebuffer[py][px] = pixel_on ? fg : bg;
            }
        }
    }
}

void render_rect(int x, int y, int w, int h, color_t color) {
    for (int py = y; py < y + h; py++) {
        for (int px = x; px < x + w; px++) {
            if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
                framebuffer[py][px] = color;
            }
        }
    }
}

void render_present(void) {
    // Move cursor to home
    printf("\033[H");
    
    // Render framebuffer to terminal (downscaled for readability)
    // Render every 4th row and every 2nd column
    for (int y = 0; y < SCREEN_HEIGHT; y += 4) {
        for (int x = 0; x < SCREEN_WIDTH; x += 2) {
            color_t c = framebuffer[y][x];
            set_color(c, c);
            printf("█");
        }
        reset_color();
        printf("\n");
    }
    
    fflush(stdout);
}
