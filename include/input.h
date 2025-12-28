#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdbool.h>

/* Button definitions for TI-84 CE */
typedef enum {
    BTN_NONE = 0,
    BTN_UP,
    BTN_DOWN,
    BTN_LEFT,
    BTN_RIGHT,
    BTN_ENTER,
    BTN_CLEAR,
    BTN_2ND,
    BTN_ALPHA,
    BTN_0,
    BTN_1,
    BTN_2,
    BTN_3,
    BTN_4,
    BTN_5,
    BTN_6,
    BTN_7,
    BTN_8,
    BTN_9,
    BTN_MODE,
    BTN_DEL,
    BTN_PLUS,
    BTN_MINUS,
    BTN_MULT,
    BTN_DIV
} button_t;

/* Input state structure */
typedef struct {
    uint8_t keys[8];
    uint8_t prev_keys[8];
} input_state_t;

/**
 * Initialize the input system
 * @return 0 on success, -1 on failure
 */
int input_init(void);

/**
 * Poll current key state from calculator
 */
void input_poll(void);

/**
 * Get the state of a specific button
 * @param button The button to check
 * @return true if button is currently pressed
 */
bool input_get_button(button_t button);

/**
 * Check if a button was just pressed (rising edge)
 * @param button The button to check
 * @return true if button was just pressed this frame
 */
bool input_button_pressed(button_t button);

/**
 * Check if a button was just released (falling edge)
 * @param button The button to check
 * @return true if button was just released this frame
 */
bool input_button_released(button_t button);

/**
 * Wait for any key press
 */
void input_wait_any_key(void);

#endif /* INPUT_H */
