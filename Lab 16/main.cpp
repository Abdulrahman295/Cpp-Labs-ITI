#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

// Helper function to print test results clearly
void report(const string& message, bool passed) {
    cout << message << ": " << (passed ? "PASSED" : "FAILED") << endl;
}

int main() {
    cout << "--- Starting Binary Search Tree Tests ---" << endl;

    // 1. Create the Tree
    BinarySearchTree bst;

    cout << "\nInserting nodes: 50, 30, 20, 40, 70, 60, 80..." << endl;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    // 3. Test SEARCH
    cout << "\n--- Testing Search ---" << endl;
    report("Search 50 (Root)", bst.search(50) == true);
    report("Search 20 (Leaf)", bst.search(20) == true);
    report("Search 99 (Not Exists)", bst.search(99) == false);

    // 4. Test UTILITIES
    cout << "\n--- Testing Stats ---" << endl;
    cout << "Min Value (Expected 20): " << bst.getMin() << endl;
    cout << "Max Value (Expected 80): " << bst.getMax() << endl;
    cout << "Tree Depth (Expected 3): " << bst.getDepth() << endl;

    // 5. Test DELETE
    cout << "\n--- Testing Delete ---" << endl;

    // Case 1: Delete Leaf (20)
    bst.remove(20);
    report("Delete Leaf (20) - verify removed", bst.search(20) == false);

    // Case 2: Delete Node with One Child
    bst.remove(30);
    report("Delete One Child (30) - verify removed", bst.search(30) == false);
    report("Verify child (40) is still there", bst.search(40) == true);

    // Case 3: Delete Node with Two Children (50 - The Root)
    bst.remove(50);
    report("Delete Root (50) - verify removed", bst.search(50) == false);
    report("Verify successor (60) is preserved", bst.search(60) == true);
    report("Verify other child (70) is preserved", bst.search(70) == true);

    cout << "\n--- All Tests Finished ---" << endl;

    return 0;
}