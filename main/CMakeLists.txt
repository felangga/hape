idf_component_register(SRCS "hardware.cpp" "chat_screen.c" "friend_list.c" "ui_common.c" "main.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES "lvgl" "LovyanGFX"
                    )
# add "ui" among REQUIRES if Squareline exported "ui" folder was copied to components folder
