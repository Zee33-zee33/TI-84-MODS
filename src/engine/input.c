#include "input.h"
#include <stdio.h>

/* Macro to suppress unused parameter warnings */
#define UNUSED(x) (void)(x)

#ifdef TI84_TARGET
/* TI-84 Plus CE specific implementation would go here */
#include <keypadc.h>
#else
/* Host stub implementation for testing */
static int initialized = 0;

void input_init(void) {
    if (!initialized) {
        printf("[INPUT] Initialized\n");
        initialized = 1;
    }
}

key_t input_get_key(void) {
    if (!initialized) return KEY_NONE;
    /* Host stub - return no key for now */
    return KEY_NONE;
}

key_t input_wait_key(void) {
    if (!initialized) return KEY_NONE;
    /* Host stub - return ENTER to allow progression */
    return KEY_ENTER;
}

int input_is_key_pressed(key_t key) {
    if (!initialized) return 0;
    UNUSED(key);
    /* Host stub - no keys pressed */
    return 0;
}

void input_shutdown(void) {
    if (initialized) {
        printf("[INPUT] Shutdown\n");
        initialized = 0;
    }
}
#endif
