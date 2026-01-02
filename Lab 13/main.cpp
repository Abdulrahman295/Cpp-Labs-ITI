#include <iostream>
#include "LinkedList.h"

using namespace std;

void print_test_header(string test_name) {
    cout << "\n--- " << test_name << " ---\n";
}

int main() {
    LinkedList list;

    // TEST 1: Basic Building (Front and Back)
    print_test_header("Test 1: Building List");
    list.insert_end(10);
    list.insert_end(20);
    list.insert_front(5);
    // Expected: 5 10 20
    cout << "List content: ";
    list.print();
    cout << "Length: " << list.getLength() << endl;

    // TEST 2: Inserting in the Middle
    print_test_header("Test 2: Insert After & Before");
    list.insert_after(15, 10);  // Insert 15 after 10
    list.insert_before(7, 10);  // Insert 7 before 10
    // Expected: 5 7 10 15 20
    cout << "List content: ";
    list.print();

    // TEST 3: Edge Case Insertion
    print_test_header("Test 3: Insert at ends using Middle functions");
    list.insert_before(1, 5);   // Insert before head
    list.insert_after(25, 20);  // Insert after tail
    // Expected: 1 5 7 10 15 20 25
    cout << "List content: ";
    list.print();

    // TEST 4: Deletion
    print_test_header("Test 4: Deletions (Front, End, Value)");
    list.delete_front();        // Removes 1
    list.delete_end();          // Removes 25
    list.delete_nodes_with_value(10); // Removes 10
    // Expected: 5 7 15 20
    cout << "List content: ";
    list.print();

    // TEST 5: Edge Case - Value not found
    print_test_header("Test 5: Delete value that doesn't exist");
    list.delete_nodes_with_value(999);
    // Expected: No change (5 7 15 20)
    cout << "List content: ";
    list.print();

    // TEST 6: Get Value safely
    print_test_header("Test 6: Get Value At Index");
    try {
        cout << "Index 0: " << list.getValueAt(0) << endl; // 5
        cout << "Index 2: " << list.getValueAt(2) << endl; // 15
        cout << "Index 99 (Error): ";
        cout << list.getValueAt(99) << endl; // Should crash/throw
    } catch (const exception& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }

    // TEST 7: Destructor check
    print_test_header("Test 7: Exiting program");
    cout << "Destructor will run automatically now to clean up remaining "
         << list.getLength() << " nodes.\n";

    return 0;
}