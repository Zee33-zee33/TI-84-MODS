# Top-level Makefile for TI-84 MODS project

.PHONY: all build-2048 test-2048 clean help

# Default target
all: build-2048

# Build the 2048 game
build-2048:
	@echo "Building 2048 game..."
	@cd src/games/2048 && $(MAKE)
	@echo "2048 game built successfully!"

# Build and run tests for 2048
test-2048:
	@echo "Building and running 2048 tests..."
	@cd tests && $(CC) -Wall -Wextra -std=c99 -I../src/engine -o 2048_test 2048_test.c \
		../src/games/2048/2048.c ../src/engine/save.c -lm
	@./tests/2048_test
	@echo "Tests completed!"

# Clean all build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@cd src/games/2048 && $(MAKE) clean
	@rm -f tests/2048_test
	@echo "Clean complete!"

# Help target
help:
	@echo "TI-84 MODS Build System"
	@echo "======================="
	@echo ""
	@echo "Available targets:"
	@echo "  all         - Build all projects (default)"
	@echo "  build-2048  - Build the 2048 game"
	@echo "  test-2048   - Run 2048 unit tests"
	@echo "  clean       - Clean all build artifacts"
	@echo "  help        - Show this help message"
