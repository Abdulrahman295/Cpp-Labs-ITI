#include <iostream>
#include <sstream> // For testing operator>>
#include "lib/MyString.h"

using namespace Custom;

void printTestHeader(const char* testName) {
    std::cout << "\n================ " << testName << " ================\n";
}

void printString(const char* label, const String& s) {
    std::cout << label << ": \"" << s << "\" (Len: " << s.length() << ", Cap: " << s.capacity() << ")\n";
}

int main() {
    // --- 1. Constructors ---
    printTestHeader("Constructors");

    String s1;
    printString("Default s1", s1);

    String s2("Hello World");
    printString("C-String s2", s2);

    String s3(s2);
    printString("Copy of s2 (s3)", s3);

    String s4;
    s4 = s2;
    printString("Assigned s4 = s2", s4);


    // --- 2. Element Access ---
    printTestHeader("Element Access");

    std::cout << "s2[0]: " << s2[0] << "\n";
    std::cout << "s2.at(6): " << s2.at(6) << "\n";
    std::cout << "s2.front(): " << s2.front() << "\n";
    std::cout << "s2.back(): " << s2.back() << "\n";

    try {
        s2.at(100);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected error: " << e.what() << "\n";
    }


    // --- 3. Modifiers (Append & Operator+=) ---
    printTestHeader("Append & +=");

    String s5("Hello");
    s5.append(" World");
    printString("Append ' World'", s5);

    s5 += "!";
    printString("+= '!'", s5);

    s5 += '!';
    printString("+= char '!'", s5);


    // --- 4. Modifiers (Insert) ---
    printTestHeader("Insert");

    String s6("Hello!");
    s6.insert(5, " World");
    printString("Insert at 5", s6);

    s6.insert(0, "Start: ");
    printString("Insert at start", s6);


    // --- 5. Modifiers (Erase) ---
    printTestHeader("Erase");

    String s7("Hello My World");
    s7.erase(5, 3);
    printString("Erase ' My'", s7);

    s7.erase(0, 1);
    printString("Erase first char", s7);


    // --- 6. Modifiers (Replace) ---
    printTestHeader("Replace");

    String s8("I like C");
    s8.replace(7, 1, "C++"); 
    printString("Replace C with C++", s8);


    // --- 7. Manipulation (Upper/Lower/Substr) ---
    printTestHeader("Manipulation");

    String s9("AbCdEfG");
    s9.toLower();
    printString("toLower", s9);

    s9.toUpper();
    printString("toUpper", s9);

    String sub = s9.substr(2, 3);
    printString("Substr(2, 3)", sub);


    // --- 8. Search (Find) ---
    printTestHeader("Find");

    String s10("Banana");
    size_t pos1 = s10.find("nana");
    size_t pos2 = s10.find("z");

    std::cout << "Find 'nana' in 'Banana': " << (pos1 != String::npos ? std::to_string(pos1) : "Not Found") << "\n";
    std::cout << "Find 'z' in 'Banana': " << (pos2 != String::npos ? std::to_string(pos2) : "Not Found") << "\n";


    // --- 9. Comparison Operators ---
    printTestHeader("Comparison");

    String a("Apple");
    String b("Banana");
    String c("Apple");

    std::cout << "Apple == Banana? " << (a == b ? "True" : "False") << "\n";
    std::cout << "Apple == Apple?  " << (a == c ? "True" : "False") << "\n";
    std::cout << "Apple != Banana? " << (a != b ? "True" : "False") << "\n";
    std::cout << "Apple < Banana?  " << (a < b ? "True" : "False") << "\n";
    std::cout << "Banana > Apple?  " << (b > a ? "True" : "False") << "\n";


    // --- 10. Operator+ (Concatenation) ---
    printTestHeader("Operator+");

    String s11 = a + " Pie";
    printString("Apple + Pie", s11);


    // --- 11. Stream I/O ---
    printTestHeader("Stream I/O");

    std::cout << "Testing << operator: " << s11 << "\n";

    std::cout << "Testing >> operator (Simulated Input 'InputTest'): ";
    std::stringstream ss("InputTest");
    String s12;
    ss >> s12;
    std::cout << "Read value: " << s12 << "\n";

    // --- 12. Clear ---
    printTestHeader("Clear");
    s12.clear();
    printString("After clear", s12);
    std::cout << "Is empty? " << (s12.empty() ? "Yes" : "No") << "\n";

    return 0;
}