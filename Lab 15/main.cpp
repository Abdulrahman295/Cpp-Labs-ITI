#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    LinkedList list;

    // 1. Setup: Create an unsorted list
    list.insert_end(40);
    list.insert_end(10);
    list.insert_end(30);
    list.insert_end(50);
    list.insert_end(20);

    cout << "Original List: ";
    list.print();

    // ---------------------------------------------------------
    // TEST 1: Linear Search 
    // ---------------------------------------------------------
    cout << "\n[Test 1] Linear Search:\n";
    cout << " - Search for 30: " << (list.linearSearch(30) ? "Found" : "Not Found") << "\n";
    cout << " - Search for 99: " << (list.linearSearch(99) ? "Found" : "Not Found") << "\n";

    // ---------------------------------------------------------
    // TEST 2: Sorting (Using Insertion Sort)
    // ---------------------------------------------------------
    cout << "\n[Test 2] Running Insertion Sort...\n";

    list.insertionSort();

    cout << "Sorted List:   ";
    list.print();

    // ---------------------------------------------------------
    // TEST 3: Binary Search
    // ---------------------------------------------------------
    cout << "\n[Test 3] Binary Search:\n";
    cout << " - Search for 20: " << (list.binarySearch(20) ? "Found" : "Not Found") << "\n";
    cout << " - Search for 99: " << (list.binarySearch(99) ? "Found" : "Not Found") << "\n";

    return 0;
}