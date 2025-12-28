#ifndef ASSETS_H
#define ASSETS_H

#include <stdint.h>
#include <stddef.h>

// Asset loading and management
int assets_init(void);
void assets_shutdown(void);

// Load asset from file
int assets_load(const char* filename, void** data, size_t* size);

// Free loaded asset
void assets_free(void* data);

#endif // ASSETS_H
