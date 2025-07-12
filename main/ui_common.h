#pragma once

#include "lvgl.h"
#include "ESP32-3248S035.h"

// Friend data structure
typedef struct {
    const char* name;
    const char* last_message;
    const char* time;
} friend_t;

// Global UI objects
extern lv_obj_t *friend_list_screen;
extern lv_obj_t *chat_screen;
extern lv_obj_t *current_friend_label;
extern lv_obj_t *message_area;
extern lv_obj_t *message_input;

// Friend data
extern friend_t friends[];
extern const int friends_count;

// Common UI functions
#ifdef __cplusplus
extern "C" {
#endif

void ui_init(void);
void ui_task(void *pvParameter);

#ifdef __cplusplus
}
#endif
