/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */

#include <stdlib.h>
#include <unistd.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_display_t *hal_init(int32_t w, int32_t h);

static void settings_page_create(void);

/**********************
 *  STATIC VARIABLES
 **********************/

static const char *const settings_titles[] = {
        "WLAN",
        "Bluetooth",
        "PersonalHotspot",
        "Notifications",
        "DoNotDisturb",
        "General",
        "DisplayBrightness",
        "Accessibility",
        "Wallpaper",
        "PasswordsAccounts",
        "Battery",
        "Privacy",
        "Camera",
        "Keyboards",
        "Location",
        "Music",
};

const uint32_t settings_items_count = sizeof(settings_titles) / sizeof(settings_titles[0]);

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

int main(int argc, char **argv) {
    (void) argc; /*Unused*/
    (void) argv; /*Unused*/

    /*Initialize LVGL*/
    lv_init();

    /*Initialize the display, and the input devices*/
    hal_init(480, 480);

    settings_page_create();

    /*To hide the memory and performance indicators in the corners
     *disable `LV_USE_MEM_MONITOR` and `LV_USE_PERF_MONITOR` in `lv_conf.h`*/

    while (1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_timer_handler();
        usleep(10 * 1000);
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_display_t *hal_init(int32_t w, int32_t h) {
    lv_group_set_default(lv_group_create());

    lv_display_t *disp = lv_sdl_window_create(w, h);

    lv_indev_t *mouse = lv_sdl_mouse_create();
    lv_indev_set_group(mouse, lv_group_get_default());
    lv_indev_set_display(mouse, disp);
    lv_display_set_default(disp);

    LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
    lv_obj_t *cursor_obj;
    cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
    lv_image_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
    lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

    lv_indev_t *mousewheel = lv_sdl_mousewheel_create();
    lv_indev_set_display(mousewheel, disp);

    lv_indev_t *keyboard = lv_sdl_keyboard_create();
    lv_indev_set_display(keyboard, disp);
    lv_indev_set_group(keyboard, lv_group_get_default());

    return disp;
}

static lv_obj_t *settings_header_create(lv_obj_t *settings_page) {
    lv_obj_t *header_toast = lv_obj_create(settings_page);
    lv_obj_remove_style_all(header_toast);
    lv_obj_set_size(header_toast, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(header_toast, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(header_toast, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t *header = lv_label_create(header_toast);
    lv_label_set_text(header, "Settings");
    lv_obj_set_style_text_color(header, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(header, &lv_font_montserrat_38, LV_PART_MAIN);
    return header;
}

static lv_obj_t *settings_item_create(lv_obj_t *settings_page, const char *title, const uint8_t *icon_path) {
    lv_obj_t *item = lv_obj_create(settings_page);

    lv_obj_remove_style_all(item);

    lv_obj_set_size(item, LV_PCT(80), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(item, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(item, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_bg_color(item, lv_color_hex3(0x666), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(item, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(item, 40, LV_PART_MAIN);

    lv_obj_t *icon = lv_image_create(item);
    lv_image_set_src(icon, icon_path);
    lv_obj_set_size(icon, 64, 64);
    lv_obj_set_style_margin_all(icon, 16, LV_PART_MAIN);
    lv_image_set_align(icon, LV_IMAGE_ALIGN_STRETCH);
    lv_obj_set_style_border_width(icon, 2, LV_PART_MAIN);
    lv_obj_set_style_border_opa(icon, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_color(icon, lv_color_hex3(0xaaa), LV_PART_MAIN);
    lv_obj_set_style_radius(icon, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_border_post(icon, true, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(item);
    lv_label_set_text(label, title);
    lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_22, LV_PART_MAIN);
    lv_obj_set_style_margin_left(label, 20, LV_PART_MAIN);
    lv_obj_set_flex_grow(label, 1);

    lv_obj_t *forward_icon = lv_image_create(item);
    lv_image_set_src(forward_icon, "/res/Forward.png");
    lv_obj_set_size(forward_icon, 32, 32);
    lv_obj_set_style_margin_right(forward_icon, 40, LV_PART_MAIN);
    lv_image_set_align(forward_icon, LV_IMAGE_ALIGN_STRETCH);

    return item;
}

static void settings_page_create(void) {
    lv_obj_t *page = lv_obj_create(lv_screen_active());
    lv_obj_remove_style_all(page);

    lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(page, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(page, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_set_flex_flow(page, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(page, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // create header
    lv_obj_t *header_toast = settings_header_create(page);
    lv_obj_set_style_margin_top(header_toast, 22, LV_PART_MAIN);
    lv_obj_set_style_margin_bottom(header_toast, 22, LV_PART_MAIN);

    // create items
    for (uint32_t i = 0; i < settings_items_count; i++) {
        const char *title = settings_titles[i];
        char path[100];
        lv_snprintf(path, sizeof(path), "/res/%s.png", title);
        lv_obj_t *item = settings_item_create(page, title, (const uint8_t *) path);

        lv_obj_set_style_margin_ver(item, 10, LV_PART_MAIN);
    }
}
