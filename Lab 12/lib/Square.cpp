#include "Square.h"

Square::Square() : Rect() {}

Square::Square(float x) : Rect(x, x) {}

void Square::setSquareDim(float x) {
    this->setDim1(x);
    this->setDim2(x);
}

float Square::getSquareDim() {
    return getDim1();
}

float Square::calculateArea() {
    return Rect::calculateArea();
}