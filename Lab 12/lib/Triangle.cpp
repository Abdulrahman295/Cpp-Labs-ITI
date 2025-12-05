#include "Triangle.h"

Triangle::Triangle() : GeoShape() {}

Triangle::Triangle(float b, float h) : GeoShape(b, h) {}

float Triangle::calculateArea() {
    return 0.5 * dim1 * dim2;
}