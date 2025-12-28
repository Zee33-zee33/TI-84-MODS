/**
 * ui.h - User Interface system for TI-84 Pixel Games Engine
 * 
 * Provides simple menu and dialog rendering
 */

#ifndef ENGINE_UI_H
#define ENGINE_UI_H

#include <stdint.h>

/**
 * Draw a simple menu with title and selectable items
 * 
 * @param x X coordinate for menu position
 * @param y Y coordinate for menu position
 * @param title Menu title (null-terminated string)
 * @param items Array of menu item strings
 * @param count Number of items in the array
 * @param selected Index of currently selected item (0-based)
 */
void menu_draw(int x, int y, const char *title, const char **items, int count, int selected);

/**
 * Draw a yes/no dialog box
 * 
 * @param x X coordinate for dialog position
 * @param y Y coordinate for dialog position
 * @param message Dialog message (null-terminated string)
 * @param selected 0 for Yes selected, 1 for No selected
 */
void dialog_yes_no(int x, int y, const char *message, int selected);

/**
 * Draw a simple message box
 * 
 * @param x X coordinate for box position
 * @param y Y coordinate for box position
 * @param message Message text (null-terminated string)
 */
void message_box(int x, int y, const char *message);

#endif /* ENGINE_UI_H */
