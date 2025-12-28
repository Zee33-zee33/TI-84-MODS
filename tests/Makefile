# TI-84 CE Engine Tests Makefile

# Check if CE toolchain is available
CEDEV := $(shell cedev-config --prefix 2>/dev/null)

# Program name
NAME = SMOKE
OUTPUT = engine_smoke

# Source files
SOURCES = engine_smoke.c
ENGINE_LIB = ../src/engine/libengine.a
ENGINE_STUB = ../src/engine/libengine_stub.a

# Include directories
INCLUDES = -I../include

# Compiler flags
CFLAGS = -Wall -Wextra -Oz
LDFLAGS = 

# Conditionally compile for TI-84 CE if toolchain is available
ifdef CEDEV
CC = ez80-clang
CFLAGS += -DTI84CE
INCLUDES += -I$(CEDEV)/include
LIBS = $(ENGINE_LIB) -L$(CEDEV)/lib -lgraphx -lkeypadc -lfileioc
OUTPUT_FILE = $(OUTPUT).8xp

# Additional flags for CE
LDFLAGS += --nostdlib
else
CC = gcc
CFLAGS += -std=c99
LIBS = $(ENGINE_STUB)
OUTPUT_FILE = $(OUTPUT)_stub
$(info ====================================================)
$(info CE Toolchain not found - building stub executable)
$(info This will compile but won't run on calculator)
$(info Install CE toolchain to build for TI-84 Plus CE)
$(info ====================================================)
endif

.PHONY: all clean

all: $(OUTPUT_FILE)

# Build for TI-84 CE
ifdef CEDEV
$(OUTPUT).8xp: $(SOURCES) $(ENGINE_LIB)
	@echo "Building $(NAME) for TI-84 Plus CE..."
	@$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) $(LIBS) -o $(OUTPUT)
	@convbin -j bin -k 8xp -i $(OUTPUT).bin -o $(OUTPUT).8xp -n $(NAME)
	@echo "Created: $(OUTPUT).8xp"
	@echo "Load this file into CEmu to test!"
else
# Build stub
$(OUTPUT)_stub: $(SOURCES) $(ENGINE_STUB)
	@echo "Building stub executable..."
	@$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) $(LIBS) -o $(OUTPUT)_stub
	@echo "Created: $(OUTPUT)_stub"
	@echo "NOTE: This is a stub - it won't function without CE libraries"
endif

# Clean build artifacts
clean:
	@echo "Cleaning tests..."
	@rm -f *.o *.bin *.8xp $(OUTPUT) $(OUTPUT)_stub
	@echo "Tests clean complete!"

# Run in CEmu (if available)
run: $(OUTPUT).8xp
	@if command -v cemu >/dev/null 2>&1; then \
		echo "Launching CEmu..."; \
		cemu $(OUTPUT).8xp; \
	else \
		echo "CEmu not found in PATH"; \
		echo "Please manually load $(OUTPUT).8xp into CEmu"; \
	fi
