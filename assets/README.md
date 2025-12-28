# Assets Directory

This directory contains game assets including:

- **palettes/** - Color palette files (.pal format)
- **sprites/** - Sprite images (PNG format)
- **fonts/** - Font data
- **audio/** - Sound effects and music

## Palette Files

Palette files (.pal) are binary files containing 256 RGB color triplets (768 bytes total).
Each color is stored as 3 bytes: Red, Green, Blue (0-255).

Load palettes using the `palette_load()` function from `palette.h`.

## Converting PNG to C Arrays

Use the `tools/png_to_c.py` script to convert PNG images to C header files:

```bash
python3 tools/png_to_c.py assets/sprites/player.png include/player.h player_sprite
```

This will generate a C header with the image data as a byte array.
