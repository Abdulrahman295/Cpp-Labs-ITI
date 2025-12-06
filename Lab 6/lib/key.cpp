#include "key.h"
#include <cstdio>

#include "terminal.h"

#ifdef _WIN32
#include <conio.h>

KeyInput detectKey() {
    if (!_kbhit()) return {K_NONE, 0};

    int ch = _getch();

    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
            case 72: return {K_UP, 0};
            case 80: return {K_DOWN, 0};
            case 75: return {K_LEFT, 0};
            case 77: return {K_RIGHT, 0};
            case 71: return {K_HOME, 0};
            case 79: return {K_END, 0};
            default: return {K_NONE, 0};
        }
    }

    switch (ch) {
        case 8:  return {K_BACKSPACE, 0};
        case 13: return {K_ENTER, '\n'}; // Return newline char for convenience
        case 27: return {K_ESCAPE, 0};
    }

    return {K_CHAR, (char)ch};
}

#else
#include <unistd.h>

KeyInput detectKey() {
    enableRawMode();

    char seq[4];
    int byte_read;

    byte_read = read(STDIN_FILENO, &seq[0], 1);

    if (byte_read <= 0) return {K_NONE, 0};

    if (seq[0] == 127 || seq[0] == 8) return {K_BACKSPACE, 0};

    if (seq[0] == '\n' || seq[0] == '\r') return {K_ENTER, '\n'};

    if (seq[0] == 27) {
        byte_read = read(STDIN_FILENO, &seq[1], 1);
        if (byte_read <= 0) return {K_ESCAPE, 0}; // Just a raw ESC press

        byte_read = read(STDIN_FILENO, &seq[2], 1);
        if (byte_read <= 0) return {K_NONE, 0};

        if (seq[1] == '[') {
            switch (seq[2]) {
                case 'A': return {K_UP, 0};
                case 'B': return {K_DOWN, 0};
                case 'C': return {K_RIGHT, 0};
                case 'D': return {K_LEFT, 0};
                case 'H': return {K_HOME, 0};
                case 'F': return {K_END, 0};
                default: return {K_NONE, 0};
            }
        }
    }

    return {K_CHAR, seq[0]};
}
#endif