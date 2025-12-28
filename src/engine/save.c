#include "save.h"
#include <stdio.h>
#include <string.h>

#ifdef TI84_TARGET
/* TI-84 Plus CE specific implementation would go here */
#else
/* Host stub implementation for testing */
static int initialized = 0;

void save_init(void) {
    if (!initialized) {
        printf("[SAVE] Initialized\n");
        initialized = 1;
    }
}

int save_write(const char *filename, const void *data, size_t size) {
    if (!initialized || !filename || !data) return -1;
    
    FILE *fp = fopen(filename, "wb");
    if (!fp) return -1;
    
    size_t written = fwrite(data, 1, size, fp);
    fclose(fp);
    
    return (written == size) ? 0 : -1;
}

int save_read(const char *filename, void *data, size_t size) {
    if (!initialized || !filename || !data) return -1;
    
    FILE *fp = fopen(filename, "rb");
    if (!fp) return -1;
    
    size_t read = fread(data, 1, size, fp);
    fclose(fp);
    
    return (read == size) ? 0 : -1;
}

int save_exists(const char *filename) {
    if (!initialized || !filename) return 0;
    
    FILE *fp = fopen(filename, "rb");
    if (!fp) return 0;
    
    fclose(fp);
    return 1;
}

int save_delete(const char *filename) {
    if (!initialized || !filename) return -1;
    return remove(filename);
}

void save_shutdown(void) {
    if (initialized) {
        printf("[SAVE] Shutdown\n");
        initialized = 0;
    }
}
#endif
