#define _POSIX_C_SOURCE 199309L
#include "engine.h"
#include "input.h"
#include <time.h>

static uint32_t start_ms;

static uint32_t now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void engine_init(void) {
    start_ms = now_ms();
    input_init();
}

void engine_shutdown(void) {}

void engine_tick(void) {
    input_poll();
}

uint32_t engine_time_ms(void) {
    return now_ms() - start_ms;
}
