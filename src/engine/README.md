# TI-84 CE Game Engine

A minimal, cross-game stable API for building games on the TI-84 Plus CE calculator.

## Overview

This engine provides a clean, simple API for common game development tasks on the TI-84 Plus CE. It abstracts away hardware-specific details and provides a consistent interface that multiple games can rely on.

## Features

### Core Modules

- **Input** (`input.h`) - TI calculator key mapping and polling
  - Simple button state queries
  - Press/release edge detection
  - Support for all common calculator keys

- **Render** (`render.h`) - Graphics and drawing
  - Frame buffer management
  - Tile-based rendering (8x8 or 16x16)
  - Sprite drawing
  - Tilemap support
  - Basic shapes (rectangles, pixels)

- **Font** (`font.h`) - Text rendering
  - Built-in bitmap font (5x7)
  - Custom font loading support
  - Text alignment (left, center, right)
  - Background color support

- **Save** (`save.h`) - Save/load game state
  - Multiple save slots per game
  - Simple serialization API
  - Per-game isolation

- **UI** (`ui.h`) - User interface utilities
  - Menu system with navigation
  - Dialog boxes (Yes/No, OK)
  - Button rendering

## Quick Start

### 1. Include Headers

```c
#include "input.h"
#include "render.h"
#include "font.h"
#include "ui.h"
#include "save.h"
```

### 2. Initialize Engine

```c
int main(void) {
    render_init();
    input_init();
    font_init();
    ui_init();
    save_init("MYGAME");
    
    // Your game code here
    
    render_shutdown();
    return 0;
}
```

### 3. Main Game Loop

```c
bool running = true;
while (running) {
    // Poll input
    input_poll();
    
    // Update game state
    if (input_button_pressed(BTN_CLEAR)) {
        running = false;
    }
    
    // Render
    render_clear_screen(COLOR_BLACK);
    font_draw_text(10, 10, "Hello World!", COLOR_WHITE);
    render_present();
}
```

## API Examples

### Input

```c
// Check if button is currently held
if (input_get_button(BTN_UP)) {
    player_y--;
}

// Check for button press (once per press)
if (input_button_pressed(BTN_ENTER)) {
    select_item();
}

// Wait for any key
input_wait_any_key();
```

### Rendering

```c
// Clear screen
render_clear_screen(COLOR_BLACK);

// Draw shapes
render_draw_rect(x, y, 32, 32, COLOR_RED);
render_draw_pixel(x, y, COLOR_WHITE);

// Draw sprites
sprite_t my_sprite = {16, 16, sprite_data};
render_draw_sprite(x, y, &my_sprite);

// Present frame
render_present();
```

### Text

```c
// Simple text
font_draw_text(10, 10, "Score: 100", COLOR_WHITE);

// Text with background
font_draw_text_bg(10, 30, "PAUSED", COLOR_BLACK, COLOR_YELLOW);

// Centered text
font_draw_text_aligned(LCD_WIDTH/2, 100, "Game Over", 
                      COLOR_RED, TEXT_ALIGN_CENTER);
```

### Menus

```c
// Create menu
menu_t *menu = ui_menu_create("Main Menu");
ui_menu_add_item(menu, "New Game", true);
ui_menu_add_item(menu, "Load Game", true);
ui_menu_add_item(menu, "Options", false);  // disabled
ui_menu_add_item(menu, "Exit", true);

// Update loop
int selection = -2;
while (selection == -2) {
    ui_menu_draw(menu);
    render_present();
    selection = ui_menu_update(menu);
}

free(menu);
```

### Dialogs

```c
// Yes/No dialog
dialog_result_t result = ui_dialog_yes_no("Quit Game", 
                                          "Are you sure?");
if (result == DIALOG_YES) {
    exit_game();
}

// Info dialog
ui_dialog_ok("Error", "Failed to load save!");
```

### Save/Load

```c
// Save game state
game_state_t state;
state.level = 5;
state.score = 1000;
save_write(0, &state, sizeof(state));

// Load game state
game_state_t loaded_state;
if (save_read(0, &loaded_state, sizeof(loaded_state)) > 0) {
    // Save loaded successfully
}

// Check if save exists
if (save_exists(0)) {
    // Slot 0 has a save
}
```

## Display Specifications

- **Resolution**: 320x240 pixels
- **Color Format**: RGB565 (16-bit)
- **Coordinate System**: (0,0) is top-left

## Color Constants

```c
COLOR_BLACK
COLOR_WHITE
COLOR_RED
COLOR_GREEN
COLOR_BLUE
COLOR_YELLOW
COLOR_CYAN
COLOR_MAGENTA
```

## Building

See [docs/build.md](../docs/build.md) for detailed build instructions.

Quick build:
```bash
make build
```

## Testing

Run the smoke test to verify the engine is working:

```bash
make tests
# Load tests/engine_smoke.8xp into CEmu
```

## Design Philosophy

This engine follows these principles:

1. **Minimal** - Only essential features, no bloat
2. **Stable** - API designed to be consistent across games
3. **Simple** - Easy to understand and use
4. **Cross-game** - Suitable for multiple game genres
5. **Well-documented** - Clear headers and examples

## Contributing

When adding features to the engine:

- Keep the API minimal and focused
- Maintain backward compatibility
- Update documentation
- Add tests for new functionality
- Follow the existing code style

## License

See repository root for license information.

## Support

- Check the header files in `include/` for detailed API documentation
- Review `tests/engine_smoke.c` for usage examples
- See `docs/build.md` for build and toolchain setup
