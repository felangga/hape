#include "hardware.h"
#include "ESP32-3248S035.h"
#include "esp_timer.h"
#define LGFX_USE_V1
#include <LovyanGFX.h>

static LGFX lcd;

void hardware_init(void)
{
    // Initialize hardware
    lcd.init();
    lcd.setRotation(0);
    lcd.setBrightness(128);
    lcd.setColorDepth(16);
}

void lvgl_init(void)
{
    // Initialize LVGL
    lv_init();

    // Create display and configure buffer
    lv_display_t *disp = lv_display_create(screenWidth, screenHeight);
    lv_display_set_flush_cb(disp, display_flush);
    lv_display_set_buffers(disp, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

    // Configure touch input
    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touchpad_read);

    // Start LVGL tick timer (1ms intervals)
    const esp_timer_create_args_t timer_args = {
        .callback = lv_tick_task,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t timer;
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer, 1000));
}

void lv_tick_task(void *arg) 
{
    lv_tick_inc(1);
}

void display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p) 
{
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;
    
    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    lcd.writePixels((uint16_t *)color_p, w * h, true);
    lcd.endWrite();
    
    lv_display_flush_ready(disp);
}

void touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) 
{
    uint16_t x, y;
    bool touched = lcd.getTouch(&x, &y);
    
    data->state = touched ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    if (touched) {
        data->point.x = x;
        data->point.y = y;
    }
}
