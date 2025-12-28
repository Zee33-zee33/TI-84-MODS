#ifndef SAVE_H
#define SAVE_H

#include <stddef.h>
#include <stdbool.h>

#define SAVE_SLOTS 8

void save_init(void);
bool save_write(int slot, const void *data, size_t size);
bool save_read(int slot, void *out, size_t size);
bool save_exists(int slot);

#endif
