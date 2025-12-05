#include <iostream>
#include "lib/Stack.h"
#include <string>

using namespace Custom;

int main() {
    std::cout << "--- Integer Stack Tests ---\n";
    Stack<int> intStack;

    // --- Test 1: Basic Operations ---
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    std::cout << "Stack: " << intStack << "\n";
    std::cout << "Top: " << intStack.top() << "\n";

    intStack.pop();
    std::cout << "After pop: " << intStack << "\n";

    // --- Test 2: Copy Constructor & Ops ---
    Stack<int> copyStack = intStack;
    std::cout << "Copy: " << copyStack << "\n";
    std::cout << "Are equal? " << (intStack == copyStack ? "Yes" : "No") << "\n";

    Stack<int> addedStack = intStack + copyStack;
    std::cout << "Added Stacks: " << addedStack << "\n";


    // --- Test 3: String Stack (Works with Objects) ---
    std::cout << "\n--- String Stack Tests ---\n";
    Stack<std::string> strStack;

    strStack.push("Hello");
    strStack.push("World");
    strStack.push("Code");

    std::cout << "String Stack: " << strStack << "\n";

    strStack.pop();
    std::cout << "Popped: " << strStack << "\n";

    return 0;
}