#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <stdbool.h>

// Engine initialization and lifecycle
int engine_init(void);
void engine_shutdown(void);
void engine_tick(void);

// Time tracking
uint32_t engine_time_ms(void);

#endif // ENGINE_H
