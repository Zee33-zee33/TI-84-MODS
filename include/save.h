/**
 * save.h - Save/load system for TI-84 Pixel Games Engine
 * 
 * Provides persistent storage for game state
 */

#ifndef ENGINE_SAVE_H
#define ENGINE_SAVE_H

#include <stdint.h>
#include <stddef.h>

#define MAX_SAVE_SLOTS 8
#define MAX_SAVE_SIZE  1024

/**
 * Initialize the save system
 * 
 * @return 0 on success, non-zero on failure
 */
int save_init(void);

/**
 * Write data to a save slot
 * 
 * @param slot Save slot number (0 to MAX_SAVE_SLOTS-1)
 * @param data Pointer to data to save
 * @param size Size of data in bytes (max MAX_SAVE_SIZE)
 * @return 0 on success, non-zero on failure
 */
int save_write(int slot, const void *data, size_t size);

/**
 * Read data from a save slot
 * 
 * @param slot Save slot number (0 to MAX_SAVE_SLOTS-1)
 * @param buf Buffer to read data into
 * @param size Maximum size to read in bytes
 * @return Number of bytes read, or negative on error
 */
int save_read(int slot, void *buf, size_t size);

/**
 * Check if a save slot has data
 * 
 * @param slot Save slot number
 * @return 1 if slot has data, 0 if empty, negative on error
 */
int save_exists(int slot);

/**
 * Delete data from a save slot
 * 
 * @param slot Save slot number
 * @return 0 on success, non-zero on failure
 */
int save_delete(int slot);

/**
 * Cleanup save system resources
 */
void save_cleanup(void);

#endif /* ENGINE_SAVE_H */
