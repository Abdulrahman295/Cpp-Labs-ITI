#include <iostream>
#include "QueueList.h" // Ensure this matches your filename

using namespace std;

void print_test_header(string test_name) {
    cout << "\n--- " << test_name << " ---\n";
}

int main() {
    QueueList q;

    // TEST 1: Enqueue (Adding items)
    print_test_header("Test 1: Enqueueing items");
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    // Expected: 10 20 30 (10 is at the front)
    cout << "Queue content: ";
    q.print();

    // TEST 2: Dequeue (Removing items)
    // In a Queue, the FIRST item added (10) should be the FIRST removed.
    print_test_header("Test 2: Dequeueing items (FIFO Check)");

    int removed = q.dequeue();
    cout << "Dequeued: " << removed << endl; // Expected: 10

    cout << "Queue content: ";
    q.print(); // Expected: 20 30

    // TEST 3: Empty Check
    print_test_header("Test 3: Empty Check");
    cout << "Is empty? " << (q.isEmpty() ? "Yes" : "No") << endl; // No

    q.dequeue(); // remove 20
    q.dequeue(); // remove 30

    cout << "Dequeued remaining items. Is empty now? "
         << (q.isEmpty() ? "Yes" : "No") << endl; // Yes

    // TEST 4: Error Handling (Underflow)
    print_test_header("Test 4: Dequeue from Empty Queue");
    try {
        // The queue is empty now. This should throw the exception
        // defined in your LinkedList::getValueAt()
        q.dequeue();
    } catch (const exception& e) {
        cout << "Success! Caught expected error: " << e.what() << endl;
    }

    return 0;
}