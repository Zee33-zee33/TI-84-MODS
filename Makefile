# TI-84 MODS Engine Build System
# Host-compatible build for development and testing

CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -Iinclude
LDFLAGS := 
DEBUGFLAGS := -g -O0
RELEASEFLAGS := -O2

# Directories
SRC_DIR := src/engine
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
TEST_DIR := tests

# Source files
ENGINE_SOURCES := $(wildcard $(SRC_DIR)/*.c)
ENGINE_OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(ENGINE_SOURCES))

# Test files
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.c)
TEST_BINARIES := $(patsubst $(TEST_DIR)/%.c,$(BIN_DIR)/%,$(TEST_SOURCES))

# Default target
.PHONY: all
all: build-engine

# Build engine library
.PHONY: build-engine
build-engine: $(ENGINE_OBJECTS)
	@echo "Engine built successfully"

# Build and run smoke test
.PHONY: test-engine
test-engine: $(BIN_DIR)/engine_smoke
	@echo "Running engine smoke test..."
	@$(BIN_DIR)/engine_smoke

# Create directories
$(OBJ_DIR) $(BIN_DIR):
	@mkdir -p $@

# Compile engine sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "CC $<"
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

# Link smoke test
$(BIN_DIR)/engine_smoke: $(TEST_DIR)/engine_smoke.c $(ENGINE_OBJECTS) | $(BIN_DIR)
	@echo "LD $@"
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) $< $(ENGINE_OBJECTS) -o $@ $(LDFLAGS)

# Clean build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)

# Help target
.PHONY: help
help:
	@echo "TI-84 MODS Engine Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  all           - Build engine (default)"
	@echo "  build-engine  - Build engine library"
	@echo "  test-engine   - Build and run smoke test"
	@echo "  clean         - Remove build artifacts"
	@echo "  help          - Show this help message"
	@echo ""
	@echo "Usage examples:"
	@echo "  make                    # Build engine"
	@echo "  make test-engine        # Run smoke test"
	@echo "  make clean              # Clean build"

.PHONY: install-deps
install-deps:
	@echo "Installing dependencies..."
	@echo "Note: This is a host build. No special dependencies required."
	@echo "For PNG tools, install: pip3 install Pillow"
