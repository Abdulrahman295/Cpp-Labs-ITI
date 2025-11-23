#include "key.h"

#ifdef _WIN32
#include <conio.h>

KeyCode detectKey() {
    if (!_kbhit()) return K_NONE;

    int ch = _getch();

    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
            case 72: return K_UP;
            case 80: return K_DOWN;
            case 75: return K_LEFT;
            case 77: return K_RIGHT;
            case 71: return K_HOME;
            case 79: return K_END;
        }
    }

    switch (ch) {
        case 8:  return K_BACKSPACE;
        case 13: return K_ENTER;
        case 27: return K_ESCAPE;
    }

    return K_NONE;
}
#else
#include <unistd.h>

KeyCode detectKey() {
    char seq[4];
    int byte_read;

    byte_read = read(STDIN_FILENO, &seq[0], 1);
    if (!byte_read) return K_NONE;

    if (seq[0] == 127) return K_BACKSPACE;
    if (seq[0] == '\n' || seq[0] == '\r') return K_ENTER;

    if (seq[0] == 27) {
        byte_read = read(STDIN_FILENO, &seq[1], 1);
        if (!byte_read) return K_ESCAPE;

        byte_read = read(STDIN_FILENO, &seq[2], 1);
        if (!byte_read) return K_NONE;

        if (seq[1] == '[') {
            switch (seq[2]) {
                case 'A': return K_UP;
                case 'B': return K_DOWN;
                case 'C': return K_RIGHT;
                case 'D': return K_LEFT;
                case 'H': return K_HOME;
                case 'F': return K_END;
            }
        }
    }

    return K_NONE;
}
#endif