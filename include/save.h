#ifndef SAVE_H
#define SAVE_H

#include <stdint.h>
#include <stddef.h>

// Initialize save system
int save_init(void);
void save_shutdown(void);

// Save data to file
int save_write(const char* filename, const void* data, size_t size);

// Load data from file
int save_read(const char* filename, void* data, size_t max_size);

// Check if save file exists
int save_exists(const char* filename);

// Delete save file
int save_delete(const char* filename);

#endif // SAVE_H
