/**
 * input.h - Input system for TI-84 Pixel Games Engine
 * 
 * Provides a cross-platform input abstraction layer for button/key input.
 * Supports both TI-84 CE hardware and host platform simulation.
 */

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include <stdint.h>

/**
 * Button bitmask definitions for commonly used keys
 * These map to TI-84 CE keys but can be simulated on host platforms
 */
typedef enum {
    INPUT_NONE   = 0x0000,
    INPUT_UP     = 0x0001,
    INPUT_DOWN   = 0x0002,
    INPUT_LEFT   = 0x0004,
    INPUT_RIGHT  = 0x0008,
    INPUT_ENTER  = 0x0010,
    INPUT_2ND    = 0x0020,
    INPUT_ALPHA  = 0x0040,
    INPUT_CLEAR  = 0x0080,
    INPUT_MODE   = 0x0100,
    INPUT_DEL    = 0x0200,
    INPUT_0      = 0x0400,
    INPUT_1      = 0x0800,
    INPUT_2      = 0x1000,
    INPUT_3      = 0x2000,
    INPUT_4      = 0x4000,
    INPUT_5      = 0x8000
} input_button_t;

/**
 * Initialize the input system
 * Must be called before any other input functions
 * 
 * @return 0 on success, non-zero on failure
 */
int input_init(void);

/**
 * Poll the input hardware for current button states
 * Should be called once per frame
 */
void input_poll(void);

/**
 * Get the current input state as a bitmask
 * 
 * @return Bitmask of currently pressed buttons (input_button_t values OR'd together)
 */
uint16_t input_get(void);

/**
 * Cleanup input system resources
 */
void input_cleanup(void);

#endif /* ENGINE_INPUT_H */
