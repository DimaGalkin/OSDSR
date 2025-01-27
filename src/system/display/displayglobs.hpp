#pragma once

#include "display.hpp"

Display* GLOBAL_DISPLAY_MANAGER;

void printf(const char* string, const uint32_t color) {
    int c = 0;

    while (string[c] != '\0') {
        GLOBAL_DISPLAY_MANAGER->draw_char(string[c], color);
        ++c;
    }
}

void printf(const char c, const uint32_t color) {
    if (c == '\0') return;
    GLOBAL_DISPLAY_MANAGER->draw_char(c, color);
}