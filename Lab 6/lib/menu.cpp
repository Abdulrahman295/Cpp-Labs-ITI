#include <cstdio>
#include <string>
#include "menu.h"

#include "editor.h"
#include "terminal.h"
#include "key.h"

enum MenuOption {
    OPTION_NEW_FILE,
    OPTION_OPEN_FILE,
    OPTION_EXIT
};

struct MenuEntry {
    MenuOption option;
    std::string label;
};

static constexpr int MENU_SIZE = 3;

static const MenuEntry MENU_ITEMS[MENU_SIZE] = {
    { OPTION_NEW_FILE,     "New File"},
    { OPTION_OPEN_FILE, "Open File"},
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
    KeyInput input = {K_NONE, '\0'};
    int selectedEntryIndex = 0;
    drawMenu(selectedEntryIndex);

    do {
        input = detectKey();
        selectedEntryIndex = calculateIndexBasedOnKey(input.code, selectedEntryIndex);
        MenuEntry entry = MENU_ITEMS[selectedEntryIndex];

        if (input.code == K_ENTER) {
            switch (entry.option) {
                case OPTION_NEW_FILE:
                    createNewFile();
                    break;
                case OPTION_OPEN_FILE:
                    openFile();
                    break;
                case OPTION_EXIT:
                    return;
            }
        }

        if (input.code != K_NONE) {
            drawMenu(selectedEntryIndex);
        }
    } while (input.code != K_ESCAPE);
}