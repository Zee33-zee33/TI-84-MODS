# TI-84 CE Game Engine Library Makefile

# Check if CE toolchain is available
CEDEV := $(shell cedev-config --prefix 2>/dev/null)

# Source files
SOURCES = input.c render.c font.c save.c ui.c
OBJECTS = $(SOURCES:.c=.o)

# Include directories
INCLUDES = -I../../include

# Compiler flags
CFLAGS = -Wall -Wextra -Oz
LDFLAGS = 

# Conditionally compile for TI-84 CE if toolchain is available
ifdef CEDEV
CC = ez80-clang
AR = ez80-ar
CFLAGS += -DTI84CE
INCLUDES += -I$(CEDEV)/include
OUTPUT = libengine.a
else
CC = gcc
AR = ar
CFLAGS += -std=c99
OUTPUT = libengine_stub.a
$(info ====================================================)
$(info CE Toolchain not found - building stub library)
$(info Install CE toolchain to build for TI-84 Plus CE)
$(info ====================================================)
endif

.PHONY: all clean

all: $(OUTPUT)

# Build the library
$(OUTPUT): $(OBJECTS)
	@echo "Creating library: $@"
	@$(AR) rcs $@ $^

# Compile source files
%.o: %.c
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning engine..."
	@rm -f $(OBJECTS) $(OUTPUT) libengine.a libengine_stub.a
	@echo "Engine clean complete!"

# Install headers (optional)
install-headers:
	@mkdir -p ../../bin/include
	@cp ../../include/*.h ../../bin/include/
	@echo "Headers installed to bin/include/"
