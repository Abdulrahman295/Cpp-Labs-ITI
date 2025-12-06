#pragma once

enum KeyCode {
    K_NONE = 0,
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_HOME,
    K_END,
    K_ESCAPE,
    K_BACKSPACE,
    K_ENTER,
    K_CHAR
};

struct KeyInput {
    KeyCode code;
    char character;
};

KeyInput detectKey();