#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "editor.h"
#include "terminal.h"
#include "key.h"
#include "MyString.h"

struct EditorState {
    std::string filename;
    std::vector<Custom::String> lines;
    int cursorX, cursorY;
    int rowOffset, colOffset;
    bool isDirty;
    bool running;
    const int SCREEN_ROWS = 20, SCREEN_COLS = 80;

    EditorState()
        : cursorX(0), cursorY(0), rowOffset(0), colOffset(0), isDirty(false), running(true) {}
};

static void editorScroll(EditorState& E) {
    E.rowOffset = std::clamp(E.rowOffset, E.cursorY - E.SCREEN_ROWS + 1, E.cursorY);
    E.colOffset = std::clamp(E.colOffset, E.cursorX - E.SCREEN_COLS + 1, E.cursorX);
}

static void EditorClampCursor(EditorState& E) {
    int maxRow = (int)E.lines.size() - 1;
    E.cursorY = std::clamp(E.cursorY, 0, maxRow);

    int lineLen = (E.lines.empty()) ? 0 : (int)E.lines[E.cursorY].length();
    E.cursorX = std::clamp(E.cursorX, 0, lineLen);
}

static void editorInsertChar(EditorState& E, int c) {
    if (!std::isprint(c)) {
        return;
    }

    while (E.cursorY >= (int)E.lines.size()) {
        E.lines.push_back("");
    }

    Custom::String& line = E.lines[E.cursorY];

    if (E.cursorX > (int)line.length()) {
        E.cursorX = (int)line.length();
    }

    line.insert(E.cursorX, 1, (char)c);
    E.cursorX++;
    E.isDirty = true;
}

static void editorInsertNewLine(EditorState& E) {
    if (E.cursorX > (int)E.lines[E.cursorY].length()) {
        E.cursorX = (int)E.lines[E.cursorY].length();
    }

    Custom::String& currentLine = E.lines[E.cursorY];
    Custom::String newLineContent = currentLine.substr(E.cursorX);

    currentLine.erase(E.cursorX);

    auto insertionPoint = E.lines.begin() + E.cursorY + 1;
    E.lines.insert(insertionPoint , newLineContent);

    E.cursorY++;
    E.cursorX = 0;
    E.isDirty = true;
}

static void editorDeleteChar(EditorState& E) {
    if (E.cursorY >= (int)E.lines.size()) return;
    if (E.cursorX == 0 && E.cursorY == 0) return;

    Custom::String& currentLine = E.lines[E.cursorY];

    if (E.cursorX > 0) {
        currentLine.erase(E.cursorX - 1, 1);
        E.cursorX--;
    }
    else {
        int prevRowIndex = E.cursorY - 1;
        Custom::String& prevLine = E.lines[prevRowIndex];

        int newCursorX = (int)prevLine.length();

        prevLine += currentLine;

        auto rowToDelete = E.lines.begin() + E.cursorY;
        E.lines.erase(rowToDelete);

        E.cursorY = prevRowIndex;
        E.cursorX = newCursorX;
    }

    E.isDirty = true;
}

static bool editorSave(EditorState& E) {
    if (E.filename.empty()) return false;

    std::ofstream out(E.filename);
    if (!out.is_open()) {
        return false;
    }

    for (const auto& line : E.lines) {
        out << line << '\n';
    }

    if (out.fail()) {
        out.close(); // Clean up
        return false;
    }

    out.close();
    E.isDirty = false;
    return true;
}

static void editorDrawRows(EditorState& E, Custom::String& buffer) {
    for (int y = 0; y < E.SCREEN_ROWS; y++) {
        int fileRow = y + E.rowOffset;

        buffer += Ansi::CSI + std::to_string(y + 1) + Ansi::GO_TO_COL_1;

        if (fileRow < (int)E.lines.size()) {
            Custom::String& line = E.lines[fileRow];

            if (E.colOffset < (int)line.length()) {
                buffer += line.substr(E.colOffset, E.SCREEN_COLS);
            }
        }

        buffer += Ansi::ERASE_LINE;
    }
}

static void editorDrawStatusBar(EditorState& E, Custom::String& buffer) {
    // move Cursor to Bottom
    buffer += Ansi::CSI + std::to_string(E.SCREEN_ROWS + 1) + Ansi::GO_TO_COL_1;

    buffer += Ansi::INVERT_COLORS;

    const Custom::String leftText = " " + E.filename + (E.isDirty ? " [modified]" : "");
    const Custom::String rightText = "Ln " + std::to_string(E.cursorY + 1) + ", Col " + std::to_string(E.cursorX + 1) + " ";

    buffer += leftText;

    int padding = E.SCREEN_COLS - (int)leftText.length() - (int)rightText.length();
    if (padding > 0) {
        buffer.append(padding, ' ');
    }
    buffer += rightText;

    buffer += Ansi::RESET_FORMAT;
    buffer += Ansi::ERASE_LINE;
}


static void editorRefreshScreen(EditorState& E) {
    editorScroll(E);

    Custom::String buffer;

    buffer += Ansi::HIDE_CURSOR;
    buffer += Ansi::HOME_CURSOR;

    editorDrawRows(E, buffer);
    editorDrawStatusBar(E, buffer);

    int screenY = (E.cursorY - E.rowOffset) + 1;
    int screenX = (E.cursorX - E.colOffset) + 1;

    buffer += Ansi::CSI + std::to_string(screenY) + ";" + std::to_string(screenX) + "H";
    buffer += Ansi::SHOW_CURSOR;

    fwrite(buffer.c_str(), buffer.length(), 1, stdout);
}

static bool editorProcessExit(EditorState& E) {
    if (!E.isDirty) return true;

    Custom::String prompt = "File has unsaved changes. Save? (y/n/ESC)";
    Custom::String output;

    output += Ansi::CSI + std::to_string(E.SCREEN_ROWS + 1) + Ansi::GO_TO_COL_1;
    output += Ansi::INVERT_COLORS;
    output += prompt;
    output += Ansi::RESET_FORMAT;
    output += Ansi::ERASE_LINE;

    fwrite(output.c_str(), output.length(), 1, stdout);
    fflush(stdout);

    while (true) {
        KeyInput input = detectKey();

        if (input.code == K_NONE) continue;

        if (input.code == K_ESCAPE) {
            return false; // Cancel Exit
        }

        if (input.character == 'y' || input.character == 'Y') {
            editorSave(E);
            return true; // Save & Exit
        }

        if (input.character == 'n' || input.character == 'N') {
            return true; // Discard & Exit
        }
    }
}

static void editorApplyCursorOffset(EditorState& E, int dx, int dy) {
    E.cursorY += dy;
    E.cursorX += dx;

    if (dx == 0) {
        EditorClampCursor(E);
        return;
    }

    int totalRows = (int)E.lines.size();
    bool isValidRow = (E.cursorY >= 0 && E.cursorY < totalRows);
    int currentLineLen = isValidRow ? (int)E.lines[E.cursorY].length() : 0;

    if (E.cursorX < 0 && E.cursorY > 0) {
        E.cursorY--;
        E.cursorX = (int)E.lines[E.cursorY].length();

    } else if (E.cursorX > currentLineLen && E.cursorY < totalRows - 1) {
        E.cursorY++;
        E.cursorX = 0;
    }

    EditorClampCursor(E);
}

static void editorProcessKeypress(EditorState& E) {
    KeyInput input = detectKey();

    switch (input.code) {
        case K_ENTER:
            editorInsertNewLine(E);
            break;
        case K_BACKSPACE:
            editorDeleteChar(E);
            break;
        case K_LEFT:
            editorApplyCursorOffset(E, -1, 0);
            break;
        case K_RIGHT:
            editorApplyCursorOffset(E, 1, 0);
            break;
        case K_UP:
            editorApplyCursorOffset(E, 0, -1);
            break;
        case K_DOWN:
            editorApplyCursorOffset(E, 0, 1);
            break;
        case K_HOME:
            E.cursorX = 0;
            break;
        case K_END:
            if (E.cursorY < (int)E.lines.size()) {
                E.cursorX = (int) E.lines[E.cursorY].length();
            }
            break;
        case K_ESCAPE:
            if (editorProcessExit(E)) {
                E.running = false;
            }
            break;
        case K_CHAR:
            editorInsertChar(E, input.character);
            break;
        default:
            break;
    }
}

static void runEditor(EditorState& E) {
    while (E.running) {
        editorRefreshScreen(E);
        editorProcessKeypress(E);
    }
}

void createNewFile() {
    clearScreen();
    disableRawMode();
    std::cout << "Enter new filename: ";

    EditorState E;
    std::cin >> E.filename;
    E.lines.push_back("");
    runEditor(E);
}

void openFile() {
    clearScreen();
    disableRawMode();
    std::cout << "Enter filename to open: ";

    EditorState E;
    std::cin >> E.filename;

    std::ifstream fp(E.filename);
    if (!fp.is_open()) {
        clearScreen();
        std::cout << " Could not open file '" << E.filename << "'. Press [BACKSPACE] to continue...";
        while (detectKey().code != K_BACKSPACE){/* Wait */}
        return;
    }

    std::string line;
    while (std::getline(fp, line)) {
        E.lines.push_back(line);
    }

    fp.close();

    if (E.lines.empty()) {
        E.lines.push_back("");
    }

    runEditor(E);
}