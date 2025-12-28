#include "render.h"
#include <stdio.h>
#include <string.h>

/* Macro to suppress unused parameter warnings */
#define UNUSED(x) (void)(x)

#ifdef TI84_TARGET
/* TI-84 Plus CE specific implementation would go here */
#include <graphx.h>
#else
/* Host stub implementation for testing */
static int initialized = 0;

void render_init(void) {
    if (!initialized) {
        printf("[RENDER] Initialized\n");
        initialized = 1;
    }
}

void render_clear(color_t color) {
    if (!initialized) return;
    UNUSED(color);
    /* Host stub - just log */
}

void render_fill_rect(int x, int y, int width, int height, color_t color) {
    if (!initialized) return;
    UNUSED(x); UNUSED(y); UNUSED(width); UNUSED(height); UNUSED(color);
    /* Host stub - just log */
}

void render_rect(int x, int y, int width, int height, color_t color) {
    if (!initialized) return;
    UNUSED(x); UNUSED(y); UNUSED(width); UNUSED(height); UNUSED(color);
    /* Host stub - just log */
}

void render_flip(void) {
    if (!initialized) return;
    /* Host stub - just log */
}

void render_shutdown(void) {
    if (initialized) {
        printf("[RENDER] Shutdown\n");
        initialized = 0;
    }
}
#endif
