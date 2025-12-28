# Building the TI-84 Engine

This document describes how to build and test the TI-84 engine on a host system (Linux/macOS).

## Prerequisites

- GCC compiler (or compatible C compiler)
- Make
- Python 3 (for asset conversion tools)
- Pillow library (optional, for PNG conversion): `pip3 install Pillow`

## Building the Engine

The engine can be built using the provided Makefile:

```bash
# Build the engine
make build-engine

# Or simply:
make
```

This will compile all engine source files in `src/engine/` and create object files in `build/obj/`.

## Running Tests

### Smoke Test

A basic smoke test is provided to verify that all engine systems initialize correctly:

```bash
# Build and run the smoke test
make test-engine
```

The smoke test will:
1. Initialize all engine subsystems (engine, input, render, font, save, UI, palette, assets)
2. Test basic functionality of each system
3. Print "ENGINE OK" if all tests pass

Expected output:
```
=== TI-84 Engine Smoke Test ===

Testing engine_init... OK
Testing input_init... OK
Testing render_init... OK
Testing font_init... OK
Testing save_init... OK
Testing ui_init... OK
Testing palette_init... OK
Testing assets_init... OK

Testing basic functionality...
  Time tracking: 0 ms -> 0 ms... OK
  Input update... OK
  Render clear... OK
  Font text width... OK (width=32)

Cleaning up...

=== ENGINE OK ===
```

## Building Individual Tests

You can also build and run the smoke test manually:

```bash
# Build the test
gcc -Wall -Wextra -std=c99 -Iinclude -g -O0 \
    tests/engine_smoke.c \
    build/obj/*.o \
    -o build/bin/engine_smoke

# Run the test
./build/bin/engine_smoke
```

## Cleaning Build Artifacts

Remove all build artifacts:

```bash
make clean
```

## Project Structure

```
TI-84-MODS/
├── include/          # Public header files
│   ├── engine.h
│   ├── input.h
│   ├── render.h
│   ├── font.h
│   ├── save.h
│   ├── ui.h
│   ├── palette.h
│   └── assets.h
├── src/engine/       # Engine implementation
│   ├── engine.c
│   ├── input.c
│   ├── render.c
│   ├── font.c
│   ├── save.c
│   ├── ui.c
│   ├── palette.c
│   ├── font_atlas.c
│   └── assets.c
├── tests/            # Test programs
│   └── engine_smoke.c
├── tools/            # Build tools
│   └── png_to_c.py
├── assets/           # Game assets
│   └── palettes/
└── Makefile          # Build configuration
```

## Notes

- The engine is designed to be host-compatible for development and testing
- Terminal-based implementations are used for CE-specific features (input, rendering)
- The renderer uses ANSI color codes for terminal output
- Input is captured from stdin in non-blocking mode
