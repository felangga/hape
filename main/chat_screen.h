#pragma once

#include "ui_common.h"

// Chat screen functions
void create_chat_screen(void);
void show_chat_screen(const char* friend_name);

// Event callbacks
void back_button_cb(lv_event_t * e);
void send_button_cb(lv_event_t * e);
