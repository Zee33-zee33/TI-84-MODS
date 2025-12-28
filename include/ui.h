#ifndef UI_H
#define UI_H

#include <stdint.h>
#include <stdbool.h>
#include "render.h"

#define MAX_MENU_ITEMS 10
#define MAX_MENU_TEXT_LEN 32

/* Menu item structure */
typedef struct {
    char text[MAX_MENU_TEXT_LEN];
    uint8_t enabled;
} menu_item_t;

/* Menu structure */
typedef struct {
    const char *title;
    menu_item_t items[MAX_MENU_ITEMS];
    uint8_t item_count;
    uint8_t selected_index;
} menu_t;

/* Dialog result */
typedef enum {
    DIALOG_YES = 1,
    DIALOG_NO = 0,
    DIALOG_CANCEL = -1
} dialog_result_t;

/**
 * Initialize the UI system
 * @return 0 on success, -1 on failure
 */
int ui_init(void);

/**
 * Create a new menu
 * @param title Menu title
 * @return Pointer to menu structure, NULL on failure
 */
menu_t *ui_menu_create(const char *title);

/**
 * Add an item to a menu
 * @param menu Pointer to menu structure
 * @param text Item text
 * @param enabled Whether the item is selectable
 * @return 0 on success, -1 on failure
 */
int ui_menu_add_item(menu_t *menu, const char *text, bool enabled);

/**
 * Draw a menu to the screen
 * @param menu Pointer to menu structure
 */
void ui_menu_draw(const menu_t *menu);

/**
 * Handle menu input and update selection
 * @param menu Pointer to menu structure
 * @return Selected item index when Enter is pressed, -1 if back/cancel
 */
int ui_menu_update(menu_t *menu);

/**
 * Show a yes/no dialog
 * @param title Dialog title
 * @param message Dialog message
 * @return DIALOG_YES or DIALOG_NO
 */
dialog_result_t ui_dialog_yes_no(const char *title, const char *message);

/**
 * Show an OK dialog (informational message)
 * @param title Dialog title
 * @param message Dialog message
 */
void ui_dialog_ok(const char *title, const char *message);

/**
 * Draw a dialog box
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Dialog width
 * @param height Dialog height
 * @param title Dialog title
 */
void ui_draw_dialog_box(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const char *title);

/**
 * Draw a button
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Button width
 * @param text Button text
 * @param selected Whether button is selected
 */
void ui_draw_button(uint16_t x, uint16_t y, uint16_t width, const char *text, bool selected);

#endif /* UI_H */
