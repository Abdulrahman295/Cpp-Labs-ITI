#include "terminal.h"
#include <cstdio>

#ifdef _WIN32
#include <windows.h>

static DWORD originalConsoleMode;

static bool isAnsiModeEnabled(DWORD mode) {
    return (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
}

void enableRawMode() {
    setbuf(stdout, NULL);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD currentMode;
    GetConsoleMode(hOut, &currentMode);

    if (!isAnsiModeEnabled(currentMode)) {
        originalConsoleMode = currentMode;
    }

    currentMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, currentMode);
}

void disableRawMode() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(hOut, originalConsoleMode);
}
#else
#include <termios.h>
#include <unistd.h>

const int READ_MIN_BYTES = 0;
const int READ_TIMEOUT_DS = 1;

static struct termios originalTerminalAttributes;

static bool isCanonicalModeEnabled(const struct termios& terminalAttributes) {
    return (terminalAttributes.c_lflag & ICANON) != 0;
}

void enableRawMode() {
    setbuf(stdout, NULL);

    struct termios currentTerminalAttributes;
    tcgetattr(STDIN_FILENO, &currentTerminalAttributes);

    if (isCanonicalModeEnabled(currentTerminalAttributes)) {
        originalTerminalAttributes = currentTerminalAttributes;
    }

    currentTerminalAttributes.c_lflag &= ~(ICANON | ECHO);
    currentTerminalAttributes.c_cc[VMIN] = READ_MIN_BYTES;
    currentTerminalAttributes.c_cc[VTIME] = READ_TIMEOUT_DS;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &currentTerminalAttributes);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTerminalAttributes);
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
