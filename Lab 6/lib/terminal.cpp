#include "terminal.h"
#include <cstdio>

#ifdef _WIN32
#include <windows.h>

struct WindowsTerminalState {
    DWORD originalMode;
    HANDLE hOut;
    bool isSaved;
};

static WindowsTerminalState termState = { 0, INVALID_HANDLE_VALUE, false };

static bool isAnsiModeEnabled(DWORD mode) {
    return (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
}

void enableRawMode() {
    setbuf(stdout, NULL);

    if (termState.hOut == INVALID_HANDLE_VALUE) {
        termState.hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    DWORD currentMode;
    GetConsoleMode(termState.hOut, &currentMode);

    if (!termState.isSaved && !isAnsiModeEnabled(currentMode)) {
        termState.originalMode = currentMode;
        termState.isSaved = true;
    }

    currentMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(termState.hOut, currentMode);
}

void disableRawMode() {
    if (termState.isSaved && termState.hOut != INVALID_HANDLE_VALUE) {
        SetConsoleMode(termState.hOut, termState.originalMode);
    }
}
#else
#include <termios.h>
#include <unistd.h>

struct LinuxTerminalState {
    struct termios originalAttributes;
    bool isSaved;
};

static LinuxTerminalState termState = { {}, false};

static bool isCanonicalModeEnabled(const struct termios& terminalAttributes) {
    return (terminalAttributes.c_lflag & ICANON) != 0;
}

void enableRawMode() {
    setbuf(stdout, NULL);

    struct termios currentAttributes;
    tcgetattr(STDIN_FILENO, &currentAttributes);

    if (!termState.isSaved && isCanonicalModeEnabled(currentAttributes)) {
        termState.originalAttributes = currentAttributes;
        termState.isSaved = true;
    }

    currentAttributes.c_lflag &= ~(ICANON | ECHO);
    const int READ_MIN_BYTES = 0;
    const int READ_TIMEOUT_DS = 1;
    currentAttributes.c_cc[VMIN] = READ_MIN_BYTES;
    currentAttributes.c_cc[VTIME] = READ_TIMEOUT_DS;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &currentAttributes);
}

void disableRawMode() {
    if (termState.isSaved) {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &termState.originalAttributes);
    }
}
#endif

void setCursorPos(int x, int y) {
    printf("%s%d;%dH", Ansi::CSI, y + 1, x + 1);
}

void clearLine() {
    printf("%s", Ansi::ERASE_LINE);
}

void clearScreen() {
    printf("%s%s", Ansi::CLEAR_SCREEN, Ansi::HOME_CURSOR);
}

void setColor(Color fg, Color bg) {
    int fgCode = (fg == DEFAULT) ? 39 : (30 + fg);
    int bgCode = (bg == DEFAULT) ? 49 : (40 + bg);
    printf("%s%d;%dm", Ansi::CSI, fgCode, bgCode);
}

void resetColor() {
    printf("%s", Ansi::RESET_FORMAT);
}
