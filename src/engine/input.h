#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

/* Key codes */
typedef enum {
    KEY_NONE = 0,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_2ND,
    KEY_ALPHA,
    KEY_CLEAR,
    KEY_DEL
} key_t;

/* Initialize the input system */
void input_init(void);

/* Poll for input and return the key pressed (non-blocking) */
key_t input_get_key(void);

/* Wait for a key press (blocking) */
key_t input_wait_key(void);

/* Check if a specific key is currently pressed */
int input_is_key_pressed(key_t key);

/* Shutdown the input system */
void input_shutdown(void);

#endif /* INPUT_H */
