#include <iostream>
#include "lib/Complex.h"

int main() {
    std::cout << "--- Complex Number Class Test ---\n";

    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);

    // Test Stream Output
    std::cout << "c1: " << c1 << "\n";
    std::cout << "c2: " << c2 << "\n";

    // Test Binary Arithmetic (Friend functions)
    Complex sum = c1 + c2;
    Complex diff = c1 - c2;
    Complex prod = c1 * c2;
    Complex div = c1 / c2;

    std::cout << "Sum (c1 + c2): " << sum << "\n";
    std::cout << "Diff (c1 - c2): " << diff << "\n";
    std::cout << "Prod (c1 * c2): " << prod << "\n";
    std::cout << "Div (c1 / c2): " << div << "\n";

    // Test Symmetry (Double + Complex)
    Complex symCheck = 5.0 + c1;
    std::cout << "Symmetry (5.0 + c1): " << symCheck << "\n";

    // Test Compound Assignment
    c1 += c2;
    std::cout << "Compound += (c1 += c2): " << c1 << "\n";

    // Test Unary
    Complex c3(10, 10);
    std::cout << "Original c3: " << c3 << "\n";
    std::cout << "Prefix ++c3: " << ++c3 << "\n";
    std::cout << "Postfix c3++: " << c3++ << "\n"; 
    std::cout << "After Postfix: " << c3 << "\n";

    // Test Subscript
    std::cout << "Real part via c3[0]: " << c3[0] << "\n";
    c3[1] = 99.9;
    std::cout << "Modified imag via c3[1]: " << c3 << "\n";

    // Test Functor (Function call)
    std::cout << "Function call: " << c3() << "\n";

    // Test Comparison
    Complex a(1, 1);
    Complex b(1, 1);
    if (a == b) std::cout << "Equality Check: Passed\n";

    return 0;
}
