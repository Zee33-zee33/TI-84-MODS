# Building TI-84 CE Game Engine

This document provides instructions for building the TI-84 CE Game Engine and related games.

## Prerequisites

### 1. CE C/C++ Toolchain

The CE C/C++ Toolchain is required to compile programs for the TI-84 Plus CE calculator.

**Download and Install:**
- Official repository: [CE-Programming/toolchain](https://github.com/CE-Programming/toolchain)
- Download the latest release for your platform:
  - Windows: `CEdev-Windows.zip`
  - macOS: `CEdev-macOS.zip`
  - Linux: `CEdev-Linux.tar.gz`

**Installation:**
1. Extract the toolchain to a directory (e.g., `~/CEdev` or `C:\CEdev`)
2. Add the toolchain's `bin` directory to your PATH:
   - Linux/macOS: `export PATH=$PATH:~/CEdev/bin`
   - Windows: Add `C:\CEdev\bin` to your system PATH

**Verify Installation:**
```bash
cedev-config --version
```

### 2. CEmu Emulator

CEmu is a TI-84 Plus CE emulator used for testing programs.

**Download and Install:**
- Official repository: [CE-Programming/CEmu](https://github.com/CE-Programming/CEmu)
- Download the latest release: [CEmu Releases](https://github.com/CE-Programming/CEmu/releases)
- Available for Windows, macOS, and Linux

**Setup:**
1. Install CEmu following the instructions for your platform
2. On first run, you'll need to provide a ROM image (follow CEmu's instructions)

## Building the Engine

### Build All Projects

From the repository root:

```bash
make build
```

This will compile all engine modules and games.

### Build Individual Components

**Engine Library Only:**
```bash
cd src/engine
make
```

**Smoke Test:**
```bash
cd tests
make engine_smoke
```

## Running the Smoke Test in CEmu

The smoke test demonstrates that all engine modules are functioning correctly.

### Steps:

1. Build the smoke test:
   ```bash
   make build
   ```

2. Locate the output file:
   - The compiled program will be at: `tests/engine_smoke.8xp`

3. Load into CEmu:
   - Open CEmu
   - Drag and drop `engine_smoke.8xp` onto the CEmu window
   - Or use: Variable → Load from file → Select `engine_smoke.8xp`

4. Run the program:
   - In CEmu, press `[prgm]` key
   - Select `SMOKE` (or `ENGINE_SMOKE`)
   - Press `[enter]` twice to run

### Expected Output:

When the smoke test runs successfully, you should see:

- **Title**: "TI-84 Game Engine" with blue background at top
- **Version**: "Smoke Test v1.0" in cyan
- **Test Results**: Five green "[ PASS ]" messages for each module:
  - Render Module
  - Input Module
  - Font Module
  - UI Module
  - Save Module
- **Status**: "ENGINE OK" with green background
- **Color Bars**: Six colored rectangles (red, green, blue, yellow, cyan, magenta)
- **Instructions**: Text prompting you to:
  - Press ENTER to test the menu system
  - Press CLEAR to exit

### Interactive Test:

- **Press ENTER**: Opens a test menu with navigation
  - Use arrow keys to navigate
  - Press ENTER to select
  - Press CLEAR to exit menu
- **Press CLEAR**: Exits the program

## Build Output Files

After building, you'll find:

- `*.8xp` files - Compiled programs for TI-84 Plus CE
- `*.bin` files - Binary executables
- `*.map` files - Symbol maps for debugging

## Troubleshooting

### "Command not found: make"

Install build tools:
- **Linux**: `sudo apt-get install build-essential`
- **macOS**: `xcode-select --install`
- **Windows**: Install [MSYS2](https://www.msys2.org/) or use WSL

### "cedev-config not found"

Ensure the CE toolchain is installed and added to your PATH. See Prerequisites section above.

### Build Errors

1. Verify toolchain installation: `cedev-config --version`
2. Check that all source files are present
3. Clean build artifacts: `make clean`
4. Try rebuilding: `make build`

### CEmu Issues

- Make sure you have a valid ROM image
- Update to the latest CEmu version
- Check CEmu documentation: [CEmu Wiki](https://github.com/CE-Programming/CEmu/wiki)

## Additional Resources

- **CE C/C++ Documentation**: [CE Programming](https://ce-programming.github.io/toolchain/)
- **CE Libraries**: [LibLoad](https://github.com/mateoconlechuga/libload)
- **TI-84 CE SDK Examples**: [CE Toolchain Examples](https://github.com/CE-Programming/toolchain/tree/master/examples)
- **Community Support**: [Cemetech Forums](https://www.cemetech.net/)

## Next Steps

After verifying the engine works with the smoke test, you can:

1. Create new games using the engine APIs
2. Refer to the header files in `include/` for API documentation
3. Study the smoke test source in `tests/engine_smoke.c` for usage examples
4. Build upon the existing engine modules
