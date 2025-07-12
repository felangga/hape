#include "ui_common.h"
#include "friend_list.h"
#include "chat_screen.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Global UI objects
lv_obj_t *friend_list_screen = NULL;
lv_obj_t *chat_screen = NULL;
lv_obj_t *current_friend_label = NULL;
lv_obj_t *message_area = NULL;
lv_obj_t *message_input = NULL;

// Friend data
friend_t friends[] = {
    {"Alice", "Hey! How are you?", "10:30"},
    {"Bob", "See you tomorrow!", "09:15"},
    {"Charlie", "Thanks for the help", "Yesterday"},
    {"Diana", "Let's meet for coffee", "Yesterday"},
    {"Eve", "Great idea!", "Tuesday"}
};

const int friends_count = sizeof(friends) / sizeof(friends[0]);

void ui_init(void)
{
    // Create UI screens
    create_friend_list_screen();
    create_chat_screen();

    // Show friend list initially
    lv_screen_load(friend_list_screen);
}

void ui_task(void *pvParameter)
{
    // Initialize UI
    ui_init();

    // Main UI loop - optimized for better responsiveness
    while (1) {
        uint32_t time_till_next = lv_timer_handler();
        if (time_till_next > 5) {
            vTaskDelay(pdMS_TO_TICKS(5)); // Reduced delay for better responsiveness
        } else {
            vTaskDelay(pdMS_TO_TICKS(time_till_next));
        }
    }
}
