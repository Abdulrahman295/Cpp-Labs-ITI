#include "square.h"
#include "terminal.h"
#include "delay.h"
#include <cstdio>

static void drawCell(int row, int col, int value) {
    Color c = (Color)((value % 7) + 1); // Cycle through colors 1 to 7

    setColor(c);
    setCursorPos(col * 4, row);
    printf("%d", value);

    delay(0.5);
}

void drawSquare(int n) {
    int i = n / 2;
    int j = n - 1;

    for (int num = 1; num <= n * n; num++) {
        drawCell(i, j, num);

        if (num % n == 0) {
            j = (j - 1 + n) % n;
        } else {
            i = (i - 1 + n) % n;
            j = (j + 1) % n;
        }
    }
}