#ifndef SAVE_H
#define SAVE_H

#include <stdint.h>
#include <stddef.h>

#define MAX_SAVE_SLOTS 3
#define MAX_SAVE_NAME_LEN 16

/* Save slot structure */
typedef struct {
    uint8_t slot_id;
    char name[MAX_SAVE_NAME_LEN];
    uint32_t timestamp;
    uint8_t valid;
} save_info_t;

/**
 * Initialize the save system
 * @param game_id Unique identifier for the game (max 8 chars)
 * @return 0 on success, -1 on failure
 */
int save_init(const char *game_id);

/**
 * Save game data to a slot
 * @param slot Slot number (0 to MAX_SAVE_SLOTS-1)
 * @param data Pointer to data to save
 * @param size Size of data in bytes
 * @return 0 on success, -1 on failure
 */
int save_write(uint8_t slot, const void *data, size_t size);

/**
 * Load game data from a slot
 * @param slot Slot number (0 to MAX_SAVE_SLOTS-1)
 * @param data Pointer to buffer to load data into
 * @param size Size of buffer in bytes
 * @return Number of bytes read on success, -1 on failure
 */
int save_read(uint8_t slot, void *data, size_t size);

/**
 * Check if a save slot exists and is valid
 * @param slot Slot number (0 to MAX_SAVE_SLOTS-1)
 * @return 1 if valid, 0 if empty/invalid
 */
int save_exists(uint8_t slot);

/**
 * Get information about a save slot
 * @param slot Slot number (0 to MAX_SAVE_SLOTS-1)
 * @param info Pointer to save_info_t structure to fill
 * @return 0 on success, -1 on failure
 */
int save_get_info(uint8_t slot, save_info_t *info);

/**
 * Delete a save slot
 * @param slot Slot number (0 to MAX_SAVE_SLOTS-1)
 * @return 0 on success, -1 on failure
 */
int save_delete(uint8_t slot);

/**
 * Delete all save slots for the current game
 * @return 0 on success, -1 on failure
 */
int save_delete_all(void);

#endif /* SAVE_H */
