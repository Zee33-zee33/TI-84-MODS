/**
 * save.c - Save/load system implementation
 * 
 * On host: Uses local files in data/ directory
 * On CE: Will use AppVar storage (to be implemented)
 */

#include "save.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* Platform detection */
#ifdef __TI84PCE__
    #define PLATFORM_CE 1
    /* CE-specific file I/O includes would go here */
    /* #include <fileioc.h> */
#else
    #define PLATFORM_HOST 1
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

#define SAVE_FILE_PREFIX "data/save_slot_"

int save_init(void) {
#ifdef PLATFORM_CE
    /* Initialize CE file I/O library */
    /* ti_CloseAll(); */
    return 0;
    
#else
    /* Create data directory if it doesn't exist */
    #ifdef _WIN32
        int result = _mkdir("data");
        if (result != 0 && errno != EEXIST) {
            return -1;
        }
    #else
        int result = mkdir("data", 0755);
        if (result != 0 && errno != EEXIST) {
            return -1;
        }
    #endif
    
    return 0;
#endif
}

int save_write(int slot, const void *data, size_t size) {
    if (slot < 0 || slot >= MAX_SAVE_SLOTS) {
        return -1;
    }
    
    if (!data || size == 0 || size > MAX_SAVE_SIZE) {
        return -1;
    }
    
#ifdef PLATFORM_CE
    /* Write to CE AppVar */
    /* char var_name[9]; */
    /* snprintf(var_name, sizeof(var_name), "SAVE%d", slot); */
    
    /* ti_var_t var = ti_Open(var_name, "w"); */
    /* if (!var) return -1; */
    
    /* ti_Write(data, size, 1, var); */
    /* ti_Close(var); */
    
    /* Stub: return success */
    return 0;
    
#else
    /* Write to local file on host */
    char filename[256];
    snprintf(filename, sizeof(filename), "%s%d.sav", SAVE_FILE_PREFIX, slot);
    
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        return -1;
    }
    
    size_t written = fwrite(data, 1, size, fp);
    fclose(fp);
    
    return (written == size) ? 0 : -1;
#endif
}

int save_read(int slot, void *buf, size_t size) {
    if (slot < 0 || slot >= MAX_SAVE_SLOTS) {
        return -1;
    }
    
    if (!buf || size == 0) {
        return -1;
    }
    
#ifdef PLATFORM_CE
    /* Read from CE AppVar */
    /* char var_name[9]; */
    /* snprintf(var_name, sizeof(var_name), "SAVE%d", slot); */
    
    /* ti_var_t var = ti_Open(var_name, "r"); */
    /* if (!var) return -1; */
    
    /* size_t read_size = ti_Read(buf, 1, size, var); */
    /* ti_Close(var); */
    
    /* return (int)read_size; */
    
    /* Stub: return no data */
    return 0;
    
#else
    /* Read from local file on host */
    char filename[256];
    snprintf(filename, sizeof(filename), "%s%d.sav", SAVE_FILE_PREFIX, slot);
    
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return -1;
    }
    
    size_t read_size = fread(buf, 1, size, fp);
    fclose(fp);
    
    return (int)read_size;
#endif
}

int save_exists(int slot) {
    if (slot < 0 || slot >= MAX_SAVE_SLOTS) {
        return -1;
    }
    
#ifdef PLATFORM_CE
    /* Check if CE AppVar exists */
    /* char var_name[9]; */
    /* snprintf(var_name, sizeof(var_name), "SAVE%d", slot); */
    
    /* ti_var_t var = ti_Open(var_name, "r"); */
    /* if (var) { */
    /*     ti_Close(var); */
    /*     return 1; */
    /* } */
    /* return 0; */
    
    /* Stub: return not exists */
    return 0;
    
#else
    /* Check if local file exists on host */
    char filename[256];
    snprintf(filename, sizeof(filename), "%s%d.sav", SAVE_FILE_PREFIX, slot);
    
    FILE *fp = fopen(filename, "rb");
    if (fp) {
        fclose(fp);
        return 1;
    }
    return 0;
#endif
}

int save_delete(int slot) {
    if (slot < 0 || slot >= MAX_SAVE_SLOTS) {
        return -1;
    }
    
#ifdef PLATFORM_CE
    /* Delete CE AppVar */
    /* char var_name[9]; */
    /* snprintf(var_name, sizeof(var_name), "SAVE%d", slot); */
    
    /* ti_Delete(var_name); */
    
    /* Stub: return success */
    return 0;
    
#else
    /* Delete local file on host */
    char filename[256];
    snprintf(filename, sizeof(filename), "%s%d.sav", SAVE_FILE_PREFIX, slot);
    
    return remove(filename);
#endif
}

void save_cleanup(void) {
#ifdef PLATFORM_CE
    /* Cleanup CE file I/O */
    /* ti_CloseAll(); */
#endif
    /* Host: no cleanup needed */
}
