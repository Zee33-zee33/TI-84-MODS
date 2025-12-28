#include "input.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

static input_state_t input_state;
static input_state_t prev_state;
static struct termios orig_termios;
static int term_configured = 0;

int input_init(void) {
    memset(&input_state, 0, sizeof(input_state));
    memset(&prev_state, 0, sizeof(prev_state));
    
    // Set terminal to non-blocking, non-canonical mode
    struct termios new_termios;
    if (tcgetattr(STDIN_FILENO, &orig_termios) == 0) {
        new_termios = orig_termios;
        new_termios.c_lflag &= ~(ICANON | ECHO);
        new_termios.c_cc[VMIN] = 0;
        new_termios.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
        
        // Set stdin to non-blocking
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
        
        term_configured = 1;
    }
    
    return 0;
}

void input_shutdown(void) {
    if (term_configured) {
        tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
        
        // Restore blocking mode
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    }
}

void input_update(void) {
    prev_state = input_state;
    
    // Read all available characters
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1) {
        uint8_t key = (uint8_t)c;
        input_state.key_pressed[key] = true;
    }
}

bool input_key_down(uint8_t key) {
    return input_state.key_pressed[key];
}

bool input_key_pressed(uint8_t key) {
    return input_state.key_pressed[key] && !prev_state.key_pressed[key];
}
