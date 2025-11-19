#include "lib/delay.h"
#include "lib/terminal.h"

int main() {
    initializeTerminal();
    setCursorPos(10, 5);
    setColor(GREEN, YELLOW);
    printf("Hello, World!");
    
    delay(5);
    
    resetColor();
    clearScreen();
    printf("screen cleared!");
    
    return 0;
}
