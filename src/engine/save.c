#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAVE_DIR ".ti84_saves"

int save_init(void) {
    // Create save directory if it doesn't exist
    // For simplicity, we'll just use the current directory
    return 0;
}

void save_shutdown(void) {
}

int save_write(const char* filename, const void* data, size_t size) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", SAVE_DIR, filename);
    
    FILE* f = fopen(path, "wb");
    if (!f) {
        // Try without directory
        f = fopen(filename, "wb");
        if (!f) {
            return -1;
        }
    }
    
    size_t written = fwrite(data, 1, size, f);
    fclose(f);
    
    return (written == size) ? 0 : -1;
}

int save_read(const char* filename, void* data, size_t max_size) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", SAVE_DIR, filename);
    
    FILE* f = fopen(path, "rb");
    if (!f) {
        // Try without directory
        f = fopen(filename, "rb");
        if (!f) {
            return -1;
        }
    }
    
    size_t read_size = fread(data, 1, max_size, f);
    fclose(f);
    
    return (int)read_size;
}

int save_exists(const char* filename) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", SAVE_DIR, filename);
    
    FILE* f = fopen(path, "rb");
    if (!f) {
        f = fopen(filename, "rb");
        if (!f) {
            return 0;
        }
    }
    
    fclose(f);
    return 1;
}

int save_delete(const char* filename) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", SAVE_DIR, filename);
    
    if (remove(path) != 0) {
        return remove(filename);
    }
    
    return 0;
}
