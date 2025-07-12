#pragma once

#include "ui_common.h"

// Friend list functions
void create_friend_list_screen(void);
void create_friend_item(lv_obj_t *parent, int index);

// Event callbacks
void friend_clicked_cb(lv_event_t * e);
