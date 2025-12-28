#include "input.h"
#include <string.h>

#ifdef TI84CE
#include <keypadc.h>
#endif

static input_state_t state;
static bool initialized = false;

int input_init(void) {
    memset(&state, 0, sizeof(input_state_t));
    initialized = true;
    return 0;
}

void input_poll(void) {
    if (!initialized) {
        return;
    }
    
    /* Save previous state */
    memcpy(state.prev_keys, state.keys, sizeof(state.keys));
    
#ifdef TI84CE
    /* Read keys from calculator hardware */
    kb_Scan();
    state.keys[0] = kb_Data[1];
    state.keys[1] = kb_Data[2];
    state.keys[2] = kb_Data[3];
    state.keys[3] = kb_Data[4];
    state.keys[4] = kb_Data[5];
    state.keys[5] = kb_Data[6];
    state.keys[6] = kb_Data[7];
    state.keys[7] = 0;
#else
    /* Stub for non-calculator builds */
    memset(state.keys, 0, sizeof(state.keys));
#endif
}

static bool check_key(button_t button, const uint8_t *keys) {
#ifdef TI84CE
    switch (button) {
        case BTN_UP:    return keys[6] & kb_Up;
        case BTN_DOWN:  return keys[6] & kb_Down;
        case BTN_LEFT:  return keys[6] & kb_Left;
        case BTN_RIGHT: return keys[6] & kb_Right;
        case BTN_ENTER: return keys[5] & kb_Enter;
        case BTN_CLEAR: return keys[5] & kb_Clear;
        case BTN_2ND:   return keys[0] & kb_2nd;
        case BTN_ALPHA: return keys[3] & kb_Alpha;
        case BTN_MODE:  return keys[2] & kb_Mode;
        case BTN_DEL:   return keys[2] & kb_Del;
        case BTN_0:     return keys[3] & kb_0;
        case BTN_1:     return keys[4] & kb_1;
        case BTN_2:     return keys[4] & kb_2;
        case BTN_3:     return keys[4] & kb_3;
        case BTN_4:     return keys[3] & kb_4;
        case BTN_5:     return keys[3] & kb_5;
        case BTN_6:     return keys[3] & kb_6;
        case BTN_7:     return keys[2] & kb_7;
        case BTN_8:     return keys[2] & kb_8;
        case BTN_9:     return keys[2] & kb_9;
        case BTN_PLUS:  return keys[1] & kb_Add;
        case BTN_MINUS: return keys[1] & kb_Sub;
        case BTN_MULT:  return keys[1] & kb_Mul;
        case BTN_DIV:   return keys[1] & kb_Div;
        default:        return false;
    }
#else
    (void)button;
    (void)keys;
    return false;
#endif
}

bool input_get_button(button_t button) {
    if (!initialized) {
        return false;
    }
    return check_key(button, state.keys);
}

bool input_button_pressed(button_t button) {
    if (!initialized) {
        return false;
    }
    return check_key(button, state.keys) && !check_key(button, state.prev_keys);
}

bool input_button_released(button_t button) {
    if (!initialized) {
        return false;
    }
    return !check_key(button, state.keys) && check_key(button, state.prev_keys);
}

void input_wait_any_key(void) {
    /* Wait for all keys to be released */
    do {
        input_poll();
    } while (memcmp(state.keys, (uint8_t[]){0,0,0,0,0,0,0,0}, 8) != 0);
    
    /* Wait for any key to be pressed */
    do {
        input_poll();
    } while (memcmp(state.keys, (uint8_t[]){0,0,0,0,0,0,0,0}, 8) == 0);
}
