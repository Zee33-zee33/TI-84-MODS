# Makefile for TI-84 MODS Engine

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99
LDFLAGS = -lrt

ENGINE_SOURCES = src/engine/engine.c \
                 src/engine/input.c \
                 src/engine/render.c \
                 src/engine/font.c \
                 src/engine/save.c \
                 src/engine/ui.c

ENGINE_OBJECTS = $(ENGINE_SOURCES:.c=.o)

TEST_ENGINE_SOURCES = test_engine.c
TEST_ENGINE_OBJECTS = $(TEST_ENGINE_SOURCES:.c=.o)

.PHONY: all build-engine clean

all: build-engine

build-engine: test_engine
	@echo "Engine smoke test built successfully!"
	@./test_engine

test_engine: $(ENGINE_OBJECTS) $(TEST_ENGINE_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(ENGINE_OBJECTS) $(TEST_ENGINE_OBJECTS) test_engine
	rm -f save_slot_*.bin

.PHONY: help
help:
	@echo "Available targets:"
	@echo "  build-engine  - Build and run the engine smoke test"
	@echo "  clean         - Remove built files and test artifacts"
	@echo "  help          - Show this help message"
