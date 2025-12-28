#ifndef SAVE_H
#define SAVE_H

#include <stddef.h>

/* Initialize the save system */
void save_init(void);

/* Save data to a file */
int save_write(const char *filename, const void *data, size_t size);

/* Load data from a file */
int save_read(const char *filename, void *data, size_t size);

/* Check if a save file exists */
int save_exists(const char *filename);

/* Delete a save file */
int save_delete(const char *filename);

/* Shutdown the save system */
void save_shutdown(void);

#endif /* SAVE_H */
