# Build Instructions for TI-84 Pixel Games Engine

This document describes how to build and test the TI-84 Pixel Games Engine.

## Prerequisites

### For Host Platform Development (Linux/macOS/Windows)

- GCC or Clang compiler
- Make (GNU Make)
- Standard C development tools

### For TI-84 CE Hardware

- [CE C/C++ Toolchain](https://github.com/CE-Programming/toolchain)
  - Follow installation instructions at the link above
  - Includes ez80-clang compiler and necessary libraries
- [CEmu Emulator](https://ce-programming.github.io/CEmu/) (for testing)
  - Download from the official website
  - Available for Windows, macOS, and Linux

## Building the Engine

### Host Platform Build (Development/Testing)

Build the engine smoke test for your local machine:

```bash
make build
```

This will:
- Compile all engine source files (`src/engine/*.c`)
- Build the smoke test executable (`tests/engine_smoke.c`)
- Output binary to `bin/engine_smoke`

Run the smoke test:

```bash
./bin/engine_smoke
```

Expected output:
```
Engine Smoke Test Starting...
Initializing input system...
Initializing render system...
Initializing font system...
Initializing save system...
All systems initialized successfully!
Clearing screen...
Drawing 'ENGINE OK' text...
Presenting frame...

=================================
SMOKE TEST PASSED!
'ENGINE OK' should be visible on screen
=================================

Cleaning up...
Engine Smoke Test Complete.
```

### TI-84 CE Build

Build for TI-84 CE hardware (requires CE toolchain installed):

```bash
make CE_TOOLCHAIN=1 build
```

This will produce:
- `bin/engine_smoke.8xp` - TI-84 CE executable

## Testing with CEmu

CEmu is the recommended emulator for testing TI-84 CE programs.

### Running the Smoke Test in CEmu

1. **Launch CEmu**
   ```bash
   cemu
   ```

2. **Load the program**
   - In CEmu, go to `Variables` → `Send to calculator...`
   - Select `bin/engine_smoke.8xp`
   - Or drag and drop the .8xp file onto CEmu window

3. **Run the program**
   - On the emulated calculator, press `[2nd]` + `[0]` to access catalog
   - Navigate to `Asm(`
   - Press `[ENTER]`
   - Type or select `engine_smoke`
   - Press `[ENTER]` to run

4. **Expected Result**
   - The screen should clear
   - Text "ENGINE OK" should appear centered on screen (white text)
   - Program exits cleanly

### Alternative: Command-line CEmu (if supported)

Some CEmu versions support command-line operation:

```bash
cemu --send bin/engine_smoke.8xp --run engine_smoke
```

Note: Command-line functionality may vary by CEmu version.

## Cleaning Build Artifacts

Remove all compiled files:

```bash
make clean
```

## Project Structure

```
TI-84-MODS/
├── src/
│   └── engine/          # Engine source code
│       ├── input.c/h    # Input system
│       ├── render.c/h   # Rendering system
│       ├── font.c/h     # Font rendering
│       ├── save.c/h     # Save/load system
│       └── ui.c/h       # UI components
├── tests/
│   └── engine_smoke.c   # Engine smoke test
├── build/               # Compiled object files (created by make)
├── bin/                 # Output binaries (created by make)
├── data/                # Save game data directory
├── docs/
│   └── build.md         # This file
├── Makefile             # Build system
└── README.md            # Project README
```

## Development Workflow

1. **Make changes** to engine source files in `src/engine/`
2. **Build** for host platform: `make build`
3. **Test** on host: `./bin/engine_smoke`
4. **Build** for CE: `make CE_TOOLCHAIN=1 build` (if toolchain installed)
5. **Test** in CEmu emulator
6. **Iterate** on changes

## Platform Differences

The engine uses `#ifdef` guards to handle platform differences:

- `__TI84PCE__` - Defined when compiling for TI-84 CE
- `PLATFORM_CE` - Set by code when on CE platform
- `PLATFORM_HOST` - Set by code when on host platform

Engine modules provide stubs for CE-specific functionality that compile on host platforms but do no-ops or use host equivalents (e.g., file I/O for save system).

## Troubleshooting

### "Command not found: gcc" or "Command not found: make"

Install development tools:
- **Linux**: `sudo apt-get install build-essential`
- **macOS**: Install Xcode Command Line Tools: `xcode-select --install`
- **Windows**: Install MinGW or use WSL

### "CE toolchain not found"

Ensure the CE toolchain is installed and in your PATH. See installation instructions at:
https://github.com/CE-Programming/toolchain

### CEmu won't load program

- Ensure you built with `CE_TOOLCHAIN=1`
- Check that the .8xp file was created in `bin/`
- Try using the CEmu Variables panel to send the file

## Next Steps

After verifying the engine skeleton builds and runs:

1. Individual game modules can be added to the project
2. Games will link against the engine API defined in `src/engine/*.h`
3. Per-game Makefiles can be added for specific games
4. The top-level Makefile will call per-game build targets

## Additional Resources

- [CE C/C++ Toolchain Documentation](https://ce-programming.github.io/toolchain/index.html)
- [CEmu Documentation](https://github.com/CE-Programming/CEmu/wiki)
- [TI-84 CE Programming Guide](https://wikiti.brandonw.net/)
