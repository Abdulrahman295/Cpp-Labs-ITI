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

namespace Ansi {
    const auto CSI = "\x1b[";

    const auto ERASE_LINE = "\x1b[K";
    const auto CLEAR_SCREEN = "\x1b[2J";

    const auto HIDE_CURSOR = "\x1b[?25l";
    const auto SHOW_CURSOR = "\x1b[?25h";
    const auto HOME_CURSOR = "\x1b[H";
    const auto GO_TO_COL_1 = ";1H";

    const auto INVERT_COLORS = "\x1b[7m";
    const auto RESET_FORMAT = "\x1b[m";
}

void enableRawMode();

void disableRawMode();

void setCursorPos(int x, int y);

void clearLine();

void clearScreen();

void setColor(Color fg, Color bg = BLACK);

void resetColor();