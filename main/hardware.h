#pragma once

#include "lvgl.h"
#include <LovyanGFX.h>

// Hardware abstraction functions
void hardware_init(void);
void display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p);
void touchpad_read(lv_indev_t *indev, lv_indev_data_t *data);
void lv_tick_task(void *arg);

// LVGL setup functions
void lvgl_init(void);
