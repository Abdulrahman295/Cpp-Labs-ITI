#pragma once

enum Color {
    BLACK = 0,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    DEFAULT = 9
};

void initializeTerminal();

void enableRawMode();

void disableRawMode();

void setCursorPos(int x, int y);

void clearLine();

void clearScreen();

void setColor(Color fg, Color bg = BLACK);

void resetColor();