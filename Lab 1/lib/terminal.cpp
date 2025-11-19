#include "terminal.h"
#include <cstdio>

#ifdef _WIN32
#include <windows.h>

void initializeTerminal() {
    setbuf(stdout, NULL);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
#include <termios.h>
#include <unistd.h>

void initializeTerminal() {
    setbuf(stdout, NULL);

    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ICANON | ECHO);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
#endif

void setCursorPos(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void clearLine() {
    printf("\033[K");
}

void clearScreen() {
    printf("\033[2J\033[3J\033[H");
}

void setColor(Color fg, Color bg) {
    int fgCode = (fg == DEFAULT) ? 39 : (30 + fg);
    int bgCode = (bg == DEFAULT) ? 49 : (40 + bg);
    printf("\033[%d;%dm", fgCode, bgCode);
}

void resetColor() {
    printf("\033[0m");
}
