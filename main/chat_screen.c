#include "chat_screen.h"
#include "ESP32-3248S035.h"
#include <string.h>

void create_chat_screen(void)
{
    chat_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(chat_screen, lv_color_hex(0xF5F5F5), 0);

    // Title bar
    lv_obj_t *title_bar = lv_obj_create(chat_screen);
    lv_obj_set_size(title_bar, screenWidth, 60);
    lv_obj_set_pos(title_bar, 0, 0);
    lv_obj_set_style_bg_color(title_bar, lv_color_hex(0x0D47A1), 0);
    lv_obj_set_style_border_width(title_bar, 0, 0);
    lv_obj_set_style_radius(title_bar, 0, 0);

    // Back button
    lv_obj_t *back_btn = lv_btn_create(title_bar);
    lv_obj_set_size(back_btn, 50, 40);
    lv_obj_set_pos(back_btn, 10, 10);
    lv_obj_set_style_bg_color(back_btn, lv_color_hex(0x1976D2), 0);
    lv_obj_add_event_cb(back_btn, back_button_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "<");
    lv_obj_set_style_text_color(back_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(back_label, &lv_font_montserrat_14, 0);
    lv_obj_center(back_label);

    // Friend name in title
    current_friend_label = lv_label_create(title_bar);
    lv_label_set_text(current_friend_label, "Chat");
    lv_obj_set_style_text_color(current_friend_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(current_friend_label, &lv_font_montserrat_14, 0);
    lv_obj_set_pos(current_friend_label, 80, 20);

    // Message area
    message_area = lv_obj_create(chat_screen);
    lv_obj_set_size(message_area, screenWidth - 20, screenHeight - 140);
    lv_obj_set_pos(message_area, 10, 70);
    lv_obj_set_style_bg_color(message_area, lv_color_white(), 0);
    lv_obj_set_style_border_width(message_area, 1, 0);
    lv_obj_set_style_radius(message_area, 10, 0);
    lv_obj_set_scroll_dir(message_area, LV_DIR_VER);

    // Input area
    lv_obj_t *input_container = lv_obj_create(chat_screen);
    lv_obj_set_size(input_container, screenWidth - 20, 60);
    lv_obj_set_pos(input_container, 10, screenHeight - 70);
    lv_obj_set_style_bg_color(input_container, lv_color_white(), 0);
    lv_obj_set_style_border_width(input_container, 1, 0);
    lv_obj_set_style_radius(input_container, 10, 0);

    // Message input
    message_input = lv_textarea_create(input_container);
    lv_obj_set_size(message_input, screenWidth - 120, 40);
    lv_obj_set_pos(message_input, 10, 10);
    lv_textarea_set_placeholder_text(message_input, "Type a message...");
    lv_textarea_set_one_line(message_input, true);

    // Send button
    lv_obj_t *send_btn = lv_btn_create(input_container);
    lv_obj_set_size(send_btn, 80, 40);
    lv_obj_set_pos(send_btn, screenWidth - 110, 10);
    lv_obj_set_style_bg_color(send_btn, lv_color_hex(0x4CAF50), 0);
    lv_obj_add_event_cb(send_btn, send_button_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *send_label = lv_label_create(send_btn);
    lv_label_set_text(send_label, "Send");
    lv_obj_set_style_text_color(send_label, lv_color_white(), 0);
    lv_obj_center(send_label);
}

void show_chat_screen(const char* friend_name)
{
    lv_label_set_text(current_friend_label, friend_name);
    
    // Clear previous messages
    lv_obj_clean(message_area);
    
    // Add some sample messages
    lv_obj_t *received_msg = lv_obj_create(message_area);
    lv_obj_set_size(received_msg, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(received_msg, lv_color_hex(0xE0E0E0), 0);
    lv_obj_set_style_radius(received_msg, 15, 0);
    lv_obj_set_style_border_width(received_msg, 0, 0);
    lv_obj_align(received_msg, LV_ALIGN_TOP_LEFT, 10, 10);

    lv_obj_t *received_label = lv_label_create(received_msg);
    lv_label_set_text(received_label, "Hello! How are you?");
    lv_obj_set_style_text_color(received_label, lv_color_black(), 0);
    lv_obj_set_style_pad_all(received_label, 10, 0);
    lv_obj_center(received_label);

    lv_screen_load(chat_screen);
}

void back_button_cb(lv_event_t * e)
{
    lv_screen_load(friend_list_screen);
}

void send_button_cb(lv_event_t * e)
{
    const char* message = lv_textarea_get_text(message_input);
    if (strlen(message) > 0) {
        // Create message bubble
        lv_obj_t *msg_bubble = lv_obj_create(message_area);
        lv_obj_set_size(msg_bubble, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(msg_bubble, lv_color_hex(0x2196F3), 0);
        lv_obj_set_style_radius(msg_bubble, 15, 0);
        lv_obj_set_style_border_width(msg_bubble, 0, 0);
        lv_obj_align(msg_bubble, LV_ALIGN_TOP_RIGHT, -10, LV_PCT(10));

        lv_obj_t *msg_label = lv_label_create(msg_bubble);
        lv_label_set_text(msg_label, message);
        lv_obj_set_style_text_color(msg_label, lv_color_white(), 0);
        lv_obj_set_style_pad_all(msg_label, 10, 0);
        lv_obj_center(msg_label);

        // Clear input
        lv_textarea_set_text(message_input, "");

        // Scroll to bottom
        lv_obj_scroll_to_y(message_area, lv_obj_get_scroll_y(message_area) + 100, LV_ANIM_ON);
    }
}
