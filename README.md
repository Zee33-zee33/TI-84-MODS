# TI-84-MODS

A collection of games and modifications for the TI-84 Plus CE calculator.

## Projects

### 2048 Game
Classic 2048 sliding puzzle game implementation for TI-84 Plus CE.

#### Features
- 4x4 game board with tile merging mechanics
- Score tracking with persistent high scores
- Single-step undo functionality
- Win detection (2048 tile) and lose detection (no moves available)
- Pause menu and game state saving
- Colorful tile rendering with distinct colors per value

#### Controls
- **Arrow Keys**: Move tiles (Up, Down, Left, Right)
- **Enter**: Undo last move
- **2nd**: Pause game
- **Clear**: Quit to menu / Exit game

## Building

### Prerequisites
- GCC compiler (for host builds)
- Make

### Build Commands

Build the 2048 game:
```bash
make build-2048
```

Run unit tests:
```bash
make test-2048
```

Clean build artifacts:
```bash
make clean
```

Get help:
```bash
make help
```

### Build Output
- Game binary: `src/games/2048/2048`
- Test binary: `tests/2048_test`

## Project Structure

```
.
├── src/
│   ├── engine/          # Shared engine API
│   │   ├── render.*     # Graphics rendering
│   │   ├── input.*      # Input handling
│   │   ├── font.*       # Text rendering
│   │   └── save.*       # File I/O
│   └── games/
│       └── 2048/        # 2048 game implementation
│           ├── 2048.*       # Game logic
│           ├── 2048_ui.*    # UI rendering and input
│           ├── main.c       # Entry point
│           └── Makefile     # Game-specific build
├── tests/               # Unit tests
├── docs/design/         # Design documentation
├── assets/original/     # Game assets
└── Makefile            # Top-level build system
```

## Testing

The project includes comprehensive unit tests for game logic:
- Move and merge behavior in all directions
- Undo functionality
- Win/lose detection
- Randomized move sequences

All tests pass with 100% success rate.

## Documentation

See `docs/design/2048.md` for detailed design documentation including:
- Game rules and mechanics
- Control mappings
- UI layout and colors
- Technical architecture
- Acceptance criteria

## Platform Compatibility

The code is written in portable C99 with platform-specific abstractions:
- **Host mode**: For development and testing on PC (default)
- **TI-84 mode**: For deployment to calculator (define `TI84_TARGET`)

The engine API provides host stubs for testing without calculator hardware.

## License

See individual project directories for licensing information.
