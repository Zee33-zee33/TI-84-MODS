#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <stdbool.h>

void engine_init(void);
void engine_shutdown(void);
void engine_tick(void);

uint32_t engine_time_ms(void);

#endif
