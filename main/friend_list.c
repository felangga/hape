#include "friend_list.h"
#include "chat_screen.h"
#include "ESP32-3248S035.h"

void create_friend_list_screen(void)
{
    friend_list_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(friend_list_screen, lv_color_hex(0x1976D2), 0);

    // Title bar
    lv_obj_t *title_bar = lv_obj_create(friend_list_screen);
    lv_obj_set_size(title_bar, screenWidth, 60);
    lv_obj_set_pos(title_bar, 0, 0);
    lv_obj_set_style_bg_color(title_bar, lv_color_hex(0x0D47A1), 0);
    lv_obj_set_style_border_width(title_bar, 0, 0);
    lv_obj_set_style_radius(title_bar, 0, 0);

    lv_obj_t *title_label = lv_label_create(title_bar);
    lv_label_set_text(title_label, "Friends");
    lv_obj_set_style_text_color(title_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_14, 0);
    lv_obj_center(title_label);

    // Friend list container - optimized for performance
    lv_obj_t *list_container = lv_obj_create(friend_list_screen);
    lv_obj_set_size(list_container, screenWidth - 20, screenHeight - 80);
    lv_obj_set_pos(list_container, 10, 70);
    lv_obj_set_style_bg_color(list_container, lv_color_white(), 0);
    lv_obj_set_style_border_width(list_container, 1, 0);
    lv_obj_set_style_radius(list_container, 10, 0);
    lv_obj_set_scroll_dir(list_container, LV_DIR_VER);
    
    // Performance optimizations for smooth scrolling
    lv_obj_set_style_bg_opa(list_container, LV_OPA_COVER, 0);
    lv_obj_clear_flag(list_container, LV_OBJ_FLAG_SCROLL_ELASTIC);

    // Create friend items
    for (int i = 0; i < friends_count; i++) {
        create_friend_item(list_container, i);
    }
}

void create_friend_item(lv_obj_t *parent, int index)
{
    lv_obj_t *friend_item = lv_obj_create(parent);
    lv_obj_set_size(friend_item, screenWidth - 50, 80);
    lv_obj_set_pos(friend_item, 5, index * 85);
    
    // Optimize styling - combine multiple style operations
    static lv_style_t friend_item_style;
    static bool style_initialized = false;
    if (!style_initialized) {
        lv_style_init(&friend_item_style);
        lv_style_set_bg_color(&friend_item_style, lv_color_white());
        lv_style_set_border_width(&friend_item_style, 1);
        lv_style_set_border_color(&friend_item_style, lv_color_hex(0xE0E0E0));
        lv_style_set_radius(&friend_item_style, 5);
        style_initialized = true;
    }
    lv_obj_add_style(friend_item, &friend_item_style, 0);
    lv_obj_add_flag(friend_item, LV_OBJ_FLAG_CLICKABLE);

    // Friend name
    lv_obj_t *name_label = lv_label_create(friend_item);
    lv_label_set_text(name_label, friends[index].name);
    lv_obj_set_style_text_font(name_label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(name_label, lv_color_black(), 0);
    lv_obj_set_pos(name_label, 15, 10);

    // Last message
    lv_obj_t *msg_label = lv_label_create(friend_item);
    lv_label_set_text(msg_label, friends[index].last_message);
    lv_obj_set_style_text_font(msg_label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(msg_label, lv_color_hex(0x666666), 0);
    lv_obj_set_pos(msg_label, 15, 35);

    // Time
    lv_obj_t *time_label = lv_label_create(friend_item);
    lv_label_set_text(time_label, friends[index].time);
    lv_obj_set_style_text_font(time_label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(time_label, lv_color_hex(0x999999), 0);
    lv_obj_align(time_label, LV_ALIGN_TOP_RIGHT, -15, 10);

    // Add click event
    lv_obj_add_event_cb(friend_item, friend_clicked_cb, LV_EVENT_CLICKED, (void*)(intptr_t)index);
}

void friend_clicked_cb(lv_event_t * e)
{
    int friend_index = (int)(intptr_t)lv_event_get_user_data(e);
    show_chat_screen(friends[friend_index].name);
}
