#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdbool.h>

// Key codes for host/terminal input
#define KEY_UP    'w'
#define KEY_DOWN  's'
#define KEY_LEFT  'a'
#define KEY_RIGHT 'd'
#define KEY_ENTER '\n'
#define KEY_ESC   27

// Input state
typedef struct {
    bool key_pressed[256];
} input_state_t;

// Initialize input system
int input_init(void);
void input_shutdown(void);

// Update input state (non-blocking)
void input_update(void);

// Query key state
bool input_key_down(uint8_t key);
bool input_key_pressed(uint8_t key);

#endif // INPUT_H
