#!/usr/bin/env python3
"""
PNG to C array converter
Converts PNG images to C header files with byte arrays
"""

import sys
import os

try:
    from PIL import Image
except ImportError:
    print("Error: Pillow library not found. Install with: pip install Pillow")
    sys.exit(1)

def png_to_c(png_path, output_path=None, var_name=None):
    """Convert PNG to C header file"""
    
    # Load PNG
    try:
        img = Image.open(png_path)
    except Exception as e:
        print(f"Error loading {png_path}: {e}")
        return False
    
    # Convert to RGB if necessary
    if img.mode != 'RGB':
        img = img.convert('RGB')
    
    # Get image data
    width, height = img.size
    pixels = list(img.getdata())
    
    # Generate variable name
    if var_name is None:
        var_name = os.path.splitext(os.path.basename(png_path))[0]
        var_name = var_name.replace('-', '_').replace('.', '_')
    
    # Generate output path
    if output_path is None:
        output_path = os.path.splitext(png_path)[0] + '.h'
    
    # Write C header
    with open(output_path, 'w') as f:
        f.write(f"// Generated from {os.path.basename(png_path)}\n")
        f.write(f"// Image size: {width}x{height}\n\n")
        f.write(f"#ifndef {var_name.upper()}_H\n")
        f.write(f"#define {var_name.upper()}_H\n\n")
        f.write(f"#include <stdint.h>\n\n")
        
        # Write dimensions
        f.write(f"#define {var_name.upper()}_WIDTH {width}\n")
        f.write(f"#define {var_name.upper()}_HEIGHT {height}\n\n")
        
        # Write pixel data as RGB888
        f.write(f"static const uint8_t {var_name}_data[] = {{\n")
        
        for i, (r, g, b) in enumerate(pixels):
            if i % 8 == 0:
                f.write("    ")
            f.write(f"0x{r:02x}, 0x{g:02x}, 0x{b:02x}, ")
            if (i + 1) % 8 == 0:
                f.write("\n")
        
        if len(pixels) % 8 != 0:
            f.write("\n")
        
        f.write("};\n\n")
        f.write(f"#endif // {var_name.upper()}_H\n")
    
    print(f"Generated {output_path}")
    return True

def main():
    if len(sys.argv) < 2:
        print("Usage: png_to_c.py <input.png> [output.h] [var_name]")
        print("\nConverts PNG images to C header files")
        print("\nExample:")
        print("  png_to_c.py sprite.png sprite.h sprite")
        sys.exit(1)
    
    png_path = sys.argv[1]
    output_path = sys.argv[2] if len(sys.argv) > 2 else None
    var_name = sys.argv[3] if len(sys.argv) > 3 else None
    
    if not os.path.exists(png_path):
        print(f"Error: File not found: {png_path}")
        sys.exit(1)
    
    if png_to_c(png_path, output_path, var_name):
        sys.exit(0)
    else:
        sys.exit(1)

if __name__ == '__main__':
    main()
