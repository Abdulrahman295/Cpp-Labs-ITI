#include "Circle.h"

Circle::Circle() : GeoShape() {}

Circle::Circle(float r) : GeoShape(r) {}

void Circle::setRadius(float r) {
    this->setDim1(r);
    this->setDim2(r);
}

float Circle::getRadius() {
    return dim1;
}

float Circle::calculateArea() {
    return 3.14159 * dim1 * dim2;
}