#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

typedef enum {
    BTN_UP     = 1 << 0,
    BTN_DOWN   = 1 << 1,
    BTN_LEFT   = 1 << 2,
    BTN_RIGHT  = 1 << 3,
    BTN_A      = 1 << 4,
    BTN_B      = 1 << 5,
    BTN_START  = 1 << 6,
    BTN_SELECT = 1 << 7
} InputButton;

void input_init(void);
void input_poll(void);
uint32_t input_get(void);
uint32_t input_pressed(void);
uint32_t input_released(void);

#endif
