#include "assets.h"
#include <stdio.h>
#include <stdlib.h>

int assets_init(void) {
    return 0;
}

void assets_shutdown(void) {
}

int assets_load(const char* filename, void** data, size_t* size) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        return -1;
    }
    
    // Get file size
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    // Allocate buffer
    *data = malloc(fsize);
    if (!*data) {
        fclose(f);
        return -1;
    }
    
    // Read file
    size_t read_size = fread(*data, 1, fsize, f);
    fclose(f);
    
    if (read_size != (size_t)fsize) {
        free(*data);
        *data = NULL;
        return -1;
    }
    
    *size = fsize;
    return 0;
}

void assets_free(void* data) {
    if (data) {
        free(data);
    }
}
