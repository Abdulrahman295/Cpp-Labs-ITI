#include "GeoShape.h"

GeoShape::GeoShape() {
    dim1 = dim2 = 0;
}

GeoShape::GeoShape(float x) {
    dim1 = dim2 = x;
}

GeoShape::GeoShape(float x, float y) {
    dim1 = x;
    dim2 = y;
}

void GeoShape::setDim1(float x) {
    dim1 = x;
}

void GeoShape::setDim2(float x) {
    dim2 = x;
}

float GeoShape::getDim1() {
    return dim1;
}

float GeoShape::getDim2() {
    return dim2;
}

float GeoShape::calculateArea() {
    return 0;
}