#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hardware.h"
#include "ui_common.h"

extern "C" {
void app_main(void)
{
    // Initialize hardware and LVGL
    hardware_init();
    lvgl_init();

    // Create UI task with larger stack and higher priority for better performance
    xTaskCreate(ui_task, "ui_task", 8192, NULL, 6, NULL);
}
}


