# Makefile for TI-84 Pixel Games Engine
# Supports both CE hardware and host platform builds

# Compiler selection
ifdef CE_TOOLCHAIN
    # TI-84 CE Toolchain (when available)
    CC = ez80-clang
    CFLAGS = -Wall -Wextra -Oz
    LDFLAGS = 
    TARGET_SUFFIX = .8xp
    PLATFORM_DEFS = -D__TI84PCE__
else
    # Host platform (GCC/Clang)
    CC = gcc
    CFLAGS = -Wall -Wextra -O2 -std=c99
    LDFLAGS = 
    TARGET_SUFFIX = 
    PLATFORM_DEFS = 
endif

# Directories
SRC_DIR = src/engine
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin

# Source files
ENGINE_SOURCES = $(SRC_DIR)/input.c \
                 $(SRC_DIR)/render.c \
                 $(SRC_DIR)/font.c \
                 $(SRC_DIR)/save.c \
                 $(SRC_DIR)/ui.c

ENGINE_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(ENGINE_SOURCES))

# Test executables
SMOKE_TEST = $(BIN_DIR)/engine_smoke$(TARGET_SUFFIX)

# Default target
.PHONY: all
all: build

# Build everything
.PHONY: build
build: dirs build-engine

# Build engine smoke test
.PHONY: build-engine
build-engine: dirs $(SMOKE_TEST)

# Create directories
.PHONY: dirs
dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p data

# Compile engine source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(PLATFORM_DEFS) -c $< -o $@

# Link smoke test
$(SMOKE_TEST): $(ENGINE_OBJECTS) $(TEST_DIR)/engine_smoke.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(PLATFORM_DEFS) $(ENGINE_OBJECTS) $(TEST_DIR)/engine_smoke.c -o $@ $(LDFLAGS)

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	rm -f data/*.sav

# Display help
.PHONY: help
help:
	@echo "TI-84 Pixel Games Engine - Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  build         - Build all targets (default)"
	@echo "  build-engine  - Build engine smoke test"
	@echo "  clean         - Remove build artifacts"
	@echo "  help          - Display this help message"
	@echo ""
	@echo "Build options:"
	@echo "  CE_TOOLCHAIN=1  - Build for TI-84 CE (requires CE toolchain)"
	@echo "  Default: Build for host platform"
	@echo ""
	@echo "Examples:"
	@echo "  make build              # Build for host"
	@echo "  make CE_TOOLCHAIN=1     # Build for TI-84 CE"
	@echo "  make clean              # Clean build artifacts"

# Phony targets
.PHONY: all build build-engine clean help
