#include "save.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef TI84CE
#include <fileioc.h>
#endif

static char game_id[9] = {0};
static bool initialized = false;

int save_init(const char *game_id_param) {
    if (!game_id_param) {
        return -1;
    }
    
    strncpy(game_id, game_id_param, 8);
    game_id[8] = '\0';
    initialized = true;
    
    return 0;
}

int save_write(uint8_t slot, const void *data, size_t size) {
    if (!initialized || slot >= MAX_SAVE_SLOTS || !data || size == 0) {
        return -1;
    }
    
#ifdef TI84CE
    /* Create filename based on game ID and slot */
    char filename[16];
    snprintf(filename, sizeof(filename), "%sSAV%d", game_id, slot);
    
    /* Open file for writing */
    ti_var_t file = ti_Open(filename, "w");
    if (!file) {
        return -1;
    }
    
    /* Write data */
    size_t written = ti_Write(data, size, 1, file);
    ti_Close(file);
    
    return (written == 1) ? 0 : -1;
#else
    /* Stub implementation for non-calculator builds */
    (void)slot;
    (void)data;
    (void)size;
    return 0;
#endif
}

int save_read(uint8_t slot, void *data, size_t size) {
    if (!initialized || slot >= MAX_SAVE_SLOTS || !data || size == 0) {
        return -1;
    }
    
#ifdef TI84CE
    /* Create filename based on game ID and slot */
    char filename[16];
    snprintf(filename, sizeof(filename), "%sSAV%d", game_id, slot);
    
    /* Open file for reading */
    ti_var_t file = ti_Open(filename, "r");
    if (!file) {
        return -1;
    }
    
    /* Read data */
    size_t read = ti_Read(data, size, 1, file);
    ti_Close(file);
    
    return (read == 1) ? (int)size : -1;
#else
    /* Stub implementation */
    (void)slot;
    (void)data;
    (void)size;
    return 0;
#endif
}

int save_exists(uint8_t slot) {
    if (!initialized || slot >= MAX_SAVE_SLOTS) {
        return 0;
    }
    
#ifdef TI84CE
    char filename[16];
    snprintf(filename, sizeof(filename), "%sSAV%d", game_id, slot);
    
    /* Check if file exists */
    ti_var_t file = ti_Open(filename, "r");
    if (file) {
        ti_Close(file);
        return 1;
    }
    return 0;
#else
    /* Stub implementation */
    (void)slot;
    return 0;
#endif
}

int save_get_info(uint8_t slot, save_info_t *info) {
    if (!initialized || slot >= MAX_SAVE_SLOTS || !info) {
        return -1;
    }
    
    if (!save_exists(slot)) {
        return -1;
    }
    
    /* Fill in basic info */
    info->slot_id = slot;
    snprintf(info->name, MAX_SAVE_NAME_LEN, "Save %d", slot);
    info->timestamp = 0; /* TODO: Add actual timestamp support */
    info->valid = 1;
    
    return 0;
}

int save_delete(uint8_t slot) {
    if (!initialized || slot >= MAX_SAVE_SLOTS) {
        return -1;
    }
    
#ifdef TI84CE
    char filename[16];
    snprintf(filename, sizeof(filename), "%sSAV%d", game_id, slot);
    
    /* Delete file */
    return ti_Delete(filename) ? 0 : -1;
#else
    /* Stub implementation */
    (void)slot;
    return 0;
#endif
}

int save_delete_all(void) {
    if (!initialized) {
        return -1;
    }
    
    for (uint8_t slot = 0; slot < MAX_SAVE_SLOTS; slot++) {
        save_delete(slot);
    }
    
    return 0;
}
