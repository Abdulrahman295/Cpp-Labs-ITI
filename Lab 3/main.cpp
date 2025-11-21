#include <iostream>
#include "lib/terminal.h"
#include "lib/square.h"

int getValidDimension() {
    int n;
    std::cout << "Enter the dimension of the square (Odd number >= 1): ";

    if (!(std::cin >> n)) {
        std::cout << "Error: Input is not a valid number.\n";
        return -1;
    }

    if (n < 1 || n % 2 == 0) {
        std::cout << "Error: Dimension must be a positive, ODD number.\n";
        return -1;
    }

    return n;
}

int main() {
    int dimension = getValidDimension();
    if (dimension == -1) {
        return 1;
    }

    initializeTerminal();
    clearScreen();
    drawSquare(dimension);
    return 0;
}