# TI-84 CE Game Engine Makefile
# Top-level makefile for building engine and all games

.PHONY: all build clean engine tests help

# Default target
all: build

# Build everything
build: engine tests
	@echo "==================================="
	@echo "Build complete!"
	@echo "==================================="
	@echo ""
	@echo "Next steps:"
	@echo "  1. Load tests/engine_smoke.8xp into CEmu"
	@echo "  2. Run the SMOKE program"
	@echo "  3. Verify 'ENGINE OK' appears on screen"
	@echo ""

# Build engine library
engine:
	@echo "Building engine library..."
	@mkdir -p bin
	@$(MAKE) -C src/engine

# Build tests
tests: engine
	@echo "Building tests..."
	@$(MAKE) -C tests

# Clean all build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@$(MAKE) -C src/engine clean
	@$(MAKE) -C tests clean
	@rm -rf bin
	@echo "Clean complete!"

# Help target
help:
	@echo "TI-84 CE Game Engine - Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  make build   - Build engine and tests (default)"
	@echo "  make engine  - Build engine library only"
	@echo "  make tests   - Build tests only"
	@echo "  make clean   - Remove all build artifacts"
	@echo "  make help    - Show this help message"
	@echo ""
	@echo "Requirements:"
	@echo "  - CE C/C++ Toolchain"
	@echo "  - CEmu emulator (for testing)"
	@echo ""
	@echo "See docs/build.md for detailed instructions"
