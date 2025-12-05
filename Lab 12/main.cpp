#include <iostream>
#include "lib/Rect.h"
#include "lib/Triangle.h"
#include "lib/Circle.h"
#include "lib/Square.h"

using namespace std;

int main() {
    Rect r(10, 20);
    cout << "Rectangle Area: " << r.calculateArea() << endl;

    Triangle t(10, 20);
    cout << "Triangle Area: " << t.calculateArea() << endl;

    Circle c(5);
    cout << "Circle Area: " << c.calculateArea() << endl;

    Square s(5);
    cout << "Square Area: " << s.calculateArea() << endl;

    return 0;
}