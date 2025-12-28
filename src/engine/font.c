#include "font.h"
#include <string.h>

/* Simple 5x7 bitmap font data */
static const uint8_t default_font_data[] = {
    /* Space (32) */
    0x00, 0x00, 0x00, 0x00, 0x00,
    /* ! (33) */
    0x00, 0x00, 0x5F, 0x00, 0x00,
    /* " (34) */
    0x00, 0x07, 0x00, 0x07, 0x00,
    /* # (35) */
    0x14, 0x7F, 0x14, 0x7F, 0x14,
    /* $ (36) */
    0x24, 0x2A, 0x7F, 0x2A, 0x12,
    /* More characters would go here... */
    /* For brevity, only including a few */
    
    /* A (65) - starting at index for uppercase */
    0x7C, 0x12, 0x11, 0x12, 0x7C,
    /* B */
    0x7F, 0x49, 0x49, 0x49, 0x36,
    /* C */
    0x3E, 0x41, 0x41, 0x41, 0x22,
    /* D */
    0x7F, 0x41, 0x41, 0x22, 0x1C,
    /* E */
    0x7F, 0x49, 0x49, 0x49, 0x41,
    /* F */
    0x7F, 0x09, 0x09, 0x09, 0x01,
    /* G */
    0x3E, 0x41, 0x49, 0x49, 0x7A,
    /* H */
    0x7F, 0x08, 0x08, 0x08, 0x7F,
    /* I */
    0x00, 0x41, 0x7F, 0x41, 0x00,
    /* J */
    0x20, 0x40, 0x41, 0x3F, 0x01,
    /* K */
    0x7F, 0x08, 0x14, 0x22, 0x41,
    /* L */
    0x7F, 0x40, 0x40, 0x40, 0x40,
    /* M */
    0x7F, 0x02, 0x0C, 0x02, 0x7F,
    /* N */
    0x7F, 0x04, 0x08, 0x10, 0x7F,
    /* O */
    0x3E, 0x41, 0x41, 0x41, 0x3E,
    /* P */
    0x7F, 0x09, 0x09, 0x09, 0x06,
    /* Q */
    0x3E, 0x41, 0x51, 0x21, 0x5E,
    /* R */
    0x7F, 0x09, 0x19, 0x29, 0x46,
    /* S */
    0x46, 0x49, 0x49, 0x49, 0x31,
    /* T */
    0x01, 0x01, 0x7F, 0x01, 0x01,
    /* U */
    0x3F, 0x40, 0x40, 0x40, 0x3F,
    /* V */
    0x1F, 0x20, 0x40, 0x20, 0x1F,
    /* W */
    0x3F, 0x40, 0x38, 0x40, 0x3F,
    /* X */
    0x63, 0x14, 0x08, 0x14, 0x63,
    /* Y */
    0x07, 0x08, 0x70, 0x08, 0x07,
    /* Z */
    0x61, 0x51, 0x49, 0x45, 0x43,
};

static const font_t default_font = {
    .char_width = 5,
    .char_height = 7,
    .first_char = 32,
    .last_char = 90,
    .bitmap_data = default_font_data
};

static const font_t *current_font = NULL;

int font_init(void) {
    current_font = &default_font;
    return 0;
}

int font_load(const font_t *font) {
    if (!font) {
        return -1;
    }
    current_font = font;
    return 0;
}

const font_t *font_get_default(void) {
    return &default_font;
}

void font_draw_text(uint16_t x, uint16_t y, const char *text, color_t color) {
    if (!current_font || !text) {
        return;
    }
    
    uint16_t cursor_x = x;
    
    for (const char *c = text; *c != '\0'; c++) {
        uint8_t ch = (uint8_t)*c;
        
        /* Handle newline */
        if (ch == '\n') {
            cursor_x = x;
            y += current_font->char_height + 2;
            continue;
        }
        
        /* Check if character is in font range */
        if (ch < current_font->first_char || ch > current_font->last_char) {
            ch = '?';
        }
        
        /* Get character data offset */
        uint16_t char_index = ch - current_font->first_char;
        const uint8_t *char_data = &current_font->bitmap_data[char_index * current_font->char_width];
        
        /* Draw character bitmap */
        for (uint8_t col = 0; col < current_font->char_width; col++) {
            uint8_t column_data = char_data[col];
            for (uint8_t row = 0; row < current_font->char_height; row++) {
                if (column_data & (1 << row)) {
                    render_draw_pixel(cursor_x + col, y + row, color);
                }
            }
        }
        
        cursor_x += current_font->char_width + 1;
    }
}

void font_draw_text_bg(uint16_t x, uint16_t y, const char *text, color_t fg_color, color_t bg_color) {
    if (!current_font || !text) {
        return;
    }
    
    /* Calculate text dimensions */
    uint16_t text_width = font_get_text_width(text);
    uint16_t text_height = current_font->char_height;
    
    /* Draw background */
    render_draw_rect(x, y, text_width, text_height, bg_color);
    
    /* Draw text on top */
    font_draw_text(x, y, text, fg_color);
}

void font_draw_text_aligned(uint16_t x, uint16_t y, const char *text, color_t color, text_align_t align) {
    if (!text) {
        return;
    }
    
    uint16_t text_width = font_get_text_width(text);
    uint16_t draw_x = x;
    
    switch (align) {
        case TEXT_ALIGN_CENTER:
            draw_x = x - text_width / 2;
            break;
        case TEXT_ALIGN_RIGHT:
            draw_x = x - text_width;
            break;
        case TEXT_ALIGN_LEFT:
        default:
            draw_x = x;
            break;
    }
    
    font_draw_text(draw_x, y, text, color);
}

uint16_t font_get_text_width(const char *text) {
    if (!current_font || !text) {
        return 0;
    }
    
    uint16_t width = 0;
    for (const char *c = text; *c != '\0'; c++) {
        if (*c == '\n') {
            continue;
        }
        width += current_font->char_width + 1;
    }
    
    /* Remove trailing spacing */
    if (width > 0) {
        width -= 1;
    }
    
    return width;
}

uint8_t font_get_height(void) {
    if (!current_font) {
        return 0;
    }
    return current_font->char_height;
}
