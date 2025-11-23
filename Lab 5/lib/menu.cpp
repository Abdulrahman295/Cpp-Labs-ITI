#include <cstdio>
#include <string>
#include "menu.h"
#include "employee.h"
#include "terminal.h"
#include "key.h"

enum MenuOption {
    OPTION_NEW,
    OPTION_DISPLAY,
    OPTION_EXIT
};

struct MenuEntry {
    MenuOption option;
    std::string label;
};

static constexpr int MENU_SIZE = 3;

static const MenuEntry MENU_ITEMS[MENU_SIZE] = {
    { OPTION_NEW,     "New Record"},
    { OPTION_DISPLAY, "Display Records"},
    { OPTION_EXIT,    "Exit Application"}
};

static void drawMenu(int selectedEntryIndex) {
    clearScreen();

    for (int i = 0; i < MENU_SIZE; ++i) {
        setCursorPos(5, i);
        const MenuEntry& entry = MENU_ITEMS[i];

        if (i == selectedEntryIndex) {
            setColor(WHITE, BLUE);
            printf(" -> %s ", entry.label.c_str());
            resetColor();
        } else {
            printf("    %s ", entry.label.c_str());
        }

        clearLine();
    }
}

static int calculateIndexBasedOnKey(KeyCode keyCode, int currentIndex) {
    switch (keyCode) {
        case K_LEFT:
        case K_UP:
            return (currentIndex - 1 + MENU_SIZE) % MENU_SIZE;
        case K_RIGHT:
        case K_DOWN:
            return (currentIndex + 1) % MENU_SIZE;
        case K_HOME:
            return 0;
        case K_END:
            return  MENU_SIZE - 1;
        default:
            return currentIndex;
    }
}

void startMenu() {
    enableRawMode();
    KeyCode keyCode = K_NONE;
    int selectedEntryIndex = 0;
    drawMenu(selectedEntryIndex);

    do {
        keyCode = detectKey();
        selectedEntryIndex = calculateIndexBasedOnKey(keyCode, selectedEntryIndex);
        MenuEntry entry = MENU_ITEMS[selectedEntryIndex];

        if (keyCode == K_ENTER) {
            switch (entry.option) {
                case OPTION_NEW:
                    createEmployee();
                    break;
                case OPTION_DISPLAY:
                     displayEmployees();
                    break;
                case OPTION_EXIT:
                    disableRawMode();
                    clearScreen();
                    return;
            }
        }

        if (keyCode != K_NONE) {
            drawMenu(selectedEntryIndex);
        }
    } while (keyCode != K_ESCAPE);
}