# TI-84-MODS

A collection of pixel games and a shared game engine for the TI-84 Plus CE calculator.

## Project Overview

This repository contains:
- **Shared Game Engine** - A portable C game engine with input, rendering, font, save, and UI systems
- **Individual Games** - Pixel-art games built on top of the engine (to be added)

## Engine Features

The TI-84 Pixel Games Engine provides:

- **Input System** (`src/engine/input.*`) - Button/key abstraction with platform-specific mapping
- **Render System** (`src/engine/render.*`) - Framebuffer management, sprite/tile drawing, palette control
- **Font System** (`src/engine/font.*`) - Bitmap font rendering with embedded 8x8 font
- **Save System** (`src/engine/save.*`) - Persistent storage for game state (multiple save slots)
- **UI System** (`src/engine/ui.*`) - Simple menus and dialogs

## Quick Start

### Building on Host Platform

```bash
make build
./bin/engine_smoke
```

### Building for TI-84 CE

Requires the [CE C/C++ Toolchain](https://github.com/CE-Programming/toolchain):

```bash
make CE_TOOLCHAIN=1 build
```

### Testing with CEmu

1. Install [CEmu emulator](https://ce-programming.github.io/CEmu/)
2. Build for CE: `make CE_TOOLCHAIN=1 build`
3. Load `bin/engine_smoke.8xp` into CEmu
4. Run the program - you should see "ENGINE OK" displayed

For detailed build instructions, see [docs/build.md](docs/build.md).

## Project Structure

```
TI-84-MODS/
├── src/engine/          # Shared game engine
├── tests/               # Engine tests
├── include/             # Public API headers
├── docs/                # Documentation
├── wilderness-survival/ # Individual game projects
└── Makefile             # Build system
```

## Development

The engine is designed to be portable:
- Compiles on host platforms (Linux/macOS/Windows) for development
- Uses `#ifdef` guards for TI-84 CE specific code
- Provides stubs that compile cleanly on all platforms

See [docs/build.md](docs/build.md) for complete development workflow.

## Engine API

Games can use the engine by including headers from `include/`:

```c
#include "input.h"
#include "render.h"
#include "font.h"
#include "save.h"
#include "ui.h"
```

All engine functions are documented in their respective header files.

## Contributing

Individual game contributions are welcome! Each game should:
1. Use the stable engine API defined in `include/`
2. Have its own directory with a dedicated Makefile
3. Include build instructions and documentation

## License

See individual game directories for licensing information.