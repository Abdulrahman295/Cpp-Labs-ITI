#include <iostream>
#include <string>
#include "lib/PyList.h"
#include "lib/Any.h"

int main() {
    try {
        std::cout << "=== 1. Creating List & Appending ===" << std::endl;
        PyList myList;

        myList.append(10);              
        myList.append(std::string("Hello"));
        myList.append(3.14);        

        std::cout << "List: " << myList << std::endl;

        std::cout << "\n=== 2. Testing Insert ===" << std::endl;
        myList.insert(1, 99);
        std::cout << "After insert(1, 99): " << myList << std::endl;


        std::cout << "\n=== 3. Testing Pop ===" << std::endl;
        Any poppedItem = myList.pop(2);

        std::cout << "Popped Item: " << poppedItem << std::endl;
        std::cout << "List after pop: " << myList << std::endl;


        std::cout << "\n=== 4. Testing Access ===" << std::endl;
        Any val = myList[0];
        std::cout << val << std::endl;


        std::cout << "\n=== 5. Testing Out of Bounds (Safety) ===" << std::endl;
        // myList[100]; // Uncomment to test crash/error


        std::cout << "\n=== 6. Testing Direct Input to Any ===" << std::endl;
        Any userVar;

        std::cout << "Enter a value (Int, Double, Boolean, or String): ";
        std::cin >> userVar; // Direct input! Auto-detects type.

        std::cout << "You entered: " << userVar.type() << std::endl;

        // Prove it works by adding it to the list
        myList.append(userVar);
        std::cout << "List after appending your input: " << myList << std::endl;


    } catch (const char* msg) {
        std::cerr << "EXCEPTION CAUGHT: " << msg << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }

    return 0;
}