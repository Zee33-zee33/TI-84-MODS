# Makefile for 2048 game
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../engine
LDFLAGS = 

# Directories
SRC_DIR = .
ENGINE_DIR = ../../engine
BUILD_DIR = build

# Source files
GAME_SRCS = 2048.c 2048_ui.c main.c
ENGINE_SRCS = $(ENGINE_DIR)/render.c $(ENGINE_DIR)/input.c $(ENGINE_DIR)/font.c $(ENGINE_DIR)/save.c
ALL_SRCS = $(GAME_SRCS) $(ENGINE_SRCS)

# Object files
GAME_OBJS = $(GAME_SRCS:.c=.o)
ENGINE_OBJS = $(notdir $(ENGINE_SRCS:.c=.o))
ALL_OBJS = $(GAME_OBJS) $(ENGINE_OBJS)

# Target binary
TARGET = 2048

# Default target
all: $(TARGET)

# Build the game
$(TARGET): $(ALL_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile game source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile engine source files
render.o: $(ENGINE_DIR)/render.c
	$(CC) $(CFLAGS) -c $< -o $@

input.o: $(ENGINE_DIR)/input.c
	$(CC) $(CFLAGS) -c $< -o $@

font.o: $(ENGINE_DIR)/font.c
	$(CC) $(CFLAGS) -c $< -o $@

save.o: $(ENGINE_DIR)/save.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(ALL_OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
