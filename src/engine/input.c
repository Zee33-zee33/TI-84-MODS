#include "input.h"

static uint32_t current;
static uint32_t previous;

void input_init(void) {
    current = previous = 0;
}

void input_poll(void) {
    previous = current;
    /* HOST STUB
       Replace with hardware scan or emulator hook */
    current = 0;
}

uint32_t input_get(void) {
    return current;
}

uint32_t input_pressed(void) {
    return (current ^ previous) & current;
}

uint32_t input_released(void) {
    return (current ^ previous) & previous;
}
