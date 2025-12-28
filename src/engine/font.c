#include "font.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Macro to suppress unused parameter warnings */
#define UNUSED(x) (void)(x)

#ifdef TI84_TARGET
/* TI-84 Plus CE specific implementation would go here */
#else
/* Host stub implementation for testing */
static int initialized = 0;

void font_init(void) {
    if (!initialized) {
        printf("[FONT] Initialized\n");
        initialized = 1;
    }
}

void font_draw_text(const char *text, int x, int y, color_t color, font_size_t size) {
    if (!initialized || !text) return;
    UNUSED(x); UNUSED(y); UNUSED(color); UNUSED(size);
    /* Host stub - just log */
}

void font_draw_number(int number, int x, int y, color_t color, font_size_t size) {
    if (!initialized) return;
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", number);
    font_draw_text(buffer, x, y, color, size);
}

int font_get_text_width(const char *text, font_size_t size) {
    if (!initialized || !text) return 0;
    /* Simple approximation: character width is roughly 60% of size */
    return (int)(strlen(text) * size * 0.6);
}

void font_shutdown(void) {
    if (initialized) {
        printf("[FONT] Shutdown\n");
        initialized = 0;
    }
}
#endif
